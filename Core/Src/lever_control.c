#include "lever_control.h"
#include "main.h"

const float r_tang[5] = {0.32, 0.73, 1, 1.37, 3.07};

const float l_tang[5] = {0.32, 0.73, 1, 1.37, 3.07};

//coordinate adjust
const float l_x_adjust = 0.87;
const float l_y_adjust = 0.78;
const float r_x_adjust = 0.89;
const float r_y_adjust = 0.77;

uint8_t get_l_state() {
    uint16_t value[2];
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 0xff);
    value[0] = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 0xff);
    value[1] = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    int16_t x = value[1] - 1830;
    int16_t y = value[0] - 1770;

    if(x > 0)
        x = x * l_x_adjust;
    if(y > 0)
        y = y * l_y_adjust;
    //stop condition
    if ((x > -start_edge) && (x < start_edge) && (y < start_edge) && (y > -start_edge))
        return 20;
    else {
        if (x >= 0) {
            if (y >= 0) {
                if (y <= x * r_tang[0])
                    return 0;
                else if (y <= x * l_tang[1])
                    return 1;
                else if (y <= x * l_tang[2])
                    return 2;
                else if (y <= x * l_tang[3])
                    return 3;
                else if (y <= x * l_tang[4])
                    return 4;
                else
                    return 5;
            } else {
                if (y >= x * (-l_tang[0]))
                    return 0;
                else if (y >= x * (-l_tang[1]))
                    return 19;
                else if (y >= x * (-l_tang[2]))
                    return 18;
                else if (y >= x * (-l_tang[3]))
                    return 17;
                else if (y >= x * (-l_tang[4]))
                    return 16;
                else
                    return 15;
            }
        } else {
            if (y >= 0) {
                if (y <= x * (-l_tang[0]))
                    return 10;
                else if (y <= x * (-l_tang[1]))
                    return 9;
                else if (y <= x * (-l_tang[2]))
                    return 8;
                else if (y <= x * (-l_tang[3]))
                    return 7;
                else if (y <= x * (-l_tang[4]))
                    return 6;
                else
                    return 5;
            } else {
                if (y >= x * (-l_tang[0]))
                    return 10;
                else if (y >= x * l_tang[1])
                    return 11;
                else if (y >= x * l_tang[2])
                    return 12;
                else if (y >= x * l_tang[3])
                    return 13;
                else if (y >= x * l_tang[4])
                    return 14;
                else
                    return 15;
            }
        }
    }
}

uint8_t get_r_state() {
    //Get ADC2 value
    uint16_t value[2];
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 0xff);
    value[0] = HAL_ADC_GetValue(&hadc2);

    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 0xff);
    value[1] = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);

    int16_t x = value[1] - 1840;
    int16_t y = value[0] - 1760;

    if(x > 0)
        x = x * r_x_adjust;
    if(y > 0)
        y = y * r_y_adjust;

    //stop condition
    if ((x > -start_edge) && (x < start_edge) && (y < start_edge) && (y > -start_edge))
        return 20;
    else {
        if (x >= 0) {
            if (y >= 0) {
                if (y <= x * r_tang[0])
                    return 0;
                else if (y <= x * r_tang[1])
                    return 1;
                else if (y <= x * r_tang[2])
                    return 2;
                else if (y <= x * r_tang[3])
                    return 3;
                else if (y <= x * r_tang[4])
                    return 4;
                else
                    return 5;
            } else {
                if (y >= x * (-r_tang[0]))
                    return 0;
                else if (y >= x * (-r_tang[1]))
                    return 19;
                else if (y >= x * (-r_tang[2]))
                    return 18;
                else if (y >= x * (-r_tang[3]))
                    return 17;
                else if (y >= x * (-r_tang[4]))
                    return 16;
                else
                    return 15;
            }
        } else {
            if (y >= 0) {
                if (y <= x * (-r_tang[0]))
                    return 10;
                else if (y <= x * (-r_tang[1]))
                    return 9;
                else if (y <= x * (-r_tang[2]))
                    return 8;
                else if (y <= x * (-r_tang[3]))
                    return 7;
                else if (y <= x * (-r_tang[4]))
                    return 6;
                else
                    return 5;
            } else {
                if (y >= x * (-r_tang[0]))
                    return 10;
                else if (y >= x * r_tang[1])
                    return 11;
                else if (y >= x * r_tang[2])
                    return 12;
                else if (y >= x * r_tang[3])
                    return 13;
                else if (y >= x * r_tang[4])
                    return 14;
                else
                    return 15;
            }
        }
    }
}
