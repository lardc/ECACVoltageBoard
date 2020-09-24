#ifndef __T1PWM_H
#define __T1PWM_H

// Include
#include "stdinc.h"

// Functions
void T1PWM_InitTIM1(float SystemClock, uint16_t Period);
void T1PWM_SetDutyCycle(float Value);
void T1PWM_Start();
void T1PWM_Stop();

#endif //__T1PWM_H
