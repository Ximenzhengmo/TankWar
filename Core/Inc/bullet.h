#ifndef TANKWAR_BULLET_H
#define TANKWAR_BULLET_H

#include "tank.h"

#define Bullet_Image_Length 7
#define BulletNumMax 10
#define Bullet_Life_Time_ms (10*1000)
#define BulletCreateSkipNum 12
#define half_bullet_image (Bullet_Image_Length >> 1)
#define LaserIconImageLen (17)

typedef struct Bullet_T {
    Tank_T* owner;
    uint8_t ifDraw;
    uint8_t subscript[DIRECTION_FIRST_DIM_LEN];
    uint8_t direction;
    int16_t xPos;
    int16_t yPos;
    uint32_t createTime;
}Bullet_T;

extern const unsigned char gImage_bullet[98];

extern Bullet_T bullets[BulletNumMax];
extern uint8_t bulletNum;

TouchState_T getBulletTouchWallState(uint8_t direction, Point_T p1, Point_T p2, Point_T p3, Point_T p4);

void BulletBound(Bullet_T *bullet, TouchState_T state);

void bulletMove_clear(Bullet_T *bullet, DirectionAdd_T directionAdd) ;

void drawBullet(Bullet_T *bullet, uint8_t direction);

void drawBullets();

void Bullet_TimeOutClear();

void Bullets_Init();

void BulletShoot(Tank_T* tank);

void Bullet_Create(Bullet_T *bullet, Tank_T* tank, uint32_t CreateTime);

void Bullet_Destroy(Bullet_T *bullet);

void Bullet_Init_random(Bullet_T* bullet);

uint8_t IsBulletCrashTank(Tank_T *tank, Bullet_T *bullet);


#endif //TANKWAR_BULLET_H
