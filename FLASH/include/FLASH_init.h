/*
 * FLASH_init.h
 *
 *  Created on: Aug 5, 2025
 *      Author: c
 */

#ifndef FLASH_INIT_H_
#define FLASH_INIT_H_

typedef enum{
	Sector0,
	Sector1,
	Sector2,
	Sector3,
	Sector4,
	Sector5
}Sector_t;

void MFMI_voidMassErase();
void MFMI_voidSectorErase(Sector_t Copy_uddtSectorNumber);
void MFMI_voidMultSectorErase(Sector_t Copy_uddtSectorStart,Sector_t Copy_uddtSectorEnd);
void MFMI_voidProgramFlash(u32 Copy_u32Address,u16*Copy_pu16PTR,u8 Copy_u8DataLength);


#endif /* FLASH_INIT_H_ */
