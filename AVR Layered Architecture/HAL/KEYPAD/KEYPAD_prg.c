#include <util/delay.h>
#include <stdio.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "KEYPAD_cfg.h"
#include "KEYPAD_int.h"
#include "KEYPAD_prv.h"

void HKEYPAD_voidInit(void)
{
    MDIO_voidSetPinDirection(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN0,PIN_OUT);
    MDIO_voidSetPinDirection(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN1,PIN_OUT);
    MDIO_voidSetPinDirection(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN2,PIN_OUT);
    MDIO_voidSetPinDirection(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN3,PIN_OUT);

    MDIO_voidSetPinValue(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN0,PIN_HIGH);
    MDIO_voidSetPinValue(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN1,PIN_HIGH);
    MDIO_voidSetPinValue(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN2,PIN_HIGH);
    MDIO_voidSetPinValue(KEYPAD_COLNUM_PORT,KEYPAD_COLUMN_PIN3,PIN_HIGH);


    MDIO_voidSetPinDirection(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN0,PIN_IN);
    MDIO_voidSetPinDirection(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN1,PIN_IN);
    MDIO_voidSetPinDirection(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN2,PIN_IN);
    MDIO_voidSetPinDirection(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN3,PIN_IN);

    MDIO_voidSetPullupResistor(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN0);
    MDIO_voidSetPullupResistor(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN1);
    MDIO_voidSetPullupResistor(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN2);
    MDIO_voidSetPullupResistor(KEYPAD_RAW_PORT,KEYPAD_RAW_PIN3);

}

u8 HKEYPAD_u8GetPressedKey(void)
{
	u8 Local_u8ColumnArray[KEYPAD_COLUMNS_NUMBER]={KEYPAD_COLUMN_PIN0,KEYPAD_COLUMN_PIN1,KEYPAD_COLUMN_PIN2,KEYPAD_COLUMN_PIN3};

	u8 Local_u8RawArray[KEYPAD_RAW_NUMBER]={KEYPAD_RAW_PIN0,KEYPAD_RAW_PIN1,KEYPAD_RAW_PIN2,KEYPAD_RAW_PIN3};



    u8 Local_u8KEYPAD_ButtonsValues[KEYPAD_RAW_NUMBER][KEYPAD_COLUMNS_NUMBER]=KEYPAD_BUTTON_VALUE;

    u8 Local_u8ButtonState=BUTTON_NOT_PRESSED;



    u8 Local_u8ColumnCounter=0;
    u8 Local_u8RawCounter=0;

    u8 Local_u8ButtonValue=BUTTON_NOT_PRESSED;


    for (Local_u8ColumnCounter=0; Local_u8ColumnCounter < KEYPAD_COLUMNS_NUMBER; Local_u8ColumnCounter++)
    {
        MDIO_voidSetPinValue(KEYPAD_COLNUM_PORT,Local_u8ColumnArray[Local_u8ColumnCounter],PIN_LOW);
        
        for (Local_u8RawCounter = 0; Local_u8RawCounter < KEYPAD_RAW_NUMBER; Local_u8RawCounter++)
        {
            Local_u8ButtonState=MDIO_u8GetPinValue(KEYPAD_RAW_PORT,Local_u8RawArray[Local_u8RawCounter]);

            if (Local_u8ButtonState==PIN_LOW)
            {
                Local_u8ButtonValue=Local_u8KEYPAD_ButtonsValues[Local_u8RawCounter][Local_u8ColumnCounter];

				while (Local_u8ButtonState==PIN_LOW)
				{
					Local_u8ButtonState=MDIO_u8GetPinValue(KEYPAD_RAW_PORT,Local_u8RawArray[Local_u8RawCounter]);
				}
				return Local_u8ButtonValue;
            }
            
        }
        MDIO_voidSetPinValue(KEYPAD_COLNUM_PORT,Local_u8ColumnArray[Local_u8ColumnCounter],PIN_HIGH);

    }
    
    return Local_u8ButtonValue;
}
