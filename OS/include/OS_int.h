/*
 * OS_int.h
 *
 *  Created on: Jul 19, 2025
 *      Author: c
 */

#ifndef OS_INT_H_
#define OS_INT_H_


ES_t OS_enuCreateTask(u8 Copy_u8Periority , u32 Copy_u8Periodicity ,u8 Copy_u8FirstDelay, void (* Copy_pf)(void));
ES_t OS_enuStertScheduler();

#endif /* OS_INT_H_ */
