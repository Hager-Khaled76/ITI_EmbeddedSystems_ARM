
#ifndef RCC_PRIV_H_
#define RCC_PRIV_H_


#define RCC_BASE_ADDRES    		(0x40023800)

#define RCC_CR                   (*((volatile u32*)0x40023800))
#define RCC_PLLCFGR              (*((volatile u32*)0x40023804))
#define RCC_CFGR                 (*((volatile u32*)0x40023808))
#define RCC_CIR                  (*((volatile u32*)0x4002380C))
#define RCC_AHB1RSTR             (*((volatile u32*)0x40023810))
#define RCC_AHB2RSTR             (*((volatile u32*)0x40023814))
#define RCC_APB1RSTR             (*((volatile u32*)0x40023820))
#define RCC_APB2RSTR             (*((volatile u32*)0x40023824))
#define RCC_AHB1ENR              (*((volatile u32*)0x40023830))
#define RCC_AHB2ENR              (*((volatile u32*)0x40023834))
#define RCC_APB1ENR              (*((volatile u32*)0x40023840))
#define RCC_APB2ENR              (*((volatile u32*)0x40023844))
#define RCC_AHB1LPEN             (*((volatile u32*)0x40023850))
#define RCC_AHB2LPENR            (*((volatile u32*)0x40023854))
#define RCC_APB1LPENR            (*((volatile u32*)0x40023860))
#define RCC_APB2LPENR            (*((volatile u32*)0x40023864))
#define RCC_BDCR                 (*((volatile u32*)0x40023870))
#define RCC_CSR                  (*((volatile u32*)0x40023874))
#define RCC_SSCGR                (*((volatile u32*)0x40023880))
#define RCC_PLLI2SCFGR           (*((volatile u32*)0x40023884))
#define RCC__DCKCFGR             (*((volatile u32*)0x4002388C))



#define RCC_HSI    0
#define RCC_HSE    1
#define RCC_PLL    2

#define RCC_CR_CLK_RC        0
#define RCC_CR_CLK_CRYSTAL   1


#define RCC_CR_HSION            0
#define RCC_CR_HSIRDY           1
//#define RCC_CR_HSI              2
#define RCC_CR_HSEON            16
#define RCC_CR_HSERDY           17
#define RCC_CR_HSEBYP           18
#define RCC_CR_CSSON            19
#define RCC_CR_PLLON            24
#define RCC_CR_PLLRDY           25
#define RCC_CR_PLLI2SON         26
#define RCC_CR_PLLI2SRDY        27




#define MUSK    3
#define SW0     0

// PLL related bits in RCC_CFGR
#define PLLSRC_BIT              16  // PLL Entry Clock Source bit (0=HSI/2, 1=HSE)
#define PLLXTPRE_BIT            17  // HSE Divider for PLL Entry bit (0=HSE not div, 1=HSE/2)

#define PLLMUL_POS              18  // Starting bit position for PLL Multiplication Factor (4 bits)
#define PLLMUL_MASK             (0xF << PLLMUL_POS) // Mask for PLL Multiplication Factor (0b1111 shifted)


#define RCC_PLL_SRC_HSI_DIV2    0
#define RCC_PLL_SRC_HSE         1

//HSE is INPUT TO PLL
#define RCC_PLL_HSE_NO_DIV      0
#define RCC_PLL_HSE_DIV2        1

#define RCC_PLL_MUL_X2          (0x0 << PLLMUL_POS) //*2
#define RCC_PLL_MUL_X3          (0x1 << PLLMUL_POS) //*3
#define RCC_PLL_MUL_X4          (0x2 << PLLMUL_POS) //*4
#define RCC_PLL_MUL_X5          (0x3 << PLLMUL_POS) //*5
#define RCC_PLL_MUL_X6          (0x4 << PLLMUL_POS) //*6
#define RCC_PLL_MUL_X7          (0x5 << PLLMUL_POS) //*7
#define RCC_PLL_MUL_X8          (0x6 << PLLMUL_POS) //*8
#define RCC_PLL_MUL_X9          (0x7 << PLLMUL_POS) //*9   if 8M will be 72MHZ
#define RCC_PLL_MUL_X10         (0x8 << PLLMUL_POS) //*10
#define RCC_PLL_MUL_X11         (0x9 << PLLMUL_POS) //*11
#define RCC_PLL_MUL_X12         (0xA << PLLMUL_POS) //*12
#define RCC_PLL_MUL_X13         (0xB << PLLMUL_POS) //*13
#define RCC_PLL_MUL_X14         (0xC << PLLMUL_POS) //*14
#define RCC_PLL_MUL_X15         (0xD << PLLMUL_POS) //*15
#define RCC_PLL_MUL_X16         (0xE << PLLMUL_POS) //*16


#endif/*< end RCC_PRIV_H_ **/


