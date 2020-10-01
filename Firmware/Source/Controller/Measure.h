#ifndef __MEASURE_H
#define __MEASURE_H

// Include
#include "stdinc.h"
#include "Global.h"

// Variables
extern volatile uint16_t ADC1DMABuff[ADC_BUFF_SIZE];
extern volatile uint16_t ADC2DMABuff[ADC_BUFF_SIZE];
extern volatile bool MEASURE_VoltageDone;
extern volatile bool MEASURE_CurrentDone;

// Functions
void MEAS_SetMeasureRange(uint16_t Voltage, uint16_t Current);

#endif //__MEASURE_H
