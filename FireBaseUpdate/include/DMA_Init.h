


#ifndef MDMA_INTERFACE_H
#define MDMA_INTERFACE_H

typedef enum{
	Byte=0,
	Half_word,
	Word
}Size_t;

typedef enum{
	FIFO_1_4,
	FIFO_1_2,
	FIFO_3_4,
	FIFO_FULL
}Threshold_t;

void MDMA2_voidInit();
void MDMA2_voidSetStreamConfig(
	u8 Copy_u8StreamId,
	u32*Copu_pu32SourceAddress,
	u32*Copu_pu32DestinationAddress,
	Size_t Copy_uddtSize,
	u16 Copy_u16BlockSize,
	Threshold_t Copy_uddtThershold
);

void MDMA2_voidEnableStream(u8 Copy_u8StreamId);
void MDMA2_voidCallBack(u8 Copy_u8StreamId,void(*Copy_Ptr)(void));


#endif
