/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2016
 * \file        GSM.h
 * \brief       Initialization and use of GPRS Pheripheral
 * \author      Sameer Narkar
 * \date        27-Aug-2016
 * \section     History
 * <pre>
 *              Date        Responsible         Description
 *              20160827    Sameer Narkar		      File Created
 * </pre>
 */
/**********************************************************************/

/* ------------------------------ Includes ------------------------------------ */
#include "GSM.h"
#include "UART_Service.h"
#include "GPS.h"
/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */

/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */
uint8_t gsm_module_received_data[MAX_GSM_MODULE_RESPONSE_DATA] ;

uint8_t gsm_module_transmit_data[MAX_GSM_MODULE_RESPONSE_DATA] ;
uint8_t mobile_number[] = "9028551648" ; 


/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */
static bool module_response_ok = false ;
static bool module_response_error = false ;
static bool module_response_sms_send_start = false ;

bool gps_communication_fixed = false ;
bool gps_continous_reception_enabled = false ;
/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */

/* ---------------------------------------------------------------------------- */

gps_tracker_error_t GSM_Service_Init(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)BASIC_AUTO_BAUD_SYNC_COMMAND,BYTES_BASIC_AUTO_BAUD_SYNC_COMMAND);
	if(error != GPS_TRACKER_SUCCESS)
	{
		//Retry
		return error ;
	}
	else
	{
		while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
		{
			//Give execution time for ISR
			HAL_Delay(1);
		}
		error = GSM_Service_Parse_Response(GSM_AUTOBAUD_SYNC_CMD);
		if(error != GPS_TRACKER_SUCCESS)
		{
			//Report error
			return error ;
		}
		else
		{
			error = GSM_Service_DetectValidSimCard();
			return error ;
		}
	}
}

gps_tracker_error_t GSM_Service_DetectValidSimCard(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)SIM_CARD_OK_COMMAND,BYTES_SIM_CARD_OK_COMMAND);
	if(error != GPS_TRACKER_SUCCESS)
	{
		//Retry error
		return error ;
	}
	else
	{
		while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
		{
			//Give execution time for ISR
			HAL_Delay(1);
		}
		
		error = GSM_Service_Parse_Response(GSM_SIM_OK_COMMAND);
		return error ;
	}
}


gps_tracker_error_t GSM_Service_ResetToDefault(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)GSM_RESET_SETTINGS_TO_DEFAULT,BYTES_GSM_RESET_SETTINGS_TO_DEFAULT);
	if(error != GPS_TRACKER_SUCCESS)
	{
		//Retry error
		return error ;
	}
	else
	{
		while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
		{
			//Give execution time for ISR
			HAL_Delay(1);
		}
		
		error = GSM_Service_Parse_Response(GSM_RESET_TO_DEFAULT_COMMAND);
		return error ;
	}
}



gps_tracker_error_t GSM_Service_SendSMS(uint8_t *message_to_be_transmitted,uint16_t size_of_data)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)GSM_SWITCH_TO_TEXT_MODE,BYTES_GSM_SWITCH_TO_TEXT_MODE);
	if(error != GPS_TRACKER_SUCCESS)
	{
		return error ;
	}
	else
	{
		while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
		{
			//Give execution time for ISR
			HAL_Delay(1);
		}
		error = GSM_Service_Parse_Response(GSM_SWITCH_TO_TEXT_MODE_COMMAND);
		if(error != GPS_TRACKER_SUCCESS)
		{
			if(error == GSM_MODULE_ALREADY_IN_TEXT_MODE)
			{
				//In this case send SMS directly to registered mobile number
				memset(gsm_module_transmit_data,0,MAX_GSM_MODULE_RESPONSE_DATA);
				memcpy(gsm_module_transmit_data,message_to_be_transmitted,size_of_data);
				gsm_module_transmit_data[size_of_data] = GSM_FINISH_SMS_TEXT_COMMAND ;
				
				error = UART_Service_Transmit_Data(gsm_module_transmit_data,size_of_data+1);
				if(error != GPS_TRACKER_SUCCESS)
				{
					//Retry error
					return error ;
				}
				else
				{
					while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
					{
						//Give execution time for ISR
						HAL_Delay(1);
					}
					error = GSM_Service_Parse_Response(GSM_SMS_SEND_SUCCESS_RESPONSE);
					return error ;
				}
			}
			else
			{
//				error = UART_Service_Transmit_Data((uint8_t*)GSM_SWITCH_TO_PDU_MODE,BYTES_GSM_SWITCH_TO_TEXT_MODE);
//				if(error != GPS_TRACKER_SUCCESS)
//				{
//					return error ;
//				}
//				else
//				{
//					while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
//					{
//						//Give execution time for ISR
//						HAL_Delay(1);
//					}
//					error = GSM_Service_Parse_Response(GSM_SWITCH_TO_TEXT_MODE_COMMAND);
//					return error ;
//				}
				return error ;
			}
		}
		else
		{
			memcpy(gsm_module_transmit_data,GSM_SEND_SMS_COMMAND,BYTES_GSM_SEND_SMS_COMMAND);
			gsm_module_transmit_data[BYTES_GSM_SEND_SMS_COMMAND] = GSM_DOUBLE_QUOTES_COMMAND ;
			memcpy(&gsm_module_transmit_data[BYTES_GSM_SEND_SMS_COMMAND+1],mobile_number,MOBILE_NUMBER_BYTES);
			gsm_module_transmit_data[BYTES_GSM_SEND_SMS_COMMAND+MOBILE_NUMBER_BYTES+1] = GSM_DOUBLE_QUOTES_COMMAND ;
			gsm_module_transmit_data[BYTES_GSM_SEND_SMS_COMMAND+MOBILE_NUMBER_BYTES+2] = '\r' ;
			
			error = UART_Service_Transmit_Data(gsm_module_transmit_data,BYTES_GSM_SEND_SMS_COMMAND+MOBILE_NUMBER_BYTES+3);
			if(error != GPS_TRACKER_SUCCESS)
			{
				//Retry error
				return error ;
			}
			else
			{
				while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
				{
					//Give execution time for ISR
					HAL_Delay(1);
				}
				error = GSM_Service_Parse_Response(GSM_SMS_SEND_COMMAND);
				if(error != GPS_TRACKER_SUCCESS)
				{
					//Report error
					return error ;
				}
				else
				{
					memset(gsm_module_transmit_data,0,MAX_GSM_MODULE_RESPONSE_DATA);
					memcpy(gsm_module_transmit_data,message_to_be_transmitted,size_of_data);
					gsm_module_transmit_data[size_of_data] = GSM_FINISH_SMS_TEXT_COMMAND ;
					
					error = UART_Service_Transmit_Data(gsm_module_transmit_data,size_of_data+1);
					if(error != GPS_TRACKER_SUCCESS)
					{
						//Retry error
						return error ;
					}
					else
					{
						while(UART_Service_Get_State() != UART_TRANSMISSION_DONE)
						{
							//Give execution time for ISR
							HAL_Delay(1);
						}
						error = GSM_Service_Parse_Response(GSM_SMS_SEND_SUCCESS_RESPONSE);
						return error ;
					}
				}
			}
		}
	}
}


void GSM_Service_ReadReceivedSMS(uint8_t *received_message)
{
	
}

gps_tracker_error_t GSM_Service_Parse_Response(gsm_msg_type_t msg_type)
{	
	memset(gsm_module_received_data,0,sizeof(gsm_module_received_data));
	module_response_ok = false ;
	module_response_error = false ;
	module_response_sms_send_start = false ;
	
	gps_tracker_error_t error = UART_Service_Receive_Data(gsm_module_received_data,MAX_GSM_MODULE_RESPONSE_DATA);
	if(error != GPS_TRACKER_SUCCESS)
	{
		return UART_RECEIVE_DATA_ERROR ;
	}
	else
	{
		//Now Parse the received response
		while(UART_Service_Get_State() != UART_RECEPTION_DONE)
		{
			//Give execution time for ISR
			HAL_Delay(1);
		}
		
		switch(msg_type)
		{
			case GSM_AUTOBAUD_SYNC_CMD :
			case GSM_SIM_OK_COMMAND :	
			case GSM_SMS_SEND_SUCCESS_RESPONSE :
			case GSM_RESET_TO_DEFAULT_COMMAND :
			case GPS_GNSS_POWER_ON_COMMAND :
			case GPS_GNSS_POWER_OFF_COMMAND :
			case GPS_GNSS_SENTENCE_TYPE :
			{
				if(module_response_ok != true)
				{
					return GSM_MODULE_WRONG_RESPONSE ;
				}
				else
				{
					return GPS_TRACKER_SUCCESS ;
				}
			}
			
			case GSM_SWITCH_TO_TEXT_MODE_COMMAND :
			{
				if(module_response_ok != true)
				{
					if(module_response_sms_send_start == true)
					{
						return GSM_MODULE_ALREADY_IN_TEXT_MODE ;
					}
					else
					{
						return GSM_MODULE_WRONG_RESPONSE ;
					}
				}
				else
				{
					return GPS_TRACKER_SUCCESS ;
				}
				
			}
			
			case GSM_SMS_SEND_COMMAND :
			{
				if(module_response_sms_send_start != true)
				{
					return GSM_MODULE_WRONG_RESPONSE ;
				}
				else
				{
					return GPS_TRACKER_SUCCESS ;
				}
			}
			
			case GSM_SMS_RECEIVE_COMMAND :
			{
				
				break ;
			}
			
			case GPS_GET_LOCATION_INFO_COMMAND :
			{
				if(module_response_ok != true)
				{
					return GSM_MODULE_WRONG_RESPONSE ;
				}
				else
				{
					if(gsm_module_received_data[GPS_FIX_BYTE_OFFSET] == '1')
					{
						//Now GPS connection with satelite is fix and lattitude and longitude captured will be accurate
						gps_communication_fixed = true ;
						
						uint8_t offset = GPS_LATTITUDE_INFO_OFFSET , temp_offset = 0 ;
						uint8_t lattitude_buffer[GPS_LATTITUDE_INFO_BYTES] = {0} ;
						uint8_t longitude_buffer[GPS_LONGITUDE_INFO_BYTES] = {0} ;
						
						while(gsm_module_received_data[offset] != ',')
						{
							lattitude_buffer[temp_offset] = gsm_module_received_data[offset] ;
							temp_offset += 1 ;
							offset += 1 ;
						}
//						if(temp_offset < (GPS_LATTITUDE_INFO_BYTES - 1))
//						{
//							//Append zeros for unfilled data
//							for(uint8_t temp_var = temp_offset + 1 ; temp_var <= (GPS_LATTITUDE_INFO_BYTES - 1) ; temp_var++)
//							{
//								lattitude_buffer[temp_var] = '0' ;
//							}
//						}
						GPS_Service_SetLattitudeData(lattitude_buffer,temp_offset);
						
						temp_offset = 0 ;
						offset += 1 ;
						while(gsm_module_received_data[offset] != ',')
						{
							longitude_buffer[temp_offset] = gsm_module_received_data[offset] ;
							temp_offset += 1 ;
							offset += 1 ;
						}
//						if(temp_offset < (GPS_LONGITUDE_INFO_BYTES - 1))
//						{
//							//Append zeros for unfilled data
//							for(uint8_t temp_var = temp_offset + 1 ; temp_var <= (GPS_LONGITUDE_INFO_BYTES - 1) ; temp_var++)
//							{
//								longitude_buffer[temp_var] = '0' ;
//							}
//						}
						GPS_Service_SetLongitudeData(longitude_buffer,temp_offset);
						
					}
					else
					{
						//GPS is not yet fixed
						gps_communication_fixed = false ;
					}
					return GPS_TRACKER_SUCCESS ;
				}
			}
			
			case GPS_ENABLE_CONTINOUS_LOCATION_INFO :
			{

				uint8_t offset = 0 , temp_offset = 0 ;
				bool found_valid_data = false ;
				gps_continous_reception_enabled = true ;
				while(offset < MAX_GSM_MODULE_RESPONSE_DATA)
				{
					if((gsm_module_received_data[offset] != 'U') && (gsm_module_received_data[offset+1] != 'G') &&
					(gsm_module_received_data[offset+2] != 'N') && (gsm_module_received_data[offset+3] != 'S') &&
					(gsm_module_received_data[offset+4] != 'I') && (gsm_module_received_data[offset+5] != 'N')
					&& (gsm_module_received_data[offset+6] != 'F'))
					{
						offset += GPS_URC_FIX_BYTE_OFFSET ;
						found_valid_data = true ;
						break ;
					}
					offset += 1 ;
				}
					
				if((gsm_module_received_data[offset] == '1') && (found_valid_data))
				{
					//Now GPS connection with satelite is fix and lattitude and longitude captured will be accurate
//					gps_communication_fixed = true ;
					
//					offset = GPS_URC_LATTITUDE_INFO_OFFSET , temp_offset = 0 ;
//					uint8_t lattitude_buffer[GPS_LATTITUDE_INFO_BYTES] = {0} ;
//					uint8_t longitude_buffer[GPS_LONGITUDE_INFO_BYTES] = {0} ;
//					
//					while(gsm_module_received_data[offset] != ',')
//					{
//						lattitude_buffer[temp_offset] = gsm_module_received_data[offset] ;
//						temp_offset += 1 ;
//						offset += 1 ;
//					}
//					if(temp_offset < (GPS_LATTITUDE_INFO_BYTES - 1))
//					{
//						//Append zeros for unfilled data
//						for(uint8_t temp_var = temp_offset + 1 ; temp_var <= (GPS_LATTITUDE_INFO_BYTES - 1) 
//								; temp_var++)
//						{
//							lattitude_buffer[temp_var] = '0' ;
//						}
//					}
//					GPS_Service_SetLattitudeData(lattitude_buffer);
//					
//					temp_offset = 0 ;
//					offset += 1 ;
//					while(gsm_module_received_data[offset] != ',')
//					{
//						longitude_buffer[temp_offset] = gsm_module_received_data[offset] ;
//						temp_offset += 1 ;
//						offset += 1 ;
//					}
//					if(temp_offset < (GPS_LONGITUDE_INFO_BYTES - 1))
//					{
//						//Append zeros for unfilled data
//						for(uint8_t temp_var = temp_offset + 1 ; temp_var <= (GPS_LONGITUDE_INFO_BYTES - 1) ; temp_var++)
//						{
//							longitude_buffer[temp_var] = '0' ;
//						}
//					}
//					GPS_Service_SetLongitudeData(longitude_buffer);
//					GPS_Service_DisableContinousGPSData();
				}
				return GPS_TRACKER_SUCCESS ;
				
			}
			
			case GPS_DISABLE_CONTINOUS_LOCATION_INFO :
			{
				if(module_response_ok != true)
				{
					return GSM_MODULE_WRONG_RESPONSE ;
				}
				else
				{
					gps_continous_reception_enabled = false ;
				}
				return GPS_TRACKER_SUCCESS ;
			}
			
			default : break ;
		}
		return GPS_TRACKER_SUCCESS ;
	}
}

uint8_t GSM_Service_Find_New_Line_Characters(uint8_t *received_data)
{
	uint8_t offset ;
	for(offset = 0 ;((received_data[offset] != '\r') && (received_data[offset+1] != '\n'));offset++);
	return (offset + 2) ;
}

bool GSM_Service_Find_OK_Response(uint8_t *received_data,uint16_t data_size)
{
	uint8_t offset = 0 ;
	while(offset < data_size)
	{
		if((received_data[offset] == '\r') && (received_data[offset+1] == '\n') && (received_data[offset+2] == 'O')
		 && (received_data[offset+3] == 'K') && (received_data[offset+4] == '\r') && (received_data[offset+5] == '\n'))
		{
			module_response_ok = true ;
			return true ;
		}
		offset += 1 ;
	}
	return false ;
}

bool GSM_Service_Find_Error_Response(uint8_t *received_data,uint16_t data_size)
{
	uint8_t offset = 0 ;
	while(offset < data_size)
	{
		if((received_data[offset] == '\r') && (received_data[offset+1] == '\n') && (received_data[offset+2] == 'E')
		 && (received_data[offset+3] == 'R') && (received_data[offset+4] == 'R') && (received_data[offset+5] == 'O') 
		&& (received_data[offset+6] == 'R') && (received_data[offset+7] == '\r') && (received_data[offset+8] == '\n'))
		{
			module_response_error = true ;
			return true ;
		}
		offset += 1 ;
	}
	return false ;
}

bool GSM_Service_Find_SMS_Send_Start_Command(uint8_t *received_data,uint16_t data_size)
{
	uint8_t offset = 0 ;
	while(offset < data_size)
	{
		if(received_data[offset] == '>')
		{
			module_response_sms_send_start = true ;
			return true ;
		}
		offset += 1 ;
	}
	return false ;
}


bool GSM_Service_Get_OK_Status_Flag(void)
{
	return module_response_ok ;
}

