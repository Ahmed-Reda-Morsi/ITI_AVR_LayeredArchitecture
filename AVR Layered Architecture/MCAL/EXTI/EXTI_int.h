/* 
* @author  : Ahmed Reda Morsi.
* @version : V 1.0
*/
#include "../../LIB/STD_TYPES.h"

#ifndef EXTI_INT_H
#define EXTI_INT_H

void MEXTI_voidGlobalInterruptEnable(void);
void MEXTI_voidGlobalInterruptDisable(void);

void MEXTI_voidEnableInterrupt(u8 Copy_u8InterruptPIN,u8 Copy_u8InterruptSensingLevel);

void MEXTI_voidDisableInterrupt(u8 Copy_u8InterruptPIN);

void MEXTI_0_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT0)(void));

void MEXTI_1_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT1)(void));

void MEXTI_2_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT2)(void));

#endif
