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
extern Int64U CONTROL_LEDTimeout;

extern volatile Int16U CONTROL_BuffRAWCurrent[VALUES_x_SIZE];
extern volatile Int16U CONTROL_BuffRAWVoltage[VALUES_x_SIZE];
extern volatile Int16U CONTROL_BuffCurrent[VALUES_x_SIZE];
extern volatile Int16U CONTROL_BuffVoltage[VALUES_x_SIZE];
extern volatile Int16U CONTROL_BuffCounterRAWCurrent;
extern volatile Int16U CONTROL_BuffCounterRAWVoltage;
extern volatile Int16U CONTROL_BuffCounterCurrent;
extern volatile Int16U CONTROL_BuffCounterVoltage;

// Functions
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_SetDeviceState(DeviceState NewState);

#endif // __CONTROLLER_H
