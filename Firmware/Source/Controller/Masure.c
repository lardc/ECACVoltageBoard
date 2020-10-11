// Header
#include "Measure.h"

// Includes
#include "Board.h"
#include "math.h"
#include "Global.h"

// Variables
volatile uint16_t ADC1DMABuff[ADC_BUFF_SIZE] = {0};
volatile uint16_t ADC2DMABuff[ADC_BUFF_SIZE] = {0};
volatile bool MEASURE_VoltageDone = false;
volatile bool MEASURE_CurrentDone = false;
static const float ADCResolution = ((float)ADC_12BIT_MAX_VAL / (float)ADC_REF);
static volatile uint16_t Rshunt;
static volatile float VoltageKu;

// Functions
void MEAS_SetCurrentRange(uint32_t Current);
void MEAS_SetVoltageRange(uint16_t Voltage);
double MEAS_Voltage();
double MEAS_Current();
static double MEAS_MeanSquare(volatile uint16_t *Address, uint16_t Num);
static double ReturnVoltageFromRAW(double RAW);
static double ReturnCurrentFromRAW(double RAW);

void MEAS_SetMeasureRange(uint16_t Voltage, uint32_t Current)
{
	MEAS_SetVoltageRange(Voltage);
	MEAS_SetCurrentRange(Current);
}
//------------------------------------------------

void MEAS_SetCurrentRange(uint32_t Current)
{
	if(Current <= HW_I_RANGE_L)
	{
		GPIO_SetState(GPIO_I_RANGE_H, false);
		GPIO_SetState(GPIO_I_RANGE_M, false);
		GPIO_SetState(GPIO_I_RANGE_L, true);
		Rshunt = 3000;
	}
	else
	{
		if(Current <= HW_I_RANGE_M)
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
	if(Voltage <= HW_U_RANGE_L)
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

double MEAS_Voltage()
{
	return ReturnVoltageFromRAW(MEAS_MeanSquare(ADC1DMABuff, ADC_BUFF_SIZE));
}

double MEAS_Current()
{
	return ReturnCurrentFromRAW(MEAS_MeanSquare(ADC2DMABuff, ADC_BUFF_SIZE));
}
//------------------------------------------------

double MEAS_MeanSquare(volatile uint16_t *Address, uint16_t Num)
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
	Summ = (double)Summ / (double)ADC_BUFF_SIZE;
	return sqrt(Summ);
}
//------------------------------------------------

double ReturnVoltageFromRAW(double RAW)
{
	double OptTransferKoeff = 1.34;
	double Offset = 2.34;
	double MulMeforeSum = 1.33;
	double VoltageDevider = 219;
	double VoltageOnADC = RAW * ADCResolution;

	return (((((VoltageOnADC * OptTransferKoeff) - Offset ) / MulMeforeSum) / 	VoltageKu ) * VoltageDevider);
}
//------------------------------------------------

double ReturnCurrentFromRAW(double RAW)
{
	float Current = 0;
	float Voltage = 0;
	double OptTransferKoeff = 1.34;
	double Offset = 2.34;
	double MulMeforeSum = 1.8;
	double VoltageOnADC = RAW * ADCResolution;

	Voltage = ((VoltageOnADC * OptTransferKoeff) - Offset ) / MulMeforeSum;
	Current = Voltage / Rshunt;

	return Current;
}
