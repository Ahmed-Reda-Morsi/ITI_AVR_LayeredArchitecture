/*
 * @author  : Ahmed Reda Morsi.
 * @version : V 1.0
 */
#ifndef ADC_PRV_H
#define ADC_PRV_H

// These bits select the voltage reference for the ADC
//  Reference Selection Bits
#define ADCMUX_REFS0_PIN   6
#define ADCMUX_REFS1_PIN   7


/*
    the result is left adjusted at ADLAR Pin is 0  
---- ---- ---- ---- ---- ---- ADC9  ADC8    <-- ADCH  register
ADC7 ADC6 ADC5 ADC4 ADC3 ADC2 ADC1  ADC0    <-- ADCL  register        
--------------------------------------------------------------
    the result is Right adjusted at ADLAR Pin is 1  
ADC9 ADC8 ADC7 ADC6 ADC5 ADC4 ADC3  ADC2   <-- ADCH   register      
ADC1 ADC0 ---- ---- ---- ---- ---- ----    <-- ADCL   register
 */
//  ADC Left Adjust Result
#define ADCMUX_ADLAR_PIN   5

/*
these bits selects which combination of analog inputs are connected to the
ADC,also select the gain for the differential channels. See Table 84 for
details
 */
// Analog Channel and Gain Selection Bits
#define ADCMUX_MUX4_PIN    4
#define ADCMUX_MUX3_PIN    3
#define ADCMUX_MUX2_PIN    2
#define ADCMUX_MUX1_PIN    1
#define ADCMUX_MUX0_PIN    0

/*
Writing this bit to one enables the ADC. By writing it to zero, the ADC is turned off.
Turning the ADC off while a conversion is in progress, will terminate this conversion.
 */
// ADC Enable
#define ADCSRA_ADEN_PIN    7

/*
In Single Conversion mode, write this bit to one to start each conversion.
In Free Running Mode, write this bit to one to start the first conversion.
 */
// ADC Start Conversion
#define ADCSRA_ADSC_PIN    6

/*
When this bit is written to one, Auto Triggering of the ADC is enabled,
The ADC will start a conversion on a positive edge of the selected trigger signal.
 */
// ADC Auto Trigger Enable
#define ADCSRA_ADATE_PIN   5

/*
This bit is set when an ADC conversion completes and the Data Registers are updated.
ADIF is cleared by writing a logical one to the flag.
 */
// ADC Interrupt Flag
#define ADCSRA_ADIF_PIN    4

/*
When this bit is written to one and the I-bit in SREG is set,
the ADC Conversion Complete Interrupt is activated.
 */
// ADC Interrupt Enable
#define ADCSRA_ADIE_PIN    3

/*
These bits determine the division factor between
the XTAL frequency and the input clock to the ADC
 */
// ADC Prescaler Select Bits
#define ADCSRA_ADPS2_PIN   2
#define ADCSRA_ADPS1_PIN   1
#define ADCSRA_ADPS0_PIN   0

/* 
If ADATE in ADCSRA is written to one, the value of these bits selects which source will
trigger an ADC conversion. If ADATE is cleared, the ADTS2:0 settings will have no
effect.
 */
//ADC Auto Trigger Source
#define SFIOR_SDTS2_PIN    7
#define SFIOR_SDTS1_PIN    6
#define SFIOR_SDTS0_PIN    5

//ADC Multiplexer Selection Register
#define MADC_ADCMUX_REG         *((volatile u8 *)0x27)
//ADC Control and Status Register
#define MADC_ADCSRA_REG         *((volatile u8 *)0x26)
//The ADC Data Register higher part
#define MADC_ADCH_REG           *((volatile u8 *)0x25)
//The ADC Data Register lower part
#define MADC_ADCL_REG           *((volatile u8 *)0x24)
//Special FunctionIO Register
#define MADC_SFIOR_REG           *((volatile u8 *)0x50)
 // ADC control pins directions
#define  MADC_DDRA	     			*((volatile u8*)0x3A)



#endif
