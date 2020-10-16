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
static float TransformerRatio, Kp, Ki, ErrorI;
static float ActualSetVoltageRMS, ControlSetVoltageRMS, ControlSetVoltageMaxRMS, TargetVoltageRMS, VoltageStepRMS;
static float VoltageStorageRMS, CurrentStorageRMS;
static bool RequestSoftStop = false;

// Forward functions
void PWM_CacheParameters();
float PWM_GetInstantVoltageSetpoint();
float PWM_ConvertVoltageToPWM(float Voltage);
float PWM_GetControlAdjustment(float ActualRMSVoltage);
void PWM_SaveResultToDataTable(float Voltage, float Current);

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
	// Получение мговенных значений напряжения и тока
	float Voltage = MEASURE_Voltage();
	float Current = MEASURE_Current();

	// Набор данных для расчёта действующих значений
	VoltageStorageRMS += Voltage * Voltage;
	CurrentStorageRMS += Current * Current;

	// Логика, выполняемая каждый период
	if(PWMTimerCounter == 0)
	{
		// Расчёт и сохранение действующих значений
		float VoltageRMS = sqrtf(VoltageStorageRMS / PWM_SINE_COUNTER_MAX);
		float CurrentRMS = sqrtf(CurrentStorageRMS / PWM_SINE_COUNTER_MAX);
		VoltageStorageRMS = CurrentStorageRMS = 0;

		// Сохранение результата
		if(RequestSoftStop)
			PWM_SaveResultToDataTable(VoltageRMS, CurrentRMS);

		// Получение корректировки по завершённому периоду
		float Control = PWM_GetControlAdjustment(VoltageRMS);

		// Алгоритм нарастания уставки напряжения
		if(ActualSetVoltageRMS < TargetVoltageRMS)
		{
			ActualSetVoltageRMS += VoltageStepRMS;
			if(ActualSetVoltageRMS > TargetVoltageRMS)
				ActualSetVoltageRMS = TargetVoltageRMS;
		}

		// Задание действующего значения напряжения для следующего импульса
		ControlSetVoltageRMS = ActualSetVoltageRMS + Control;

		// Проверка насыщения выходного напряжения
		if(ControlSetVoltageRMS > ControlSetVoltageMaxRMS)
			ControlSetVoltageRMS = ControlSetVoltageMaxRMS;

		// Сохранение полученных значений
		MU_LogRMS(ActualSetVoltageRMS, ControlSetVoltageRMS, VoltageRMS, CurrentRMS);
	}

	// Расчёт, сохранение и запись уставки ШИМ
	float InstantVoltage = PWM_GetInstantVoltageSetpoint();
	float PWMSetpoint = PWM_ConvertVoltageToPWM(InstantVoltage);
	MU_LogFast(InstantVoltage, PWMSetpoint, Voltage, Current);

	// Обработка запроса остановки
	if(RequestSoftStop)
		T1PWM_Stop();
	else
		T1PWM_SetDutyCycle(PWMSetpoint);

	return RequestSoftStop;
}
//------------------------------------------------

void PWM_SaveResultToDataTable(float Voltage, float Current)
{
	DataTable[REG_VOLTAGE_RESULT] = (uint16_t)Voltage;

	uint32_t CurrentInt = (uint32_t)Current;
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

	TransformerRatio = (float)DataTable[REG_PWM_TRANS_RATIO] / 100;
	ControlSetVoltageMaxRMS = (float)DataTable[REG_PWM_OUT_VOLTAGE_LIMIT];
	VoltageStepRMS = (float)DataTable[REG_PWM_VOLTAGE_RISE_RATE] / PWM_SINE_FREQ;
}
//------------------------------------------------
