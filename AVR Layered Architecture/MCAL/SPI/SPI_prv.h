/*
 * @author  : Ahmed Reda Morsi.
 * @version : V 1.0
 */
#ifndef SPI_INT_PRV_H
#define SPI_INT_PRV_H


// Bit 4 – MSTR: Master/Slave Select
#define SPCP_MSTR_PIN			4

//Bit 6 – SPE: SPI Enable
#define SPCP_SPE_PIN			6

// Bit 5 – DORD: Data Order
#define SPCP_DORD_PIN			5

// Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0


 //******************** ****************************
#define SPI_SPCR_REG		(*(volatile u8*)0x2D)
#define SPI_SPSR_REG		(*(volatile u8*)0x2E)
#define SPI_SPDR_REG		(*(volatile u8*)0x2F)

#endif
