
#ifndef NVIC_CONFIG_H_
#define NVIC_CONFIG_H_


#define NUMBER_OF_INTERRUPT      240 //CORTX-3M _>>67
#define NVIC_MAX_PRIOROTY        15


/**
          _16_GROUP_0_SUB_PRIORITY 
          _8_GROUP_2_SUB_PRIORITY  
          _4_GROUP_4_SUB_PRIORITY  
          _2_GROUP_8_SUB_PRIORITY  
          _0_GROUP_16_SUB_PRIORITY
*/

 #define PRIORITY_GROUPING       _16_GROUP_0_SUB_PRIORITY


#endif