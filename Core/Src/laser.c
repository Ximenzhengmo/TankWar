#include "laser.h"

const unsigned char gImage_laser[8] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

LaserIconImage_T laserIconImage = {
        .xLen = LaserIconImageLen,
        .yLen = LaserIconImageLen,
        .image = gImage_LaserIcon,
        .crashTest = &crashTest_laserIcon,
};

Laser_T laserBuff = {
        .laserIconImage = &laserIconImage
};

void Laser_Init(Laser_T *laser) {
    memset(laser->points, 0, sizeof(laser->points));
    memset(laser->subscript, 0, sizeof(laser->subscript));
    laser->direction = 0;
    laser->color = WHITE;
    laser->owner = NULL;
    laser->yPos = 0;
    laser->yPos = 0;
    laser->state = LaserNotCreated;
}

void Laser_Create(Laser_T* laser){
    static uint32_t RNG_Value;
    if (laser->state != LaserNotCreated) return;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK) return;
    if ( (RNG_Value & 0xFFF) > 5 ) return;
    uint8_t xHalfLenOfImage = (laser->laserIconImage->xLen) >> 1;
    uint8_t yHalfLenOfImage = (laser->laserIconImage->yLen) >> 1;
    if ( HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK ) return;
    laser->xPos = RNG_Value % MapXLen;
    if (  HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK ) return;
    laser->yPos = RNG_Value % MapYLen;
    if ( isTouchWall((Point_T) {laser->xPos - xHalfLenOfImage,
                                laser->yPos - yHalfLenOfImage},
                     (Point_T) {laser->xPos + xHalfLenOfImage,
                                laser->yPos - yHalfLenOfImage},
                     (Point_T) {laser->xPos - xHalfLenOfImage,
                                laser->yPos + yHalfLenOfImage},
                     (Point_T) {laser->xPos + xHalfLenOfImage,
                                laser->yPos + yHalfLenOfImage}) ){
        return;
    }
    laser->state = LaserNotGet;
}

void drawLaserIcon(Laser_T *laser) {
    if (laser->state != LaserNotGet) return;
    LCD_Fill(laser->xPos - (laser->laserIconImage->xLen >> 1),
             laser->yPos - (laser->laserIconImage->yLen >> 1),
             laser->laserIconImage->xLen,
             laser->laserIconImage->yLen,
             laserIconImage.image
    );
}

void Laser_tankGet(Laser_T *laser, Tank_T *tank) {
    if (laser->state != LaserNotGet) return;
    static uint16_t testX, testY;
    const CrashTest_T *crashTest = laser->laserIconImage->crashTest;
    for (uint8_t i = 0; i < crashTest->number; ++i) {
        testX = laser->xPos + crashTest->addpoint[i].x;
        testY = laser->yPos + crashTest->addpoint[i].y;
        if (testX >= tank->xPos - (tank->tankImage[tank->direction].xLen >> 1)
            && testX < tank->xPos + (tank->tankImage[tank->direction].xLen >> 1)
            && testY >= tank->yPos - (tank->tankImage[tank->direction].yLen >> 1)
            && testY < tank->yPos + (tank->tankImage[tank->direction].yLen >> 1)) {

            laser->state = LaserShow;
            laser->owner = tank;
            if (tank == &redTank) {
                laser->color = RED;
            } else {
                laser->color = GREEN;
            }
            LCD_ClearToBackground(
                    (Point_T) {laser->xPos - (LaserIconImageLen >> 1), laser->yPos - (LaserIconImageLen >> 1)},
                    (Point_T) {laser->xPos + (LaserIconImageLen >> 1), laser->yPos + (LaserIconImageLen >> 1)});
            return;
        }
    }
}

TouchState_T Laser_GetTouchState(Laser_T *laser, uint16_t xPos, uint16_t yPos) {
    static Point_T testPoint;
    static uint8_t testBool, rowBool, colBool;
    switch (laser->direction / DIRECTION_FIRST_DIM_LEN) {
        case 0:
            if (laser->direction == 0) return isWall(xPos, yPos) || isWall(xPos + 1, yPos) ? rebound : notouch;
            testPoint = (Point_T) {xPos, yPos};
            testBool = isWall(xPos, yPos);
            rowBool = isWall(testPoint.x + LaserPointImageLength, testPoint.y);
            colBool = isWall(testPoint.x, testPoint.y + LaserPointImageLength);
            if (testBool) {
                if (colBool && rowBool) return rebound;
                else if (colBool && !rowBool) return left;
                else if (!colBool && rowBool) return up;
                else return rebound;
            } else {
                return notouch;
            }
        case 1:
            if (laser->direction == 5) return isWall(xPos, yPos) || isWall(xPos, yPos + 1) ? rebound : notouch;
            testPoint = (Point_T) {xPos, yPos + 1};
            testBool = isWall(xPos, yPos + 1);
            rowBool = isWall(testPoint.x + LaserPointImageLength, testPoint.y);
            colBool = isWall(testPoint.x, testPoint.y - LaserPointImageLength);
            if (testBool) {
                if (colBool && rowBool) return rebound;
                else if (colBool && !rowBool) return left;
                else if (!colBool && rowBool) return down;
                else return rebound;
            } else {
                return notouch;
            }
        case 2:
            if (laser->direction == 10) return isWall(xPos + 1, yPos + 1) || isWall(xPos, yPos + 1) ? rebound : notouch;
            testPoint = (Point_T) {xPos + 1, yPos + 1};
            testBool = isWall(xPos + 1, yPos + 1);
            rowBool = isWall(testPoint.x - LaserPointImageLength, testPoint.y);
            colBool = isWall(testPoint.x, testPoint.y - LaserPointImageLength);
            if (testBool) {
                if (colBool && rowBool) return rebound;
                else if (colBool && !rowBool) return right;
                else if (!colBool && rowBool) return down;
                else return rebound;
            } else {
                return notouch;
            }
        case 3:
            if (laser->direction == 15) return isWall(xPos + 1, yPos + 1) || isWall(xPos + 1, yPos) ? rebound : notouch;
            testPoint = (Point_T) {xPos + 1, yPos};
            testBool = isWall(xPos + 1, yPos);
            rowBool = isWall(testPoint.x - LaserPointImageLength, testPoint.y);
            colBool = isWall(testPoint.x, testPoint.y + LaserPointImageLength);
            if (testBool) {
                if (colBool && rowBool) return rebound;
                else if (colBool && !rowBool) return right;
                else if (!colBool && rowBool) return up;
                else return rebound;
            } else {
                return notouch;
            }
        default:
            perror("error in Laser_GetTouchState");
            return rebound;
    }
}

void Laser_Bound(Laser_T *laser, TouchState_T state) {
    switch (state) {
        case up:
        case down:
            laser->direction = laser->direction > 10 ? 30 - laser->direction : 10 - laser->direction;
            break;
        case left:
        case right:
            laser->direction = 20 - laser->direction;
            break;
        case rebound:
            laser->direction = (laser->direction + 10) % 20;
            break;
        default:
            perror("notouch error");
            break;
    }
}

void Laser_Renew(Laser_T *laser) {
    if (laser->state != LaserShow) return;
    memset(laser->subscript, 0, sizeof(laser->subscript));
    Laser_Clear(laser);

    laser->points[0].x = laser->owner->xPos;
    laser->points[0].y = laser->owner->yPos;
    laser->direction = laser->owner->direction;
    static DirectionAdd_T directionAdd;
    static TouchState_T touchState;
    for (uint8_t i = 1; i < LaserPointNum; ++i) {
        directionAdd = getDirectionAdd(laser->subscript, laser->direction);
        touchState = Laser_GetTouchState(laser,
                                         laser->points[i - 1].x + directionAdd.x_add,
                                         laser->points[i - 1].y + directionAdd.y_add);
        while (touchState != notouch) {
            Laser_Bound(laser, touchState);
            directionAdd = getDirectionAdd(laser->subscript, laser->direction);
            touchState = Laser_GetTouchState(laser,
                                             laser->points[i - 1].x + directionAdd.x_add,
                                             laser->points[i - 1].y + directionAdd.y_add);
        }
        laser->points[i].x = laser->points[i - 1].x + directionAdd.x_add;
        laser->points[i].y = laser->points[i - 1].y + directionAdd.y_add;
    }
}

void Laser_Show(Laser_T *laser) {
    if (laser->state != LaserShow) return;
    uint16_t color = laser->color;
    for (uint8_t i = LaserCreatSkipNum; i < LaserPointNum; ++i) {
        if ((i & 0x3) > 1) {
            continue;
        }
        LCD_SetWindows(laser->points[i].x,
                       laser->points[i].y,
                       laser->points[i].x + LaserPointImageLength - 1,
                       laser->points[i].y + LaserPointImageLength - 1);
        Lcd_WriteData_16Bit(color);
        Lcd_WriteData_16Bit(color);
        Lcd_WriteData_16Bit(color);
        Lcd_WriteData_16Bit(color);
    }
}

void Laser_Clear(Laser_T *laser) {
    for (uint8_t i = LaserCreatSkipNum; i < LaserPointNum; ++i) {
        if ((i & 0x3) > 1) {
            continue;
        }
        LCD_SetWindows(laser->points[i].x,
                       laser->points[i].y,
                       laser->points[i].x + LaserPointImageLength - 1,
                       laser->points[i].y + LaserPointImageLength - 1);
        Lcd_WriteData_16Bit(WHITE);
        Lcd_WriteData_16Bit(WHITE);
        Lcd_WriteData_16Bit(WHITE);
        Lcd_WriteData_16Bit(WHITE);
    }
}

Tank_T *Laser_Shoot(Laser_T *laser) {
    if (laser->state != LaserShoot) return NULL;
    static uint8_t loopNum = 0;
    uint16_t color = laser->owner == &redTank ? RED : GREEN;
    if (loopNum == LaserShootLoopNum) {
        loopNum = 0;
        Laser_Destroy(laser);
        return NULL;
    }
    for (uint8_t i = LaserCreatSkipNum + loopNum * LaserShootPace; i < LaserCreatSkipNum + (loopNum + 1) * LaserShootPace; ++i) {
        LCD_SetWindows(laser->points[i].x,
                       laser->points[i].y,
                       laser->points[i].x + LaserPointImageLength - 1,
                       laser->points[i].y + LaserPointImageLength - 1);
        Lcd_WriteData_16Bit(color);
        Lcd_WriteData_16Bit(color);
        Lcd_WriteData_16Bit(color);
        Lcd_WriteData_16Bit(color);
        if (laser->points[i].x >= greenTank.xPos - (greenTank.tankImage[greenTank.direction].xLen >> 1)
            && laser->points[i].x < greenTank.xPos + (greenTank.tankImage[greenTank.direction].xLen >> 1)
            && laser->points[i].y >= greenTank.yPos - (greenTank.tankImage[greenTank.direction].yLen >> 1)
            && laser->points[i].y < greenTank.yPos + (greenTank.tankImage[greenTank.direction].yLen >> 1)) {
            loopNum = 0;
            return &greenTank;
        }
        if (laser->points[i].x >= redTank.xPos - (redTank.tankImage[redTank.direction].xLen >> 1)
            && laser->points[i].x < redTank.xPos + (redTank.tankImage[redTank.direction].xLen >> 1)
            && laser->points[i].y >= redTank.yPos - (redTank.tankImage[redTank.direction].yLen >> 1)
            && laser->points[i].y < redTank.yPos + (redTank.tankImage[redTank.direction].yLen >> 1)) {
            loopNum = 0;
            return &redTank;
        }
    }
    loopNum++;
    return NULL;
}

void Laser_Destroy(Laser_T *laser) {
    for (uint8_t i = LaserCreatSkipNum; i < LaserPointNum; ++i) {
        LCD_SetWindows(laser->points[i].x,
                       laser->points[i].y,
                       laser->points[i].x + LaserPointImageLength - 1,
                       laser->points[i].y + LaserPointImageLength - 1);
        Lcd_WriteData_16Bit(WHITE);
        Lcd_WriteData_16Bit(WHITE);
        Lcd_WriteData_16Bit(WHITE);
        Lcd_WriteData_16Bit(WHITE);
    }
    Laser_Init(laser);
}