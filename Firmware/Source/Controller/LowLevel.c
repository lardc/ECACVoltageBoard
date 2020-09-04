// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetSync1State()
{
	GPIO_SetState(GPIO_CTRL_SYNC_1, true);
	DELAY_MS(10);
	GPIO_SetState(GPIO_CTRL_SYNC_1, false);
}
//-----------------------------

void LL_SetSync2State()
{
	GPIO_SetState(GPIO_CTRL_SYNC_2, true);
	DELAY_MS(10);
	GPIO_SetState(GPIO_CTRL_SYNC_2, false);
}
//-----------------------------
