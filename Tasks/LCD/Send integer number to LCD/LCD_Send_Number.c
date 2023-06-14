/*
 * LCD_Send_Number.c
 *
 *  Created on: Mar 25, 2023
 *      Author: aland
 */


#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_cfg.h"

#include "../LIB/STD_TYPES.h"
#include <util/delay.h>


	int main(void)
{


    HLCD_voidInit();
    HLCD_voidSendNumber(452);
    while(1)
    {

    }
  return 0;
}

