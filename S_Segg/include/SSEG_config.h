/*
 * SSEG_config.h
 *
 * Created: 10/1/2024 5:35:04 PM
 * Author: c
 */

#ifndef SSEG_CONFIG_H
#define SSEG_CONFIG_H


#define SSEG_U8_PORT    PORTA //  ÕœÌœ «·‹ Port «·„” Œœ„ · Ê’Ì· «·‹ 7-segment

/*
  Define the pins for each segment on the chosen port
   ÕœÌœ «·‹ Pins ·ﬂ· segment (A-G) ⁄·Ï «·‹ Port «·„Œ «—
*/
#define SSEG_PIN_A      PIN0
#define SSEG_PIN_B      PIN1
#define SSEG_PIN_C      PIN2
#define SSEG_PIN_D      PIN3
#define SSEG_PIN_E      PIN4
#define SSEG_PIN_F      PIN5
#define SSEG_PIN_G      PIN6


/*
  choose from it
SSEG_U8_CATHODE
SSEG_U8_ANODE
*/
#define SSEG_HARDWARE  SSEG_U8_CATHODE //  ÕœÌœ ‰Ê⁄ «·‹ 7-segment (Common Cathode √Ê Common Anode)



#endif
