// Header
#include "Timer1PWM.h"

// Includes
#include "ZwTIM.h"
#include "ZwRCC.h"
#include "SysConfig.h"

// Defines
#define T1PWM_CLOCK			20000
#define T1PWM_PERIOD		(1000000L / T1PWM_CLOCK)
#define T1PWM_MAX_OUTPUT	0.95f

// Variables
static uint32_t PWMBase = 0;

// Functions
void T1PWM_Init(float SystemClock, uint16_t Period)
{
	// ������ ����������� ���
	uint32_t Prescaler = (uint32_t)(SystemClock / 1000000 * Period / 65536);
	PWMBase = (uint32_t)((SystemClock / ((Prescaler + 1) * 1000000)) * Period);

	// ����������� �������������
	TIM_Clock_En(TIM_1);
	TIM_Config(TIM1, SYSCLK, T1PWM_PERIOD);
	TIM_Interupt(TIM1, 0, true);

	// ����� ������ ��� - PWM mode 1
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;

	// ��������� ������� Preload
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	// ��������� ������� AutoPreload
	TIM1->CR1 |= TIM_CR1_ARPE;
	// ��������� ������ Preload ��� �������� ����������
	TIM1->CR2 |= TIM_CR2_CCPC;

	// ���������� ������ ������� �� �����
	TIM1->BDTR |= TIM_BDTR_MOE;

	// ������������� ���������� ���������
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->SR &= ~TIM_SR_UIF;
}
//------------------------------------------------

void T1PWM_SetDutyCycle(float Value)
{
	// ����� ���������� �������������
	if(Value > 0)
	{
		TIM1->CCER |= TIM_CCER_CC1E;
		TIM1->CCER &= ~TIM_CCER_CC1NE;
	}
	else if(Value < 0)
	{
		TIM1->CCER &= ~TIM_CCER_CC1E;
		TIM1->CCER |= TIM_CCER_CC1NE;

		// ����� ����� ��� ������������� ��������
		Value = -Value;
	}
	else
		TIM1->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC1NE);

	// �������� �������� �� ���������
	float MaxOutput = T1PWM_MAX_OUTPUT * PWMBase;
	TIM1->ARR = (uint32_t)((Value > MaxOutput) ? MaxOutput : Value);
}
//------------------------------------------------

void T1PWM_Start()
{
	TIM_Start(TIM1);
}
//------------------------------------------------

void T1PWM_Stop()
{
	T1PWM_SetDutyCycle(0);
	TIM_Stop(TIM1);
}
//------------------------------------------------
