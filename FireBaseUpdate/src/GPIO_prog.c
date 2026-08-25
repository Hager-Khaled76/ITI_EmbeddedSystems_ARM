
//AI
/*
 * GPIO_prog.c
 *
 * Created on: Jul 10, 2025
 * Author: c
 */

#include "errorStates.h"
#include "stdTypes.h"
#include "BIT_MATH.h"

#include "GPIO_priv.h"
#include "GPIO_config.h"
#include "GPIO_int.h"

/*
 * INPUT
 * OUTPUT
 * AL_F
 * ANALOG
 * */
ES_t GPIO_enuSetMode(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Modes_t Copy_uddtMode)
{
	ES_t localenuErrorState = ES_NOK;

	/*if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		localenuErrorState = ES_RESERVED_A;
	}*/
	/*else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		localenuErrorState = ES_RESERVED_B;
	}*/
	//else
//	{
		switch(Copy_uddtPort)
		{
		case PORTA:
			GPIOA->MODER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOA->MODER|=(Copy_uddtMode<<(Copy_uddtPin*2));
			break;

		case PORTB:
			GPIOB->MODER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOB->MODER|=(Copy_uddtMode<<(Copy_uddtPin*2));
			break;

		case PORTC:
			GPIOC->MODER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOC->MODER|=(Copy_uddtMode<<(Copy_uddtPin*2));
			break;
		}
		localenuErrorState = ES_OK;
	//}
	return localenuErrorState;
}


/*
 * PUSHPULL
 * OPENDRAIN
 * */
ES_t GPIO_enuSetOutputConfig(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Output_t Copy_uddtOutType,Speed_t Copy_uddtSpeed)
{
	ES_t localenuErrorState = ES_NOK;

	/*if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		localenuErrorState = ES_RESERVED_A;
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		localenuErrorState = ES_RESERVED_B;
	}*/
	//else
	//{
		switch(Copy_uddtPort)
		{
		case PORTA:
			GPIOA->OTYPER&=~(1<<Copy_uddtPin);
			GPIOA->OTYPER|=(Copy_uddtOutType<<Copy_uddtPin);

			GPIOA->OSPEEDER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOA->OSPEEDER|=(Copy_uddtSpeed<<(Copy_uddtPin*2));
			break;

		case PORTB:
			GPIOB->OTYPER&=~(1<<Copy_uddtPin);
			GPIOB->OTYPER|=(Copy_uddtOutType<<Copy_uddtPin);

			GPIOB->OSPEEDER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOB->OSPEEDER|=(Copy_uddtSpeed<<(Copy_uddtPin*2));
			break;

		case PORTC:
			GPIOC->OTYPER&=~(1<<Copy_uddtPin);
			GPIOC->OTYPER|=(Copy_uddtOutType<<Copy_uddtPin);

			GPIOC->OSPEEDER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOC->OSPEEDER|=(Copy_uddtSpeed<<(Copy_uddtPin*2));
			break;
		}
		localenuErrorState = ES_OK;
	//}
	return localenuErrorState;
}

ES_t GPIO_enuSetInputConfig(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Input_t Copy_uddtInputType)
{
	ES_t localenuErrorState = ES_NOK;

	//if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	//{
		//localenuErrorState = ES_RESERVED_A;
	//}
	/*else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		localenuErrorState = ES_RESERVED_B;
	}*/
	//else
	//{
		switch(Copy_uddtPort)
		{
		case PORTA:
			GPIOA->PUPDR&=~(MUSK<<(Copy_uddtPin*2));
			GPIOA->PUPDR|=(Copy_uddtInputType<<(Copy_uddtPin*2));
			break;

		case PORTB:
			GPIOB->PUPDR&=~(MUSK<<(Copy_uddtPin*2));
			GPIOB->PUPDR|=(Copy_uddtInputType<<(Copy_uddtPin*2));
			break;

		case PORTC:
			GPIOC->PUPDR&=~(MUSK<<(Copy_uddtPin*2));
			GPIOC->PUPDR|=(Copy_uddtInputType<<(Copy_uddtPin*2));
			break;
		}
		localenuErrorState = ES_OK;
	//}
	return localenuErrorState;
}

ES_t GPIO_enuSetPinValue(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,PinValue_t Copy_uddtPinValue)
{
	ES_t localenuErrorState = ES_NOK;

	//if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	//{
		//localenuErrorState = ES_RESERVED_A;
	//}
	/*else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		localenuErrorState = ES_RESERVED_B;
	}*/
	//else
	//{
		switch(Copy_uddtPort)
		{
		case PORTA:
			if(Copy_uddtPinValue==LOW)
			{
				CLR_BIT(GPIOA->ODR,Copy_uddtPin);
			}
			else
			{
				SET_BIT(GPIOA->ODR,Copy_uddtPin);
			}
			break;

		case PORTB:
			if(Copy_uddtPinValue==LOW)
			{
				CLR_BIT(GPIOB->ODR,Copy_uddtPin);
			}
			else
			{
				SET_BIT(GPIOB->ODR,Copy_uddtPin);
			}
			break;

		case PORTC:
			if(Copy_uddtPinValue==LOW)
			{
				CLR_BIT(GPIOC->ODR,Copy_uddtPin);
			}
			else
			{
				SET_BIT(GPIOC->ODR,Copy_uddtPin);
			}
			break;
		}
		localenuErrorState = ES_OK;
	//}
	return localenuErrorState;
}

ES_t GPIO_enuGetPinValue(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,u8* Copy_uddtPinValue)
{
	ES_t localenuErrorState = ES_NOK;

	//if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	//{
		//localenuErrorState = ES_RESERVED_A;
	//}
	/*else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		localenuErrorState = ES_RESERVED_B;
	}*/
	//else
	//{
		switch(Copy_uddtPort)
		{
		case PORTA:
			*Copy_uddtPinValue=GET_BIT(GPIOA->IDR,Copy_uddtPin);
			break;

		case PORTB:
			*Copy_uddtPinValue=GET_BIT(GPIOB->IDR,Copy_uddtPin);
			break;

		case PORTC:
			*Copy_uddtPinValue=GET_BIT(GPIOC->IDR,Copy_uddtPin);
			break;
		}
		localenuErrorState = ES_OK;
	//}
	return localenuErrorState;
}


ES_t GPIO_enuSetPinValueAtomic(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,PinValue_t Copy_uddtPinValue)
{
	ES_t localenuErrorState = ES_NOK;

	/*if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		localenuErrorState = ES_RESERVED_A;
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		localenuErrorState = ES_RESERVED_B;
	}
	else
	{*/
		switch(Copy_uddtPort)
		{
		case PORTA:
			if(Copy_uddtPinValue==LOW)
			{
				GPIOA->BSRR = (1 << (Copy_uddtPin + 16));
			}
			else
			{
				GPIOA->BSRR = (1 << Copy_uddtPin);
			}
			break;

		case PORTB:
			if(Copy_uddtPinValue==LOW)
			{
				GPIOB->BSRR = (1 << (Copy_uddtPin + 16));
			}
			else
			{
				GPIOB->BSRR = (1 << Copy_uddtPin);
			}
			break;

		case PORTC:
			if(Copy_uddtPinValue==LOW)
			{
				GPIOC->BSRR = (1 << (Copy_uddtPin + 16));
			}
			else
			{
				GPIOC->BSRR = (1 << Copy_uddtPin);
			}
			break;
		//}
		localenuErrorState = ES_OK;
	}
	return localenuErrorState;
}


ES_t GPIO_enuSetAlternativeConfig(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin,Alternative_t Copy_uddtType)
{
	ES_t localenuErrorState = ES_NOK;

	/*if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		localenuErrorState = ES_RESERVED_A;
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		localenuErrorState = ES_RESERVED_B;
	}
	else
	{*/
		switch(Copy_uddtPort)
		{
		case PORTA:
			if(Copy_uddtPin<8)
			{
				GPIOA->AFRL&=~(ALF_MUSK<< (Copy_uddtPin*4));
				GPIOA->AFRL|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			else // if(Copy_uddtPin<16)
			{
				Copy_uddtPin-=8;
				GPIOA->AFRH&=~(ALF_MUSK<<((Copy_uddtPin%8)*4));
				GPIOA->AFRH|=(Copy_uddtType<<((Copy_uddtPin%8)*4));
			}
			break;
		case PORTB:
			if(Copy_uddtPin<8)
			{
				GPIOB->AFRL&=~(ALF_MUSK<< (Copy_uddtPin*4));
				GPIOB->AFRL|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			else // if(Copy_uddtPin<16)Ç
			{
				Copy_uddtPin-=8;
				GPIOB->AFRH&=~(ALF_MUSK<<((Copy_uddtPin%8)*4));
				GPIOB->AFRH|=(Copy_uddtType<<((Copy_uddtPin%8)*4));
			}
			break;
		case PORTC:
			if(Copy_uddtPin<8)
			{
				GPIOC->AFRL&=~(ALF_MUSK<<(Copy_uddtPin*4));
				GPIOC->AFRL|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
            else
			{
				Copy_uddtPin-=8;
				GPIOC->AFRH&=~(ALF_MUSK<<((Copy_uddtPin%8)*4));
				GPIOC->AFRH|=(Copy_uddtType<<((Copy_uddtPin%8)*4));
			}
			break;
		}
		localenuErrorState = ES_OK;
	//}
	return localenuErrorState;
}


ES_t GPIO_enuLUCKPIN(PORT_t Copy_uddtPort,PIN_t Copy_uddtPin)
{
	ES_t localenuErrorState = ES_NOK;

	switch(Copy_uddtPort)
	{
	    case PORTA:
		   SET_BIT(GPIOA->LCKR , Copy_uddtPin);
		   SET_BIT(GPIOA->LCKR , LUCK_PIN);
		   while(!(GET_BIT(GPIOA->LCKR,LUCK_PIN)));
		break;

	    case PORTB:
		   SET_BIT(GPIOB->LCKR , Copy_uddtPin);
		   SET_BIT(GPIOB->LCKR , LUCK_PIN);
		   while(!(GET_BIT(GPIOB->LCKR,LUCK_PIN)));
		break;

	    case PORTC:
		   SET_BIT(GPIOC->LCKR , Copy_uddtPin);
		   SET_BIT(GPIOC->LCKR , LUCK_PIN);
		   while(!(GET_BIT(GPIOC->LCKR,LUCK_PIN)));

		break;
	}
	localenuErrorState=ES_OK;

	return localenuErrorState;

}






