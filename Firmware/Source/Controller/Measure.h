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
void MEASURE_SetMeasureRange(uint16_t Voltage, uint32_t Current);
extern float MEASURE_Voltage();
extern float MEASURE_Current();

#endif //__MEASURE_H
