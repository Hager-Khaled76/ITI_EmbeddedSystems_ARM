/*
 * TFT_Prog.c
 *
 *  Created on: Jul 31, 2025
 *      Author: c
 */

#ifndef TFT_CONFIG_H_
#define TFT_CONFIG_H_


#define TFT_PORT       PORTA
#define RST_PIN        PIN0
#define CONTROL_PIN    PIN1

#define SLEEP_OUT      0x11
#define C0LOR_MODE     0x3A
#define DISPLAY_ON     0x29
#define X_Direction    0x2A
#define Y_Direction    0x2B
#define SCREEN_WRITE   0x2C

#define RGB565         0x05

// Start & End x
#define START_X_B0       0
#define START_X_B1       0
#define END_X_B0         0
#define END_X_B1        127

// Start & End Y
#define START_Y_B0       0
#define START_Y_B1       0
#define END_Y_B0         0
#define END_Y_B1         159

// Image size
#define IMAGE_SIZE    20480

#endif /* TFT_PROG_C_ */
