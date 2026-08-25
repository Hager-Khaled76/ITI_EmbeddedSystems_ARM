#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"


#include "RCC_Int.h"
#include "GPIO_int.h"
#include "NVIC_int.h"
#include "EXTI_int.h"


#include "arr1.h"
#include "arr2.h"
#include "sample.h"

// --- Timer 2 Register Definitions (Simplified) ---
// These are direct register accesses for STM32F401 TIM2
//  MUST ensure these addresses and bit definitions match your specific MCU datasheet
// or use official SPL/HAL headers if available in your project setup.
#define TIM2_BASE_ADDRESS   (0x40000000UL)


typedef struct
{
  volatile u32 CR1;
  volatile u32 CR2;
  volatile u32 SMCR;
  volatile u32 DIER;
  volatile u32 SR;
  volatile u32 EGR;
  volatile u32 CCMR1;
  volatile u32 CCMR2;
  volatile u32 CCER;
  volatile u32 CNT;
  volatile u32 PSC;
  volatile u32 ARR;
  volatile u32 RCR;
  volatile u32 CCR1;
  volatile u32 CCR2;
  volatile u32 CCR3;
  volatile u32 CCR4;
  volatile u32 BDTR;
  volatile u32 DCR;
  volatile u32 DMAR;
  volatile u32 DMAR2; // Added based on common TIM register maps
  volatile u32 OR;
} TIM_TypeDef;

#define TIM2                ((volatile TIM_TypeDef *)TIM2_BASE_ADDRESS)

// TIM_CR1 bits
#define TIM_CR1_CEN     (1UL << 0)   // Counter enable

// TIM_SR bits
#define TIM_SR_UIF      (1UL << 0)   // Update interrupt flag


// --- Pin Definitions for Buttons and R-2R DAC ---
#define BUTTON_TOGGLE_PORT  PORTA
#define BUTTON_TOGGLE_PIN   PIN0 // PA0 for Toggle Play/Pause

// R-2R DAC Pins (8-bit on PORTB)
#define R2R_DAC_PORT        PORTB
#define R2R_DAC_START_PIN   PIN0 // PB0 is LSB, PB7 is MSB


// --- Audio Playback Control Variables ---
volatile u8 is_playing = 0;
volatile u32 current_audio_index = 0;
const unsigned char* current_audio_buffer = NULL;
u32 current_audio_length = 0;


void setup_system(void);
void play_audio(const unsigned char* audio_data, u32 data_length);
void stop_audio(void);
void delay_ms(u32 ms);
void R2R_DAC_Write(u8 data); // New function to write to R-2R DAC



// --- Button ISR Callbacks (Will be called by EXTI IRQ Handlers) ---
void ButtonToggle_ISR(void);
//  ButtonFirst_ISR and ButtonLast_ISR won't be used with EXTI callbacks
// unless EXTI driver is modified to support EXTI_LINE1 and EXTI_LINE2.


// --- Main Function ---
int main(void)
{
    setup_system();

    // Set initial audio to arr1, but paused
    current_audio_buffer = arr1_raw;
    current_audio_length = arr1_raw_len;

    while (1)
    {

    }
}


void setup_system(void)
{
    // 1. Clock Setup using RCC driver
    RCC_enumIntSysClk(); // Initialize System Clock (from RCC_Config.h, likely HSI)

    // Enable clocks for necessary peripherals
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);  // GPIOA for button
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);  // GPIOB for R-2R DAC
    RCC_enumEnablePeriphral(RCC_APB1_BUS, 0);           // TIM2 peripheral (P_ID 0 on APB1)
    RCC_enumEnablePeriphral(RCC_APB2_BUS, 14);          // SYSCFG (for EXTI, P_ID 14 on APB2)

    // 2. GPIO Setup using GPIO driver
    // Button PA0 as Input with Pull-up
    GPIO_enuSetMode(PORTA, PIN0, INPUT);
    GPIO_enuSetInputConfig(PORTA, PIN0, PULLUP);

    // R-2R DAC Pins (PB0-PB7) as Output
    for (u8 i = 0; i < 8; i++)
    {
        GPIO_enuSetMode(PORTB, PIN0+i, OUTPUT);
        // Set output type and speed if needed, for R-2R Push-Pull Low Speed is usually fine
        GPIO_enuSetOutputConfig(PORTB, PIN0+i, Push_Pull,Low_Speed);
    }

    // 3. Timer 2 Setup for 16kHz DAC Trigger (direct register access)
    //  APB1 clock = 16MHz (common for STM32F401 if HSI is used without PLL).
    // For 16MHz APB1 and 16kHz Sample Rate: ARR = (16,000,000 / 16,000) - 1 = 1000 - 1 = 999

    TIM2->PSC = 0;   // No prescaling (clock / 1)
    TIM2->ARR = 999; // Auto-Reload Register for 16kHz (with 16MHz APB1)

    // Enable Timer 2 counter
    TIM2->CR1 |= TIM_CR1_CEN;


    // 4. Button PA0 Interrupt Setup using EXTI and NVIC drivers
    // Configure EXTI for PA0 on falling edge
    EXTI_enuSetEnabletPort(EXTI_LINE0, EXTI_PORTA); // PA0 for EXTI Line 0
    EXTI_enuEnable(EXTI_LINE0); // Enable EXTI Line 0 interrupt
    EXT_enuSetTrigger(EXTI_LINE0, EXTI_FALLING); // Trigger on falling edge
    // Assign callback for EXTI Line 0 (PA0) using the specific function in your EXTI_prog.c
    EXTI0_voidCallBack(ButtonToggle_ISR);

    // Enable NVIC interrupts for EXTI Line 0 and TIM2
    NVIC_enuSetEnable(6);    // EXTI0_IRQn
    NVIC_enuSetEnable(28);   // TIM2_IRQn (Check your STM32F401 datasheet for correct IRQ numbers!)
}

// --- R-2R DAC Write Function ---
// This function takes an 8-bit data and sets the corresponding GPIO pins
void R2R_DAC_Write(u8 data)
{
    for (u8 i = 0; i < 8; i++)
    {
        if (GET_BIT(data, i))
        {
            GPIO_enuSetPinValue(R2R_DAC_PORT, R2R_DAC_START_PIN + i, HIGH);
        }
        else
        {
            GPIO_enuSetPinValue(R2R_DAC_PORT, R2R_DAC_START_PIN + i, LOW);
        }
    }
}

void play_audio(const unsigned char* audio_data, u32 data_length)
{
    stop_audio(); // Ensure previous playback is stopped

    current_audio_buffer = audio_data;
    current_audio_length = data_length;
    current_audio_index = 0;
    is_playing = 1; // Start playing

    // Timer is already enabled and generating interrupts
    // The TIM2_IRQHandler will handle feeding data to R-2R DAC
}

void stop_audio(void)
{
    is_playing = 0;
    current_audio_index = 0; // Reset index for next play
    R2R_DAC_Write(0x80); // Write mid-value (128) to DAC to silence output for 8-bit unsigned
}

// Simple blocking delay for debouncing
void delay_ms(u32 ms)
{
    // This is a crude blocking delay. Adjust the loop count for your CPU clock speed.
    // For a 16MHz clock, ~1600 iterations is roughly 1ms.
    for (u32 i = 0; i < ms * 1600; i++); // Adjusted for 16MHz HSI clock
}


// --- Interrupt Service Routines (ISRs) Callbacks ---

void ButtonToggle_ISR(void)
{
    delay_ms(50); // Debounce
    u8 pin_state;
    GPIO_enuGetPinValue(BUTTON_TOGGLE_PORT, BUTTON_TOGGLE_PIN, &pin_state);

    if (pin_state == LOW) // Confirm button is still pressed
    {
        if (is_playing)
        {
            stop_audio();
        }
        else
        {
            // If no specific audio selected yet, default to arr1_raw
            if (current_audio_buffer == NULL)
            {
                current_audio_buffer = arr1_raw;
                current_audio_length = arr1_raw_len;
            }
            play_audio(current_audio_buffer, current_audio_length);
        }
    }
}

// Timer 2 Interrupt Handler
// This function needs to be linked to the TIM2_IRQHandler vector in your startup file.
void TIM2_IRQHandler(void)
{
    // Check if the Update Interrupt Flag is set
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF; // Clear the flag by writing 0 to it

        if (is_playing && current_audio_buffer != NULL && current_audio_index < current_audio_length)
        {
            // Write the current audio sample to the R-2R DAC
            R2R_DAC_Write(current_audio_buffer[current_audio_index]);
            current_audio_index++;
        }
        else if (is_playing && current_audio_index >= current_audio_length)
        {
            // Audio finished playing
            stop_audio();
        }
    }
}
