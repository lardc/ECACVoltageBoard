// Header
#include "Measure.h"

// Includes
#include "Board.h"
#include "math.h"
#include "Global.h"
#include "DataTable.h"

// Types
typedef struct __MeasureSettings
{
	float K;
	float Offset;
	float P2;
	float P1;
	float P0;
	float Rshunt;
} MeasureSettings, *pMeasureSettings;

// Variables
volatile uint16_t ADC1DMAVoltageBuffer[ADC_DMA_BUFF_SIZE] = {0};
volatile uint16_t ADC2DMACurrentBuffer[ADC_DMA_BUFF_SIZE] = {0};
static MeasureSettings VoltageSettings, CurrentSettings;

static const float ADCResolution = ((float)ADC_REF / (float)ADC_12BIT_MAX_VAL);
static const float OptTransferKoeff = 1.34;
static const float VoltageOffset = 2300;
static const float VoltMulBeforeSum = 1.33;
static const float CurMulBeforeSum = 1.8;
static const float VoltDevider = 219;
static volatile float VoltageKu;

// Functions
void MEASURE_SetCurrentRange(uint32_t Current);
void MEASURE_SetVoltageRange(uint16_t Voltage);
void MEASURE_CacheSettings(pMeasureSettings Storage, uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1,
		uint16_t RegP0);
void MEASURE_CacheVoltageSettings(uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1, uint16_t RegP0);
void MEASURE_CacheCurrentSettings(uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1, uint16_t RegP0,
		uint16_t RegShunt);

float MEASURE_Voltage();
float MEASURE_Current();
static float MEASURE_MeanSquare(volatile uint16_t *Address, uint16_t Num);
static float ReturnVoltageFromRAW(float RAW);
static float ReturnCurrentFromRAW(float RAW);

void MEASURE_SetMeasureRange(uint16_t Voltage, uint32_t Current)
{
	MEASURE_SetVoltageRange(Voltage);
	MEASURE_SetCurrentRange(Current);
}
//------------------------------------------------

void MEASURE_SetCurrentRange(uint32_t Current)
{
	if(Current <= DataTable[REG_CURRENT_RANGE1_LIMIT])
	{
		GPIO_SetState(GPIO_I_RANGE_H, false);
		GPIO_SetState(GPIO_I_RANGE_M, false);
		GPIO_SetState(GPIO_I_RANGE_L, true);
		MEASURE_CacheCurrentSettings(REG_ADC_I1_CONV_K, REG_ADC_I1_CONV_B, REG_ADC_I1_FINE_P2, REG_ADC_I1_FINE_P1,
				REG_ADC_I1_FINE_P0, REG_CURRENT_RANGE1_RES);
	}
	else if(Current <= DataTable[REG_CURRENT_RANGE2_LIMIT])
	{
		GPIO_SetState(GPIO_I_RANGE_H, false);
		GPIO_SetState(GPIO_I_RANGE_M, true);
		GPIO_SetState(GPIO_I_RANGE_L, false);
		MEASURE_CacheCurrentSettings(REG_ADC_I2_CONV_K, REG_ADC_I2_CONV_B, REG_ADC_I2_FINE_P2, REG_ADC_I2_FINE_P1,
				REG_ADC_I2_FINE_P0, REG_CURRENT_RANGE2_RES);
	}
	else
	{
		GPIO_SetState(GPIO_I_RANGE_H, true);
		GPIO_SetState(GPIO_I_RANGE_M, false);
		GPIO_SetState(GPIO_I_RANGE_L, false);
		MEASURE_CacheCurrentSettings(REG_ADC_I3_CONV_K, REG_ADC_I3_CONV_B, REG_ADC_I3_FINE_P2, REG_ADC_I3_FINE_P1,
				REG_ADC_I3_FINE_P0, REG_CURRENT_RANGE3_RES);
	}
}
//------------------------------------------------

void MEASURE_SetVoltageRange(uint16_t Voltage)
{
	if(Voltage <= DataTable[REG_VOLTAGE_RANGE1_LIMIT])
	{
		GPIO_SetState(GPIO_U_RANGE, true);
		MEASURE_CacheVoltageSettings(REG_ADC_V1_CONV_K, REG_ADC_V1_CONV_B, REG_ADC_V1_FINE_P2, REG_ADC_V1_FINE_P1,
				REG_ADC_V1_FINE_P0);
	}
	else
	{
		MEASURE_CacheVoltageSettings(REG_ADC_V2_CONV_K, REG_ADC_V2_CONV_B, REG_ADC_V2_FINE_P2, REG_ADC_V2_FINE_P1,
				REG_ADC_V2_FINE_P0);
		GPIO_SetState(GPIO_U_RANGE, false);
	}
}
//------------------------------------------------

void MEASURE_CacheSettings(pMeasureSettings Storage, uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1,
		uint16_t RegP0)
{
	Storage->K = (float)DataTable[RegK] / 1000;
	Storage->Offset = (float)((int16_t)DataTable[Offset]);
	
	Storage->P2 = (float)((int16_t)DataTable[RegP2]) / 1e6;
	Storage->P1 = (float)DataTable[RegP1] / 1000;
	Storage->P0 = (float)((int16_t)DataTable[RegP0]);
}
//------------------------------------------------

void MEASURE_CacheVoltageSettings(uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1, uint16_t RegP0)
{
	MEASURE_CacheSettings(&VoltageSettings, RegK, Offset, RegP2, RegP1, RegP0);
}
//------------------------------------------------

void MEASURE_CacheCurrentSettings(uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1, uint16_t RegP0,
		uint16_t RegShunt)
{
	MEASURE_CacheSettings(&CurrentSettings, RegK, Offset, RegP2, RegP1, RegP0);
	CurrentSettings.Rshunt = (float)DataTable[RegShunt];
}
//------------------------------------------------

float MEASURE_Voltage()
{
	return ReturnVoltageFromRAW(MEASURE_MeanSquare(ADC1DMAVoltageBuffer, ADC_DMA_BUFF_SIZE));
}
//------------------------------------------------

float MEASURE_Current()
{
	return ReturnCurrentFromRAW(MEASURE_MeanSquare(ADC2DMACurrentBuffer, ADC_DMA_BUFF_SIZE));
}
//------------------------------------------------

float MEASURE_MeanSquare(volatile uint16_t *Address, uint16_t Num)
{
	uint32_t Summ = 0;
	uint32_t Buff[ADC_DMA_BUFF_SIZE] = {0};
	uint32_t Mul = 0;
	
	for(uint16_t i = 0; i < ADC_DMA_BUFF_SIZE; i++)
	{
		Mul = (uint32_t)(*(Address + i));
		Buff[i] = (uint32_t)(Mul * Mul);
		Summ += Buff[i];
	}
	
	if(Summ == 0)
	{
		return 0;
	}
	Summ = (float)Summ / (float)ADC_DMA_BUFF_SIZE;
	return sqrtf(Summ);
}
//------------------------------------------------

float ReturnVoltageFromRAW(float RAW)
{
	float VoltageOnADC = RAW * ADCResolution;
	return ((((((VoltageOnADC * OptTransferKoeff) - VoltageOffset) / VoltMulBeforeSum) / VoltageKu) * VoltDevider)
			/ 1000); // В
}
//------------------------------------------------

float ReturnCurrentFromRAW(float RAW)
{
	float Current, Voltage;
	float VoltageOnADC = RAW * ADCResolution;
	Voltage = ((VoltageOnADC * OptTransferKoeff) - VoltageOffset) / CurMulBeforeSum;
	Current = (Voltage / 1000) / (float)Rshunt; // мкА
	return Current;
}
