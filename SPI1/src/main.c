/*
 * main.c
 *
 *  Created on: Jul 30, 2025
 *      Author: c
 */

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "SPI1_init.h"



int main()
{

	RCC_enumIntSysClk();
	RCC_enumEnablePeriphral(RCC_AHB1_BUS , AHB1_GPIOA);
	RCC_enumEnablePeriphral(RCC_APB2_BUS , APB2_SPI1  );

	GPIO_enuSetMode(PORTA , PIN4, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN4 , AF5);

	GPIO_enuSetMode(PORTA , PIN5, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN5 , AF5);

	GPIO_enuSetMode(PORTA , PIN6, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN6 , AF5);

	GPIO_enuSetMode(PORTA , PIN7, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA , PIN7 , AF5);

	SPI1_voidMasterInit();

	while(1)
	{
		SPI_u16Tranceive('H');
	}

	return 0;
}
