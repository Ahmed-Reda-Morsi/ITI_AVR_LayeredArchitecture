

#include "../HAL/LCD/LCD_cfg.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEYPAD/KEYPAD_int.h"
#include "../HAL/KEYPAD/KEYPAD_cfg.h"
#include "../HAL/LM35/LM35_int.h"
#include "../MCAL/TIMER0/TIMER0_cfg.h"
#include "../MCAL/TIMER0/TIMER0_int.h"
#include "../MCAL/TIMER2/TIMER2_cfg.h"
#include "../MCAL/TIMER2/TIMER2_int.h"

// for save the temperature value updated with interrupt of ADC
f32 Temperarture_value;

 // get user entered password(only 3 digits)
void Get_Password(u8* Copy_pu8Password)
{
		HLCD_voidClearDisplay();
		HLCD_voidSendString("Password:");
		u8 Pressed_key=BUTTON_NOT_PRESSED;
		u8 i=0;
		while(i<3)
		{
			Pressed_key=HKEYPAD_u8GetPressedKey();
			if(Pressed_key!=BUTTON_NOT_PRESSED&&Pressed_key>=0&&Pressed_key<=9)
				{
				Copy_pu8Password[i]=Pressed_key+0x30; // convert number to ascii
				HLCD_voidSendData((Pressed_key+0x30));
				i++;
				}
		}


}

// check user entered password
u8 check_Password(u8* Copy_pu8CorrectPassword,u8* Copy_pu8EnteredPassword)
{
	u8 passwordValid=1;
	for(u8 i=0;i<3;i++)
	{
		if(Copy_pu8CorrectPassword[i]!=Copy_pu8EnteredPassword[i])
		{
			passwordValid=0;
			break;
		}
	}


	HLCD_voidClearDisplay();
	if(passwordValid==1)
	{
		HLCD_voidSendString("Correct -_-");
	}
	else
	{
		HLCD_voidSendString("Wrong !!");
	}
	return passwordValid;
}

// ISR for LM35
 void LM35_ISR(void){

	static  f32 Temp_prev=0xff;
	 if(Temp_prev!=Temperarture_value)
	 {
		 // calcuate duty cycle for DC motor
		 if(Temperarture_value>20 &&Temperarture_value<=100)
		  {
			 MTIMER0_voidPWMDutyCycle(Temperarture_value);
			 MTIMER0_voidCompareOutputMode(TIMER0_FAST_PWM_MODE,TIMER0_COM_FASTPWM_OC0_PIN_CLEAR);
		  }
		else
		  {	// turn off DC motor.
			 MTIMER0_voidCompareOutputMode(TIMER0_FAST_PWM_MODE,TIMER0_COM_FASTPWM_OC0_PIN_DISCONNETED);
		 }
	 }
	 Temp_prev=Temperarture_value;

 }

void main(void)
{
	// LCD Configure for 4 bit mode.
	HLCD_voidInit(HLCD_4BIT_MODE);

	// LM35 configure for 0 to 150 c
	HLM35_voidInit(0,LM35_ISR);

	// Keypad configure
	HKEYPAD_voidInit();

	// Timer 0 configure as fast PWM with prescaller 256
	MTIMER0_voidInit(TIMER0_FAST_PWM_MODE,TIMER0_CS_PRESCALLER_256);


	// Timer 2 configure as fast PWM with prescaller 256
	MTIMER2_voidInit(TIMER2_FAST_PWM_MODE,TIMER2_CS_PRESCALLER_256);

	//get password for keypad
	u8 Local_EnteredPassword[4]={'\0'};

	// check password validity
	u8 CorrectPassword[4]="123";

	//check user entered password is correct password or not
	u8 PasswordValid=0;

	// for calculate duty cycle for LED
	u8 LED_intensity=0;
	while(1)
	{
		// check entered password for certain number.
		LED_intensity=0;
		for(u8 i=0 ;i<4;i++)
		{
			Get_Password(Local_EnteredPassword);
			PasswordValid=check_Password(CorrectPassword,Local_EnteredPassword);
			if(PasswordValid==1)
			{
				// disable LED at correct password.
				MTIMER2_voidCompareOutputMode(TIMER2_FAST_PWM_MODE,TIMER2_COM_FASTPWM_OC2_PIN_DISCONNETED);
				break;
			}
			else
			{
				// LED with PWM
				LED_intensity+=25;
				 MTIMER2_voidPWMDutyCycle(LED_intensity);
				 MTIMER2_voidCompareOutputMode(TIMER2_FAST_PWM_MODE,TIMER2_COM_FASTPWM_OC2_PIN_CLEAR);

			}
			if(i==3)
			{
				HLCD_voidClearDisplay();
				HLCD_voidSendString("You have tried 3 times! try again");
			}
		}

		//control DC with LM35 value.
		while(PasswordValid==1)
		{
			// get temperature value with interrupt
			HLM35_voidGetTemperatureAsync(&Temperarture_value);

		}

	}
}



