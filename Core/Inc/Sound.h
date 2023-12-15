//
// Created by Dell on 2023/12/15.
//

#ifndef TANKWAR_SOUND_H
#define TANKWAR_SOUND_H

#include "main.h"
#include "audio.h"

#define Sound_shoot_len 5000
#define Sound_break_len 10000

extern volatile int8_t saicplt;

int __io_putchar(int ch);
void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai);
void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai);

void play_sound(uint32_t audio_len, uint16_t* audioFile);

extern SAI_HandleTypeDef hsai_BlockA1;
extern SAI_HandleTypeDef hsai_BlockB1;
extern DMA_HandleTypeDef hdma_sai1_a;

extern const uint8_t audioFile_break[];
extern const uint8_t audioFile_shoot[];

#endif //TANKWAR_SOUND_H
