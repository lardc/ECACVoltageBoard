#ifndef __MEASURE_H
#define __MEASURE_H

// Include
#include "stdinc.h"
#include "Global.h"

// Variables
extern volatile uint16_t ADC1DMAVoltageBuffer[];
extern volatile uint16_t ADC2DMACurrentBuffer[];
extern volatile bool MEASURE_InMilliAmperes;

// Functions
void MEASURE_SetMeasureRange();
float MEASURE_Voltage();
float MEASURE_Current();
float MEASURE_GetCurrentPeakLimit();

#endif //__MEASURE_H
