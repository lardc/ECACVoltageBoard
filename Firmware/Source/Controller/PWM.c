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

// Types
typedef struct __VIPair
{
	float Voltage;
	float Current;
} VIPair, pVIPair;

// Variables
volatile uint32_t PWMTimerCounter = 0;
static float TransformerRatio, Kp, Ki, ErrorI;
static float ActualSetVoltageRMS, ControlSetVoltageRMS, ControlSetVoltageMaxRMS, TargetVoltageRMS, VoltageStepRMS;
static float VoltageStorageRMS, CurrentStorageRMS;
static float CurrentLimitRMS;
static bool RequestSoftStop = false;

// Forward functions
void PWM_CacheParameters();
float PWM_GetInstantVoltageSetpoint();
float PWM_ConvertVoltageToPWM(float Voltage);
float PWM_GetControlAdjustment(float ActualRMSVoltage);
void PWM_SaveResultToDataTable(VIPair Pair);
VIPair PWM_GetMeasureData();
void PWM_AddToRMS(VIPair Pair);
VIPair PWM_CalculateRMSValue();
void PWM_ProcessPeriodRegulation(uint16_t *Problem);
void PWM_ProcessInstantPWMOutput(VIPair Pair);

// Functions
void PWM_SignalStart()
{
	T1PWM_Start();
}
//------------------------------------------------

void PWM_SignalStop()
{
	RequestSoftStop = true;
}
//------------------------------------------------

bool PWM_SinRegulation(uint16_t *Problem)
{
	*Problem = PROBLEM_NONE;
	VIPair Sample = PWM_GetMeasureData();

	// Защита от КЗ
	if(Sample.Current > MEASURE_GetCurrentPeakLimit())
	{
		*Problem = PROBLEM_INSTANT_OVERCURRENT;
		T1PWM_Stop();
		return true;
	}

	PWM_AddToRMS(Sample);
	PWM_ProcessPeriodRegulation(Problem);
	PWM_ProcessInstantPWMOutput(Sample);

	return RequestSoftStop;
}
//------------------------------------------------

void PWM_SaveResultToDataTable(VIPair Pair)
{
	DataTable[REG_VOLTAGE_RESULT] = (uint16_t)Pair.Voltage;

	uint32_t CurrentInt = (uint32_t)Pair.Current;
	DataTable[REG_CURRENT_RESULT] = CurrentInt;
	DataTable[REG_CURRENT_RESULT_32] = CurrentInt >> 16;
}
//------------------------------------------------

float PWM_GetControlAdjustment(float ActualRMSVoltage)
{
	// Регулятор
	float Error = ActualSetVoltageRMS - ActualRMSVoltage;

	// Если интегральная составляющая задана
	if(Ki)
	{
		ErrorI += Error;
		// Проверка насыщения интегральной ошибки
		if(fabsf(ErrorI) > REGULATOR_I_ERR_SAT)
			ErrorI = (ErrorI > 0) ? REGULATOR_I_ERR_SAT : -REGULATOR_I_ERR_SAT;
	}

	return Error * Kp + ErrorI * Ki;
}
//------------------------------------------------

void PWM_ProcessPeriodRegulation(uint16_t *Problem)
{
	if(PWMTimerCounter == 0)
	{
		VIPair ValuesRMS = PWM_CalculateRMSValue();

		// Сохранение результата при остановке
		if(RequestSoftStop)
			PWM_SaveResultToDataTable(ValuesRMS);

		// Получение корректировки по завершённому периоду
		float Control = PWM_GetControlAdjustment(ValuesRMS.Voltage);

		// Алгоритм нарастания уставки напряжения
		if(ActualSetVoltageRMS < TargetVoltageRMS)
		{
			ActualSetVoltageRMS += VoltageStepRMS;
			if(ActualSetVoltageRMS > TargetVoltageRMS)
				ActualSetVoltageRMS = TargetVoltageRMS;
		}

		// Задание действующего значения напряжения для следующего импульса
		ControlSetVoltageRMS = ActualSetVoltageRMS + Control;

		// Проверка условий остановки формирования
		// Проверка насыщения выходного напряжения
		if(ControlSetVoltageRMS > ControlSetVoltageMaxRMS)
		{
			*Problem = PROBLEM_OUTPUT_SATURATION;
			RequestSoftStop = true;
		}
		// Проверка превышения действующего значения тока
		else if(ValuesRMS.Current > CurrentLimitRMS)
		{
			*Problem = PROBLEM_RMS_OVER_CURRENT;
			RequestSoftStop = true;
		}

		// Сохранение полученных значений
		MU_LogRMS(ActualSetVoltageRMS, ControlSetVoltageRMS, ValuesRMS.Voltage, ValuesRMS.Current);
	}
}
//------------------------------------------------

void PWM_ProcessInstantPWMOutput(VIPair Pair)
{
	// Расчёт, сохранение и запись уставки ШИМ
	float InstantVoltage = PWM_GetInstantVoltageSetpoint();
	float PWMSetpoint = PWM_ConvertVoltageToPWM(InstantVoltage);
	MU_LogFast(InstantVoltage, PWMSetpoint, Pair.Voltage, Pair.Current);

	// Обработка запроса остановки
	if(RequestSoftStop)
		T1PWM_Stop();
	else
		T1PWM_SetDutyCycle(PWMSetpoint);
}
//------------------------------------------------

float PWM_GetInstantVoltageSetpoint()
{
	return ControlSetVoltageRMS * M_SQRT2 * sinf(2 * M_PI * PWMTimerCounter / PWM_SINE_COUNTER_MAX);
}
//------------------------------------------------

float PWM_ConvertVoltageToPWM(float Voltage)
{
	return Voltage / TransformerRatio / PWM_PRIMARY_VOLTAGE * T1PWM_GetPWMBase();
}
//------------------------------------------------

VIPair PWM_GetMeasureData()
{
	VIPair Result;
	Result.Voltage = MEASURE_Voltage();
	Result.Current = MEASURE_Current();
	return Result;
}
//------------------------------------------------

void PWM_AddToRMS(VIPair Pair)
{
	VoltageStorageRMS += Pair.Voltage * Pair.Voltage;
	CurrentStorageRMS += Pair.Current * Pair.Current;
}
//------------------------------------------------

VIPair PWM_CalculateRMSValue()
{
	VIPair Result;
	Result.Voltage = sqrtf(VoltageStorageRMS / PWM_SINE_COUNTER_MAX);
	Result.Current = sqrtf(CurrentStorageRMS / PWM_SINE_COUNTER_MAX);
	VoltageStorageRMS = CurrentStorageRMS = 0;
	return Result;
}
//------------------------------------------------

void PWM_CacheParameters()
{
	RequestSoftStop = false;

	PWMTimerCounter = 0;
	ActualSetVoltageRMS = ControlSetVoltageRMS = 0;
	VoltageStorageRMS = CurrentStorageRMS = 0;
	ErrorI = 0;

	Kp = (float)DataTable[REG_KP] / 1000;
	Ki = (float)DataTable[REG_KI] / 1000;

	TargetVoltageRMS = (float)DataTable[REG_VOLTAGE_SETPOINT];
	CurrentLimitRMS = (float)(((uint32_t)DataTable[REG_CURRENT_SETPOINT_32] << 16) | DataTable[REG_CURRENT_SETPOINT]);

	TransformerRatio = (float)DataTable[REG_PWM_TRANS_RATIO];
	ControlSetVoltageMaxRMS = (float)DataTable[REG_PWM_OUT_VOLTAGE_LIMIT];
	VoltageStepRMS = (float)DataTable[REG_PWM_VOLTAGE_RISE_RATE] / PWM_SINE_FREQ;
}
//------------------------------------------------
