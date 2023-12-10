#include "main.h"
#include "lcd_driver.h"

void LCD_RS_SET() {
#ifdef USE_DMA
    while(LL_SPI_IsActiveFlag_BSY( SPI3));
#endif
    LL_GPIO_SetOutputPin(DCRS_GPIO_Port, DCRS_Pin);
}

void LCD_RS_CLR() {
#ifdef USE_DMA
    while(LL_SPI_IsActiveFlag_BSY( SPI3));
#endif
    LL_GPIO_ResetOutputPin(DCRS_GPIO_Port, DCRS_Pin);
}

void LCD_CS_SET() {
    LL_GPIO_SetOutputPin(SPI3_CS_GPIO_Port, SPI3_CS_Pin);
}

void LCD_CS_CLR() {
    LL_GPIO_ResetOutputPin(SPI3_CS_GPIO_Port, SPI3_CS_Pin);
}

void SPI_WriteByte(uint8_t data) {
#ifndef USE_DMA
    LCD_CS_CLR();
    while (!LL_SPI_IsActiveFlag_TXE(SPI3));
    LL_SPI_TransmitData8(SPI3, data);
    while (LL_SPI_IsActiveFlag_BSY(SPI3));
    LCD_CS_SET();
#else
    LCD_CS_CLR();
    SPI_DMAWrite(&data, 1);
#endif
}

void Lcd_WriteData_16Bit(uint16_t Data) {
    LCD_RS_SET();
    SPI_WriteByte(Data >> 8);
    SPI_WriteByte(Data);
}

void LCD_Fill(uint16_t xpos, uint16_t ypos, uint16_t xlen, uint16_t ylen, const uint8_t *src) {
#ifndef USE_DMA
    uint16_t *src_16b = (uint16_t *) src;
    LCD_SetWindows(xpos, ypos, xpos + xlen - 1, ypos + ylen - 1);
    LCD_RS_SET();
    for (int i = 0; i < ylen; i++) {
        for (int j = 0; j < xlen; j++) {
            Lcd_WriteData_16Bit(src_16b[i * xlen + j]);
        }
    }
#else
    if( xpos >= LCD_H || ypos >= LCD_W || xpos + xlen >= LCD_H || ypos + ylen >= LCD_W ) {
        printf("error in LCD_fill\n");
        return;
    }
    const uint8_t * srcPtr = src;
    uint32_t len = (uint32_t)(xlen)*ylen*2;

    uint32_t step = 0xFFFF;
    LCD_SetWindows(xpos, ypos, xpos + xlen - 1, ypos + ylen - 1);
    while( len > step ) {
        LCD_RS_SET();
        LCD_CS_CLR();
        SPI_DMAWrite(srcPtr,step);
        len -= step;
        srcPtr += step;
    }
    LCD_RS_SET();
    LCD_CS_CLR();
    SPI_DMAWrite(srcPtr,len);
#endif
}

_lcd_dev lcddev;

void LCD_WR_REG(uint8_t data) {
    LCD_RS_CLR();
    SPI_WriteByte(data);
}

void LCD_WR_DATA(uint8_t data) {
    LCD_RS_SET();
    SPI_WriteByte(data);
}

void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue) {
    LCD_WR_REG(LCD_Reg);
    LCD_WR_DATA(LCD_RegValue);
}

void LCD_WriteRAM_Prepare(void) {
    LCD_WR_REG(lcddev.wramcmd);
}

void LCD_Clear(uint16_t Color) {
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
    LCD_RS_SET();

    for (int i = 0; i < 480; i++) {
        for (int j = 0; j < 320; j++) {
            Lcd_WriteData_16Bit(Color);
        }
    }
}

void SPI_DMAInit() {
    /* Configure the DMA1_Channel3 functional parameters */
    LL_DMA_ConfigTransfer(DMA1,
                          LL_DMA_CHANNEL_1,
                          LL_DMA_DIRECTION_MEMORY_TO_PERIPH | LL_DMA_PRIORITY_HIGH | LL_DMA_MODE_NORMAL |
                          LL_DMA_PERIPH_NOINCREMENT | LL_DMA_MEMORY_INCREMENT |
                          LL_DMA_PDATAALIGN_BYTE | LL_DMA_MDATAALIGN_BYTE);

    LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_SPI3_TX);

    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
}

void SPI_DMAWrite(uint8_t *data, uint32_t length) {
    LL_DMA_ConfigAddresses(DMA1,
                           LL_DMA_CHANNEL_1,
                           (uint32_t) data, LL_SPI_DMA_GetRegAddr(SPI3),
                           LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, length);

    /* Configure SPI1 DMA transfer interrupts */
    /* Enable DMA RX Interrupt */
    LL_SPI_EnableDMAReq_TX(SPI3);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
}

void LCD_Init(void) {
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0xC3);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0x96);
    LCD_WR_REG(0x36);
    LCD_WR_DATA(0x68);
    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x05);
    LCD_WR_REG(0xB0);
    LCD_WR_DATA(0x80);
    LCD_WR_REG(0xB6);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x02);
    LCD_WR_REG(0xB5);
    LCD_WR_DATA(0x02);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x04);
    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x80);
    LCD_WR_DATA(0x10);
    LCD_WR_REG(0xB4);
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0xB7);
    LCD_WR_DATA(0xC6);
    LCD_WR_REG(0xC5);
    LCD_WR_DATA(0x24);
    LCD_WR_REG(0xE4);
    LCD_WR_DATA(0x31);
    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x40);
    LCD_WR_DATA(0x8A);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x29);
    LCD_WR_DATA(0x19);
    LCD_WR_DATA(0xA5);
    LCD_WR_DATA(0x33);
    LCD_WR_REG(0xC2);
    LCD_WR_REG(0xA7);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA(0xF0);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x2B);
    LCD_WR_DATA(0x3C);
    LCD_WR_DATA(0x44);
    LCD_WR_DATA(0x4B);
    LCD_WR_DATA(0x1B);
    LCD_WR_DATA(0x18);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x1D);
    LCD_WR_DATA(0x21);

    LCD_WR_REG(0XE1);
    LCD_WR_DATA(0xF0);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x0C);
    LCD_WR_DATA(0x0D);
    LCD_WR_DATA(0x27);
    LCD_WR_DATA(0x3B);
    LCD_WR_DATA(0x44);
    LCD_WR_DATA(0x4D);
    LCD_WR_DATA(0x0B);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x1D);
    LCD_WR_DATA(0x21);

    LCD_WR_REG(0X36);
    LCD_WR_DATA(0xEC);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0xC3);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0x69);
    LCD_WR_REG(0X13);
    LCD_WR_REG(0X11);
    LCD_WR_REG(0X29);

    LCD_direction(USE_HORIZONTAL);
    LCD_Clear(WHITE);
}

void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd) {
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(xStar >> 8);
    LCD_WR_DATA(0x00FF & xStar);
    LCD_WR_DATA(xEnd >> 8);
    LCD_WR_DATA(0x00FF & xEnd);

    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(yStar >> 8);
    LCD_WR_DATA(0x00FF & yStar);
    LCD_WR_DATA(yEnd >> 8);
    LCD_WR_DATA(0x00FF & yEnd);

    LCD_WriteRAM_Prepare();
}

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos) {
    LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

void LCD_direction(uint8_t direction) {
    lcddev.setxcmd = 0x2A;
    lcddev.setycmd = 0x2B;
    lcddev.wramcmd = 0x2C;
    switch (direction) {
        case 0:
            lcddev.width = LCD_W;
            lcddev.height = LCD_H;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 6));
            break;
        case 1:
            lcddev.width = LCD_H;
            lcddev.height = LCD_W;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 5));
            break;
        case 2:
            lcddev.width = LCD_W;
            lcddev.height = LCD_H;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 7));
            break;
        case 3:
            lcddev.width = LCD_H;
            lcddev.height = LCD_W;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 6) | (1 << 5));
            break;
        default:
            break;
    }
}
