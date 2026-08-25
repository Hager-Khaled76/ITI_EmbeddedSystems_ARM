/*
 * STK_prog.c
 *
 *  Created on: Jul 18, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "STK_config.h"
#include "STK_priv.h"
#include "STK_int.h"




/*Global Variable take address**/
void (*STK_CALLBACK)(void);

/*Global Variable ( STK_SINGLE - STK_PERIODIC )**/
static volatile u8 G_u8SetMode;


/* Function to Apply The Clock If AHB or AHB/8   **/
ES_t STK_enuInit()
{
	ES_t localenuErrorState = ES_NOK;

#if STK_CLK_SRC == STK_CLK_AHB
	/* Disable STK interrupt && Set clk source of AHB**/
	//STK->CTRL = 0X00000004;--> 0b0000---0100
    SET_BIT(STK->CTRL , 2);

#elif STK_CLK_SRC == STK_CLK_AHB_8
	STK->CTRL =0;

#endif

	localenuErrorState = ES_OK;

	return localenuErrorState;
}


/* Function take Count or Tick time **/

ES_t STK_enuSetBusyWait(u32 Copy_u32Ticks)
{
	ES_t localenuErrorState = ES_NOK;

	/* 1- Load Value in LOAD REG**/
	STK->LOAD =Copy_u32Ticks;
	///////
	STK->VAL =0;


	/* Start Timer**/
	STK->CTRL |=(1<<0);

	/*Wait The Count Flag**/
	while(GET_BIT(STK->CTRL , 16) == 0);

	/*Stop Timer**/
	STK->CTRL &=~(1<<0);
	STK->LOAD =0;
	STK->VAL =0;


	localenuErrorState = ES_OK;

	return localenuErrorState;

}

/*Function return The Remaining Time To Make ISR Rad Value Reguster*/
ES_t STK_enuGetRemainigTime(void)
{
	ES_t localenuErrorState = ES_NOK;

	localenuErrorState = STK->VAL;

	return localenuErrorState;
}


/*Function return The Elapsed (ÇáÈÇÞí)Time From Stert to Count (Load - Value)*/
ES_t STK_enuGetElapsedTime(void)
{
	ES_t localenuErrorState = ES_NOK;

	localenuErrorState = ((STK->LOAD) - (STK->VAL)) ;

	return localenuErrorState;
}

/*Function Asynchronous Take Tick Time To Count , Then Give Flag And Work one Time
 * (ONE TIME )
 * **/
ES_t STK_enuSetIntervalPeriodic(u32 Copy_u32Tick , void(*Copy_ptr)(void))
{
	ES_t localenuErrorState = ES_NOK;

	/* Load Tick To Load Register */
	STK->LOAD = Copy_u32Tick;

	/*Save CallBack**/
	STK_CALLBACK = Copy_ptr;

	/* Set Mode to Periodic**/
	G_u8SetMode = STK_PERIODIC;

	/* Enable STK Interrupt **/
	SET_BIT(STK->CTRL , 1);

	/*Start Timer**/
	SET_BIT(STK->CTRL,0);

	localenuErrorState = ES_OK;
	return localenuErrorState;
}


/*Function Asynchronous Take Tick Time To Count , Then Give Flag And Work one Time **/
ES_t STK_enuSetInternalSingle(u32 Copy_u32Tick , void(*Copy_ptr)(void))
{
	ES_t localenuErrorState = ES_NOK;

	/* Load Tick To Load Register */
	STK->LOAD = Copy_u32Tick;

	/*Save CallBack**/
	STK_CALLBACK = Copy_ptr;

	/* Set Mode to Periodic**/
	G_u8SetMode = STK_SINGLE;

	/* Enable STK Interrupt **/
	SET_BIT(STK->CTRL , 1);

	/*Start Timer**/
	SET_BIT(STK->CTRL,0);// when start count will jump into --ISR-- (systic_handler)

	localenuErrorState = ES_OK;
	return localenuErrorState;
}

/*Function Will Stop The Interval If it Periodic Or Single**/
ES_t STK_enuStopInterval(void)
{
	ES_t localenuErrorState = ES_NOK;

	/*Disable STK Interrupt**/
	CLR_BIT(STK->CTRL , 1);

	/* Stop Timer**/
	CLR_BIT(STK->CTRL , 0);
	STK->LOAD =0;
	STK->VAL =0;

	localenuErrorState = ES_OK;
	return localenuErrorState;
}

/*--ISR-- **/
ES_t SYSTICK_Handler(void)
{
	ES_t localenuErrorState = ES_NOK;

	if(G_u8SetMode == STK_SINGLE )
	{
		/**Disable STK Interrupt**/
		CLR_BIT(STK->CTRL , 1);

		/*Stop Timer **/
		CLR_BIT(STK->CTRL , 0);
		STK->LOAD =0;
		STK->VAL=0;
	}

	/*cALLBACK NOTIFICATION**/
	STK_CALLBACK();

	/*CLEAR INTRRUPT FLAG -->?? CLEAR BY READING **/
	localenuErrorState = GET_BIT(STK->CTRL , 16);

	return localenuErrorState;

}



ES_t STK_delayUs(u32 Copy_u32MicroSeconds)
{
    ES_t localenuErrorState = ES_NOK;
    u32 Local_u32Ticks;

    #if STK_CLK_SRC == STK_CLK_AHB
        // System Clock (AHB)
        Local_u32Ticks = Copy_u32MicroSeconds * SYSTEM_CLK_MHZ;
    #elif STK_CLK_SRC == STK_CLK_AHB_8
        // System Clock / 8 (AHB/8)
        Local_u32Ticks = Copy_u32MicroSeconds * (SYSTEM_CLK_MHZ / 8UL);
    #else
        #error "STK_CLK_SRC is not defined correctly in STK_config.h"
    #endif

    localenuErrorState = STK_enuSetBusyWait(Local_u32Ticks);

    return localenuErrorState;
}








