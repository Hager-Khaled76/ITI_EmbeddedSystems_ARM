#include "BIT_MATH.h"
#include "stdTypes.h".h"

#include "MUART_Interface.h"
#include "MUART_Private.h"
#include "MUART_Config.h"


void MUART_voidInit()
{
	//oversample -->16
	UART1->CR1.OVER8=0;

	//Baud Rate -->9600 bit rate
	UART1->BRR=(104<<4)|(3);

	//data length -->8 data
	UART1->CR1.M=0;

	//disable parity
	UART1->CR1.PCE=0;

	//transmit enable
	UART1->CR1.TE=1;

	//receive enable
	UART1->CR1.RE=1;

	//uart enable
	UART1->CR1.UE=1;
}
void MUART_voidSendData(u8 Copy_u8Data)
{
	while(!GET_BIT(UART1->SR,TXE));
	UART1->DR=Copy_u8Data;
}
u8 MUART_u8ReceiveData()
{
	while(GET_BIT(UART1->SR,RXE)==0);
	return ((u8)UART1->DR);
}

void MUART_voidSendString(u8 *Copy_u8Data)
{
	u8 i=0;
	while(Copy_u8Data[i]!='\0')
	{
		MUART_voidSendData(Copy_u8Data[i]);
		i++;
	}
}
