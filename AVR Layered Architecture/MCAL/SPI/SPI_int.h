/* 
* @author  : Ahmed Reda Morsi.
* @version : V 1.0
*/

#ifndef SPI_INT_H
#define SPI_INT_H

//******************************************************
#define MASTER	1
#define SLAVE	2



//***************************************************************
void MSPI_voidinit(void);

void MPSI_voidSendData(u8 Copy_u8Data);
u8 MPSI_u8RecieveData(void);

#endif
