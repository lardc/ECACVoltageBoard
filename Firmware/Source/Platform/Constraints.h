#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

// Definitions
#define NO		0
#define YES		1

#define REGULATOR_K_MAX			10000

#define SHUNT_RES_MIN			1
#define SHUNT_RES_MAX			60000
#define SHUNT_RES_DEF			1000

#define VOLTAGE_OUTPUT_MIN		1
#define VOLTAGE_OUTPUT_MAX		350
#define VOLTAGE_OUTPUT_DEF		10

#define CURRENT_OUTPUT_MIN		1
#define CURRENT_OUTPUT_MAX		1000
#define CURRENT_OUTPUT_DEF		10

// Types
typedef struct __TableItemConstraint
{
	Int16U Min;
	Int16U Max;
	Int16U Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE];
extern const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START];

#endif // __CONSTRAINTS_H
