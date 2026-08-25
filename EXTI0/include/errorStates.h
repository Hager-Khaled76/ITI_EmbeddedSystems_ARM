/*
 * errorStates.h
 *
 *  Created on: Aug 11, 2024
 *      Author: !?
 */

#ifndef ERRORSTATES_H_
#define ERRORSTATES_H_
/*
 * #define OK  0
 * #define NOK  1
 * #define NULLPOINTER 2
 *
 * but we can used enum to make it becouse it return enumerator by one
 * Sooo
 */
typedef enum
{
	ES_OK,                //0
	ES_NOK,               //1
	ES_NULL_POINTER,     //2
	ES_OUT_OF_RANGE      //3

}ES_t;


#endif /* ERRORSTATES_H_ */
