#include "stdTypes.h"
#include "BIT_MATH.h"

#include "FLASH_Priv.h"
#include "FLASH_init.h"


void MFMI_voidMassErase()
{
	//waith busy flag
	while(GET_BIT(FMI->SR,BSY)==1);
	//Unlock CR register
	if(GET_BIT(FMI->CR,LOCK)==1)
	{
		FMI->KEYR=KEY1;
		FMI->KEYR=KEY2;
	}
	//Select mass erase
	FMI->CR=(1<<MER);
	//Start operation
	FMI->CR=(1<<STRT);
	//wait on busy flag
	while(GET_BIT(FMI->SR,BSY)==1);
	//disable mass erase
	FMI->CR&=~(1<<MER);
}
void MFMI_voidSectorErase(Sector_t Copy_uddtSectorNumber)
{
		//waith busy flag
	while(GET_BIT(FMI->SR,BSY)==1);
	//Unlock CR register
	if(GET_BIT(FMI->CR,LOCK)==1)
	{
		FMI->KEYR=KEY1;
		FMI->KEYR=KEY2;
	}
	//Select sector number
	FMI->CR &=(MUSK_SECTOR<<SNB);
	FMI->CR |=(Copy_uddtSectorNumber<<SNB);

	//Select Sector erase
	FMI->CR=(1<<SER);
	//Start operation
	FMI->CR=(1<<STRT);
	//wait on busy flag
	while(GET_BIT(FMI->SR,BSY)==1);
	//disable s erase
	FMI->CR&=~(1<<SER);
}
void MFMI_voidMultSectorErase(Sector_t Copy_uddtSectorStart,Sector_t Copy_uddtSectorEnd)
{
	u8 Local_u8Iterator=0;
	for(Local_u8Iterator=Copy_uddtSectorStart;Local_u8Iterator<=Copy_uddtSectorEnd;Local_u8Iterator++)
	{
		MFMI_voidSectorErase(Local_u8Iterator);
	}
}
void MFMI_voidProgramFlash(u32 Copy_u32Address,u16*Copy_pu16PTR,u8 Copy_u8DataLength)
{
	//waih busy flag
	while(GET_BIT(FMI->SR,BSY)==1);
	//Unlock CR register
	if(GET_BIT(FMI->CR,LOCK)==1)
	{
		FMI->KEYR=KEY1;
		FMI->KEYR=KEY2;
	}
	//Select width to be programmed
	FMI->CR&=~(MUSK_SIZE<<PSIZE);
	FMI->CR|=~(1<<PSIZE);

	for(u8 Local_u8Iterator=0;Local_u8Iterator<Copy_u8DataLength;Local_u8Iterator++)
	{
		//select program mode
		FMI->CR|=(1<<PG);

		*((volatile u16*)Copy_u32Address)=Copy_pu16PTR[Local_u8Iterator];
		Copy_u32Address+=2;

		//wait busy flag
	    while(GET_BIT(FMI->SR,BSY)==1);

		//clear program mode
		FMI->CR&=~(1<<PG);
	}

}
