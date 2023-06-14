/*
 * USART_TEST.c
 *
 *  Created on: Apr 18, 2023
 *      Author: aland
 */

#include "../MCAL/TIMER0/TIMER_int.h"
#include "../MCAL/TIMER0/TIMER_cfg.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"

void requiredtime_ISR(void)
{
	MDIO_voidTogglePinValue(PORTA,PIN0);

}
void overflow_ISR(void)
{

	MDIO_voidTogglePinValue(PORTA,PIN3);
}

int main(void)
{
	MDIO_voidSetPinDirection(PORTA,PIN0,PIN_OUT);
	MDIO_voidSetPinValue(PORTA,PIN0,PIN_LOW);
	MDIO_voidSetPinDirection(PORTA,PIN3,PIN_OUT);
	MDIO_voidSetPinValue(PORTA,PIN3,PIN_LOW);

	MGIE_voidEnable();

	MTIMER0_voidInit(TIMER0_NORMAL_MODE,TIMER0_CS_PRESCALLER_8);

	// overflow interrupt approach
	MTIMER0_voidSetCallBack_OverFlow(overflow_ISR);
	MTIMER0_voidSetCallBack_REQUIREDTIME(requiredtime_ISR);
	//MTIMER0_voidDelayInterrupt_MS(5000);
	while(1)
	{
		//flag wait approach
		MDIO_voidTogglePinValue(PORTA,PIN0);
		MTIMER0_voidDelay_MS(5000);
	}
	return 0;

}
