/*
 * main.c
 *
 *  Created on: Jul 29, 2025
 *      Author: c
 */




#include "stdTypes.h"
#include "errorStates.h"

#include "RCC_Int.h"
#include "GPIO_int.h"
#include "MSTK_Interface.h"

#include "ledM_init.h"


/*
 *
 //Character 'G'
int main()
{
	RCC_enumIntSysClk();

	RCC_enumEnablePeriphral(RCC_AHB1_BUS , AHB1_GPIOA);

	RCC_enumEnablePeriphral(RCC_AHB1_BUS , AHB1_GPIOB);

	MSTK_voidInit();

    LEDMATRIX_voidInit();

    u8 Local_u8DisplayPattern[8] = {126, 129, 145, 145, 145, 243, 0, 0};

    while (1)
    {
        LEDMATRIX_u8Display(Local_u8DisplayPattern);
    }

    return 0;
}


*/





/*
 *
// count from 0 to 9
u8 arr[10][8]={
			{0, 0, 126, 66, 66, 126, 0, 0},
			{0, 0, 68, 66, 127, 64, 64, 0},
			{0, 0, 121, 73, 73, 79, 0, 0},
			{0, 0, 73, 73, 73, 127, 0, 0},
			{0, 0, 24, 20, 18, 126, 16, 0},
			{0, 0, 0, 79, 73, 121, 0, 0},
			{0, 0, 124, 84, 84, 116, 0, 0},
			{0, 0, 6, 2, 18, 126, 16, 0},
			{0, 0, 254, 146, 146, 254, 0, 0},
			{0, 0, 78, 74, 74, 126, 0, 0}
	};


int main()
{
    RCC_enumIntSysClk();

    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);

    MSTK_voidInit();

    LEDMATRIX_voidInit();

    u8 Local_u8CurrentNumber = 0;

    u32 Local_u32LoopCounter = 0;
    const u32 DISPLAY_SPEED_FACTOR = 50; // Adjust for speed. Higher value = slower count.

       while (1)
       {
           LEDMATRIX_u8Display(arr[Local_u8CurrentNumber]);

           Local_u32LoopCounter++;

           if (Local_u32LoopCounter >= DISPLAY_SPEED_FACTOR)
           {
               Local_u32LoopCounter = 0;
               Local_u8CurrentNumber++;
               if (Local_u8CurrentNumber > 9)
               {
                   Local_u8CurrentNumber = 0;
               }
           }
       }

}


*/








u8 HAGER_SCROLL_PATTERN[61] = {
		 // Leading Spaces (8 columns for text to scroll in)
		    0, 0, 0, 0, 0, 0, 0, 0,

		    // H Pattern (8 columns) + 1 Space
			255, 16, 16, 16, 16, 16, 255, 0, // H pattern
		    0, // Space after H

		    // A Pattern (8 columns) + 1 Space
			254, 17, 17, 17, 17, 17, 254, 0,       // A
		    0, // Space after A

		    // G Pattern (8 columns) + 1 Space
			126, 129, 145, 145, 145, 243, 0, 0,        // G
		    0, // Space after G

		    // E Pattern (8 columns) + 1 Space
			126, 145, 145, 145, 145, 129, 0, 0, // E
		    0, // Space after E

		    // R Pattern (8 columns) + 1 Space
			255, 9, 25, 37, 69, 130, 0, 0, // R
		    0, // Space after R
			0, 36, 0, 66, 36, 24, 0, 0,
			0,// Space

		    // Trailing Spaces (8 columns for text to scroll out)
		    0, 0, 0, 0, 0, 0, 0, 0
		};

int main()
{
    RCC_enumIntSysClk();

    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);

    MSTK_voidInit();

    LEDMATRIX_voidInit();

    u16 scrollOffset = 0;      // Current starting column for display (0 to 61-8)
    u32 loopCounter = 0;       // Counter to control scrolling speed
    const u32 SCROLL_SPEED = 15; // Adjust speed: Higher value = slower scroll

    while (1)
    {
        // Display 8 columns starting from 'scrollOffset'
        LEDMATRIX_u8Display(&HAGER_SCROLL_PATTERN[scrollOffset]);

        loopCounter++;

        if (loopCounter >= SCROLL_SPEED)
        {
            loopCounter = 0;   // Reset counter
            scrollOffset++;    // Move to the next column in the pattern

            // If text has scrolled completely off-screen, reset to start
            if (scrollOffset > (sizeof(HAGER_SCROLL_PATTERN) - 8))
            {
                scrollOffset = 0; // Loop back to the beginning
            }
        }
    }
}



