#ifndef __PWM_H
#define __PWM_H

// Include
#include "stdinc.h"
#include "Global.h"

// Variables
extern volatile uint32_t PWMTimerCounter;

// Functions
void PWM_SignalStart(uint16_t Voltage, uint32_t Current);
void PWM_SignalStop();
void PWM_SinRegulation();

#endif //__PWM_H
