#include <util/delay.h>
#include <stdio.h>
#include "LCD_int.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LCD_cfg.h"
#include "LCD_prv.h"

// for configure the lcd mode in all functions.
static u8 Global_HLCDMODE;


// for automatically move to the next line or clear if lcd is full.
static s8 GLobal_CursorPositionX=-1;
static u8 GLobal_CursorPositionY=0;

void HLCD_voidCursorPosition(void)
{


		if((GLobal_CursorPositionY==0||GLobal_CursorPositionY==1)&&GLobal_CursorPositionX<=14)
		{
			GLobal_CursorPositionX++;
		}
		else if(GLobal_CursorPositionY==0&&GLobal_CursorPositionX==15)
		{
			GLobal_CursorPositionY=1;
			GLobal_CursorPositionX=0;

		}
		else if(GLobal_CursorPositionY==1&&GLobal_CursorPositionX==15)
		{
			GLobal_CursorPositionY=0;
			GLobal_CursorPositionX=0;
			HLCD_voidClearDisplay();

		}
		HLCD_voidGoToXY(GLobal_CursorPositionY,GLobal_CursorPositionX);
}

// enable read operation. for 4bit mode
void HLCD_void4BitModeEnable(void)
{
		MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_EN_PIN,PIN_HIGH);
		_delay_ms(2);
		MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_EN_PIN,PIN_LOW);
}

// enable read operation. for 8bit mode
void HLCD_void8BitModeEnable(void)
{
    MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,PIN_HIGH);
	_delay_ms(2);
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,PIN_LOW);
}

void HLCD_voidSendData(u8 Copy_u8Data)
{ 

	HLCD_voidCursorPosition();
	switch (Global_HLCDMODE) {
		case HLCD_8BIT_MODE:
				MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,PIN_HIGH);
			    MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,PIN_LOW);
			    MDIO_voidSetPortValue(HLCD_DATA_PORT,Copy_u8Data);
			    HLCD_void8BitModeEnable();

			break;
		case HLCD_4BIT_MODE:
				MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_RS_PIN,PIN_HIGH);
			    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_RW_PIN,PIN_LOW);

			    u8 Local_HLCD_data=Copy_u8Data;
			     /*right left data 4 time to send higher nibble*/
			    Local_HLCD_data>>=4;

			    u8 Local_HLCD_data4_value=Local_HLCD_data&0x01;
			    Local_HLCD_data>>=1;
			    u8 Local_HLCD_data5_value=Local_HLCD_data&0x01;
			    Local_HLCD_data>>=1;
			    u8 Local_HLCD_data6_value=Local_HLCD_data&0x01;
			    Local_HLCD_data>>=1;
			    u8 Local_HLCD_data7_value=Local_HLCD_data&0x01;

			    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA4_PIN,Local_HLCD_data4_value);
			    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA5_PIN,Local_HLCD_data5_value);
			    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA6_PIN,Local_HLCD_data6_value);
			    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA7_PIN,Local_HLCD_data7_value);
			    HLCD_void4BitModeEnable();

			     Local_HLCD_data=Copy_u8Data;
			     /*send low nibble of Data for LCD*/
				    Local_HLCD_data4_value=Local_HLCD_data&0x01;
				    Local_HLCD_data>>=1;
				    Local_HLCD_data5_value=Local_HLCD_data&0x01;
				    Local_HLCD_data>>=1;
				    Local_HLCD_data6_value=Local_HLCD_data&0x01;
				    Local_HLCD_data>>=1;
				    Local_HLCD_data7_value=Local_HLCD_data&0x01;
				 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA4_PIN,Local_HLCD_data4_value);
				 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA5_PIN,Local_HLCD_data5_value);
				 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA6_PIN,Local_HLCD_data6_value);
				 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA7_PIN,Local_HLCD_data7_value);
			    HLCD_void4BitModeEnable();

			break;
		default:
			break;
	}





}

void HLCD_voidSendCommand(u8 Copy_u8Command)
{
	switch (Global_HLCDMODE) {
			case HLCD_8BIT_MODE:
				 MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,PIN_LOW);
				 MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,PIN_LOW);
				 MDIO_voidSetPortValue(HLCD_DATA_PORT,Copy_u8Command);
				     // enable read operation.
				    HLCD_void8BitModeEnable();

				break;
			case HLCD_4BIT_MODE:
				MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_RS_PIN,PIN_LOW);
			    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_RW_PIN,PIN_LOW);

				   u8 Local_HLCD_Command=Copy_u8Command;
				     /*right left data 4 time to send higher nibble*/
				         Local_HLCD_Command>>=4;
				    u8 Local_HLCD_data4_value=Local_HLCD_Command&0x01;
				         Local_HLCD_Command>>=1;
				    u8 Local_HLCD_data5_value=Local_HLCD_Command&0x01;
				         Local_HLCD_Command>>=1;
				    u8 Local_HLCD_data6_value=Local_HLCD_Command&0x01;
				         Local_HLCD_Command>>=1;
				    u8 Local_HLCD_data7_value=Local_HLCD_Command&0x01;

				    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA4_PIN,Local_HLCD_data4_value);
				    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA5_PIN,Local_HLCD_data5_value);
				    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA6_PIN,Local_HLCD_data6_value);
				    MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA7_PIN,Local_HLCD_data7_value);
				    HLCD_void4BitModeEnable();

				     Local_HLCD_Command=Copy_u8Command;
				     /*send low nibble of Data for LCD*/
				     Local_HLCD_data4_value=Local_HLCD_Command&0x01;
				   	 Local_HLCD_Command>>=1;
				     Local_HLCD_data5_value=Local_HLCD_Command&0x01;
				   	 Local_HLCD_Command>>=1;
				   	 Local_HLCD_data6_value=Local_HLCD_Command&0x01;
				   	 Local_HLCD_Command>>=1;
				     Local_HLCD_data7_value=Local_HLCD_Command&0x01;
					 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA4_PIN,Local_HLCD_data4_value);
					 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA5_PIN,Local_HLCD_data5_value);
					 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA6_PIN,Local_HLCD_data6_value);
					 MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA7_PIN,Local_HLCD_data7_value);
				    HLCD_void4BitModeEnable();

				break;
			default:
				break;
		}

}

void HLCD_voidInit(u8 Copy_u8LCDMODE)
{
		Global_HLCDMODE=Copy_u8LCDMODE;

		switch (Copy_u8LCDMODE) {
			case HLCD_8BIT_MODE:
					MDIO_voidSetPortDirection(HLCD_DATA_PORT, PORT_OUT);
					MDIO_voidSetPinDirection(HLCD_CTRL_PORT,HLCD_RS_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_CTRL_PORT,HLCD_EN_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_CTRL_PORT,HLCD_RW_PIN,PIN_OUT);

					HLCD_voidSendCommand(HLCD_8BITMODE_FUNCSET_CMD);
					break;

			case HLCD_4BIT_MODE:
					MDIO_voidSetPinDirection(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA4_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA5_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA6_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA7_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_EN_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_RW_PIN,PIN_OUT);
					MDIO_voidSetPinDirection(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_RS_PIN,PIN_OUT);

					MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA4_PIN,0);
					MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA5_PIN,1);
					MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA6_PIN,0);
					MDIO_voidSetPinValue(HLCD_4BITMODE_DATA_CTRL_PORT,HLCD_4BITMODE_DATA7_PIN,0);
					HLCD_void4BitModeEnable();


					HLCD_voidSendCommand(HLCD_4BITMODE_FUNCSET_CMD);
				break;
			default:
				break;
		}

	_delay_ms(40);   // LCD initial  time.

	HLCD_voidSendCommand(HLCD_DOC_CMD);

	HLCD_voidSendCommand(HLCD_CLR_CMD);



}

void HLCD_voidSendString(const u8* Copy_pu8Data)
{
	for (u8 i = 0; Copy_pu8Data[i]!='\0'; i++) {
	     HLCD_voidSendData(Copy_pu8Data[i]);
	}
}


void HLCD_voidGoToXY(u8 Copy_u8YPostion,u8 Copy_u8XPostion)
{		u8 Local_Postion_CMD=0;
		if(Copy_u8XPostion>=HLCD_LINE1_BEGIN&&Copy_u8XPostion<=HLCD_LINE1_END)
		{
				if(Copy_u8YPostion==0)
				{
					Local_Postion_CMD=Copy_u8XPostion;
				}
				else if(Copy_u8YPostion==1)
				{
					Local_Postion_CMD=Copy_u8XPostion+HLCD_LINE2_BEGIN;
				}
		}
		Local_Postion_CMD+=HLCD_SET_DDRAM_ADDRESS_CMD;
		HLCD_voidSendCommand(Local_Postion_CMD);
}


void HLCD_voidSendSpectialChar(u8* Copy_pu8Specialchar,u8 Copy_u8PatternNumber, u8 Copy_u8YPostion,u8 Copy_u8XPostion)
{
		u8 Local_CGRAM_Adrress=Copy_u8PatternNumber*8;
		SET_BIT(Local_CGRAM_Adrress,6);
		HLCD_voidSendCommand(Local_CGRAM_Adrress);
		for(u8 i=0;i<8;i++)
		{
			HLCD_voidSendData(Copy_pu8Specialchar[i]);
		}
		HLCD_voidGoToXY(Copy_u8YPostion,Copy_u8XPostion);
		HLCD_voidSendData(Copy_u8PatternNumber);
}

void HLCD_voidClearDisplay(void)
{
	HLCD_voidSendCommand(HLCD_CLR_CMD);
	GLobal_CursorPositionX=-1;
    GLobal_CursorPositionY=0;

}

void HLCD_voidSendNumber(u16 Copy_u32Number)
{
		//HLCD_voidCursorPosition();
		u8 Number_AS_String[10];
		for(u8 i=0;i<10;i++)
		{
			Number_AS_String[i]='\0';
		}
		sprintf(Number_AS_String, "%d",Copy_u32Number);
		HLCD_voidSendString( Number_AS_String);
}

