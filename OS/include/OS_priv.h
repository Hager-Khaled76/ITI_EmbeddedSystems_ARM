/*
 * OS_priv.h
 *
 *  Created on: Jul 19, 2025
 *      Author: c
 */

#ifndef OS_PRIV_H_
#define OS_PRIV_H_


typedef enum{
	Redy,
	Running,
	Wating
};


typedef struct {
	//u8 Periority;
	u16 Periodicity;
	u8 FirstDelay;
	void (*pf)(void);

}TCB_t ;

static TCB_t OS_Task[NUM_OF_TASKS];



#endif /* OS_PRIV_H_ */
