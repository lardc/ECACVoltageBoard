#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_FAULT_CLEAR					3	// Очистка fault
#define ACT_WARNING_CLEAR				4	// Очистка warning

#define ACT_START_SIGNAL				20	// Запуск формирования сигнала
#define ACT_STOP_SIGNAL					21	// Остановка формирования сигнала

#define ACT_DBG_SYNC_1_IMPULSE			50 // Сигнал синхронизации
#define ACT_DBG_SYNC_2_IMPULSE			51 // Сигнал синхронизации
#define ACT_DBG_SET_STATE_CTRL_RELAY	52 // Изменить состояние реле цепи CTRL
#define ACT_DBG_SET_STATE_POW_RELAY		53 // Изменить состояние реле цепи POW
#define ACT_DBG_SIN						54 // Запуск формирования сигнала

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры
#define REG_Kp							0	// Коэффициент регулятора П
#define REG_Ki							1	// Коэффициент регулятора И

#define REG_HW_U_RANGE_L				10	// Граница L-диапазона по напряжению
#define REG_HW_U_RANGE_H				11	// Граница H-диапазона по напряжению
#define REG_HW_I_RANGE_L				12	// Граница L-диапазона по току
#define REG_HW_I_RANGE_M				13	// Граница M-диапазона по току
#define REG_HW_I_RANGE_HH				14	// Граница H-диапазона по току HWord
#define REG_HW_I_RANGE_HL				15	// Граница H-диапазона по току LWord

// Несохраняемы регистры чтения-записи
#define REG_SIN_VOLTAGE					128 // Амплитуда напряжение выходного сигнала, В
#define REG_SIN_CURRENT					129 // Амплитуда тока выходного сигнала, мкА
#define REG_SIN_TO_LINE					132 // Канал подачи сигнала POW, CTRL или в никуда

#define REG_DBG_RELAY_CTRL_STATE		150	// Регистр состояния
#define REG_DBG_RELAY_POW_STATE			151	// Регистр состояния

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
#define REG_SIGNAL_OUT					198 // Состояние выходной цепи
// -----------------------------
#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

// ENDPOINTS
#define EP_I_RAW						1	// Сырые значения I
#define EP_V_RAW						2	// Сырые значения V
#define EP_I							3	// Расчетное значение I
#define EP_V							4	// Расчетное значение V

//  Fault and disable codes
#define DF_NONE							0

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

#endif //  __DEV_OBJ_DIC_H
