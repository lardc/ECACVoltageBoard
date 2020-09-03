#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"
#include "BCCIxParams.h"
#include "LowLevel.h"
#include "Delay.h"

// Functions
//
Boolean INITCFG_ConfigSystemClock()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------

void INITCFG_ConfigInterrupt()
{
	EXTI_Config(EXTI_PB, EXTI_8, BOTH_TRIG, 0);	// GPIO_KEY_STOP
	EXTI_EnableInterrupt(EXTI9_5_IRQn, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigIO()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);
	
	// Выходы
	GPIO_InitPushPullOutput(GPIO_LED_EXT_RED);
	GPIO_InitPushPullOutput(GPIO_LED_EXT_GREEN);
	GPIO_InitPushPullOutput(GPIO_SET);
	GPIO_InitPushPullOutput(GPIO_CTRL_SYNC_1);
	GPIO_InitPushPullOutput(GPIO_CTRL_SYNC_2);
	GPIO_InitPushPullOutput(GPIO_LOCK_1);
	GPIO_InitPushPullOutput(GPIO_LOCK_2);
	GPIO_InitPushPullOutput(GPIO_RESET);
	GPIO_InitPushPullOutput(GPIO_OE);
	
	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_CAN_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN_TX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_UART_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART_TX, AltFn_7);
	GPIO_InitAltFunction(GPIO_CLK, AltFn_5);
	GPIO_InitAltFunction(GPIO_DATA, AltFn_5);

	// Входы
	GPIO_InitInput(GPIO_SYNC_1, NoPull);
	GPIO_InitInput(GPIO_SYNC_2, NoPull);
	GPIO_InitInput(GPIO_SFTY_1, Pull_Up);
	GPIO_InitInput(GPIO_SFTY_2, Pull_Up);
	GPIO_InitInput(GPIO_KEY_START, Pull_Up);
	GPIO_InitInput(GPIO_KEY_STOP, Pull_Up);

	// Начальные состояние выходов
	GPIO_SetState(GPIO_RESET, false);
	GPIO_SetState(GPIO_SET, true);
	GPIO_SetState(GPIO_OE, true);

/*	GPIO_SetState(GPIO_LED_EXT_RED, true);
	GPIO_SetState(GPIO_LED_EXT_GREEN, true);
	GPIO_SetState(GPIO_LOCK_1, true);
	GPIO_SetState(GPIO_LOCK_2, true);*/
}
//------------------------------------------------
void INITCFG_ConfigSPI()
{
	SPI_Init8b(SPI1, SPI_CR1_BR, FALSE);
}

//------------------------------------------------
void INITCFG_ConfigCAN()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, FALSE);
	NCAN_FIFOInterrupt(TRUE);
	NCAN_FilterInit(0, CAN_SLAVE_FILTER_ID, CAN_SLAVE_NID_MASK);
}
//------------------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigTimer7()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 0, true);
	TIM_Start(TIM7);
}
//------------------------------------------------

void INITCFG_ConfigWatchDog()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------------------
