/*
 * EEPROM_int.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */

#ifndef EEPROM_INT_H
#define EEPROM_INT_H

typedef enum{
	EEPROM_24C02=2,
	EEPROM_24C04=4,
	EEPROM_24C08=8
}EEPROM_TPYES;




void HEEPROM_voidInit(EEPROM_TPYES Copy_u8SelectedEEPROM,u8 Copy_u8PageSelect);

void HEEPROM_voidWriteDataByte(u8 Copy_u8EEPOMAddress, u8 Copy_u8DataByte);

void HEEPROM_voidReadDataByte(u8 Copy_u8EEPOMAddress,u8 *Copy_u8DataByte);


#endif /* EEPROM_INT_H */
