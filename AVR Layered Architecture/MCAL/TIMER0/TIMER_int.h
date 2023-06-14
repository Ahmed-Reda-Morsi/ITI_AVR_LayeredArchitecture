/* 
* @author  : Ahmed Reda Morsi.
* @version : V 1.0
*/

#ifndef  TIMER_INT_H
#define TIMER_INT_H
#include "../../LIB/STD_TYPES.h"

//______________________________________________________________________________

void MTIMER0_voidInit(u8 Copy_u8Mode,u8 Copy_u8PreScaler);
void MTIMER0_voidCompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM);
void MTIMER0_voidPWMDutyCycle(u8 Copy_u8DutyCycle);

void MTIMER0_voidDelayInterrupt_MS(u32 Copy_u32Delay);
void MTIMER0_voidDelay_MS(u32 Copy_u32Delay);

void MTIMER0_voidSetPreLoad(u16 Copy_u16PreLoad);

void MTIMER0_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue);

u8    MTIMER0_u8CheckOverFlow(void);
u8    MTIMER0_u8CheckCompareMatchMode(void);

void MTIMER0_voidSetCallBack_REQUIREDTIME(void (*TIMER0_OF_RT_ISR)(void));
void MTIMER0_voidSetCallBack_OverFlow(void(*TIMER0_OF_ISR)(void));
void MTIMER0_voidSetCallBack_CompareMatchValue(void(*TIMER0_CMV_ISR)(void));



#endif
