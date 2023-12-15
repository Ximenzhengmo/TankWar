#ifndef TANKWAR_MAINMENU_H
#define TANKWAR_MAINMENU_H

#include "main.h"
#include "lcd_driver.h"
#include "stdio.h"
#include "tank.h"
#include "map.h"
#include "Touch.h"
#include "bullet.h"
#include "lever_control.h"
#include "showScore.h"
#include "target.h"
#include "audio.h"
#include "Sound.h"


#define PCA9554_ADDR (0b0111000 << 1)
#define PCA9554_INPUT_PORT_REG 0
#define PCA9554_OUTPUT_PORT_REG 1
#define PCA9554_POL_INV_REG 2
#define PCA9554_CONFIG_REG 3

extern uint8_t type;
extern const unsigned char gImage_MainMenu[235200];

extern uint8_t FPS;

void gameBegin_1player();
void gameBegin_2players();
uint8_t keyDownTest();
void gameBegin();
#endif //TANKWAR_MAINMENU_H
