#ifndef TANKWAR_BULLET_H
#define TANKWAR_BULLET_H

#include "main.h"
#include "tank.h"

extern const unsigned char gImage_bullet[98];
#define Bullet_Image_Length 7

typedef enum Bullet_Touch_State{
    up,down,left,right,notouch,rebound
}Bullet_Touch_State;

typedef struct Bullet_T {
    uint8_t direction;
    int16_t xPos;
    int16_t yPos;
}Bullet_T;

extern const uint8_t bullet_detection[20][2];

DirectionAdd_T getDirectionAdd_Bullet(uint8_t newDirection) ;

Bullet_Touch_State isBulletTouchWall(Bullet_T *bullet,Point_T p1, Point_T p2, Point_T p3, Point_T p4);

void BulletBound(Bullet_T *bullet,Bullet_Touch_State state);

uint8_t bulletMove_clear(Bullet_T *bullet, DirectionAdd_T directionAdd, uint8_t newDirection) ;

void drawBullet(Bullet_T *bullet, uint8_t direction);

extern Bullet_T bullet;

void Bullet_Init(Bullet_T *bullet,int16_t x,int16_t y,uint8_t direction);

#endif //TANKWAR_BULLET_H
