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
#include "STK_int.h"
#include "GPIO_int.h"

#define SYS_CLOCK_MHZ   8 // Assuming 8MHz System Clock for STK calculations

int main(void)
{
    // 1. Initialize RCC (System Clock)
    RCC_enumIntSysClk();

    // 2. Initialize SysTick Timer
    STK_enuInit(); // Initialize SysTick (e.g., set clock source)

    // 3. Enable GPIOA Peripheral Clock
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);

    // 4. Configure LED Pin as Output
    GPIO_enuSetMode(PORTA, PIN0, OUTPUT);
    GPIO_enuSetOutputConfig(PORTA, PIN0, Push_Pull, Low_Speed);

    while (1)
    {
        // Turn LED ON
        GPIO_enuSetPinValue(PORTA, PIN0, HIGH);
        // Calculate ticks for 500ms delay: (8,000,000 Hz / 1000) * 500ms = 8000 * 500 = 4,000,000 ticks
        STK_enuSetBusyWait(SYS_CLOCK_MHZ * 1000 * 500); // Delay for 500ms (0.5 seconds)

        // Turn LED OFF
        GPIO_enuSetPinValue(PORTA, PIN0, LOW);
        STK_enuSetBusyWait(SYS_CLOCK_MHZ * 1000 * 500); // Delay for 500ms (0.5 seconds)
    }

    return 0;
}


