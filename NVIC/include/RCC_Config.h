

//AI

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/*
 * Choose RCC System Clock from:
 * RCC_HSE
 * RCC_HSI
 * RCC_PLL
 * **/\


#define RCC_SYSCLK     RCC_HSI

/*
 * if choosen  RCC_HSE select what do you want :
 * RCC_CR_CLK_RC
 * RCC_CR_CLK_CRYSTAL
 * **/\
#if  RCC_SYSCLK == RCC_HSE
#define RCC_CR_CLK_BYPASS         RCC_CR_CLK_CRYSTAL // ** „ «· ⁄œÌ· Â‰«: ﬂ«‰  RCC_CR_CLK_RC**
#endif /*< end RCC_SYSCLK**/


#if RCC_SYSCLK == RCC_PLL
/*choose  PLL:
 *RCC_PLL_SRC_HSI_DIV2, RCC_PLL_SRC_HSE
 */
#define RCC_PLL_SOURCE              RCC_PLL_SRC_HSE
/*
 * if choosen  RCC_PLL_SRC_HSE
 *RCC_PLL_HSE_NO_DIV, RCC_PLL_HSE_DIV2
 */
#define RCC_PLL_HSE_PREDIV          RCC_PLL_HSE_NO_DIV

#define RCC_PLL_MUL                 RCC_PLL_MUL_X9
#endif

#endif/*RCC_CONFIG_H_*/
