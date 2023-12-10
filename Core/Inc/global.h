//
// Created by zsm on 2023/11/15.
//

#ifndef TANKWAR_GLOBAL_H
#define TANKWAR_GLOBAL_H

#include "main.h"

typedef struct{
    int16_t x;
    int16_t y;
}Point_T;

typedef struct DirectionAdd_T {
    int8_t x_add;
    int8_t y_add;
}DirectionAdd_T;

#define DIRECTION_FIRST_DIM_LEN (5)

extern const uint8_t whiteBackground[3040];

DirectionAdd_T getDirectionAdd(uint8_t *subscript ,uint8_t newDirection);
#endif //TANKWAR_GLOBAL_H
