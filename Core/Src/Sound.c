//
// Created by Dell on 2023/12/15.
//

#include "main.h"
#include "audio.h"
#include "Sound.h"

//int __io_putchar(int ch)
//{
//    while (ITM->PORT[0].u32 == 0UL)
//        __NOP();
//    ITM->PORT[0].u8 = (uint8_t) ch;
//    return ch;
//}

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
    uint16_t *audio_play = (uint16_t *) audioFile;
    if( saicplt == 1 ) {
        HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *) audio_play, audio_len);
        saicplt = 0;
    }
//    for (int i = 0; i < audio_len; i += 60000) {
//        uint32_t send_len = 60000;
//        if (audio_len - i < 60000)
//            send_len = audio_len - i;
//        if (HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *) &audio_play[i], send_len) != HAL_OK) {
//            Error_Handler();
//        }
//        while (saicplt == 0);
//        saicplt = 0;
//    }
}