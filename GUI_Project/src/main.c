/*
 * main.c
 *
 *  Created on: Jul 23, 2025
 *      Author: c
 */
#include "stdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"


#include "MUART_Interface.h"
#include "RCC_Int.h"
#include "GPIO_int.h"
#include "NVIC_int.h"
#include "EXTI_int.h"

#include "arr1.h"
#include "arr2.h"
// #include "sample.h"

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
  volatile u32 DMAR2;
  volatile u32 OR;
} TIM_TypeDef;

#define TIM2                ((volatile TIM_TypeDef *)TIM2_BASE_ADDRESS)

// TIM_CR1 bits
#define TIM_CR1_CEN     (1UL << 0)   // Counter enable

// TIM_SR bits
#define TIM_SR_UIF      (1UL << 0)   // Update interrupt flag


// --- Buttons ---
#define BUTTON_TOGGLE_PORT  PORTA
#define BUTTON_TOGGLE_PIN   PIN0 // PA0 for Toggle Play/Pause

// R-2R DAC Pins (8-bit on PORTB)
#define R2R_DAC_PORT        PORTB
#define R2R_DAC_START_PIN   PIN0 // PB0 is LSB, PB7 is MSB


#define LED1_PORT           PORTC
#define LED1_PIN            PIN13

#define SEGMENT_PORT        PORTA
#define SEG_A_PIN           PIN1
#define SEG_B_PIN           PIN2
#define SEG_C_PIN           PIN3
#define SEG_D_PIN           PIN4
#define SEG_E_PIN           PIN5
#define SEG_F_PIN           PIN6
#define SEG_G_PIN           PIN7

// UART1 Pins
#define UART1_TX_PORT       PORTA
#define UART1_TX_PIN        PIN9
#define UART1_RX_PORT       PORTA
#define UART1_RX_PIN        PIN10

// --- Timer 3 for 7-Segment Counter ---
#define TIM3_BASE_ADDRESS   (0x40000400UL)
#define TIM3                ((volatile TIM_TypeDef *)TIM3_BASE_ADDRESS)



volatile u8 is_playing = 0;
volatile u32 current_audio_index = 0;
const unsigned char* current_audio_buffer = NULL;
u32 current_audio_length = 0;

// --- 7-Segment Counter Control Variables ---
volatile u8 seven_segment_counter_enabled = 0;
volatile u8 seven_segment_current_digit = 0;

// 7-segment common anode
// Each array element represents a digit (0 to 9)
// LOW = segment ON, HIGH = segment OFF for common anode
const u8 seven_segment_patterns[10] = {

	0b00100000, // 0
    0b10111101, // 1
    0b01001000, // 2
    0b01100000, // 3
    0b10011010, // 4
    0b01000100, // 5
    0b00000100, // 6
    0b11110001, // 7
    0b00000000, // 8
    0b01001000  // 9
};


void setup_system(void);
void play_audio(const unsigned char* audio_data, u32 data_length);
void stop_audio(void);
void delay_ms(u32 ms);
void R2R_DAC_Write(u8 data);

//  LED and 7-Segment
void turn_on_led1(void);
void turn_off_led1(void);
void seven_segment_write_digit(u8 digit);
void start_seven_segment_counter(void);
void stop_seven_segment_counter(void);

// --- Button ISR Callbacks (Will be called by EXTI IRQ Handlers) ---
void ButtonToggle_ISR(void);


// --- Main Function ---
int main(void)
{
    setup_system();

    // Set initial audio to arr1, but paused
    current_audio_buffer = arr1_raw;
    current_audio_length = arr1_raw_len;

    // Display 0 on 7-segment initially
    seven_segment_write_digit(0);

    while (1)
    {
        // Check for received UART data. MUART_u8ReceiveData() is blocking.
        // It waits until a byte is received.
        u8 received_command = MUART_u8ReceiveData();

        // Convert received character to integer if it's a digit '0'-'9'
        // If the command is '0', its ASCII value is 48. So '0' - '0' = 0.
        // Commands are '0' through '5'
        if (received_command >= '0' && received_command <= '5') {
            received_command = received_command - '0';
        } else {
            // Handle invalid command
            continue;
        }

        switch (received_command)
        {
            case 0: // Turn on LED1
                turn_on_led1();
                break;
            case 1: // Turn off LED1
                turn_off_led1();
                break;
            case 2: // Turn on music
                play_audio(current_audio_buffer, current_audio_length);
                break;
            case 3: // Turn off music
                stop_audio();
                break;
            case 4: // Set counter (7-segment) from 0 to 9
                start_seven_segment_counter();
                break;
            case 5: // Stop counter
                stop_seven_segment_counter();
                break;
            default:
                   /* any thing else**/
            	break;
        }
    }
}


void setup_system(void)
{
    // 1. Clock Setup using RCC driver
    RCC_enumIntSysClk();

    // Enable clocks for peripherals
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOA);  // GPIOA for button, UART, 7-segment
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOB);  // GPIOB for R-2R DAC
    RCC_enumEnablePeriphral(RCC_AHB1_BUS, AHB1_GPIOC);  // GPIOC for LED1
    RCC_enumEnablePeriphral(RCC_APB2_BUS, APB2_USART1);
    RCC_enumEnablePeriphral(RCC_APB1_BUS, 0);           // TIM2 peripheral (P_ID 0 on APB1)

    RCC_enumEnablePeriphral(RCC_APB2_BUS, 4);           // USART1 peripheral
    RCC_enumEnablePeriphral(RCC_APB2_BUS, 14);          // SYSCFG
    RCC_enumEnablePeriphral(RCC_APB1_BUS, 1);           // TIM3 peripheral

    // Button PA0 as Input with Pull-up
    GPIO_enuSetMode(BUTTON_TOGGLE_PORT, BUTTON_TOGGLE_PIN, INPUT);
    GPIO_enuSetInputConfig(BUTTON_TOGGLE_PORT, BUTTON_TOGGLE_PIN, PULLUP);

    // R-2R DAC Pins (PB0-PB7) as Output
    for (u8 i = 0; i < 8; i++) {
        GPIO_enuSetMode(R2R_DAC_PORT, R2R_DAC_START_PIN + i, OUTPUT);
        GPIO_enuSetOutputConfig(R2R_DAC_PORT, R2R_DAC_START_PIN + i, Push_Pull, Low_Speed);
    }

    // LED1 Pin (PC13) as Output
    GPIO_enuSetMode(LED1_PORT, LED1_PIN, OUTPUT);
    GPIO_enuSetOutputConfig(LED1_PORT, LED1_PIN, Push_Pull, Low_Speed);
    turn_off_led1();

    // 7-Segment Pins (PA1-PA7) as Output
    for (u8 i = 0; i < 7; i++) {
        GPIO_enuSetMode(SEGMENT_PORT, SEG_A_PIN + i, OUTPUT);
        GPIO_enuSetOutputConfig(SEGMENT_PORT, SEG_A_PIN + i, Push_Pull, Low_Speed);
    }
    seven_segment_write_digit(10); // Display nothing


    // UART1 Pins (PA9 TX, PA10 RX) as Alternative Function
    GPIO_enuSetMode(UART1_TX_PORT, UART1_TX_PIN, Alternative_Func);
    GPIO_enuSetAlternativeConfig(UART1_TX_PORT, UART1_TX_PIN, AF7); // AF7 for USART1
    GPIO_enuSetOutputConfig(UART1_TX_PORT, UART1_TX_PIN, Push_Pull, High_Speed); // High Speed for UART TX

    GPIO_enuSetMode(UART1_RX_PORT, UART1_RX_PIN, Alternative_Func);
    GPIO_enuSetAlternativeConfig(UART1_RX_PORT, UART1_RX_PIN, AF7); // AF7 for USART1
    GPIO_enuSetInputConfig(UART1_RX_PORT, UART1_RX_PIN, PULLUP); // Pull-up for RX

    // 3. Timer 2 Setup for 16kHz DAC
    //  APB1 clock = 16MHz .
    // For 16MHz APB1 and 16kHz Sample Rate: ARR = (16,000,000 / 16,000) - 1 = 1000 - 1 = 999
    TIM2->PSC = 0; // No prescaling (clock / 1)
    TIM2->ARR = 999; // Auto-Reload value for 16kHz
    TIM2->DIER |= (1UL << 0); // Enable Update Interrupt (UIE bit)

    // 4. Timer 3 Setup for 7-Segment Counter
    //  APB1 clock is 16MHz
    // For 1Hz (1 second) tick: PSC * ARR = 16,000,000
    //  PSC = 15999, ARR = 999 ( (15999+1) * (999+1) = 16,000 * 1,000 = 16,000,000)
    TIM3->PSC = 15999; // Prescaler for 16MHz / 16000 = 1000 Hz ->1ms
    TIM3->ARR = 999;   // Auto-Reload value for 1000 Hz / 1000 = 1 Hz ->1s
    TIM3->DIER |= (1UL << 0); // Enable Update Interrupt

    // 5. NVIC Setup for TIM2, TIM3 and EXTI (Button)
    // Enable TIM2 Interrupt in NVIC
    NVIC_enuSetEnable(28); // Enable TIM2 IRQ

    // Enable TIM3 Interrupt in NVIC
    NVIC_enuSetEnable(29); // Enable TIM3 IRQ

    // Configure EXTI for BUTTON_TOGGLE_PIN (PA0) using your EXTI driver
    EXTI_enuSetEnabletPort(EXTI_LINE0, EXTI_PORTA); // Map EXTI Line 0 to PORTA
    EXTI_enuEnable(EXTI_LINE0); // Enable EXTI Line 0 interrupt
    EXT_enuSetTrigger(EXTI_LINE0, EXTI_RISING); // Trigger on rising edge
    EXTI0_voidCallBack(ButtonToggle_ISR); // Set the callback for EXTI Line 0
    NVIC_enuSetEnable(6); // Enable EXTI Line0 IRQ (EXTI0_IRQn is '6' for STM32)

    // 6. Initialize UART1
    MUART_voidInit();
}

// --- Audio Playback Functions ---
void play_audio(const unsigned char* audio_data, u32 data_length)
{
    if (audio_data == NULL || data_length == 0) return;

    current_audio_buffer = audio_data;
    current_audio_length = data_length;
    current_audio_index = 0;
    is_playing = 1;

    // Enable TIM2 counter
    TIM2->CR1 |= TIM_CR1_CEN;
}

void stop_audio(void)
{
    is_playing = 0;
    // Disable TIM2 counter
    TIM2->CR1 &= ~TIM_CR1_CEN;
    // Optionally clear DAC output
    R2R_DAC_Write(0);
}

void delay_ms(u32 ms)
{
    // Simple busy-wait delay.
    for (u32 i = 0; i < ms * 1000; i++) {
        asm("nop");
    }
}

void R2R_DAC_Write(u8 data)
{
    // Write 8-bit data to PORTB pins (PB0-PB7)
    for (u8 i = 0; i < 8; i++) {
        if (GET_BIT(data, i)) {
            GPIO_enuSetPinValue(R2R_DAC_PORT, R2R_DAC_START_PIN + i, HIGH);
        } else {
            GPIO_enuSetPinValue(R2R_DAC_PORT, R2R_DAC_START_PIN + i, LOW);
        }
    }
}


// --- New LED Control Functions ---
void turn_on_led1(void)
{
    //  LED is active low
    GPIO_enuSetPinValue(LED1_PORT, LED1_PIN, HIGH);
}

void turn_off_led1(void)
{
    //  LED is active low
    GPIO_enuSetPinValue(LED1_PORT, LED1_PIN, LOW);
}

// ---  7-Segment Control Functions --

void seven_segment_write_digit(u8 digit)
{
    // Common Anode : LOW to turn  ON, HIGH to turn OFF
    if (digit > 9) {
        for (u8 i = 0; i < 7; i++) {
            GPIO_enuSetPinValue(SEGMENT_PORT, SEG_A_PIN + i, HIGH);
        }
        return;
    }

    u8 pattern = seven_segment_patterns[digit];
    for (u8 i = 0; i < 7; i++) {
        if (GET_BIT(pattern, i)) {
            GPIO_enuSetPinValue(SEGMENT_PORT, SEG_A_PIN + i, HIGH);
        } else {
            GPIO_enuSetPinValue(SEGMENT_PORT, SEG_A_PIN + i, LOW);
        }
    }
}


void start_seven_segment_counter(void)
{
    seven_segment_counter_enabled = 1;
    seven_segment_current_digit = 0; // Start from 0
    seven_segment_write_digit(seven_segment_current_digit);
    TIM3->CNT = 0; // Reset Timer 3
    TIM3->CR1 |= TIM_CR1_CEN; // Enable TIM3
}

void stop_seven_segment_counter(void)
{
    seven_segment_counter_enabled = 0;
    TIM3->CR1 &= ~TIM_CR1_CEN; // Disable TIM3
    seven_segment_write_digit(10); // Clear 7-segment
}


// ---  (ISRs) Callbacks ---

void ButtonToggle_ISR(void)
{
    delay_ms(50);
    u8 pin_state;
    GPIO_enuGetPinValue(BUTTON_TOGGLE_PORT, BUTTON_TOGGLE_PIN, &pin_state);

    if (pin_state == LOW)
    {
        if (is_playing)
        {
            stop_audio();
        }
        else
        {
            //  default to arr1_raw
            if (current_audio_buffer == NULL)
            {
                current_audio_buffer = arr1_raw;
                current_audio_length = arr1_raw_len;
            }
            play_audio(current_audio_buffer, current_audio_length);
        }
    }
}

// Timer 2 Interrupt Handler for DAC
void TIM2_IRQHandler(void)
{
    // Check if the Update Interrupt Flag is set
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF; // Clear the flag by writing 0

        if (is_playing && current_audio_buffer != NULL && current_audio_index < current_audio_length)
        {
            // Write the current audio
            R2R_DAC_Write(current_audio_buffer[current_audio_index]);
            current_audio_index++;
        }
        else if (current_audio_index >= current_audio_length)
        {
            stop_audio();
        }
    }
}

// Timer 3 Interrupt Handler for 7-Segment counter
void TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF; // Clear the flag

        if (seven_segment_counter_enabled)
        {
            seven_segment_current_digit++;
            if (seven_segment_current_digit > 9)
            {
                seven_segment_current_digit = 0; // Reset counter to 0 after 9
            }
            seven_segment_write_digit(seven_segment_current_digit);
        }
    }
}



