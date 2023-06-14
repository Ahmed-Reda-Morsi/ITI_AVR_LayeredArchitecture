/*
 * USART_int.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */

#ifndef USART_INT_H
#define USART_INT_H


void MUSART_voidInit(u16 Copy_u16BaudRate);
u8 MUSART_voidReceiveData(void);
void MUSART_voidSendData(u8 Copy_u8Data);

void MUSART_void_SetCallBack_TX(void(*TX_complete_ISR)(void));
void MUSART_void_SetCallBack_RX(void(*RX_complete_ISR)(void));
void MUSART_void_SetCallBack_UDREmpty(void(*UDR_Empty_ISR)(void));
#endif /* USART_INT_H */
