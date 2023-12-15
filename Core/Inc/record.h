//
// Created by Dell on 2023/12/16.
//

#ifndef TANKWAR_RECORD_H
#define TANKWAR_RECORD_H
#include "main.h"

#define M24C64_ADDR (0b1010000 << 1)

void get_record(uint8_t* data);
void update_record(uint8_t data);


#endif //TANKWAR_RECORD_H
