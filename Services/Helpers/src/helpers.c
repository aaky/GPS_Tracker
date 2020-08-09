/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2016 Leaf Technologies
 * \file        helpers.c
 * \brief       Consists of functions which will act as helpers. 
 *              
 * \author      Akash Patil 
 * \date        03-Feb-2016
 * \section     History
 * <pre>
 *              Date        Responsible         Description
 *              20160203    Akash Patil		      File Created
 * </pre>
 */
/**********************************************************************/
#include "helpers.h"

extern UART_HandleTypeDef huart1 ;

void printBuffer(char *uart_buffer)
{
	#if 0
	uint8_t uart_tx_data = 0;
	while(*uart_buffer != NULL_CHARACTER)
	{
		uart_tx_data = *uart_buffer ;
		HAL_UART_Transmit(&huart1,&uart_tx_data,sizeof(uart_tx_data),UART_TIMEOUT);
		uart_buffer += 1 ;
	}
	#endif
}

uint8_t calculate_checksum(uint8_t *data,uint8_t size)
{
	uint8_t checksum = 0 ;
	for( uint8_t count = 0 ; count < size ; count++ )
	{
		checksum ^= data[count] ;
	}
	return (checksum & 0xFF) ;
}


