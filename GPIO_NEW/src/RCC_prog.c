/*
 * RCC_Prog.c
 *
 *  Created on: Jul 9, 2025
 *      Author: !?
 */

#include "stdTypes.h"
#include "BIT_MATH.h"

#include "errorStates.h"

#include "RCC_Int.h"
#include "RCC_Config.h"
#include "RCC_Priv.h"

ES_t RCC_enumIntSysClk()
{

	CLR_BIT(RCC_CR , RCC_CR_HSEBYP);/*< choose Crystal as a System Clock**/

	/*< Enable HSE**/
	SET_BIT(RCC_CR , RCC_CR_HSEON);

	/*< wait untill CLK stable**/
	while((GET_BIT(RCC_CR , RCC_CR_HSERDY)==0));

	/*< Select External CLK to be SYSCLK**/
	RCC_CFGR &=~(3<<0);
	RCC_CFGR |=(1<<0);
	//SET_BIT(RCC_CFGR , 0);


}

ES_t RCC_enumDisablePeriphral(u8 Copy_u8BusId , u8 Copy_u8Periphralid)
{
	ES_t LocalenumErrorState = ES_NOK;
	if(Copy_u8Periphralid <32)
	{
		switch(Copy_u8BusId)
		{
		case RCC_AHB1_BUS :
			CLR_BIT(RCC_AHB1ENR , Copy_u8Periphralid);
			break;

		case RCC_AHB2_BUS:
			CLR_BIT(RCC_AHB2ENR , Copy_u8Periphralid);
			break;

		case RCC_APB1_BUS :
			CLR_BIT(RCC_APB1ENR , Copy_u8Periphralid);
			break;

		case RCC_APB2_BUS:
			CLR_BIT(RCC_APB2ENR , Copy_u8Periphralid);
			break;
		}
		LocalenumErrorState = ES_OK;
	}
	else
	{
		LocalenumErrorState = ES_OUT_OF_RANGE;
	}

	return LocalenumErrorState;
}
