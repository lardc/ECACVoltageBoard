// Header
#include "Measure.h"

// Includes
#include "Board.h"
#include "math.h"
#include "Global.h"
#include "DataTable.h"

// Variables
volatile uint16_t ADC1DMABuff[ADC_BUFF_SIZE] = {0};
volatile uint16_t ADC2DMABuff[ADC_BUFF_SIZE] = {0};
volatile bool MEASURE_VoltageDone = false;
volatile bool MEASURE_CurrentDone = false;
static const float ADCResolution = ((float)ADC_REF / (float)ADC_12BIT_MAX_VAL);
static const float OptTransferKoeff = 1.34;
static const float VoltageOffset = 2300;
static const float VoltMulBeforeSum = 1.33;
static const float CurMulBeforeSum = 1.8;
static const float VoltDevider = 219;

static volatile uint16_t Rshunt;
static volatile float VoltageKu;

// Functions
void MEAS_SetCurrentRange(uint32_t Current);
void MEAS_SetVoltageRange(uint16_t Voltage);
float MEAS_Voltage();
float MEAS_Current();
static float MEAS_MeanSquare(volatile uint16_t *Address, uint16_t Num);
static float ReturnVoltageFromRAW(float RAW);
static float ReturnCurrentFromRAW(float RAW);

void MEAS_SetMeasureRange(uint16_t Voltage, uint32_t Current)
{
	MEAS_SetVoltageRange(Voltage);
	MEAS_SetCurrentRange(Current);
}
//------------------------------------------------

void MEAS_SetCurrentRange(uint32_t Current)
{
	if(Current <= DataTable[REG_HW_I_RANGE_L])
	{
		GPIO_SetState(GPIO_I_RANGE_H, false);
		GPIO_SetState(GPIO_I_RANGE_M, false);
		GPIO_SetState(GPIO_I_RANGE_L, true);
		Rshunt = 3000;
	}
	else
	{
		if(Current <= DataTable[REG_HW_I_RANGE_M])
		{
			GPIO_SetState(GPIO_I_RANGE_H, false);
			GPIO_SetState(GPIO_I_RANGE_M, true);
			GPIO_SetState(GPIO_I_RANGE_L, false);
			Rshunt = 200;
		}
		else
		{
			GPIO_SetState(GPIO_I_RANGE_H, true);
			GPIO_SetState(GPIO_I_RANGE_M, false);
			GPIO_SetState(GPIO_I_RANGE_L, false);
			Rshunt = 10;
		}
	}
}
//------------------------------------------------

void MEAS_SetVoltageRange(uint16_t Voltage)
{
	if(Voltage <= DataTable[REG_HW_U_RANGE_L])
	{
		GPIO_SetState(GPIO_U_RANGE, true);
		VoltageKu = 7.0;
	}
	else
	{
		GPIO_SetState(GPIO_U_RANGE, false);
		VoltageKu = 1.0;
	}
}
//------------------------------------------------

float MEAS_Voltage()
{
	return ReturnVoltageFromRAW(MEAS_MeanSquare(ADC1DMABuff, ADC_BUFF_SIZE));
}

float MEAS_Current()
{
	return ReturnCurrentFromRAW(MEAS_MeanSquare(ADC2DMABuff, ADC_BUFF_SIZE));
}
//------------------------------------------------

float MEAS_MeanSquare(volatile uint16_t *Address, uint16_t Num)
{
	uint32_t Summ = 0;
	uint32_t Buff[ADC_BUFF_SIZE] = {0};
	uint32_t Mul = 0;

	for(uint16_t i = 0; i < (ADC_BUFF_SIZE); i++)
	{
		Mul = (uint32_t)(*(Address + i));
		Buff[i] = (uint32_t)(Mul * Mul);
		Summ += Buff[i];
	}

	if(Summ == 0)
	{
		return 0;
	}
	Summ = (float)Summ / (float)ADC_BUFF_SIZE;
	return sqrtf(Summ);
}
//------------------------------------------------

float ReturnVoltageFromRAW(float RAW)
{
	float VoltageOnADC = RAW * ADCResolution;
	return ((((((VoltageOnADC * OptTransferKoeff) - VoltageOffset) / VoltMulBeforeSum) / VoltageKu) * VoltDevider) / 1000); // В
}
//------------------------------------------------

float ReturnCurrentFromRAW(float RAW)
{
	float Current, Voltage;
	float VoltageOnADC = RAW * ADCResolution;
	Voltage = ((VoltageOnADC * OptTransferKoeff) - VoltageOffset ) / CurMulBeforeSum;
	Current = (Voltage /1000 ) / (float)Rshunt; // мкА
	return Current;
}
