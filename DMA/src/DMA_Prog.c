



#include "BIT_MATH.h"
#include "stdTypes.h"

#include "RCC_Int.h"
#include "DMA_Priv.h"
#include "DMA_Config.h"
#include "DMA_Init.h"

static void (*GLB_PTR[8])(void);

void MDMA2_voidInit()
{
	// Memory increment
	SET_BIT(DMA2->S[0].CR, MINC_BIT);

	// pheripheral increment
	SET_BIT(DMA2->S[0].CR, PINC_BIT);

	// Enbale Transfer interrupt
	SET_BIT(DMA2->S[0].CR, 4);

	// Set memory to memory mode (DIR bits 6 and 7)
	SET_BIT(DMA2->S[0].CR, 7);
	CLR_BIT(DMA2->S[0].CR, 6);
}

void MDMA2_voidSetStreamConfig(
	u8 Copy_u8StreamId,
	u32*Copu_pu32SourceAddress,
	u32*Copu_pu32DestinationAddress,
	Size_t Copy_uddtSize,
	u16 Copy_u16BlockSize,
	Threshold_t Copy_uddtThershold
)
{
	// Set sourec address
	DMA2->S[Copy_u8StreamId].PAR = (u32)Copu_pu32SourceAddress;

	// Set destination address
	DMA2->S[Copy_u8StreamId].M0AR = (u32)Copu_pu32DestinationAddress;

	// clear pervious data size (memory)
	DMA2->S[Copy_u8StreamId].CR &= ~ (0b11 << MSIZE_BIT);

	// Set memory size
	DMA2->S[Copy_u8StreamId].CR |= (Copy_uddtSize << MSIZE_BIT);

	// clear pervious data size (peripheral)
	DMA2->S[Copy_u8StreamId].CR &= ~ (0b11 << PSIZE_BIT);

	// set peripheral size
	DMA2->S[Copy_u8StreamId].CR |= (Copy_uddtSize << PSIZE_BIT);

	// Set the number of data iteams to transfer
	DMA2->S[Copy_u8StreamId].NDTR = Copy_u16BlockSize;

	// Clear pervious thershold
	DMA2->S[Copy_u8StreamId].FCR &= ~(0b11 << 0);

	// Set new thershold
	DMA2->S[Copy_u8StreamId].FCR |= (Copy_uddtThershold << 0);

}

void MDMA2_voidEnableStream(u8 Copy_u8StreamId)
{
	// Set enable bit for the specified stream
	SET_BIT(DMA2->S[Copy_u8StreamId].CR, EN_BIT);
}

void MDMA2_voidCallBack(u8 Copy_u8StreamId,void(*Copy_Ptr)(void))
{
	// store the registered call back function for stream (n)=0
	GLB_PTR[Copy_u8StreamId] = Copy_Ptr;
}

void DMA2_Stream0_IRQHandler()
{
	// call function
	if (GLB_PTR[0] != NULL)
	{
		GLB_PTR[0]();
	}

	// clear the interrupt flag for stream 0
	SET_BIT(DMA2->LIFCR, 5); // TCIF flag
}
