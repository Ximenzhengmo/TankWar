#ifndef TANKWAR_BULLET_H
#define TANKWAR_BULLET_H

#include "main.h"
#include "tank.h"

extern const unsigned char gImage_bullet[98];

typedef struct Bullet_T {
    uint8_t direction;
    int16_t xPos;
    int16_t yPos;
}Bullet_T;


#endif //TANKWAR_BULLET_H
