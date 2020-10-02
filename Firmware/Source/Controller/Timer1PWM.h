#ifndef __T1PWM_H
#define __T1PWM_H

// Include
#include "stdinc.h"

// Variables
extern volatile uint32_t T1PWM_PWMBase;

// Functions
void T1PWM_Init(float SystemClock, uint16_t Period);
void T1PWM_SetDutyCycle(float Value);
void T1PWM_Start();
void T1PWM_Stop();

#endif //__T1PWM_H
