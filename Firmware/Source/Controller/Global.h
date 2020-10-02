#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT			2		// Количество массивов для записи
#define EP_COUNT				4		// Количество массивов для чтения
#define ENABLE_LOCKING			FALSE	// Защита NV регистров паролем

// Временные параметры
#define TIME_LED_BLINK			500		// Мигание светодиодом (в мс)

#define ADC_BUFF_SIZE 			5		// Размер буфера ДМА для АЦП
#define VALUES_x_SIZE			101		// Размер буфера Epoint

#define KU_DEVIDER				206.66	// Коэффициент делителя по напряжению
#define KU_H					1.0		// Коэфф. усиления в вверхнем диапазоне
#define KU_L					7.6		// Коэфф. усиления в нижнем диапазоне

#define R_H						10010	// Сопротивление верхнего диапазона в цепи токового ОУ
#define R_M						10200	// Сопротивление среднего диапазона
#define R_L						13000	// Сопротивление нижнего диапазона


#define HW_MAX_VOLTAGE			310		// Максимальное выходное амплитудное напряжение (в В)
#define HW_MAX_CURRENT			11000	// Максимальный ток	(x10 в мкА)

#define HW_I_RANGE_L			30		// Верхняя граница диапазона имзмерения тока (x10 в мкА)
#define HW_I_RANGE_M			500 	// Верхняя граница диапазона имзмерения тока (x10 в мкА)
#define HW_I_RANGE_H			11000	// Верхняя граница диапазона имзмерения тока (x10 в мкА)

#define HW_U_RANGE_L			45		// Верхняя граница диапазона имзмерения напряжения (в В)
#define HW_U_RANGE_H			330		// Верхняя граница диапазона имзмерения напряжения(в В)

#define HW_MAX_VARIANT_POLARITY	2		// Количество варантов полярности сигнала
#define HW_MAX_TIME_PULSE		10		// Длительность сигнала
#define HW_MAX_LINE				2		// Колличество ццепей для подачи сигнала

#define SW_MAX_KOEFF_P			10000	// Максимальное значение коэффициента П
#define SW_MAX_KOEFF_I			10000	// Максимальное значение коэффициента И

// Параметры АЦП
#define ADC_REF					3300	// Опорное напряжение
#define ADC_12BIT_MAX_VAL		4095	// Максимальное разрешение АЦП
#define ADC_RESOLUTION			(ADC_12BIT_MAX_VAL / ADC_REF) // Разрешение АЦП

#endif //  __GLOBAL_H
