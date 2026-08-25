/*
 * main.c
 *
 * Created on: Jul 20, 2025
 * Author: C
 * Description: Displays numbers from 00 to 99 on dual 7-segment displays.
 */

#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "STK_int.h"


#define SYS_CLOCK_MHZ   8

const u8 SevenSegmentPatterns_Hex[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F
};

ES_t DisplayDigitOn7Segment(PORT_t Copy_uddtPort, u8 Copy_u8Digit)
{
    ES_t localErrorState = ES_NOK;
    if (Copy_u8Digit <= 9)
    {
        u8 pattern = SevenSegmentPatterns_Hex[Copy_u8Digit];
        for (u8 i = 0; i < 7; i++)
        {
            PinValue_t segment_value = ((pattern >> i) & 0x01) ? HIGH : LOW;
            GPIO_enuSetPinValue(Copy_uddtPort, (PIN_t)(PIN0 + i), segment_value);
        }
        localErrorState = ES_OK;
    }
    else
    {
        localErrorState = ES_OUT_OF_RANGE;
    }
    return localErrorState;
}

int main(void)
{
    // 1. Initialize RCC (System Clock)
    RCC_enumIntSysClk();

    // 2. Initialize SysTick Timer
    STK_enuInit();

    // 3. Enable GPIO Peripheral Clocks for PORTB (Units) and PORTC (Tens)
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOC);

    // 4. Configure 7-segment pins as Output on PORTB (PIN0 to PIN6 for Units)
    for (u8 i = 0; i < 7; i++)
    {
        GPIO_enuSetMode(PORTB, (PIN_t)(PIN0 + i), OUTPUT);
        GPIO_enuSetOutputConfig(PORTB, (PIN_t)(PIN0 + i), Push_Pull, Low_Speed);
    }

    // If you have an enable pin for the units 7-segment, configure it here:
    // GPIO_enuSetMode(PORTB, PIN7, OUTPUT);
    // GPIO_enuSetOutputConfig(PORTB, PIN7, Push_Pull, Low_Speed);
    // GPIO_enuSetPinValue(PORTB, PIN7, HIGH);
    // Assuming common cathode, enable HIGH


    // 5. Configure 7-segment pins as Output on PORTC (PIN0 to PIN6 for Tens)
    for (u8 i = 0; i < 7; i++)
    {
        GPIO_enuSetMode(PORTC, (PIN_t)(PIN0 + i), OUTPUT);
        GPIO_enuSetOutputConfig(PORTC, (PIN_t)(PIN0 + i), Push_Pull, Low_Speed);
    }

    // If you have an enable pin for the tens 7-segment, configure it here:
    // GPIO_enuSetMode(PORTC, PIN7, OUTPUT);
    // GPIO_enuSetOutputConfig(PORTC, PIN7, Push_Pull, Low_Speed);
    // GPIO_enuSetPinValue(PORTC, PIN7, HIGH); // Assuming common cathode, enable HIGH

    while (1)
    {
        // Loop to display numbers from 00 to 99
        for (u8 tens = 0; tens <= 9; tens++)
        {
            for (u8 units = 0; units <= 9; units++)
            {
                // Display tens digit on PORTC 7-segment
                DisplayDigitOn7Segment(PORTC, tens);

                // Display units digit on PORTB 7-segment
                DisplayDigitOn7Segment(PORTB, units);

                // Delay for 200ms
                STK_enuSetBusyWait(SYS_CLOCK_MHZ * 1000 * 200);
            }
        }
    }

    return 0;
}
