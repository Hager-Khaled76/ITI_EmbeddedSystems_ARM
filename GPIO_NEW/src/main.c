/*
 * main.c
 *
 *  Created on: Jul 13, 2025
 *      Author: c
 */




/*
 * main.c
 *
 *  Created on: Jul 10, 2025
 *      Author: c
 */


#include "stdTypes.h"
#include "BIT_MATH.h"
#include "errorStates.h"

#include "RCC_Int.h"
#include "GPIO_int.h"



int main()
{

	RCC_enumIntSysClk();

	/*RCC_enumEnablePeriphral(RCC_AHB1_BUS,AHB1_GPIOA);//LED
	RCC_enumEnablePeriphral(RCC_AHB1_BUS,AHB1_GPIOB);//SWITCH

	GPIO_enuSetMode(PORTA,PIN0,OUTPUT);//Led is output on porta , pin0

	GPIO_enuSetOutputConfig(PORTA,PIN0,Push_Pull,Low_Speed);//Led is output-> push-pull

	GPIO_enuSetPinValueAtomic(PORTA,PIN0,LOW);// initial value to led is low

	GPIO_enuSetMode(PORTB,PIN1,INPUT);// Switch is input on portb , pin1

	GPIO_enuSetInputConfig(PORTB,PIN1,PULLUP);//Switch is input ->pullup

	u8 LocalSwitchState ;
	ES_t LocalErrorState ;*/

	while(1)
	{
		/*LocalErrorState = GPIO_enuGetPinValue(PORTB ,PIN1 , &LocalSwitchState);

		if(LocalErrorState == ES_OK)
		{
			if(LocalSwitchState == LOW)// if pressed
				GPIO_enuSetPinValueAtomic(PORTA,PIN0,HIGH);// Led is High

			else
				GPIO_enuSetPinValueAtomic(PORTA,PIN0,LOW);

		}*/

	}

}


