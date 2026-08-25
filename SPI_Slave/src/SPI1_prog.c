/*
 * SPI_prog.c
 *
 *  Created on: Jul 30, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "BIT_MATH.h"
#include "errorStates.h"

#include "SPI1_Priv.h"
#include "SPI1_init.h"

void SPI1_voidMasterInit()
{
	SPI1->CR1 |=(1<<SSM);
	SPI1->CR1 |=(1<<SSI);

	SPI1->CR1 |=(1<<MSTR);
	SPI1->CR1 |=(1<<CPOL);

	SPI1->CR1 |=(1<<SPE);

}

void SPI1_voidSlaveInit()
{
	SPI1->CR1 &=~(1<<MSTR);
	SPI1->CR1 |=(1<<CPOL);

	SPI1->CR1 |=(1<<SPE);

}

u16 SPI_u16Tranceive(u16 Copy_u16Data)
{
	while(!GET_BIT(SPI1->SR,TXE));
	SPI1->DR = Copy_u16Data;

	while(!GET_BIT(SPI1->SR , RXNE));
	return (u16)(SPI1->DR);

}


