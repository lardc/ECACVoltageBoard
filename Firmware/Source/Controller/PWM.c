// Header
#include "PWM.h"

// Includes
#include "Measure.h"
#include "Timer1PWM.h"
#include "math.h"
#include "DeviceObjectDictionary.h"
#include "DataTable.h"
#include "SysConfig.h"
#include "LogUtils.h"

// Variables
volatile uint32_t PWMTimerCounter = 0;
static float TransformerRatio, ActualAmplitude, TargetAmplitude, AmplitudeLimit, AmplitudeRiseStep, Kp, Ki, ErrorI;
static float VoltageStorageRMS, CurrentStorageRMS;

// Forward functions
void PWM_CacheParameters();
float PWM_GetInstantVoltageSetpoint();
float PWM_ConvertVoltageToPWM(float Voltage);

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
	// Получение мговенных значений напряжения и тока
	float Voltage = MEASURE_Voltage();
	float Current = MEASURE_Current();

	// Набор данных для расчёта действующих значений
	VoltageStorageRMS += Voltage * Voltage;
	CurrentStorageRMS += Current * Current;

	// Логика, выполняемая каждый период
	if(PWMTimerCounter == 0)
	{
		// Алгоритм нарастания уставки напряжения
		if(ActualAmplitude < TargetAmplitude)
		{
			ActualAmplitude += AmplitudeRiseStep;
			if(ActualAmplitude > TargetAmplitude)
				ActualAmplitude = TargetAmplitude;
		}

		// Расчёт и сохранение действующих значений
		float VoltageRMS = sqrtf(VoltageStorageRMS / PWM_SINE_COUNTER_MAX);
		float CurrentRMS = sqrtf(CurrentStorageRMS / PWM_SINE_COUNTER_MAX);
		VoltageStorageRMS = CurrentStorageRMS = 0;
		MU_LogRMS(0, VoltageRMS, CurrentRMS);
	}

	// Запись уставки ШИМ
	float InstantVoltage = PWM_GetInstantVoltageSetpoint();
	float PWMSetpoint = PWM_ConvertVoltageToPWM(InstantVoltage);
	MU_LogFast(InstantVoltage, PWMSetpoint, Voltage, Current);
	T1PWM_SetDutyCycle(PWMSetpoint);
}
//------------------------------------------------

float PWM_GetInstantVoltageSetpoint()
{
	return ActualAmplitude * sinf(2 * M_PI * PWMTimerCounter / PWM_SINE_COUNTER_MAX);
}
//------------------------------------------------

float PWM_ConvertVoltageToPWM(float Voltage)
{
	return Voltage / TransformerRatio / PWM_PRIMARY_VOLTAGE * T1PWM_GetPWMBase();
}
//------------------------------------------------

void PWM_CacheParameters()
{
	PWMTimerCounter = 0;
	VoltageStorageRMS = CurrentStorageRMS = 0;
	ErrorI = 0;

	Kp = (float)DataTable[REG_KP] / 1000;
	Ki = (float)DataTable[REG_KI] / 1000;

	TargetAmplitude = (float)DataTable[REG_VOLTAGE_SETPOINT] * M_SQRT2;

	TransformerRatio = (float)DataTable[REG_PWM_TRANS_RATIO] / 100;
	AmplitudeLimit = (float)DataTable[REG_PWM_OUT_VOLTAGE_LIMIT];
	AmplitudeRiseStep = (float)DataTable[REG_PWM_VOLTAGE_RISE_RATE] / PWM_SINE_FREQ;
}
//------------------------------------------------
