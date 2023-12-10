#include "global.h"


DirectionAdd_T getDirectionAdd(uint8_t *subscript ,uint8_t newDirection) {
    // 26 * 38   0 ->         y+=-1 ,       y+=-2
    // 32 * 40  18 ->         y+=-2 , x+=-1 y+=-1
    // 38 * 40  36 ->   x+=-1 y+=-1 , x+=-1 y+=-2 , x+=-1 y+=-1
    // 40 * 38  54 ->   x+=-1 y+=-1 , x+=-2 y+=-1 , x+=-1 y+=-1
    // 40 * 32  72 ->   x+=-1       , x+=-2 y+=-1
    static const DirectionAdd_T directionAdd[DIRECTION_FIRST_DIM_LEN][3] = {
            {{0,  -1}, {0,  -2}, {0,  0}},
            {{0,  -2}, {-1, -1}, {0,  0}},
            {{-1, -1}, {-1, -2}, {-1, -1}},
            {{-1, -1}, {-2, -1}, {-1, -1}},
            {{-1, 0},  {-2, -1}, {0,  0}},
    };
    static uint8_t sub;
    uint8_t degreeMap = newDirection % DIRECTION_FIRST_DIM_LEN;
    if (degreeMap == 2 || degreeMap == 3) {
        sub = (subscript[degreeMap] = (subscript[degreeMap] + 1) % 3);
    } else {
        sub = (subscript[degreeMap] = (subscript[degreeMap] + 1) % 2);
    }
    switch (newDirection / DIRECTION_FIRST_DIM_LEN) {
        case 0: // [0 , 90)
            return (DirectionAdd_T) {
                    .x_add =   directionAdd[degreeMap][sub].x_add,
                    .y_add =   directionAdd[degreeMap][sub].y_add,
            };
        case 1: // [90, 180)
            return (DirectionAdd_T) {
                    .x_add =   directionAdd[degreeMap][sub].y_add,
                    .y_add = -directionAdd[degreeMap][sub].x_add,
            };
        case 2: // [180, 270)
            return (DirectionAdd_T) {
                    .x_add = -directionAdd[degreeMap][sub].x_add,
                    .y_add = -directionAdd[degreeMap][sub].y_add,
            };
        case 3: // [270, 360)
            return (DirectionAdd_T) {
                    .x_add = -directionAdd[degreeMap][sub].y_add,
                    .y_add =  directionAdd[degreeMap][sub].x_add,
            };
        default:
            return (DirectionAdd_T) {0, 0};
    }
}