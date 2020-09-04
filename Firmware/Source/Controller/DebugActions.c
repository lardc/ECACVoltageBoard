// Header
#include "DebugActions.h"

// Include
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Functions
//
void DBGACT_GenerateImpulseLineSync1()
{
	LL_SetSync1State(TRUE);
	CONTROL_DelayMs(10);
	LL_SetSync1State(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseLineSync2()
{
	LL_SetSync2State(TRUE);
	CONTROL_DelayMs(10);
	LL_SetSync2State(FALSE);
}
//-----------------------------
