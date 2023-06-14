
#include "../HAL/KEYPAD/KEYPAD_int.h"
#include "../HAL/KEYPAD/KEYPAD_cfg.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_cfg.h"

int main(void)
{
	HKEYPAD_voidInit();
	HLCD_voidInit(HLCD_8BIT_MODE);

	u8 Local_u8ButtonPressed;

	while (1)
	{
		Local_u8ButtonPressed=HKEYPAD_u8GetPressedKey();
		if(Local_u8ButtonPressed!=BUTTON_NOT_PRESSED)
		{
			if(Local_u8ButtonPressed>20)
					HLCD_voidSendData(Local_u8ButtonPressed);
			else
				HLCD_voidSendNumber(Local_u8ButtonPressed);


		}
	}



	return 0;
}
