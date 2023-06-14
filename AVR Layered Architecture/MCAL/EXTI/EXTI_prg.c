// best oreder for including.
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../EXTI/EXTI_cfg.h"
#include "../EXTI/EXTI_int.h"
#include "../EXTI/EXTI_prv.h"

//#define _VECTOR(N) __vector_ ## N
//
//#define INT0_vect _VECTOR(1)  /* External Interrupt Request 0*/

// global pointers to functions for INT0 , INT1 and INT2 ISRs
void (*EXTI_0_CALL_BACK)(void)=NULL;
void (*EXTI_1_CALL_BACK)(void)=NULL;
void (*EXTI_2_CALL_BACK)(void)=NULL;
//=====================================
void MEXTI_voidGlobalInterruptEnable(void)
{
	SET_BIT(MEXTINT_SREG_REG, GEI_PIN);
}
void MEXTI_voidGlobalInterruptDisable(void)
{
	CLEAR_BIT(MEXTINT_SREG_REG, GEI_PIN);
}

//=================== set vectors for External Interrupt Requests of interrupt vector table (IVT) ==================================
/*
vector 1  of IVT for External Interrupt Request 0
 */
// disable Linker optimization process for vector_1
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	//call the ISR for INT0 implemented in the APP layer.
	EXTI_0_CALL_BACK();
}

/*
vector 2 of IVT for External Interrupt Request 1
 */
// disable Linker optimization process for vector_2
void __vector_2(void)  __attribute__((signal));
void __vector_2(void)
{
	EXTI_1_CALL_BACK();
}

/*
vector 3 of IVT for External Interrupt Request 2
 */
// disable Linker optimization process for vector_3
void __vector_3(void)  __attribute__((signal));
void __vector_3(void)
{
	EXTI_2_CALL_BACK();
}
//=================================================================================
void MEXTI_voidGlobalInterrupt(u8 Copy_u8GIState)
{
	switch (Copy_u8GIState)
	{
		case GLOBAL_INTERRUPT_ENABLE: SET_BIT(MEXTINT_SREG_REG, GEI_PIN); break;
		case GLOBAL_INTERRUPT_DISABLE: CLEAR_BIT(MEXTINT_SREG_REG, GEI_PIN); break;
		default:break;
	}
}

//==================================================================================================
void MEXTI_voidEnableInterrupt(u8 Copy_u8InterruptPIN, u8 Copy_u8InterruptSensingLevel)
{
	// enable global interrupt.
	SET_BIT(MEXTINT_SREG_REG, GEI_PIN);

	switch (Copy_u8InterruptPIN)
	{
	case INT0_PIN:
			switch (Copy_u8InterruptSensingLevel)
			{
			case LOW_LEVEL:
				//The low level of INT0 generates an interrupt request.
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;

			case ANY_LOGICAL_CHANGE:
				//Any logical change on INT0 generates an interrupt request
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;

			case FALLING_EDGE:
				//The falling edge of INT0 generates an interrupt request
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;

			case RISING_EDGE:
				// The rising edge of INT0 generates an interrupt request.
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC00_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT0_ISC01_PIN);
				break;
			}
		//enable external interrupt  INT0.
		SET_BIT(MEXTINT_GICR_REG, INT0_PIN);
		break;

	case INT1_PIN:
			switch (Copy_u8InterruptSensingLevel)
			{
			case LOW_LEVEL:
				//The low level of INT1 generates an interrupt request.
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;

			case ANY_LOGICAL_CHANGE:
				//Any logical change on INT1 generates an interrupt request
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;

			case FALLING_EDGE:
				//The falling edge of INT1 generates an interrupt request
				CLEAR_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;

			case RISING_EDGE:
				// The rising edge of INT1 generates an interrupt request.
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC10_PIN);
				SET_BIT(MEXTINT_MCUCR_REG, INT1_ISC11_PIN);
				break;
			}
		//enable external interrupt  INT1.
		SET_BIT(MEXTINT_GICR_REG, INT1_PIN);
		break;

	case INT2_PIN:
			switch (Copy_u8InterruptSensingLevel)
			{
			case FALLING_EDGE:
				//The falling edge of INT2 generates an interrupt request
				CLEAR_BIT(MEXTINT_MCUCSR_REG, INT2_ISC2_PIN);
				break;
			case RISING_EDGE:
				// The rising edge of INT2 generates an interrupt request.
				SET_BIT(MEXTINT_MCUCSR_REG, INT2_ISC2_PIN);
				break;
			}
	    //enable external interrupt  INT2.
		SET_BIT(MEXTINT_GICR_REG, INT2_PIN);
		break;
	default:
		break;
	}
}

void MEXTI_voidDisableInterrupt(u8 Copy_u8InterruptPIN)
{
	{
		switch (Copy_u8InterruptPIN)
		{
		case INT0_PIN:
			//disable external interrupt  INT0.
			CLEAR_BIT(MEXTINT_GICR_REG, INT0_PIN);
			break;
		case INT1_PIN:
			//disable external interrupt  INT0.
			CLEAR_BIT(MEXTINT_GICR_REG, INT1_PIN);
			break;
		case INT2_PIN:
			//disable external interrupt  INT0.
			CLEAR_BIT(MEXTINT_GICR_REG, INT2_PIN);
			break;
		default:
			break;
		}
	}
}


//================== Set call back functions(ISR) for external interrupts.=====================
void MEXTI_0_SET_CALL_BACK(void (*Copy_Pfunction_ISR_INT0)(void))
{
	EXTI_0_CALL_BACK = Copy_Pfunction_ISR_INT0;
}

void MEXTI_1_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT1)(void))
{
	EXTI_1_CALL_BACK=Copy_Pfunction_ISR_INT1;
}

void MEXTI_2_SET_CALL_BACK(void(*Copy_Pfunction_ISR_INT2)(void))
{
	EXTI_2_CALL_BACK=Copy_Pfunction_ISR_INT2;
}


