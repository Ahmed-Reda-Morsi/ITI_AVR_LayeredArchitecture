#ifndef STEPPER_MOTOR_CFG_H
#define STEPPER_MOTOR_CFG_H
#include "../../LIB/STD_TYPES.h"

#define STEPPER_MOTOR_PORT 									PORTA

// coil 1 pin
#define STEPPER_MOTOR_PIN0									PIN0
// coil 2 pin
#define STEPPER_MOTOR_PIN1									PIN1
// coil 3 pin
#define STEPPER_MOTOR_PIN2									PIN2
// coil 4 pin
#define STEPPER_MOTOR_PIN3									PIN3

#define  STEPPERMOTOR_TOTAL_ITERATIONS 			512
#define  STEPPERMOTOR_STEP           						11.25
#define  STEPPERMOTOR_STEP_DELAY           			5

#define  STEPPERMOTOR_GEARRATIO           				64

#define  STEPPERMOTOR_TRUTHTABLE_RAWS       	4


#endif
