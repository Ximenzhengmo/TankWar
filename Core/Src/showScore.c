//
// Created by Dell on 2023/12/10.
//
#include "main.h"
#include "lcd_driver.h"
#include "showScore.h"


void Print_number(uint16_t xpos, uint16_t ypos, uint8_t color, const uint8_t *src) {
#ifndef USE_DMA
uint16_t *src_16b = (uint16_t *)src;
LCD_SetWindows(xpos, ypos, xpos + number_xlen - 1, ypos + number_ylen - 1);
LCD_RS_SET();
if(color == 0) {
    for (int i = 0; i < number_ylen; i++) {
        for (int j = 0; j < number_xlen; j += 2) {
            Lcd_WriteData_16Bit(src_16b[i * number_xlen + j] | 0xF1);
            Lcd_WriteData_16Bit(src_16b[i * number_xlen + j + 1] | 0xF1);
        }
    }
}
else{
    for (int i = 0; i < number_ylen; i++) {
        for (int j = 0; j < number_xlen; j += 2) {
            Lcd_WriteData_16Bit(src_16b[i * number_xlen + j] | 0x0D);
            Lcd_WriteData_16Bit(src_16b[i * number_xlen + j + 1] | 0x0D);
        }
    }
}
#else
    if( xpos >= LCD_H || ypos >= LCD_W || xpos + xlen >= LCD_H || ypos + ylen >= LCD_W ) {
        printf("error in LCD_fill\n");
        return;
    }
    const uint8_t * srcPtr = src;
    uint32_t len = (uint32_t)(xlen)*ylen*2;

    uint32_t step = 0xFFFF;
    LCD_SetWindows(xpos, ypos, xpos + xlen - 1, ypos + ylen - 1);
    while( len > step ) {
        LCD_RS_SET();
        LCD_CS_CLR();
        SPI_DMAWrite(srcPtr,step);
        len -= step;
        srcPtr += step;
    }
    LCD_RS_SET();
    LCD_CS_CLR();
    SPI_DMAWrite(srcPtr,len);
#endif
}


void show_score(uint8_t score, uint8_t color)  //0代表red,1代表green
{
    uint8_t units_digit = score % 10;
    uint8_t tens_digit = score / 10;

    //red
    if(color == 0){
        LCD_Fill(show_xpos, show_red_ypos,number_xlen, number_ylen, (uint8_t *) whiteBackground);

        Print_number(show_xpos, show_red_ypos, 0, (uint8_t *) numImage[tens_digit]);
        Print_number(show_xpos+number_xlen, show_red_ypos, 0, (uint8_t *) numImage[units_digit]);
    }
    //green
    else{
        LCD_Fill(show_xpos, show_green_ypos,number_xlen, number_ylen, (uint8_t *) whiteBackground);

        Print_number(show_xpos, show_green_ypos, 1, (uint8_t *) numImage[tens_digit]);
        Print_number(show_xpos+number_xlen, show_green_ypos, 1, (uint8_t *) numImage[units_digit]);

    }
}
