#include "target.h"

const TargetImage_T tankTargetImage = {
        .xLen = Target_Image_Len,
        .yLen = Target_Image_Len,
        .image = gImage_target,
        .crashTest = &crashTest_target,
};

Target_T randomTarget[TargetNumMax] = {
        {.targetImage = &tankTargetImage},
        {.targetImage = &tankTargetImage},
        {.targetImage = &tankTargetImage},
        {.targetImage = &tankTargetImage},
        {.targetImage = &tankTargetImage},
};

void targetInit(Target_T *target) {
    uint8_t crash_flag = 0;
    target->isAlive = 1;
    static uint32_t RNG_Value;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK) {
        RNG_Value = 0;
    }
    uint8_t xHalfLenOfImage = (target->targetImage->xLen) >> 1;
    uint8_t yHalfLenOfImage = (target->targetImage->yLen) >> 1;
    do {
        while (HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK);
        target->xPos = RNG_Value % MapXLen;
        while (HAL_RNG_GenerateRandomNumber(&hrng, &RNG_Value) != HAL_OK);
        target->yPos = RNG_Value % MapYLen;
        crash_flag = IsTargetCrashTargets(target);
    } while (isTouchWall((Point_T) {target->xPos - xHalfLenOfImage,
                                    target->yPos - yHalfLenOfImage},
                         (Point_T) {target->xPos + xHalfLenOfImage,
                                    target->yPos - yHalfLenOfImage},
                         (Point_T) {target->xPos - xHalfLenOfImage,
                                    target->yPos + yHalfLenOfImage},
                         (Point_T) {target->xPos + xHalfLenOfImage,
                                    target->yPos + yHalfLenOfImage}) || crash_flag);
}

uint8_t IsTargetCrashTargets(Target_T *target) {
    uint16_t target_1_center_x = target->xPos, target_1_center_y = target->yPos;
    uint16_t target_2_center_x = 0, target_2_center_y = 0;
    int16_t distance_x = 0, distance_y = 0;
    int16_t distance;
    for (uint8_t i = 0; i < TargetNumMax; i++) {
        if (&randomTarget[i] == target) continue;
        if (randomTarget[i].isAlive == 1) {
            target_2_center_x = randomTarget[i].xPos;
            target_2_center_y = randomTarget[i].yPos;
            distance_x = (int16_t) target_2_center_x - (int16_t) target_1_center_x;
            distance_y = (int16_t) target_2_center_y - (int16_t) target_1_center_y;
            distance = ABS (distance_x) - ABS(distance_y);
            if (ABS(distance) > 60)
                continue;
            else {
                const CrashTest_T *crash = target->targetImage->crashTest;
                const uint8_t xHalfLenOfImage = (randomTarget[i].targetImage->xLen >> 1);
                const uint8_t yHalfLenOfImage = (randomTarget[i].targetImage->yLen >> 1);
                for (uint8_t j = 0; j < crash->number; j++) {
                    if ((target_1_center_x + crash->addpoint[j].x >
                         target_2_center_x - xHalfLenOfImage) &&
                        (target_1_center_x + crash->addpoint[j].x <
                         target_2_center_x + xHalfLenOfImage) &&
                        (target_1_center_y + crash->addpoint[j].y >
                         target_2_center_y - yHalfLenOfImage) &&
                        (target_1_center_y + crash->addpoint[j].y <
                         target_2_center_y + yHalfLenOfImage)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void drawTarget(Target_T *target) {
    LCD_Fill(target->xPos - (target->targetImage->xLen >> 1),
             target->yPos - (target->targetImage->yLen >> 1),
             target->targetImage->xLen,
             target->targetImage->yLen,
             gImage_target
    );
}

void target_Destroy(Target_T *target) {
    target->isAlive = 0;
    LCD_Fill(target->xPos - (target->targetImage->xLen >> 1),
             target->yPos - (target->targetImage->yLen >> 1),
             target->targetImage->xLen,
             target->targetImage->yLen,
             whiteBackground
    );
}

uint8_t IsBulletCrashTarget(Target_T *target, Bullet_T *bullet) {
    uint16_t tank_center_x = target->xPos, tank_center_y = target->yPos;
    uint16_t bullet_center_x = bullet->xPos, bullet_center_y = bullet->yPos;
    int16_t distance_x = (int16_t) bullet_center_x - (int16_t) tank_center_x;
    int16_t distance_y = (int16_t) bullet_center_y - (int16_t) tank_center_y;
    int16_t distance = ABS(distance_x) - ABS(distance_y);
    if (ABS(distance) > 30) {
        return 0;
    } else {
        const CrashTest_T *crash = target->targetImage->crashTest;
        for (uint8_t i = 0; i < crash->number; i++) {
            if ((tank_center_x + crash->addpoint[i].x > bullet_center_x - half_bullet_image &&
                 tank_center_x + crash->addpoint[i].x < bullet_center_x + half_bullet_image) &&
                (tank_center_y + crash->addpoint[i].y > bullet_center_y - half_bullet_image &&
                 tank_center_y + crash->addpoint[i].y < bullet_center_y + half_bullet_image))
                return 1;
        }
    }
    return 0;
}