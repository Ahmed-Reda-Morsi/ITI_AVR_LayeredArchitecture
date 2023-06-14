/*
 * Simple_Calculator.c
 *
 *  Created on: Mar 27, 2023
 *      Author: Ahmed Reda
 */

#include "../HAL/KEYPAD/KEYPAD_int.h"
#include "../HAL/KEYPAD/KEYPAD_cfg.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_cfg.h"


//=======================================================================================================

// can perform arithmetic operation on numbers that have more that one digit.
void APP_voidSimpleCalculator(u8 Local_u8ButtonPressed)
{

	static u16 Local_Number1Pressed = 0xffff;
	static u16 Local_Number2Pressed = 0xffff;
	static u8 Local_OperationPressed = 0xff;
	static s32 Local_Result = 0;

	// for divide operation.
	static u8 Local_ResultMolus = 0;
	static u8 Flag_Valid_Operation = 1;

	if (Local_u8ButtonPressed == 'c')
	{
		HLCD_voidClearDisplay();

		Local_Number1Pressed = 0xffff;
		Local_Number2Pressed = 0xffff;
		Local_OperationPressed = 0xff;
		Local_Result = 0xffff;
		Local_ResultMolus = 0;
		Flag_Valid_Operation = 1;
	}
	else
	{

		if (Local_u8ButtonPressed <= 9 && Local_OperationPressed == 0xff)
		{
			if (Local_Number1Pressed == 0xffff)
			{
				Local_Number1Pressed = Local_u8ButtonPressed;
			}
			else
			{
				Local_Number1Pressed = (Local_Number1Pressed * 10 + Local_u8ButtonPressed);
			}
			HLCD_voidSendNumber(Local_u8ButtonPressed);
		}
		else if ((Local_u8ButtonPressed == '+' || Local_u8ButtonPressed == '/' || Local_u8ButtonPressed == '-' || Local_u8ButtonPressed == '*') && Local_OperationPressed == 0xff)
		{
			Local_OperationPressed = Local_u8ButtonPressed;
			HLCD_voidSendData(Local_u8ButtonPressed);
		}

		else if (Local_u8ButtonPressed <= 9 && Local_OperationPressed != '=')
		{
			if (Local_Number2Pressed == 0xffff)
			{
				Local_Number2Pressed = Local_u8ButtonPressed;
			}
			else
			{
				Local_Number2Pressed = Local_Number2Pressed * 10 + Local_u8ButtonPressed;
			}
			HLCD_voidSendNumber(Local_u8ButtonPressed);
		}
		else if (Local_u8ButtonPressed == '=')
		{
			HLCD_voidSendData('=');

			if (Local_OperationPressed == '*')
			{
				Local_Result = Local_Number1Pressed * Local_Number2Pressed;
			}
			else if (Local_OperationPressed == '/')
			{
				if (Local_Number2Pressed != 0)
				{
					Local_Result = Local_Number1Pressed / Local_Number2Pressed;
					Local_ResultMolus = Local_Number1Pressed % Local_Number2Pressed;
				}
				else
				{
					Flag_Valid_Operation = 0;
					HLCD_voidSendString(" Divide By Zero.!!");
				}
			}
			else if (Local_OperationPressed == '+')
			{
				Local_Result = Local_Number1Pressed + Local_Number2Pressed;
			}
			else if (Local_OperationPressed == '-')
			{
				Local_Result = Local_Number1Pressed - Local_Number2Pressed;
				if (Local_Result < 0)
				{
					HLCD_voidSendData('-');
					Local_Result = abs(Local_Result);
				}
			}

			if (Flag_Valid_Operation == 1)
				HLCD_voidSendNumber(Local_Result);
			if (Local_ResultMolus != 0)
			{
				HLCD_voidSendData(' ');
				HLCD_voidSendNumber(Local_ResultMolus);
				HLCD_voidSendData('/');
				HLCD_voidSendNumber(Local_Number2Pressed);
			}
		}
	}
}

int main(void)
{
	HKEYPAD_voidInit();
	HLCD_voidInit(HLCD_8BIT_MODE);
	u8 Local_u8ButtonPressed;

	while (1)
	{
		Local_u8ButtonPressed = HKEYPAD_u8GetPressedKey();
		if (Local_u8ButtonPressed != BUTTON_NOT_PRESSED)
		{
			APP_voidSimpleCalculator(Local_u8ButtonPressed);
		}
	}

	return 0;
}
