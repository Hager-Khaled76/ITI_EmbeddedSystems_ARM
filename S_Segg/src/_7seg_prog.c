/*
 * SSEG_prog.c
 *
 * Created: 10/1/2024 5:34:30 PM
 * Author: c
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "GPIO_int.h"
#include "RCC_Int.h"

#include "SSEG_priv.h"
#include "SSEG_config.h"
#include "SSEG_int.h"


u8 seg[SSEG_MAX]={SSEG_U8_0,SSEG_U8_1,SSEG_U8_2,SSEG_U8_3,SSEG_U8_4,SSEG_U8_5,SSEG_U8_6,SSEG_U8_7,SSEG_U8_8,SSEG_U8_9};

ES_t SSEG_u8_init()
{
	ES_t LocalErrorState = ES_NOK;

    #if SSEG_U8_PORT == PORTA
        LocalErrorState = RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);
    #elif SSEG_U8_PORT == PORTB
        LocalErrorState = RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);
    #elif SSEG_U8_PORT == PORTC
        LocalErrorState = RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOC);
    #else
        LocalErrorState = ES_OUT_OF_RANGE;
    #endif


    if (LocalErrorState == ES_OK)
    {

        GPIO_enuSetMode(SSEG_U8_PORT, SSEG_PIN_A, OUTPUT);
        GPIO_enuSetMode(SSEG_U8_PORT, SSEG_PIN_B, OUTPUT);
        GPIO_enuSetMode(SSEG_U8_PORT, SSEG_PIN_C, OUTPUT);
        GPIO_enuSetMode(SSEG_U8_PORT, SSEG_PIN_D, OUTPUT);
        GPIO_enuSetMode(SSEG_U8_PORT, SSEG_PIN_E, OUTPUT);
        GPIO_enuSetMode(SSEG_U8_PORT, SSEG_PIN_F, OUTPUT);
        GPIO_enuSetMode(SSEG_U8_PORT, SSEG_PIN_G, OUTPUT);

        LocalErrorState = ES_OK;
    }
	return LocalErrorState;

}

ES_t SSEG_U8_Display(u8 SSE_U8_Data)
{
	ES_t LocalErrorState = ES_NOK;
    u8 displayPattern;

    if(SSE_U8_Data >= SSEG_MIN && SSE_U8_Data < SSEG_MAX)
	{
        displayPattern = seg[SSE_U8_Data];

		#if SSEG_HARDWARE == SSEG_U8_CATHODE

            GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_A, GET_BIT(displayPattern, 0) ? HIGH : LOW);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_B, GET_BIT(displayPattern, 1) ? HIGH : LOW);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_C, GET_BIT(displayPattern, 2) ? HIGH : LOW);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_D, GET_BIT(displayPattern, 3) ? HIGH : LOW);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_E, GET_BIT(displayPattern, 4) ? HIGH : LOW);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_F, GET_BIT(displayPattern, 5) ? HIGH : LOW);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_G, GET_BIT(displayPattern, 6) ? HIGH : LOW);
		#elif SSEG_HARDWARE == SSEG_U8_ANODE

		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_A, GET_BIT(displayPattern, 0) ? LOW : HIGH);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_B, GET_BIT(displayPattern, 1) ? LOW : HIGH);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_C, GET_BIT(displayPattern, 2) ? LOW : HIGH);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_D, GET_BIT(displayPattern, 3) ? LOW : HIGH);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_E, GET_BIT(displayPattern, 4) ? LOW : HIGH);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_F, GET_BIT(displayPattern, 5) ? LOW : HIGH);
		    GPIO_enuSetPinValueAtomic(SSEG_U8_PORT, SSEG_PIN_G, GET_BIT(displayPattern, 6) ? LOW : HIGH);
		#endif

		LocalErrorState = ES_OK;
	}

    else
    {
        LocalErrorState = ES_OUT_OF_RANGE;
    }

	return LocalErrorState;

}
