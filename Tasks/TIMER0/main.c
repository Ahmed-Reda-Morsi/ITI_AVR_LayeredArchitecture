/*
 * main.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Ahmed_Reda
 */

#include  "../HAL/LED/LED_int.h"
#include  "../HAL/LED/LED_cfg.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"

#include <util/delay.h>

#include "../MCAL/TIMER0/TIMER_cfg.h"
#include "../MCAL/TIMER0/TIMER_int.h"


// Phase Correct RWM MODE
//int main(void)
//{
//	MTIMER0_voidInit(TIMER0_PWM_PHASECORRECT_MODE ,TIMER0_CS_PRESCALLER_256);
//	MTIMER0_voidPWMDutyCycle(70); // %70
//	MTIMER0_voidCompareOutputMode(TIMER0_PWM_PHASECORRECT_MODE,TIMER0_COM_PHASECORRECTPWM_OC0_PIN_CLEAR_COUNTUP);
//
//  while(1)
//  {
//  }
//}

//====================================================
// FAST RWM MODE
int main(void)
{
	MTIMER0_voidInit(TIMER0_FAST_PWM_MODE ,TIMER0_CS_PRESCALLER_256);
	MTIMER0_voidPWMDutyCycle(70); // %70

	MTIMER0_voidCompareOutputMode(TIMER0_FAST_PWM_MODE,TIMER0_COM_FASTPWM_OC0_PIN_CLEAR);

  while(1)
  {
  }
}
//-----------------------------------------------------------------------------------------------------------------
// Interrupt Compare match
//void Timer_ISR_CompareMatch(void)
//{
//	HLED_voidTurnOn(PORTC,3);
//}
//int main(void)
//{
//	HLED_voidInit(PORTC,3);
//	MTIMER0_voidInit(TIMER0_CTC_MODE,TIMER0_CS_PRESCALLER_256);
//	MTIMER0_voidSetCompareMatchValue(200);
//	MTIMER0_voidCompareOutputMode(TIMER0_CTC_MODE, TIMER0_COM_NOPWM_OC0_PIN_TOGGLE);
//
//	MINT_voidGlobalInterruptEnable();
//	MTIMER0_voidSetCallBack_CompareMatchValue(Timer_ISR_CompareMatch);
//  while(1)
//  {
//  }
//}
//-------------------------------------------------------------------------------------------------

// Interrupt OverFlow
//void Timer_ISR_OverFlow(void)
//{
//	HLED_voidFlip(PORTC,2,1000);
//}
//int main(void)
//{
//	MINT_voidGlobalInterruptEnable();
//	MTIMER0_voidInit(TIMER0_NORMAL_MODE,TIMER0_CS_PRESCALLER_256);
//	HLED_voidInit(PORTC,2);
//	MTIMER0_voidSetCallBack_OverFlow(Timer_ISR_OverFlow);
//  while(1)
//  {
//
//  }
//
//}


//--------------------------------------------------------------------
//normal   compare match value
//int main(void)
//{
//	MTIMER0_voidInit(TIMER0_NORMAL_MODE,TIMER0_CS_PRESCALLER_256);
//	HLED_voidInit(PORTC,1);
//	MTIMER0_voidSetCompareMatchValue(200);
//  while(1)
//  {
//	  if (MTIMER0_u8CheckCompareMatchMode()==1)
//	  {
//		  HLED_voidFlip(PORTC,1,100);
//	}
//
//  }
//
//}

//---------------------------------------------------------------------------------
// normal overflow
//int main(void)
//{
//	MTIMER0_voidInit(TIMER0_NORMAL_MODE,TIMER0_CS_PRESCALLER_256);
//	HLED_voidInit(PORTC,0);
//  while(1)
//  {
//	  if (MTIMER0_u8CheckOverFlow()==1)
//	  {
//		  HLED_voidFlip(PORTC,0,1000);
//	}
//
//  }
//
//}
