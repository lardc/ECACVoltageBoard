// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "LowLevel.h"
#include "Delay.h"
#include "Controller.h"
#include "DebugActions.h"

// Variables
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

		case ACT_DBG_SET_STATE_POW_RELAY:
			{
				LL_ConnectPOWRelay(DataTable[REG_DBG_RELAY_POW_STATE]);
			}
			break;

		case ACT_DBG_SET_STATE_CTRL_RELAY:
			{
				LL_ConnectCTRLRelay(DataTable[REG_DBG_RELAY_CTRL_STATE]);
			}
			break;

		case ACT_DBG_SIN:
			{
				DBGACT_GenerateOneSin(DataTable[REG_SIN_VOLTAGE], DataTable[REG_SIN_CURRENT], DataTable[REG_SIN_POLARITY]);
			}
			break;

		default:
			return false;
	}

	return true;
}
