//
// Created by Dell on 2023/12/10.
//
#include "main.h"
#include "lcd_driver.h"
#include "showScore.h"


void Print_number(uint16_t xpos, uint16_t ypos, uint16_t color, const uint8_t *src) {
    uint16_t *src_16b = (uint16_t *) src;
    LCD_SetWindows(xpos, ypos, xpos + number_xlen - 1, ypos + number_ylen - 1);
    LCD_RS_SET();
    for (int i = 0; i < number_ylen; i++) {
        for (int j = 0; j < number_xlen; j++) {
            Lcd_WriteData_16Bit(src_16b[i * number_xlen + j] | color);
        }
    }
}


void show_score(uint8_t score, uint16_t color)
{
    score %= 100;
    uint8_t units_digit = score % 10;
    uint8_t tens_digit = score / 10;
    if( color == RED ) {

        Print_number(show_xpos, show_red_ypos, color, (uint8_t *) numImage[tens_digit]);
        Print_number(show_xpos + number_xlen, show_red_ypos, color, (uint8_t *) numImage[units_digit]);
    }
    if( color == GREEN ){
        Print_number(show_xpos, show_green_ypos, color, (uint8_t *) numImage[tens_digit]);
        Print_number(show_xpos + number_xlen, show_green_ypos, color, (uint8_t *) numImage[units_digit]);
    }

    if(color == BLACK){
        Print_number(show_xpos, show_black_ypos, color, (uint8_t *) numImage[tens_digit]);
        Print_number(show_xpos + number_xlen, show_black_ypos, color, (uint8_t *) numImage[units_digit]);
    }
}
