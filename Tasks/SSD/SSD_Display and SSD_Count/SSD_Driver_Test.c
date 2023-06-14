/*
 * main.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Ahmed_Reda
 */
#include"../HAL/SSD/SSD_int.h"
#include "../HAL/SSD/SSD_cfg.h"
#include "../MCAL/DIO/DIO_int.h"
#include <util/delay.h>

int main(void)
{
	HSSD_voidInit();

	HSSD_voidDisplay(40,SSD_COMMON_ADONE,SSD_COMMON_CATHODE);
	_delay_ms(2000);
	HSSD_voidCount(45,70,250,SSD_COMMON_ADONE,SSD_COMMON_CATHODE);
  while(1)
  {

	  }

}
