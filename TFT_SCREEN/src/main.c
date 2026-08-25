/*
 * main.c
 *
 *  Created on: Jul 31, 2025
 *      Author: c
 */


#include "stdTypes.h"
#include "errorStates.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "MSTK_Interface.h"

#include "TFT_Init.h"
#include "TFT_image.h"


int main()
{
	RCC_enumIntSysClk();
	RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);
	RCC_enumEnablePeriphral(RCC_APB2_BUS ,APB2_SPI1);


	GPIO_enuSetMode(PORTA , PIN4, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN4 , AF5);

	GPIO_enuSetMode(PORTA , PIN5, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN5 , AF5);

	GPIO_enuSetMode(PORTA , PIN6, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN6 , AF5);

	GPIO_enuSetMode(PORTA , PIN7, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN7 , AF5);

	//GPIO_enuSetMode(PORTA , PIN0, OUTPUT);
	//GPIO_enuSetOutputConfig(PORTA ,PIN0 , Push_Pull , Low_Speed);


	MSTK_voidInit();
	SPI1_voidMasterInit();
	TFT_voidInit();
	TFT_voidDisplay(IMAGE);

	while(1)
	{

	}


}
