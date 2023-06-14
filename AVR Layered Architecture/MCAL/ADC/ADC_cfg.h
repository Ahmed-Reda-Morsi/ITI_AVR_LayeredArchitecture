/* 
* @author  : Ahmed Reda Morsi.
* @version : V 1.0
*/
#ifndef ADC_CFG_H
#define ADC_CFG_H


/* 
*@  Note: there is 8 channel but One ADC periphral, meaning one channel active at a time.
*/

//=================== to control ADC configure============================
#define ADC_VRS         				ADC_VRS_AVCC
#define ADC_ADJUST     	 			ADC_RIGHT_ADJUST
#define ADC_PRESCALLER  			ADC_PRESCALLER_2


//#define ADC_CHANNEL     			ADC_CHANNEL_SEI_0


//=============================================================================
#define ADC_VRS_ARFF        		0     // 0 0
#define ADC_VRS_AVCC        		1     // 0 1
#define ADC_VRS_INTERNAL   	 	3     // 1 1   Internal 2.56V Voltage Reference

//============================================
//auto trigger mode
#define ADC_AUTO_TRIGGER_ENABLE 		SER_BIT(MADC_ADCSRA_REG,ADCSRA_ADATE_PIN)
#define ADC_AUTO_TRIGGER_DISABLE 		CLEAR_BIT(MADC_ADCSRA_REG,ADCSRA_ADATE_PIN)
//===========================================================
// Result Adjust
#define ADC_LEFT_ADJUST     		0   //ADLAR --> 0
#define ADC_RIGHT_ADJUST    	1   //ADLAR --> 1
//=========================================================
//ADC Prescaler Selections
#define ADC_PRESCALLER_2           			 2
#define ADC_PRESCALLER_4            		 4
#define ADC_PRESCALLER_8           			 8
#define ADC_PRESCALLER_16          	 	16
#define ADC_PRESCALLER_32           		32
#define ADC_PRESCALLER_64           		64
#define ADC_PRESCALLER_128          		128
//=====================================================
//ADC Auto Trigger Source Selections
#define ADC_TRIGGER_SOURCE_FRM             	 		0   //Free Running mode
#define ADC_TRIGGER_SOURCE_AC               			1   //Analog Comparator
#define ADC_TRIGGER_SOURCE_EXTI0            		2   //External Interrupt Request 0
#define ADC_TRIGGER_SOURCE_TIMER0_CM        	3   //Timer/Counter0 Compare Match
#define ADC_TRIGGER_SOURCE_TIMER0_OF       		4   //Timer/Counter0 Overflow
#define ADC_TRIGGER_SOURCE_TIMER_CM_B       	5   //Timer/Counter Compare Match B
#define ADC_TRIGGER_SOURCE_TIMER1_OF        	6   //Timer/Counter1 Overflow
#define ADC_TRIGGER_SOURCE_TIMER1_CE        	7   //Timer/Counter1 Capture Event


//ADC Input Channel and Gain Selections
/* Single Ended Input */
#define ADC_CHANNEL_SEI_0       0   
#define ADC_CHANNEL_SEI_1       1
#define ADC_CHANNEL_SEI_2       2
#define ADC_CHANNEL_SEI_3       3
#define ADC_CHANNEL_SEI_4       4
#define ADC_CHANNEL_SEI_5       5
#define ADC_CHANNEL_SEI_6       6   
#define ADC_CHANNEL_SEI_7       7



#endif
