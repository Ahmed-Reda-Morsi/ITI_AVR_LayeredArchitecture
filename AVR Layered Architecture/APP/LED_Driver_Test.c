/*
 * main.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Ahmed_Reda
 */
#include"../HAL/LED/LED_int.h"

#include <util/delay.h>

int main(void)
{
	HLED_voidInit();
  while(1)
  {
	  //HLED_voidTurnOn();
	  //_delay_ms(1000);
	  //HLED_voidTurnOFF();
	HLED_voidFlip(200);
 }

}
