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

// Defines
#define PWM_MAX_STEP_PWM 8

// Typedef
typedef struct __Error
{
	double Summ;
	double Now;
	double Last;
} Error;

typedef struct __Measure
{
	double Target;
	double Now;
	uint32_t Set;
} Measure;

typedef struct __Koefficient
{
	double Q;
	double K;
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
static const double Steper = M_PI * (2 * (1 / (double)PWM_MAX_STEP_PWM));

// Functions
static void PWM_ResetDataOut();
//static void PWM_SaveEndPoint();
void PWM_CopyRAWFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);
void PWM_CopyVoltageFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);
void PWM_CopyCurrentFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);
void PWM_SinRegulation();
static void PWM_StepUpdate();
static void PWM_UpdateMeasValue();
static void PWM_ChekEndOfSignal();
static void PWM_UpdateKoeff();
static void PWM_CalculateVoltageInPoint();
static void PWM_CalculateDuty();

void PWM_SignalStart(uint16_t Voltage, uint32_t Current)
{
	Regulator.Voltage.Set = Voltage;
	Regulator.Current.Set = Current;
	PWM_ResetDataOut();
	MEAS_SetMeasureRange(Voltage, Current);
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
	PWM_UpdateMeasValue();
	PWM_CalculateVoltageInPoint();
	PWM_UpdateKoeff();
	PWM_ChekEndOfSignal();
	PWM_CalculateDuty();
	T1PWM_SetDutyCycle(Regulator.Duty);
	PWM_StepUpdate();
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
	Regulator.Voltage.Now = MEAS_Voltage();
	Regulator.Current.Now = MEAS_Current();
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
	Regulator.PI.P.K = (double)DataTable[REG_Kp] / 1000;
	Regulator.PI.I.K = (double)DataTable[REG_Ki] / 1000;
}
//------------------------------------------------

void PWM_ResetDataOut()
{
	T1PWM_SetDutyCycle(0);
}
//------------------------------------------------

/*void PWM_SaveEndPoint()
{
	//��������� ������ � endpoints
	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC1DMABuff, (uint32_t*)&CONTROL_BuffRAWCurrent);
	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC2DMABuff, (uint32_t*)&CONTROL_BuffRAWVoltage);
	PWM_CopyVoltageFromDMAToEndPoint((uint32_t*)&ADC1DMABuff, (uint32_t*)&CONTROL_BuffCurrent);
	PWM_CopyCurrentFromDMAToEndPoint((uint32_t*)&ADC2DMABuff, (uint32_t*)&CONTROL_BuffVoltage);
}*/
//------------------------------------------------

void PWM_CopyRAWFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin)
{
	for(uint16_t i = 0; i < (VALUES_x_SIZE + 1); i++)
	{
		AdressEndPoin[i] = AdressDMABuff[i];
	}
}

//------------------------------------------------

void PWM_CalculateVoltageInPoint()
{
	Regulator.Voltage.Target = Regulator.Voltage.Set * sin(Steper * Regulator.Point);
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
