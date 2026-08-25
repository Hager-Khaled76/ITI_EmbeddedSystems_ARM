/*
 * RCC_Prog.c
 *
 *  Created on: Jul 9, 2025
 *      Author: !?
 */

#include "stdTypes.h"
#include "BIT_MATH.h"

#include "errorStates.h"

#include "RCC_Priv.h"
#include "RCC_Int.h"
#include "RCC_Config.h"

ES_t RCC_enumIntSysClk()
{
	ES_t LocalenumErrorState = ES_NOK;
    /**********HSE**************/
    #if RCC_SYSCLK == RCC_HSE
        #if  RCC_CR_CLK_BYPASS <=RCC_CR_CLK_CRYSTAL

	    /*sellect which Exeternal Clk will be entered to the system*/
             #if RCC_CR_CLK_BYPASS == RCC_CR_CLK_RC
	             SET_BIT(RCC_CR ,RCC_CR_HSEBYP);/*< choose RC as a System clock**/
	             LocalenumErrorState = ES_OK;

	         #elif RCC_CR_CLK_BYPASS == RCC_CR_CLK_CRYSTAL
	             CLR_BIT(RCC_CR , RCC_CR_HSEBYP);/*< choose Crystal as a System Clock**/
	             LocalenumErrorState = ES_OK;
 	         #endif
        #else
	         LocalenumErrorState = ES_OUT_OF_RANGE;
        #endif

	   /*< Enable HSE**/
	   SET_BIT(RCC_CR , RCC_CR_HSEON);

	   /*< wait untill CLK stable**/
       while(!(GET_BIT(RCC_CR , RCC_CR_HSERDY)));

       /*< Select External CLK to be SYSCLK**/
       RCC_CFGR =0x0001;
       LocalenumErrorState = ES_OK;
   /**************HSI****************/
   #elif RCC_SYSCLK == RCC_CR_HSI
       /*< Enable HSI**/
       SET_BIT(RCC_CR , RCC_CR_HSION);

       /*< wait Untill CLK stable**/
       while(!GET_BIT(RCC_CR , RCC_CR_HSIRDY));

       /*< Select External CLK to be SYSCLK**/
       CLR_BIT(RCC_CFGR,0);
       CLR_BIT(RCC_CFGR,1);
      // RCC_CFGR =0x0000;
       LocalenumErrorState = ES_OK;

   /***************PLL***********************/
   #elif RCC_SYSCLK == RCC_PLL


        CLR_BIT(RCC_CFGR, PLLSRC_BIT);
        CLR_BIT(RCC_CFGR, PLLXTPRE_BIT);

        RCC_CFGR &= ~(1<<PLLMUL_MASK);

        // PLL (HSI/2 or HSE)
        #if RCC_PLL_SOURCE == RCC_PLL_SRC_HSI_DIV2
            CLR_BIT(RCC_CFGR, PLLSRC_BIT);
            LocalenumErrorState = ES_OK;

        #elif RCC_PLL_SOURCE == RCC_PLL_SRC_HSE
            SET_BIT(RCC_CFGR, PLLSRC_BIT);
            LocalenumErrorState = ES_OK;

            // if input HSE
            #if RCC_PLL_HSE_PREDIV == RCC_PLL_HSE_DIV2
                SET_BIT(RCC_CFGR, PLLXTPRE_BIT);
                LocalenumErrorState = ES_OK;
            #elif RCC_PLL_HSE_PREDIV == RCC_PLL_HSE_NO_DIV
                CLR_BIT(RCC_CFGR, PLLXTPRE_BIT);
                LocalenumErrorState = ES_OK;
            #else
                LocalenumErrorState = ES_OUT_OF_RANGE;
            #endif
        #else
            LocalenumErrorState = ES_OUT_OF_RANGE;
        #endif



        RCC_CFGR |= RCC_PLL_MUL;
        LocalenumErrorState = ES_OK;

        //Enable PLL
        SET_BIT(RCC_CR, RCC_CR_PLLON);

        while(!(GET_BIT(RCC_CR, RCC_CR_PLLRDY)));


        CLR_BIT(RCC_CFGR, SYSCLK_SW_POS);
        CLR_BIT(RCC_CFGR, SYSCLK_SW_POS + 1); // sw0,sw1

        SET_BIT(RCC_CFGR, SYSCLK_SW_POS + 1); // sw0,sw1
        LocalenumErrorState = ES_OK;

   #else

        LocalenumErrorState = ES_NOK;
#endif

	   return LocalenumErrorState;
}


ES_t RCC_enumEnablePeriphral(u8 Copy_u8BusId , u8 Copy_u8Periphralid)
{
	ES_t LocalenumErrorState = ES_NOK;

	if(Copy_u8Periphralid <32)
	{
		switch(Copy_u8BusId)
		{
		   case RCC_AHB1_BUS :
			   SET_BIT(RCC_AHB1ENR , Copy_u8Periphralid);
		   break;

		   case RCC_AHB2_BUS:
			   SET_BIT(RCC_AHB2ENR , Copy_u8Periphralid);
		   break;

		   case RCC_APB1_BUS :
			   SET_BIT(RCC_APB1ENR , Copy_u8Periphralid);
		   break;

		   case RCC_APB2_BUS:
			   SET_BIT(RCC_APB2ENR , Copy_u8Periphralid);
		   break;
		}
		LocalenumErrorState = ES_NOK;
	}
	else
	{
		LocalenumErrorState = ES_OUT_OF_RANGE;
	}


	return LocalenumErrorState;
}

ES_t RCC_enumDisablePeriphral(u8 Copy_u8BusId , u8 Copy_u8Periphralid)
{
	ES_t LocalenumErrorState = ES_NOK;
	if(Copy_u8Periphralid <32)
	{
		switch(Copy_u8BusId)
		{
		   case RCC_AHB1_BUS :
			   CLR_BIT(RCC_AHB1ENR , Copy_u8Periphralid);
		   break;

		   case RCC_AHB2_BUS:
			   CLR_BIT(RCC_AHB2ENR , Copy_u8Periphralid);
		   break;

		   case RCC_APB1_BUS :
			   CLR_BIT(RCC_APB1ENR , Copy_u8Periphralid);
		   break;

		   case RCC_APB2_BUS:
			   CLR_BIT(RCC_APB2ENR , Copy_u8Periphralid);
		   break;
		}
		LocalenumErrorState = ES_NOK;
	}
	else
	{
		LocalenumErrorState = ES_OUT_OF_RANGE;
	}

	return LocalenumErrorState;
}

ES_t RCC_enuEnableSecuritySystem()
{
	SET_BIT(RCC_CR , RCC_CR_CSSON);
}

ES_t RCC_enuDisableSecuritySystem()
{
	CLR_BIT(RCC_CR , RCC_CR_CSSON);
}
