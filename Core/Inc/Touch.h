#ifndef TANKWAR_TOUCH_H
#define TANKWAR_TOUCH_H

#include "main.h"
#include "lcd_driver.h"
#include "stdio.h"

typedef struct touch {
    uint8_t isPressed;
    uint16_t X;
    uint16_t Y;
} TouchTypedef;

typedef enum {
    TOUCH_SUCCESS = 0x00U,
    TOUCH_ERROR = 0x01U,
    TOUCH_BUSY = 0x02U,
    TOUCH_TIMEOUT = 0x03U
} Touch_StatusTypeDef;

Touch_StatusTypeDef Touch_Read(TouchTypedef *dst);

uint8_t Touch(void);

#endif //TANKWAR_TOUCH_H
