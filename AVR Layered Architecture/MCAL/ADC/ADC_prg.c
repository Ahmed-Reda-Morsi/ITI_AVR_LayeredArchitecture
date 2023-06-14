// best oreder for including.
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../ADC/ADC_cfg.h"
#include "../ADC/ADC_int.h"
#include "../ADC/ADC_prv.h"

void (*ADC_CALL_BACK)(void) =NULL_PTR ;
u16*   Global_pu16Data = NULL ;

void MADC_voidInit(void)
{
//-------------------------------------------------------------------------------------------------------------------------------------------
    // 1. select voltage reference
#if ADC_VRS == ADC_VRS_ARFF // 0  0
	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_REFS0_PIN);
    CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_REFS1_PIN);

#elif ADC_VRS == ADC_VRS_AVCC //  0  1
        SET_BIT(MADC_ADCMUX_REG, ADCMUX_REFS0_PIN);
        CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_REFS1_PIN);

#elif ADC_VRS == ADC_VRS_INTERNAL //  1  1    // internal 2.56V
        SET_BIT(MADC_ADCMUX_REG, ADCMUX_REFS0_PIN);
        SET_BIT(MADC_ADCMUX_REG, ADCMUX_REFS1_PIN);

#else
#error "Wrong Voltage Reference Choice" ;
#endif
//-------------------------------------------------------------Result ADJUST -----------------------------------------------------------------------------------
#if ADC_ADJUST == ADC_LEFT_ADJUST // 0
        CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_ADLAR_PIN);

#elif ADC_ADJUST == ADC_RIGHT_ADJUST // 1
        SET_BIT(MADC_ADCMUX_REG, ADCMUX_ADLAR_PIN);
#else
#error "Wrong Result Adjust Choice" ;
#endif

//----------------------------------------------- auto trigger	-------------------------------------------------------
// close auto trigger
        ADC_AUTO_TRIGGER_DISABLE;



//-------------------------------------------------------  select prescaller --------------------------------------------------------------------------------------------

#if ADC_PRESCALLER == ADC_PRESCALLER_2 //  0 0 0
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS0_PIN);
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS1_PIN);
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS2_PIN);

#elif ADC_PRESCALLER == ADC_PRESCALLER_4   //   0  1  0
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS0_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS1_PIN);
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS2_PIN);

#elif ADC_PRESCALLER == ADC_PRESCALLER_8   // 0  1  1
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS0_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS1_PIN);
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS2_PIN);

#elif ADC_PRESCALLER == ADC_PRESCALLER_16  //  1 0 0
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS0_PIN);
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS1_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS2_PIN);

#elif ADC_PRESCALLER == ADC_PRESCALLER_32  //  1 0 1
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS0_PIN);
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS1_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS2_PIN);

#elif ADC_PRESCALLER == ADC_PRESCALLER_64  //  1 1 0
	CLEAR_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS0_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS1_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS2_PIN);

#elif ADC_PRESCALLER == ADC_PRESCALLER_128 //  1 1 1
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS0_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS1_PIN);
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADPS2_PIN);

#else
#error "Wrong Prescaller Choice" ;
#endif

    //4. ADC enable
	SET_BIT(MADC_ADCSRA_REG,ADCSRA_ADEN_PIN);
}
 //----------------------------------------------------------------- Sync -------------------------------------------------------------------------------------------
void MADC_voidStartConversionSync(u8 Copy_u8ADCChannel)
{
	// set ADC channel as input
	CLEAR_BIT(MADC_DDRA,Copy_u8ADCChannel);
    // select Analog Channel Signal End Input
	switch(Copy_u8ADCChannel)
    {
        case ADC_CHANNEL_SEI_0 :
        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        case ADC_CHANNEL_SEI_1 :
          	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        case ADC_CHANNEL_SEI_2 :
          	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
          	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        case ADC_CHANNEL_SEI_3 :
            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
          	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        case ADC_CHANNEL_SEI_4 :
            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        case ADC_CHANNEL_SEI_5 :
        	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        case ADC_CHANNEL_SEI_6 :
        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
        	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        case ADC_CHANNEL_SEI_7 :
        	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
            break;
        default:
            break;
	}
    //--------------------------------------------------------------------
    // start conversion
	SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADSC_PIN);
}

u16 MADC_ReadSync (void)
{
    u16 LocaL_u16Data=0;
    // stop until conversion is done
    // while (==0)  if = 1 conversion is done
    while (GET_BIT(MADC_ADCSRA_REG,ADCSRA_ADIF_PIN) == 0);

#if ADC_ADJUST == ADC_LEFT_ADJUST // 0
    LocaL_u16Data	|=   MADC_ADCL_REG;
    LocaL_u16Data |= (MADC_ADCH_REG << 8);


#elif ADC_ADJUST == ADC_RIGHT_ADJUST // 1
    LocaL_u16Data |=  (MADC_ADCL_REG >> 6);
    LocaL_u16Data |= (MADC_ADCH_REG << 2);
#endif

    // SET_BIT() // to clear the flag again
    SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADIF_PIN);

    return LocaL_u16Data;
}
//============================== Async ===========================================
void MADC_voidStartConversionAsync(u8 Copy_u8ChannelID , void (*CallBackFunc)(void) , u16 *const  Copy_pu16Data)
{
		// set ADC channel as input
		CLEAR_BIT(MADC_DDRA,Copy_u8ChannelID);
	  // select Analog Channel Signal End Input
		switch(Copy_u8ChannelID)
	    {
	        case ADC_CHANNEL_SEI_0 :
	        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        case ADC_CHANNEL_SEI_1 :
	          	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        case ADC_CHANNEL_SEI_2 :
	          	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	          	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        case ADC_CHANNEL_SEI_3 :
	            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	          	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        case ADC_CHANNEL_SEI_4 :
	            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        case ADC_CHANNEL_SEI_5 :
	        	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	            CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        case ADC_CHANNEL_SEI_6 :
	        	CLEAR_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	        	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        case ADC_CHANNEL_SEI_7 :
	        	SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX0_PIN);
	            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX1_PIN);
	            SET_BIT(MADC_ADCMUX_REG, ADCMUX_MUX2_PIN);
	            break;
	        default:
	            break;
		}

		Global_pu16Data=Copy_pu16Data;
		ADC_CALL_BACK=CallBackFunc;

}

//=================================================================================
void MADC_ReadASync()  //  convert and at complete make au interrupt.
{

			// start conversion
		SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADSC_PIN);
		/*ADC interrupt Enable*/
		SET_BIT(MADC_ADCSRA_REG, ADCSRA_ADIE_PIN);
}

// ADC Interrupt ISR
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
    if (Global_pu16Data != NULL)
    {
        *Global_pu16Data=0;
#if ADC_ADJUST == ADC_LEFT_ADJUST // 0
        *Global_pu16Data|=   MADC_ADCL_REG;
        *Global_pu16Data|= (MADC_ADCH_REG << 8);


#elif ADC_ADJUST == ADC_RIGHT_ADJUST // 1
        *Global_pu16Data |=  (MADC_ADCL_REG >> 6);
        *Global_pu16Data |= (MADC_ADCH_REG << 2);
#endif
    }

    if (ADC_CALL_BACK != NULL_PTR)
    {
        ADC_CALL_BACK();
    }
}
