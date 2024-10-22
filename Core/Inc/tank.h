//
// Created by zsm on 2023/11/15.
//

#ifndef TANKWAR_TACK_H
#define TANKWAR_TACK_H

#include "lcd_driver.h"
#include "map.h"
#include "crash.h"
#include "sound.h"

typedef Image_T TankImage_T;

typedef struct Tank_T{
    uint8_t isAlive; // 0: died, 1: alive
    uint8_t bulletNum;
    uint8_t subscript[DIRECTION_FIRST_DIM_LEN]; // pace
    const TankImage_T* const tankImage;
    uint8_t direction;
    int16_t xPos; // x_center of tankImage
    int16_t yPos; // y_center of tankImage
}Tank_T;

#define tankDiedTimeDelay_ms (3*1000)

extern Tank_T redTank;
extern Tank_T greenTank;

extern const TankImage_T redTankImage[20];
extern const TankImage_T greenTankImage[20];

void tank_Init(Tank_T* tank);

uint8_t tankMove_clear(Tank_T* tank, DirectionAdd_T directionAdd, uint8_t newDirection);

void drawTank(Tank_T* tank ,uint8_t direction);

void tank_Destroy(Tank_T* tank);

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

#endif //TANKWAR_TACK_H
