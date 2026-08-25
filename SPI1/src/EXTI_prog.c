/*
 * EXTI_prog.c
 *
 *  Created on: Jul 15, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "EXTI_cofig.h"
#include "EXTI_priv.h"
#include "EXTI_int.h"



// Global Var to Call in Func

static void(*Global_PtrEXTI0)(void) = NULL ;


ES_t EXTI_enuSetEnabletPort(EXTI_LINE_t CopyuddLine , EXTI_PORT_t CopyuddPort)
{
	ES_t LocalErrorstate = ES_NOK;
	SYSCFG->EXTICR [CopyuddLine /SYS_DIV] &=~(SYS_MUSK<<((CopyuddLine)%SYS_DIV)*4);
	SYSCFG->EXTICR [CopyuddLine /SYS_DIV] |=(CopyuddPort<<((CopyuddLine)%SYS_DIV)*4);
	LocalErrorstate = ES_OK;

	return LocalErrorstate;

}

ES_t EXTI_enuEnable( EXTI_LINE_t CopyuddLine)
{
	ES_t LocalErrorstate = ES_NOK;

	EXTI->IMR |=(1<<CopyuddLine);

	LocalErrorstate = ES_OK;

	return LocalErrorstate;
}

ES_t EXTI_enuDisable( EXTI_LINE_t CopyuddLine)
{
	ES_t LocalErrorstate = ES_NOK;

	EXTI->IMR &=~(1<<CopyuddLine);

	LocalErrorstate = ES_OK;

	return LocalErrorstate;
}


ES_t EXT_enuSetTrigger(EXTI_LINE_t CopyuddLine , EXTI_Trigger_Mode_t CopyuddMode)
{
	ES_t LocalErrorstate = ES_NOK;

	switch(CopyuddMode)
	{  case EXTI_FALLING:
		EXTI->RTSR &=~(1<<CopyuddLine);
		EXTI->FTSR |=(1<<CopyuddLine);
		break;

	case EXTI_RISING:
		EXTI->RTSR |=(1<<CopyuddLine);
		EXTI->FTSR &=~(1<<CopyuddLine);
		break;

	case EXTI_ONCHANGE:
		EXTI->RTSR |=(1<<CopyuddLine);
		EXTI->FTSR |=(1<<CopyuddLine);
		break;

	default:
		break;

	}
	LocalErrorstate = ES_OK;

	return LocalErrorstate;
}



// Call Back Func
void  EXTI0_voidCallBack(void(*ptr)(void))
{
	Global_PtrEXTI0 = ptr;
}

void EXTI0_IRQHandler()
{
	if(Global_PtrEXTI0 != NULL)
	{
		// clear by software soo
		Global_PtrEXTI0();
		EXTI ->PR |=(1<<0); // clear pending flag && line0 soo one bit(1<<0)
	}
}

/*Software INT**/
void EXTI_vTriggSW(u8 Copy_u8LineNum)
{
	SET_BIT(EXTI->SWIER , Copy_u8LineNum);

}



/* select pin on port **/

void EXTI_vSelectPort(u8 Copy_u8LineNum , u8 Copy_u8PortId)
{
	/* For port from 0 to 3 we have SYSCFG_EXTICR1**/
	if(Copy_u8LineNum<=3)
	{
		/*Make Place =0000       Safty-----**/
		SYSCFG->EXTICR[0] &=~(0b1111<<(4*Copy_u8LineNum));
		/*shift by 4 bit**/
		SYSCFG->EXTICR[0] |=(Copy_u8PortId<<(4*Copy_u8LineNum));
	}

	/* For port from 4 to 7 we have SYSCFG_EXTICR1**/
	if(Copy_u8LineNum<=7)
	{
		/*Map (4,5,6,7) to(0,1,2,3) -----**/
		Copy_u8LineNum-=4;

		/*Make Place =0000       Safty-----**/
		SYSCFG->EXTICR[1] &=~(0b1111<<(4*Copy_u8LineNum));
		/*shift by 4 bit**/
		SYSCFG->EXTICR[1] |=(Copy_u8PortId<<(4*Copy_u8LineNum));
	}

	/* For port from 8 to 11 we have SYSCFG_EXTICR1**/
	else if(Copy_u8LineNum<=11)
	{
		/*Map (8,9,10,11) to(0,1,2,3) -----**/
		Copy_u8LineNum-=8;

		/*Make Place =0000 -----**/
		SYSCFG->EXTICR[2] &=~(0b1111<<(4*Copy_u8LineNum));
		/*shift by 4 bit**/
		SYSCFG->EXTICR[2] |=(Copy_u8PortId<<(4*Copy_u8LineNum));
	}

	else if(Copy_u8LineNum<=15)
	{
		/*Map (12,13,14,15) to(0,1,2,3) -----**/
		Copy_u8LineNum-=12;

		/*Make Place =0000 -----**/
		SYSCFG->EXTICR[3] &=~(0b1111<<(4*Copy_u8LineNum));
		/*shift by 4 bit**/
		SYSCFG->EXTICR[3] |=(Copy_u8PortId<<(4*Copy_u8LineNum));
	}



}
