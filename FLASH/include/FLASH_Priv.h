
#ifndef MFMI_PRIVATE_H
#define MFMI_PRIVATE_H

#define FMI_BASE_ADDRESS  (0x40023C00)

typedef struct{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;
}FMI_t;

#define FMI     ((volatile FMI_t*)FMI_BASE_ADDRESS)

#define KEY1    0x45670123UL
#define KEY2    0xCDEF89ABUL

#define BSY   16

#define LOCK  31
#define STRT  16
#define PSIZE 8
#define SNB   3
#define MER   2
#define SER   1
#define PG    0

#define MUSK_SIZE    3
#define MUSK_SECTOR  15

#endif
