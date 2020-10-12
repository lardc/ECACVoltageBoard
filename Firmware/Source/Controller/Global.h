#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT			2		// Количество массивов для записи
#define EP_COUNT				5		// Количество массивов для чтения
#define ENABLE_LOCKING			FALSE	// Защита NV регистров паролем

// Временные параметры
#define TIME_LED_BLINK			500		// Мигание светодиодом (в мс)

#define ADC_BUFF_SIZE 			1		// Размер буфера ДМА для АЦП
#define VALUES_x_SIZE			1000	// Размер буфера Epoint

#define HW_MAX_LINE				2		// Колличество ццепей для подачи сигнала

#define SW_MAX_KOEFF_P			10000	// Максимальное значение коэффициента П
#define SW_MAX_KOEFF_I			10000	// Максимальное значение коэффициента И

#define SW_MAX_U_Low			45		// Нижний диапазон измерения напряжения
#define SW_MAX_U_High			310 	// Верхний диапазон имзмерения напряжения
#define SW_MAX_I_Low			300		// Нижний диапазон имзмерения тока
#define SW_MAX_I_Middle			5000	// Средний диапазон имзмерения тока
#define SW_MAX_I_HighH			1		// Верхняя диапазон имзмерения тока HiWord
#define SW_MAX_I_HighL			44464	// Верхняя диапазон имзмерения тока LoWord

#define HW_MAX_VOLTAGE			310		// Максимальное задаваемое напряжение
#define HW_MAX_CURRENT_LWORD	65535	// Максимальный задаваемый ток - младшее слово
#define HW_MAX_CURRENT_HWORD	1		// Максимальный задаваемый ток - старшее слово

// Параметры АЦП
#define ADC_REF					3300	// Опорное напряжение, мВ
#define ADC_12BIT_MAX_VAL		4095	// Максимальное разрешение АЦП

#endif //  __GLOBAL_H
