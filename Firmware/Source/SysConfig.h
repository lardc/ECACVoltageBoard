#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H


// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x08008000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// Тактовая частота системной шины процессора
#define QUARTZ_FREQUENCY				20000000	// Частота кварца
// ----------------------------------------------

// USART
#define USART_BAUDRATE					115200		// Скорость USART
#define USART_FIFOlen					32			// Длина FIFO USART
// ----------------------------------------------

// PWM
#define PWM_FREQUENCY					20000		// в Гц
#define PWM_PERIOD						(1000000 / PWM_FREQUENCY)	// в мкс
// ----------------------------------------------

// Timers
#define TIMER7_uS						1000		// в мкс
// ----------------------------------------------

// CAN
#define CAN_BAUDRATE					1000000		// Битрейт CAN
// ----------------------------------------------

// High-speed sampling
#define DMA_ADC1_V_CHANNEL				DMA1_Channel1	// Канал DMA для АЦП напряжения
#define DMA_ADC2_I_CHANNEL				DMA2_Channel1	// Канал DMA для АЦП тока
//
#define ADC1_VOLTAGE_CHANNEL			1				// АЦП1 номер канала напряжения
#define ADC2_CURRENT_CHANNEL			1				// АЦП2 номер канала тока
// ----------------------------------------------

#endif // __SYSCONFIG_H
