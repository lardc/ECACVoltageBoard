#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_LedGreen(bool State);
void LL_LedRed(bool State);
void LL_SetStateLock1(bool State);
void LL_SetStateLock2(bool State);
void LL_SoftSpiData(bool State);
void LL_SetSync1State(bool State);
void LL_SetSync2State(bool State);
void LL_SetStateReset(bool State);
void LL_WriteToShiftRegister(volatile uint8_t *Data, uint8_t DataSize);
bool LL_GetStateSync1();
bool LL_GetStateSync2();
bool LL_GetStateSens1();
bool LL_GetStateSens2();
bool LL_GetStateButtonStart();
bool LL_GetStateButtonStop();

#endif //__LOWLEVEL_H
