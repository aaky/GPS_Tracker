/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2015 Leaf Technologies
 * \file        Watchdog_Service.c
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

#ifndef WATCHDOG_SERVICE_H
#define WATCHDOG_SERVICE_H

#include "Error_codes.h"

/* This macro can disable watchdog timer while debugging code in development */
#define WATCHDOG_ENABLE								//Uncomment this macro for OTA or factory release

/* Generating watchdog reset after 7 seconds if system stucks */
#define WATCHDOG_LSI_RC_FREQ							(40*1000)

/* User can modify this macro for adjusting watchdog timer timeout in seconds */
/* Note : Maximum timeout for current PRESCALAR IWDG_PRESCALER_128 is 13 seconds maximum */
#define WATCHDOG_RESET_TIMEOUT_SECONDS					(7)

#define WATCHDOG_MAX_RELOAD_COUNTER(PRESCALAR)			((WATCHDOG_LSI_RC_FREQ / PRESCALAR) * WATCHDOG_RESET_TIMEOUT_SECONDS )	

//leaf_error_t Watchdog_Service_Init(void);
//leaf_error_t Watchdog_Service_TimerRefresh(void);
//leaf_error_t Watchdog_Service_TimerStart(void);
//leaf_error_t Watchdog_Service_GetResetReason(void);
//void Watchdog_Service_ResetNRF(void);

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
