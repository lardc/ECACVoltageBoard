// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "LowLevel.h"
#include "Delay.h"
#include "Controller.h"
#include "DebugActions.h"

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

		default:
			return false;
	}

	return true;
}
