
#include "errorStates.h"
#include "stdTypes.h"

#ifndef MGPIO_INT_H
#define MGPIO_INT_H



typedef enum{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PIN_t;


typedef enum
{
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTH
}PORT_t;


typedef enum
{
	INPUT,
	OUTPUT,
	Alternative_Func,
	Analog
}Modes_t;


typedef enum
{
	NOPULLUPORPULLDOWN,
	PULLUP,
	PULLDOWN
}Input_t;

typedef enum
{
	Push_Pull,
	Open_Drain
}Output_t;


typedef enum
{
	Low_Speed,
	Med_Speed,
	High_Speed,
	VHigh_Speed
}Speed_t;

typedef enum
{
	LOW,
	HIGH
}PinValue_t;

typedef enum
{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}Alternative_t;


ES_t GPIO_enuSetMode(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Modes_t Copy_uddtMode);

/*< OUTPUT MODE **/
ES_t GPIO_enuSetOutputConfig(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Output_t Copy_uddtType,Speed_t Copy_uddtSpeed);

ES_t GPIO_enuSetPinValue(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,PinValue_t Copy_uddtPinValue);

ES_t GPIO_enuSetPinValueAtomic(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,PinValue_t Copy_uddtPinValue);

/*< INPUT MODE */
ES_t GPIO_enuSetInputConfig(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Input_t Copy_uddtType);

ES_t GPIO_enuGetPinValue(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin , u8 * Copy_pointeru8Value);

/*Alternative Mode*/
//ES_t GPIO_enuSetAlternativeConfig(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Alternative_t Copy_uddtType);

///------------------------------

void MGPIO_voidSetAlternativeConfig(PORT_t Copy_uddtPort,PIN_t Copy_uddtpin,Alternative_t Copy_uddtAltfunc);


/* LUCK PIN**/
ES_t GPIO_enuLUCKPIN(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin);

#endif
