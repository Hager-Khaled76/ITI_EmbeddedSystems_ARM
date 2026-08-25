
#ifndef  MDMA_PRIVATE_H
#define  MDMA_PRIVATE_H

#define MDMA1_BASE_ADDRESS  (0x40026000)
#define MDMA2_BASE_ADDRESS  (0x40026400)

typedef struct{
	u32 CR;
	u32 NDTR;
	u32 PAR;
	u32 M0AR;
	u32 M1AR;
	u32 FCR;
}DMA_Stram_t;

typedef struct{
	u32 LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;
	DMA_Stram_t S[8];
}DMA_t;


#define DMA1    ((volatile DMA_t*)MDMA1_BASE_ADDRESS)
#define DMA2    ((volatile DMA_t*)MDMA2_BASE_ADDRESS)



#define EN_BIT      0
#define DIR_BIT     6
#define MINC_BIT    10
#define PINC_BIT    9
#define PSIZE_BIT   11
#define MSIZE_BIT   13
#define TCIF_BIT    5


#endif
