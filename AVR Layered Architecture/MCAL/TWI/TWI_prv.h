/*
 * TWI_prv.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */

#ifndef MTWI_PRV_H
#define MTWI_PRV_H

//_______________| TWI Control Register|______________
#define TWI_TWCR_REG				(*((volatile u8*)0x56))

//Bit 7 – TWINT: TWI Interrupt Flag
#define TWCR_TWINT_BIT					7

//Bit 6 – TWEA: TWI Enable Acknowledge Bit
#define TWCR_TWIEA_BIT					6

// Bit 5 – TWSTA: TWI START Condition Bit
#define TWCR_TWSTA_BIT					5

//Bit 4 – TWSTO: TWI STOP Condition Bit
#define TWCR_TWSTO_BIT					4

//Bit 3 – TWWC: TWI Write Collision Flag
#define TWCR_TWWC_BIT					3

//Bit 2 – TWEN: TWI Enable Bit
#define TWCR_TWEN_BIT					2

//Bit 0 – TWIE: TWI Interrupt Enable
#define TWCR_TWIE_BIT					0

//_________________________|TWI Status Register|_________________
#define TWI_TWSR_REG				(*((volatile u8*)0x21))

//Bits 7..3 – TWS: TWI Status These five bits reflect the status of the TWI logic and the Two-wire Serial Bus
#define TWSR_TWS7_BIT					7
#define TWSR_TWS6_BIT					6
#define TWSR_TWS5_BIT					5
#define TWSR_TWS4_BIT					4
#define TWSR_TWS3_BIT					3

//Bits 1..0 – TWPS: TWI Prescaler Bits
//These bits can be read and written, and control the bit rate prescaler.
#define TWSR_TWPS1_BIT					1
#define TWSR_TWPS0_BIT					0


//______________________|TWI Data Register|__________________________
 //for address packets and data packets
#define TWI_TWDR_REG				(*((volatile u8*)0x23))
 // bit 0 for set read or write operation.
#define TWDR_TWRWO_bit					0

//______________________| TWI (Slave) Address Register |_________________
//Bits 7..1 – TWA: TWI (Slave) Address Register
#define TWI_TWAR_REG				(*((volatile u8*)0x22))


//Bit 0 – TWGCE: TWI General Call Recognition Enable Bit
#define TWAR_TWGCE_BIT					0

//___________________________|TWI Bit Rate Register|___________________
/*TWBR selects the division factor for the bit rate generator. The bit rate generator is a
frequency divider which generates the SCL clock frequency in the Master modes. See
“Bit Rate Generator Unit” on page 173 for calculating bit rates.*/
#define TWI_TWBR_REG				(*((volatile u8*)0x20))


#endif /* MTWI_PRV_H */
