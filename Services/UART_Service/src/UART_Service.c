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

/* ------------------------------ Includes ------------------------------------ */
#include "UART_Service.h"
/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */

/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */
UART_HandleTypeDef huart1;
/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */
static uart_bus_states_t uart_state ;
/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */

/* ---------------------------------------------------------------------------- */

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	UART_Service_Set_State(UART_TRANSMISSION_DONE);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UART_Service_Set_State(UART_RECEPTION_DONE);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
//	UART_Service_Set_State(UART_IDLE);
}


gps_tracker_error_t UART_Service_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate = UART_BAUD_RATE;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		return UART_INIT_ERROR ;
	}
	else
	{
		return GPS_TRACKER_SUCCESS ;
	}
}


gps_tracker_error_t UART_Service_Transmit_Data(uint8_t *data,uint16_t data_size)
{
	if(HAL_OK != HAL_UART_Transmit_IT(&huart1,data,data_size))
	{
		return UART_TRANSMIT_DATA_ERROR ;
	}
	else
	{
		UART_Service_Set_State(UART_COMMUNICATION_IN_PROGRESS);
		return GPS_TRACKER_SUCCESS ;
	}
}


gps_tracker_error_t UART_Service_Receive_Data(uint8_t *rx_data_buffer,uint16_t data_size)
{
	if(HAL_OK != HAL_UART_Receive_IT(&huart1,rx_data_buffer,data_size))
	{
		return UART_RECEIVE_DATA_ERROR ;
	}
	else
	{
		UART_Service_Set_State(UART_COMMUNICATION_IN_PROGRESS);
		return GPS_TRACKER_SUCCESS ;
	}
}

void UART_Service_Set_State(uart_bus_states_t state)
{
	uart_state = state ;
}	

uart_bus_states_t UART_Service_Get_State(void)
{
	return uart_state ;
}

