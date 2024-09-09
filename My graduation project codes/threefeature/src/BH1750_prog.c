/***************************************************************************/
/*  Author     :   Andrew Ashraf                                           */
/*  Date       :   13/9/2023                                               */
/*  Version    :   V01                                                     */
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "BH1750_private.h"
#include "BH1750_config.h"
#include "BH1750_interface.h"

#include "I2C_interface.h"



void BH1750_VoidInit (void)
{
    MI2C_voidMasterTransmit(MI2C_1,BH1750_POWER_ON,1,BH1750_ADDR_H);

	for(u16 LOC_u8Count=0 ; LOC_u8Count < 100 ; LOC_u8Count++)
    {
   		asm("NOP");
   	}
    MI2C_voidMasterTransmit(MI2C_1,BH1750_CONT_H_RES,1,BH1750_ADDR_H);

	for(u16 LOC_u8Count=0 ; LOC_u8Count < 500 ; LOC_u8Count++)
    {
   		asm("NOP");
   	}

    MI2C_voidMasterTransmit(MI2C_1,BH1750_POWER_ON,1,BH1750_ADDR_L);

	for(u16 LOC_u8Count=0 ; LOC_u8Count < 100 ; LOC_u8Count++)
    {
   		asm("NOP");
   	}
    MI2C_voidMasterTransmit(MI2C_1,BH1750_CONT_H_RES,1,BH1750_ADDR_L);

}

void BH1750_VoidReadLeft (u16* Copy_u16Lux)
{
	u8 Received_data[2];
	MI2C_voidMasterReceive(MI2C_1,Received_data,2,BH1750_ADDR_H);
	for(u32 LOC_u8Count=0 ; LOC_u8Count < 100 ; LOC_u8Count++)
	{
		asm("NOP");
	}
	u16 LOC_u16Data = ((Received_data[0]<<8)|(Received_data[1]))/1.2;
	*Copy_u16Lux = LOC_u16Data;

}
void BH1750_VoidReadRight (u16* Copy_u16Lux)
{
	u8 Received_data[2];
	MI2C_voidMasterReceive(MI2C_1,Received_data,2,BH1750_ADDR_L );
	for(u32 LOC_u8Count=0 ; LOC_u8Count < 100 ; LOC_u8Count++)
	{
		asm("NOP");
	}
	u16 LOC_u16Data = ((Received_data[0]<<8)|(Received_data[1]))/1.2;
	*Copy_u16Lux = LOC_u16Data;

}
