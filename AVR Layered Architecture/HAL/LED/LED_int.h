#ifndef LED_INT_H
#define LED_INT_H
#include "../../LIB/STD_TYPES.h"

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PIN0  0
#define PIN1  1
#define PIN2  2
#define PIN3  3
#define PIN4  4
#define PIN5  5
#define PIN6  6
#define PIN7  7

void HLED_voidInit(u8 Copy_u8Port,u8 Copy_u8Pin);
void HLED_voidTurnOn(u8 Copy_u8Port,u8 Copy_u8Pin);
void HLED_voidTurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin);
void HLED_voidFlip(u8 Copy_u8Port,u8 Copy_u8Pin,u16 Copy_u8Delay);



#endif
