#ifndef TANKWAR_BULLET_H
#define TANKWAR_BULLET_H

#include "main.h"
#include "tank.h"

#define DIRECTION_FIRST_DIM_LEN (5)
#define Bullet_Image_Length 7
#define BulletNumMax 6
#define Bullet_Life_Time_ms 10000

typedef enum Bullet_Touch_State{
    up,down,left,right,notouch,rebound
}Bullet_Touch_State;

typedef struct Bullet_T {
    uint8_t subscript[5];
    uint8_t direction;
    int16_t xPos;
    int16_t yPos;
    uint32_t createTime;
}Bullet_T;

extern const unsigned char gImage_bullet[98];

extern Bullet_T bullets[BulletNumMax];
extern Bullet_T bullet_test;
extern uint8_t bulletNum;

DirectionAdd_T getDirectionAdd_Bullet(uint8_t *subscript , uint8_t newDirection) ;

Bullet_Touch_State getBulletTouchWallState(uint8_t direction, Point_T p1, Point_T p2, Point_T p3, Point_T p4);

void BulletBound(Bullet_T *bullet,Bullet_Touch_State state);

uint8_t bulletMove_clear(Bullet_T *bullet, DirectionAdd_T directionAdd) ;

void drawBullet(Bullet_T *bullet, uint8_t direction);

void Bullet_Init(Bullet_T *bullet, Point_T pos, uint8_t direction, uint32_t CreateTime);

void Bullet_Init_random(Bullet_T* bullet);
#endif //TANKWAR_BULLET_H
