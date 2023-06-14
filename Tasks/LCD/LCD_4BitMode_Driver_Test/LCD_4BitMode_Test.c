/*
 * LCD_4BitMode_Test.c
 *
 *  Created on: Mar 26, 2023
 *      Author: Ahmed Reda
 */

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_cfg.h"

#include "../LIB/STD_TYPES.h"
#include <util/delay.h>


	int main(void)
{


    HLCD_voidInit(HLCD_4BIT_MODE);

    HLCD_voidSendString("Ahmed Reda");

    while(1)
    {

    }
  return 0;
}
