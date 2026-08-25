/*
 * main.c
 *
 *  Created on: Jul 9, 2025
 *      Author: dell
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_Interface.h"
#include "MGPIO_Interface.h"


int main()
{
	u32 x;
	MRCC_voidInit();
	MRCC_voidEnablePeripheralClock(AHB1_BUS,AHB1_GPIOA);
	MRCC_voidEnablePeripheralClock(AHB1_BUS,AHB1_GPIOB);

	MGPIO_voidSetMode(PORTA,PIN0,OUTPUT);
	MGPIO_voidSetOutputConfig(PORTA,PIN0,Push_Pull,Low_Speed);
	MGPIO_voidSetPinValueAtomic(PORTA,PIN0,LOW);

	MGPIO_voidSetMode(PORTB,PIN1,INPUT);
	MGPIO_voidSetInputConfig(PORTB,PIN1,PULLUP);

	while(1)
	{
		x=MGPIO_u8GetPinValue(PORTB,PIN1);
		if(x==0)
		{
			MGPIO_voidSetPinValueAtomic(PORTA,PIN0,HIGH);
		}
	}
}
