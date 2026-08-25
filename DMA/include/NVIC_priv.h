

#ifndef NVIC_PRIV_H_
#define NVIC_PRIV_H_



typedef    u8                         _IRQn_Type;

#define NVIC_ISER0 					  (*((volatile u32 *)0xE000E100))/*< INTERRUPT SET-ENABLE REGISTER FROM 0 to 32**/
#define NVIC_ISER1                    (*((volatile u32 *)0xE000E104))/*< INTERRUPT SET-ENABLE REGISTER FROM 32 to 63**/
#define NVIC_ISER2                    (*((volatile u32 *)0xE000E108))/*< INTERRUPT SET-ENABLE REGISTER FROM 63 to 95**/
																	 
#define NVIC_ICER0                    (*((volatile u32 *)0xE000E180))/*< INTERRUPT CLEAR-ENABLE REGISTER FROM  0 to 32**/
#define NVIC_ICER1                    (*((volatile u32 *)0xE000E184))/*< INTERRUPT CLEAR-ENABLE REGISTER FROM  32 to 63**/
#define NVIC_ICER2                    (*((volatile u32 *)0xE000E188))/*< INTERRUPT CLEAR-ENABLE REGISTER FROM  63 to 95**/
																	
#define NVIC_ISPR0                    (*((volatile u32 *)0xE000E200))/*< INTERRUPT SET-PENDING REGISTER FROM  0 to 32**/
#define NVIC_ISPR1                    (*((volatile u32 *)0xE000E204))/*< INTERRUPT SET-PENDING REGISTER FROM  32 to 63**/
#define NVIC_ISPR2                    (*((volatile u32 *)0xE000E208))/*< INTERRUPT SET-PENDING REGISTER FROM  63 to 95**/
																	 
#define NVIC_ICPR0                    (*((volatile u32 *)0xE000E280))/*< INTERRUPT CLEAR-PENDING REGISTER FROM  0 to 32**/
#define NVIC_ICPR1                    (*((volatile u32 *)0xE000E284))/*< INTERRUPT CLEAR-PENDING REGISTER FROM  32 to 63**/
#define NVIC_ICPR2                    (*((volatile u32 *)0xE000E288))/*< INTERRUPT CLEAR-PENDING REGISTER FROM  63 to 95**/
																
#define NVIC_IABR0                    (*((volatile u32 *)0xE000ED0C))/*< INTERRUPT ACTIVE BIT REGISTER FROM  0 to 32**/
//#define NVIC_IABR1                    (*((volatile u32 *)0xE000ED0C+0x))/*< INTERRUPT ACTIVE BIT REGISTER FROM  32 to 63**/
//#define NVIC_IABR2                    (*((volatile u32 *)0xE000ED0C+0X))/*< INTERRUPT ACTIVE BIT REGISTER FROM  63 to 95**/

                                       /* < 0xE000E100 + 300 **/
#define NVIC_IPR_BASE_ADDRESSES       (((volatile u8 *)0xE000E400)) //Array step size 8 bit // u8 to be sstep by 8bit && not * to access manual to step or shift by 8 bit


#define _16_GROUP_0_SUB_PRIORITY      0x05FA0300
#define _8_GROUP_2_SUB_PRIORITY       0x05FA0400
#define _4_GROUP_4_SUB_PRIORITY       0x05FA0500
#define _2_GROUP_8_SUB_PRIORITY       0x05FA0600
#define _0_GROUP_16_SUB_PRIORITY      0x05FA0700


#define SCB_AICR                       (*((volatile u8*)0xE000ED0C))

 

#endif
