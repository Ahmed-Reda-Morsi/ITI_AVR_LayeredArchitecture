#ifndef LCD_CFG_H
#define LCD_CFG_H

//#include "../../LIB/STD_TYPES.h"

#define 	HLCD_8BIT_MODE 									1
#define 	HLCD_4BIT_MODE 									0

/*for 8Bit Mode connection */
#define 	HLCD_DATA_PORT 									PORTA
#define 	HLCD_CTRL_PORT 									PORTB

#define 	HLCD_EN_PIN           	   		 						PIN0
#define 	HLCD_RW_PIN         	    							PIN1
#define 	HLCD_RS_PIN              								PIN2


/*for 4Bit Mode to connect data and control pins to one port*/
#define 	HLCD_4BITMODE_DATA_CTRL_PORT		PORTA
/*for 4Bit Mode*/
#define 	HLCD_4BITMODE_DATA4_PIN           	    PIN0
#define 	HLCD_4BITMODE_DATA5_PIN         	        PIN2
#define 	HLCD_4BITMODE_DATA6_PIN              		PIN4
#define 	HLCD_4BITMODE_DATA7_PIN           	    PIN6

#define 	HLCD_4BITMODE_EN_PIN           	   		 	PIN1
#define 	HLCD_4BITMODE_RW_PIN         	    		PIN3
#define 	HLCD_4BITMODE_RS_PIN              			PIN5



/* cursor position boundries */
#define HLCD_LINE1_BEGIN					0x00
#define HLCD_LINE1_END      				0x0F
#define HLCD_LINE2_BEGIN					0x40
#define HLCD_LINE2_END					0x4F


#endif
