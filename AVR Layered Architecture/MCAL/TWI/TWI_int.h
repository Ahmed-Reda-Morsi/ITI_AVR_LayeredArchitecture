/*
 * TWI_int.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */

#ifndef MTWI_INT_H
#define MTWI_INT_H

void MTWI_voidMASTERInit(u8 Copy_u8SlaveAddress);
void MTWI_voidSLAVEInit(u8 Copy_u8SlaveAddress);

void MTWI_voidSendStartCondition(void);
void MTWI_voidSendRepeatedStartCondition(void);

void MTWI_voidSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
void MTWI_voidSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

void MTWI_voidMASTERWriteDataByte(u8 Copy_u8DataByte);
void MTWI_voidMASTEReadDataByte(u8* Copy_pu8DataByte);

void MTWI_voidStopCondtion(void);

//TODO: Slave Functions.


#endif /* MTWI_INT_H */
