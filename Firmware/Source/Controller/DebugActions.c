// Header
#include "DebugActions.h"

// Include
#include "Delay.h"
#include "LowLevel.h"
#include "PWM.h"

// Functions
void DBGACT_GenerateImpulseLineSync1()
{
	LL_SetSync1State(TRUE);
	DELAY_MS(10);
	LL_SetSync1State(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseLineSync2()
{
	LL_SetSync2State(TRUE);
	DELAY_MS(10);
	LL_SetSync2State(FALSE);
}
//-----------------------------

void DBGACT_SetStatePOWRelay(bool NewState)
{
	LL_ConnectPOWRelay(NewState);
}
//-----------------------------
void DBGACT_SetStateCTRLRelay(bool NewState)
{
	LL_ConnectCTRLRelay(NewState);
}
//-----------------------------

void DBGACT_GenerateOneSin(uint16_t Voltage, uint16_t Current, uint8_t Polarity)
{
	PWM_PrepareAndGenerateSignal(Voltage, Current, Polarity);
}
//-----------------------------
