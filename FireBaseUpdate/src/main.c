/*
 * main.c
 *
 * This file contains the main firmware for the STM32 microcontroller.
 * It's responsible for managing the LED Matrix display, controlling two LEDs,
 * and handling the DMA data transfer to simulate firmware update.
 *
 * Created on: Jul 29, 2025
 * Author: c
 */

#include "stdTypes.h"
#include "BIT_MATH.h"
#include "RCC_Int.h"
#include "GPIO_int.h"
#include "NVIC_int.h"
#include "DMA_Init.h"
#include "MSTK_Interface.h"
#include "LEDM_init.h"


/*

// Define the pins for the two normal LEDs
#define LED1_PORT PORTA
#define LED1_PIN  PIN1 // Pin A1
#define LED2_PORT PORTA
#define LED2_PIN  PIN2 // Pin A2

// Character patterns for the LED Matrix display
// The patterns are in decimal format and include leading/trailing spaces for scrolling

u8 LOADING_PATTERN[] = {
    // Leading Spaces
    0, 0, 0, 0, 0, 0, 0, 0,
    // L
	0, 127, 64, 64, 64, 64, 0, 0,
    // O
	0, 62, 65, 65, 65, 65, 62, 0,
    // A
	0, 240, 30, 17, 17, 30, 240, 0,
    // D
	0, 127, 65, 65, 65, 62, 0, 0,
    // I
	0, 65, 65, 127, 127, 65, 65, 0,
    // N
	127, 2, 4, 8, 16, 32, 127, 0,
	// G
	0, 62, 65, 73, 73, 73, 58, 0,
    // Trailing Spaces
    0, 0, 0, 0, 0, 0, 0, 0
};

u8 DONE_PATTERN[] = {
    // Leading Spaces
    0, 0, 0, 0, 0, 0, 0, 0,
    // D
	0, 127, 65, 65, 65, 62, 0, 0,
    // O
	0, 62, 65, 65, 65, 65, 62, 0,
    // N
	127, 2, 4, 8, 16, 32, 127, 0,
    // E
	0, 62, 73, 73, 73, 73, 73, 0,
	// Trailing Spaces
    0, 0, 0, 0, 0, 0, 0, 0
};

// DMA Callback function declaration
void FuncTest();

// DMA arrays for data transfer simulation
u32 arr1[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 33, 21, 22, 99};
u32 arr2[15] = {0};

int main()
{
    // 1. Initialize the system clock
    RCC_enumIntSysClk();

    // 2. Enable clock for GPIOA and GPIOB
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);

    // 3. Initialize SysTick Timer (required for LED Matrix refresh)
    MSTK_voidInit();

    // 4. Initialize the LED Matrix
    LEDMATRIX_voidInit();

    // 5. Configure the normal LED pins as outputs
    GPIO_enuSetMode(LED1_PORT, LED1_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(LED1_PORT, LED1_PIN, Push_Pull, Low_Speed);
    GPIO_enuSetPinValue(LED1_PORT, LED1_PIN, LOW); // Turn off LED initially

    GPIO_enuSetMode(LED2_PORT, LED2_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(LED2_PORT, LED2_PIN, Push_Pull, Low_Speed);
    GPIO_enuSetPinValue(LED2_PORT, LED2_PIN, LOW); // Turn off LED initially

    // 6. Enable clock for DMA2
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_DMA2);

    // 7. Enable the interrupt for DMA2 Stream 0 in NVIC
    NVIC__EnableIRQ(56); // 56 is the interrupt number for DMA2 Stream 0

    // 8. Initialize the DMA2
    MDMA2_voidInit();

    // 9. Configure the DMA2 Stream 0 settings
    MDMA2_voidSetStreamConfig(
        0,          // Stream ID
        arr1,       // Source Address
        arr2,       // Destination Address
        Word,       // Data Size (Word = 32-bit)
        15,         // Block Size (number of data items)
        FIFO_FULL   // FIFO Threshold
    );

    // 10. Set the DMA callback function
    MDMA2_voidCallBack(0, FuncTest);

    // 11. Display "Loading" on the LED Matrix while the DMA transfer is in progress
    u16 scrollOffset_Loading = 0;
    u32 loopCounter_Loading = 0;
    const u32 SCROLL_SPEED_Loading = 15;

    // 12. Start the DMA transfer
    MDMA2_voidEnableStream(0);

    // The main loop
    while (1)
    {
        // Display "Loading" on the LED Matrix
        // This part will run until the DMA transfer completes and the interrupt is triggered
        LEDMATRIX_u8Display(&LOADING_PATTERN[scrollOffset_Loading]);

        loopCounter_Loading++;
        if (loopCounter_Loading >= SCROLL_SPEED_Loading)
        {
            loopCounter_Loading = 0;
            scrollOffset_Loading++;
            if (scrollOffset_Loading > (sizeof(LOADING_PATTERN) - 8))
            {
                scrollOffset_Loading = 0;
            }
        }
    }
}

// This callback function is called when the DMA transfer is complete
void FuncTest()
{
    // Turn on the two normal LEDs to indicate the transfer is complete
    GPIO_enuSetPinValue(LED1_PORT, LED1_PIN, HIGH);
    GPIO_enuSetPinValue(LED2_PORT, LED2_PIN, HIGH);

    // Display "Done" on the LED Matrix
    u16 scrollOffset_Done = 0;
    u32 loopCounter_Done = 0;
    const u32 SCROLL_SPEED_Done = 15;

    // Display "Done" for a fixed number of loops
    for (int i = 0; i < 500; i++)
    {
        LEDMATRIX_u8Display(&DONE_PATTERN[scrollOffset_Done]);
        MSTK_voidDelayms(5);

        loopCounter_Done++;
        if (loopCounter_Done >= SCROLL_SPEED_Done)
        {
            loopCounter_Done = 0;
            scrollOffset_Done++;
            if (scrollOffset_Done > (sizeof(DONE_PATTERN) - 8))
            {
                scrollOffset_Done = 0;
            }
        }
    }
}


*/







/*

// Define LED pins
#define LED1_PORT PORTA
#define LED1_PIN  PIN0

#define LED2_PORT PORTA
#define LED2_PIN  PIN1

// Simulate update complete callback
void FuncTest();

int main()
{
    // 1. Initialize system clock
    RCC_enumIntSysClk();

    // 2. Enable GPIOA clock
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);

    // 3. Set LED pins as output
    GPIO_enuSetMode(LED1_PORT, LED1_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(LED1_PORT, LED1_PIN, Push_Pull, Low_Speed);
    GPIO_enuSetPinValue(LED1_PORT, LED1_PIN, HIGH);

    GPIO_enuSetMode(LED2_PORT, LED2_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(LED2_PORT, LED2_PIN, Push_Pull, Low_Speed);
    GPIO_enuSetPinValue(LED2_PORT, LED2_PIN, HIGH);

    // Simulate update trigger (replace with UART or other event)
    FuncTest();

    // Main loop
    while (1)
    {
        // Do nothing, waiting for future triggers
    }
}

// This function is called when update is triggered
void FuncTest()
{
    // Toggle LED1
    u8 led1_val;
    GPIO_enuGetPinValue(LED1_PORT, LED1_PIN, &led1_val);
    GPIO_enuSetPinValue(LED1_PORT, LED1_PIN, !led1_val);

    // Toggle LED2
    u8 led2_val;
    GPIO_enuGetPinValue(LED2_PORT, LED2_PIN, &led2_val);
    GPIO_enuSetPinValue(LED2_PORT, LED2_PIN, !led2_val);
}

*/

