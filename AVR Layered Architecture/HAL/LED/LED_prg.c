#include "LED_int.h"
#include "LED_cfg.h"
#include "LED_prv.h"

#include <util/delay.h>
#include "../../MCAL/DIO/DIO_int.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

void HLED_voidInit(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	MDIO_voidSetPinDirection(Copy_u8Port,Copy_u8Pin,PIN_OUT);
}   
void HLED_voidTurnOn(u8 Copy_u8Port,u8 Copy_u8Pin)
{
    MDIO_voidSetPinValue(Copy_u8Port,Copy_u8Pin,PIN_HIGH);
}
void HLED_voidTurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin)
{
    MDIO_voidSetPinValue(Copy_u8Port,Copy_u8Pin,PIN_LOW);
}
void HLED_voidFlip (u8 Copy_u8Port,u8 Copy_u8Pin,u16 Copy_u8Delay)
{
    _delay_ms(Copy_u8Delay);
    MDIO_voidSetPinValue(Copy_u8Port,Copy_u8Pin,PIN_HIGH);
    _delay_ms(Copy_u8Delay);
    MDIO_voidSetPinValue(Copy_u8Port,Copy_u8Pin,PIN_LOW);
}

