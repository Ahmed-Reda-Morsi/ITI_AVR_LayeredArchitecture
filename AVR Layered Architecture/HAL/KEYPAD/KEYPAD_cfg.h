#ifndef 	KEYPAD_CFG_H
#define 	KEYPAD_CFG_H
#include "../../LIB/STD_TYPES.h"

#define KEYPAD_COLNUM_PORT         	   				 PORTC
#define KEYPAD_RAW_PORT          					 PORTC
#define KEYPAD_COLUMNS_NUMBER       				4
#define KEYPAD_RAW_NUMBER           				4

#define KEYPAD_RAW_PIN0      						0
#define KEYPAD_RAW_PIN1      						1
#define KEYPAD_RAW_PIN2      						2
#define KEYPAD_RAW_PIN3      						3

#define KEYPAD_COLUMN_PIN0  	 				    4
#define KEYPAD_COLUMN_PIN1   						5
#define KEYPAD_COLUMN_PIN2   						6
#define KEYPAD_COLUMN_PIN3   						7

#define BUTTON_NOT_PRESSED					0xff

#define KEYPAD_BUTTON_VALUE				{{1,2,3,'/'},{4,5,6,'*'},{7,8,9,'-'},{'c',0,'=','+'}}


#endif
