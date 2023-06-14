// best oreder for including.
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER2_cfg.h"
#include "TIMER2_int.h"
#include "TIMER2_prv.h"

void (*TIMER2_CALL_BACK_OverFlow)(void)=NULL_PTR;
void (*TIMER2_CALL_BACK_CompareMatch)(void)=NULL_PTR;

/*open cfg  header to configure TIMER2  */
void MTIMER2_voidInit(u8 Copy_u8Mode,u8 Copy_u8PreScaler)
{

 switch(Copy_u8Mode)
 {
	case TIMER2_NORMAL_MODE:
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

	case TIMER2_CTC_MODE:
		// set OC2 as OUTPUT for generate  wave.
		SET_BIT(OC2_DDR,OC2_PIN);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

	case TIMER2_PWM_PHASECORRECT_MODE:
		// set OC2 as OUTPUT for generate  wave.
		SET_BIT(OC2_DDR,OC2_PIN);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

	case TIMER2_FAST_PWM_MODE:
		// set OC2 as OUTPUT for generate  wave.
		SET_BIT(OC2_DDR,OC2_PIN);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM20_BIT);
		SET_BIT(MTIMER2_TCCR2_REG, TCCR2_WGM21_BIT);
		break;

    default:
        break;

 }

 //________________________________| Clock Select MODE|_________________________

 switch(Copy_u8PreScaler)
 {
	 case TIMER2_CS_STOP:
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 case TIMER2_CS_NOPRESCALLER:
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 case TIMER2_CS_PRESCALLER_8:
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 case TIMER2_CS_PRESCALLER_32:
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 case TIMER2_CS_PRESCALLER_64:
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 case TIMER2_CS_PRESCALLER_128:
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 case TIMER2_CS_PRESCALLER_256:
		 CLEAR_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 case TIMER2_CS_PRESCALLER_1024:
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS20_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS21_BIT);
		 SET_BIT(MTIMER2_TCCR2_REG, TCCR2_CS22_BIT);
			break;

	 default:
		 break;
 	 }
}
//======================================================================
 void MTIMER2_voidCompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM)
 {

	 switch(Copy_u8Mode)
	 {
		case TIMER2_CTC_MODE:
			//-----------------------" Compare Output Mode with NO PWM " --------------------------
			switch (Copy_u8COM)
					{
					case	TIMER2_COM_NOPWM_OC2_PIN_DISCONNETED:
							CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
							CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
							break;

					case	TIMER2_COM_NOPWM_OC2_PIN_TOGGLE:
							SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
							CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
							break;

					case	TIMER2_COM_NOPWM_OC2_PIN_CLEAR:
							CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
							SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
							break;

					case TIMER2_COM_NOPWM_OC2_PIN_SET:
							SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
							SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
							break;

					default:
						break;
				}
			break;


		//-----------------------" Compare Output Mode with PHASE CORRECT PWM " --------------------------
		case TIMER2_PWM_PHASECORRECT_MODE:
				switch (Copy_u8COM)
				{
				case TIMER2_COM_PHASECORRECTPWM_OC2_PIN_DISCONNETED:
					CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
					CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
					break;

				case TIMER2_COM_PHASECORRECTPWM_OC2_PIN_CLEAR_COUNTUP:
					CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
					SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
					 break;

				case TIMER2_COM_PHASECORRECTPWM_OC2_PIN_SET_COUNTUP:
					SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
					SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
					break;

			  default:
					break;
			}
		break;

		//-----------------------" Compare Output Mode with FAST PWM " --------------------------
		case TIMER2_FAST_PWM_MODE:
			switch (Copy_u8COM)
				{
					case TIMER2_COM_FASTPWM_OC2_PIN_DISCONNETED:
						CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
						CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
						break;

					case TIMER2_COM_FASTPWM_OC2_PIN_CLEAR:
						CLEAR_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
						SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
						break;

					case TIMER2_COM_FASTPWM_OC2_PIN_SET:
						SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM20_BIT);
						SET_BIT(MTIMER2_TCCR2_REG,TCCR2_COM21_BIT);
						break;

					default:
						break;
				}
			break;

	    default:
	        break;
	 	}
 }

 //___________________________________________________________________________

u8  MTIMER2_u8CheckOverFlow(void)
{
	u8 Local_u8OverFlowFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER2_TOV2_BIT)!=1);
	Local_u8OverFlowFlag=1;

	// to clear Timer/Counter0 Overflow Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER2_TOV2_BIT);
	 return Local_u8OverFlowFlag;
}
u8    MTIMER2_u8CheckCompareMatchMode(void)
{
	u8 Local_u8CompareMatchFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER2_OCF2_BIT)!=1);
		Local_u8CompareMatchFlag=1;

	// to clear Timer/Counter0 CompareMatch Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER2_OCF2_BIT);
	 return Local_u8CompareMatchFlag;
}


void MTIMER2_voidSetPreLoad(u16 Copy_u16PreLoad)
{
	MTIMER2_OCR2_REG=Copy_u16PreLoad;
}
void MTIMER2_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	MTIMER2_OCR2_REG=Copy_u8CompareMatchValue;
}
//=======================================================
void MTIMER2_voidPWMDutyCycle(u8 Copy_u8DutyCycle)
{
	if(Copy_u8DutyCycle<=100&&Copy_u8DutyCycle>0)
	{
		u8 local_CompareMatchValue=(Copy_u8DutyCycle*TIMER2_OverFlowValue)/TIMER2_MaxDutyCycle;

		MTIMER2_OCR2_REG=local_CompareMatchValue;
	}
}
//=======================================================

void MTIMER2_voidSetCallBack_OverFlow(void (*TIMER2_OF_ISR)(void))
{
	TIMER2_CALL_BACK_OverFlow=TIMER2_OF_ISR;
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE2_BIT);
}
void MTIMER2_voidSetCallBack_CompareMatchValue(void (*TIMER2_CMV_ISR)(void))
{
	TIMER2_CALL_BACK_CompareMatch=TIMER2_CMV_ISR;
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_OCIE2_BIT);
}

//TIMER2 COMP Timer/Counter2 Compare Match  Interrupt Vector
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	if (TIMER2_CALL_BACK_CompareMatch!=NULL_PTR) {
		TIMER2_CALL_BACK_CompareMatch();
	}
}
// TIMER2 OVF Timer/Counter0 Overflow  Interrupt Vector
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	if (TIMER2_CALL_BACK_OverFlow!=NULL_PTR) {
	  TIMER2_CALL_BACK_OverFlow();
	}
}
