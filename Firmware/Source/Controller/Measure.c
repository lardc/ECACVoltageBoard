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

// Forward functions
void MEASURE_SetCurrentRange(uint32_t Current);
void MEASURE_SetVoltageRange(uint16_t Voltage);
void MEASURE_CacheSettings(pMeasureSettings Storage, uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1,
		uint16_t RegP0);
void MEASURE_CacheVoltageSettings(uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1, uint16_t RegP0);
void MEASURE_CacheCurrentSettings(uint16_t RegK, uint16_t Offset, uint16_t RegP2, uint16_t RegP1, uint16_t RegP0,
		uint16_t RegShunt);
float MEASURE_ArrayToValue(pMeasureSettings Storage, uint16_t *Data, uint16_t DataLen);

// Functions
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

	Storage->Rshunt = 0;
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

float MEASURE_ArrayToValue(pMeasureSettings Storage, uint16_t *Data, uint16_t DataLen)
{
	// Рассчёт среднего
	float tmp = 0;
	for(uint8_t i = 0; i < DataLen; ++i)
		tmp += (float)Data[i];
	tmp /= DataLen;

	// Пересчёт тиков в милливольты
	tmp = (tmp * ADC_REF_VOLTAGE / ADC_RESOLUTION + Storage->Offset) * Storage->K;

	// Для канала тока - пересчёт в ток
	if(Storage->Rshunt != 0)
		tmp /= Storage->Rshunt;

	// Тонкая корректировка
	return tmp * tmp * Storage->P2 + tmp * Storage->P1 + Storage->P0;
}
//------------------------------------------------

float MEASURE_Voltage()
{
	return MEASURE_ArrayToValue(&VoltageSettings, (uint16_t *)ADC1DMAVoltageBuffer, ADC_DMA_BUFF_SIZE);
}
//------------------------------------------------

float MEASURE_Current()
{
	return MEASURE_ArrayToValue(&CurrentSettings, (uint16_t *)ADC2DMACurrentBuffer, ADC_DMA_BUFF_SIZE);
}
//------------------------------------------------
