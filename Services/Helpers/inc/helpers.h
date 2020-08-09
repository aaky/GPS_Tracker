/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2016 Leaf Technologies
 * \file        helpers.h
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
#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
#include "stm32f0xx_hal.h"
#include "Leaf_error_codes.h"
#include "Leaf_structs.h"

#define UART_TIMEOUT							(100)
#define NULL_CHARACTER							('\0')

void printBuffer(char *uart_buffer);
uint8_t calculate_checksum(uint8_t *data,uint8_t size);

#endif
