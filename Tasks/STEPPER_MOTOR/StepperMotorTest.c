/*
 *StepperMotorTest.c
 *
 *  Created on: Mar 29, 2023
 *      Author: Ahmed_Reda
 */
#include <util/delay.h>
#include "../HAL/STEPPERMOTOR_28BYJ-48/STEPPER_MOTOR_int.h"

int main(void)
{
	HSTEPPERMOTOR_voidInit();

  while(1)
  {
		HSTEPPERMOTOR_voidStepperFullStepCW(); // rotate 360 clockwise
		_delay_ms(5000);
		HSTEPPERMOTOR_voidSpecificDegreeCW(65);  // rotate 65  clockwise
		_delay_ms(5000);
		HSTEPPERMOTOR_voidSpecificDegreeACW(65); // rotate 65 anti clockwise
		_delay_ms(5000);
		HSTEPPERMOTOR_voidStepperFullStepACW();// rotate  360 anti clockwise
		_delay_ms(5000);

  }


}
