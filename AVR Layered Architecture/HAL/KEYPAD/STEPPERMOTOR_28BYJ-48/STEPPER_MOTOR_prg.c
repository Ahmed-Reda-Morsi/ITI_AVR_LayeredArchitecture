#include <util/delay.h>
#include "../../MCAL/DIO/DIO_int.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "STEPPER_MOTOR_cfg.h"
#include "STEPPER_MOTOR_int.h"
#include "STEPPER_MOTOR_prv.h"

void  HSTEPPERMOTOR_voidInit(void)
{
	MDIO_voidSetPinDirection(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_OUT);
	MDIO_voidSetPinDirection(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_OUT);
	MDIO_voidSetPinDirection(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_OUT);
	MDIO_voidSetPinDirection(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_OUT);

	// set default values as high
	MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
	MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
	MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
	MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
}

void HSTEPPERMOTOR_voidStepperFullStepCW(void)
{
	u16 LocalIteration;
	for (LocalIteration=0; LocalIteration < STEPPERMOTOR_TOTAL_ITERATIONS; LocalIteration++)
	{	
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
	}
	
}

void HSTEPPERMOTOR_voidSpecificDegreeCW(u16 Copy_u16Degree)
{
	u16 LocalIteration;
	u16 LocalRequiredIterationsNumber=(((Copy_u16Degree/STEPPERMOTOR_STEP)*STEPPERMOTOR_GEARRATIO)/STEPPERMOTOR_TRUTHTABLE_RAWS);
	//u16 LocalRequiredIterationsNumber=((Copy_u16Degree/360)*STEPPERMOTOR_TOTAL_ITERATIONS);

	for (LocalIteration=0; LocalIteration < LocalRequiredIterationsNumber; LocalIteration++)
	{	
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
	}
	
}
void HSTEPPERMOTOR_voidStepperFullStepACW(void)
{
	u16 LocalIteration;
	for (LocalIteration=0; LocalIteration < STEPPERMOTOR_TOTAL_ITERATIONS; LocalIteration++)
	{	
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
	}
	
}

void HSTEPPERMOTOR_voidSpecificDegreeACW(u16 Copy_u16Degree)
{
	u16 LocalIteration;
	u16 LocalRequiredIterationsNumber=(((Copy_u16Degree/STEPPERMOTOR_STEP)*STEPPERMOTOR_GEARRATIO)/STEPPERMOTOR_TRUTHTABLE_RAWS);
	//u16 LocalRequiredIterationsNumber=((Copy_u16Degree/360)*STEPPERMOTOR_TOTAL_ITERATIONS);

	for (LocalIteration=0; LocalIteration < LocalRequiredIterationsNumber; LocalIteration++)
	{	
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		
		
	}
	
}


/* 		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(STEPPERMOTOR_STEP_DELAY);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_LOW);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_HIGH);
		_delay_ms(2);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN0,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,PIN_HIGH);
		MDIO_voidSetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,PIN_LOW);
		_delay_ms(STEPPERMOTOR_STEP_DELAY); */