/*
 * SpecialCharacter_SineWave.c
 *
 *  Created on: Mar 25, 2023
 *      Author: aland
 */


#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_cfg.h"

#include "../LIB/STD_TYPES.h"
#include <util/delay.h>

// Ahmed Reda in arabic characrters.
	u8 CharacterS[7][8]={
								{ 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00 },
								{ 0x00, 0x02, 0x00, 0x02, 0x05, 0xff, 0x08, 0x00 },
								{ 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08 },
								{ 0x00, 0x00, 0x04, 0x02, 0x01, 0x1f, 0x00, 0x00 },
								{ 0x00, 0x00, 0x00,0x00, 0x0E, 0x1B, 0x0E, 0x00 },
								{ 0x00, 0x00, 0x04, 0x0A, 0x01, 0x1f, 0x00, 0x00 },
								{ 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00 },
								};


int main(void)
{


    HLCD_voidInit();

	u8 line_number=0x01;
    while(1)
    {		for(u8 j=0; j<10;j+=2)
    		{
    				line_number^= 0x01;
    				for(u8 i=0;i<7;i++)
    				{
    				HLCD_voidSendSpectialChar(CharacterS[i],6-i,line_number,j+i);
    				}
    				_delay_ms(1000);
    				HLCD_voidSendCommand(0x01);
    		}
			for(s8 j=9; j>0;j-=2)
    		{
    				line_number^= 0x01;
    				for(u8 i=0;i<7;i++)
    				{
    				HLCD_voidSendSpectialChar(CharacterS[i],6-i,line_number,j+i);
    				}
    				_delay_ms(1000);
    				HLCD_voidSendCommand(0x01);
    		}

    }
  return 0;
}
