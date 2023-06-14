#ifndef LCD_INT_H
#define LCD_INT_H
#include "../../LIB/STD_TYPES.h"

void HLCD_voidInit(u8 Copy_u8LCDMODE);


void HLCD_voidSendData(u8 Copy_u8Data);
void HLCD_voidSendSpectialChar(u8* Copy_pu8char,u8 Copy_u8PatternNumber, u8 Copy_u8YPostion,u8 Copy_u8XPostion);
void HLCD_voidSendString(const u8* Copy_pu8Data);
void HLCD_voidGoToXY(u8 Copy_u8YPostion,u8 Copy_u8XPostion);
void HLCD_voidSendCommand(u8 Copy_u8Command);
void HLCD_voidClearDisplay(void);
void HLCD_voidSendNumber(u16 Copy_u32Number);


#endif
