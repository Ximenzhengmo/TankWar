#include "tank.h"
#include "lcd_driver.h"
#include "stdio.h"

Tank_T redTank = {
        .bulletNum =  5,
        .tankImage =  redTankImage,
        .direction = 0,
        .xPos =  0,
        .yPos =  0,
};
Tank_T greenTank = {
        .bulletNum =  5,
        .tankImage =  greenTankImage,
        .direction = 0,
        .xPos =  0,
        .yPos =  0,
};

void tank_Init(Tank_T *tank) {
    static uint32_t RNG_Value;
    tank->bulletNum = 5;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK) {
        RNG_Value = 0;
    }
    tank->direction = RNG_Value % 20;
    uint8_t xHalfLenOfImage = tank->tankImage[tank->direction].xLen >> 1;
    uint8_t yHalfLenOfImage = tank->tankImage[tank->direction].yLen >> 1;
    do {
        HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value);
        tank->xPos = RNG_Value % ScreenXLen;
        HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value);
        tank->yPos = RNG_Value % ScreenYLen;
    } while (isTankTouchWall((Point_T) {tank->xPos - xHalfLenOfImage,
                                        tank->yPos - yHalfLenOfImage},
                             (Point_T) {tank->xPos + xHalfLenOfImage - 1,
                                        tank->yPos - yHalfLenOfImage},
                             (Point_T) {tank->xPos - xHalfLenOfImage,
                                        tank->yPos + yHalfLenOfImage - 1},
                             (Point_T) {tank->xPos + xHalfLenOfImage - 1,
                                        tank->yPos + yHalfLenOfImage - 1}));
}

void LCD_ClearToBackground(Point_T LeftUp, Point_T RightDown) {
    uint16_t xLen = RightDown.x - LeftUp.x + 1;
    uint16_t yLen = RightDown.y - LeftUp.y + 1;
    LCD_Fill(LeftUp.x, LeftUp.y, xLen, yLen, (uint8_t *) whiteBackground);
}

DirectionAdd_T getDirectionAdd(uint8_t newDirection) {
    // 26 * 38   0 ->         y+=-1 ,       y+=-2
    // 32 * 40  18 ->         y+=-2 , x+=-1 y+=-1
    // 38 * 40  36 ->   x+=-1 y+=-1 , x+=-1 y+=-2 , x+=-1 y+=-1
    // 40 * 38  54 ->   x+=-1 y+=-1 , x+=-2 y+=-1 , x+=-1 y+=-1
    // 40 * 32  72 ->   x+=-1       , x+=-2 y+=-1
    static const DirectionAdd_T directionAdd[DIRECTION_FIRST_DIM_LEN][3] = {
            {{0,  -1}, {0,  -2}, {0,  0}},
            {{0,  -2}, {-1, -1}, {0,  0}},
            {{-1, -1}, {-1, -2}, {-1, -1}},
            {{-1, -1}, {-2, -1}, {-1, -1}},
            {{-1, 0},  {-2, -1}, {0,  0}},
    };
    static uint8_t subscript[DIRECTION_FIRST_DIM_LEN] = {1, 1, 2, 1, 1};
    static uint8_t sub;
    uint8_t degreeMap = newDirection % DIRECTION_FIRST_DIM_LEN;
    if (degreeMap == 2 || degreeMap == 3) {
        sub = (subscript[degreeMap] = (subscript[degreeMap] + 1) % 3);
    } else {
        sub = (subscript[degreeMap] = (subscript[degreeMap] + 1) % 2);
    }
    switch (newDirection / DIRECTION_FIRST_DIM_LEN) {
        case 0: // [0 , 90)
            return (DirectionAdd_T) {
                    .x_add =   directionAdd[degreeMap][sub].x_add,
                    .y_add =   directionAdd[degreeMap][sub].y_add,
            };
        case 1: // [90, 180)
            return (DirectionAdd_T) {
                    .x_add =   directionAdd[degreeMap][sub].y_add,
                    .y_add = -directionAdd[degreeMap][sub].x_add,
            };
        case 2: // [180, 270)
            return (DirectionAdd_T) {
                    .x_add = -directionAdd[degreeMap][sub].x_add,
                    .y_add = -directionAdd[degreeMap][sub].y_add,
            };
        case 3: // [270, 360)
            return (DirectionAdd_T) {
                    .x_add = -directionAdd[degreeMap][sub].y_add,
                    .y_add =  directionAdd[degreeMap][sub].x_add,
            };
        default:
            printf("newDirection = %d\n", newDirection);
            perror("In tank.c : getDirectionAdd(uint8_t newDirection) error");
            return (DirectionAdd_T) {0, 0};
    }
}

uint8_t tankMove_clear(Tank_T *tank, DirectionAdd_T directionAdd, uint8_t newDirection) {
#define InRange(pos, pos1, pos4) (((pos).x >= (pos1).x && (pos).x <= (pos4).x) && ((pos).y >= (pos1).y && (pos).y <= (pos4).y))
    static Point_T old1, old2, old3, old4;
    static Point_T new1, new2, new3, new4;
    static Point_T oldPos;
    static Point_T newPos;
    static uint8_t OldXLen, OldYLen, NewXLen, NewYLen;
    static uint8_t isOld1InRange, isOld2InRange, isOld3InRange, isOld4InRange;
    OldXLen = tank->tankImage[tank->direction].xLen;
    OldYLen = tank->tankImage[tank->direction].yLen;
    NewXLen = tank->tankImage[newDirection].xLen;
    NewYLen = tank->tankImage[newDirection].yLen;
    oldPos.x = tank->xPos;
    oldPos.y = tank->yPos;
    newPos.x = tank->xPos + directionAdd.x_add;
    newPos.y = tank->yPos + directionAdd.y_add;
    old1.x = oldPos.x - (OldXLen >> 1);
    old1.y = oldPos.y - (OldYLen >> 1);
    old2.x = oldPos.x + (OldXLen >> 1) - 1;
    old2.y = oldPos.y - (OldYLen >> 1);
    old3.x = oldPos.x - (OldXLen >> 1);
    old3.y = oldPos.y + (OldYLen >> 1) - 1;
    old4.x = oldPos.x + (OldXLen >> 1) - 1;
    old4.y = oldPos.y + (OldYLen >> 1) - 1;
    new1.x = newPos.x - (NewXLen >> 1);
    new1.y = newPos.y - (NewYLen >> 1);
    new2.x = newPos.x + (NewXLen >> 1) - 1;
    new2.y = newPos.y - (NewYLen >> 1);
    new3.x = newPos.x - (NewXLen >> 1);
    new3.y = newPos.y + (NewYLen >> 1) - 1;
    new4.x = newPos.x + (NewXLen >> 1) - 1;
    new4.y = newPos.y + (NewYLen >> 1) - 1;
    if (isTankTouchWall(new1, new2, new3, new4)) {
        return 0;
    }
    isOld1InRange = InRange(old1, new1, new4);
    isOld2InRange = InRange(old2, new1, new4);
    isOld3InRange = InRange(old3, new1, new4);
    isOld4InRange = InRange(old4, new1, new4);
    switch (isOld1InRange + isOld2InRange + isOld3InRange + isOld4InRange) {
        case 4:
        case 3:
            break;
        case 2:
            if (isOld1InRange) {
                if (isOld2InRange) {
                    LCD_ClearToBackground((Point_T) {old3.x, new3.y}, old4);
                } else if (isOld3InRange) {
                    LCD_ClearToBackground((Point_T) {new2.x, old2.y}, old4);
                } else {
                    perror("tankMove_clear error");
                }
            } else {
                if (isOld2InRange) {
                    LCD_ClearToBackground(old1, (Point_T) {new3.x, old3.y});
                } else if (isOld3InRange) {
                    LCD_ClearToBackground(old1, (Point_T) {old2.x, new2.y});
                } else {
                    perror("tankMove_clear error");
                }
            }
            break;
        case 1:
            if (isOld1InRange) {
                LCD_ClearToBackground((Point_T) {new4.x, old1.y}, old4);
                LCD_ClearToBackground((Point_T) {old3.x, new3.y}, (Point_T) {new4.x, old4.y});
            } else if (isOld2InRange) {
                LCD_ClearToBackground(old1, (Point_T) {new1.x, old3.y});
                LCD_ClearToBackground(new3, old4);
            } else if (isOld3InRange) {
                LCD_ClearToBackground(old1, (Point_T) {old2.x, new2.y});
                LCD_ClearToBackground(new2, old4);
            } else {
                LCD_ClearToBackground(old1, (Point_T) {new1.x, old3.y});
                LCD_ClearToBackground((Point_T) {new1.x, old1.y}, (Point_T) {old2.x, new2.y});
            }
            break;
        case 0:
//            LCD_Fill(old1.x, old1.y, OldXLen, OldYLen, whiteBackground);
            if (old1.x <= new1.x && old1.y <= new1.y) {
                if (old4.x >= new4.x && (old4.y >= new2.y && old4.y <= new4.y)) {
                    LCD_ClearToBackground(old1, (Point_T) {old2.x, new2.y});
                    LCD_ClearToBackground((Point_T) {old1.x, new1.y}, (Point_T) {new3.x, old3.y});
                    LCD_ClearToBackground(new2, old4);
                } else if (old4.y >= new4.y && old4.x >= new4.x) {
                    LCD_ClearToBackground(old1, (Point_T) {new3.x, old3.y});
                    LCD_ClearToBackground((Point_T) {new1.x, old1.y}, (Point_T) {old2.x, new2.y});
                    LCD_ClearToBackground(new3, old4);
                    LCD_ClearToBackground(new2, (Point_T) {old4.x, new4.y});
                } else if (old4.y >= new4.y && (old4.x >= new3.x && old4.x <= new4.x)) {
                    LCD_ClearToBackground(old1, (Point_T) {new3.x, old3.y});
                    LCD_ClearToBackground(new3, old4);
                    LCD_ClearToBackground((Point_T) {new1.x, old1.y}, (Point_T) {old2.x, new2.y});
                }
            } else if (old1.x >= new1.x && old1.y <= new1.y) {
                if (old4.y >= new4.y && old4.x >= new4.x) {
                    LCD_ClearToBackground(old1, new2);
                    LCD_ClearToBackground((Point_T) {new2.x, old2.y}, old4);
                    LCD_ClearToBackground((Point_T) {old3.x, new3.y}, (Point_T) {new4.x, old4.y});
                } else if (old4.y >= new4.y && (old4.x >= new3.x && old4.x <= new4.x)) {
                    LCD_ClearToBackground(old1, (Point_T) {old2.x, new2.y});
                    LCD_ClearToBackground((Point_T) {old3.x, new3.y}, old4);
                }
            } else if (old1.x <= new1.x && old1.y >= new1.y) {
                if (old4.x >= new4.x && (old4.y >= new2.y && old4.y <= new4.y)) {
                    LCD_ClearToBackground(old1, (Point_T) {new3.x, old3.y});
                    LCD_ClearToBackground((Point_T) {new2.x, old2.y}, old4);
                } else if (old4.y >= new4.y && old4.x >= new4.x) {
                    LCD_ClearToBackground(old1, (Point_T) {new3.x, old3.y});
                    LCD_ClearToBackground(new3, old4);
                    LCD_ClearToBackground((Point_T) {new2.x, old2.y}, (Point_T) {old4.x, new4.y});
                }
            }
            break;
    }
    tank->xPos = newPos.x;
    tank->yPos = newPos.y;
    tank->direction = newDirection;
    return 1;
}

uint8_t isTankTouchWall(Point_T p1, Point_T p2, Point_T p3, Point_T p4) {
    if ((0 < p1.x && p1.x < ScreenXLen && 0 < p1.y && p1.y < ScreenYLen)
        && (0 < p2.x && p2.x < ScreenXLen && 0 < p2.y && p2.y < ScreenYLen)
        && (0 < p3.x && p3.x < ScreenXLen && 0 < p3.y && p3.y < ScreenYLen)
        && (0 < p4.x && p4.x < ScreenXLen && 0 < p4.y && p4.y < ScreenYLen)) {

        for (uint16_t i = p1.x; i < p2.x; i += wallWidth) if (isWall(i, p1.y)) return 1;
        for (uint16_t i = p3.x; i < p4.x; i += wallWidth) if (isWall(i, p3.y)) return 1;
        for (uint16_t i = p1.y; i < p3.y; i += wallWidth) if (isWall(p1.x, i)) return 1;
        for (uint16_t i = p2.y; i < p4.y; i += wallWidth) if (isWall(p2.x, i)) return 1;

        return 0; // not touch wall
    } else {
        return 1; // touch wall
    }
}

void drawTank(Tank_T *tank, uint8_t direction) {
    if (direction < 20) {
        DirectionAdd_T directionAdd = getDirectionAdd(direction);
        tankMove_clear(tank, directionAdd, direction);
    }
    LCD_Fill(tank->xPos - (tank->tankImage[tank->direction].xLen >> 1),
             tank->yPos - (tank->tankImage[tank->direction].yLen >> 1),
             tank->tankImage[tank->direction].xLen,
             tank->tankImage[tank->direction].yLen,
             (uint8_t *) tank->tankImage[tank->direction].image);
}

const TankImage_T redTankImage[20] = {
        {.image=gImage_red0, .xLen=26, .yLen=38,  .crashTest=&crashTest[0]},
        {.image=gImage_red18, .xLen=32, .yLen=40, .crashTest=&crashTest[1]},
        {.image=gImage_red36, .xLen=38, .yLen=40, .crashTest=&crashTest[2]},
        {.image=gImage_red54, .xLen=40, .yLen=38, .crashTest=&crashTest[3]},
        {.image=gImage_red72, .xLen=40, .yLen=32, .crashTest=&crashTest[4]},

        {.image=gImage_red90, .xLen=38, .yLen=26,  .crashTest=&crashTest[5]},
        {.image=gImage_red108, .xLen=40, .yLen=32, .crashTest=&crashTest[6]},
        {.image=gImage_red126, .xLen=40, .yLen=38, .crashTest=&crashTest[7]},
        {.image=gImage_red144, .xLen=38, .yLen=40, .crashTest=&crashTest[8]},
        {.image=gImage_red162, .xLen=32, .yLen=40, .crashTest=&crashTest[9]},

        {.image=gImage_red180, .xLen=26, .yLen=38,.crashTest=&crashTest[10]},
        {.image=gImage_red198, .xLen=32, .yLen=40,.crashTest=&crashTest[11]},
        {.image=gImage_red216, .xLen=38, .yLen=40,.crashTest=&crashTest[12]},
        {.image=gImage_red234, .xLen=40, .yLen=38,.crashTest=&crashTest[13]},
        {.image=gImage_red252, .xLen=40, .yLen=32,.crashTest=&crashTest[14]},

        {.image=gImage_red270, .xLen=38, .yLen=26,.crashTest=&crashTest[15]},
        {.image=gImage_red288, .xLen=40, .yLen=32,.crashTest=&crashTest[16]},
        {.image=gImage_red306, .xLen=40, .yLen=38,.crashTest=&crashTest[17]},
        {.image=gImage_red324, .xLen=38, .yLen=40,.crashTest=&crashTest[18]},
        {.image=gImage_red342, .xLen=32, .yLen=40,.crashTest=&crashTest[19]},
};

const TankImage_T greenTankImage[20] = {
        {.image=gImage_green0, .xLen=26, .yLen=38, .crashTest=&crashTest[0]},
        {.image=gImage_green18, .xLen=32, .yLen=40,.crashTest=&crashTest[1]},
        {.image=gImage_green36, .xLen=38, .yLen=40,.crashTest=&crashTest[2]},
        {.image=gImage_green54, .xLen=40, .yLen=38,.crashTest=&crashTest[3]},
        {.image=gImage_green72, .xLen=40, .yLen=32,.crashTest=&crashTest[4]},

        {.image=gImage_green90, .xLen=38, .yLen=26, .crashTest=&crashTest[5]},
        {.image=gImage_green108, .xLen=40, .yLen=32,.crashTest=&crashTest[6]},
        {.image=gImage_green126, .xLen=40, .yLen=38,.crashTest=&crashTest[7]},
        {.image=gImage_green144, .xLen=38, .yLen=40,.crashTest=&crashTest[8]},
        {.image=gImage_green162, .xLen=32, .yLen=40,.crashTest=&crashTest[9]},

        {.image=gImage_green180, .xLen=26, .yLen=38,.crashTest=&crashTest[10]},
        {.image=gImage_green198, .xLen=32, .yLen=40,.crashTest=&crashTest[11]},
        {.image=gImage_green216, .xLen=38, .yLen=40,.crashTest=&crashTest[12]},
        {.image=gImage_green234, .xLen=40, .yLen=38,.crashTest=&crashTest[13]},
        {.image=gImage_green252, .xLen=40, .yLen=32,.crashTest=&crashTest[14]},

        {.image=gImage_green270, .xLen=38, .yLen=26,.crashTest=&crashTest[15]},
        {.image=gImage_green288, .xLen=40, .yLen=32,.crashTest=&crashTest[16]},
        {.image=gImage_green306, .xLen=40, .yLen=38,.crashTest=&crashTest[17]},
        {.image=gImage_green324, .xLen=38, .yLen=40,.crashTest=&crashTest[18]},
        {.image=gImage_green342, .xLen=32, .yLen=40,.crashTest=&crashTest[19]},
};


