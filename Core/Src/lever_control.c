#include "lever_control.h"
#include "main.h"

const float r_tang_1[5] = {0.32, 0.73, 1, 1.37, 3.07};
const float r_tang_2[5] = {0.32, 0.73, 1, 1.37, 3.07};
const float r_tang_3[5] = {0.32, 0.73, 1, 1.37, 3.07};
const float r_tang_4[5] = {0.1, 0.73, 1.05, 1.37, 2.5};

const float l_tang_1[5] = {0.32, 0.73, 1, 1.37, 3.07};
const float l_tang_2[5] = {0.32, 0.73, 1, 1.37, 3.07};
const float l_tang_3[5] = {0.32, 0.73, 1, 1.37, 3.07};
const float l_tang_4[5] = {0.32, 0.73, 1, 1.37, 3.07};

//Coordinate mapping adjustment
const float r_x_adjust = 0.809;
const float r_y_adjust = 0.774;
const float l_x_adjust = 0.82;
const float l_y_adjust = 0.767;


uint8_t get_l_state() {
    uint16_t value[2];
    HAL_ADC_Start(&hadc1);
//      HAL_ADC_PollForConversion(&hadc1,10);
    value[0] = HAL_ADC_GetValue(&hadc1);
//      HAL_ADC_PollForConversion(&hadc1,10);
    value[1] = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    int16_t x = value[0] - 1835;
    int16_t y = value[1] - 1772;

    if (x > 0)
        x = x * l_x_adjust;
    if (y > 0)
        y = y * l_y_adjust;
    printf("%d %d\n", x, y);
    //stop condition
    if ((x > -start_edge) && (x < start_edge) && (y < start_edge) && (y > -start_edge))
        return 20;
    else {
        if (x >= 0) {
            if (y >= 0) {
                if (y <= x * r_tang_1[0])
                    return 0;
                else if (y <= x * l_tang_1[1])
                    return 1;
                else if (y <= x * l_tang_1[2])
                    return 2;
                else if (y <= x * l_tang_1[3])
                    return 3;
                else if (y <= x * l_tang_1[4])
                    return 4;
                else
                    return 5;
            } else {
                if (y >= x * (-l_tang_4[0]))
                    return 0;
                else if (y >= x * (-l_tang_4[1]))
                    return 19;
                else if (y >= x * (-l_tang_4[2]))
                    return 18;
                else if (y >= x * (-l_tang_4[3]))
                    return 17;
                else if (y >= x * (-l_tang_4[4]))
                    return 16;
                else
                    return 15;
            }
        } else {
            if (y >= 0) {
                if (y <= x * (-l_tang_2[0]))
                    return 10;
                else if (y <= x * (-l_tang_2[1]))
                    return 9;
                else if (y <= x * (-l_tang_2[2]))
                    return 8;
                else if (y <= x * (-l_tang_2[3]))
                    return 7;
                else if (y <= x * (-l_tang_2[4]))
                    return 6;
                else
                    return 5;
            } else {
                if (y >= x * (-l_tang_3[0]))
                    return 10;
                else if (y >= x * l_tang_3[1])
                    return 11;
                else if (y >= x * l_tang_3[2])
                    return 12;
                else if (y >= x * l_tang_3[3])
                    return 13;
                else if (y >= x * l_tang_3[4])
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
//      HAL_ADC_PollForConversion(&hadc2,10);
    value[0] = HAL_ADC_GetValue(&hadc2);
//      HAL_ADC_PollForConversion(&hadc2,10);
    value[1] = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);

    int16_t x = value[0] - 1769;
    int16_t y = value[1] - 1766;

    if (x > 0)
        x = x * r_x_adjust;
    if (y > 0)
        y = y * r_y_adjust;

    //stop condition
    if ((x > -start_edge) && (x < start_edge) && (y < start_edge) && (y > -start_edge))
        return 20;
    else {
        if (x >= 0) {
            if (y >= 0) {
                if (y <= x * r_tang_1[0])
                    return 0;
                else if (y <= x * r_tang_1[1])
                    return 1;
                else if (y <= x * r_tang_1[2])
                    return 2;
                else if (y <= x * r_tang_1[3])
                    return 3;
                else if (y <= x * r_tang_1[4])
                    return 4;
                else
                    return 5;
            } else {
                if (y >= x * (-r_tang_4[0]))
                    return 0;
                else if (y >= x * (-r_tang_4[1]))
                    return 19;
                else if (y >= x * (-r_tang_4[2]))
                    return 18;
                else if (y >= x * (-r_tang_4[3]))
                    return 17;
                else if (y >= x * (-r_tang_4[4]))
                    return 16;
                else
                    return 15;
            }
        } else {
            if (y >= 0) {
                if (y <= x * (-r_tang_2[0]))
                    return 10;
                else if (y <= x * (-r_tang_2[1]))
                    return 9;
                else if (y <= x * (-r_tang_2[2]))
                    return 8;
                else if (y <= x * (-r_tang_2[3]))
                    return 7;
                else if (y <= x * (-r_tang_2[4]))
                    return 6;
                else
                    return 5;
            } else {
                if (y >= x * (-r_tang_3[0]))
                    return 10;
                else if (y >= x * r_tang_3[1])
                    return 11;
                else if (y >= x * r_tang_3[2])
                    return 12;
                else if (y >= x * r_tang_3[3])
                    return 13;
                else if (y >= x * r_tang_3[4])
                    return 14;
                else
                    return 15;
            }
        }
    }
}
