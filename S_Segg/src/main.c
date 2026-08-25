/*
 * main.c
 *
 * Created on: Jul 15, 2025
 * Author: Your_Name
 */
/*
#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "SSEG_int.h"


void _delay_ms(u32 milliseconds) {
    for (u32 i = 0; i < milliseconds * 1000; i++) {
        // Þã ÈÊÚÏíá åÐå ÇáÞíãÉ ÈäÇÁð Úáì ÊÑÏÏ ÇáãÚÇáÌ ÇáÎÇÕ Èß
        // åÐÇ ÊÞÑíÈ ÊÞÑíÈí ÌÏÇð áÊÑÏÏ 16MHz Úáì STM32F401
        // áÊÃÎíÑÇÊ ÏÞíÞÉ¡ ÇÓÊÎÏã Timer Ãæ SysTick
        volatile u32 dummy = 0; // áãäÚ ÊÍÓíäÇÊ ÇáÜ Compiler ÇáÊí ÞÏ ÊÒíá ÇáÍáÞÉ
        (void)dummy; // áÊåÏÆÉ ÊÍÐíÑÇÊ ÇáÜ Compiler
    }
}


int main()
{
    ES_t error_state;


    error_state = RCC_enumIntSysClk();
    if (error_state != ES_OK) {
        while(1);
    }

    error_state = SSEG_u8_init();
    if (error_state != ES_OK) {

        while(1);
    }


    SSEG_U8_Display(0);

    while (1)
    {
        for(u8 count = 0 ; count < 10 ; count++)
        {
            SSEG_U8_Display(count);
            _delay_ms(500);
        }
    }
}
*/



#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"
#include "stm32f4xx_hal.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "SSEG_int.h"


int main()
{
    ES_t error_state;
    error_state = RCC_enumIntSysClk();

    if (error_state != ES_OK) {
        while(1);
    }

    error_state = SSEG_u8_init();
    if (error_state != ES_OK) {
        while(1);
    }

    SSEG_U8_Display(0);

    while (1)
    {
        for(u8 count = 0 ; count < 10 ; count++)
        {
            SSEG_U8_Display(count);

            HAL_Delay(500);
        }
    }
}
