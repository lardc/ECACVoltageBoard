#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"

// Defines
#define RELAY_CTRL		1
#define RELAY_POW		2

// Functions
//
void LL_ToggleBoardLED();
void LL_SetSync1State(bool NewState);
void LL_SetSync2State(bool NewState);
void LL_SetStateRelay(uint8_t NumRelay, bool NewState);

#endif //__LOWLEVEL_H
