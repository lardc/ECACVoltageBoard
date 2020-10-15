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

// Variables
volatile uint32_t PWMTimerCounter = 0;
static float TargetValue, Kp, Ki, ErrorI;
static float TransformerRatio, TransformerPrimVoltage;

// Forward functions
void PWM_CacheParameters();

// Functions
void PWM_SignalStart(uint16_t Voltage, uint32_t Current)
{
	PWM_CacheParameters();
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
	float VoltageSetpoint = TargetValue * sinf(2 * M_PI * PWMTimerCounter / PWM_SINE_COUNTER_MAX);
}
//------------------------------------------------

void PWM_ApplyControl(float Voltage)
{

}
//------------------------------------------------

void PWM_CacheParameters()
{
	ErrorI = 0;

	TransformerPrimVoltage = (float)DataTable[REG_PWM_PRIM_VOLTAGE];
	TransformerRatio = (float)DataTable[REG_PWM_TRANS_RATIO] / 100;

	Kp = (float)DataTable[REG_KP] / 1000;
	Ki = (float)DataTable[REG_KI] / 1000;
}
//------------------------------------------------
