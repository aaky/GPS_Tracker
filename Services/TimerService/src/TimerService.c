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

/* ------------------------------ Includes ------------------------------------ */
#include "TimerService.h"

/* ---------------------------------------------------------------------------- */

/* ------------------ Preprocessor directives declaration --------------------- */

/* ---------------------------------------------------------------------------- */

/* ---------------------- Global Variable declaration ------------------------- */
TIM_HandleTypeDef htim2 ;
bool timer_timeout_state = false ;
/* ---------------------------------------------------------------------------- */

/* -------------------- Global static variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* -------------------- Global extern variable declaration -------------------- */

/* ---------------------------------------------------------------------------- */

/* --------------------- Function prototype defination ------------------------ */

/* ---------------------------------------------------------------------------- */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		Timer_Service_SetTimeoutState(true);
	}
}


void Timer_Service_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = FIVE_MSEC_PRESCALER_TIMER ;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = PERIOD_FIVE_MSEC_TIMER;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		//Report error
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		//Report error
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		//Report error
	}
}

void Timer_Service_StartTimer(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}

void Timer_Service_StopTimer(void)
{
	HAL_TIM_Base_Stop_IT(&htim2);
}

void Timer_Service_SetTimeoutState(bool state)
{
	timer_timeout_state = state ;
}

bool Timer_Service_GetTimeoutState(void)
{
	return timer_timeout_state ;
}



