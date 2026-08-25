
#ifndef MGPIO_PRIVATE_H
#define MGPIO_PRIVATE_H


#define GPIOA_BASE_ADRESSES     (0x40020000)
#define GPIOB_BASE_ADRESSES     (0x40020400)
#define GPIOC_BASE_ADRESSES     (0x40020800)


typedef struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDER;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
    u32 LCKR;
	u32 AFRL;
	u32 AFRH;

}GPIO_t;


#define GPIOA    ((volatile GPIO_t*)GPIOA_BASE_ADRESSES)
#define GPIOB    ((volatile GPIO_t*)GPIOB_BASE_ADRESSES)
#define GPIOC    ((volatile GPIO_t*)GPIOC_BASE_ADRESSES)

#define MUSK       3/*< 0x11**/
#define ALF_MUSK   15/*< 0x11111**/

#endif
