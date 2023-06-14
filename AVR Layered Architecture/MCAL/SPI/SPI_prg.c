
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../SPI/SPI_cfg.h"
#include "../SPI/SPI_int.h"
#include "../SPI/SPI_prv.h"


void MSPI_voidinit(void)
{

	SET_BIT(SPI_SPCR_REG,SPCP_DORD_PIN);  //SEND  LSB  FIRST

#if 	SPI_MODE== MASTER

	SET_BIT(SPI_SPCR_REG,SPCP_MSTR_PIN);  // MASTER MODE

	// PreScaller 128
	SET_BIT(SPI_SPCR_REG,1);
	SET_BIT(SPI_SPCR_REG,0);

	// clock polarity
	CLEAR_BIT(SPI_SPCR_REG,2);
	CLEAR_BIT(SPI_SPCR_REG,3);

#elif	SPI_MODE == SLAVE
	CLEAR_BIT(SPI_SPCR_REG,SPCP_MSTR_PIN);  // MASTER MODE

#endif


	SET_BIT(SPI_SPCR_REG,SPCP_SPE_PIN);  // SPI Enable

}
void MPSI_voidSendData(u8 Copy_u8Data)
{
	SPI_SPDR_REG=Copy_u8Data;
	while(GET_BIT(SPI_SPSR_REG,7)==0);
}
u8 MPSI_u8RecieveData(void)
{
	while(GET_BIT(SPI_SPSR_REG,7)==0);  // check
	return SPI_SPDR_REG;
}
