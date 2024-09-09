 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: STK                                           */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_confg.h"

//poiner to function for STK
 void (*STK_callback)(void);
//varible to deffrentiate between if the Interval is Single or Periodic
 u8 MSTK_U8ModeOfInterval;


void MSTK_voidInit(void)
{
/* this function Apply Clock choice from configuration file  Disable SysTick interrupt Disable Systick  */

// FREQUENCY AHB/8 and Disable SysTick interrupt Disable Systick 
//as frequency = 8Mhz and we choose AHB/8 ,tick time will equal (1/1Mhz)=1usec
#if   STK_FREQUENCY ==  STK_AHB_DIV8
MSTK->CTRL =0x00000000;
// FREQUENCY AHB and Disable SysTick interrupt Disable Systick 
#elif   STK_FREQUENCY == STK_AHB
MSTK->CTRL =0x00000004;
#endif
}


void MSTK_voidSetBusyWaitms( u32 Copy_u32Ticks )
{
/*this is a delay function which take value in usec if frequency = 8Mhz and we choose AHB/8*/
	/* Load ticks to load register */
	Copy_u32Ticks=Copy_u32Ticks*1000;
MSTK->LOAD = Copy_u32Ticks-1;
MSTK->VAL = 0 ;
/* enable STK Timer */
	SET_BIT(MSTK->CTRL, 0);
	//delay func
while (GET_BIT (MSTK->CTRL , 16) == 0)
	;  //DO NOTHING



	
}
void MSTK_voidSetBusyWaitus( u32 Copy_u32Ticks )
{
/*this is a delay function which take value in usec if frequency = 8Mhz and we choose AHB/8*/
	/* Load ticks to load register */
MSTK->LOAD = Copy_u32Ticks;
MSTK->VAL = 0 ;
/* enable STK Timer */
	SET_BIT(MSTK->CTRL, 0);
	//delay func
while (GET_BIT (MSTK->CTRL , 16) == 0)
	;  //DO NOTHING


}

void MSTK_voidSetIntervalSinglems  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{

	/* Disable Timer FOR IR */
		CLR_BIT(MSTK->CTRL,0);
		MSTK -> VAL = 0;
	//0 for single

	Copy_u32Ticks=Copy_u32Ticks*1000;
	MSTK->LOAD = Copy_u32Ticks-1;
	MSTK_U8ModeOfInterval=MSTK_SINGLE_INTERVAL;
	//get callback func
		STK_callback = Copy_ptr;
	//  enable SysTick Timer
	SET_BIT ( MSTK->CTRL , 0);

	// enable SysTick interrupt
	SET_BIT ( MSTK -> CTRL , 1);
 
	
}


void MSTK_voidSetIntervalPeriodicms( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	//1 for periodic
	Copy_u32Ticks=Copy_u32Ticks*1000;
	MSTK -> LOAD = Copy_u32Ticks-1 ;
	MSTK_U8ModeOfInterval=MSTK_PERIOD_INTERVAL;
	//get callback func
	STK_callback = Copy_ptr;
	//  enable SysTick Timer
	SET_BIT ( MSTK->CTRL , 0);

	// enable SysTick interrupt
	SET_BIT ( MSTK->CTRL , 1);
 
 

}

void MSTK_voidSetIntervalPeriodicus( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	//1 for periodic
	MSTK -> LOAD = Copy_u32Ticks-1 ;
	MSTK_U8ModeOfInterval=MSTK_PERIOD_INTERVAL;
	//get callback func
	STK_callback = Copy_ptr;
	//  enable SysTick Timer
	SET_BIT ( MSTK->CTRL , 0);

	// enable SysTick interrupt
	SET_BIT ( MSTK->CTRL , 1);
 
 

}
void MSTK_voidStopInterval(void)
{
	/* Stop STK */
	CLR_BIT ( MSTK->CTRL , 0);
	/* Disable STK Interrupt */
	CLR_BIT ( MSTK->CTRL , 1);
	MSTK -> LOAD = 0 ;
	MSTK -> VAL = 0 ;
}


u32  MSTK_u32GetElapsedTime(void)
{
	u32 Loc_ElapsedTime ;
	Loc_ElapsedTime = (MSTK -> LOAD) - (MSTK -> VAL) ;
	return Loc_ElapsedTime;
}


u32  MSTK_u32GetRemainingTime(void)
{
	u32 Loc_RemainingTime ;
	Loc_RemainingTime = MSTK -> VAL ;
	return Loc_RemainingTime;
}


/*ISR for STK*/
void SysTick_Handler(void)
{
	STK_callback();

		if (MSTK_U8ModeOfInterval ==  MSTK_SINGLE_INTERVAL) {
			/* Stop the counter*/
			CLR_BIT(MSTK->CTRL, 0);
			/*Assign the LOAD and VAL Registers by 0*/
			MSTK->LOAD = 0;
			MSTK->VAL = 0;
		}
		// Clear the Interrupt flag to start over again
		CLR_BIT(MSTK->CTRL, 16);

	}

