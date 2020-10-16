#ifndef __MEASURE_H
#define __MEASURE_H

// Include
#include "stdinc.h"
#include "Global.h"

// Variables
extern volatile uint16_t ADC1DMAVoltageBuffer[];
extern volatile uint16_t ADC2DMACurrentBuffer[];

// Functions
void MEASURE_SetMeasureRange(uint16_t Voltage, uint32_t Current);
float MEASURE_Voltage();
float MEASURE_Current();
float MEASURE_GetCurrentLimit();

#endif //__MEASURE_H
