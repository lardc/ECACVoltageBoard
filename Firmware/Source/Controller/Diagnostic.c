// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "LowLevel.h"
#include "Delay.h"
#include "Controller.h"
#include "DebugActions.h"
#include "Safety.h"
#include "Commutation.h"

extern volatile DeviceState CONTROL_State;
// Functions

bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch (ActionID)
	{

		case ACT_DBG_SYNC_1_IMPULSE:
			{
				DBGACT_GenerateImpulseLineSync1();
			}
			break;

		case ACT_DBG_SYNC_2_IMPULSE:
			{
				DBGACT_GenerateImpulseLineSync2();
			}
			break;

		case ACT_DBG_LOCK_1_IMPULSE:
			{
				DBGACT_GenerateImpulseLineLock1();
			}
			break;

		case ACT_DBG_LOCK_2_IMPULSE:
			{
				DBGACT_GenerateImpulseLineLock2();
			}
			break;

		case ACT_DBG_SIMPLE_RELAY_ON:
			{
				COMM_SwitchSimpleRelay(DataTable[REG_DBG_RELAY_INDEX], true);
			}
			break;

		case ACT_DBG_SIMPLE_RELAY_OFF:
			{
				COMM_SwitchSimpleRelay(DataTable[REG_DBG_RELAY_INDEX], false);
			}
			break;

		case ACT_DBG_BISTABLE_RELAY_ON:
			{
				COMM_SwitchBistableRelay(DataTable[REG_DBG_RELAY_INDEX], true);
			}
			break;

		case ACT_DBG_BISTABLE_RELAY_OFF:
			{
				COMM_SwitchBistableRelay(DataTable[REG_DBG_RELAY_INDEX], false);
			}
			break;

		case ACT_DBG_SAFETY_DISABLE:
			{
				if(CONTROL_State == DS_None)
				{
					SFTY_SwitchInterruptState(false);
				}
				else
				{
					*pUserError = ERR_OPERATION_BLOCKED;
				}
			}
			break;

		case ACT_DBG_SAFETY_ENABLE:
			{
				SFTY_SwitchInterruptState(true);
			}
			break;

		case ACT_DBG_LED_RED_IMPULSE:
			{
				DBGACT_GenerateImpulseLedRed();
			}
			break;

		case ACT_DBG_LED_GREEN_IMPULSE:
			{
				DBGACT_GenerateImpulseLedGreen();
			}
			break;

		case ACT_SET_RELAY_TABLE:
			{
				COMM_DisconnectAllRelay();
				COMM_CommutateGroupOnTableNumber(DataTable[REG_NUM_TABLE]);
			}
			break;

		default:
			return false;
	}

	return true;
}
