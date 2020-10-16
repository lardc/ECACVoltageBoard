#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
#include "stdinc.h"
#include "Global.h"

// Types
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Ready = 3,
	DS_InProcess = 4
} DeviceState;

// Variables
extern volatile Int64U CONTROL_TimeCounter;

extern volatile Int16U CONTROL_VSetFast[];
extern volatile Int16U CONTROL_PWMSetFast[];
extern volatile Int16U CONTROL_VResultFast[];
extern volatile Int16U CONTROL_IResultFast[];
extern volatile Int16U CONTROL_VSetRMS[];
extern volatile Int16U CONTROL_VControlRMS[];
extern volatile Int16U CONTROL_VResultRMS[];
extern volatile Int16U CONTROL_IResultRMS[];

extern volatile Int16U CONTROL_CounterFast;
extern volatile Int16U CONTROL_CounterRMS;

// Functions
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_ProcessPWMStop(uint16_t Problem);

#endif // __CONTROLLER_H
