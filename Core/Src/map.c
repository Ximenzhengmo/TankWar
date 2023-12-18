#include "map.h"

#define MALLOC(X) (X*)malloc(sizeof(X))

static uint64_t bool_is_in_tree = 0;
static Box_T box[XMAX][YMAX];
static Node_T *head = NULL;
uint16_t MapXLen = XMAX * boxSideLen;
uint16_t MapYLen = YMAX * boxSideLen;

void setVisited(uint8_t id) {
    bool_is_in_tree |= (1ULL << id);
}

uint8_t isVisited(uint8_t id) {
    return (((1ULL << id) & bool_is_in_tree) != 0ULL);
}

void insertWallToList(Node_T *headList, Wall_T wall) {
    Node_T *node = MALLOC(Node_T);
    if (node == NULL) {
        printf("malloc error\n");
        exit(1);
    }
    node->property.wall = wall;
    node->next = headList->next;
    headList->next = node;
    headList->property.num++;
}

uint8_t isWallListEmpty(Node_T *headList) {
    return headList->next == NULL;
}

void insertAllWall(Node_T *headList, const Box_T *boxInMap) {
    if (boxInMap->up == 0 && !isVisited(boxInMap->id - XMAX)) {
        insertWallToList(headList, (Wall_T) {boxInMap->id, boxInMap->id - XMAX});
    }
    if (boxInMap->down == 0 && !isVisited(boxInMap->id + XMAX)) {
        insertWallToList(headList, (Wall_T) {boxInMap->id, boxInMap->id + XMAX});
    }
    if (boxInMap->left == 0 && !isVisited(boxInMap->id - 1)) {
        insertWallToList(headList, (Wall_T) {boxInMap->id, boxInMap->id - 1});
    }
    if (boxInMap->right == 0 && !isVisited(boxInMap->id + 1)) {
        insertWallToList(headList, (Wall_T) {boxInMap->id, boxInMap->id + 1});
    }
}

Wall_T popWallFromList(Node_T *headList) {
    Node_T *node = headList;
    Wall_T wall;
    if (node->next == NULL) {
        printf("list is empty\n");
        exit(1);
    }
    uint32_t RNG_num;
    uint8_t index;
    if( HAL_RNG_GenerateRandomNumber(&hrng, &RNG_num) != HAL_OK ){
        RNG_num = HAL_GetTick();
    }
    index = (uint8_t) (RNG_num % node->property.num);
    for (uint8_t i = 0; i < index; ++i) {
        node = node->next;
    }
    wall = node->next->property.wall;
    Node_T *temp = node->next;
    node->next = node->next->next;
    free(temp);
    headList->property.num--;
    return wall;
}

HAL_StatusTypeDef createMap() {
    // 初始化
    bool_is_in_tree = 0;
    head = NULL;
    for (uint8_t i = 0; i < XMAX; ++i) {
        for (uint8_t j = 0; j < YMAX; ++j) {
            memset(&box[i][j], 0, sizeof(Box_T));
        }
    }
    srand(HAL_GetTick());
    // 保护墙体
    for (uint8_t i = 0; i < XMAX; ++i) {
        box[i][0].up = 1;
        box[i][YMAX - 1].down = 1;
    }
    for (uint8_t i = 0; i < YMAX; ++i) {
        box[0][i].left = 1;
        box[XMAX - 1][i].right = 1;
    }
    for (uint8_t i = 0; i < XMAX; ++i) {
        for (uint8_t j = 0; j < YMAX; ++j) {
            box[i][j].id = i + j * XMAX;
            box[i][j].x = i;
            box[i][j].y = j;
        }
    }
    head = MALLOC(Node_T);
    head->next = NULL;
    head->property.num = 0;
    // 生成迷宫
    insertAllWall(head, &box[0][0]);
    while (!isWallListEmpty(head)) {
        Wall_T wall = popWallFromList(head);
        if (isVisited(wall.outBox_id)) {
            continue;
        }
        Box_T *boxOutMap = &box[wall.outBox_id % XMAX][wall.outBox_id / XMAX];
        Box_T *boxInMap = &box[wall.inBox_id % XMAX][wall.inBox_id / XMAX];
        if (wall.outBox_id == wall.inBox_id - XMAX) {
            boxOutMap->down = 1;
            boxInMap->up = 1;
        } else if (wall.outBox_id == wall.inBox_id + XMAX) {
            boxOutMap->up = 1;
            boxInMap->down = 1;
        } else if (wall.outBox_id == wall.inBox_id - 1) {
            boxOutMap->right = 1;
            boxInMap->left = 1;
        } else if (wall.outBox_id == wall.inBox_id + 1) {
            boxOutMap->left = 1;
            boxInMap->right = 1;
        } else {
            return HAL_ERROR;
        }
        setVisited(boxOutMap->id);
        insertAllWall(head, boxOutMap);
    }
    // 消除保护墙体
    for (uint8_t i = 0; i < XMAX; ++i) {
        box[i][0].up = 0;
        box[i][YMAX - 1].down = 0;
    }
    for (uint8_t i = 0; i < YMAX; ++i) {
        box[0][i].left = 0;
        box[XMAX - 1][i].right = 0;
    }
    free(head);
    return HAL_OK;
}

uint8_t isWall(uint16_t x, uint16_t y) {
    uint8_t boxX;
    uint8_t boxY;
    uint8_t boxXOffset;
    uint8_t boxYOffset;
#if boxSideLen == 64
        boxX = x >> 6;
        boxY = y >> 6;
        boxXOffset = x & 0x3F;
        boxYOffset = y & 0x3F;
#else
        boxX = x / boxSideLen;
        boxY = y / boxSideLen;
        boxXOffset = x % boxSideLen;
        boxYOffset = y % boxSideLen;
#endif
    if( boxXOffset < wallWidth ){
        if( boxYOffset < wallWidth ){
            return !(box[boxX][boxY].up && box[boxX][boxY].left);
        }else if( boxYOffset < boxSideLen - wallWidth ){
            return !box[boxX][boxY].left;
        }else{
            return !(box[boxX][boxY].left && box[boxX][boxY].down);
        }
    }else if( boxXOffset < boxSideLen - wallWidth ){
        if( boxYOffset < wallWidth ){
            return !box[boxX][boxY].up;
        }else if( boxYOffset < boxSideLen - wallWidth ){
            return 0;
        }else{
            return !box[boxX][boxY].down;
        }
    }else{
        if( boxYOffset < wallWidth ){
            return !(box[boxX][boxY].up && box[boxX][boxY].right);
        }else if( boxYOffset < boxSideLen - wallWidth ){
            return !box[boxX][boxY].right;
        }else{
            return !(box[boxX][boxY].right && box[boxX][boxY].down);
        }
    }
}


uint8_t isTouchWall(Point_T p1, Point_T p2, Point_T p3, Point_T p4) {
    if ((0 < p1.x && p1.x < MapXLen && 0 < p1.y && p1.y < MapYLen)
        && (0 < p2.x && p2.x < MapXLen && 0 < p2.y && p2.y < MapYLen)
        && (0 < p3.x && p3.x < MapXLen && 0 < p3.y && p3.y < MapYLen)
        && (0 < p4.x && p4.x < MapXLen && 0 < p4.y && p4.y < MapYLen)) {

        for (uint16_t i = p1.x; i < p2.x; i += wallWidth) if (isWall(i, p1.y)) return 1;
        for (uint16_t i = p3.x; i < p4.x; i += wallWidth) if (isWall(i, p3.y)) return 1;
        for (uint16_t i = p1.y; i < p3.y; i += wallWidth) if (isWall(p1.x, i)) return 1;
        for (uint16_t i = p2.y; i < p4.y; i += wallWidth) if (isWall(p2.x, i)) return 1;

        return 0; // not touch wall
    } else {
        return 1; // touch wall
    }
}

void drawMap(){
    if ( createMap() == HAL_OK ) {
        LCD_SetWindows(0, 0, MapXLen - 1, MapYLen - 1);
        LCD_RS_SET();
        for (uint16_t j = 0; j < MapYLen; ++j) {
            for (uint16_t i = 0; i < MapXLen; ++i) {
                if (isWall(i, j)) {
                    Lcd_WriteData_16Bit(BLACK);
                } else {
                    Lcd_WriteData_16Bit(WHITE);
                }
            }
        }
    }
}