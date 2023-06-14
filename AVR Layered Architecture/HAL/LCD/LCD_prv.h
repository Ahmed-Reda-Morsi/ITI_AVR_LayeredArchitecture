#ifndef LCD_PRV_H
#define LCD_PRV_H
#include "../../LIB/STD_TYPES.h"


/*		LCD Function Set Command   initialization    (0b 0 0 1 1  1   0  0 0 )
 * 																									   N  F  X X
 * 	*/
#define  HLCD_8BITMODE_FUNCSET_CMD            									 0x38

#define  HLCD_4BITMODE_FUNCSET_CMD            									 0x2C

/* LCD Display on off control  Command  */
#define  HLCD_DOC_CMD                     									0x0f
/* LCD Clear Display  Command  */
#define  HLCD_CLR_CMD                     									0x01

/* LCD Set DDRAM Address  Command  */
#define  HLCD_SET_DDRAM_ADDRESS_CMD                     0x80

/* LCD Set CGRAM Address  Command  */
#define  HLCD_SET_CGRAM_ADDRESS_CMD                     0x40


/*LCD return home display*/
#define HLCD_RH_DISPLAY_CMD										0x02
#endif
