#ifndef TANKWAR_MAP_H
#define TANKWAR_MAP_H

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lcd_driver.h"

#define XMAX 7
#define YMAX 5

#define boxSideLen 64
#define wallWidth (4>>1)

extern uint16_t MapXLen;
extern uint16_t MapYLen;

typedef struct {
    uint8_t up: 1; // if box up is wall ? 0 : 1
    uint8_t down: 1; // if box down is wall ? 0 : 1
    uint8_t left: 1; // if box left is wall ? 0 : 1
    uint8_t right: 1; // if box right is wall ? 0 : 1
    uint8_t : 4; // preserved for memory alignment
    uint8_t id; // box id
    uint8_t x: 4; // box x (top left corner)
    uint8_t y: 4; // box y (top left corner)
} Box_T;

typedef struct {
    uint8_t inBox_id;
    uint8_t outBox_id;
} Wall_T;

typedef struct Node_T {
    union {
        Wall_T wall;
        uint8_t num;
    } property;
    struct Node_T *next;
} Node_T;

HAL_StatusTypeDef createMap();
void drawMap();
uint8_t isWall(uint16_t x, uint16_t y);
uint8_t isTouchWall(Point_T p1, Point_T p2, Point_T p3, Point_T p4);

#endif //TANKWAR_MAP_H
