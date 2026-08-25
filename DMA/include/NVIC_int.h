
#ifndef NVIC_INT_H_
#define NVIC_INT_H_


ES_t NVIC__EnableIRQ(u8 COpy_IRQn);

ES_t NVIC_DisableIRQ(u8 COpy_IRQn);

ES_t NVIC_SetPendingIRQ( u8 COpy_IRQn);

ES_t NVIC_ClearPendingIRQ(u8 COpy_IRQn);

ES_t NVIC_GetPendingIRQ_(u8 COpy_IRQn , u8 * Copy_pu8RetPendingFlag);

ES_t NVIC_SetPriority(u8 COpy_IRQn , u32 Copy_Priority);

ES_t NVIC_Super_SetPriority(u8 COpy_IRQn , u8 Copy_GroupPriority , u8 Copy_SubPriority );

ES_t NVIC_GetPriority(u8 COpy_IRQn , u8 *Copy_pu8Priority);

ES_t NVIC_ActiveReg(u8 COpy_IRQn);

#endif
