#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT			0		// Количество массивов для записи
#define EP_COUNT				0		// Количество массивов для чтения
#define ENABLE_LOCKING			FALSE	// Защита NV регистров паролем

// Временные параметры
#define TIME_LED_BLINK			500	// Мигание светодиодом (в мс)

//
#define SIN_BUFF_SIZE 			101		// Размер буфера ДМА для ШИМ
#define ADC_DMA_BUFF_SIZE 		8		// Размер буфера ДМА для АЦП

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

// Параметры АЦП
#define ADC_REF_MV				3300	// Опорное напряжение
#define ADC_RESOLUTION			4095	// Максимальное разрешение АЦП

#endif //  __GLOBAL_H
