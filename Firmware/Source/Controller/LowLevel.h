#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"

// Functions
void LL_ToggleBoardLED();
void LL_SetSync1State(bool NewState);
void LL_SetSync2State(bool NewState);
void LL_ConnectPOWRelay(bool NewState);
void LL_ConnectCTRLRelay(bool NewState);
void LL_EnablePWMOut();
void LL_DisablePWMOut();
bool LL_GetStateKU();
bool LL_GetStateKI_H();
bool LL_GetStateKI_M();
bool LL_GetStateKI_L();

#endif //__LOWLEVEL_H
