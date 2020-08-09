/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2016
 * \file        Error_codes.h
 * \brief       Error Code Logging service
 * \author      Sameer Narkar
 * \date        27-Aug-2016
 * \section     History
 * <pre>
 *              Date        Responsible         Description
 *              20160827    Sameer Narkar		      File Created
 * </pre>
 */
/**********************************************************************/

#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum
{
	GPS_TRACKER_SUCCESS,
	UART_INIT_ERROR,
	UART_TRANSMIT_DATA_ERROR,
	UART_RECEIVE_DATA_ERROR,
	GSM_MODULE_WRONG_RESPONSE,
	GSM_MODULE_ALREADY_IN_TEXT_MODE,
	GPS_COMMUNICATION_FIXED,
	GPS_COMMUNICATION_NOT_FIXED,
}gps_tracker_error_t ;
/* ------------------------------ Includes ------------------------------------ */

/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */

/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */

/* ---------------------------------------------------------------------------- */


#endif
