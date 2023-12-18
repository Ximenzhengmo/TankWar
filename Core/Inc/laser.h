#ifndef TANKWAR_LASER_H
#define TANKWAR_LASER_H

#include "bullet.h"

#define LaserPointNum 150
#define LaserPointImageLength 2
#define LaserCreatSkipNum 20
#define LaserShootLoopNum 13
#define LaserShootPace 10

extern const unsigned char gImage_laser[8];

typedef enum{
    LaserNotCreated,
    LaserNotGet,
    LaserShow,
    LaserShoot,
}LaserState_T;

typedef Image_T LaserIconImage_T;

typedef struct Laser_T {
    Point_T points[LaserPointNum];
    uint8_t direction;
    uint8_t subscript[DIRECTION_FIRST_DIM_LEN];
    LaserState_T state;
    uint16_t color;
    uint16_t xPos;
    uint16_t yPos;
    const LaserIconImage_T* const laserIconImage;
    Tank_T* owner; // to do
}Laser_T;

extern LaserIconImage_T laserIconImage;
extern Laser_T laserBuff;
extern unsigned char gImage_LaserIcon[];

void Laser_Init(Laser_T* laser);

void Laser_Create(Laser_T* laser);

void drawLaserIcon(Laser_T* laser);

void Laser_tankGet(Laser_T* laser, Tank_T* tank);

void Laser_Renew(Laser_T* laser);

void Laser_Show(Laser_T* laser);

TouchState_T Laser_GetTouchState(Laser_T *laser, uint16_t xPos, uint16_t yPos);

void Laser_Bound(Laser_T* laser, TouchState_T state);

void Laser_Clear(Laser_T* laser);

Tank_T* Laser_Shoot(Laser_T* laser);

void Laser_Destroy(Laser_T* laser);
#endif //TANKWAR_LASER_H
