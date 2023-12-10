//
// Created by 86180 on 2023/12/4.
//
#include "main.h"
#include "lcd_driver.h"

typedef struct touch {
    uint8_t isPressed;
    uint16_t X;
    uint16_t Y;
} TouchTypedef;

typedef enum {
    TOUCH_SUCCESS = 0x00U,
    TOUCH_ERROR = 0x01U,
    TOUCH_BUSY = 0x02U,
    TOUCH_TIMEOUT = 0x03U
} Touch_StatusTypeDef;

uint16_t SPI_SwapBitMode(SPI_TypeDef *SPI,DMA_HandleTypeDef *DMA,uint16_t SPIDataSize){
    uint16_t SPI_BIT_MODE = READ_BIT(SPI->CR2,SPI_CR2_DS_Msk);
    MODIFY_REG(SPI->CR2,SPI_CR2_DS_Msk,SPIDataSize);
    LL_SPI_SetDataWidth(SPI,SPIDataSize);

    if(DMA!=NULL){
        MODIFY_REG(DMA->Instance->CCR,DMA_CCR_PSIZE_Msk,DMA_PDATAALIGN_HALFWORD);
        MODIFY_REG(DMA->Instance->CCR,DMA_CCR_MSIZE_Msk,DMA_MDATAALIGN_HALFWORD);
        DMA->Init.PeriphDataAlignment=SPIDataSize==LL_SPI_DATAWIDTH_16BIT ? DMA_PDATAALIGN_HALFWORD : DMA_PDATAALIGN_BYTE;
        DMA->Init.MemDataAlignment=SPIDataSize==LL_SPI_DATAWIDTH_16BIT ? DMA_MDATAALIGN_HALFWORD : DMA_MDATAALIGN_BYTE;
    }
    return SPI_BIT_MODE;
}


Touch_StatusTypeDef Touch_Read(TouchTypedef *dst){
    if(LL_GPIO_IsInputPinSet(PEN_IRQ_GPIO_Port,PEN_IRQ_Pin) == 0u)
        dst->isPressed=1;
    else{
        dst->isPressed=0;
        return TOUCH_TIMEOUT;
    }
    LL_GPIO_ResetOutputPin(SPI3_CS_TOUCH_GPIO_Port,SPI3_CS_TOUCH_Pin);

    uint8_t xr[3];
    uint8_t yr[3];

    uint8_t instx[3] = {0xd0,0x00,0x00};
    uint8_t insty[3] = {0x90,0x00,0x00};

    uint8_t XNum = 0,YNum=0;
    while(XNum<3){
        while(LL_SPI_IsActiveFlag_TXE(SPI3)==0);
        LL_SPI_TransmitData8(SPI3, instx[XNum++]);
        while(LL_SPI_IsActiveFlag_BSY(SPI3));
        while(LL_SPI_IsActiveFlag_RXNE(SPI3)==0);
        xr[XNum++] = LL_SPI_ReceiveData8(SPI3);
    }
    dst->Y=(((uint16_t)xr[1]<<8)|xr[2])>>4;
    YNum=0;
    while(YNum<3) {
        while(LL_SPI_IsActiveFlag_TXE(SPI3)==0);
        LL_SPI_TransmitData8(SPI3, insty[YNum++]);
        while(LL_SPI_IsActiveFlag_BSY(SPI3));
        while(LL_SPI_IsActiveFlag_RXNE(SPI3)==0);
        yr[YNum++]=LL_SPI_ReceiveData8(SPI3);
    }
    dst->X=(((uint16_t)yr[1]<<8)|yr[2])>>4;
    LL_GPIO_SetOutputPin(SPI3_CS_TOUCH_GPIO_Port,SPI3_CS_TOUCH_Pin);
    return TOUCH_SUCCESS;
}

void Touch(void)
{
    LL_GPIO_SetOutputPin(SPI3_CS_SDCARD_GPIO_Port,SPI3_CS_SDCARD_Pin);
    LL_GPIO_SetOutputPin(SPI3_CS_TOUCH_GPIO_Port,SPI3_CS_TOUCH_Pin);

    TouchTypedef user_touch;
    for(;;){
        Touch_Read(&user_touch);
        if(user_touch.isPressed){
            printf("%d %d\n",user_touch.X,user_touch.Y);
        }
    }
}