/*
 * main.c
 *
 *  Created on: Jul 23, 2025
 *      Author: c
 */


#include "stdTypes.h"
#include "errorStates.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "MUART_Interface.h"


int main()
{
	RCC_enumIntSysClk();

	RCC_enumEnablePeriphral(RCC_AHB1_BUS , AHB1_GPIOA);
	RCC_enumEnablePeriphral(RCC_APB2_BUS , APB2_USART1);

	MUART_voidInit();
	GPIO_enuSetMode(PORTA , PIN9 ,Alternative_Func);
	GPIO_enuSetAlternativeConfig(PORTA ,PIN9 , AF7);
	GPIO_enuSetMode(PORTA , PIN10 ,Alternative_Func);
	GPIO_enuSetAlternativeConfig(PORTA, PIN10 , AF7);

	GPIO_enuSetMode(PORTA , PIN0 , OUTPUT);
	GPIO_enuSetOutputConfig(PORTA , PIN0 , Push_Pull , Low_Speed);

	char myName[]="Hager_Khaled";

	/** Out of Loop -> Will print one Time */
	for (u8 i = 0; myName[i] != '\0'; i++)
	{
		MUART_voidSendData(myName[i]);
	}

	//u8 res;
	while(1)
	{
		//MUART_voidSendData('H');

		GPIO_enuSetPinValue(PORTA , PIN0 , HIGH);



	}
}


