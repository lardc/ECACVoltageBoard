// Include
#include "Interrupts.h"
//
#include "Controller.h"
#include "LowLevel.h"
#include "Board.h"
#include "SysConfig.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "ZwDMA.h"
#include "Measure.h"
#include "PWM.h"

// Functions
//
void USART1_IRQHandler()
{
	if(ZwSCI_RecieveCheck(USART1))
	{
		ZwSCI_RegisterToFIFO(USART1);
		ZwSCI_RecieveFlagClear(USART1);
	}
}
//-----------------------------------------

void USB_LP_CAN_RX0_IRQHandler()
{
	if(NCAN_RecieveCheck())
	{
		NCAN_RecieveData();
		NCAN_RecieveFlagReset();
	}
}
//-----------------------------------------

void TIM7_IRQHandler()
{
	static uint16_t LED_BlinkTimeCounter = 0;

	if(TIM_StatusCheck(TIM7))
	{
		CONTROL_TimeCounter++;
		if(++LED_BlinkTimeCounter > TIME_LED_BLINK)
		{
			LL_ToggleBoardLED();
			LED_BlinkTimeCounter = 0;
		}

		TIM_StatusClear(TIM7);
	}
}
//-----------------------------------------

void INITCFG_ConfigInterrupt()
{

}
//-----------------------------------------

void DMA1_Channel1_IRQHandler()
{
	if((DMA1->ISR & DMA_ISR_TCIF1))
	{
		DMA1->IFCR |= DMA_IFCR_CTCIF1;
		MEASURE_VoltageDone = true;
		if(MEASURE_VoltageDone && MEASURE_CurrentDone)
		{
			MEASURE_VoltageDone = MEASURE_CurrentDone = 0;
			PWM_SinRegulation();
			ADC_SamplingStart(ADC1);
		}
	}
	DMA1->IFCR |= DMA_IFCR_CGIF1;
}
//-----------------------------------------

void DMA2_Channel1_IRQHandler()
{
	if((DMA2->ISR & DMA_ISR_TCIF1))
	{
		DMA2->IFCR |= DMA_IFCR_CTCIF1;
		MEASURE_CurrentDone = true;
		if(MEASURE_VoltageDone && MEASURE_CurrentDone)
		{
			MEASURE_VoltageDone = MEASURE_CurrentDone = 0;
			PWM_SinRegulation();
			ADC_SamplingStart(ADC1);
		}
	}
	DMA2->IFCR |= DMA_IFCR_CGIF1;
}
//-----------------------------------------
