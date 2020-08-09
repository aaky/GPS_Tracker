/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2016
 * \file        Timer_Service.h
 * \brief       Timer Service
 * \author      Sameer Narkar
 * \date        27-Aug-2016
 * \section     History
 * <pre>
 *              Date        Responsible         Description
 *              20160827    Sameer Narkar		      File Created
 * </pre>
 */
/**********************************************************************/

#ifndef TIMERSERVICE_H
#define TIMERSERVICE_H
/* ------------------------------ Includes ------------------------------------ */
#include "Error_codes.h"
#include "stm32l0xx_hal.h"
#include <stdbool.h>
/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */
#define FIVE_MSEC_PRESCALER_TIMER						(0x13880)
#define PERIOD_FIVE_MSEC_TIMER							(2)
/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */
void Timer_Service_Init(void);
void Timer_Service_StartTimer(void);
void Timer_Service_StopTimer(void);

void Timer_Service_SetTimeoutState(bool state);
bool Timer_Service_GetTimeoutState(void);
/* ---------------------------------------------------------------------------- */
#endif

