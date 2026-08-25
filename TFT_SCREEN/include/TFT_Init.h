/*
 * TFT_Init.h
 *
 *  Created on: Jul 31, 2025
 *      Author: c
 */

#ifndef TFT_INIT_H_
#define TFT_INIT_H_


void TFT_voidInit();

void TFT_voidWriteData(u8 Copy_u8Data);

void TFT_voidwriteCMD(u8 Copy_u8CMD);

void TFT_voidDisplay(const u16*Copy_pu16PTR);


#endif /* TFT_INIT_H_ */
