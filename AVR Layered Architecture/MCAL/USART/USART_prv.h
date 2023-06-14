/*
 * USART_prv.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */

#ifndef USART_PRV_H
#define USART_PRV_H

//_______________________|USART I/O Data Register|__________________________________
/*
The USART Transmit Data Buffer Register and USART Receive Data Buffer Registers
share the same I/O address referred to as USART Data Register or UDR. The Transmit
Data Buffer Register (TXB) will be the destination for data written to the UDR Register
location. Reading the UDR Register location will return the contents of the Receive Data
Buffer Register (RXB).
 */
#define MUSART_UDR_REG 					*((volatile u8*)0x2C)



//_______________________|USART Control and Status Register A|__________________________________
#define MUSART_UCSRA_REG 				*((volatile u8*)0x2B)

/*
This flag bit is set when there are unread data in the receive buffer and cleared when the
receive buffer is empty
*/
// Bit 7 – RXC: USART Receive Complete  FLag
#define UCSRA_RXC_BIT					7


/*
This flag bit is set when the entire frame in the transmit Shift Register has been shifted
out and there are no new data currently present in the transmit buffer (UDR). The TXC
Flag bit is automatically cleared when a transmit complete interrupt is executed, or it can
be cleared by writing a one to its bit location. The TXC Flag can generate a Transmit
Complete interrupt (see description of the TXCIE bit).
*/
//Bit 6 – TXC: USART Transmit Complete   FLag
#define UCSRA_TXC_BIT					6

/*
The UDRE Flag indicates if the transmit buffer (UDR) is ready to receive new data. If
UDRE is one, the buffer is empty, and therefore ready to be written. The UDRE Flag can
generate a Data Register empty Interrupt (see description of the UDRIE bit).
UDRE is set after a reset to indicate that the transmitter is ready
*/
// Bit 5 – UDRE: USART Data Register Empty Flag
#define UCSRA_UDRE_BIT					5

/*
This bit is set if the next character in the receive buffer had a Frame Error when
received,Always set this bit to zero when writing to UCSRA
*/
//Bit 4 – FE: Frame Error
#define UCSRA_FE_BIT					4

/*
This bit is set if a Data OverRun condition is detected. A Data OverRun occurs when the
receive buffer is full (two characters),Always set this bit to zero when writing to UCSRA.
 */
//Bit 3 – DOR: Data OverRun
#define UCSRA_DOR_BIT					3


/*
This bit is set if the next character in the receive buffer had a Parity Error when received
and the parity checking was enabled at that point (UPM1 = 1).
 */
//Bit 2 – PE: Parity Error
#define UCSRA_RE_BIT					2

/*
This bit only has effect for the asynchronous operation. Write this bit to zero when using
synchronous operation.
*/
// Bit 1 – U2X: Double the USART Transmission Speed
#define UCSRA_U2X_BIT					1

/*
This bit enables the Multi-processor Communication mode. When the MPCM bit is written to one, all the incoming frames received by the USART receiver that do not contain
address information will be ignored. The transmitter is unaffected by the MPCM setting
*/
//Bit 0 – MPCM: Multi-processor Communication Mode
#define UCSRA_MPCM_BIT					0


//_______________________|USART Control and Status Register B |__________________________________
#define MUSART_UCSRB_REG 				*((volatile u8*)0x2A)

/*
Writing this bit to one enables interrupt on the RXC Flag. A USART Receive Complete
Interrupt will be generated only if the RXCIE bit is written to one,
*/
// Bit 7 – RXCIE: RX Complete Interrupt Enable
#define UCSRB_RXCIE_BIT					7

/*
Writing this bit to one enables interrupt on the TXC Flag. A USART Transmit Complete
Interrupt will be generated only if the TXCIE bit is written to one,
*/
// Bit 6 – TXCIE: TX Complete Interrupt Enable
#define UCSRB_TXCIE_BIT					6

/*
Writing this bit to one enables interrupt on the UDRE Flag.
*/
//Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
#define UCSRB_UDRIE_BIT					5


/*
Writing this bit to one enables the USART Receiver. The Receiver will override normal
port operation for the RxD pin when enabled. Disabling the Receiver will flush the
receive buffer invalidating the FE, DOR, and PE Flags.
*/
//Bit 4 – RXEN: Receiver Enable
#define UCSRB_RXEN_BIT					4


/*
Writing this bit to one enables the USART Transmitter. The Transmitter will override normal port operation for the TxD pin when enabled. The disabling of the Transmitter
(writing TXEN to zero) will not become effective until ongoing and pending transmissions are completed, i.e., when the transmit Shift Register and transmit Buffer Register
do not contain data to be transmitted. When disabled, the transmitter will no longer override the TxD port.
*/
//Bit 3 – TXEN: Transmitter Enable
#define UCSRB_TXEN_BIT					3

/*
The UCSZ2 bits combined with the UCSZ1:0 bit in UCSRC sets the number of data bits
(Character Size) in a frame the receiver and transmitter use.
*/
//Bit 2 – UCSZ2: Character Size
#define UCSRB_UCSZ2_BIT					2

/*
RXB8 is the ninth data bit of the received character when operating with serial frames
with nine data bits. Must be read before reading the low bits from UDR.
*/
//Bit 1 – RXB8: Receive Data Bit 8
#define UCSRB_RXB8_BIT					1


/*
TXB8 is the ninth data bit in the character to be transmitted when operating with serial
frames with nine data bits. Must be written before writing the low bits to UDR
*/
//Bit 0 – TXB8: Transmit Data Bit 8
#define UCSRB_TXB8_BIT					0

//_______________________|USART Control and Status Register C|__________________________________
/*
The UCSRC Register shares the same I/O location as the UBRRH Register. See the
“Accessing UBRRH/ UCSRC Registers” on page 156 section which describes how to
access this register.
*/
#define MUSART_UCSRC_REG 				*((volatile u8*)0x40)


/*
This bit selects between accessing the UCSRC or the UBRRH Register. It is read as
one when reading UCSRC. The URSEL must be one when writing the UCSRC
*/
// Bit 7 – URSEL: Register Select
#define UCSRC_URSEL_BIT						7

/*
This bit selects between Asynchronous and Synchronous mode of operation
*/
//Bit 6 – UMSEL: USART Mode Select
#define UCSRC_UMSEL_BIT						6


/*
These bits enable and set type of parity generation and check. If enabled,
the transmitter will automatically generate and send the parity of the transmitted data bits
within each frame. The Receiver will generate a parity value for the incoming data
and compare it to the UPM0 setting.
If a mismatch is detected, the PE Flag in UCSRA will be set
*/
//Bit 5:4 – UPM1:0: Parity Mode
#define UCSRC_UPM1_BIT						5
#define UCSRC_UPM0_BIT						4


/*
This bit selects the number of Stop Bits to be inserted by the Transmitter. The Receiver
ignores this setting.
//Bit 3 – USBS: Stop Bit Select*/
#define UCSRC_USBS_BIT						3


/*
The UCSZ1:0 bits combined with the UCSZ2 bit in UCSRB sets the number of data bits
(Character Size) in a frame the Receiver and Transmitter use
*/
//UCSZ1:0: Character Size
#define UCSRC_UCSZ1_BIT						2
#define UCSRC_UCSZ0_BIT						1

/*
This bit is used for Synchronous mode only. Write this bit to zero when Asynchronous
mode is used. The UCPOL bit sets the relationship between data output change and
data input sample, and the synchronous clock (XCK)
*/
// Bit 0 – UCPOL: Clock Polarity
#define UCSRC_UCPOL_BIT						0

//_______________________|USART Baud Rate Registers|__________________________________
/*
Bit 15(7 in UBRRH) – URSEL: Register Select
This bit selects between accessing the UBRRH or the UCSRC Register. It is read as
zero when reading UBRRH. The URSEL must be zero when writing the UBRRH.
*/
#define MUSART_UBRRH_REG 				*((volatile u8*)0x40)
#define MUSART_UBRRL_REG 				*((volatile u8*)0x29)
/*
//Bit 11:0 – UBRR11:0: USART Baud Rate Register
This is a 12-bit register which contains the USART baud rate. The UBRRH contains the
four most significant bits, and the UBRRL contains the 8 least significant bits of the
USART baud rate. Ongoing transmissions by the transmitter and receiver will be corrupted if the baud rate is changed. Writing UBRRL will trigger an immediate update of
the baud rate prescaler.
*/
//__________________________________________________________________________________

#endif /* USART_PRV_H */
