#include "main.h"
#include "lcd_driver.h"
#include "touch.h"

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