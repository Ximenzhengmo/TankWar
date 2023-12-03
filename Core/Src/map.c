#include "map.h"

#define MALLOC(X) (X*)malloc(sizeof(X))

static uint64_t bool_is_in_tree = 0;
static Box box[XMAX][YMAX];
static Node *head = NULL;
uint16_t ScreenXLen = XMAX * boxSideLen;
uint16_t ScreenYLen = YMAX * boxSideLen;

void setVisited(uint8_t id) {
    bool_is_in_tree |= (1ULL << id);
}

uint8_t isVisited(uint8_t id) {
    return (((1ULL << id) & bool_is_in_tree) != 0ULL);
}

void insertWallToList(Node *headList, Wall wall) {
    Node *node = MALLOC(Node);
    if (node == NULL) {
        printf("malloc error\n");
        exit(1);
    }
    node->property.wall = wall;
    node->next = headList->next;
    headList->next = node;
    headList->property.num++;
}

uint8_t isWallListEmpty(Node *headList) {
    return headList->next == NULL;
}

void insertAllWall(Node *headList, const Box *boxInMap) {
    if (boxInMap->up == 0 && !isVisited(boxInMap->id - XMAX)) {
        insertWallToList(headList, (Wall) {boxInMap->id, boxInMap->id - XMAX});
    }
    if (boxInMap->down == 0 && !isVisited(boxInMap->id + XMAX)) {
        insertWallToList(headList, (Wall) {boxInMap->id, boxInMap->id + XMAX});
    }
    if (boxInMap->left == 0 && !isVisited(boxInMap->id - 1)) {
        insertWallToList(headList, (Wall) {boxInMap->id, boxInMap->id - 1});
    }
    if (boxInMap->right == 0 && !isVisited(boxInMap->id + 1)) {
        insertWallToList(headList, (Wall) {boxInMap->id, boxInMap->id + 1});
    }
}

Wall popWallFromList(Node *headList) {
    Node *node = headList;
    Wall wall;
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
    Node *temp = node->next;
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
            memset(&box[i][j], 0, sizeof(Box));
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
    head = MALLOC(Node);
    head->next = NULL;
    head->property.num = 0;
    // 生成迷宫
    insertAllWall(head, &box[0][0]);
    while (!isWallListEmpty(head)) {
        Wall wall = popWallFromList(head);
        if (isVisited(wall.outBox_id)) {
            continue;
        }
        Box *boxOutMap = &box[wall.outBox_id % XMAX][wall.outBox_id / XMAX];
        Box *boxInMap = &box[wall.inBox_id % XMAX][wall.inBox_id / XMAX];
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

void drawMap(){
    if ( createMap() == HAL_OK ) {
        LCD_SetWindows(0, 0, ScreenXLen - 1, ScreenYLen - 1);
        LCD_RS_SET();
        for (uint16_t j = 0; j < ScreenYLen; ++j) {
            for (uint16_t i = 0; i < ScreenXLen; ++i) {
                if (isWall(i, j)) {
                    Lcd_WriteData_16Bit(BLACK);
                } else {
                    Lcd_WriteData_16Bit(WHITE);
                }
            }
        }
    }
}