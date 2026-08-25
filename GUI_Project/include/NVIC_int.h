/*
 * NVIC_int.h
 *
 *  Created on: Jul 14, 2025
 *      Author: c
 */

#ifndef NVIC_INT_H_
#define NVIC_INT_H_


ES_t NVIC_enuSetEnable(u8 Copy_u8Position);

ES_t NVIC_enuDisable(u8 Copy_u8Position);

ES_t NVIC_enuEnablePendidngFlag(u8 Copy_u8Position);

ES_t NVIC_enuDisablePendidngFlag(u8 Copy_u8Position);

ES_t NVIC_enuGetActiveFlag(u8 Copy_u8Position , u8 *Copy_pu8Value);

ES_t NVIC_enuGroupMode(u8 Copyu8GroupMode);

ES_t NVIC_enuSetPeriority(u8 Copy_u8Periority , u8 Copy_u8Pariphral , u8 Copy_u8SubGroup);

#endif /* NVIC_INT_H_ */
