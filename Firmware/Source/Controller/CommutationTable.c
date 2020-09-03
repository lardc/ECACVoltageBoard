// Header
#include "CommutationTable.h"

#define COMM_POTPlusToPOT1 					(uint64_t) 1 << 0
#define COMM_POTPlusToPOT2 					(uint64_t) 1 << 1
#define COMM_POTPlusToPOT3 					(uint64_t) 1 << 2
#define COMM_POTPlusToPOT4 					(uint64_t) 1 << 3
#define COMM_POTPlusToPOT5 					(uint64_t) 1 << 4
#define COMM_POTPlusToPOT6 					(uint64_t) 1 << 5

#define COMM_POTMinusToPOT1 				(uint64_t) 1 << 6
#define COMM_POTMinusToPOT2 				(uint64_t) 1 << 7
#define COMM_POTMinusToPOT3 				(uint64_t) 1 << 8
#define COMM_POTMinusToPOT4 				(uint64_t) 1 << 9
#define COMM_POTMinusToPOT5 				(uint64_t) 1 << 10
#define COMM_POTMinusToPOT6 				(uint64_t) 1 << 11

#define COMM_POTOutToPOT1 					(uint64_t) 1 << 12
#define COMM_POTOutToPOT2 					(uint64_t) 1 << 13
#define COMM_POTOutToPOT3 					(uint64_t) 1 << 14
#define COMM_POTOutToPOT4 					(uint64_t) 1 << 15
#define COMM_POTOutToPOT5 					(uint64_t) 1 << 16
#define COMM_POTOutToPOT6 					(uint64_t) 1 << 17

#define COMM_BUSHVPlusToPOW1 				(uint64_t) 1 << 18
#define COMM_BUSHVPlusToPOW2 				(uint64_t) 1 << 19
#define COMM_BUSHVPlusToPOW3 				(uint64_t) 1 << 20
#define COMM_BUSHVPlusToPOW4 				(uint64_t) 1 << 21
#define COMM_BUSHVPlusToPOW5 				(uint64_t) 1 << 22
#define COMM_BUSHVPlusToPOW6 				(uint64_t) 1 << 23

#define COMM_BUSHVMinusToPOW1				(uint64_t) 1 << 24
#define COMM_BUSHVMinusToPOW2				(uint64_t) 1 << 25
#define COMM_BUSHVMinusToPOW3				(uint64_t) 1 << 26
#define COMM_BUSHVMinusToPOW4				(uint64_t) 1 << 27
#define COMM_BUSHVMinusToPOW5				(uint64_t) 1 << 28
#define COMM_BUSHVMinusToPOW6				(uint64_t) 1 << 29

#define COMM_Ctrl1ToCtrl1 					(uint64_t) 1 << 30
#define COMM_Ctrl1ToCtrl2 					(uint64_t) 1 << 31
#define COMM_Ctrl1ToCtrl3 					(uint64_t) 1 << 32
#define COMM_Ctrl1ToCtrl4 					(uint64_t) 1 << 33
#define COMM_Ctrl2ToCtrl1 					(uint64_t) 1 << 34
#define COMM_Ctrl2ToCtrl2 					(uint64_t) 1 << 35
#define COMM_Ctrl2ToCtrl3 					(uint64_t) 1 << 36
#define COMM_Ctrl2ToCtrl4 					(uint64_t) 1 << 37

#define COMM_PotCtrlPlusToCtrlPot1 			(uint64_t) 1 << 38
#define COMM_PotCtrlPlusToCtrlPot2 			(uint64_t) 1 << 39
#define COMM_PotCtrlPlusToCtrlPot3 			(uint64_t) 1 << 40
#define COMM_PotCtrlPlusToCtrlPot4 			(uint64_t) 1 << 41
#define COMM_PotCtrlMinusToCtrlPot1 		(uint64_t) 1 << 42
#define COMM_PotCtrlMinusToCtrlPot2 		(uint64_t) 1 << 43
#define COMM_PotCtrlMinusToCtrlPot3 		(uint64_t) 1 << 44
#define COMM_PotCtrlMinusToCtrlPot4 		(uint64_t) 1 << 45

#define COMM_BUSLVPlusToPOW1 				(uint64_t) 1 << 46
#define COMM_BUSLVPlusToPOW2 				(uint64_t) 1 << 47
#define COMM_BUSLVPlusToPOW3 				(uint64_t) 1 << 48
#define COMM_BUSLVPlusToPOW4 				(uint64_t) 1 << 49
#define COMM_BUSLVPlusToPOW5 				(uint64_t) 1 << 50
#define COMM_BUSLVPlusToPOW6 				(uint64_t) 1 << 51

#define COMM_BUSLVMinusToPOW1 				(uint64_t) 1 << 52
#define COMM_BUSLVMinusToPOW2 				(uint64_t) 1 << 53
#define COMM_BUSLVMinusToPOW3 				(uint64_t) 1 << 54
#define COMM_BUSLVMinusToPOW4 				(uint64_t) 1 << 55
#define COMM_BUSLVMinusToPOW5 				(uint64_t) 1 << 56
#define COMM_BUSLVMinusToPOW6 				(uint64_t) 1 << 57

const RegisterPin* const COMM_SimpleRelayArray[] = {&COMM_SwitchPOTPlusToPOT1,					// 0
		&COMM_SwitchPOTPlusToPOT2,					// 1
		&COMM_SwitchPOTPlusToPOT3,					// 2
		&COMM_SwitchPOTPlusToPOT4,					// 3
		&COMM_SwitchPOTPlusToPOT5,					// 4
		&COMM_SwitchPOTPlusToPOT6,					// 5

		&COMM_SwitchPOTMinusToPOT1,					// 6
		&COMM_SwitchPOTMinusToPOT2,					// 7
		&COMM_SwitchPOTMinusToPOT3,					// 8
		&COMM_SwitchPOTMinusToPOT4,					// 9
		&COMM_SwitchPOTMinusToPOT5,					// 10
		&COMM_SwitchPOTMinusToPOT6,					// 11

		&COMM_SwitchPOTOutToPOT1,					// 12
		&COMM_SwitchPOTOutToPOT2,					// 13
		&COMM_SwitchPOTOutToPOT3,					// 14
		&COMM_SwitchPOTOutToPOT4,					// 15
		&COMM_SwitchPOTOutToPOT5,					// 16
		&COMM_SwitchPOTOutToPOT6,					// 17

		&COMM_SwitchBUSHVPlusToPOW1,				// 18
		&COMM_SwitchBUSHVPlusToPOW2,				// 19
		&COMM_SwitchBUSHVPlusToPOW3,				// 20
		&COMM_SwitchBUSHVPlusToPOW4,				// 21
		&COMM_SwitchBUSHVPlusToPOW5,				// 22
		&COMM_SwitchBUSHVPlusToPOW6,				// 23

		&COMM_SwitchBUSHVMinusToPOW1,				// 24
		&COMM_SwitchBUSHVMinusToPOW2,				// 25
		&COMM_SwitchBUSHVMinusToPOW3,				// 26
		&COMM_SwitchBUSHVMinusToPOW4,				// 27
		&COMM_SwitchBUSHVMinusToPOW5,				// 28
		&COMM_SwitchBUSHVMinusToPOW6,				// 29

		&COMM_SwitchCtrl1ToCtrl1,					// 30
		&COMM_SwitchCtrl1ToCtrl2,					// 31
		&COMM_SwitchCtrl1ToCtrl3,					// 32
		&COMM_SwitchCtrl1ToCtrl4,					// 33
		&COMM_SwitchCtrl2ToCtrl1,					// 34
		&COMM_SwitchCtrl2ToCtrl2,					// 35
		&COMM_SwitchCtrl2ToCtrl3,					// 36
		&COMM_SwitchCtrl2ToCtrl4,					// 37

		&COMM_SwitchPotCtrlPlusToCtrlPot1,			// 38
		&COMM_SwitchPotCtrlPlusToCtrlPot2,			// 39
		&COMM_SwitchPotCtrlPlusToCtrlPot3,			// 40
		&COMM_SwitchPotCtrlPlusToCtrlPot4,			// 41
		&COMM_SwitchPotCtrlMinusToCtrlPot1,			// 42
		&COMM_SwitchPotCtrlMinusToCtrlPot2,			// 43
		&COMM_SwitchPotCtrlMinusToCtrlPot3,			// 44
		&COMM_SwitchPotCtrlMinusToCtrlPot4			// 45
		};

const BistableSwitch* const COMM_BistableRelayArray[] = {&COMM_SwitchBUSLVPlusToPOW1,				// 0 (46)
		&COMM_SwitchBUSLVPlusToPOW2,				// 1	(47)
		&COMM_SwitchBUSLVPlusToPOW3,				// 2	(48)
		&COMM_SwitchBUSLVPlusToPOW4,				// 3	(49)
		&COMM_SwitchBUSLVPlusToPOW5,				// 4	(50)
		&COMM_SwitchBUSLVPlusToPOW6,				// 5	(51)

		&COMM_SwitchBUSLVMinusToPOW1,				// 6	(52)
		&COMM_SwitchBUSLVMinusToPOW2,				// 7	(53)
		&COMM_SwitchBUSLVMinusToPOW3,				// 8	(54)
		&COMM_SwitchBUSLVMinusToPOW4,				// 9	(55)
		&COMM_SwitchBUSLVMinusToPOW5,				// 10	(56)
		&COMM_SwitchBUSLVMinusToPOW6				// 11	(57)
		};

void COMM_MakeMeasCommutateTable(uint8_t NumbTable, uint8_t TypeMeasure, uint8_t TypeCase, uint8_t TypePositionOfCase,
		uint8_t TypeCtrl, uint8_t TypeSignalAsLeakAge, uint8_t SignalDirection, uint64_t NumRelay);

void COMM_InitTable();

void COMM_InitTable()
{
//MEAS_CURR_LEAK
	COMM_MakeMeasCommutateTable(0, COMM_MEAS_CURR_LEAK, CASE_A1, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(1, COMM_MEAS_CURR_LEAK, CASE_A1, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(2, COMM_MEAS_CURR_LEAK, CASE_I1, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(3, COMM_MEAS_CURR_LEAK, CASE_I1, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(4, COMM_MEAS_CURR_LEAK, CASE_I1, POS_2, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(5, COMM_MEAS_CURR_LEAK, CASE_I6, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(6, COMM_MEAS_CURR_LEAK, CASE_B1, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(7, COMM_MEAS_CURR_LEAK, CASE_B2, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(8, COMM_MEAS_CURR_LEAK, CASE_B5, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(9, COMM_MEAS_CURR_LEAK, CASE_V1, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(10, COMM_MEAS_CURR_LEAK, CASE_V2, POS_1, CTRL_AC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(11, COMM_MEAS_CURR_LEAK, CASE_V2, POS_1, CTRL_AC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl2 | COMM_Ctrl2ToCtrl1 | COMM_PotCtrlPlusToCtrlPot2 | COMM_PotCtrlMinusToCtrlPot1);
	COMM_MakeMeasCommutateTable(12, COMM_MEAS_CURR_LEAK, CASE_V2, POS_2, CTRL_AC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);
	COMM_MakeMeasCommutateTable(13, COMM_MEAS_CURR_LEAK, CASE_V2, POS_2, CTRL_AC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl4 | COMM_Ctrl2ToCtrl3 | COMM_PotCtrlPlusToCtrlPot4 | COMM_PotCtrlMinusToCtrlPot3);

	COMM_MakeMeasCommutateTable(14, COMM_MEAS_CURR_LEAK, CASE_V104, POS_1, CTRL_AC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(15, COMM_MEAS_CURR_LEAK, CASE_V104, POS_1, CTRL_AC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl2 | COMM_Ctrl2ToCtrl1 | COMM_PotCtrlPlusToCtrlPot2 | COMM_PotCtrlMinusToCtrlPot1);
	COMM_MakeMeasCommutateTable(16, COMM_MEAS_CURR_LEAK, CASE_V104, POS_2, CTRL_AC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);
	COMM_MakeMeasCommutateTable(17, COMM_MEAS_CURR_LEAK, CASE_V104, POS_2, CTRL_AC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl4 | COMM_Ctrl2ToCtrl3 | COMM_PotCtrlPlusToCtrlPot4 | COMM_PotCtrlMinusToCtrlPot3);

	COMM_MakeMeasCommutateTable(18, COMM_MEAS_CURR_LEAK, CASE_V108, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(19, COMM_MEAS_CURR_LEAK, CASE_L1, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(20, COMM_MEAS_CURR_LEAK, CASE_L1, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(21, COMM_MEAS_CURR_LEAK, CASE_L2, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(22, COMM_MEAS_CURR_LEAK, CASE_L2, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(23, COMM_MEAS_CURR_LEAK, CASE_L2, POS_2, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW3 | COMM_BUSHVMinusToPOW4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);
	COMM_MakeMeasCommutateTable(24, COMM_MEAS_CURR_LEAK, CASE_L2, POS_2, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW4 | COMM_BUSHVMinusToPOW3 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(25, COMM_MEAS_CURR_LEAK, CASE_D1, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(26, COMM_MEAS_CURR_LEAK, CASE_D1, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(27, COMM_MEAS_CURR_LEAK, CASE_D1, POS_2, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW3 | COMM_BUSHVMinusToPOW4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(28, COMM_MEAS_CURR_LEAK, CASE_D1, POS_2, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW4 | COMM_BUSHVMinusToPOW3 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(29, COMM_MEAS_CURR_LEAK, CASE_D1, POS_3, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW5 | COMM_BUSHVMinusToPOW6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(30, COMM_MEAS_CURR_LEAK, CASE_D1, POS_3, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW6 | COMM_BUSHVMinusToPOW5 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(31, COMM_MEAS_CURR_LEAK, CASE_D2, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(32, COMM_MEAS_CURR_LEAK, CASE_D2, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(33, COMM_MEAS_CURR_LEAK, CASE_D2, POS_2, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW3 | COMM_BUSHVMinusToPOW4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(34, COMM_MEAS_CURR_LEAK, CASE_D2, POS_2, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW4 | COMM_BUSHVMinusToPOW3 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(35, COMM_MEAS_CURR_LEAK, CASE_D2, POS_3, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW5 | COMM_BUSHVMinusToPOW6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(36, COMM_MEAS_CURR_LEAK, CASE_D2, POS_3, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW6 | COMM_BUSHVMinusToPOW5 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(37, COMM_MEAS_CURR_LEAK, CASE_D192, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(38, COMM_MEAS_CURR_LEAK, CASE_D192, POS_1, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(39, COMM_MEAS_CURR_LEAK, CASE_D192, POS_1, CTRL_AC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(40, COMM_MEAS_CURR_LEAK, CASE_D192, POS_1, CTRL_AC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(41, COMM_MEAS_CURR_LEAK, CASE_D192, POS_2, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW3 | COMM_BUSHVMinusToPOW4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(42, COMM_MEAS_CURR_LEAK, CASE_D192, POS_2, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW4 | COMM_BUSHVMinusToPOW3 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(43, COMM_MEAS_CURR_LEAK, CASE_D192, POS_2, CTRL_AC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW3 | COMM_BUSHVMinusToPOW4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(44, COMM_MEAS_CURR_LEAK, CASE_D192, POS_2, CTRL_AC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW4 | COMM_BUSHVMinusToPOW3 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(45, COMM_MEAS_CURR_LEAK, CASE_D192, POS_3, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW5 | COMM_BUSHVMinusToPOW6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(46, COMM_MEAS_CURR_LEAK, CASE_D192, POS_3, CTRL_DC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW6 | COMM_BUSHVMinusToPOW5 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(47, COMM_MEAS_CURR_LEAK, CASE_D192, POS_3, CTRL_AC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW5 | COMM_BUSHVMinusToPOW6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(48, COMM_MEAS_CURR_LEAK, CASE_D192, POS_3, CTRL_AC_V, LEAK_DC, REVERSE, COMM_BUSHVPlusToPOW6 | COMM_BUSHVMinusToPOW5 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	// MEAS_DROP_VOLT
	COMM_MakeMeasCommutateTable(49, COMM_MEAS_DROP_VOLT, CASE_A1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(50, COMM_MEAS_DROP_VOLT, CASE_A1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(51, COMM_MEAS_DROP_VOLT, CASE_I1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(52, COMM_MEAS_DROP_VOLT, CASE_I1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(53, COMM_MEAS_DROP_VOLT, CASE_I6, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(54, COMM_MEAS_DROP_VOLT, CASE_B1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(55, COMM_MEAS_DROP_VOLT, CASE_B2, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(56, COMM_MEAS_DROP_VOLT, CASE_B5, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(57, COMM_MEAS_DROP_VOLT, CASE_V1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(58, COMM_MEAS_DROP_VOLT, CASE_V2, POS_1, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(59, COMM_MEAS_DROP_VOLT, CASE_V2, POS_2, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(60, COMM_MEAS_DROP_VOLT, CASE_V104, POS_1, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(61, COMM_MEAS_DROP_VOLT, CASE_V104, POS_2, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(62, COMM_MEAS_DROP_VOLT, CASE_V108, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot1);

	COMM_MakeMeasCommutateTable(63, COMM_MEAS_DROP_VOLT, CASE_L1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(64, COMM_MEAS_DROP_VOLT, CASE_L1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(65, COMM_MEAS_DROP_VOLT, CASE_L2, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(66, COMM_MEAS_DROP_VOLT, CASE_L2, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(67, COMM_MEAS_DROP_VOLT, CASE_L2, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);
	COMM_MakeMeasCommutateTable(68, COMM_MEAS_DROP_VOLT, CASE_L2, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(69, COMM_MEAS_DROP_VOLT, CASE_D1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(70, COMM_MEAS_DROP_VOLT, CASE_D1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(71, COMM_MEAS_DROP_VOLT, CASE_D1, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(72, COMM_MEAS_DROP_VOLT, CASE_D1, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(73, COMM_MEAS_DROP_VOLT, CASE_D1, POS_3, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(74, COMM_MEAS_DROP_VOLT, CASE_D1, POS_3, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(75, COMM_MEAS_DROP_VOLT, CASE_D2, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(76, COMM_MEAS_DROP_VOLT, CASE_D2, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(77, COMM_MEAS_DROP_VOLT, CASE_D2, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(78, COMM_MEAS_DROP_VOLT, CASE_D2, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(79, COMM_MEAS_DROP_VOLT, CASE_D2, POS_3, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(80, COMM_MEAS_DROP_VOLT, CASE_D2, POS_3, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(81, COMM_MEAS_DROP_VOLT, CASE_D192, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(82, COMM_MEAS_DROP_VOLT, CASE_D192, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(83, COMM_MEAS_DROP_VOLT, CASE_D192, POS_1, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(84, COMM_MEAS_DROP_VOLT, CASE_D192, POS_1, CTRL_AC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(85, COMM_MEAS_DROP_VOLT, CASE_D192, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(86, COMM_MEAS_DROP_VOLT, CASE_D192, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(87, COMM_MEAS_DROP_VOLT, CASE_D192, POS_2, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(88, COMM_MEAS_DROP_VOLT, CASE_D192, POS_2, CTRL_AC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(89, COMM_MEAS_DROP_VOLT, CASE_D192, POS_3, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(90, COMM_MEAS_DROP_VOLT, CASE_D192, POS_3, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(91, COMM_MEAS_DROP_VOLT, CASE_D192, POS_3, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(92, COMM_MEAS_DROP_VOLT, CASE_D192, POS_3, CTRL_AC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

//	MEAS_IN_VOLT
	COMM_MakeMeasCommutateTable(93, COMM_MEAS_IN_VOLT, CASE_A1, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(94, COMM_MEAS_IN_VOLT, CASE_I1, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(95, COMM_MEAS_IN_VOLT, CASE_I6, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(96, COMM_MEAS_IN_VOLT, CASE_B1, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(97, COMM_MEAS_IN_VOLT, CASE_B2, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(98, COMM_MEAS_IN_VOLT, CASE_B5, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(99, COMM_MEAS_IN_VOLT, CASE_V1, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(100, COMM_MEAS_IN_VOLT, CASE_V2, POS_1, CTRL_AC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(101, COMM_MEAS_IN_VOLT, CASE_V2, POS_2, CTRL_AC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(102, COMM_MEAS_IN_VOLT, CASE_V104, POS_1, CTRL_AC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(103, COMM_MEAS_IN_VOLT, CASE_V104, POS_2, CTRL_AC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(104, COMM_MEAS_IN_VOLT, CASE_V108, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(105, COMM_MEAS_IN_VOLT, CASE_L1, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(106, COMM_MEAS_IN_VOLT, CASE_L2, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(107, COMM_MEAS_IN_VOLT, CASE_L2, POS_2, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(108, COMM_MEAS_IN_VOLT, CASE_D1, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(109, COMM_MEAS_IN_VOLT, CASE_D2, POS_1, CTRL_DC_V, IGNORE, IGNORE, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(110, COMM_MEAS_IN_VOLT, CASE_D192, POS_1, CTRL_DC_V, IGNORE, IGNORE,  COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(111, COMM_MEAS_IN_VOLT, CASE_D192, POS_3, CTRL_AC_V, IGNORE, IGNORE,  COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

// MEAS_VOLT_BAN
	COMM_MakeMeasCommutateTable(112, COMM_MEAS_VOLT_BAN, CASE_A1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(113, COMM_MEAS_VOLT_BAN, CASE_A1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(114, COMM_MEAS_VOLT_BAN, CASE_I1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(115, COMM_MEAS_VOLT_BAN, CASE_I1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(116, COMM_MEAS_VOLT_BAN, CASE_I6, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(117, COMM_MEAS_VOLT_BAN, CASE_B1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(118, COMM_MEAS_VOLT_BAN, CASE_B2, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(119, COMM_MEAS_VOLT_BAN, CASE_B5, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(120, COMM_MEAS_VOLT_BAN, CASE_V1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(121, COMM_MEAS_VOLT_BAN, CASE_V2, POS_1, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(122, COMM_MEAS_VOLT_BAN, CASE_V2, POS_2, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(123, COMM_MEAS_VOLT_BAN, CASE_V104, POS_1, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(124, COMM_MEAS_VOLT_BAN, CASE_V104, POS_2, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(125, COMM_MEAS_VOLT_BAN, CASE_V108, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot1);

	COMM_MakeMeasCommutateTable(126, COMM_MEAS_VOLT_BAN, CASE_L1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(127, COMM_MEAS_VOLT_BAN, CASE_L1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(128, COMM_MEAS_VOLT_BAN, CASE_L2, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(129, COMM_MEAS_VOLT_BAN, CASE_L2, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(130, COMM_MEAS_VOLT_BAN, CASE_L2, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);
	COMM_MakeMeasCommutateTable(131, COMM_MEAS_VOLT_BAN, CASE_L2, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl3 | COMM_Ctrl2ToCtrl4 | COMM_PotCtrlPlusToCtrlPot3 | COMM_PotCtrlMinusToCtrlPot4);

	COMM_MakeMeasCommutateTable(132, COMM_MEAS_VOLT_BAN, CASE_D1, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(133, COMM_MEAS_VOLT_BAN, CASE_D1, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(134, COMM_MEAS_VOLT_BAN, CASE_D1, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(135, COMM_MEAS_VOLT_BAN, CASE_D1, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(136, COMM_MEAS_VOLT_BAN, CASE_D1, POS_3, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(137, COMM_MEAS_VOLT_BAN, CASE_D1, POS_3, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(138, COMM_MEAS_VOLT_BAN, CASE_D2, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(139, COMM_MEAS_VOLT_BAN, CASE_D2, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(140, COMM_MEAS_VOLT_BAN, CASE_D2, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(141, COMM_MEAS_VOLT_BAN, CASE_D2, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(142, COMM_MEAS_VOLT_BAN, CASE_D2, POS_3, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(143, COMM_MEAS_VOLT_BAN, CASE_D2, POS_3, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(144, COMM_MEAS_VOLT_BAN, CASE_D192, POS_1, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(145, COMM_MEAS_VOLT_BAN, CASE_D192, POS_1, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(146, COMM_MEAS_VOLT_BAN, CASE_D192, POS_1, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTMinusToPOT2 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(147, COMM_MEAS_VOLT_BAN, CASE_D192, POS_1, CTRL_AC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW2 | COMM_BUSLVMinusToPOW1 | COMM_POTPlusToPOT2 | COMM_POTMinusToPOT1 | COMM_POTOutToPOT1 | COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(148, COMM_MEAS_VOLT_BAN, CASE_D192, POS_2, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(149, COMM_MEAS_VOLT_BAN, CASE_D192, POS_2, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(150, COMM_MEAS_VOLT_BAN, CASE_D192, POS_2, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW3 | COMM_BUSLVMinusToPOW4 | COMM_POTPlusToPOT3 | COMM_POTMinusToPOT4 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(151, COMM_MEAS_VOLT_BAN, CASE_D192, POS_2, CTRL_AC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW4 | COMM_BUSLVMinusToPOW3 | COMM_POTPlusToPOT4 | COMM_POTMinusToPOT3 | COMM_POTOutToPOT3 | COMM_POTOutToPOT4 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(152, COMM_MEAS_VOLT_BAN, CASE_D192, POS_3, CTRL_DC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(153, COMM_MEAS_VOLT_BAN, CASE_D192, POS_3, CTRL_DC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(154, COMM_MEAS_VOLT_BAN, CASE_D192, POS_3, CTRL_AC_V, IGNORE, FORVARD, COMM_BUSLVPlusToPOW5 | COMM_BUSLVMinusToPOW6 | COMM_POTPlusToPOT5 | COMM_POTMinusToPOT6 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
	COMM_MakeMeasCommutateTable(155, COMM_MEAS_VOLT_BAN, CASE_D192, POS_3, CTRL_AC_V, IGNORE, REVERSE, COMM_BUSLVPlusToPOW6 | COMM_BUSLVMinusToPOW5 | COMM_POTPlusToPOT6 | COMM_POTMinusToPOT5 | COMM_POTOutToPOT5 | COMM_POTOutToPOT6 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);
}

void COMM_MakeMeasCommutateTable(uint8_t NumbTable, uint8_t TypeMeasure, uint8_t TypeCase, uint8_t TypePositionOfCase,
		uint8_t TypeCtrl, uint8_t TypeSignalAsLeakAge, uint8_t SignalDirection, uint64_t NumRelay)
{
	COMM_Table[NumbTable].TypeMeasure = TypeMeasure;
	COMM_Table[NumbTable].TypeCase = TypeCase;
	COMM_Table[NumbTable].TypePositionOfCase = TypePositionOfCase;
	COMM_Table[NumbTable].TypeCtrl = TypeCtrl;
	COMM_Table[NumbTable].TypeSignalAsLeakAge = TypeSignalAsLeakAge;
	COMM_Table[NumbTable].SignalDirection = SignalDirection;
	COMM_Table[NumbTable].Relay = NumRelay;
}
