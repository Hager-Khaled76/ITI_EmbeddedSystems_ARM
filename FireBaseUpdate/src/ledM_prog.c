/*
 * led_prog.c
 *
 *  Created on: Jul 29, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "BIT_MATH.h"
#include "errorStates.h"

#include "GPIO_int.h"
#include "MSTK_Interface.h"

#include "ledM_init.h"
#include "ledM_config.h"




void LEDMATRIX_voidInit()
{
	u8 Local_u8Iterator =0;
	for(Local_u8Iterator =0 ; Local_u8Iterator <13 ;Local_u8Iterator++)
	{
		GPIO_enuSetMode(PORTA , Local_u8Iterator , OUTPUT);
		GPIO_enuSetOutputConfig(PORTA , Local_u8Iterator , Push_Pull , Low_Speed);

	}

	for(Local_u8Iterator =8 ; Local_u8Iterator <12 ;Local_u8Iterator++)
	{
		GPIO_enuSetMode(PORTB , Local_u8Iterator , OUTPUT);
		GPIO_enuSetOutputConfig(PORTB , Local_u8Iterator , Push_Pull , Low_Speed);

	}

}

static void LEDMATRIX_voidSetRawValue(u8 Copy_u8RawVal)
{
	u8 Local_u8Iterator =0;
	for(Local_u8Iterator =0 ; Local_u8Iterator< 8 ; Local_u8Iterator++)
	{
		GPIO_enuSetPinValue(PORTA , Local_u8Iterator , GET_BIT(Copy_u8RawVal , Local_u8Iterator));

	}
}

static void LEDMATRIX_voidDeActivateCoL()
{
	u8 Local_u8Iterator =8;
	for(Local_u8Iterator =8 ; Local_u8Iterator< 13 ; Local_u8Iterator++)
	{
		GPIO_enuSetPinValue(PORTA , Local_u8Iterator , HIGH);

	}

	for(Local_u8Iterator =8 ; Local_u8Iterator <12 ;Local_u8Iterator++)
		{
			GPIO_enuSetMode(PORTB , Local_u8Iterator , OUTPUT);
			GPIO_enuSetOutputConfig(PORTB , Local_u8Iterator , Push_Pull , Low_Speed);

		}

}

void LEDMATRIX_u8Display(u8 *Copy_puArr)
{
	// active coloumn on portA from a8 to a12
	u8 local_u8Iterator =0;
	for(local_u8Iterator=0 ; local_u8Iterator<5 ; local_u8Iterator++)
	{
		// SET ROW
		LEDMATRIX_voidSetRawValue(Copy_puArr[local_u8Iterator]);

		// ACTIVE COL
		GPIO_enuSetPinValue(PORTA ,PIN8+local_u8Iterator , LOW);

		// DELAY = 2500 Usec
		MSTK_voidDelayus(2500);

		// DEACTIVETE COL
		LEDMATRIX_voidDeActivateCoL();
	}

	for(local_u8Iterator=0 ; local_u8Iterator<3 ; local_u8Iterator++)
	{
		// SET ROW
		LEDMATRIX_voidSetRawValue(Copy_puArr[local_u8Iterator+5]);

		// ACTIVE COL
		GPIO_enuSetPinValue(PORTB ,PIN8+local_u8Iterator , LOW);

		// DELAY = 2500 Usec
		MSTK_voidDelayus(2500);

		// DEACTIVETE COL
		LEDMATRIX_voidDeActivateCoL();
	}


}
