#include "bullet.h"

Bullet_T bullets[BulletNumMax];

Bullet_T bullet_test = {
        .direction=6,
        .xPos=20,
        .yPos=20
};

uint8_t bulletNum = 0;

const unsigned char gImage_bullet[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
};


Bullet_Touch_State getBulletTouchWallState(uint8_t direction, Point_T p1, Point_T p2, Point_T p3, Point_T p4) {
#define boolIsWall(x, y) (isWall(x, y)!=0) // 0 is not wall, 1 is wall
    if ((0 <= p1.x && p1.x < MapXLen && 0 <= p1.y && p1.y < MapYLen)
        && (0 <= p2.x && p2.x < MapXLen && 0 <= p2.y && p2.y < MapYLen)
        && (0 <= p3.x && p3.x < MapXLen && 0 <= p3.y && p3.y < MapYLen)
        && (0 <= p4.x && p4.x < MapXLen && 0 <= p4.y && p4.y < MapYLen)) {
        int16_t cent_x = (p1.x + p2.x) >> 1, cent_y = (p1.y + p3.y) >> 1;
        uint8_t num1 = 0, num2 = 0;
        switch (direction) {
            case 0:
                if (boolIsWall(cent_x + 3, cent_y - 3) || boolIsWall(cent_x, cent_y - 3) ||
                    boolIsWall(cent_x - 3, cent_y - 3))
                    return up;
                else
                    return notouch;
            case 5:
                if (boolIsWall(cent_x - 3, cent_y - 3) || boolIsWall(cent_x - 3, cent_y) ||
                    boolIsWall(cent_x - 3, cent_y + 3))
                    return left;
                else
                    return notouch;
            case 10:
                if (boolIsWall(cent_x - 3, cent_y + 3) || boolIsWall(cent_x, cent_y + 3) ||
                    boolIsWall(cent_x + 3, cent_y + 3))
                    return down;
                else
                    return notouch;
            case 15:
                if (boolIsWall(cent_x + 3, cent_y - 3) || boolIsWall(cent_x + 3, cent_y) ||
                    boolIsWall(cent_x + 3, cent_y - 3))
                    return right;
                else
                    return notouch;
            default:
                if (direction > 0 && direction < 5) {
                    num1 = boolIsWall(cent_x + 3, cent_y - 3) + boolIsWall(cent_x, cent_y - 3) +
                           boolIsWall(cent_x - 3, cent_y - 3);
                    num2 = boolIsWall(cent_x - 3, cent_y + 3) + boolIsWall(cent_x - 3, cent_y) +
                           boolIsWall(cent_x - 3, cent_y - 3);
                    if (num1 > num2)
                        return up;
                    else if (num1 < num2)
                        return left;
                    else if (num1 == 0 && num2 == 0)
                        return notouch;
                    else // if(num1==num2)
                        return rebound;
                } else if (direction > 5 && direction < 10) {
                    num1 = boolIsWall(cent_x - 3, cent_y + 3) + boolIsWall(cent_x - 3, cent_y) +
                           boolIsWall(cent_x - 3, cent_y - 3);
                    num2 = boolIsWall(cent_x - 3, cent_y + 3) + boolIsWall(cent_x, cent_y + 3) +
                           boolIsWall(cent_x + 3, cent_y + 3);
                    if (num1 > num2)
                        return left;
                    else if (num1 < num2)
                        return down;
                    else if (num1 == 0 && num2 == 0)
                        return notouch;
                    else // if(num1==num2)
                        return rebound;
                } else if (direction > 10 && direction < 15) {
                    num1 = boolIsWall(cent_x - 3, cent_y + 3) + boolIsWall(cent_x, cent_y + 3) +
                           boolIsWall(cent_x + 3, cent_y + 3);
                    num2 = boolIsWall(cent_x + 3, cent_y + 3) + boolIsWall(cent_x + 3, cent_y) +
                           boolIsWall(cent_x + 3, cent_y - 3);
                    if (num1 > num2)
                        return down;
                    else if (num1 < num2)
                        return right;
                    else if (num1 == 0 && num2 == 0)
                        return notouch;
                    else // if(num1==num2)
                        return rebound;
                } else {
                    num1 = boolIsWall(cent_x + 3, cent_y + 3) + boolIsWall(cent_x + 3, cent_y) +
                           boolIsWall(cent_x + 3, cent_y - 3);
                    num2 = boolIsWall(cent_x + 3, cent_y - 3) + boolIsWall(cent_x, cent_y - 3) +
                           boolIsWall(cent_x - 3, cent_y - 3);
                    if (num1 > num2)
                        return right;
                    else if (num1 < num2)
                        return up;
                    else if (num1 == 0 && num2 == 0)
                        return notouch;
                    else // if(num1==num2)
                        return rebound;
                }
        }
    } else {
        if (p1.x <= 0)
            return left;
        else if (p1.y <= 0)
            return up;
        else if (p4.x >= MapXLen)
            return right;
        else return down; // touch wall
    }
}

void BulletBound(Bullet_T *bullet, Bullet_Touch_State state) {
    if( bullet->direction > 19 ){
        printf("in BulletBound: bullet->direction: %d \n", bullet->direction);
    }
    switch (state) {
        case up:
        case down:
            bullet->direction = bullet->direction > 10 ? 30 - bullet->direction : 10 - bullet->direction;
            break;
        case left:
        case right:
            bullet->direction = 20 - bullet->direction;
            break;
        case rebound:
            bullet->direction = (bullet->direction + 10) % 20;
//            bullet->direction = bullet->direction >= 10 ? 19-bullet->direction : 10 + bullet->direction;
            break;
        default:
            perror("notouch error");
            break;
    }
}

uint8_t bulletMove_clear(Bullet_T *bullet, DirectionAdd_T directionAdd) {
#define InRange(pos, pos1, pos4) (((pos).x >= (pos1).x && (pos).x <= (pos4).x) && ((pos).y >= (pos1).y && (pos).y <= (pos4).y))
    static Point_T old1, old2, old3, old4;
    static Point_T new1, new2, new3, new4;
    static Point_T oldPos;
    static Point_T newPos;
    static uint8_t XLen, YLen;
    static uint8_t isOld1InRange, isOld2InRange, isOld3InRange, isOld4InRange;
    oldPos.x = bullet->xPos;
    oldPos.y = bullet->yPos;
    newPos.x = bullet->xPos + directionAdd.x_add;
    newPos.y = bullet->yPos + directionAdd.y_add;
    XLen = Bullet_Image_Length;
    YLen = Bullet_Image_Length;
    //存疑，子弹的图片大小为奇数,减1是什么意思
    old1.x = oldPos.x - (XLen >> 1);
    old1.y = oldPos.y - (YLen >> 1);
    old2.x = oldPos.x + (XLen >> 1);
    old2.y = oldPos.y - (YLen >> 1);
    old3.x = oldPos.x - (XLen >> 1);
    old3.y = oldPos.y + (YLen >> 1);
    old4.x = oldPos.x + (XLen >> 1);
    old4.y = oldPos.y + (YLen >> 1);
    new1.x = newPos.x - (XLen >> 1);
    new1.y = newPos.y - (YLen >> 1);
    new2.x = newPos.x + (XLen >> 1);
    new2.y = newPos.y - (YLen >> 1);
    new3.x = newPos.x - (XLen >> 1);
    new3.y = newPos.y + (YLen >> 1);
    new4.x = newPos.x + (XLen >> 1);
    new4.y = newPos.y + (YLen >> 1);
    //反弹逻辑
    Bullet_Touch_State state = getBulletTouchWallState(bullet->direction, new1, new2, new3, new4);
    if (state != notouch) {
        BulletBound(bullet, state);
        return 0;
    }
    bullet->xPos = newPos.x;
    bullet->yPos = newPos.y;
    if ( bullet->ifDraw == 0 ){
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
                    perror("bulletMove_clear error");
                }
            } else {
                if (isOld2InRange) {
                    LCD_ClearToBackground(old1, (Point_T) {new3.x, old3.y});
                } else if (isOld3InRange) {
                    LCD_ClearToBackground(old1, (Point_T) {old2.x, new2.y});
                } else {
                    perror("bulletMove_clear error");
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
    return 1;
}

void drawBullet(Bullet_T *bullet, uint8_t direction) {
    DirectionAdd_T directionAdd = getDirectionAdd(bullet->subscript, direction);
    bulletMove_clear(bullet, directionAdd);
    if( bullet->ifDraw == 0 ) return;
    LCD_Fill(bullet->xPos - (Bullet_Image_Length >> 1),
             bullet->yPos - (Bullet_Image_Length >> 1),
             Bullet_Image_Length, Bullet_Image_Length,
             gImage_bullet
    );
}

void drawBullets(){
    for (int i = 0; i < BulletNumMax; ++i) {
        if( bullets[i].owner != NULL ) {
            drawBullet(&bullets[i], bullets[i].direction);
        }
    }
}

void Bullet_TimeOutClear(){
    uint32_t loopNowTick = HAL_GetTick();
    for (uint8_t i = 0; i < BulletNumMax; ++i) {
        if( bullets[i].owner != NULL ){
            if(loopNowTick - bullets[i].createTime > Bullet_Life_Time_ms ){
                Bullet_Destroy(&bullets[i]);
            }
        }
    }
}

void Bullets_Init() {
    for( uint8_t i = 0 ; i < BulletNumMax ; i++ ){
        memset(bullets[i].subscript, 0U, sizeof(bullets[i].subscript));
        bullets[i].direction = 20;
        bullets[i].xPos = -1;
        bullets[i].yPos = -1;
        bullets[i].createTime = 0xFFFFFFFF;
        bullets[i].owner = NULL;
        bullets[i].ifDraw = 1;
    }
}

void BulletShoot(Tank_T* tank){
    if(tank->bulletNum > 0){
        for (uint8_t i = 0; i < BulletNumMax; ++i) {
            if(bullets[i].owner == NULL){
                Bullet_Create(&bullets[i], tank, HAL_GetTick());
                bullets[i].ifDraw = 0;
                for (int j = 0; j < Bullet_Create_Loop_Num; ++j) {
                    drawBullet(&bullets[i], bullets[i].direction);
                }
                bullets[i].ifDraw = 1;
                break;
            }
        }
    }
}

void Bullet_Create(Bullet_T *bullet, Tank_T* tank, uint32_t CreateTime){
    bullet->xPos = tank->xPos;
    bullet->yPos = tank->yPos;
    bullet->direction = tank->direction;
    bullet->createTime = CreateTime;
    bullet->owner = tank;
    tank->bulletNum--;
    bulletNum++;
}

void Bullet_Destroy(Bullet_T *bullet) {
    if( bullet->owner != NULL ){
        bullet->owner->bulletNum++;
        bullet->owner = NULL;
    }
    LCD_Fill(bullet->xPos - (Bullet_Image_Length >> 1),
             bullet->yPos - (Bullet_Image_Length >> 1),
             Bullet_Image_Length, Bullet_Image_Length,
             whiteBackground
    );
    bulletNum--;
}

void Bullet_Init_random(Bullet_T *bullet) {
    memset(bullet->subscript, 0U, DIRECTION_FIRST_DIM_LEN);
    uint32_t RNG_Value = 0;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK) {
        RNG_Value = 0;
    }
    bullet->direction = RNG_Value % 20;
    uint8_t HalfLenOfImage = Bullet_Image_Length >> 1;
    do {
        HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value);
        bullet->xPos = RNG_Value % MapXLen;
        HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value);
        bullet->yPos = RNG_Value % MapYLen;
    } while (notouch != getBulletTouchWallState(bullet->direction,
                                                (Point_T) {bullet->xPos - HalfLenOfImage,
                                                           bullet->yPos - HalfLenOfImage},
                                                (Point_T) {bullet->xPos + HalfLenOfImage,
                                                           bullet->yPos - HalfLenOfImage},
                                                (Point_T) {bullet->xPos - HalfLenOfImage,
                                                           bullet->yPos + HalfLenOfImage},
                                                (Point_T) {bullet->xPos + HalfLenOfImage,
                                                           bullet->yPos + HalfLenOfImage}));
    bullet->createTime = 0xFFFFFFFF;
}

uint8_t IsCrash(Tank_T *tank, Bullet_T *bullet)
{
#define abs(x) ((x)>0?(x):-(x))
    uint16_t tank_center_x=tank->xPos, tank_center_y=tank->yPos;
    uint16_t bullet_center_x=bullet->xPos, bullet_center_y=bullet->yPos;
    int16_t distance_x = (int16_t)bullet_center_x - (int16_t)tank_center_x;
    int16_t distance_y = (int16_t)bullet_center_y - (int16_t)tank_center_y;
    int16_t distance = abs(distance_x) - abs(distance_y);
    if( abs(distance) > 45 )
    {
        return 0;
    }
    else {
        const CrashTest_T *crash = tank->tankImage[tank->direction].crashTest;
        for (uint8_t i = 0; i < crash->number; i++) {
            if ((tank_center_x + crash->addpoint[i].x > bullet_center_x - half_bullet_image &&
                 tank_center_x + crash->addpoint[i].x < bullet_center_x + half_bullet_image) &&
                (tank_center_y + crash->addpoint[i].y > bullet_center_y - half_bullet_image &&
                 tank_center_y + crash->addpoint[i].y < bullet_center_y + half_bullet_image))
                return 1;
        }
    }
    return 0;
}

uint8_t IsTankCrashTank(Tank_T *tank,Tank_T randomtank[],uint8_t number)
{
    uint16_t tank_1_center_x = tank->xPos, tank_1_center_y = tank->yPos;
    uint16_t tank_2_center_x = 0, tank_2_center_y = 0;
    int16_t distance_x=0, distance_y=0;
    int16_t distance;
    for(uint8_t i = 0; i < 5 && i!=number; i++)
    {
        if( randomtank[i].isAlive == 1 )
        {
            tank_2_center_x = randomtank[i].xPos;
            tank_2_center_y = randomtank[i].yPos;
            distance_x = (int16_t)tank_2_center_x - (int16_t)tank_1_center_x;
            distance_y = (int16_t)tank_2_center_y - (int16_t)tank_1_center_y;
            distance = abs (distance_x) - abs(distance_y);
            if(abs(distance) > 60)
                continue;
            else{
                const CrashTest_T *crash = tank->tankImage[tank->direction].crashTest;
                for(uint8_t j = 0; j < crash->number ; j++) {
                    if ((tank_1_center_x + crash->addpoint[j].x >
                         tank_2_center_x - (randomtank[i].tankImage->xLen >> 1)) &&
                        (tank_1_center_x + crash->addpoint[j].x <
                         tank_2_center_x + (randomtank[i].tankImage->xLen >> 1)) &&
                        (tank_1_center_y + crash->addpoint[j].y >
                         tank_2_center_y - (randomtank[i].tankImage->yLen >> 1)) &&
                        (tank_1_center_y + crash->addpoint[j].y <
                         tank_2_center_y + (randomtank[i].tankImage->yLen >> 1))) {
                        return 1;
                    }
                }
            }
        }else
            continue;
    }
    return 0;
}