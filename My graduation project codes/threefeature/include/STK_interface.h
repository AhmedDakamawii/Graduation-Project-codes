 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: STK                                           */ 
/****************************************************************/
#ifndef _STK_INTER_H
#define _STK_INTER_H

/* this function Apply Clock choice from configuration file  Disable SysTick interrupt Disable Systick               */
void MSTK_voidInit(void);
void MSTK_voidSetBusyWaitms( u32 Copy_u32Ticks );
void MSTK_voidSetBusyWaitus( u32 Copy_u32Ticks );
void MSTK_voidSetIntervalSinglems  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void MSTK_voidSetIntervalPeriodicms( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void MSTK_voidSetIntervalPeriodicus( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void MSTK_voidStopInterval(void);
u32  MSTK_u32GetElapsedTime(void);
u32  MSTK_u32GetRemainingTime(void);





#endif
