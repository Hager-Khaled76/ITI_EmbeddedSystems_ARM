/*
 * EXTI_int.h
 *
 *  Created on: Jul 15, 2025
 *      Author: c
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_



typedef enum{
	EXTI_LINE0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINEI14,
	EXTI_LINE15

}EXTI_LINE_t;



typedef enum{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC

}EXTI_PORT_t;


typedef enum{
	EXTI_FALLING,
	EXTI_RISING,
	EXTI_ONCHANGE
}EXTI_Trigger_Mode_t;



//ES_t EXTI_enuInt();

ES_t EXTI_enuSetEnabletPort(EXTI_LINE_t CopyuddLine , EXTI_PORT_t CopyuddPort);

ES_t EXTI_enuEnable( EXTI_LINE_t CopyuddLine);

ES_t EXTI_enuDisable( EXTI_LINE_t CopyuddLine);

ES_t EXT_enuSetTrigger(EXTI_LINE_t CopyuddLine , EXTI_Trigger_Mode_t CopyuddMode);

void  EXTI0_voidCallBack(void(*ptr)(void));

void EXTI_vTriggSW(u8 Copy_u8LineNum);

void EXTI_vSelectPort(u8 Copy_u8LineNum , u8 Copy_u8PortId);

#endif /* EXTI_INT_H_ */
