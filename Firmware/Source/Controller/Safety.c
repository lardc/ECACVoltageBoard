// Header
#include "Safety.h"

// Include
#include "LowLevel.h"
#include "InitConfig.h"
#include "DataTable.h"
#include "stdinc.h"
#include "Commutation.h"
#include "Controller.h"
#include "ZwEXTI.h"
#include "DeviceObjectDictionary.h"
#include "stm32f3xx.h"

// Volatile
extern volatile DeviceState CONTROL_State;

// Forward functions
void SFTY_DisconnectAndSetStopState();
void SFTY_SwitchInterruptState(bool NewState);
void SFTY_CheckSafety();
void SFTY_SetSensState();
void SFTY_ReadSensLine();

volatile Safety SafetyState = {TRUE, {FALSE, FALSE}, {FALSE, FALSE}, {FALSE, FALSE}, {FALSE, FALSE}};

// Functions
void SFTY_CheckSafety()
{

	if(SFTY_GET_STATE_BUTTON_STOP)
	{
		SFTY_DisconnectAndSetStopState();
		SFTY_CLR_STATE_BUTTON_STOP;
	}
	else
	{
		if((CONTROL_State != DS_None) && (CONTROL_State != DS_Disabled))
		{
			if(!(LL_GetStateButtonStart()))
			{
				if(SFTY_GET_STATUS)
				{
					SFTY_ReadSensLine();
					if(SFTY_GET_STATE_SENS1 || SFTY_GET_STATE_SENS2)
					{
						SFTY_SetSensState();
						SFTY_CLR_STATE_SENS1;
						SFTY_CLR_STATE_SENS2;
						return;
					}
					else
					{
						DataTable[REG_PROBLEM] = PROBLEM_NONE;
						CONTROL_SetDeviceState(DS_SafetyEnabled);
					}
				}
				else
				{
					CONTROL_SetDeviceState(DS_Enabled);
				}

				SFTY_CLR_STATE_BUTTON_START;
				DataTable[REG_BUTTON_START] = BUTT_START_IS_PRESSED;
			}
			else
			{
				if(CONTROL_State != DS_SafetyDanger)
				{
					if(SFTY_GET_STATUS)
					{
						CONTROL_SetDeviceState(DS_SafetyEnabled);
					}
					else
					{
						CONTROL_SetDeviceState(DS_Enabled);
					}
				}
				SFTY_CLR_STATE_SENS1;
				SFTY_CLR_STATE_SENS2;
				DataTable[REG_BUTTON_START] = BUTT_START_IS_UNPRESSED;
			}
		}
	}
}
//-----------------------------------------------

void SFTY_DisconnectAndSetStopState()
{
	CONTROL_SetDeviceState(DS_SafetyDanger);
	DataTable[REG_PROBLEM] = PROBLEM_BUTTON_STOP;
	SafetyState.StateButton.Stop = false;
	COMM_DisconnectAllRelay();
}
//-----------------------------------------------

void SFTY_SetSensState()
{
	CONTROL_SetDeviceState(DS_SafetyDanger);
	DataTable[REG_PROBLEM] = PROBLEM_SENS;
}
//-----------------------------------------------
void SFTY_ReadSensLine()
{
	SFTY_SET_STATE_SENS1 = !LL_GetStateSens1();
	SFTY_SET_STATE_SENS2 = !LL_GetStateSens2();
	SFTY_SET_STATE_BUTTON_STOP = !LL_GetStateButtonStop();
}
//-----------------------------------------------

void SFTY_SwitchInterruptState(bool NewState)
{
	if(NewState)
	{
		//	EXTI_Config(EXTI_PB, EXTI_9, BOTH_TRIG, 0);	// GPIO_KEY_START
		EXTI_Config(EXTI_PB, EXTI_6, BOTH_TRIG, 0);	// GPIO_SFTY_2
		EXTI_Config(EXTI_PB, EXTI_7, BOTH_TRIG, 0);	// GPIO_SFTY_1
		EXTI_EnableInterrupt(EXTI9_5_IRQn, 0, true);
	}
	else
	{
		EXTI->IMR |= 0 << EXTI_6;
		EXTI->IMR |= 0 << EXTI_7;
//		EXTI->IMR |= 0 << EXTI_9;
	}
}
//------------------------------------------
