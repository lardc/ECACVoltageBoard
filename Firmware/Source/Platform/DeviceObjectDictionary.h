#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_FAULT_CLEAR					3	// Очистка fault
#define ACT_WARNING_CLEAR				4	// Очистка warning

#define ACT_SET_RELAY_GROUP				20 	// Подключить группу реле (на основании корпуса и т.д.)
#define ACT_SET_RELAY_NONE				21 	// Отключить все релле
#define ACT_SET_RELAY_TABLE				22 	// Подключить группу реле по номеру таблицы

#define ACT_DBG_LED_RED_IMPULSE			50	// Одиночный импусль цепи красного индикатора
#define ACT_DBG_LED_GREEN_IMPULSE		51	// Одиночный импусль цепи зелёного индикатора
#define ACT_DBG_SYNC_1_IMPULSE			52	// Одиночный импусль цепи SYNC_1
#define ACT_DBG_SYNC_2_IMPULSE			53	// Одиночный импусль цепи SYNC_2
#define ACT_DBG_LOCK_1_IMPULSE			54	// Одиночный импусль цепи LOCK1
#define ACT_DBG_LOCK_2_IMPULSE			55	// Одиночный импусль цепи LOCK2
#define ACT_DBG_SIMPLE_RELAY_ON 		56	// Включить одно обычное реле
#define ACT_DBG_SIMPLE_RELAY_OFF 		57	// Отключить одно обычноее реле
#define ACT_DBG_BISTABLE_RELAY_ON 		58	// Включить одно бистабильное реле
#define ACT_DBG_BISTABLE_RELAY_OFF		59	// Отключить одно бистабильное реле
#define ACT_DBG_SAFETY_DISABLE			60	// Отключение датчиков безопасности
#define ACT_DBG_SAFETY_ENABLE			61	// Включение датчиков безопасности

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры

// Несохраняемы регистры чтения-записи
#define REG_TYPE_MEASURE				130	// Тип измерения
#define REG_TYPE_CASE					131	// Тип корпуса
#define REG_POSITION_OF_CASE			132	// Позиция
#define REG_TYPE_SIGNAL_CTRL			133	// Тип управления
#define REG_TYPE_SIGNAL_AT_LEAKAGE		134	// Тип сигнала при утечке
#define REG_TYPE_POLARITY				135	// Полярность подключения

#define REG_NUM_TABLE					140	// Номер подключаемой таблици

#define REG_DBG_STATE					150	// Регистр режима Отладки
#define REG_DBG_RELAY_INDEX				151	// Регистр номера реле из CommutateTable

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
#define REG_BUTTON_START				199	// Регистр состояния кнопки старт
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

//  Fault and disable codes
#define DF_NONE							0

// Problem
#define PROBLEM_NONE					0
#define PROBLEM_BUTTON_STOP				1
#define PROBLEM_SENS					2

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

// Start button state
#define BUTT_START_IS_UNPRESSED			0
#define BUTT_START_IS_PRESSED			1

#endif //  __DEV_OBJ_DIC_H
