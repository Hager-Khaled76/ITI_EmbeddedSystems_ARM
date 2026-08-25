/*
 * EXTI_priv.h
 *
 *  Created on: Jul 15, 2025
 *      Author: c
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_



#define SYSTCKCFG_BASE_ADRESSES     0X40013800
#define EXTI_BASE_ADRESSES          0X40013C00

//==================================
typedef struct
{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];//==========================================
	u32 RESERVED[2];//=========================================
	u32 CMPCR;

}SYSCFG_t;

typedef struct
{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}EXTI_t;

#define SYSCFG    ((volatile SYSCFG_t *)SYSTCKCFG_BASE_ADRESSES)
#define EXTI      ((volatile EXTI_t *)EXTI_BASE_ADRESSES)


#define SYSCFG_EXTICR1      (*(volatile u32 *)SYSTCKCFG_BASE_ADRESSES+0X08)
#define SYSCFG_EXTICR2      (*(volatile u32 *)SYSTCKCFG_BASE_ADRESSES+0X0C)
#define SYSCFG_EXTICR3      (*(volatile u32 *)SYSTCKCFG_BASE_ADRESSES+0X10)
#define SYSCFG_EXTICR4      (*(volatile u32 *)SYSTCKCFG_BASE_ADRESSES+0X14)


#define SYS_DIV     4

#define SYS_MUSK    15

#define NULL       (void *)0

#endif /* EXTI_PRIV_H_ */
