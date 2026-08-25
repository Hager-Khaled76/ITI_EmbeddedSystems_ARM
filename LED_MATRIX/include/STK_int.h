/*
 * STK_INT.H
 *
 *  Created on: Jul 18, 2025
 *      Author: c
 */

#ifndef STK_INT_H_
#define STK_INT_H_




#define STK_SINGLE    0
#define STK_PERIODIC  1


#define STK_CLK_AHB       0
#define STK_CLK_AHB_8     1

/* Function to Apply The Clock If AHB or AHB/8   **/
ES_t STK_enuInit();

ES_t ST_enuSetBusyWait(u32 Copy_u32Ticks);

ES_t STK_enuGetRemainigTime(void);

ES_t STK_enuGetElapsedTime(void);

ES_t STK_enuSetIntervalPeriodic(u32 Copy_u32Tick , void(*Copy_ptr)(void));

ES_t STK_enuSetInternalSingle(u32 Copy_u32Tick , void(*Copy_ptr)(void));

ES_t STK_enuStopInterval(void);

ES_t SYSTICK_Handler(void);

ES_t STK_delayUs(u32 Copy_u32MicroSeconds);


#endif /* STK_INT_H_ */
