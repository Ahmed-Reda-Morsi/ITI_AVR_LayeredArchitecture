#ifndef LCD_INT_H
#define LCD_INT_H

void HLM35_voidInit(u8 Copy_u8ADC_Channel,void(*LM_PTR)(void));
void HLM35_voidGetTemperatureAsync(f32* Copy_ps8Temperature_Value);


#endif
