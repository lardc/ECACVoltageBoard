#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
#include "stdinc.h"

void DBGACT_GenerateImpulseLineSync1();
void DBGACT_GenerateImpulseLineSync2();
void DBGACT_SetStateRelay(uint8_t NumRelay, bool NewState);
void DBGACT_GenerateOneSin(uint16_t Voltage, uint16_t Current, uint8_t Polarity);

#endif //__DEBUGACTIONS_H
