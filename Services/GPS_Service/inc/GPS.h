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

#ifndef GPS_H
#define GPS_H
/* ------------------------------ Includes ------------------------------------ */
#include <stdint.h>
#include "Error_codes.h"
#include <string.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */
#define GPS_TURN_ON_GNSS							("AT+CGNSPWR=1\r")
#define GPS_TURN_OFF_GNSS							("AT+CGNSPWR=0\r")
#define GPS_SET_TYPE_NMEA_SENTENCE					("AT+CGNSSEQ=")
#define GPS_SET_RMC_TYPE_NMEA_SENTENCE				("RMC")
#define GPS_GET_LOCATION_INFO						("AT+CGNSINF\r")
#define GPS_GET_CONTINOUS_LOCATION_INFO				("AT+CGNSURC=5\r")
#define GPS_DISABLE_GET_CONTINOUS_LOCATION_INFO		("AT+CGNSURC=0\r")

//Change this parameter as per application requirement
#define GPS_CONTINOUS_GPS_DATA_RECEPTION_INTERVAL	("5\r")


#define BYTES_GPS_TURN_ON_GNSS								(13)
#define BYTES_GPS_TURN_OFF_GNSS								(13)
#define BYTES_GPS_SET_TYPE_NMEA_SENTENCE					(11)
#define BYTES_GPS_SET_RMC_TYPE_NMEA_SENTENCE				(3)
#define BYTES_GPS_GET_LOCATION_INFO							(11)
#define BYTES_GPS_GET_CONTINOUS_LOCATION_INFO				(13)
#define BYTES_GPS_DISABLE_GET_CONTINOUS_LOCATION_INFO		(13)
#define BYTES_GPS_CONTINOUS_GPS_DATA_RECEPTION_INTERVAL		(2)

#define GPS_FIX_BYTE_OFFSET									(25)
#define GPS_URC_FIX_BYTE_OFFSET								(11)
#define GPS_LATTITUDE_INFO_OFFSET							(46)
#define GPS_URC_LATTITUDE_INFO_OFFSET						(35)

#define GPS_LATTITUDE_INFO_BYTES							(9)
#define GPS_LONGITUDE_INFO_BYTES							(9)
/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */

/* ---------------------------------------------------------------------------- */

gps_tracker_error_t GPS_Service_Init(void);
gps_tracker_error_t GPS_Service_DeInit(void);
gps_tracker_error_t GPS_Service_GetLocationInfo(void);
gps_tracker_error_t GPS_Service_CheckGPSFix(void);
gps_tracker_error_t GPS_Service_EnableContinousGPSData(void);
gps_tracker_error_t GPS_Service_DisableContinousGPSData(void);

void GPS_Service_GetLattitudeData(uint8_t *lattitude_data,uint8_t *offset);
void GPS_Service_SetLattitudeData(uint8_t *lattitude_data,uint8_t offset);
void GPS_Service_GetLongitudeData(uint8_t *longitude_data,uint8_t *offset);
void GPS_Service_SetLongitudeData(uint8_t *longitude_data,uint8_t offset);

#endif
