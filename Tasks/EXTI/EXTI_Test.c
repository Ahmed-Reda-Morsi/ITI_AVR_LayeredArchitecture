/*
 * main.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Ahmed_Reda
 */
#include "../HAL/LED/LED_int.h"
#include "../HAL/LED/LED_cfg.h"
#include "../MCAL/EXTI/EXTI_cfg.h"
#include "../MCAL/EXTI/EXTI_int.h"

#include <util/delay.h>
void ISR_INT0(void);
void ISR_INT1(void);
void ISR_INT2(void);
int main(void)
{
	// LEDs for test external interrupt INT0 INT1 INT2
	HLED_voidInit(PORTA,PIN0);
	HLED_voidInit(PORTA,PIN1);
	HLED_voidInit(PORTA,PIN2);

	// LED for normal execution
	HLED_voidInit(PORTB,PIN6);

	MEXTI_voidEnableInterrupt(INT0_PIN,LOW_LEVEL);
	MEXTI_voidEnableInterrupt(INT1_PIN,FALLING_EDGE);
	MEXTI_voidEnableInterrupt(INT2_PIN,RISING_EDGE);

	MEXTI_0_SET_CALL_BACK(ISR_INT0);
	MEXTI_1_SET_CALL_BACK(ISR_INT1);
	MEXTI_2_SET_CALL_BACK(ISR_INT2);

  while(1)
  {
	  // normal execution
	 HLED_voidFlip(PORTB,PIN6,100);
  }

}
void ISR_INT0(void)
{
	HLED_voidFlip(PORTA,PIN0,1000);
	HLED_voidFlip(PORTA,PIN1,1000);
	HLED_voidFlip(PORTA,PIN2,1000);
}
void ISR_INT1(void)
{
	HLED_voidTurnOn(PORTA,PIN0);
	_delay_ms(1000);
	HLED_voidTurnOn(PORTA,PIN1);
	_delay_ms(1000);
	HLED_voidTurnOn(PORTA,PIN2);
	_delay_ms(1000);
}
void ISR_INT2(void)
{
	HLED_voidTurnOFF(PORTA,PIN2);
	_delay_ms(1000);
	HLED_voidTurnOFF(PORTA,PIN1);
	_delay_ms(1000);
	HLED_voidTurnOFF(PORTA,PIN0);
}


