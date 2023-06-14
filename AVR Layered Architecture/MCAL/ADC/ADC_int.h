/* 
* @author  : Ahmed Reda Morsi.
* @version : V 1.0
*/

#ifndef ADC_INT_H
#define ADC_INT_H

void MADC_voidStartConversionAsync(u8 Copy_u8ChannelID, void (*ptr)(void), u16* Copy_pu16Data);
void MADC_ReadASync(void);
void MADC_voidInit(void);
void MADC_voidStartConversionSync(u8 Copy_u8ADCChannel);
u16 MADC_ReadSync(void);

#endif
