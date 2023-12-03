//
// Created by zsm on 2023/11/15.
//

#ifndef TANKWAR_TACK_H
#define TANKWAR_TACK_H

#include "lcd_driver.h"
#include "stdbool.h"
#include "map.h"

typedef struct{
    int16_t x;
    int16_t y;
}Point_T;

typedef struct TankImage_T{
    const unsigned char* image;
    uint8_t xLen;
    uint8_t yLen;
}TankImage_T;

typedef struct DirectionAdd_T {
    int8_t x_add;
    int8_t y_add;
}DirectionAdd_T;

typedef struct Tank_T{
    uint8_t bulletNum;
    const TankImage_T* const tankImage;
    uint8_t direction;
    int16_t xPos;
    int16_t yPos;
}Tank_T;

extern Tank_T redTank;
extern Tank_T greenTank;

extern const TankImage_T redTankImage[20];
extern const TankImage_T greenTankImage[20];

void tank_Init(Tank_T* tank);

void LCD_ClearToBackground(Point_T LeftUp, Point_T RightDown);

bool isTankTouchWall(Point_T p1, Point_T p2, Point_T p3, Point_T p4);

DirectionAdd_T getDirectionAdd(uint8_t newDirection);

uint8_t tankMove_clear(Tank_T* tank, DirectionAdd_T directionAdd, uint8_t newDirection);

void drawTank(Tank_T* tank ,uint8_t direction);

extern const unsigned char gImage_red0[];
extern const unsigned char gImage_red18[];
extern const unsigned char gImage_red36[];
extern const unsigned char gImage_red54[];
extern const unsigned char gImage_red72[];
extern const unsigned char gImage_red90[];
extern const unsigned char gImage_red108[];
extern const unsigned char gImage_red126[];
extern const unsigned char gImage_red144[];
extern const unsigned char gImage_red162[];
extern const unsigned char gImage_red180[];
extern const unsigned char gImage_red198[];
extern const unsigned char gImage_red216[];
extern const unsigned char gImage_red234[];
extern const unsigned char gImage_red252[];
extern const unsigned char gImage_red270[];
extern const unsigned char gImage_red288[];
extern const unsigned char gImage_red306[];
extern const unsigned char gImage_red324[];
extern const unsigned char gImage_red342[];

extern const unsigned char gImage_green0[];
extern const unsigned char gImage_green18[];
extern const unsigned char gImage_green36[];
extern const unsigned char gImage_green54[];
extern const unsigned char gImage_green72[];
extern const unsigned char gImage_green90[];
extern const unsigned char gImage_green108[];
extern const unsigned char gImage_green126[];
extern const unsigned char gImage_green144[];
extern const unsigned char gImage_green162[];
extern const unsigned char gImage_green180[];
extern const unsigned char gImage_green198[];
extern const unsigned char gImage_green216[];
extern const unsigned char gImage_green234[];
extern const unsigned char gImage_green252[];
extern const unsigned char gImage_green270[];
extern const unsigned char gImage_green288[];
extern const unsigned char gImage_green306[];
extern const unsigned char gImage_green324[];
extern const unsigned char gImage_green342[];

extern const uint8_t whiteBackground[3040];

#endif //TANKWAR_TACK_H
