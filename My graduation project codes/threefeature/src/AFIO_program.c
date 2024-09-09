 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: AFIO                                           */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_confg.h"

void MAFIO_VidSetEXTIConfig(u8 Copy_Line, u8 Copy_Portmap )
{
	u8 LOC_regindex =0;
	if(Copy_Line <= 3)
	{
		LOC_regindex =0;
	}
	else if(Copy_Line <= 7)
	{
		LOC_regindex =1;
		//as copy line is from 4 to 7 and copy line should be multply by 4 so we should subtract 4 from it
		//so Copy_Line should be 0 or 1 or 2 or 3 not more than this
		Copy_Line -=4 ;
	}
		else if(Copy_Line <= 11)
	{
		LOC_regindex =2;
		//as copy line is from 7 to 11 and copy line should be multply by 4 so we should subtract 8 from it
		Copy_Line -=8 ;
	}
	else if(Copy_Line <= 15)
	{
		LOC_regindex =3;
		Copy_Line -=12 ;
	}
	AFIO->EXTICR [LOC_regindex] &= ~((0b1111) << (Copy_Line*4));
	//(Copy_Portmap parameter) includes a binary value to determine which port we will use
	AFIO->EXTICR [LOC_regindex] |= ((Copy_Portmap) << (Copy_Line*4));
	
}
