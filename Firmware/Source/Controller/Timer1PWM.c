// Header
#include "Timer1PWM.h"

// Includes
#include "ZwTIM.h"
#include "ZwRCC.h"
#include "SysConfig.h"

// Defines
#define T1PWM_MAX_OUTPUT	0.95f

// Variables
volatile uint32_t T1PWM_PWMBase = 0;

// Functions
void T1PWM_Init(float SystemClock, uint16_t Period)
{
	// Расчёт размерности ШИМ
	uint32_t Prescaler = (uint32_t)(SystemClock / 1000000 * Period / 65536);
	T1PWM_PWMBase = (uint32_t)((SystemClock / ((Prescaler + 1) * 1000000)) * Period);

	// Стандартная инициализация
	TIM_Clock_En(TIM_1);
	TIM_Config(TIM1, SystemClock, Period);

	// Активация функции AutoPreload ARR регистра
	TIM1->CR1 |= TIM_CR1_ARPE;
	// Режим Update mode для АЦП
	TIM1->CR2 |= TIM_CR2_MMS2_1;

	// Канал 1 - положительный
	// Режим ШИМ - PWM mode 1, c функцией Preload
	TIM1->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE);
	TIM1->CCR1 = 0;

	// Канал 2 - отрицательный
	// Режим ШИМ - PWM mode 1, c функцией Preload
	TIM1->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE);
	TIM1->CCR2 = 0;

	// Разрешение прерывания при появлении события обновления
	TIM1->DIER |=  TIM_DIER_UIE ;
	// Инициализация обновления регистров
	TIM1->EGR |= TIM_EGR_UG;
	// Сборс флага обновления
	TIM1->SR &= ~TIM_SR_UIF;

	// Разрешение выход CH1 и CH2N
	TIM1->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2NE);
	// Разрешение работы таймера на выход
	TIM1->BDTR |= TIM_BDTR_MOE;
}
//------------------------------------------------

void T1PWM_SetDutyCycle(volatile float Volue)
{
	// Выбор полярности формирователя
	float MaxOutput = T1PWM_MAX_OUTPUT * T1PWM_PWMBase;

	if(Volue > 0)
	{
		TIM1->CCR1 = (uint32_t)((Volue > MaxOutput) ? MaxOutput : Volue);
		TIM1->CCR2 = 0;
	}
	else
	{
		if(Volue < 0)
		{
			Volue = -Volue;
			TIM1->CCR1 = 0;
			TIM1->CCR2 = (uint32_t)((Volue > MaxOutput) ? MaxOutput : Volue);
		}
		else
		{
			TIM1->CCR1 = TIM1->CCR2 = 0;
		}
	}
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
