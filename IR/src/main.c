/*
 * main.c
 *
 *  Created on: Aug 3, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "BIT_MATH.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "EXTI_int.h"
#include "MSTK_Interface.h"



void Func1();
void Func2();
u8 GLB_u8StartFlag=0;
u32 GLB_u8IRArr[33]={0};
u8 GLB_u8Counter=0;
u8 Value=0;
int main()
{
	RCC_enumIntSysClk();
	RCC_enumEnablePeriphral(RCC_AHB1_BUS,AHB1_GPIOA);
	RCC_enumEnablePeriphral(RCC_APB2_BUS,RCC_AHB2_SYSCFG);

	MSTK_voidInit();

	GPIO_enuSetMode(PORTA,PIN1,OUTPUT);
	GPIO_enuSetOutputConfig(PORTA,PIN1,Push_Pull,Low_Speed);

	GPIO_enuSetMode(PORTA,PIN0,INPUT);
	GPIO_enuSetInputConfig(PORTA,PIN0,PULLUP);

	EXTI0_voidCallBack(Func1);
	EXTI_enuSetEnabletPort(EXTI_LINE0,EXTI_PORTA);
	EXT_enuSetTrigger(EXTI_LINE0,EXTI_FALLING);
	EXTI_enuEnable(EXTI_LINE0);
	EXTI_enuEnable(6);
	while(1)
	{
		switch(Value)
		{
		case 3:
			GPIO_enuSetPinValue(PORTA,PIN1,HIGH);
			break;
		case 11:
			GPIO_enuSetPinValue(PORTA,PIN1,LOW);
			break;
		}
	}
}

void Func1()
{
	if(GLB_u8StartFlag==0)
	{
		MSTK_voidCtrlIntState(Systick_IntEnable);
		GLB_u8StartFlag=1;
		MSTK_voidCallBackSingle(Func2,15000);
	}
	else
	{
		GLB_u8IRArr[GLB_u8Counter]=(MSTK_u32GetElapsedTickSingleShot()/2);
		GLB_u8Counter++;
		MSTK_voidCallBackSingle(Func2,4000);
	}
}
void Func2()
{
	GLB_u8StartFlag=0;
	GLB_u8Counter=0;
	u8 i;
	for(i=0;i<8;i++)
	{
		if((GLB_u8IRArr[17+i]<=1250) && (GLB_u8IRArr[17+i]>=1000))
		{
			CLR_BIT(Value,i);
		}
		else if((GLB_u8IRArr[17+i]<=2400) && (GLB_u8IRArr[17+i]>=2000))
		{
			SET_BIT(Value,i);
		}
	}
}


