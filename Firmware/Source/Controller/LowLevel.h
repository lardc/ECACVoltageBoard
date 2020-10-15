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
void LL_DMAReload();

#endif //__LOWLEVEL_H
