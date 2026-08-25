/*
 * NVIC_priv.h
 *
 *  Created on: Jul 14, 2025
 *      Author: c
 */

#ifndef NVIC_PRIV_H_
#define NVIC_PRIV_H_


#define NVIC_BASEREG       0XE000E100

typedef struct
{
	u32 ISER[8];
	u32 RESERVED0[24];
	u32 ICER[8];
	u32 RESERVED1[24];
	u32 ISPR[8];
	u32 RESERVED2[24];
	u32 ICPR[8];
	u32 RESERVED3[24];
	u32 IABR[8];
	u32 RESERVED4[65];
	u8 IPR[240];
	u32 RESERVED5[580];
	u32 STIR;
}NVIC_t;


#define NVIC     ((volatile NVIC_t*)NVIC_BASEREG)


#endif /* NVIC_PRIV_H_ */
