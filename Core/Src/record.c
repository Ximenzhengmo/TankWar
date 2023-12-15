//
// Created by Dell on 2023/12/16.
//
#include "main.h"
#include "record.h"

void get_record(uint8_t* data){
    HAL_I2C_Mem_Read(&hi2c3, M24C64_ADDR, 1, I2C_MEMADD_SIZE_16BIT, data, 1, 0xff);
}
void update_record(uint8_t data){
    HAL_I2C_Mem_Write(&hi2c3, M24C64_ADDR, 1, I2C_MEMADD_SIZE_16BIT, &data, 1, 0xff);
}