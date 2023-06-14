/*
 * EEPROM_prg.c
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/TWI/TWI_int.h"
#include "../../MCAL/TWI/TWI_cfg.h"

#include <util/delay.h>
#include "EEPROM_cfg.h"
#include "EEPROM_int.h"
#include "EEPROM_prv.h"

static u8 EEPROM_ADDRESS=EEPROM_RESERVED_ADDRESS_BITS;

void HEEPROM_voidInit(EEPROM_TPYES Copy_u8SelectedEEPROM,u8 Copy_u8PageSelect)
{
	//initialize the master with default address 0x01
	MTWI_voidMASTERInit(MATSER_DEFUALT_ADDRESS);

	//configure the address of selected  EEPROM Type to select wanted page.
	switch(Copy_u8SelectedEEPROM)
	{
	case EEPROM_24C02:
		if(Copy_u8PageSelect<EEPROM_24c02_PAGESNUMBER)
			{
				EEPROM_ADDRESS=EEPROM_RESERVED_ADDRESS_BITS|Copy_u8PageSelect;////to set A2, A1 and A0 bits
			}
		break;
	case EEPROM_24C04:
		if(Copy_u8PageSelect<EEPROM_24c04_PAGESNUMBER)
			{
				EEPROM_ADDRESS=EEPROM_RESERVED_ADDRESS_BITS|(Copy_u8PageSelect<<1); //to set A2 and A1 bits
			}
		break;
	case EEPROM_24C08:
		if(Copy_u8PageSelect<EEPROM_24c08_PAGESNUMBER)
			{
				EEPROM_ADDRESS=EEPROM_RESERVED_ADDRESS_BITS|(Copy_u8PageSelect<<2);//to set A2
			}
		break;
	}

}

/*
void HEEPROM_voidWriteDataByte(u16 Copy_u16EEPOMAddress, u8 Copy_u8DataByte)
{
	//send start condition to start TWI
	MTWI_voidSendStartCondition();

	//select the page address of EEPROM
	MTWI_voidSendSlaveAddressWithWrite(EEPROM_ADDRESS | (Copy_u16EEPOMAddress>>8));

	//send wanted address in the chosen page
	MTWI_voidMASTERWriteDataByte((u8)Copy_u16EEPOMAddress);

	//write data in the chosen address
	MTWI_voidMASTERWriteDataByte(Copy_u8DataByte);

	//stop the connection
	MTWI_voidStopCondtion();

	//wait for EEPROM operation done.
	_delay_ms(2);
}
*/

void HEEPROM_voidWriteDataByte(u8 Copy_u8EEPOMAddress, u8 Copy_u8DataByte)
{
	//send start condition to start TWI
	MTWI_voidSendStartCondition();

	//select the page address of EEPROM
	MTWI_voidSendSlaveAddressWithWrite(EEPROM_ADDRESS);

	//send wanted address in the chosen page
	MTWI_voidMASTERWriteDataByte(Copy_u8EEPOMAddress);

	//write data in the chosen address
	MTWI_voidMASTERWriteDataByte(Copy_u8DataByte);

	//stop the connection
	MTWI_voidStopCondtion();

	//wait for EEPROM operation done.
	_delay_ms(2);
}

void HEEPROM_voidReadDataByte(u8 Copy_u8EEPOMAddress,u8 *Copy_pu8DataByte)
{
		//send start condition to start TWI
		MTWI_voidSendStartCondition();

		//select the page address of EEPROM to write operation.
		MTWI_voidSendSlaveAddressWithWrite(EEPROM_ADDRESS);

		//send wanted address in the chosen page
		MTWI_voidMASTERWriteDataByte(Copy_u8EEPOMAddress);

		//send repeated start condition to start TWI to chose Read operation  .
		MTWI_voidSendRepeatedStartCondition();

		//select the page address of EEPROM to read operation.
		MTWI_voidSendSlaveAddressWithRead(EEPROM_ADDRESS);

		// get the data from wanted address
		MTWI_voidMASTEReadDataByte(Copy_pu8DataByte);

		//stop the connection
		MTWI_voidStopCondtion();

		//wait for EEPROM operation done.
		_delay_ms(2);
}
/*void HEEPROM_voidReadDataByte(u16 Copy_u16EEPOMAddress,u8 *Copy_pu8DataByte)
{
		//send start condition to start TWI
		MTWI_voidSendStartCondition();

		//select the page address of EEPROM
		MTWI_voidSendSlaveAddressWithWrite(EEPROM_ADDRESS | (Copy_u16EEPOMAddress>>8));

		//send wanted address in the chosen page
		MTWI_voidMASTERWriteDataByte((u8)Copy_u16EEPOMAddress);

		//send repeated start condition to start TWI to chose Read operation  .
		MTWI_voidSendRepeatedStartCondition();

		//send wanted address in the chosen page
		MTWI_voidSendSlaveAddressWithRead(EEPROM_ADDRESS | (Copy_u16EEPOMAddress>>8));

		// get the data from wanted address
		MTWI_voidMASTEReadDataByte(Copy_pu8DataByte);

		//stop the connection
		MTWI_voidStopCondtion();

		//wait for EEPROM operation done.
		_delay_ms(2);
}*/
