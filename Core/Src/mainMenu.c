#include "mainMenu.h"

uint8_t type;
uint8_t FPS = 0;
void SPI3_ReInit(void){
    LL_SPI_InitTypeDef SPI_InitStruct = {0};
    SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
    SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
    SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
    SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
    SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
    SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
    SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV8;
    SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
    SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
    SPI_InitStruct.CRCPoly = 7;
    LL_SPI_Init(SPI3, &SPI_InitStruct);
    LL_SPI_SetStandard(SPI3, LL_SPI_PROTOCOL_MOTOROLA);
    LL_SPI_EnableNSSPulseMgt(SPI3);
    LL_SPI_Enable(SPI3);
}
void gameBegin(){
    uint8_t getTouch;
    while( (getTouch = Touch()) == 0 );
    LL_SPI_Disable(SPI3);
    SPI3_ReInit();
    if(getTouch == 2)
    {
        show_score(0, RED);
        show_score(0, GREEN);
        while(1) gameBegin_2players();
    }else if(getTouch == 1)
    {
        while(1) gameBegin_1player();
    }
}

void gameBegin_2players() {
    type = 2;
    static uint8_t direction_r;
    static uint8_t direction_l;
    static uint8_t scoreRed = 0;
    static uint8_t scoreGreen = 0;
    drawMap();
    tank_Init(&redTank);
    tank_Init(&greenTank);
    Bullets_Init();
    Laser_Init(&laserBuff);
    direction_l = redTank.direction;
    direction_r = greenTank.direction;
    uint32_t loopStartTick = 0, loopNowTick = 0, tankDiedTick = 0x3F114514;
    while ( 1 ) {
        FPS++;
        loopStartTick = HAL_GetTick();

        direction_l = get_l_state();
        direction_r = get_r_state();
        drawBullets();

        drawTank(&redTank, direction_l);
        drawTank(&greenTank, direction_r);

        Bullet_TimeOutClear();

        Laser_Create(&laserBuff);
        drawLaserIcon(&laserBuff);
        Laser_tankGet(&laserBuff, &redTank);
        Laser_tankGet(&laserBuff, &greenTank);
        Laser_Renew(&laserBuff);
        Laser_Show(&laserBuff);
        Tank_T *laserShootTank = Laser_Shoot(&laserBuff);
        if ( laserShootTank != NULL ){
            tankDiedTick = HAL_GetTick();
            Laser_Destroy(&laserBuff);
            tank_Destroy(laserShootTank);
        }

        for(uint8_t i = 0; i < BulletNumMax; i++) {
            if (bullets[i].owner != NULL) {
                if (greenTank.isAlive && IsBulletCrashTank(&greenTank, &bullets[i])) {
                    tankDiedTick = HAL_GetTick();
                    Bullet_Destroy(&bullets[i]);
                    if ( laserBuff.owner == &greenTank ){
                        Laser_Destroy(&laserBuff);
                    }
                    tank_Destroy(&greenTank);
                }else if (redTank.isAlive && IsBulletCrashTank(&redTank, &bullets[i])){
                    tankDiedTick = HAL_GetTick();
                    Bullet_Destroy(&bullets[i]);
                    if ( laserBuff.owner == &redTank ){
                        Laser_Destroy(&laserBuff);
                    }
                    tank_Destroy(&redTank);
                }
            }
        }

        loopNowTick = HAL_GetTick();
        if( loopNowTick > tankDiedTick + tankDiedTimeDelay_ms ) {
            break;
        }
        if(loopNowTick - loopStartTick < 1000 / 60 ) {
            HAL_Delay(1000 / 60 - (loopNowTick - loopStartTick));
        }
    }

    if( greenTank.isAlive ) {
        show_score(++scoreGreen, GREEN);
    }else if( redTank.isAlive ) {
        show_score(++scoreRed, RED);
    }
}

void gameBegin_1player() {
    type = 1;
    static uint8_t direction_r;
    uint8_t scoreGreen = 0;
    uint8_t gameOver = 0;
    uint8_t highest_record;
    get_record(&highest_record);
    drawMap();

    show_score(highest_record, BLACK);
    show_score(scoreGreen, GREEN);
    tank_Init(&greenTank);
    Bullets_Init();
    for (uint8_t i = 0; i < TargetNumMax; i++) {
        targetInit(&randomTarget[i]);
        drawTarget(&randomTarget[i]);
    }
    direction_r = greenTank.direction;
    uint32_t loopStartTick = 0, loopNowTick = 0, tankDiedTick = 0x3F114514;
    uint32_t countStart = 0, countNow = 0;
    uint8_t Time=90,seconds=0;
    countStart = HAL_GetTick();
    while (1) {
        FPS++;
        loopStartTick = HAL_GetTick();

        direction_r = get_r_state();
        drawBullets();

        drawTank(&greenTank, direction_r);
        for (uint8_t i = 0; i < TargetNumMax; i++) {
            if ( ! randomTarget[i].isAlive ) {
                targetInit(&randomTarget[i]);
            }
            drawTarget(&randomTarget[i]);
        }

        Bullet_TimeOutClear();

        for (uint8_t i = 0; i < BulletNumMax; i++) {
            if (bullets[i].owner != NULL) {
                if (greenTank.isAlive && IsBulletCrashTank(&greenTank, &bullets[i])) {
                    Bullet_Destroy(&bullets[i]);
                    tank_Destroy(&greenTank);
                    gameOver = 1;
                    tankDiedTick = HAL_GetTick();
                }else{
                    for (uint8_t j = 0; j < TargetNumMax; j++) {
                        if (randomTarget[j].isAlive && IsBulletCrashTarget(&randomTarget[j], &bullets[i])) {
                            show_score(++scoreGreen, GREEN);

                            if(scoreGreen > highest_record){
                                highest_record = scoreGreen;
                                update_record(highest_record);
                                show_score(highest_record, BLACK);
                            }

                            Bullet_Destroy(&bullets[i]);
                            target_Destroy(&randomTarget[j]);
                        }
                    }
                }
            }
        }
        countNow = HAL_GetTick();
        if (countNow - countStart > 1000 * seconds){
            seconds++;
            show_score(--Time, RED);
        }
        loopNowTick = HAL_GetTick();
        if( gameOver && loopNowTick > tankDiedTick + tankDiedTimeDelay_ms )
            break;
        if(Time == 0)
            break;
        if (loopNowTick - loopStartTick < 1000 / 60) {
            HAL_Delay(1000 / 60 - (loopNowTick - loopStartTick));
        }
    }
}

KeyState_T keyDownTest(){
    static uint8_t dataBuffer[1] = {0};
    HAL_I2C_Mem_Read(&hi2c3, PCA9554_ADDR, PCA9554_INPUT_PORT_REG, I2C_MEMADD_SIZE_8BIT, dataBuffer,1,0xff);
    if(dataBuffer[0]==253) {
        return Key_Shoot; // shoot
    }else if (dataBuffer[0]==254){
        return Key_Reset; // reset
    }else {
        return Key_NoPressed; // no pressed
    }
}