#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Includes
#include "stdinc.h"
#include "CommutationTable.h"

// Variable
bool COMM_ReturnResultConnectGroup();
bool COMM_ReturnResultChekExistParametrs();

// Functions
void COMM_DisconnectSimpleRelays();
void COMM_DisconnectBistableRelays();
void COMM_SwitchBistableRelay(uint8_t IndexRelay, bool NewState);
void COMM_SwitchSimpleRelay(uint8_t IndexRelay, bool NewState);
void COMM_DisconnectAllRelay();
void COMM_CommutateGroupOnTableNumber(uint8_t NumbOfTable);

#endif // __COMMUTATOR_H
