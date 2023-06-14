/* 
* @author  : Ahmed Reda Morsi.
* @version : V 1.0
*/

#ifndef  TIMER2_INT_H
#define TIMER2_INT_H
#include "../../LIB/STD_TYPES.h"


void MTIMER2_voidInit(u8 Copy_u8Mode,u8 Copy_u8PreScaler);
void MTIMER2_voidCompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM);
void MTIMER2_voidPWMDutyCycle(u8 Copy_u8DutyCycle);

void MTIMER2_voidSetPreLoad(u16 Copy_u16PreLoad);
void MTIMER2_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue);
u8    MTIMER2_u8CheckOverFlow(void);
u8    MTIMER2_u8CheckCompareMatchMode(void);
void MTIMER2_voidSetCallBack_OverFlow(void(*TIMER2_OF_ISR)(void));
void MTIMER2_voidSetCallBack_CompareMatchValue(void(*TIMER2_CMV_ISR)(void));



#endif
