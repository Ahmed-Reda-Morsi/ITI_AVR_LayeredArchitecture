/*
 * SPI_KeyPad_LCD.c
 *
 *  Created on: Apr 6, 2023
 *      Author: aland
 */


/*
 * SPI_MASTER.c
 *
 *  Created on: Apr 6, 2023
 *      Author: aland
 */


#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/DIO/DIO_cfg.h"
#include "../MCAL/SPI/SPI_int.h"
#include "../HAL/LCD/LCD_cfg.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEYPAD/KEYPAD_cfg.h"
#include "../HAL/KEYPAD/KEYPAD_int.h"


#define CODE 	SLAVE


#if		CODE == MASTER
//_______________________| MASTER |________________________________
void main(void)
{
	HKEYPAD_voidInit();

	MDIO_voidSetPinDirection(PORTB,PIN4,PIN_OUT);  	//SSPIN
	MDIO_voidSetPinDirection(PORTB,PIN5,PIN_OUT);  	// MOSI
	MDIO_voidSetPinDirection(PORTB,PIN6,PIN_IN);    // MISO
	MDIO_voidSetPinDirection(PORTB,PIN7,PIN_OUT);   // SCK

	MSPI_voidinit();

	 u8 Local_ButtonValue;

	MDIO_voidSetPinValue(PORTB,PIN4,PIN_HIGH); // stop select pin
	while(1)
	{
		Local_ButtonValue=HKEYPAD_u8GetPressedKey();

		MDIO_voidSetPinValue(PORTB,PIN4,PIN_LOW);

		MPSI_voidSendData(Local_ButtonValue);

		MDIO_voidSetPinValue(PORTB,PIN4,PIN_HIGH);
	}
}


#elif CODE==SLAVE
////_______________________| SLAVE |________________________________
void main(void)
{
	HLCD_voidInit(HLCD_8BIT_MODE);

	MDIO_voidSetPinDirection(PORTB,PIN4,PIN_IN);  	//SSPIN
	MDIO_voidSetPinDirection(PORTB,PIN5,PIN_IN);  	// MOSI
	MDIO_voidSetPinDirection(PORTB,PIN6,PIN_OUT);   // MISO
	MDIO_voidSetPinDirection(PORTB,PIN7,PIN_IN);   	// SCK

	MSPI_voidinit();

	 u8 Local_RevcievedData=1;
	while(1)
	{
		Local_RevcievedData=MPSI_u8RecieveData();
			if(Local_RevcievedData!=0xff)
				HLCD_voidSendNumber(Local_RevcievedData);

	}
}

#endif
