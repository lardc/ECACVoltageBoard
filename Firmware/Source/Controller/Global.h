#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS		1000	// ������� ���������� SCCI (� ��)
#define EP_WRITE_COUNT			0		// ���������� �������� ��� ������
#define EP_COUNT				0		// ���������� �������� ��� ������
#define ENABLE_LOCKING			FALSE	// ������ NV ��������� �������

// ��������� ���������
#define TIME_LED_BLINK			500	// ������� ����������� (� ��)

//
#define SIN_BUFF_SIZE 			101		// ������ ������ ��� ��� ���
#define ADC_DMA_BUFF_SIZE 		8		// ������ ������ ��� ��� ���

#define HW_MAX_VOLTAGE			310		// ������������ �������� ����������� ���������� (� �)
#define HW_MAX_CURRENT			11000	// ������������ ���	(x10 � ���)

#define HW_I_RANGE_L			30		// ������� ������� ��������� ���������� ���� (x10 � ���)
#define HW_I_RANGE_M			500 	// ������� ������� ��������� ���������� ���� (x10 � ���)
#define HW_I_RANGE_H			11000	// ������� ������� ��������� ���������� ���� (x10 � ���)

#define HW_U_RANGE_L			45		// ������� ������� ��������� ���������� ���������� (� �)
#define HW_U_RANGE_H			330		// ������� ������� ��������� ���������� ����������(� �)

#define HW_MAX_VARIANT_POLARITY	2		// ���������� �������� ���������� �������
#define HW_MAX_TIME_PULSE		10		// ������������ �������
#define HW_MAX_LINE				2		// ����������� ������ ��� ������ �������

// ��������� ���
#define ADC_REF_MV				3300	// ������� ����������
#define ADC_RESOLUTION			4095	// ������������ ���������� ���

#endif //  __GLOBAL_H
