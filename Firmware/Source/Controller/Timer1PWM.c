// Header
#include "Timer1PWM.h"

// Includes
#include "ZwTIM.h"
#include "ZwRCC.h"
#include "math.h"

// Defines
#define T1PWM_MAX_OUTPUT	0.95f

// Variables
static uint32_t PWMBase = 0;

// Functions
void T1PWM_Init(uint32_t SystemClock, uint32_t Period)
{
	// Расчёт размерности ШИМ
	uint32_t Prescaler = (uint32_t)((float)SystemClock / 1000000 * Period / 65536);
	PWMBase = (uint32_t)((SystemClock / ((Prescaler + 1) * 1000000)) * Period);

	// Стандартная инициализация
	TIM_Clock_En(TIM_1);
	TIM_Interupt(TIM1, 0, true);

	TIM1->PSC = Prescaler;
	TIM1->ARR = PWMBase;

	// Канал 1 - положительный
	// Режим ШИМ - PWM mode 1, c функцией Preload
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
	TIM1->CCR1 = 0;

	// Канал 2 - отрицательный
	// Режим ШИМ - PWM mode 1, c функцией Preload
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
	TIM1->CCR2 = 0;

	// Разрешение выход CH1 и CH2N
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2NE;
	// Разрешение работы таймера на выход
	TIM1->BDTR |= TIM_BDTR_MOE;

	// Сброс выхода
	T1PWM_SetDutyCycle(0);

	// Инициализация обновления регистров
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->SR &= ~TIM_SR_UIF;
}
//------------------------------------------------

void T1PWM_SetDutyCycle(float Value)
{
	// Проверка значения на насыщение
	float MaxOutput = T1PWM_MAX_OUTPUT * PWMBase;
	float absValue = fabsf(Value);
	uint32_t IntValue = (uint32_t)(absValue > MaxOutput ? MaxOutput : absValue);

	// Выбор полярности формирователя
	if(Value > 0)
	{
		TIM1->CCR1 = IntValue;
		TIM1->CCR2 = 0;
	}
	else if(Value < 0)
	{
		TIM1->CCR1 = 0;
		TIM1->CCR2 = IntValue;
	}
	else
		TIM1->CCR1 = TIM1->CCR2 = 0;
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
