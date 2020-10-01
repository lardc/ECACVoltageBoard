// Header
#include "Controller.h"
//
// Includes
#include "DebugActions.h"
#include "Board.h"
#include "Delay.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "Diagnostic.h"
#include "BCCIxParams.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = false;
volatile Int64U CONTROL_TimeCounter = 0;
volatile Int16U CONTROL_BuffRAWCurrent[VALUES_x_SIZE] = {0};
volatile Int16U CONTROL_BuffRAWVoltage[VALUES_x_SIZE] = {0};
volatile Int16U CONTROL_BuffCurrent[VALUES_x_SIZE] = {0};
volatile Int16U CONTROL_BuffVoltage[VALUES_x_SIZE] = {0};
volatile Int16U CONTROL_BuffCounterRAWCurrent = 0;
volatile Int16U CONTROL_BuffCounterRAWVoltage = 0;
volatile Int16U CONTROL_BuffCounterCurrent = 0;
volatile Int16U CONTROL_BuffCounterVoltage = 0;

/// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();

// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = {EP_I_RAW, EP_V_RAW, EP_I, EP_V};
	Int16U EPSized[EP_COUNT] = {VALUES_x_SIZE, VALUES_x_SIZE, VALUES_x_SIZE, VALUES_x_SIZE};
	pInt16U EPCounters[EP_COUNT] = {(pInt16U)&CONTROL_BuffCounterRAWCurrent, (pInt16U)&CONTROL_BuffCounterRAWVoltage,
			(pInt16U)&CONTROL_BuffCounterCurrent, (pInt16U)&CONTROL_BuffCounterVoltage};
	pInt16U EPDatas[EP_COUNT] = {(pInt16U)&CONTROL_BuffRAWCurrent, (pInt16U)&CONTROL_BuffRAWVoltage, (pInt16U)&CONTROL_BuffCurrent, (pInt16U)&CONTROL_BuffCounterVoltage};

	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	CONTROL_SetDeviceState(DS_None);
}

//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			{
				DataTable[REG_OP_RESULT] = OPRESULT_NONE;
				if((CONTROL_State == DS_None) || (CONTROL_State == DS_Disabled))
				{
					CONTROL_SetDeviceState(DS_Enabled);
					DataTable[REG_OP_RESULT] = OPRESULT_OK;
				}
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					*pUserError = ERR_OPERATION_BLOCKED;
				}
				break;
			}
			
		case ACT_DISABLE_POWER:
			DataTable[REG_OP_RESULT] = OPRESULT_NONE;
			if((CONTROL_State == DS_None) || (CONTROL_State == DS_Enabled))
			{
				CONTROL_SetDeviceState(DS_Disabled);
			}
			else
			{
				if((CONTROL_State == DS_Disabled))
				{
					DataTable[REG_OP_RESULT] = OPRESULT_OK;
				}
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
				}
			}
			
		case ACT_FAULT_CLEAR:
			{
				CONTROL_ResetToDefaultState();
			}
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			
	}
	return true;
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//------------------------------------------

void CONTROL_DelayMs(uint32_t Delay)
{
	uint64_t Counter = (uint64_t)CONTROL_TimeCounter + Delay;
	while(Counter > CONTROL_TimeCounter)
		CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

