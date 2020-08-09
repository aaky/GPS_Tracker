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

#ifndef GSM_H
#define GSM_H
/* ------------------------------ Includes ------------------------------------ */
#include <stdint.h>
#include "Error_codes.h"
#include <string.h>
#include <stdbool.h>
/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */

#define BASIC_AUTO_BAUD_SYNC_COMMAND				("AT\r")
#define GSM_RESET_SETTINGS_TO_DEFAULT				("ATZ\r")
#define SIM_CARD_OK_COMMAND							("AT+CCID\r")
#define GSM_SWITCH_TO_TEXT_MODE						("AT+CMGF=1\r")
#define GSM_SWITCH_TO_PDU_MODE						("AT+CMGF=0\r")
#define GSM_SEND_SMS_COMMAND						("AT+CMGS=")
#define GSM_READ_RECEIVED_MESSAGE					("AT+CMGR=")


#define GSM_FINISH_SMS_TEXT_COMMAND					(0x1A)
#define GSM_DOUBLE_QUOTES_COMMAND					(0x22)
#define GSM_READY_TO_SEND_COMMAND					(0x3E)

#define BYTES_BASIC_AUTO_BAUD_SYNC_COMMAND			(3)
#define BYTES_GSM_RESET_SETTINGS_TO_DEFAULT			(4)
#define BYTES_SIM_CARD_OK_COMMAND					(8)
#define BYTES_GSM_SWITCH_TO_TEXT_MODE				(10)
#define BYTES_GSM_SEND_SMS_COMMAND					(8)

#define VALID_SIM_CARD_NUMBER_BYTES					(20)
#define MOBILE_NUMBER_BYTES							(10)

#define MAX_GSM_MODULE_RESPONSE_DATA				(150)
/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */
typedef enum
{
	GSM_AUTOBAUD_SYNC_CMD = 0 ,
	GSM_SIM_OK_COMMAND,
	GSM_RESET_TO_DEFAULT_COMMAND,
	GSM_SWITCH_TO_TEXT_MODE_COMMAND,
	GSM_SMS_SEND_COMMAND,
	GSM_SMS_SEND_SUCCESS_RESPONSE,
	GSM_SMS_RECEIVE_COMMAND,
	GPS_GNSS_POWER_ON_COMMAND,
	GPS_GNSS_POWER_OFF_COMMAND,
	GPS_GNSS_SENTENCE_TYPE,
	GPS_GET_LOCATION_INFO_COMMAND,
	GPS_ENABLE_CONTINOUS_LOCATION_INFO,
	GPS_DISABLE_CONTINOUS_LOCATION_INFO,
}gsm_msg_type_t ;

/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */
gps_tracker_error_t GSM_Service_Init(void);
gps_tracker_error_t GSM_Service_DetectValidSimCard(void);
gps_tracker_error_t GSM_Service_ResetToDefault(void);
gps_tracker_error_t GSM_Service_SendSMS(uint8_t *message_to_be_transmitted,uint16_t size_of_data);
void GSM_Service_ReadReceivedSMS(uint8_t *received_message);

gps_tracker_error_t GSM_Service_Parse_Response(gsm_msg_type_t msg_type);

uint8_t GSM_Service_Find_New_Line_Characters(uint8_t *received_data);

bool GSM_Service_Find_OK_Response(uint8_t *received_data,uint16_t data_size);
bool GSM_Service_Find_Error_Response(uint8_t *received_data,uint16_t data_size);
bool GSM_Service_Find_SMS_Send_Start_Command(uint8_t *received_data,uint16_t data_size);
bool GSM_Service_Get_OK_Status_Flag(void);
/* ---------------------------------------------------------------------------- */



#endif
