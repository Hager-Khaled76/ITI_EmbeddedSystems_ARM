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
#include "STK_int.h"


#include "ledM_init.h"



int main()
{
	RCC_enumIntSysClk();

	RCC_enumEnablePeriphral(RCC_AHB1_BUS , AHB1_GPIOA);

	RCC_enumEnablePeriphral(RCC_AHB1_BUS , AHB1_GPIOB);

    STK_enuInit();

    LEDMATRIX_voidInit();

    u8 Local_u8DisplayPattern[8] = {126, 129, 145, 145, 145, 243, 0, 0};

    while (1)
    {
        LEDMATRIX_u8Display(Local_u8DisplayPattern);
    }

    return 0;
}





/*

 const u8 NUM_PATTERNS[10][8] = {
    {60, 66, 66, 66, 66, 66, 60, 0}, // 0
    {16, 48, 16, 16, 16, 16, 16, 0}, // 1
    {60, 66, 4, 8, 16, 32, 126, 0},  // 2
    {60, 66, 2, 12, 2, 66, 60, 0},   // 3
    {8, 24, 40, 72, 126, 8, 8, 0},   // 4
    {126, 64, 64, 60, 2, 66, 60, 0}, // 5
    {60, 64, 64, 60, 66, 66, 60, 0}, // 6
    {126, 2, 4, 8, 16, 32, 64, 0},   // 7
    {60, 66, 66, 60, 66, 66, 60, 0}, // 8
    {60, 66, 66, 62, 2, 2, 60, 0}    // 9
};


int main()
{
    RCC_enumIntSysClk();

    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);

    STK_enuInit();

    LEDMATRIX_voidInit();

    u8 Local_u8CurrentNumber = 0;

    while (1)
    {
        for (Local_u8CurrentNumber = 0; Local_u8CurrentNumber <= 9; Local_u8CurrentNumber++)
        {
            LEDMATRIX_u8Display(NUM_PATTERNS[Local_u8CurrentNumber]);
            STK_delayUs(500000UL);
        }
    }

    return 0;
}




*/

/*

const u8 LETTER_H[8] = {255, 255, 16, 16, 16, 16, 255, 255};
const u8 LETTER_A[8] = {0, 252, 18, 17, 17, 18, 252, 0};
const u8 LETTER_G[8] = {255, 129, 145, 145, 145, 243, 0, 0};
const u8 LETTER_E[8] = {255, 145, 145, 145, 145, 145, 145, 145};
const u8 LETTER_R[8] = {255, 17, 17, 17, 42, 68, 128, 0};

// Total columns for the full "HAGER" -> 5*8=40 +(8+8) to first & end empty
#define TEXT_TOTAL_COLUMNS  56

// Array to store the complete text pattern
u8 HAGER_TEXT_PATTERN[TEXT_TOTAL_COLUMNS];


void prepareTextPattern()
{
    u16 text_idx = 0;
    u8 col_idx = 0;

    // Add leading empty columns at first
    for (col_idx = 0; col_idx < 8; col_idx++) HAGER_TEXT_PATTERN[text_idx++] = 0;

    // Add HAGER letters
    for (col_idx = 0; col_idx < 8; col_idx++) HAGER_TEXT_PATTERN[text_idx++] = LETTER_H[col_idx];
    for (col_idx = 0; col_idx < 8; col_idx++) HAGER_TEXT_PATTERN[text_idx++] = LETTER_A[col_idx];
    for (col_idx = 0; col_idx < 8; col_idx++) HAGER_TEXT_PATTERN[text_idx++] = LETTER_G[col_idx];
    for (col_idx = 0; col_idx < 8; col_idx++) HAGER_TEXT_PATTERN[text_idx++] = LETTER_E[col_idx];
    for (col_idx = 0; col_idx < 8; col_idx++) HAGER_TEXT_PATTERN[text_idx++] = LETTER_R[col_idx];

    // Add trailing empty columns at end
    for (col_idx = 0; col_idx < 8; col_idx++) HAGER_TEXT_PATTERN[text_idx++] = 0;
}


int main()
{
    RCC_enumIntSysClk();

    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);

    STK_enuInit();

    LEDMATRIX_voidInit();

    prepareTextPattern();

    u16 Local_u16ScrollOffset = 0; // Current scroll position

    while (1)
    {
        for (Local_u16ScrollOffset = 0; Local_u16ScrollOffset <= (TEXT_TOTAL_COLUMNS - 8); Local_u16ScrollOffset++)
        {
            // Display 8 columns starting from the current scroll offset
            LEDMATRIX_u8Display(&HAGER_TEXT_PATTERN[Local_u16ScrollOffset]);

            STK_delayUs(50000UL); // delay 50ms
        }
    }

    return 0;
}


*/

