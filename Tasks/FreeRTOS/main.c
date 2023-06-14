///*
// *
// *  Created on: Apr 8, 2023
// *      Author: Ahmed Reda
// */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../Source/FreeRTOS.h"
#include "../Source/task.h"
#include "../MCAL/DIO/DIO_int.h"



void LED_1(void*pv);
void LED_2(void*pv);
void LED_3(void*pv);


void main(void)
{
	MDIO_voidSetPinDirection(PORTA,PA0,PIN_OUT);
	MDIO_voidSetPinDirection(PORTA,PA1,PIN_OUT);
	MDIO_voidSetPinDirection(PORTA,PA2,PIN_OUT);

	xTaskCreate(&LED_1,NULL,100,NULL,0,NULL);
	xTaskCreate(&LED_2,NULL,100,NULL,1,NULL);
	xTaskCreate(&LED_3,NULL,100,NULL,2,NULL);

	vTaskStartScheduler();
	while(1)
	{

	}

}



void LED_3(void*pv)
{
	while(1)
	{
		MDIO_voidTogglePinValue(PORTA,PA2);
		vTaskDelay(5000);
	}
}
void LED_2(void*pv)
{
	while(1)
	{
		MDIO_voidTogglePinValue(PORTA,PA1);
		vTaskDelay(3000);
	}
}



void LED_1(void*pv)
{
	while(1)
	{
		MDIO_voidTogglePinValue(PORTA,PA0);
		vTaskDelay(1000);
	}
}
