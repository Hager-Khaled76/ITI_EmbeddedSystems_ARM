/*
 * STP_Prog.c
 *
 *  Created on: Aug 3, 2025
 *      Author: c
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "MSTK_Interface.h"
#include "STP_init.h"
#include "STP_Config.h"



/*** user include begin *****/
/**
 * @brief  Initializes the GPIO pins and clock for the Serial to Parallel converter.
 * @param  None
 * @retval None
 */
void STP_voidInit()
{
    RCC_enumIntSysClk(); // Initialize the system clock
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA); // Enable clock for GPIOA

    MSTK_voidInit();

    /* Define STP_u8_SDI_PIN as o/p*/
    GPIO_enuSetMode(STP_u8_SDI_PORT, STP_u8_SDI_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(STP_u8_SDI_PORT, STP_u8_SDI_PIN, Push_Pull, Low_Speed);

    /* Define STP_u8_SHIFT_PIN as o/p*/
    GPIO_enuSetMode(STP_u8_SHIFT_PORT, STP_u8_SHIFT_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(STP_u8_SHIFT_PORT, STP_u8_SHIFT_PIN, Push_Pull, Low_Speed);

    /* Define STP_u8_LATCH_PIN as o/p*/
    GPIO_enuSetMode(STP_u8_LATCH_PORT, STP_u8_LATCH_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(STP_u8_LATCH_PORT, STP_u8_LATCH_PIN, Push_Pull, Low_Speed);

    /*  LATCH and SHIFT pins are initially low */
    GPIO_enuSetPinValue(STP_u8_LATCH_PORT, STP_u8_LATCH_PIN, LOW);
    GPIO_enuSetPinValue(STP_u8_SHIFT_PORT, STP_u8_SHIFT_PIN, LOW);
}
/*** user include end *****/




/*** user include begin *****/
/**
 * @brief  Shifts 8 bits of data serially into the shift register.
 * @param  Copy_u8Data: The 8-bit data to be shifted.
 * @retval None
 */
void STP_voidShiftData(u8 Copy_u8Data)
{
    // Loop through each of the 8 bits, from MSB  to LSB
    for(s8 i = 7; i >= 0; i--)
    {
        /* Get bit from data */
        PinValue_t Local_uddtBitValue = (GET_BIT(Copy_u8Data, i) == 1) ? HIGH : LOW;
        GPIO_enuSetPinValue(STP_u8_SDI_PORT, STP_u8_SDI_PIN, Local_uddtBitValue);

        /* Send pulse on STP_u8_SHIFT_PIN */ // -> rising edge
        GPIO_enuSetPinValue(STP_u8_SHIFT_PORT, STP_u8_SHIFT_PIN, LOW);
        /** Delay */
        MSTK_voidDelayms(10);

        /* Set STP_u8_SHIFT_PIN low */
        GPIO_enuSetPinValue(STP_u8_SHIFT_PORT, STP_u8_SHIFT_PIN, HIGH);
    }
}
/*** user include end *****/




/*** user include begin *****/
/**
 * @brief  Sends a pulse to the latch pin to transfer the shifted data to the parallel output.
 * @param  None
 * @retval None
 */
void STP_voidSendData()
{
    /* Set STP_u8_LATCH_PIN LOW */
    GPIO_enuSetPinValue(STP_u8_LATCH_PORT, STP_u8_LATCH_PIN, LOW);

    /* Delay 10 ms */
    MSTK_voidDelayms(10);

    /* Set STP_u8_LATCH_PIN HIGH */
    GPIO_enuSetPinValue(STP_u8_LATCH_PORT, STP_u8_LATCH_PIN, HIGH);
}
/*** user include end *****/


























