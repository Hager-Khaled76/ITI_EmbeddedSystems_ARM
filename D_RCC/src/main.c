/*
 * main.c
 *
 *  Created on: Jul 9, 2025
 *      Author: c
 */

#include "stdTypes.h""
#include "BIT_MATH.h"

#include "RCC_Int.h""


int main()
{
	RCC_enumIntSysClk();

	RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);

	while(1)
	{

	}
}


