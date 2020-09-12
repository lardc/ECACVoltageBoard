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

// Defines
#define PWM_TIM1_OUT_ENABLE		(TIM1->BDTR |= TIM_BDTR_MOE)
#define PWM_TIM1_OUT_DISABLE	(TIM1->BDTR &= ~TIM_BDTR_MOE)
#define PWM_TIM1_GenerateEvent	(TIM1->EGR |= TIM_EGR_UG);

// Variables
volatile uint16_t TIM1_DMA_Buffer[SIN_BUFF_SIZE + 1] = {0};

// Functions
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
	PWM_TIM1_GenerateEvent;
	while((TIM1->EGR & TIM_EGR_UG) == true)
	{
	}
	PWM_TIM1_GenerateEvent;
	PWM_TIM1_OUT_ENABLE;
}
//------------------------------------------------

