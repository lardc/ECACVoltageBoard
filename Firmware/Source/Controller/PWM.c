// Header
#include "PWM.h"

// Includes
#include "LowLevel.h"
#include "Measure.h"
#include "ZwDMA.h"
#include "Global.h"
#include "ZwADC.h"
#include "Controller.h"
#include "Timer1PWM.h"
#include "math.h"
#include "DeviceObjectDictionary.h"
#include "DataTable.h"
#include "Board.h"

// Defines
#define PWM_MAX_STEP_PWM 400

// Typedef
typedef struct __Error
{
	float Summ;
	float Now;
	float Last;
} Error;

typedef struct __Measure
{
	float Target;
	float Now;
	uint32_t Set;
} Measure;

typedef struct __Koefficient
{
	float Q;
	float K;
} Koefficient;

typedef struct __KoefficientStr
{
	Koefficient P;
	Koefficient I;

} KoefficientStr;

typedef struct __SinControl
{
	Measure Voltage;
	Measure Current;
	Error Error;
	KoefficientStr	PI;
	float Duty;
	uint16_t Point;
	int16_t PWMRAW[PWM_MAX_STEP_PWM];
} SinControl;

volatile SinControl Regulator = {0};

// Variables
static const float Steper = M_PI * (2 * (1 / (float)PWM_MAX_STEP_PWM));

// Functions
static void PWM_ResetDataOut();
static void PWM_SaveEndPoint();

static void PWM_SaveToEndPoint(volatile uint32_t *AdressEndPoint, volatile uint16_t Data, volatile uint32_t *Counter);

void PWM_SinRegulation();
static void PWM_StepUpdate();
static void PWM_UpdateMeasValue();
static void PWM_ChekEndOfSignal();
static void PWM_UpdateKoeff();
static void PWM_CalculateVoltageInPoint();
static void PWM_CalculateDuty();
static void PWM_OneMeasure();

void PWM_SignalStart(uint16_t Voltage, uint32_t Current)
{
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();

	Regulator.Voltage.Set = Voltage;
	Regulator.Current.Set = Current;
	PWM_UpdateKoeff();
	PWM_ResetDataOut();
	MEAS_SetMeasureRange(Voltage, Current);
	PWM_OneMeasure();
	PWM_SinRegulation();
	ADC_SamplingStart(ADC1);
	T1PWM_Start();
}
//------------------------------------------------

void PWM_SignalStop()
{
	T1PWM_Stop();
}
//------------------------------------------------

void PWM_SinRegulation()
{
	GPIO_SetState(GPIO_LED_EXT, true);
	PWM_UpdateMeasValue();

	PWM_SaveEndPoint();

	PWM_CalculateVoltageInPoint();

	PWM_ChekEndOfSignal();
	PWM_CalculateDuty();
	T1PWM_SetDutyCycle(Regulator.Duty);
	if(CONTROL_BuffCounterVoltage < VALUES_x_SIZE)
	{
		CONTROL_BuffCounterVoltage++;
	}
	else
	{
		CONTROL_BuffCounterVoltage = 0;
	}

	PWM_StepUpdate();
	GPIO_SetState(GPIO_LED_EXT, false);
}

//------------------------------------------------
void PWM_StepUpdate()
{
	if(Regulator.Point >= (PWM_MAX_STEP_PWM - 1))
	{
		Regulator.Point = 0;
	}
	else
	{
		Regulator.Point++;
	}
}
//------------------------------------------------

void PWM_UpdateMeasValue()
{
	Regulator.Voltage.Now = MEAS_Voltage();
	Regulator.Current.Now = MEAS_Current();
}
//------------------------------------------------

void PWM_ChekEndOfSignal()
{
	if(Regulator.Point == 0)
	{
		Regulator.Error.Now = 0;
	}
	else
	{
		Regulator.Error.Now = Regulator.Voltage.Target - Regulator.Voltage.Now;
	}
}
//------------------------------------------------

void PWM_UpdateKoeff()
{
	Regulator.PI.P.K = (float)DataTable[REG_Kp] / 1000;
	Regulator.PI.I.K = (float)DataTable[REG_Ki] / 1000;
}
//------------------------------------------------

void PWM_ResetDataOut()
{
	T1PWM_SetDutyCycle(0);
}
//------------------------------------------------

void PWM_SaveEndPoint()
{
//	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC1DMABuff, (uint32_t*)&CONTROL_BuffRAWCurrent);
//	PWM_CopyRAWFromDMAToEndPoint((uint32_t*)&ADC2DMABuff, (uint32_t*)&CONTROL_BuffRAWVoltage);
	PWM_SaveToEndPoint((uint32_t*)&CONTROL_BuffVoltage, Regulator.Voltage.Now, (uint32_t*)&CONTROL_BuffCounterVoltage);
	PWM_SaveToEndPoint((uint32_t*)&CONTROL_BuffCurrent, Regulator.Current.Now, (uint32_t*)&CONTROL_BuffCounterCurrent);
}
//------------------------------------------------

void PWM_CalculateVoltageInPoint()
{
	Regulator.Voltage.Target = Regulator.Voltage.Set * sinf(Steper * Regulator.Point);
}
//------------------------------------------------

void PWM_CalculateDuty()
{
	Regulator.PI.P.Q = Regulator.Error.Now * Regulator.PI.P.K;
	Regulator.PI.I.Q += Regulator.Error.Now * Regulator.PI.I.K;

	Regulator.Error.Last = Regulator.Error.Now;
	Regulator.Error.Summ += Regulator.Error.Last;

	Regulator.Duty = Regulator.PI.P.Q + Regulator.PI.I.Q;
}
//------------------------------------------------

void PWM_OneMeasure()
{
	DMA_Interrupt(DMA1_Channel1, DMA_CCR_TCIE, 0, false);
	DMA_Interrupt(DMA2_Channel1, DMA_CCR_TCIE, 0, false);

	ADC_SamplingStart(ADC1);

	TIM1->EGR |= TIM_EGR_UG;
	TIM1->SR &= ~TIM_SR_UIF;

	while(((DMA2->ISR & DMA_ISR_TCIF1) && (DMA1->ISR & DMA_ISR_TCIF1)) == false);

	DMA2->IFCR |= DMA_IFCR_CTCIF1;
	DMA1->IFCR |= DMA_IFCR_CTCIF1;

	DMA_Interrupt(DMA1_Channel1, DMA_CCR_TCIE, 0, true);
	DMA_Interrupt(DMA2_Channel1, DMA_CCR_TCIE, 0, true);
}
//------------------------------------------------

void PWM_SaveToEndPoint(volatile uint32_t *AdressEndPoint, volatile uint16_t Data, volatile uint32_t *Counter)
{
/*	volatile uint32_t *pAdr;

	if(*Counter < VALUES_x_SIZE)
	{
		(*Counter)++;
	}
	else
	{
		*Counter = 0;
	}
	pAdr = AdressEndPoint + (*Counter) * sizeof(*Counter);
	*pAdr = Data;*/
}
