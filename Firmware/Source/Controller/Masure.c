// Header
#include "Measure.h"

// Includes
#include "Global.h"
#include "Board.h"

// Variables
void MEAS_SetCurrentRange(uint16_t Current);
void MEAS_SetVoltageRange(uint16_t Voltage);

// Functions
void MEAS_SetMeasureRange(uint16_t Voltage, uint16_t Current)
{
	MEAS_SetVoltageRange(Voltage);
	MEAS_SetCurrentRange(Current);
}

void MEAS_SetCurrentRange(uint16_t Current)
{
	if(Current <= HW_I_RANGE_L)
	{
		GPIO_SetState(GPIO_I_RANGE_H, false);
		GPIO_SetState(GPIO_I_RANGE_M, false);
		GPIO_SetState(GPIO_I_RANGE_L, true);
	}
	else
	{
		if(Current <= HW_I_RANGE_M)
		{
			GPIO_SetState(GPIO_I_RANGE_H, false);
			GPIO_SetState(GPIO_I_RANGE_M, true);
			GPIO_SetState(GPIO_I_RANGE_L, false);
		}
		else
		{
			GPIO_SetState(GPIO_I_RANGE_H, true);
			GPIO_SetState(GPIO_I_RANGE_M, false);
			GPIO_SetState(GPIO_I_RANGE_L, false);
		}
	}
}

void MEAS_SetVoltageRange(uint16_t Voltage)
{
	if(Voltage <= HW_U_RANGE_L)
	{
		GPIO_SetState(GPIO_U_RANGE, true);
	}
	else
	{
		GPIO_SetState(GPIO_U_RANGE, false);
	}
}

