/*
 * main.c
 *
 *  Created on: Aug 4, 2025
 *      Author: c
 */


#include "stdTypes.h"
#include "BIT_MATH.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "NVIC_int.h"
#include "DMA_Init.h"

void FuncTest();

u32 arr1[15]={1,2,3,4,5,6,7,8,9,10,20,33,21,22,99};
u32 arr2[15]={0};

int main()
{
	// RCC INIT
	RCC_enumIntSysClk();

	// Enable GPIOA ,AHB1
	RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);

	// Enable DMA2 ,AHB1
	RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_DMA2);

	// Set PA0 as output
	GPIO_enuSetMode(PORTA, PIN0, OUTPUT);

	// Configure PA0 (PORTA,PIN0,Push_pull,low_speed)
	GPIO_enuSetOutputConfig(PORTA, PIN0, Push_Pull, Low_Speed);

	// Enable interrupt for DMA2 stream 0 (NVIC=56)
	NVIC__EnableIRQ(56);

	// DMA2 Init
	MDMA2_voidInit();

	// Configure DMA2 stream 0 with sourceAdd=arr1,deststinationAdd=arr2,word,15,Full_Fifo
	MDMA2_voidSetStreamConfig(
		0,
		arr1,
		arr2,
		Word,
		15,
		FIFO_FULL
	);

	// Set callback function
	MDMA2_voidCallBack(0, FuncTest);

	// Enable DMA2 Stream 0 to strat transfer
	MDMA2_voidEnableStream(0);

	while(1)
	{

	}
}

void FuncTest()
{
	// Set PA0 HIGH to indiucate transfer complete
	GPIO_enuSetPinValue(PORTA, PIN0, HIGH);
}

