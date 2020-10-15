// Header
#include "PWM.h"

// Includes
#include "Measure.h"
#include "Global.h"
#include "Timer1PWM.h"
#include "math.h"
#include "DeviceObjectDictionary.h"
#include "DataTable.h"
#include "Board.h"
#include "Delay.h"

// Types
typedef struct __RegulatorSettings
{
	float TargetValue;
	float TargetValuePrev;
	float Kp;
	float Ki;
	float ErrorI;
	float Control;
} RegulatorSettings, *pRegulatorSettings;

// Variables
volatile uint32_t PWMTimerCounter = 0;


void PWM_SignalStart(uint16_t Voltage, uint32_t Current)
{
	T1PWM_Start();
}
//------------------------------------------------

void PWM_SignalStop()
{
	T1PWM_Stop();
}
//------------------------------------------------

void PWM_SinRegulation()
{
	GPIO_SetState(GPIO_LED_EXT, true);
	DELAY_US(5);
	GPIO_SetState(GPIO_LED_EXT, false);
}

//------------------------------------------------
