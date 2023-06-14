///*
// * main.c
// *
// *  Created on: Apr 8, 2023
// *      Author: Ahmed Reda
// */
//
//#include "../HAL/LCD/LCD_cfg.h"
//#include "../HAL/LCD/LCD_int.h"
//#include "../MCAL/ADC/ADC_cfg.h"
//#include "../MCAL/ADC/ADC_int.h"
//#include "../MCAL/EXTI/EXTI_int.h"
#include "../HAL/LED/LED_int.h"
#include "../HAL/LED/LED_cfg.h"
#include "../HAL/EEPROM/EEPROM_int.h"
#include "../HAL/LCD/LCD_cfg.h"
#include "../HAL/LCD/LCD_int.h"
#include <util/delay.h>
void main(void)
{

    HLCD_voidInit(HLCD_8BIT_MODE);

	u8 EEPROM_DATA=0; //to save readed data from EEPROM Types

    	//write "A"in EEPROM_24C02
		HEEPROM_voidInit(EEPROM_24C02,1);
		HEEPROM_voidWriteDataByte(0x17,'A');
		_delay_ms(10);
		HEEPROM_voidReadDataByte(0x17,&EEPROM_DATA);
		HLCD_voidSendData(EEPROM_DATA);
		_delay_ms(10);

		//write "R"in EEPROM_24C04
		HEEPROM_voidInit(EEPROM_24C04,1);
		HEEPROM_voidWriteDataByte(0x16,'R');
		_delay_ms(10);
		HEEPROM_voidReadDataByte(0x16,&EEPROM_DATA);
		HLCD_voidSendData('_');
		HLCD_voidSendData(EEPROM_DATA);
		_delay_ms(10);

		//write "M"in EEPROM_24C08
		HEEPROM_voidInit(EEPROM_24C08,1);
		HEEPROM_voidWriteDataByte(0x20,'M');
		_delay_ms(10);
		HEEPROM_voidReadDataByte(0x20,&EEPROM_DATA);
		HLCD_voidSendData('_');
		HLCD_voidSendData(EEPROM_DATA);
		_delay_ms(10);

		while(1)
			{
			}
}
