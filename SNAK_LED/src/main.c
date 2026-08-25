/*
 * main.c
 *
 *  Created on: Jul 20, 2025
 *      Author: c
 */


#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "STK_int.h"

#define SYS_CLOCK_MHZ   8 // Assuming 8MHz System Clock for STK calculations

int main(void)
{
    // 1. Initialize RCC (System Clock)
    RCC_enumIntSysClk();

    // 2. Initialize SysTick Timer
    STK_enuInit(); // Initialize SysTick (e.g., set clock source)

    // 3. Enable GPIOA Peripheral Clock
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);

    // 4. Configure 7 LED Pins as Output (PIN0 to PIN6 on PORTA)
    for (PIN_t pin = PIN0; pin <= PIN6; pin++)
    {
        GPIO_enuSetMode(PORTA, pin, OUTPUT);
        GPIO_enuSetOutputConfig(PORTA, pin, Push_Pull, Low_Speed);
        GPIO_enuSetPinValue(PORTA, pin, LOW); // Ensure all are off initially
    }

    while (1)
    {
        // Forward Snake Effect
        for (PIN_t pin = PIN0; pin <= PIN6; pin++)
        {
            GPIO_enuSetPinValue(PORTA, pin, HIGH); // Turn on current LED
            STK_enuSetBusyWait(SYS_CLOCK_MHZ * 1000 * 100); // Delay for 100ms
            GPIO_enuSetPinValue(PORTA, pin, LOW);  // Turn off current LED
        }

        // Backward Snake Effect (optional, for a complete snake loop)
        for (PIN_t pin = PIN6; pin >= PIN0; pin--)
        {
            GPIO_enuSetPinValue(PORTA, pin, HIGH); // Turn on current LED
            STK_enuSetBusyWait(SYS_CLOCK_MHZ * 1000 * 100); // Delay for 100ms
            GPIO_enuSetPinValue(PORTA, pin, LOW);  // Turn off current LED
        }
    }

    return 0;
}


