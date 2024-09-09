 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: NVIC                                           */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_confg.h"

void MNVIC_VidEnableInterrupts (u8 Copy_InterruptNum)
{
	
	if ( Copy_InterruptNum <= 31)
	{
		NVIC_ISER0 = 1 << Copy_InterruptNum ;
	}
	else if ( Copy_InterruptNum <= 59)
	{
		Copy_InterruptNum -=32;
		NVIC_ISER1 = 1 << Copy_InterruptNum ;
	}
	
	
}

void MNVIC_VidDisableInterrupts (u8 Copy_InterruptNum)
{
	
	if ( Copy_InterruptNum <= 31)
	{
		NVIC_ICER0 = 1 << Copy_InterruptNum ;
	}
	else if ( Copy_InterruptNum <= 59)
	{
		Copy_InterruptNum -=32;
		NVIC_ICER1 = 1 << Copy_InterruptNum ;
	}
	
	
}

void MNVIC_VidSetPendingFlag (u8 Copy_InterruptNum)
{
	
	if ( Copy_InterruptNum <= 31)
	{
		NVIC_ISPR0 = 1 << Copy_InterruptNum ;
	}
	else if ( Copy_InterruptNum <= 59)
	{
		Copy_InterruptNum -=32;
		NVIC_ISPR1 = 1 << Copy_InterruptNum ;
	}
	
	
}

void MNVIC_VidClearPendingFlag (u8 Copy_InterruptNum)
{
	
	if ( Copy_InterruptNum <= 31)
	{
		NVIC_ICPR0 = 1 << Copy_InterruptNum ;
	}
	else if ( Copy_InterruptNum <= 59)
	{
		Copy_InterruptNum -=32;
		NVIC_ICPR1 = 1 << Copy_InterruptNum ;
	}
	
	
}

u8 MNVIC_U8GetActiveFlag (u8 Copy_InterruptNum)
{
	u8 LOC_ActiveFlag =0 ;
	if ( Copy_InterruptNum <= 31)
	{
		LOC_ActiveFlag = GET_BIT(NVIC_IABR0 , Copy_InterruptNum);
	}
	else if ( Copy_InterruptNum <= 59)
	{
		Copy_InterruptNum -=32;
		LOC_ActiveFlag = GET_BIT(NVIC_IABR1 , Copy_InterruptNum);
	}
	
	return LOC_ActiveFlag;
}
                     
					 //periphral with id  //group and sub priorty for prephiral  //num of bits for group and for sub
void MNVIC_VidSetPriorty (s8 Copy_ID , u8 Copy_GroupPriorty , u8 Copy_SubPriorty , u32 Copy_GroupNum )
{
	/*to put the group and sub priorty in thier place according to the num of bits reserved for group priorty 
	or for sub piriorty which we passed in the function we should use this equation*/
	                                                         //we get from this equ in double bracket 0 or 1 or 2 or 3
	u8 LOC_Priorty = Copy_SubPriorty | (Copy_GroupPriorty << ((Copy_GroupNum - 0x05FA0300)/256))  ; 
	
	/*for core interrupts*/
	
	
	/*for external interrupts*/
if (Copy_ID >=0)
{
	//as NVIC_IPR is a pointer with u8 not u32 so the Copy_ID is refrence for external inttrupt index
	NVIC_IPR[Copy_ID]=LOC_Priorty << 4 ;
}
//to understand which of the 4 MSB is for group and which is for sub group we should put Copy_GroupNum in register
	SCB_AIRCR = Copy_GroupNum ;
	
	
}
