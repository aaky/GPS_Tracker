/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2016
 * \file        GPS.h
 * \brief       Initialization and use of GPS Pheripheral
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
#include "GPS.h"
#include "UART_Service.h"
#include "GSM.h"
/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */
#define MAX_GPS_DATA_TRANSMIT_RECEIVE					(100)
/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */
uint8_t gps_transmit_data[MAX_GPS_DATA_TRANSMIT_RECEIVE] ;

uint8_t gps_lattitude_data[GPS_LATTITUDE_INFO_BYTES] ;
uint8_t gps_longitude_data[GPS_LONGITUDE_INFO_BYTES] ;
/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */
static uint8_t current_offset_lattitude ;
static uint8_t current_offset_longitude ;
/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */
extern bool gps_communication_fixed ;
/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */

/* ---------------------------------------------------------------------------- */

gps_tracker_error_t GPS_Service_Init(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)GPS_TURN_ON_GNSS,BYTES_GPS_TURN_ON_GNSS);
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
		error = GSM_Service_Parse_Response(GPS_GNSS_POWER_ON_COMMAND);
		if(error != GPS_TRACKER_SUCCESS)
		{
			//Report error
			return error ;
		}
		else
		{
			memset(gps_transmit_data,0,MAX_GPS_DATA_TRANSMIT_RECEIVE);
			memcpy(gps_transmit_data,(uint8_t*)GPS_SET_TYPE_NMEA_SENTENCE,BYTES_GPS_SET_TYPE_NMEA_SENTENCE);
			gps_transmit_data[BYTES_GPS_SET_TYPE_NMEA_SENTENCE] = GSM_DOUBLE_QUOTES_COMMAND ;
			memcpy(&gps_transmit_data[BYTES_GPS_SET_TYPE_NMEA_SENTENCE+1],(uint8_t*)GPS_SET_RMC_TYPE_NMEA_SENTENCE
					,BYTES_GPS_SET_RMC_TYPE_NMEA_SENTENCE);
			gps_transmit_data[BYTES_GPS_SET_TYPE_NMEA_SENTENCE+1+BYTES_GPS_SET_RMC_TYPE_NMEA_SENTENCE] = GSM_DOUBLE_QUOTES_COMMAND ;
			gps_transmit_data[BYTES_GPS_SET_TYPE_NMEA_SENTENCE+2+BYTES_GPS_SET_RMC_TYPE_NMEA_SENTENCE] = '\r' ;
			
			error = UART_Service_Transmit_Data(gps_transmit_data,
											BYTES_GPS_SET_TYPE_NMEA_SENTENCE+BYTES_GPS_SET_RMC_TYPE_NMEA_SENTENCE+3);
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
				error = GSM_Service_Parse_Response(GPS_GNSS_SENTENCE_TYPE);
				return error ;
			}
		}
	}
}	

gps_tracker_error_t GPS_Service_DeInit(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)GPS_TURN_OFF_GNSS,BYTES_GPS_TURN_OFF_GNSS);
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
		error = GSM_Service_Parse_Response(GPS_GNSS_POWER_ON_COMMAND);
		return error ;
	}
}



gps_tracker_error_t GPS_Service_GetLocationInfo(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)GPS_GET_LOCATION_INFO,BYTES_GPS_GET_LOCATION_INFO);
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
		error = GSM_Service_Parse_Response(GPS_GET_LOCATION_INFO_COMMAND);
		return error ;
	}
}	


gps_tracker_error_t GPS_Service_CheckGPSFix(void)
{
	return gps_communication_fixed == true ? GPS_COMMUNICATION_FIXED : GPS_COMMUNICATION_NOT_FIXED ;
}

gps_tracker_error_t GPS_Service_EnableContinousGPSData(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)GPS_GET_CONTINOUS_LOCATION_INFO,BYTES_GPS_GET_CONTINOUS_LOCATION_INFO);
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
		error = GSM_Service_Parse_Response(GPS_ENABLE_CONTINOUS_LOCATION_INFO) ;
		return error ;
	}
}

gps_tracker_error_t GPS_Service_DisableContinousGPSData(void)
{
	gps_tracker_error_t error ;
	error = UART_Service_Transmit_Data((uint8_t*)GPS_DISABLE_GET_CONTINOUS_LOCATION_INFO,BYTES_GPS_DISABLE_GET_CONTINOUS_LOCATION_INFO);
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
		error = GSM_Service_Parse_Response(GPS_DISABLE_CONTINOUS_LOCATION_INFO) ;
		return error ;
	}
}


void GPS_Service_GetLattitudeData(uint8_t *lattitude_data,uint8_t *offset)
{
	for(uint8_t temp = 0 ; temp <= current_offset_lattitude ; temp++)
	{
		lattitude_data[temp] = gps_lattitude_data[temp] ;
	}
	*offset = current_offset_lattitude ;
}

void GPS_Service_SetLattitudeData(uint8_t *lattitude_data,uint8_t offset)
{
	for(uint8_t temp = 0 ; temp <= offset ; temp++)
	{
		gps_lattitude_data[temp] = lattitude_data[temp] ;
	}
	current_offset_lattitude = offset ;
}

void GPS_Service_GetLongitudeData(uint8_t *longitude_data,uint8_t *offset)
{
	for(uint8_t temp = 0 ; temp <= current_offset_longitude ; temp++)
	{
		longitude_data[temp] = gps_longitude_data[temp] ;
	}
	*offset = current_offset_longitude ;
}

void GPS_Service_SetLongitudeData(uint8_t *longitude_data,uint8_t offset)
{
	for(uint8_t temp = 0 ; temp <= offset ; temp++)
	{
		gps_longitude_data[temp] = longitude_data[temp] ;
	}
	current_offset_longitude = offset ;
}



