/*
 * main.c
 *
 *  Created on: Aug 5, 2025
 *      Author: c
 */


#include "stdTypes.h"
#include "RCC_Int.h"
#include "FLASH_init.h"

int main(){

	RCC_enumIntSysClk();

	u16 arr[3] ={0x33,0x45,0x12};

	//MFMI_voidMassErase();

	MFMI_voidProgramFlash(0x08008000,arr,3);
	while(1)
	{

	}
}

