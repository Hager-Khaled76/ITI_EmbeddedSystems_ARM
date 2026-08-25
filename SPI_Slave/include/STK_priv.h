/*
 * STK_priv.h
 *
 *  Created on: Jul 18, 2025
 *      Author: c
 */

#ifndef STK_PRIV_H_
#define STK_PRIV_H_

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}STK_t;

#define SYSTIC_BASE_ADRESSES      0xE000E010

#define STK      ((STK_t *)SYSTIC_BASE_ADRESSES)

#define STK_CLK_AHB       0
#define STK_CLK_AHB_8     1

#define STK_SINGLE    0
#define STK_PERIODIC  1



#endif /* STK_PRIV_H_ */
