// best oreder for including.
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <math.h>

#include "../GIE/GIE_int.h"
#include "../TIMER0/TIMER_cfg.h"
#include "../TIMER0/TIMER_int.h"
#include "../TIMER0/TIMER_prv.h"

static u16 GLOBAL_TIMER0_PRESCALER=0;

static u32 GLOBAL_TIMER0_NO_OVERFLOW=0;
static u32 GLOBAL_TIMER0_PRELOAD=0;

static u8 GLOBAL_u8TickTime=0;
static u16 GLOBAL_u16TimeOverFlow=0;


void (*TIMER0_CALL_BACK_OverFlow)(void)=NULL_PTR;
void (*TIMER0_CALL_BACK_REQUIREDTIME)(void)=NULL_PTR;
void (*TIMER0_CALL_BACK_CompareMatch)(void)=NULL_PTR;

/*open cfg  header to configure TIMER0  */
void MTIMER0_voidInit(u8 Copy_u8Mode,u8 Copy_u8PreScaler)
{

 switch(Copy_u8Mode)
 {
	case TIMER0_NORMAL_MODE:
		CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
		CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
		break;

	case TIMER0_CTC_MODE:
		// set OC0 as OUTPUT for generate  wave.
		SET_BIT(OC0_DDR,OC0_PIN);
		CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
		SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
		break;

	case TIMER0_PWM_PHASECORRECT_MODE:
		// set OC0 as OUTPUT for generate  wave.
		SET_BIT(OC0_DDR,OC0_PIN);
		SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
		CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
		break;

	case TIMER0_FAST_PWM_MODE:
		// set OC0 as OUTPUT for generate  wave.
		SET_BIT(OC0_DDR,OC0_PIN);
		SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM00_BIT);
		SET_BIT(MTIMER0_TCCR0_REG, TCCR0_WGM01_BIT);
		break;

    default:
        break;

 }

 //________________________________| Clock Select MODE|_________________________

 switch(Copy_u8PreScaler)
 {
	 case TIMER0_CS_STOP:
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			break;

	 case TIMER0_CS_NOPRESCALLER:
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			break;

	 case TIMER0_CS_PRESCALLER_8:
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
		 GLOBAL_TIMER0_PRESCALER=8;
			break;

	 case TIMER0_CS_PRESCALLER_64:
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
		 GLOBAL_TIMER0_PRESCALER=64;
			break;

	 case TIMER0_CS_PRESCALLER_256:
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
		 GLOBAL_TIMER0_PRESCALER=256;
			break;

	 case TIMER0_CS_PRESCALLER_1024:
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
		 GLOBAL_TIMER0_PRESCALER=1024;
			break;

	 case TIMER0_CS_EXTERNAL_T0_PIN_FALLINGEDGE:
		 CLEAR_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			break;

	 case TIMER0_CS_EXTERNAL_T0_PIN_RISINGEDGE:
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS00_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS01_BIT);
		 SET_BIT(MTIMER0_TCCR0_REG, TCCR0_CS02_BIT);
			break;

	 default:
		 break;
 	 }

 	 /*calucate in init func. becuase they are depend of Prescaler*/
 	 //calucate Tick time in microsecond unit.
	 GLOBAL_u8TickTime=(GLOBAL_TIMER0_PRESCALER*1000000UL)/CPU_F;
	//overflow time for Timer0 in microsecond unit.
	  GLOBAL_u16TimeOverFlow=GLOBAL_u8TickTime*(pow(2,TIMER0_RESOLUTION));

}
//=======================================================
void MTIMER0_voidSetPreLoad(u16 Copy_u16PreLoad)
{
	MTIMER0_OCR0_REG=Copy_u16PreLoad;
}
//=======================================================
void MTIMER0_voidDelayInterrupt_MS(u32 Copy_u32Delay)
{
	// user delay in microsecond unit.
	Copy_u32Delay=Copy_u32Delay*1000UL;

	if (Copy_u32Delay>=GLOBAL_u16TimeOverFlow) {

		//number of overflow needed to required time.
		GLOBAL_TIMER0_NO_OVERFLOW=Copy_u32Delay/GLOBAL_u16TimeOverFlow;

		//remainder time needed to after number of overflow required time. in  microsecond unit.
		GLOBAL_TIMER0_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

	} else if(Copy_u32Delay<GLOBAL_u16TimeOverFlow)
	{
		//remainder required time. in  microsecond unit.
		GLOBAL_TIMER0_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

	}
	//Enable overflow interrupt for timer0
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
}

void MTIMER0_voidDelay_MS(u32 Copy_u32Delay)
{

	Copy_u32Delay=Copy_u32Delay*1000UL;  // for microsecond unit.

	//timer counter
	u32 Local_counter=0,Local_NO_OVERFLOW=0,Local_PRELOAD=0;

	if (Copy_u32Delay>=GLOBAL_u16TimeOverFlow) {

		//number of overflow needed to required time.
		Local_NO_OVERFLOW=Copy_u32Delay/GLOBAL_u16TimeOverFlow;

		while(Local_counter!=Local_NO_OVERFLOW)
		{
			 // Clear the overflow flag
			SET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT);
			while(GET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT)==0);

			Local_counter++;
		}
		//remainder time needed to after number of overflow required time. in  microsecond unit.
		Local_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));

		MTIMER0_TCNT0_REG=Local_PRELOAD;

		// Clear the overflow flag
		SET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT);
		while(GET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT)==0);

	} else if(Copy_u32Delay<GLOBAL_u16TimeOverFlow)
	{
		//remainder required time. in  microsecond unit.
		Local_PRELOAD=(Copy_u32Delay%GLOBAL_u16TimeOverFlow)*(pow(2,TIMER0_RESOLUTION));
		MTIMER0_TCNT0_REG=Local_PRELOAD;
		// Clear the overflow flag
		SET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT);
		while(GET_BIT(MTIMER_TIFR_REG,TIMER0_TOV0_BIT)==0);
	}


}
//======================================================================
 void MTIMER0_voidCompareOutputMode(u8 Copy_u8Mode,u8 Copy_u8COM)
 {

	 switch(Copy_u8Mode)
	 {
		case TIMER0_CTC_MODE:
			//-----------------------" Compare Output Mode with NO PWM " --------------------------
			switch (Copy_u8COM)
					{
					case	TIMER0_COM_NOPWM_OC0_PIN_DISCONNETED:
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					case	TIMER0_COM_NOPWM_OC0_PIN_TOGGLE:
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					case	TIMER0_COM_NOPWM_OC0_PIN_CLEAR:
							CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					case TIMER0_COM_NOPWM_OC0_PIN_SET:
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
							SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
							break;

					default:
						break;
				}
			break;


		//-----------------------" Compare Output Mode with PHASE CORRECT PWM " --------------------------
		case TIMER0_PWM_PHASECORRECT_MODE:
				switch (Copy_u8COM)
				{
				case TIMER0_COM_PHASECORRECTPWM_OC0_PIN_DISCONNETED:
					CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
					CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
					break;

				case TIMER0_COM_PHASECORRECTPWM_OC0_PIN_CLEAR_COUNTUP:
					CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
					SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
					 break;

				case TIMER0_COM_PHASECORRECTPWM_OC0_PIN_SET_COUNTUP:
					SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
					SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
					break;

			  default:
					break;
			}
		break;

		//-----------------------" Compare Output Mode with FAST PWM " --------------------------
		case TIMER0_FAST_PWM_MODE:
			switch (Copy_u8COM)
				{
					case TIMER0_COM_FASTPWM_OC0_PIN_DISCONNETED:
						    CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
						    CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
						    break;

					case TIMER0_COM_FASTPWM_OC0_PIN_CLEAR:
						    CLEAR_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
						    SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
						    break;

					case TIMER0_COM_FASTPWM_OC0_PIN_SET:
						    SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM00_BIT);
						    SET_BIT(MTIMER0_TCCR0_REG,TCCR0_COM01_BIT);
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

u8  MTIMER0_u8CheckOverFlow(void)
{
	u8 Local_u8OverFlowFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER0_TOV0_BIT)!=1);
	Local_u8OverFlowFlag=1;

	// to clear Timer/Counter0 Overflow Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER0_TOV0_BIT);
	 return Local_u8OverFlowFlag;
}
u8    MTIMER0_u8CheckCompareMatchMode(void)
{
	u8 Local_u8CompareMatchFlag=0;
	while(GET_BIT(MTIMER_TIFR_REG, TIMER0_OCF0_BIT)!=1);
		Local_u8CompareMatchFlag=1;

	// to clear Timer/Counter0 CompareMatch Flag
	SET_BIT(MTIMER_TIFR_REG, TIMER0_OCF0_BIT);
	 return Local_u8CompareMatchFlag;
}



void MTIMER0_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	MTIMER0_OCR0_REG=Copy_u8CompareMatchValue;
}
//=======================================================
void MTIMER0_voidPWMDutyCycle(u8 Copy_u8DutyCycle)
{
	if(Copy_u8DutyCycle<=100&&Copy_u8DutyCycle>0)
	{
		u8 local_CompareMatchValue=(Copy_u8DutyCycle*TIMER0_OverFlowValue)/TIMER0_MaxDutyCycle;

		MTIMER0_OCR0_REG=local_CompareMatchValue;
	}
}

//=======================================================
void MTIMER0_voidSetCallBack_OverFlow(void (*TIMER0_OF_ISR)(void))
{
	TIMER0_CALL_BACK_OverFlow=TIMER0_OF_ISR;
	//SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
}
void MTIMER0_voidSetCallBack_REQUIREDTIME(void (*TIMER0_OF_RT_ISR)(void))
{
	TIMER0_CALL_BACK_REQUIREDTIME=TIMER0_OF_RT_ISR;
	//SET_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
}
void MTIMER0_voidSetCallBack_CompareMatchValue(void (*TIMER0_CMV_ISR)(void))
{
	TIMER0_CALL_BACK_CompareMatch=TIMER0_CMV_ISR;
	SET_BIT(MTIMER_TIMSK_REG,TIMSK_OCIE0_BIT);
}

//TIMER0 COMP Timer/Counter0 Compare Match  Interrupt Vector
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if (TIMER0_CALL_BACK_CompareMatch!=NULL_PTR) {
		TIMER0_CALL_BACK_CompareMatch();
	}
}


// TIMER0 OVF Timer/Counter0 Overflow  Interrupt Vector
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u32 Local_Counter=0;
	 // to indicate that the no. overflow needed is done.
	static u8  NO_OVERFLOW_Done=0;

	// to indicate that the  preload needed is done.
	//static PreLoad_Done=0;

	if((Local_Counter<GLOBAL_TIMER0_NO_OVERFLOW) && NO_OVERFLOW_Done!=1 )
	{
		Local_Counter++;
	}
	else if((Local_Counter==GLOBAL_TIMER0_NO_OVERFLOW) && NO_OVERFLOW_Done!=1 )
	{
		if(GLOBAL_TIMER0_PRELOAD!=0)
		{
			//set preload
			MTIMER0_TCNT0_REG=GLOBAL_TIMER0_PRELOAD;
		}

		NO_OVERFLOW_Done=1;

	}
			//to guard executing ISR for required time
	else if(NO_OVERFLOW_Done==1&&(GLOBAL_TIMER0_NO_OVERFLOW!=0||GLOBAL_TIMER0_PRELOAD!=0))
	{
		if (TIMER0_CALL_BACK_REQUIREDTIME!=NULL_PTR)
		{
			//REQUIRED TIME time ISR Calling
			TIMER0_CALL_BACK_REQUIREDTIME();

			//disable overflow interrupt for timer0
			CLEAR_BIT(MTIMER_TIMSK_REG,TIMSK_TOIE0_BIT);
		}

		//reset the delay valiable for new time.
		Local_Counter=0;
		NO_OVERFLOW_Done=0;
	}

//normal overflow time ISR Calling
	if (TIMER0_CALL_BACK_OverFlow!=NULL_PTR)
	{
	TIMER0_CALL_BACK_OverFlow();
	}
}






