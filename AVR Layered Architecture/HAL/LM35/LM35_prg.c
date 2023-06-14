
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/ADC/ADC_cfg.h"
#include "../../MCAL/EXTI/EXTI_int.h"
#include "LM35_cfg.h"
#include "LM35_int.h"
#include "LM35_prv.h"

u16 ADC_value;

void HLM35_voidInit(u8 Copy_u8ADC_Channel,void(*LM_PTR)(void))
{
	MEXTI_voidGlobalInterruptEnable();
	MADC_voidInit();
	MADC_voidStartConversionAsync(Copy_u8ADC_Channel,LM_PTR,&ADC_value);
}
void HLM35_voidGetTemperatureAsync(f32* Copy_ps8Temperature_Value)
{
	MADC_ReadASync();
	*Copy_ps8Temperature_Value=((ADC_STEP*ADC_value)/LM35_TEMPERATURE_SLOPE);
}
