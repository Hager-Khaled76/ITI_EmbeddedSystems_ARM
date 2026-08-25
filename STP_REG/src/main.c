/*
 * main.c
 *
 *  Created on: Aug 3, 2025
 *      Author: !?
 */

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "STP_init.h"
#include "MSTK_Interface.h"

int main(void)
{
	RCC_enumIntSysClk();
	RCC_enumEnablePeriphral(RCC_AHB1_BUS , AHB1_GPIOA);
	MSTK_voidInit();
    STP_voidInit();



    while(1)
    {
        // Send 0x00
        STP_voidShiftData(0x00);
        STP_voidSendData();
        MSTK_voidDelayms(1000);

        // Send 0x0F
        STP_voidShiftData(0x0F);
        STP_voidSendData();
        MSTK_voidDelayms(1000);

        // Send 0xF0
        STP_voidShiftData(0xF0);
        STP_voidSendData();
        MSTK_voidDelayms(1000);

        // Send 0xFF
        STP_voidShiftData(0xFF);
        STP_voidSendData();
        MSTK_voidDelayms(1000);


    }




/*

    while(1)
       {
           //  Display the pattern 0x0F
           STP_voidShiftData(0x0F);
           STP_voidSendData();
           MSTK_voidDelayms(1000);

          //  Turn OFF all LEDs
           STP_voidShiftData(0x00);
           STP_voidSendData();
           MSTK_voidDelayms(500);

           //  Display the pattern 0xF0
           STP_voidShiftData(0xF0);
           STP_voidSendData();
           MSTK_voidDelayms(1000);

           // Turn OFF all LEDs
           STP_voidShiftData(0x00);
           STP_voidSendData();
           MSTK_voidDelayms(500);

           //  Display the pattern 0xFF
           STP_voidShiftData(0xFF);
           STP_voidSendData();
           MSTK_voidDelayms(1000);

           //  Turn OFF all LEDs
           STP_voidShiftData(0x00);
           STP_voidSendData();
           MSTK_voidDelayms(500);


       }
       */


    return 0;
}

