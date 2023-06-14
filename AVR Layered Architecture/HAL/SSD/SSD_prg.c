#include "SSD_cfg.h"
#include "SSD_prv.h"
#include "SSD_int.h"

#include <util/delay.h>
#include "../../MCAL/DIO/DIO_int.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* numebr  digits repesenpation
						 	 	 	 	 	 	 0 	    1    	 2			3		 4			5	 	 6  		7	 	8	    9    */
const char numbers[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void HSSD_voidInit(void)
{
	MDIO_voidSetPortDirection(SSD_1_PORT, PORT_OUT);
	MDIO_voidSetPortDirection(SSD_2_PORT, PORT_OUT);
}
void HSSD_voidDisplay(u8 Copy_u8Data, u8 Copy_u8SSD_1_Type, u8 Copy_u8SSD_2_Type)
{
	u8 Local_SSD1_NUM = Copy_u8Data % 10;
	u8 Local_SSD2_NUM = Copy_u8Data / 10;
	if (Copy_u8SSD_1_Type == SSD_COMMON_CATHODE)
	{
		MDIO_voidSetPortValue(SSD_1_PORT, numbers[Local_SSD1_NUM]);
	}
	else
	{
		MDIO_voidSetPortValue(SSD_1_PORT, (~numbers[Local_SSD1_NUM]));
	}

	if (Copy_u8SSD_2_Type == SSD_COMMON_CATHODE)
	{
		MDIO_voidSetPortValue(SSD_2_PORT, numbers[Local_SSD2_NUM]);
	}
	else
	{
		MDIO_voidSetPortValue(SSD_2_PORT, (~numbers[Local_SSD2_NUM]));
	}
}
void HSSD_voidCount(u8 Copy_u8Start, u8 Copy_u8End, u8 Copy_u8CounterDelay,u8 Copy_u8SSD_1_Type, u8 Copy_u8SSD_2_Type)
{

	for (u8 i = Copy_u8Start; i <= Copy_u8End; i++)
	{
		_delay_ms(Copy_u8CounterDelay);
		u8 Local_SSD1_NUM = i % 10;
		u8 Local_SSD2_NUM = i / 10;

		if (Copy_u8SSD_1_Type == SSD_COMMON_CATHODE)
		{
			MDIO_voidSetPortValue(SSD_1_PORT, numbers[Local_SSD1_NUM]);
		}
		else
		{
			MDIO_voidSetPortValue(SSD_1_PORT, (~numbers[Local_SSD1_NUM]));
		}
		if (Copy_u8SSD_2_Type == SSD_COMMON_CATHODE)
		{
			MDIO_voidSetPortValue(SSD_2_PORT, numbers[Local_SSD2_NUM]);
		}
		else
		{
			MDIO_voidSetPortValue(SSD_2_PORT, (~numbers[Local_SSD2_NUM]));
		}
	}
}
