// Header
#include "PWM.h"

// Includes
#include "Measure.h"
#include "LowLevel.h"
#include "DataTable.h"
#include "math.h"
#include "ZwTIM.h"
#include "Delay.h"
#include "ZwDMA.h"
#include "Global.h"
#include "ZwADC.h"
#include "Controller.h"

// Defines
#define DMA1_CHANEL2			32
#define POLARITY_FULL			0
#define POLARITY_POSITIVE		1
#define POLARITY_NEGATIVE		2
#define PWM_SET_POSITIVE_OUT	TIM1->CCER  &= ~ TIM_CCER_CC1NE; TIM1->CCER |= TIM_CCER_CC1E;
#define PWM_SET_NEGATIVE_OUT	TIM1->CCER  &= ~ TIM_CCER_CC1E; TIM1->CCER |= TIM_CCER_CC1NE;
#define PWM_SET_DISABLE_OUT		TIM1->CCER  &= ~ (TIM_CCER_CC1E | TIM_CCER_CC1NE);
#define PWM_TIM1_OUT_ENABLE		(TIM1->BDTR |= TIM_BDTR_MOE)
#define PWM_TIM1_OUT_DISABLE	(TIM1->BDTR &= ~TIM_BDTR_MOE)
#define PWM_TIM1_GenerateEvent	(TIM1->EGR |= TIM_EGR_UG);

// Variables
volatile uint16_t TIM1_DMA_Buffer[SIN_BUFF_SIZE + 1] = {0};

// Functions
void PWM_PrepareTable(uint16_t Amplitude);
void PWM_GenerateSignal();
void PWM_GenFullSinusPulse();
void PWM_PositivePulse();
void PWM_NegativePulse();
void PWM_Stop();
void PWM_Start();
void PWM_WaitEndPulse();
void PWM_SaveEndPoint();
void PWM_CopyRAWFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);
void PWM_CopyVoltageFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);
void PWM_CopyCurrentFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin);

void PWM_PrepareAndGenerateSignal(uint16_t Voltage, uint32_t Current, uint8_t Polarity)
{
	MEAS_SetMeasureRange(Voltage, Current);
	PWM_PrepareTable(Voltage);
	ADC_SamplingStart(ADC1);
	switch (Polarity)
	{
		case POLARITY_FULL:
			{
				PWM_GenFullSinusPulse();
			}
			break;
		case POLARITY_POSITIVE:
			{
				PWM_SET_POSITIVE_OUT;
				PWM_GenerateSignal();
			}
			break;
		case POLARITY_NEGATIVE:
			{
				PWM_SET_NEGATIVE_OUT;
				PWM_GenerateSignal();
			}
			break;

		default:
			break;
	}
	ADC_SamplingStop(ADC1);
	PWM_SET_DISABLE_OUT;
	PWM_SaveEndPoint();
}
//------------------------------------------

void PWM_PrepareTable(uint16_t Amplitude)
{
	volatile double_t MaxPWM_RAW = 3500 * 0.9;
	volatile double_t PWM_Razradnost = (double_t)HW_MAX_VOLTAGE / MaxPWM_RAW;
	volatile double_t PWM_RAW = (double_t)Amplitude / PWM_Razradnost;
	volatile double_t A, D, B;
	volatile double_t Step = M_PI / SIN_BUFF_SIZE;
	for(uint16_t i = 0; i < (SIN_BUFF_SIZE + 1); i++)
	{
		A = Step * i;
		D = (double_t)sin(A);
		B = PWM_RAW * D;
		TIM1_DMA_Buffer[i] = (uint16_t)B;
	}
}
//------------------------------------------

void PWM_GenerateSignal()
{
	PWM_Start();
	PWM_WaitEndPulse();
	PWM_Stop();
}
//------------------------------------------

void PWM_GenFullSinusPulse()
{
	PWM_SET_POSITIVE_OUT;
	PWM_GenerateSignal();
	PWM_SET_NEGATIVE_OUT;
	PWM_GenerateSignal();
}
//------------------------------------------------

void PWM_Start()
{
	DMA1->IFCR |= (DMA_IFCR_CGIF2 | DMA_IFCR_CHTIF2 | DMA_IFCR_CTCIF2 | DMA_IFCR_CTEIF2);
	DMA1_Channel2->CNDTR = SIN_BUFF_SIZE + 1;
	DMA_ChannelEnable(DMA1_Channel2, true);
	PWM_TIM1_GenerateEvent;
	TIM_Start(TIM1);
	PWM_TIM1_OUT_ENABLE;
}
//------------------------------------------------

void PWM_Stop()
{
	PWM_TIM1_OUT_DISABLE;
	TIM1->CCR1 = 0;
	TIM_Stop(TIM1);
	DMA_ChannelEnable(DMA1_Channel2, false);
}
//------------------------------------------------

void PWM_WaitEndPulse()
{
	while(!(DMA_IsTransferComplete(DMA1, DMA1_CHANEL2)));
}
//------------------------------------------------

void PWM_ConfigureTIM1_Ch1(float SystemClock, uint16_t Period)
{
	uint32_t PSC_TEMP = (uint32_t)(SystemClock / 1000000 * Period / 65536); //Значение предделителя
	uint32_t ARR_TEMP = (uint32_t)((SystemClock / ((PSC_TEMP + 1) * 1000000)) * Period); //Значение до которого считает счетчик

	RCC_TIM_Clk_EN(TIM_1);
	TIM1->PSC = PSC_TEMP;
	TIM1->ARR = ARR_TEMP;
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM1->CR1 |= TIM_CR1_ARPE;
	TIM1->DIER |= (TIM_DIER_TDE | TIM_DIER_CC1DE | TIM_DIER_COMDE | TIM_DIER_UDE | TIM_DIER_UIE);
	TIM1->DCR &= ~TIM_DCR_DBA;
	TIM1->DCR &= ~TIM_DCR_DBL;
	TIM1->DCR |= (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 | TIM_DCR_DBA_0);
	TIM1->CR2 |= TIM_CR2_MMS2_1;
	PWM_TIM1_GenerateEvent;
	while((TIM1->EGR & TIM_EGR_UG) == true)
	{
	}
	PWM_TIM1_GenerateEvent;
	PWM_TIM1_OUT_ENABLE;
}
//------------------------------------------------

void PWM_SaveEndPoint()
{
	//Сохраняем данные в endpoints
	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC1DMABuff, (uint32_t*)&CONTROL_BuffRAWCurrent);
	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC2DMABuff, (uint32_t*)&CONTROL_BuffRAWVoltage);
	PWM_CopyVoltageFromDMAToEndPoint((uint32_t*)&ADC1DMABuff, (uint32_t*)&CONTROL_BuffCurrent);
	PWM_CopyCurrentFromDMAToEndPoint((uint32_t*)&ADC2DMABuff, (uint32_t*)&CONTROL_BuffVoltage);
}
//------------------------------------------------

void PWM_CopyRAWFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin)
{
	for(uint16_t i = 0; i < (VALUES_x_SIZE + 1); i++)
	{
		AdressEndPoin[i] = AdressDMABuff[i];
	}
}
//------------------------------------------------

void PWM_CopyVoltageFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin)
{
	double_t Resistance = 1;

	if(LL_GetStateKI_L())
	{
		Resistance = R_L;
	}
	else
	{
		if(LL_GetStateKI_M())
		{
			Resistance = R_M;
		}
		else
		{
			Resistance = R_H;
		}
	}

	for(uint16_t i = 0; i < (VALUES_x_SIZE + 1); i++)
	{
		AdressEndPoin[i] = (uint16_t)((AdressDMABuff[i] * (double_t)ADC_RESOLUTION) / Resistance);
	}
}
//------------------------------------------------

void PWM_CopyCurrentFromDMAToEndPoint(uint32_t *AdressDMABuff, uint32_t *AdressEndPoin)
{
	double_t KU = 1;

	if(LL_GetStateKU())
		KU = 7.6;

	for(uint16_t i = 0; i < (VALUES_x_SIZE + 1); i++)
	{
		AdressEndPoin[i] = (uint16_t)(AdressDMABuff[i] * (double_t)ADC_RESOLUTION * KU * KU_DEVIDER);
	}
}
//------------------------------------------------
