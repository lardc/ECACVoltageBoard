#ifndef __SAFETY_H
#define __SAFETY_H

#include "stdinc.h"

#define SFTY_SET_STATE_SENS1 SafetyState.StateSensor.One
#define SFTY_SET_STATE_SENS2 SafetyState.StateSensor.Two
#define SFTY_SET_STATE_BUTTON_STOP SafetyState.StateButton.Stop
#define SFTY_SET_STATE_BUTTON_START SafetyState.StateButton.Start

#define SFTY_GET_STATE_SENS1 SafetyState.StateSensor.One
#define SFTY_GET_STATE_SENS2 SafetyState.StateSensor.Two
#define SFTY_GET_STATE_BUTTON_STOP SafetyState.StateButton.Stop
#define SFTY_GET_STATE_BUTTON_START SafetyState.StateButton.Start
#define SFTY_GET_STATUS SafetyState.SafetyIsActive
#define SFTY_SET_ENABLE SafetyState.SafetyIsActive = 1
#define SFTY_SET_DISABLE SafetyState.SafetyIsActive = 0

#define SFTY_CLR_STATE_SENS1		SafetyState.StateSensor.One = 0
#define SFTY_CLR_STATE_SENS2		SafetyState.StateSensor.Two = 0
#define SFTY_CLR_STATE_BUTTON_STOP	SafetyState.StateButton.Stop = 0
#define SFTY_CLR_STATE_BUTTON_START	SafetyState.StateButton.Start = 0

typedef struct __Buttons
{
	bool Start;
	bool Stop;
} Buttons;

typedef struct __Led
{
	bool Red;
	bool Green;
} Led;

typedef struct __TwoElem
{
	bool One;
	bool Two;
} TwoElem;

typedef struct __Safety
{
	bool SafetyIsActive;
	Buttons StateButton;
	Led StateLed;
	TwoElem StateLock;
	TwoElem StateSensor;
} Safety;

extern volatile Safety SafetyState;

//Functions
void SFTY_ReadStateSafety();
void SFTY_EnableInterrupt();
void SFTY_CheckSafety();
void SFTY_SwitchInterruptState(bool NewState);

#endif //__SAFETY_H
