/*
 * USART_prg.c
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "USART_cfg.h"
#include "USART_int.h"
#include "USART_prv.h"

static u8 RX_DataUpdated=0;
/*pointers for callback functions */
static void(*PtrReceivedCompleteINT)(void)=NULL_PTR;
static void(*PtrTransmitCompleteINT)(void)=NULL_PTR;
static void(*PtrDataRegisterEmptyINT)(void)=NULL_PTR;

/*variables for holding TX and RX data*/
#if 	USART_CHARACTERSIZE_MODE == USART_CHARACTERSIZE_9BITS
static u16 TX_Data='\0';
static u16 RX_Data='\0';
#else
static u8 TX_Data='\0';
static u8 RX_Data='\0';
#endif

//----------------------------------------------------------------
void MUSART_voidInit(u16 Copy_u8BaudRate)
{
	//to select UCSRC  Register
	SET_BIT(MUSART_UCSRC_REG,UCSRC_URSEL_BIT);

	//1_ Set Stop Bits
		#if		USART_STOPBIT_MODE 	==	USART_STOPBIT_ONEBIT
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_USBS_BIT);

		#elif 	USART_STOPBIT_MODE	==	USART_STOPBIT_TWOBIT
				SET_BIT(MUSART_UCSRC_REG,UCSRC_USBS_BIT);
		#endif

		//2_ Set parity bits.
		#if 	USART_PARITY_MODE == USART_PARITY_DISABLED
				// Parity disable
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UPM0_BIT);
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UPM1_BIT);

		#elif 	USART_PARITY_MODE == USART_PARITY_EVENPARITY
				//even parity
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UPM0_BIT);
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UPM1_BIT);

		#elif 	USART_PARITY_MODE == USART_PARITY_ODDPARITY
				//odd parity
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UPM0_BIT);
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UPM1_BIT);

		#endif

		//3_ Set Character size
		#if		USART_CHARACTERSIZE_MODE == USART_CHARACTERSIZE_5BITS
				//select 5 bit data frame
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ0_BIT);
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ1_BIT);
				CLEAR_BIT(MUSART_UCSRB_REG,UCSRB_UCSZ2_BIT);

		#elif 	USART_CHARACTERSIZE_MODE == USART_CHARACTERSIZE_6BITS
				//select 6 bit data frame
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ0_BIT);
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ1_BIT);
				CLEAR_BIT(MUSART_UCSRB_REG,UCSRB_UCSZ2_BIT);

		#elif 	USART_CHARACTERSIZE_MODE == USART_CHARACTERSIZE_7BITS
				//select 7 bit data frame
				CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ0_BIT);
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ1_BIT);
				CLEAR_BIT(MUSART_UCSRB_REG,UCSRB_UCSZ2_BIT);

		#elif 	USART_CHARACTERSIZE_MODE == USART_CHARACTERSIZE_8BITS
				//select 8 bit data frame
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ0_BIT);
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ1_BIT);
				CLEAR_BIT(MUSART_UCSRB_REG,UCSRB_UCSZ2_BIT);

		#elif 	USART_CHARACTERSIZE_MODE == USART_CHARACTERSIZE_9BITS
				//select 9 bit data frame
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ0_BIT);
				SET_BIT(MUSART_UCSRC_REG,UCSRC_UCSZ1_BIT);
				SET_BIT(MUSART_UCSRB_REG,UCSRB_UCSZ2_BIT);

		#endif

	//4_ USART mode select
	#if 	USART_MODE == USART_SYNC_MODE
			//Synchronous Operation
		SET_BIT(MUSART_UCSRC_REG,UCSRC_UMSEL_BIT);
		Copy_u8BaudRate=(F_CPU/(2UL*Copy_u8BaudRate))-1;

	#elif 	USART_MODE == USART_ASYNC_NORMAL_MODE
		 //Asynchronous Operation
		CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UMSEL_BIT);
		//Asynchronous Normal Mode
		CLEAR_BIT(MUSART_UCSRA_REG,UCSRA_U2X_BIT);
		Copy_u8BaudRate=(F_CPU/(16UL*Copy_u8BaudRate))-1;

	#elif	USART_MODE == USART_AYNC_DOUBLESPEED_MODE
		// Asynchronous Operation
		CLEAR_BIT(MUSART_UCSRC_REG,UCSRC_UMSEL_BIT);
		//Asynchronous Double Speed Mode
		SET_BIT(MUSART_UCSRA_REG,UCSRA_U2X_BIT);
		Copy_u8BaudRate=(F_CPU/(8UL*Copy_u8BaudRate))-1;

	#endif

	//5_Set baudrate.
	CLEAR_BIT(MUSART_UBRRH_REG,UCSRC_URSEL_BIT);// to access UBRRH register for buadrate.
	MUSART_UBRRH_REG=(Copy_u8BaudRate>>8);
	MUSART_UBRRL_REG=Copy_u8BaudRate;

	// _ Enable receiver and transmitter
	SET_BIT(MUSART_UCSRB_REG,UCSRB_RXEN_BIT);
	SET_BIT(MUSART_UCSRB_REG,UCSRB_TXEN_BIT);

}

void MUSART_voidSendData(u8 Copy_u8Data)
{
	//1_ wait until the USART Data Register is empty.
	while(GET_BIT(MUSART_UCSRA_REG,UCSRA_UDRE_BIT)==0);
	//2_ put Data in Data Register
	MUSART_UDR_REG=Copy_u8Data;/* Note: Writing on `UDR` clears the UDRE flag*/
}

u8 MUSART_voidReceiveData(void)
{
	//1_ wait until the receiving is complete.
	while(GET_BIT(MUSART_UCSRA_REG,UCSRA_RXC_BIT)==0);
	//2_return Data in Data Register
	return MUSART_UDR_REG;  /* Note: Reading `UDR` Clears the RXC flag*/
}
//-------------------------------Interrupt----------------------------------

/*set call back functions for TX */
void MUSART_void_SetCallBack_TX(void(*TX_complete_ISR)(void))
{
	/*SET ISR of TX is complete*/
	PtrTransmitCompleteINT=TX_complete_ISR;
}
/*set call back functions for  RX*/
void MUSART_void_SetCallBack_RX(void(*RX_complete_ISR)(void))
{
	/*SET ISR of RX is complete*/
	PtrReceivedCompleteINT=RX_complete_ISR;
}
/*set call back functions for  data register empty*/
void MUSART_void_SetCallBack_UDREmpty(void(*UDR_Empty_ISR)(void))
{
	/*SET ISR of data register empty ISR*/
	PtrDataRegisterEmptyINT=UDR_Empty_ISR;
}

void MUSART_voidSendData_Interrupt(u8 Copy_u8Data)
{
	// set TX data value
	TX_Data=Copy_u8Data;

	/*enable data register empty Interrupt*/
	SET_BIT(MUSART_UCSRB_REG,UCSRB_UDRIE_BIT);

	/*enable TX Interrupt*/
	SET_BIT(MUSART_UCSRB_REG,UCSRB_TXCIE_BIT);
}



/* USART Interrupt Data Register Empty */
void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	// put transmission Data in Data Register
	MUSART_UDR_REG=TX_Data;

	// execute ISR for data register is empty
	if(PtrDataRegisterEmptyINT!=NULL_PTR)
	{
		PtrDataRegisterEmptyINT();
	}

	//stop interrupt for data register is empty
	CLEAR_BIT(MUSART_UCSRB_REG,UCSRB_UDRIE_BIT);

}
/* USART Interrupt TX complete*/
void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{

	// execute ISR of TX complete if it has been set..
	if(PtrTransmitCompleteINT!=NULL_PTR)
		{
		PtrTransmitCompleteINT();
		}

	/*Disable TX Interrupt*/
	CLEAR_BIT(MUSART_UCSRB_REG,UCSRB_TXCIE_BIT);

}
/* USART Interrupt RX complete*/
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{

   // update RX_data with received data
	RX_Data=MUSART_UDR_REG;

	// to indicate that RX_Data is updated
	RX_DataUpdated=1;

	// execute ISR of RX complete if it has been set..
	if(PtrReceivedCompleteINT!=NULL_PTR)
	{
	PtrReceivedCompleteINT();
	}

	/*Disable RX Interrupt*/
	CLEAR_BIT(MUSART_UCSRB_REG,UCSRB_RXCIE_BIT);
}

u8 MUSART_voidReceiveData_Interrupt(void)
{

	/*enable RX Interrupt*/
	SET_BIT(MUSART_UCSRB_REG,UCSRB_RXCIE_BIT);

	u8 Local_RX_Data=NOT_RECEIVED;
	if(RX_DataUpdated&&RX_Data!='\0')
	{
		RX_DataUpdated=0;
	return RX_Data;   // return received data if it's updated
	}
	else
	{
	return Local_RX_Data; // return NOT_RECEIVED if no data sent
	}

}
