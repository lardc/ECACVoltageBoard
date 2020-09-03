// Header
#include "Interrupts.h"

// Include
#include "Safety.h"
#include "ZwEXTI.h"
#include "LowLevel.h"

// Forward functions
void EXTI9_5_IRQHandler();
void ITRPT_Sen1();
void ITRPT_Sen2();
void ITRPT_SaveActiveStateButtonStop();
void ITRPT_SaveActiveStateButtonStart();

// Functions
void EXTI9_5_IRQHandler()
{
	if(EXTI_FlagCheck(EXTI_6))	// SEN2
	{
		ITRPT_Sen2();
		EXTI_FlagReset(EXTI_6);
	}

	if(EXTI_FlagCheck(EXTI_7))	// SEN1
	{
		ITRPT_Sen1();
		EXTI_FlagReset(EXTI_7);
	}

	if(EXTI_FlagCheck(EXTI_8))	// STOP
	{
		ITRPT_SaveActiveStateButtonStop();
		EXTI_FlagReset(EXTI_8);
	}

	if(EXTI_FlagCheck(EXTI_9))	// START
	{
		ITRPT_SaveActiveStateButtonStart();
		EXTI_FlagReset(EXTI_9);
	}
}
//------------------------------------------

void ITRPT_Sen1()
{
	SafetyState.StateSensor.One = 1;
}
//------------------------------------------

void ITRPT_Sen2()
{
	SafetyState.StateSensor.Two = 1;
}
//------------------------------------------

void ITRPT_SaveActiveStateButtonStop()
{
	SafetyState.StateButton.Stop = 1;
}
//------------------------------------------

void ITRPT_SaveActiveStateButtonStart()
{
	SafetyState.StateButton.Start = 1;
}
//------------------------------------------
