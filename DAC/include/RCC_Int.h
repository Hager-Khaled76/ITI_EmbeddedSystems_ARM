


#ifndef RCC_INT_H_
#define RCC_INT_H_

#include "errorStates.h"
#include "stdTypes.h"


#define RCC_AHB1_BUS     0
#define RCC_AHB2_BUS     1

#define RCC_APB1_BUS     2
#define RCC_APB2_BUS     3






ES_t RCC_enumIntSysClk();

ES_t RCC_enumEnablePeriphral(u8 Copy_u8BusId , u8 Copy_u8Periphralid);

ES_t RCC_enumDisablePeriphral(u8 Copy_u8BusId , u8 Copy_u8Periphralid);



ES_t RCC_enuEnableSecuritySystem();

ES_t RCC_enuDisableSecuritySystem();










/*****************AHB1***************/

#define AHB1_GPIOA    0
#define AHB1_GPIOB    1
#define AHB1_GPIOC    2
#define AHB1_DMA1     21
#define AHB1_DMA2     22

/*****************APB1***************/
#define APB1_SPI2     14
#define APB1_SPI3     15
#define APB1_USART2   17
#define APB1_I2C1     21
#define APB1_I2C2     22
#define APB1_I2C3     23

/*****************APB2***************/
#define APB2_USART1   4
#define APB2_USART6   5
#define APB2_SPI1     12




//ES_t RCC_enumDisablePeriphral(u8 Copy_u8BusId , u8 Copy_u8Periphralid);

#endif
