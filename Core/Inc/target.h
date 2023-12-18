#ifndef TANKWAR_TARGET_H
#define TANKWAR_TARGET_H

#include "bullet.h"

typedef Image_T TargetImage_T;

typedef struct Target_T {
    uint8_t isAlive;
    const TargetImage_T* const targetImage;
    int16_t xPos;
    int16_t yPos;
}Target_T;

#define TargetNumMax (5)
#define Target_Image_Len (17)

extern const TargetImage_T tankTargetImage;
extern Target_T randomTarget[TargetNumMax];
extern const unsigned char gImage_target[];

void targetInit(Target_T *target);
uint8_t IsTargetCrashTargets(Target_T *target);
void drawTarget(Target_T *target);
void target_Destroy(Target_T *target);
uint8_t IsBulletCrashTarget(Target_T *target, Bullet_T *bullet);

#endif //TANKWAR_TARGET_H
