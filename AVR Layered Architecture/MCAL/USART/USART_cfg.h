/*
 * USART_cfg.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */

#ifndef USART_CFG_H
#define USART_CFG_H

#define F_CPU			8000000UL //HZ

#define NOT_RECEIVED	0xff   // RX_DATA  DEFAULT in interrupt mode


//_________________________________| BaudRate    |______________________________
//#define USART_BAUDRATE_PRECALLER			 ((F_CPU/(BAUDRATE*16UL))-1)

//_________________________________| USART MODES |______________________________
 // UCSRC  	  UMSEL-> 0	 U2X->0
# define USART_ASYNC_NORMAL_MODE						0

 // UCSRC  	  UMSEL-> 1
# define USART_SYNC_MODE								1

 // UCSRC  	  UMSEL-> 1    U2X->1
# define USART_AYNC_DOUBLESPEED_MODE					2

# define USART_MODE									USART_ASYNC_NORMAL_MODE

//________________________________| Parity Modes|________________________
//	UCSRC  UPM1-> 0     UPM0-> 0
# define USART_PARITY_DISABLED				0
//	UCSRC  UPM1-> 1     UPM0-> 0
# define USART_PARITY_EVENPARITY			2
//	UCSRC  UPM1-> 1     UPM0-> 1
# define USART_PARITY_ODDPARITY				3

#define USART_PARITY_MODE				 USART_PARITY_DISABLED

//________________________________|Stop Bit Select|________________________

//	UCSRC  USBS-> 0
#define  USART_STOPBIT_ONEBIT				0
//	UCSRC  USBS-> 1
#define  USART_STOPBIT_TWOBIT				1

#define USART_STOPBIT_MODE		USART_STOPBIT_TWOBIT
//________________________________|Character Size|________________________
//	UCSZ2->0		 UCSZ1->0 			UCSZ0->0
#define  USART_CHARACTERSIZE_5BITS				0
//	UCSZ2->0		 UCSZ1->0 			UCSZ0->1
#define  USART_CHARACTERSIZE_6BITS				1
//	UCSZ2->0		 UCSZ1->1 			UCSZ0->0
#define  USART_CHARACTERSIZE_7BITS				2
//	UCSZ2->0		 UCSZ1->1			UCSZ0->1
#define  USART_CHARACTERSIZE_8BITS				3
//	UCSZ2->1		 UCSZ1->1 			UCSZ0->1
#define  USART_CHARACTERSIZE_9BITS				7


#define  USART_CHARACTERSIZE_MODE				USART_CHARACTERSIZE_8BITS


//________________________________|Clock Polarity between TX and RX|________________________
//	UCPOL-> 0
#define  USART_CP_TX_RISING_RX_FALLING				0
//	UCPOL-> 1
#define  USART_CP_TX_FALLING_RX_RISING				1


//___________________________________________________________________________________________

#endif /* USART_CFG_H */
