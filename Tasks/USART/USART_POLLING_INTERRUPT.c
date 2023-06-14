	///*

// * main.c
// *
// *  Created on: Apr 8, 2023
// *      Author: Ahmed Reda
// */
//
//#include "../HAL/LCD/LCD_cfg.h"
//#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LED/LED_int.h"
#include "../HAL/LED/LED_cfg.h"
#include "../HAL/LCD/LCD_cfg.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/USART/USART_cfg.h"
#include "../MCAL/USART/USART_int.h"


#include <util/delay.h>
#define NODE1		1
#define NODE2		2

#define INTERRUPT	1
#define POLLING		2
//_______________________________________________________
#define code_type 	POLLING
#define code NODE2

//_______________________________________________________

#if code_type==INTERRUPT
//______________________________________________________
void UDR_EMPTY_ISR(void)
{
	HLED_voidInit(PORTA,PIN1);
	HLED_voidFlip(PORTA,PIN1,50);

}
void TX_ISR(void)
{
	HLED_voidInit(PORTA,PIN2);
	HLED_voidFlip(PORTA,PIN2,50);
}
void RX_ISR(void)
{
	HLED_voidInit(PORTA,PIN3);
	HLED_voidFlip(PORTA,PIN3,50);

}
//_____________________ USART WITH Interrupt__________________________________

#if  code ==NODE1
//int main(void)
//{
//	HLED_voidInit(PORTC,PIN0);
//	HLED_voidInit(PORTC,PIN5);
//	MUSART_voidInit(9600);
//	MEXTI_voidGlobalInterruptEnable();
//	MUSART_void_SetCallBack_RX(RX_ISR);
//	MUSART_void_SetCallBack_TX(TX_ISR);
//	MUSART_void_SetCallBack_UDREmpty(UDR_EMPTY_ISR);
//
//
//	while(1)
//	{
//		_delay_ms(1000);
//		HLED_voidFlip(PORTC,PIN0,200);
//		MUSART_voidSendData_Interrupt('A');
//		_delay_ms(2000);
//		HLED_voidTurnOFF(PORTA,PIN0);
//	if(MUSART_voidReceiveData_Interrupt()=='B')
//		{
//		HLED_voidFlip(PORTC,PIN5,200);
//		}
//	}
//	return 0;
//}
//#elif code==2
//int main(void)
//{
//	HLED_voidInit(PORTD,PIN7);
//	MUSART_voidInit(9600);
//	MEXTI_voidGlobalInterruptEnable();
//	MUSART_void_SetCallBack_RX(RX_ISR);
//	MUSART_void_SetCallBack_TX(TX_ISR);
//	MUSART_void_SetCallBack_UDREmpty(UDR_EMPTY_ISR);
//	while(1)
//	{
//		HLED_voidTurnOFF(PORTD,PIN7);
//		if(MUSART_voidReceiveData_Interrupt()=='A')
//		{
//			HLED_voidFlip(PORTD	,PIN7,200);
//			_delay_ms(1000);
//			MUSART_voidSendData_Interrupt('B');
//		}
//		_delay_ms(1000);
//	}
// return 0;
//}
//#endif

int main(void)
{
	HLCD_voidInit(HLCD_4BIT_MODE);

	MUSART_voidInit(9600);
	MEXTI_voidGlobalInterruptEnable();
	MUSART_void_SetCallBack_RX(RX_ISR);
	MUSART_void_SetCallBack_TX(TX_ISR);
	MUSART_void_SetCallBack_UDREmpty(UDR_EMPTY_ISR);

	HLED_voidInit(PORTC,PIN0);
	HLED_voidInit(PORTC,PIN5);

	u8 node1[]="NiceToMeetYou N2!";
	u8 i=0;
	u8 receivedcharacter=0;

	// send data to node2
	  HLCD_voidSendString("Sending To Node2:");
		for(i=0;node1[i]!='\0';i++)
		{
			MUSART_voidSendData_Interrupt(node1[i]);
		}
		HLCD_voidSendString("DONE");

		_delay_ms(2000);
		HLCD_voidClearDisplay();

	// receive from node2
		receivedcharacter=NOT_RECEIVED;
		HLCD_voidSendString("Data From Node2:");
		while(receivedcharacter!='!')
		{
			receivedcharacter=MUSART_voidReceiveData_Interrupt();
			if(receivedcharacter==NOT_RECEIVED)
					continue;
			HLCD_voidSendData(receivedcharacter);
		}
		_delay_ms(2000);
		HLCD_voidClearDisplay();

		while(1)
		{

		}

	return 0;
}
#elif code==NODE2
int main(void)
{
	HLCD_voidInit(HLCD_4BIT_MODE);

	HLED_voidInit(PORTD,PIN7);
	MUSART_voidInit(9600);
	MEXTI_voidGlobalInterruptEnable();
	MUSART_void_SetCallBack_RX(RX_ISR);
	MUSART_void_SetCallBack_TX(TX_ISR);
	MUSART_void_SetCallBack_UDREmpty(UDR_EMPTY_ISR);

	//u8 node2[6]={'R','E','D','A','!','\0'};
	u8 node2[]="ThankYou N1!";
	u8 i=0;
	u8 receivedcharacter=NOT_RECEIVED;

		//receive from node1
		receivedcharacter=NOT_RECEIVED;
		HLCD_voidSendString("Data From Node1:");
		while(receivedcharacter!='!')
		{
			receivedcharacter=MUSART_voidReceiveData_Interrupt();
			if(receivedcharacter==NOT_RECEIVED)
					continue;
			HLCD_voidSendData(receivedcharacter);
		}
		_delay_ms(2000);
		HLCD_voidClearDisplay();

	//send to node1
		HLCD_voidSendString("Sending To Node1:");
		for(i=0;node2[i]!='\0';i++)
		{
			MUSART_voidSendData_Interrupt(node2[i]);

		}
		HLCD_voidSendString("DONE");
		_delay_ms(2000);
		HLCD_voidClearDisplay();


		while(1)
		{

		}

}
#endif
#elif code_type==POLLING
//_____________________ USART WITH POLLING__________________________________
 #if  code ==NODE1
void main(void)
{
	HLCD_voidInit(HLCD_4BIT_MODE);
	HLED_voidInit(PORTC,PIN0);
	HLED_voidInit(PORTC,PIN5);
	MUSART_voidInit(19200);
	u8 node1[]="HowAreYou N2!";
	u8 i=0;
	while(1)
	{
		_delay_ms(1000);
		 HLCD_voidSendString("Sending To Node2:");
		i=0;
		for(;node1[i]!='\0';i++)
		{
			MUSART_voidSendData(node1[i]);
		HLED_voidFlip(PORTC,PIN0,100);
		}
		HLCD_voidSendString("Done");

		_delay_ms(1000);
		HLCD_voidClearDisplay();

	}

}
#elif code==NODE2
void main(void)
{
	HLCD_voidInit(HLCD_4BIT_MODE);

	HLED_voidInit(PORTD,PIN7);
	MUSART_voidInit(19200);

	u8 i=0;
	u8 receivedCharacter=NOT_RECEIVED;
	while(1)
	{
		receivedCharacter=NOT_RECEIVED;
		HLCD_voidSendString("Data From Node1:");
		while(receivedCharacter!='!')
		{
			receivedCharacter=MUSART_voidReceiveData();
			HLCD_voidSendData(receivedCharacter);
		}
		HLCD_voidClearDisplay();



	}
}
#endif
#endif
