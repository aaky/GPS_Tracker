/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2015 Leaf Technologies
 * \file        UART_Service.c
 * \brief       
 *				
 *
 * \author      Sameer Narkar
 * \date        28-Aug-2016
 * \section     History
 * <pre>
 *              Date        Responsible         Description
 *              20160827    Sameer Narkar       File Created
 * </pre>
 */
/**********************************************************************/

#ifndef UART_SERVICE_H
#define UART_SERVICE_H
/* ------------------------------ Includes ------------------------------------ */
#include <stdint.h>
#include "Error_codes.h"
#include "stm32l0xx_hal.h"
/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */
#define UART_BAUD_RATE					(9600)
/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */
typedef enum
{
	UART_IDLE,
	UART_TRANSMISSION_DONE,
	UART_COMMUNICATION_IN_PROGRESS,
	UART_RECEPTION_DONE,
}uart_bus_states_t ;


/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */
gps_tracker_error_t UART_Service_Init(void);
gps_tracker_error_t UART_Service_Transmit_Data(uint8_t *data,uint16_t data_size);
gps_tracker_error_t UART_Service_Receive_Data(uint8_t *rx_data_buffer,uint16_t data_size);

void UART_Service_Set_State(uart_bus_states_t state);
uart_bus_states_t UART_Service_Get_State(void);
/* ---------------------------------------------------------------------------- */
#endif
