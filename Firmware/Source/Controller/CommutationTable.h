#ifndef __COMMUTATIONTABLE_H
#define __COMMUTATIONTABLE_H

// Includes
#include "stdinc.h"

// Definitions
#define MAX_TUPE_MEASURE		4
#define MAX_TUPE_CASE			15
#define MAX_TUPE_POS_CASE		3
#define MAX_TUPE_CTRL			3
#define MAX_TUPE_LEAKAGE		2
#define MAX_TUPE_POLARITY		2

#define BISTABLE_ARRAY_SIZE		12
#define SIMPLE_ARRAY_SIZE		46

#define BISTABLE_RELAY_START_BIT	SIMPLE_ARRAY_SIZE

#define MAX_NUM_RELAY			45

#define MAX_COUNTER_TABLE		155

#define REGISTERS_NUM	11

#define REGISTER_A		2
#define REGISTER_B		1
#define REGISTER_C		0
#define REGISTER_D		8
#define REGISTER_E		7
#define REGISTER_F		10
#define REGISTER_G		9
#define REGISTER_H		3
#define REGISTER_I		4
#define REGISTER_J		5
#define REGISTER_K		6

#define COMM_MEAS_CURR_LEAK	1
#define COMM_MEAS_DROP_VOLT	2
#define COMM_MEAS_IN_VOLT	3
#define COMM_MEAS_VOLT_BAN	4

#define CASE_A1			1
#define CASE_I1			2
#define CASE_I6			3
#define CASE_B1			4
#define CASE_B2			5
#define CASE_B5			6
#define CASE_V1			7
#define CASE_V2			8
#define CASE_V104		9
#define CASE_V108		10
#define CASE_L1			11
#define CASE_L2			12
#define CASE_D1			13
#define CASE_D2			14
#define CASE_D192		15

#define POS_1	1
#define POS_2	2
#define POS_3	3

#define CTRL_DC_V		1
#define CTRL_DC_I		2
#define CTRL_AC_V		3

#define IGNORE	0

#define LEAK_DC	1
#define LEAK_AC	2

#define FORVARD	1
#define REVERSE	2

#define COMM_RegisterPin static const RegisterPin
#define COMM_BistableSwitch static const BistableSwitch
#define COMM_MainTable static const MeasureTypeTable

// Types
typedef struct __RegisterPin
{
	uint8_t Register;
	uint8_t Bit;
} RegisterPin;

typedef struct __BistableSwitch
{
	RegisterPin TurnOnPin;
	RegisterPin TurnOffPin;
} BistableSwitch;

typedef struct __MeasureTypeTable
{
	uint8_t TypeMeasure;
	uint8_t TypeCase;
	uint8_t TypePositionOfCase;
	uint8_t TypeCtrl;
	uint8_t TypeSignalAsLeakAge;
	uint8_t SignalDirection;
	uint64_t Relay;

} MeasureTypeTable;

MeasureTypeTable COMM_Table[MAX_COUNTER_TABLE];

// Инициализация для простых реле
COMM_RegisterPin COMM_SwitchPOTPlusToPOT1 = {REGISTER_A, BIT0};
COMM_RegisterPin COMM_SwitchPOTPlusToPOT2 = {REGISTER_A, BIT1};
COMM_RegisterPin COMM_SwitchPOTPlusToPOT3 = {REGISTER_A, BIT2};
COMM_RegisterPin COMM_SwitchPOTPlusToPOT4 = {REGISTER_A, BIT3};
COMM_RegisterPin COMM_SwitchPOTPlusToPOT5 = {REGISTER_A, BIT4};
COMM_RegisterPin COMM_SwitchPOTPlusToPOT6 = {REGISTER_A, BIT5};

COMM_RegisterPin COMM_SwitchPOTMinusToPOT1 = {REGISTER_B, BIT0};
COMM_RegisterPin COMM_SwitchPOTMinusToPOT2 = {REGISTER_B, BIT1};
COMM_RegisterPin COMM_SwitchPOTMinusToPOT3 = {REGISTER_B, BIT2};
COMM_RegisterPin COMM_SwitchPOTMinusToPOT4 = {REGISTER_B, BIT3};
COMM_RegisterPin COMM_SwitchPOTMinusToPOT5 = {REGISTER_B, BIT4};
COMM_RegisterPin COMM_SwitchPOTMinusToPOT6 = {REGISTER_B, BIT5};

COMM_RegisterPin COMM_SwitchPOTOutToPOT1 = {REGISTER_C, BIT0};
COMM_RegisterPin COMM_SwitchPOTOutToPOT2 = {REGISTER_C, BIT1};
COMM_RegisterPin COMM_SwitchPOTOutToPOT3 = {REGISTER_C, BIT2};
COMM_RegisterPin COMM_SwitchPOTOutToPOT4 = {REGISTER_C, BIT3};
COMM_RegisterPin COMM_SwitchPOTOutToPOT5 = {REGISTER_C, BIT4};
COMM_RegisterPin COMM_SwitchPOTOutToPOT6 = {REGISTER_C, BIT5};

COMM_RegisterPin COMM_SwitchBUSHVPlusToPOW1 = {REGISTER_H, BIT0};
COMM_RegisterPin COMM_SwitchBUSHVPlusToPOW2 = {REGISTER_H, BIT1};
COMM_RegisterPin COMM_SwitchBUSHVPlusToPOW3 = {REGISTER_H, BIT2};
COMM_RegisterPin COMM_SwitchBUSHVPlusToPOW4 = {REGISTER_H, BIT3};
COMM_RegisterPin COMM_SwitchBUSHVPlusToPOW5 = {REGISTER_H, BIT4};
COMM_RegisterPin COMM_SwitchBUSHVPlusToPOW6 = {REGISTER_H, BIT5};

COMM_RegisterPin COMM_SwitchBUSHVMinusToPOW1 = {REGISTER_I, BIT0};
COMM_RegisterPin COMM_SwitchBUSHVMinusToPOW2 = {REGISTER_I, BIT1};
COMM_RegisterPin COMM_SwitchBUSHVMinusToPOW3 = {REGISTER_I, BIT2};
COMM_RegisterPin COMM_SwitchBUSHVMinusToPOW4 = {REGISTER_I, BIT3};
COMM_RegisterPin COMM_SwitchBUSHVMinusToPOW5 = {REGISTER_I, BIT4};
COMM_RegisterPin COMM_SwitchBUSHVMinusToPOW6 = {REGISTER_I, BIT5};

COMM_RegisterPin COMM_SwitchCtrl1ToCtrl1 = {REGISTER_J, BIT0};
COMM_RegisterPin COMM_SwitchCtrl1ToCtrl2 = {REGISTER_J, BIT1};
COMM_RegisterPin COMM_SwitchCtrl1ToCtrl3 = {REGISTER_J, BIT2};
COMM_RegisterPin COMM_SwitchCtrl1ToCtrl4 = {REGISTER_J, BIT3};
COMM_RegisterPin COMM_SwitchCtrl2ToCtrl1 = {REGISTER_J, BIT4};
COMM_RegisterPin COMM_SwitchCtrl2ToCtrl2 = {REGISTER_J, BIT5};
COMM_RegisterPin COMM_SwitchCtrl2ToCtrl3 = {REGISTER_J, BIT6};
COMM_RegisterPin COMM_SwitchCtrl2ToCtrl4 = {REGISTER_J, BIT7};

COMM_RegisterPin COMM_SwitchPotCtrlPlusToCtrlPot1 = {REGISTER_K, BIT0};
COMM_RegisterPin COMM_SwitchPotCtrlPlusToCtrlPot2 = {REGISTER_K, BIT1};
COMM_RegisterPin COMM_SwitchPotCtrlPlusToCtrlPot3 = {REGISTER_K, BIT2};
COMM_RegisterPin COMM_SwitchPotCtrlPlusToCtrlPot4 = {REGISTER_K, BIT3};
COMM_RegisterPin COMM_SwitchPotCtrlMinusToCtrlPot1 = {REGISTER_K, BIT4};
COMM_RegisterPin COMM_SwitchPotCtrlMinusToCtrlPot2 = {REGISTER_K, BIT5};
COMM_RegisterPin COMM_SwitchPotCtrlMinusToCtrlPot3 = {REGISTER_K, BIT6};
COMM_RegisterPin COMM_SwitchPotCtrlMinusToCtrlPot4 = {REGISTER_K, BIT7};

// Инициализация для бистабильных реле
COMM_BistableSwitch COMM_SwitchBUSLVPlusToPOW1 = {{REGISTER_E, BIT0}, {REGISTER_D, BIT0}};
COMM_BistableSwitch COMM_SwitchBUSLVPlusToPOW2 = {{REGISTER_E, BIT1}, {REGISTER_D, BIT1}};
COMM_BistableSwitch COMM_SwitchBUSLVPlusToPOW3 = {{REGISTER_E, BIT2}, {REGISTER_D, BIT2}};
COMM_BistableSwitch COMM_SwitchBUSLVPlusToPOW4 = {{REGISTER_E, BIT3}, {REGISTER_D, BIT3}};
COMM_BistableSwitch COMM_SwitchBUSLVPlusToPOW5 = {{REGISTER_E, BIT4}, {REGISTER_D, BIT4}};
COMM_BistableSwitch COMM_SwitchBUSLVPlusToPOW6 = {{REGISTER_E, BIT5}, {REGISTER_D, BIT5}};

COMM_BistableSwitch COMM_SwitchBUSLVMinusToPOW1 = {{REGISTER_G, BIT0}, {REGISTER_F, BIT0}};
COMM_BistableSwitch COMM_SwitchBUSLVMinusToPOW2 = {{REGISTER_G, BIT1}, {REGISTER_F, BIT1}};
COMM_BistableSwitch COMM_SwitchBUSLVMinusToPOW3 = {{REGISTER_G, BIT2}, {REGISTER_F, BIT2}};
COMM_BistableSwitch COMM_SwitchBUSLVMinusToPOW4 = {{REGISTER_G, BIT3}, {REGISTER_F, BIT3}};
COMM_BistableSwitch COMM_SwitchBUSLVMinusToPOW5 = {{REGISTER_G, BIT4}, {REGISTER_F, BIT4}};
COMM_BistableSwitch COMM_SwitchBUSLVMinusToPOW6 = {{REGISTER_G, BIT5}, {REGISTER_F, BIT5}};

// Variables
extern const RegisterPin* const COMM_SimpleRelayArray[];
extern const BistableSwitch* const COMM_BistableRelayArray[];

void COMM_InitTable();
void COMM_MakeMeasCommutateTable(uint8_t NumbTable, uint8_t TypeMeasure, uint8_t TypeCase, uint8_t TypePositionOfCase,
		uint8_t TypeCtrl, uint8_t TypeSignalAsLeakAge, uint8_t SignalDirection, uint64_t NumRelay);

#endif // __COMMUTATIONTABLE_H
