// Header
#include "LowLevel.h"

// Includes
#include "Board.h"
#include "Delay.h"

// Functions
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetSync1State(bool NewState)
{
	GPIO_SetState(GPIO_CTRL_SYNC_1, NewState);
}
//-----------------------------

void LL_SetSync2State(bool NewState)
{
	GPIO_SetState(GPIO_CTRL_SYNC_2, NewState);
}
//-----------------------------

void LL_SetStateRelay(uint8_t NumChanel, bool NewState)
{
	if(NumChanel == RELAY_POW)
	{
		if(NewState)
		{
			GPIO_SetState(GPIO_CTRL_RELAY_1, true);
			GPIO_SetState(GPIO_CTRL_RELAY_2, true);
		}
		else
		{
			GPIO_SetState(GPIO_CTRL_RELAY_1, false);
			GPIO_SetState(GPIO_CTRL_RELAY_2, false);
		}
	}
}
//-----------------------------

void LL_SetStatePWMOutput(bool NewState)
{
	if(NewState)
	{
		GPIO_SetState(GPIO_CTRL_PWMSD_1, true);
		GPIO_SetState(GPIO_CTRL_PWMSD_2, true);
	}
	else
	{
		GPIO_SetState(GPIO_CTRL_PWMSD_1, false);
		GPIO_SetState(GPIO_CTRL_PWMSD_2, false);
	}
}
//-----------------------------
