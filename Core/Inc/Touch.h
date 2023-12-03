//
// Created by 86180 on 2023/12/4.
//

#ifndef TANKWAR_TOUCH_H
#define TANKWAR_TOUCH_H

//
// Created by 86180 on 2023/12/4.
//
#include "main.h"
#include "lcd_driver.h"

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

uint16_t SPI_SwapBitMode(SPI_TypeDef *SPI,DMA_HandleTypeDef *DMA,uint16_t SPIDataSize);

Touch_StatusTypeDef Touch_Read(TouchTypedef *dst);

void Touch(void);

#endif //TANKWAR_TOUCH_H
