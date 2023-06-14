/*
 * TWI_prg.c
 *
 *  Created on: Apr 8, 2023
 *      Author: Ahmed Reda
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TWI_cfg.h"
#include "TWI_prv.h"
#include "TWI_int.h"

// TWI _ErrStatus 	enum for checking error.

void MTWI_voidMASTERInit(u8 Copy_u8SlaveAddress)
{
	/* make scL frequency= 400kbps */
		//1_ set TWI freq.
		TWI_TWBR_REG=TWI_PRESCALLER; //0x02
		//2_ Set Prescaller
		CLEAR_BIT(TWI_TWSR_REG,TWSR_TWPS1_BIT);
		CLEAR_BIT(TWI_TWSR_REG,TWSR_TWPS0_BIT);

	//3_ set Slave address
		TWI_TWAR_REG=(Copy_u8SlaveAddress<<1);

	//4_ enable ACK
	    SET_BIT(TWI_TWCR_REG,TWCR_TWIEA_BIT);

	//5_ Enable TWI
		SET_BIT(TWI_TWCR_REG,TWCR_TWEN_BIT);
}
//________________|SLAVE |__________________________
void MTWI_voidSLAVEInit(u8 Copy_u8SlaveAddress)
{
	//1_ set Slave address
		TWI_TWAR_REG=(Copy_u8SlaveAddress<<1);

	//2_ enable ACK
		SET_BIT(TWI_TWCR_REG,TWCR_TWIEA_BIT);

	//3_ Enable TWI
		SET_BIT(TWI_TWCR_REG,TWCR_TWEN_BIT);
}

//______________________| Start condition |______________________
void MTWI_voidSendStartCondition(void)
{
	//1_ set start condtion bit.
		SET_BIT(TWI_TWCR_REG,TWCR_TWSTA_BIT);

	//2_ clear interrupt flag. by set 1
		SET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT);

	//3_ wait till the interrupt flag is raised again.
		while(GET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT)==0);
	////4_ check the status bit and return err_state
}
//______________________| Repeated Start condition |______________________
void MTWI_voidSendRepeatedStartCondition(void)
{
	//1_ set start condtion bit.
		SET_BIT(TWI_TWCR_REG,TWCR_TWSTA_BIT);

	//2_ clear interrupt flag. by set 1
		SET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT);

	//3_wait till the interrupt flag is raised again.
		while(GET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT)==0);
	////4_ check the status bit and return err_state
}

//______________________| Send Slave Address with R/W operation|_________________
void MTWI_voidSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	//2_ Set Address in TWDR
	  /*The masking is made to make the first bit 0 for write request*/
	  TWI_TWDR_REG=(Copy_u8SlaveAddress<<1);

	//1_ Clear Start Condition Bit
	  CLEAR_BIT(TWI_TWCR_REG,TWCR_TWSTA_BIT);

	//4_ Clear Flag TWINT by set 1
	   SET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT);

	//4_wait for raising flag again.
	   while(GET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT)==0);
	////6_Check status bits and return err_state
}
void MTWI_voidSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	//2_ Set Address in TWDR
	   TWI_TWDR_REG=(Copy_u8SlaveAddress<<1);
	//3_Set TWDR Bit Zero by 1 for Read operation.
	   SET_BIT(TWI_TWDR_REG,TWDR_TWRWO_bit);

	 //1_ Clear Start Condition Bit
	  CLEAR_BIT(TWI_TWCR_REG,TWCR_TWSTA_BIT);

	//4_ Clear Flag TWINT by set 1
	   SET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT);
	//4_wait for raising flag again.
	   while(GET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT)==0);
	////6_Check status bits and return err_state
}

//________________________________|MASTER Write Data Byte|_____________________________
void MTWI_voidMASTERWriteDataByte(u8 Copy_u8DataByte)
{
	//1_ Set data in TWDR
		TWI_TWDR_REG=Copy_u8DataByte;

		/* clear start condition */
		 CLEAR_BIT(TWI_TWCR_REG,TWCR_TWSTA_BIT);

	//2_ Clear Flag TWINT by set 1
		SET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT);

	//3_wait for raising flag again.
		while(GET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT)==0);
	//// 4_ check err_state
}
//________________________________|MASTER Read Data Byte|_____________________________
void MTWI_voidMASTEReadDataByte(u8* Copy_pu8DataByte)
{
	/* clear start condition */
	 CLEAR_BIT(TWI_TWCR_REG,TWCR_TWSTA_BIT);

	//1_ Clear Flag TWINT by set 1 --> to start reading
		SET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT);
	//2_wait for raising flag again.
		while(GET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT)==0);
	//3_check Null pointer

	//3_check err_state
	if(Copy_pu8DataByte!=NULL)
	{

	 //4_Set TWDR Data in address that pointer point
	 *Copy_pu8DataByte=TWI_TWDR_REG;
	}

}

//______________________| stop condition |________________
void MTWI_voidStopCondtion(void)
{
	/* clear start condition */
	 CLEAR_BIT(TWI_TWCR_REG,TWCR_TWSTA_BIT);

	//1_ set stop condition.
		SET_BIT(TWI_TWCR_REG,TWCR_TWSTO_BIT);
	//2_Clear flag
	   SET_BIT(TWI_TWCR_REG,TWCR_TWINT_BIT);
}
