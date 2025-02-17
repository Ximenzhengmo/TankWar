#ifndef TANKWAR_CRASH_H
#define TANKWAR_CRASH_H

#include "global.h"

typedef struct{
    const Point_T *addpoint;
    int number;
}CrashTest_T;

typedef struct Image_T{
    const unsigned char* image;
    uint8_t xLen;
    uint8_t yLen;
    const CrashTest_T *crashTest;
}Image_T;

extern const CrashTest_T crashTest_bullet[20];
extern const CrashTest_T crashTest_target;
extern const CrashTest_T crashTest_laserIcon;

extern const Point_T AddPoint_0[];
extern const Point_T AddPoint_18[];
extern const Point_T AddPoint_36[];
extern const Point_T AddPoint_54[];
extern const Point_T AddPoint_72[];
extern const Point_T AddPoint_90[];
extern const Point_T AddPoint_108[];
extern const Point_T AddPoint_126[];
extern const Point_T AddPoint_144[];
extern const Point_T AddPoint_162[];
extern const Point_T AddPoint_180[];
extern const Point_T AddPoint_198[];
extern const Point_T AddPoint_216[];
extern const Point_T AddPoint_234[];
extern const Point_T AddPoint_252[];
extern const Point_T AddPoint_270[];
extern const Point_T AddPoint_288[];
extern const Point_T AddPoint_306[];
extern const Point_T AddPoint_324[];
extern const Point_T AddPoint_342[];

extern const Point_T AddPoint_target[];


#endif //TANKWAR_CRASH_H
