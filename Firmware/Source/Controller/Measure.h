#ifndef __MEASURE_H
#define __MEASURE_H

// Include
#include "stdinc.h"
#include "Global.h"

// Variables
extern volatile uint16_t ADC1DMAVoltageBuffer[];
extern volatile uint16_t ADC2DMACurrentBuffer[];

extern volatile uint16_t VoltageTarget, CurrentTarget;

// Functions
void MEAS_SetMeasureRange(uint16_t Voltage, uint32_t Current);
extern float MEAS_Voltage();
extern float MEAS_Current();

#endif //__MEASURE_H
