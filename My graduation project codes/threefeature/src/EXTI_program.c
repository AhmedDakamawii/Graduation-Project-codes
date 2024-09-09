 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: EXTI                                           */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_confg.h"

/*poiner to function in EXTI*/
static void (*EXTI0_CallBack) (void)=NULL;
static void (*EXTI1_CallBack) (void)=NULL;
static void (*EXTI2_CallBack) (void)=NULL;
/*we should check line and mode*/
//EXTI_VidInit is not an important function 
void MEXTI_VidInit()
{
	//choose line 
	#if EXTI_LINE == LINE0 
	SET_BIT (EXTI -> IMR , 0);
	#elif EXTI_LINE == LINE1 
	SET_BIT (EXTI -> IMR , 1);
	#elif EXTI_LINE == LINE2 
	SET_BIT (EXTI -> IMR , 2);
	#elif EXTI_LINE == LINE3 
	SET_BIT (EXTI -> IMR , 3);
	#elif EXTI_LINE == LINE4 
	SET_BIT (EXTI -> IMR , 4);
	#elif EXTI_LINE == LINE5 
	SET_BIT (EXTI -> IMR , 5);
	#elif EXTI_LINE == LINE6 
	SET_BIT (EXTI -> IMR , 6);
#endif
//if mode is raising
	#if EXTI_MODE == RASING 
	SET_BIT (EXTI -> RTSR , EXTI_LINE);
	//if mode is falling
	#elif EXTI_MODE == FALLING 
	SET_BIT (EXTI -> FTSR , EXTI_LINE);
	//if mode is ON CHANGE
	#elif EXTI_MODE == ON_CHANGE 
	SET_BIT (EXTI -> RTSR , EXTI_LINE);
	SET_BIT (EXTI -> FTSR , EXTI_LINE);
	#endif
}

void MEXTI_VidEnableEXTI(u8 Copy_Line)
{
	SET_BIT(EXTI -> IMR ,Copy_Line);	
}

void MEXTI_VidDisableEXTI(u8 Copy_Line)
{
	CLR_BIT(EXTI -> IMR ,Copy_Line);
	
}

void MEXTI_VidSoftwareTrigger(u8 Copy_Line)
{
	SET_BIT(EXTI -> SWIER ,Copy_Line);
	CLR_BIT(EXTI -> PR ,Copy_Line);

}
//this more important and do the functions that EXTI_VidInit and EXTI_VidEnableEXTI together can do
void MEXTI_VidSetSignalLatch(u8 Copy_Line ,u8 Copy_Mode)
{
switch (Copy_Mode)
{
	case RASING:	
	SET_BIT (EXTI -> RTSR , Copy_Line); 
	break;
case FALLING:	
SET_BIT (EXTI -> FTSR , Copy_Line);
	break;
	case ON_CHANGE:
	SET_BIT (EXTI -> RTSR , Copy_Line); 
	SET_BIT (EXTI -> FTSR , Copy_Line);
	break;
}
	SET_BIT(EXTI -> IMR ,Copy_Line);	
 

}
void MEXTI0_VidSetCallBack(void (*Ptr)(void))
{
	EXTI0_CallBack=Ptr;
}

void MEXTI1_VidSetCallBack(void (*Ptr)(void))
{
	EXTI1_CallBack=Ptr;
}

void MEXTI2_VidSetCallBack(void (*Ptr)(void))
{
	EXTI2_CallBack=Ptr;
}

void EXTI0_IRQHandler (void)
{
	EXTI0_CallBack();
	/*clear the pending bit*/
	SET_BIT (EXTI->PR , 0);
}

void EXTI1_IRQHandler (void)
{
	EXTI1_CallBack();
	/*clear the pending bit*/
	SET_BIT (EXTI->PR , 1);
}

void EXTI2_IRQHandler (void)
{
	EXTI2_CallBack();
	/*clear the pending bit*/
	SET_BIT (EXTI->PR , 2);
}

