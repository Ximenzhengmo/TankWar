//
// Created by zouyuyang on 2023/9/8.
//

#include "main.h"
#include "audio.h"

extern I2C_HandleTypeDef hi2c3;
extern SAI_HandleTypeDef hsai_BlockA1, hsai_BlockB1;

void write_reg(uint8_t devaddr, uint8_t reg, uint8_t data) {
  if (HAL_I2C_Mem_Write(&hi2c3, devaddr, reg, 1, &data, 1, 0xff) != HAL_OK) {
    Error_Handler();
  }
}

HAL_StatusTypeDef ES8388_init() {
/* mute DAC during setup, power up all systems, slave mode */
  write_reg(ES8388_ADDR, ES8388_DACCONTROL3, 0x04);
  write_reg(ES8388_ADDR, ES8388_CONTROL2, 0x50);
  write_reg(ES8388_ADDR, ES8388_CHIPPOWER, 0x00);
  write_reg(ES8388_ADDR, ES8388_MASTERMODE, 0x00);

/* power up DAC and enable LOUT1+2 / ROUT1+2, ADC sample rate = DAC sample rate */
  write_reg(ES8388_ADDR, ES8388_DACPOWER, 0x3e);
  write_reg(ES8388_ADDR, ES8388_CONTROL1, 0x12);

/* DAC I2S setup: 16 bit word length, I2S format; MCLK / Fs = 256*/
  write_reg(ES8388_ADDR, ES8388_DACCONTROL1, 0x18);
  write_reg(ES8388_ADDR, ES8388_DACCONTROL2, 0x02);

/* DAC to output route mixer configuration: DAC MIX TO OUTPUT */
  write_reg(ES8388_ADDR, ES8388_DACCONTROL16, 0x1B); // 0b00_011_011
  write_reg(ES8388_ADDR, ES8388_DACCONTROL17, 0x90);
  write_reg(ES8388_ADDR, ES8388_DACCONTROL20, 0x90); // 0b1001_0000

/* DAC and ADC use same LRCK, enable MCLK input; output resistance setup */
  write_reg(ES8388_ADDR, ES8388_DACCONTROL21, 0x80);
  write_reg(ES8388_ADDR, ES8388_DACCONTROL23, 0x00);

/* DAC volume control: 0dB (maximum, unattenuated)  */
  write_reg(ES8388_ADDR, ES8388_DACCONTROL5, 0x00);
  write_reg(ES8388_ADDR, ES8388_DACCONTROL4, 0x00);

/* power down ADC while configuring; volume: +9dB for both channels */
  write_reg(ES8388_ADDR, ES8388_ADCPOWER, 0xff);
  write_reg(ES8388_ADDR, ES8388_ADCCONTROL1, 0x88); // +24db

/* select LINPUT2 / RINPUT2 as ADC input; stereo; 16 bit word length, format right-justified, MCLK / Fs = 256 */
  write_reg(ES8388_ADDR, ES8388_ADCCONTROL2, 0x50); // 50
  write_reg(ES8388_ADDR, ES8388_ADCCONTROL3, 0x80); // Input 2, 0x00 Input1,
  write_reg(ES8388_ADDR, ES8388_ADCCONTROL4, 0x0c);
  write_reg(ES8388_ADDR, ES8388_ADCCONTROL5, 0x02); // ADCFsRatio @ [4:0]

/* set ADC volume */
  write_reg(ES8388_ADDR, ES8388_ADCCONTROL8, 0x80);
  write_reg(ES8388_ADDR, ES8388_ADCCONTROL9, 0x80);

/* set LOUT1 / ROUT1 volume: 0dB (unattenuated) */
  write_reg(ES8388_ADDR, ES8388_DACCONTROL24, 0x24);
  write_reg(ES8388_ADDR, ES8388_DACCONTROL25, 0x24);

/* set LOUT2 / ROUT2 volume: 0dB (unattenuated) */
  write_reg(ES8388_ADDR, ES8388_DACCONTROL26, 0x24);
  write_reg(ES8388_ADDR, ES8388_DACCONTROL27, 0x24);

/* power up and enable DAC; power up ADC (no MIC bias) */
  write_reg(ES8388_ADDR, ES8388_DACPOWER, 0x3c);
  write_reg(ES8388_ADDR, ES8388_DACCONTROL3, 0x00);
  write_reg(ES8388_ADDR, ES8388_ADCPOWER, 0x00);
  write_reg(ES8388_ADDR, ES8388_CHIPPOWER, 0x00);
}