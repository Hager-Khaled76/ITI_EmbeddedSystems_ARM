/*
 * OS_prog.c
 *
 *  Created on: Jul 19, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"


#include "STK_int.h"

#include "OS_config.h"
#include "OS_priv.h"
#include "OS_int.h"


ES_t OS_enuCreateTask(u8 Copy_u8Periority , u32 Copy_u8Periodicity ,u8 Copy_u8FirstDelay, void (* Copy_pf)(void))
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_pf !=NULL)
	{
		if(Copy_u8Periority < NUM_OF_TASKS)
		{
			OS_Task[Copy_u8Periority].Periodicity = Copy_u8Periodicity;
			OS_Task[Copy_u8Periority].FirstDelay = Copy_u8FirstDelay;
			OS_Task[Copy_u8Periority].pf = Copy_pf;

			Local_enuErrorState = ES_OK;
		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState ;

}



ES_t OS_enuStertScheduler()
{
	ES_t Local_enuErrorState =ES_NOK;

	/*Init STK**/
	STK_enuInit();

	/*Run a schedular each 1 ms**/
	//STK_enuSetIntervalPeriodic(TICK_TIME_us ,OS_Scheduler);

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState ;

}

static u8 TickCount = 0;
static void OS_Scheduler(void)
{
	for (u8 Count =0 ; Count < NUM_OF_TASKS ; Count++)
	{
		if((TickCount % OS_Task[Count].Periodicity) ==0)
		{
			OS_Task[Count].pf();
		}
	}
	TickCount++;
	TickCount*=1000;
	}
