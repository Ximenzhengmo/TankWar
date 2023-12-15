//
// Created by Dell on 2023/12/15.
//

#include "main.h"
#include "sound.h"

volatile int8_t saicplt = 1;

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai) {
    if (hsai->Instance == SAI1_Block_A) {
        saicplt = 1;
    }
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai){
    if(hsai->Instance == SAI1_Block_B){
        saicplt = 1;
    }
}

void play_sound(uint32_t audio_len, uint16_t * audioFile){
    if( saicplt == 1 ) {
        HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *)audioFile, audio_len);
        saicplt = 0;
    }
}