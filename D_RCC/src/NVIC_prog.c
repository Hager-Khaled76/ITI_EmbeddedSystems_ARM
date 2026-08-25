/*
 * NVIC_prog.c
 *
 *  Created on: Jul 14, 2025
 *      Author: c
 */


#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "NVIC_config.h"
#include "NVIC_priv.h"
#include "NVIC_int.h"


ES_t NVIC_enuSetEnable(u8 Copy_u8Position)
{
	ES_t LocalEnumErrorState = ES_NOK;

	NVIC ->ISER[Copy_u8Position/32] |=(1<<(Copy_u8Position % 32));

	LocalEnumErrorState = ES_OK;
	return LocalEnumErrorState;
}

ES_t NVIC_enuDisable(u8 Copy_u8Position)
{
	ES_t LocalEnumErrorState = ES_NOK;

	NVIC ->ICER[Copy_u8Position/32] |=(1<<(Copy_u8Position % 32));

	LocalEnumErrorState = ES_OK;

	return LocalEnumErrorState;
}

ES_t NVIC_enuEnablePendidngFlag(u8 Copy_u8Position)
{
	ES_t LocalEnumErrorState = ES_NOK;

	NVIC ->ISPR[Copy_u8Position/32] |=(1<<(Copy_u8Position % 32));

	LocalEnumErrorState = ES_OK;

	return LocalEnumErrorState;
}

ES_t NVIC_enuDisablePendidngFlag(u8 Copy_u8Position)
{
	ES_t LocalEnumErrorState = ES_NOK;

	NVIC ->ICPR[Copy_u8Position/32] |=(1<<(Copy_u8Position % 32));

	LocalEnumErrorState =ES_OK;

	return LocalEnumErrorState;
}

ES_t NVIC_enuGetActiveFlag(u8 Copy_u8Position , u8 *Copy_pu8Value)
{
	ES_t LocalEnumErrorState = ES_NOK;

	*Copy_pu8Value = GET_BIT(NVIC->IABR[Copy_u8Position/32] ,(Copy_u8Position % 32));

	LocalEnumErrorState = ES_OK;

	return LocalEnumErrorState;
}
