#ifndef CUBE_LCD_DRIVER_H
#define CUBE_LCD_DRIVER_H

#include "global.h"
//#define USE_DMA
typedef struct {
    uint16_t width;     //LCD 宽度
    uint16_t height;    //LCD 高度
    uint16_t id;        //LCD ID
    uint8_t dir;        //横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t wramcmd;   //开始写gram指令
    uint16_t setxcmd;   //设置x坐标指令
    uint16_t setycmd;   //设置y坐标指令
} _lcd_dev;

extern _lcd_dev lcddev;

#define USE_HORIZONTAL  1
//定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

#define LCD_W 320
#define LCD_H 480

#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define BRED        0xF81F
#define GRED        0xFFE0
#define GBLUE       0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN       0xBC40
#define BRRED       0xFC07
#define GRAY        0x8430
#define DARKBLUE    0x01CF
#define LIGHTBLUE   0x7D7C
#define GRAYBLUE    0x5458
#define LIGHTGREEN  0x841F
#define LIGHTGRAY   0xEF5B
#define LGRAY       0xC618
#define LGRAYBLUE   0xA651
#define LBBLUE      0x2B12

void LCD_Init(void);

void LCD_RS_SET();

void LCD_RS_CLR();

void LCD_CS_SET();

void LCD_CS_CLR();

void LCD_Clear(uint16_t Color);

void LCD_ClearToBackground(Point_T LeftUp, Point_T RightDown);

void Lcd_WriteData_16Bit(uint16_t Data);

void LCD_Fill(uint16_t xpos, uint16_t ypos, uint16_t xlen, uint16_t ylen,const uint8_t *src);

void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);

void LCD_direction(uint8_t direction);

void SPI_DMAInit();

void SPI_DMAWrite(uint8_t *data, uint32_t length);


#endif //CUBE_LCD_DRIVER_H
