// Header
#include "PWM.h"

// Includes
#include "Measure.h"
#include "LowLevel.h"
#include "DataTable.h"
#include "math.h"
#include "ZwTIM.h"
#include "Delay.h"
#include "ZwDMA.h"
#include "Global.h"
#include "ZwADC.h"
#include "Controller.h"

// Defines

// Variables

// Functions
void PWM_SaveEndPoint();
void PWM_CopyRAWFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);
void PWM_CopyVoltageFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);
void PWM_CopyCurrentFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);

void PWM_SaveEndPoint()
{
	//��������� ������ � endpoints
	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC1DMABuff, (uint32_t*)&CONTROL_BuffRAWCurrent);
	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC2DMABuff, (uint32_t*)&CONTROL_BuffRAWVoltage);
	PWM_CopyVoltageFromDMAToEndPoint((uint32_t*)&ADC1DMABuff, (uint32_t*)&CONTROL_BuffCurrent);
	PWM_CopyCurrentFromDMAToEndPoint((uint32_t*)&ADC2DMABuff, (uint32_t*)&CONTROL_BuffVoltage);
}
//------------------------------------------------

void PWM_CopyRAWFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin)
{
	for(uint16_t i = 0; i < (VALUES_x_SIZE + 1); i++)
	{
		AdressEndPoin[i] = AdressDMABuff[i];
	}
}
//------------------------------------------------

void PWM_CopyVoltageFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin)
{
	double_t Resistance = 1;

	if(LL_GetStateKI_L())
	{
		Resistance = R_L;
	}
	else
	{
		if(LL_GetStateKI_M())
		{
			Resistance = R_M;
		}
		else
		{
			Resistance = R_H;
		}
	}

	for(uint16_t i = 0; i < (VALUES_x_SIZE + 1); i++)
	{
		AdressEndPoin[i] = (uint16_t)((AdressDMABuff[i] * (double_t)ADC_RESOLUTION) / Resistance);
	}
}
//------------------------------------------------

void PWM_CopyCurrentFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin)
{
	double_t KU = 1;

	if(LL_GetStateKU())
		KU = 7.6;

	for(uint16_t i = 0; i < (VALUES_x_SIZE + 1); i++)
	{
		AdressEndPoin[i] = (uint16_t)(AdressDMABuff[i] * (double_t)ADC_RESOLUTION * KU * KU_DEVIDER);
	}
}
//------------------------------------------------
