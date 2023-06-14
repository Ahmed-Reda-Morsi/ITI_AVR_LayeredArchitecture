/*
 * ADC_Driver_Test.c
 *
 *  Created on: Mar 31, 2023
 *      Author: Ahmed_Reda
 */
#include "../HAL/LCD/LCD_cfg.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/ADC/ADC_cfg.h"
#include "../MCAL/ADC/ADC_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../HAL/LED/LED_int.h"
#include "../HAL/LED/LED_cfg.h"

#include <util/delay.h>


// ======================= ADC with Interrupt ==========================
u16 ADC_u16Data=0;
void ADC_ISR(void)
{
	static u16 Local_ADC_Data_Prevous=0;

	if	(ADC_u16Data!=Local_ADC_Data_Prevous)
	  {HLCD_voidClearDisplay();
	  HLCD_voidSendString("ADC_EXTI: ");
	  HLCD_voidSendNumber(ADC_u16Data);
	  Local_ADC_Data_Prevous=ADC_u16Data;
	  }
}


int main(void)
{
	HLCD_voidInit(HLCD_8BIT_MODE);

	MADC_voidInit();
	MEXTI_voidGlobalInterruptEnable();
    MADC_voidStartConversionAsync(ADC_CHANNEL_SEI_7,ADC_ISR,&ADC_u16Data);

    HLED_voidInit(PORTA,PIN0);

  while(1)
  {

	     MADC_ReadASync();

  }

}

//=================== ADC with Polling  ===================================

//int main(void)
//{
//	HLCD_voidInit(HLCD_8BIT_MODE);
//	u16 ADC_u16Data=0;
//	MADC_voidInit();
//  while(1)
//  {
//
//	  MADC_voidStartConversionSync(ADC_CHANNEL_SEI_7);
//	  ADC_u16Data=MADC_ReadSync();
//	  HLCD_voidClearDisplay();
//	  HLCD_voidSendString("ADC_Poll: ");
//	  HLCD_voidSendNumber(ADC_u16Data);
//	  _delay_ms(1000);
//  }
//
//}

