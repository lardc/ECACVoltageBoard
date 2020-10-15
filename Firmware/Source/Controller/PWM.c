// Header
#include "PWM.h"

// Includes
#include "LowLevel.h"
#include "Measure.h"
#include "ZwDMA.h"
#include "Global.h"
#include "ZwADC.h"
#include "Controller.h"
#include "Timer1PWM.h"
#include "math.h"
#include "DeviceObjectDictionary.h"
#include "DataTable.h"
#include "Board.h"
#include "Delay.h"

// Defines
#define PWM_MAX_STEP_PWM 400

// Typedef
typedef struct __Error
{
	float Summ;
	float Now;
	float Last;
} Error;

typedef struct __Measure
{
	float Target;
	float Now;
	uint32_t Set;
} Measure;

typedef struct __Koefficient
{
	float Q;
	float K;
} Koefficient;

typedef struct __KoefficientStr
{
	Koefficient P;
	Koefficient I;

} KoefficientStr;

typedef struct __SinControl
{
	Measure Voltage;
	Measure Current;
	Error Error;
	KoefficientStr	PI;
	float Duty;
	uint16_t Point;
	int16_t PWMRAW[PWM_MAX_STEP_PWM];
} SinControl;

volatile SinControl Regulator = {0};

// Variables
static const float Steper = M_PI * (2 * (1 / (float)PWM_MAX_STEP_PWM));

// Functions
void PWM_SinRegulation();
void PWM_StepUpdate();
void PWM_UpdateMeasValue();
void PWM_ChekEndOfSignal();
void PWM_UpdateKoeff();
void PWM_CalculateVoltageInPoint();
void PWM_CalculateDuty();

void PWM_SignalStart(uint16_t Voltage, uint32_t Current)
{
	Regulator.Voltage.Set = Voltage;
	Regulator.Current.Set = Current;
	PWM_UpdateKoeff();
	MEASURE_SetMeasureRange(Voltage, Current);
	PWM_SinRegulation();
	ADC_SamplingStart(ADC1);
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
	/*
	PWM_UpdateMeasValue();

	PWM_CalculateVoltageInPoint();

	PWM_ChekEndOfSignal();
	PWM_CalculateDuty();
	T1PWM_SetDutyCycle(Regulator.Duty);
	if(CONTROL_BuffCounterVoltage < VALUES_x_SIZE)
	{
		CONTROL_BuffCounterVoltage++;
	}
	else
	{
		CONTROL_BuffCounterVoltage = 0;
	}

	PWM_StepUpdate();
	*/
	GPIO_SetState(GPIO_LED_EXT, false);
}

//------------------------------------------------
void PWM_StepUpdate()
{
	if(Regulator.Point >= (PWM_MAX_STEP_PWM - 1))
	{
		Regulator.Point = 0;
	}
	else
	{
		Regulator.Point++;
	}
}
//------------------------------------------------

void PWM_UpdateMeasValue()
{
	Regulator.Voltage.Now = MEASURE_Voltage();
	Regulator.Current.Now = MEASURE_Current();
}
//------------------------------------------------

void PWM_ChekEndOfSignal()
{
	if(Regulator.Point == 0)
	{
		Regulator.Error.Now = 0;
	}
	else
	{
		Regulator.Error.Now = Regulator.Voltage.Target - Regulator.Voltage.Now;
	}
}
//------------------------------------------------

void PWM_UpdateKoeff()
{
	Regulator.PI.P.K = (float)DataTable[REG_KP] / 1000;
	Regulator.PI.I.K = (float)DataTable[REG_KI] / 1000;
}
//------------------------------------------------

void PWM_ResetDataOut()
{
	T1PWM_SetDutyCycle(0);
}
//------------------------------------------------

void PWM_CalculateVoltageInPoint()
{
	Regulator.Voltage.Target = Regulator.Voltage.Set * sinf(Steper * Regulator.Point);
}
//------------------------------------------------

void PWM_CalculateDuty()
{
	Regulator.PI.P.Q = Regulator.Error.Now * Regulator.PI.P.K;
	Regulator.PI.I.Q += Regulator.Error.Now * Regulator.PI.I.K;

	Regulator.Error.Last = Regulator.Error.Now;
	Regulator.Error.Summ += Regulator.Error.Last;

	Regulator.Duty = Regulator.PI.P.Q + Regulator.PI.I.Q;
}
//------------------------------------------------
