//
// Created by Dell on 2023/12/10.
//

#ifndef TANKWAR_SHOWSCORE_H
#define TANKWAR_SHOWSCORE_H

#include "lcd_driver.h"
#include "main.h"

#define number_xlen 16
#define number_ylen 22
#define show_xpos 448
#define show_red_ypos 90
#define show_green_ypos 210

void Print_number(uint16_t xpos, uint16_t ypos, uint8_t color, const uint8_t *src);

void show_score(uint8_t score, uint8_t color);


extern const unsigned char numImage[10][704];

#endif //TANKWAR_SHOWSCORE_H
