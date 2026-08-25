/*
 * TFT_Prog.c
 *
 *  Created on: Jul 31, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "GPIO_int.h"
#include "RCC_Int.h"
#include "SPI1_init.h"

#include "TFT_Init.h"
#include "TFT_Config.h"


void TFT_voidInit()
{
	//RESET PIN -> O/P
	GPIO_enuSetMode(TFT_PORT , RST_PIN , OUTPUT);
	GPIO_enuSetOutputConfig(TFT_PORT , RST_PIN ,Push_Pull , Low_Speed);

	// CONTROLE PIN -> O/P
	GPIO_enuSetMode(TFT_PORT , CONTROL_PIN , OUTPUT);
	GPIO_enuSetOutputConfig(TFT_PORT , CONTROL_PIN , Push_Pull , Low_Speed);

	// RESET Sequence
	GPIO_enuSetPinValue(TFT_PORT , RST_PIN , HIGH);
	MSTK_voidDelayus(100);
	GPIO_enuSetPinValue(TFT_PORT , RST_PIN , LOW);
	MSTK_voidDelayus(1);
	GPIO_enuSetPinValue(TFT_PORT , RST_PIN , HIGH);
	MSTK_voidDelayus(100);
	GPIO_enuSetPinValue(TFT_PORT , RST_PIN , LOW);
	MSTK_voidDelayus(100);
	GPIO_enuSetPinValue(TFT_PORT , RST_PIN , HIGH);
	MSTK_voidDelayms(120);

	// Sleep o/p
	TFT_voidwriteCMD(SLEEP_OUT);
	MSTK_voidDelayms(10);
	// Color mode
	TFT_voidwriteCMD(C0LOR_MODE);
	TFT_voidWriteData(RGB565);

	// Display on
	TFT_voidwriteCMD(DISPLAY_ON);



}


void TFT_voidWriteData(u8 Copy_u8Data)
{
	GPIO_enuSetPinValue(TFT_PORT , CONTROL_PIN , HIGH);
	(void)SPI_u16Tranceive(Copy_u8Data);
}


void TFT_voidwriteCMD(u8 Copy_u8CMD)
{
	GPIO_enuSetPinValue(TFT_PORT , CONTROL_PIN , LOW);
	(void)SPI_u16Tranceive(Copy_u8CMD);
}


void TFT_voidDisplay(const u16*Copy_pu16PTR)
{
	u16 Local_u16Iterator ;
	u8 Local_u8HighPart , Local_u8LowPart;

	// Set X
	TFT_voidwriteCMD(X_Direction);
	TFT_voidWriteData(START_X_B0);
	TFT_voidWriteData(START_X_B1);
	TFT_voidWriteData(END_X_B0);
	TFT_voidWriteData(END_X_B1);


	// Set Y
	TFT_voidwriteCMD(Y_Direction);
	TFT_voidWriteData(START_Y_B0);
	TFT_voidWriteData(START_Y_B1);
	TFT_voidWriteData(END_Y_B0);
	TFT_voidWriteData(END_Y_B1);


	// write on screen
	TFT_voidwriteCMD(SCREEN_WRITE);
	for(Local_u16Iterator =0 ; Local_u16Iterator <= IMAGE_SIZE ; Local_u16Iterator++)
	{
		Local_u8LowPart=(u8)Copy_pu16PTR[Local_u16Iterator];
		Local_u8HighPart=(u8)(Copy_pu16PTR[Local_u16Iterator]>>8);
		TFT_voidWriteData(Local_u8HighPart);
		TFT_voidWriteData(Local_u8LowPart);

	}
}
