#ifndef STEPPER_MOTOR_INT_H
#define STEPPER_MOTOR_INT_H
#include "../../LIB/STD_TYPES.h"

void HSTEPPERMOTOR_voidInit(void);

void HSTEPPERMOTOR_voidStepperFullStepCW(void);
void HSTEPPERMOTOR_voidSpecificDegreeCW(u16 Copy_u16Degree);

void HSTEPPERMOTOR_voidStepperFullStepACW(void);
void HSTEPPERMOTOR_voidSpecificDegreeACW(u16 Copy_u16Degree);
#endif
