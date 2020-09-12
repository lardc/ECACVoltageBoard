#ifndef __PWM_H
#define __PWM_H

// Include
#include "stdinc.h"
#include "Global.h"

// Variables
extern volatile uint16_t TIM1_DMA_Buffer[SIN_BUFF_SIZE + 1];

// Functions
void PWM_ConfigureTIM1_Ch1(float SystemClock, uint16_t Period);

#endif //__PWM_H
