
#include "StdTypes.h"
#include "errorStates.h"
#include "BIT_MATH.h"

#include "NVIC_priv.h"
#include "NVIC_config.h"
#include "NVIC_int.h"



ES_t NVIC__EnableIRQ(u8 COpy_IRQn)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(COpy_IRQn >=0 && COpy_IRQn <=31)
	{
		/*< in ARM in this reg not need to make set just write on it */
		NVIC_ISER0 =(1<<COpy_IRQn);
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn >=32 && COpy_IRQn <=63)
	{
		NVIC_ISER1 =(1<<(COpy_IRQn-32));
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn >=64 && COpy_IRQn <=94)
	{
		NVIC_ISER2 =(1<<(COpy_IRQn-64));
        Local_enuErrorState = ES_OK;		
		
	}
	else 
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}



ES_t NVIC_DisableIRQ(u8 COpy_IRQn)
{
	ES_t Local_enuErrorState = ES_NOK;
	if( COpy_IRQn <32)
	{
		/*< in ARM in this reg not need to make set just write on it */
		NVIC_ICER0 =(1<<COpy_IRQn);
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn <64)
	{
		NVIC_ICER1 =(1<<(COpy_IRQn-32));
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn <95)
	{
		NVIC_ICER2 =(1<<(COpy_IRQn-64));
Local_enuErrorState = ES_OK;		
	}
	else 
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}



ES_t NVIC_SetPendingIRQ(u8 COpy_IRQn)
{
	ES_t Local_enuErrorState = ES_NOK;
	if( COpy_IRQn <32)
	{
		/*< in ARM in this reg not need to make set just write on it */
		NVIC_ISPR0 =(1<<COpy_IRQn);
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn <64)
	{
		NVIC_ISPR1 =(1<<(COpy_IRQn-32));
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn <95)
	{
		NVIC_ISPR2 =(1<<(COpy_IRQn-64));
Local_enuErrorState = ES_OK;		
	}
	else 
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}



ES_t NVIC_ClearPendingIRQ(u8 COpy_IRQn)
{
	ES_t Local_enuErrorState = ES_NOK;
	if( COpy_IRQn <32)
	{
		/*< in ARM in this reg not need to make set just write on it */
		NVIC_ICPR0 =(1<<COpy_IRQn);
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn <64)
	{
		NVIC_ICPR1 =(1<<(COpy_IRQn-32));
		Local_enuErrorState = ES_OK;
	}
	else if (COpy_IRQn <95)
	{
		NVIC_ICPR2 =(1<<(COpy_IRQn-64));
Local_enuErrorState = ES_OK;		
	}
	else 
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}



ES_t NVIC_GetPendingIRQ_(u8 COpy_IRQn , u8 * Copy_pu8RetPendingFlag)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu8RetPendingFlag != NULL)
	{
		if(COpy_IRQn <32)
		{
			*Copy_pu8RetPendingFlag = ((NVIC_ISPR0>>COpy_IRQn)&1);
		}
		if(COpy_IRQn <64)
		{
			*Copy_pu8RetPendingFlag = ((NVIC_ISPR0>>(COpy_IRQn-32))&1);
		}
		if(COpy_IRQn <95)
		{
			*Copy_pu8RetPendingFlag = ((NVIC_ISPR0>>(COpy_IRQn-64))&1);
		}
	   Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}


/* need Enhansment*/

ES_t NVIC_SetPriority(u8 Copy_IRQn , u32 Copy_Priority)
{
	ES_t Local_enuErrorState = ES_NOK;
	/*< not nestined all of them are sub group**/
	if(Copy_IRQn < NUMBER_OF_INTERRUPT && Copy_Priority <= NVIC_MAX_PRIOROTY)
	{
		/*< Calculate register index (IPRx) and bit position within the register*/
		u8 Local_Index = Copy_IRQn/4 ; /*< Division by 4 to get the register index**/
		/*< Set the priority in the appropriate (IPRx) register */
		NVIC_IPR_BASE_ADDRESSES[Local_Index] = (Copy_Priority <<4) ;
		/*< SYSTEM CONTROLE BLOCK **/
		SCB_AICR = _0_GROUP_16_SUB_PRIORITY;
	}
	else 
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}


/*<   **/
ES_t NVIC_Super_SetPriority(u8 COpy_IRQn , u8 Copy_GroupPriority , u8 Copy_SubPriority )
{
	ES_t Local_enuErrorState = ES_NOK;
	#if (PRIORITY_GROUPING == _16_GROUP_0_SUB_PRIORITY || PRIORITY_GROUPING == _8_GROUP_2_SUB_PRIORITY || PRIORITY_GROUPING == _4_GROUP_4_SUB_PRIORITY || PRIORITY_GROUPING ==_2_GROUP_8_SUB_PRIORITY ||  PRIORITY_GROUPING == _0_GROUP_16_SUB_PRIORITY)
		/*< ADC , 2,3 ->> 500-300=200/100=2 ->>(0010<<2)=(1000|3)=(1011)*/
	    u8 Local_Priority = (Copy_SubPriority |(Copy_GroupPriority <<(PRIORITY_GROUPING - _16_GROUP_0_SUB_PRIORITY)/0x100));
	    if(COpy_IRQn < 0)
	    {
			return Local_enuErrorState ;
	    }
			
		/*< Calculate register index (IPRx) and bit position within the register*/
		u8 Local_Index = COpy_IRQn/4 ; /*< Division by 4 to get the register index**/

		
		/*< Set the priority in the appropriate (IPRx) register*/
		NVIC_IPR_BASE_ADDRESSES[Local_Index] = (Local_Priority <<4);
		
	#else
		#error "    "
		
	#endif /*<Copy_GroupPriority  */
	
	return Local_enuErrorState;
}



ES_t NVIC_GetPriority(u8 COpy_IRQn , u8 *Copy_pu8Priority)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pu8Priority !=NULL)
	{
		if(COpy_IRQn < NUMBER_OF_INTERRUPT)
		{
			return Local_enuErrorState;
		}
	
	/*< Calculate register index (IPRx) and bit position within the register*/
	u8 RegisterIndex = COpy_IRQn/4;  /*< Divide by 4 to get the register index**/
	u8 BitIndex = (COpy_IRQn % 4);   /*< Reminder 4 to get the bit index **/
	u8 BitPosition = (COpy_IRQn % 4)*8; /*< Multiply by 8 to get the bit position **/
	
	/*< Pointer arithmetic to access the IPRx register**/
	u8 *PriorityRegister = (u8 *)&NVIC_IPR_BASE_ADDRESSES[RegisterIndex];
	
	/*<Extract the pointer from the IPRx register **/
	*Copy_pu8Priority =(PriorityRegister[BitIndex] >>(BitPosition))&0xFF;
	
	Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}
	
	return Local_enuErrorState;
}
