

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_private.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"

static u8 MTIM2_Interval_Option;
static u8 MTIM3_Interval_Option;
static u8 MTIM4_Interval_Option;

// Global variables
volatile u32 start_time=0 ;
volatile u32 end_time=0 ;
volatile u32 pulse_duration=0 ;
volatile u32 distance=0 ;



#if MTIM1_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM1_voidInit(void)
{

	CLR_BIT( MTIM1->CR1 , 4 ); /* Set UPCounter*/
	SET_BIT( MTIM1->CR1 , 7 ); /* Set APRE*/

	SET_BIT(MTIM1->CR1 ,2); /* Set URS*/
	SET_BIT(MTIM1->EGR ,0 ); /* Set UG*/

#if MTIM1_PWM_CHANNEL1_STATUS   ==  ON
	/*channel1 is configured as output*/
	CLR_BIT(MTIM1->CCMR1 ,1 );
	CLR_BIT(MTIM1->CCMR1 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM1->CCMR1 ,6 );
	SET_BIT(MTIM1->CCMR1 ,5 );
	CLR_BIT(MTIM1->CCMR1 ,4 );
	SET_BIT(MTIM1->CCMR1 ,3 ); /* Set OC1PE*/


	CLR_BIT(MTIM1->CCER ,1 ); /* Set OC1 Active HIGH CC1P*/
	SET_BIT(MTIM1->CCER ,0 ); /* Set OC1EN CC1E*/

	SET_BIT(MTIM1->DIER ,1 ); /*  CC1 Interrupt Enabled */
	CLR_BIT(MTIM1->SR ,1 ); /* Clear CC1 Interrupt Flag */
#endif
#if MTIM1_PWM_CHANNEL2_STATUS   ==  ON
	/*channel2 is configured as output*/
	CLR_BIT(MTIM1->CCMR1 ,9 );
	CLR_BIT(MTIM1->CCMR1 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM1->CCMR1 ,14 );
	SET_BIT(MTIM1->CCMR1 ,13 );
	CLR_BIT(MTIM1->CCMR1 ,12 );
	SET_BIT(MTIM1->CCMR1 ,11 ); /* Set OC2PE*/


	CLR_BIT(MTIM1->CCER ,5 ); /* Set OC2 Active HIGH CC2P*/
	SET_BIT(MTIM1->CCER ,4 ); /* Set OC2EN CC2E*/

	SET_BIT(MTIM1->DIER ,2 ); /*  CC2 Interrupt Enabled */
	CLR_BIT(MTIM1->SR ,2 ); /* Clear CC2 Interrupt Flag */
#endif
#if MTIM1_PWM_CHANNEL3_STATUS   ==  ON
	/*channel3 is configured as output*/
	CLR_BIT(MTIM1->CCMR2 ,1 );
	CLR_BIT(MTIM1->CCMR2 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM1->CCMR2 ,6 );
	SET_BIT(MTIM1->CCMR2 ,5 );
	CLR_BIT(MTIM1->CCMR2 ,4 );
	SET_BIT(MTIM1->CCMR2 ,3 ); /* Set OC3PE*/


	CLR_BIT(MTIM1->CCER ,9 ); /* Set OC3 Active HIGH CC3P*/
	SET_BIT(MTIM1->CCER ,8 ); /* Set OC3EN CC3E*/

	SET_BIT(MTIM1->DIER ,3 ); /*  CC3 Interrupt Enabled */
	CLR_BIT(MTIM1->SR ,3 ); /* Clear CC3 Interrupt Flag */
#endif
#if MTIM1_PWM_CHANNEL4_STATUS   ==  ON
	/*channel4 is configured as output*/
	CLR_BIT(MTIM1->CCMR2 ,9 );
	CLR_BIT(MTIM1->CCMR2 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM1->CCMR2 ,14 );
	SET_BIT(MTIM1->CCMR2 ,13 );
	CLR_BIT(MTIM1->CCMR2 ,12 );
	SET_BIT(MTIM1->CCMR2 ,11 ); /* Set OC4PE*/


	CLR_BIT(MTIM1->CCER ,13 ); /* Set OC4 Active HIGH CC4P*/
	SET_BIT(MTIM1->CCER ,12 ); /* Set OC4EN CC4E*/

	SET_BIT(MTIM1->DIER ,4 ); /*  CC4 Interrupt Enabled */
	CLR_BIT(MTIM1->SR ,4 ); /* Clear CC4 Interrupt Flag */
#endif

	SET_BIT(MTIM1->DIER ,0 );
	CLR_BIT(MTIM1->SR ,0 );

	MTIM1->PSC = MTIM1_PRESCALER-1 ;

}



/*
* Description : Output PWM on OC1REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM1_voidSetPWM(u8 Copy_u8ChannelNo ,u16 Copy_u8Percentage  )
{

	MTIM1->ARR = (u16)(( F_CPU / MTIM1_PRESCALER )/ (MTIM1_PWM_FREQ)) ;

	MTIM1->CCR[Copy_u8ChannelNo] =(u16) (Copy_u8Percentage) ;

	SET_BIT(MTIM1->BDTR,15); /* SET MOE */
	SET_BIT(MTIM1->CR1 ,0 ); /* Counter Enable*/

}
/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM1_voidStopTimer( void )
{
	MTIM1->ARR = 0 ;
	CLR_BIT(MTIM1->CR1 ,0 ); /* Counter Disable*/
	CLR_BIT(MTIM1->DIER ,0 ); /* Update interrupt Disabled */
}


#endif





#if MTIM2_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM2_voidInit(void)
{

	CLR_BIT( MTIM2->CR1 , 4 ); /* Set UPCounter*/
	SET_BIT( MTIM2->CR1 , 7 ); /* Set APRE*/

#if MTIM2_MODE        ==     PWM_MODE
	SET_BIT(MTIM2->CR1 ,2); /* Set URS*/
	SET_BIT(MTIM2->EGR ,0 ); /* Set UG*/

#if MTIM2_PWM_CHANNEL1_STATUS   ==  ON
	/*channel1 is configured as output*/
	CLR_BIT(MTIM2->CCMR1 ,1 );
	CLR_BIT(MTIM2->CCMR1 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM2->CCMR1 ,6 );
	SET_BIT(MTIM2->CCMR1 ,5 );
	CLR_BIT(MTIM2->CCMR1 ,4 );
	SET_BIT(MTIM2->CCMR1 ,3 ); /* Set OC1PE*/


	CLR_BIT(MTIM2->CCER ,1 ); /* Set OC1 Active HIGH CC1P*/
	SET_BIT(MTIM2->CCER ,0 ); /* Set OC1EN CC1E*/

	SET_BIT(MTIM2->DIER ,1 ); /*  CC1 Interrupt Enabled */
	CLR_BIT(MTIM2->SR ,1 ); /* Clear CC1 Interrupt Flag */
#endif
#if MTIM2_PWM_CHANNEL2_STATUS   ==  ON
	/*channel2 is configured as output*/
	CLR_BIT(MTIM2->CCMR1 ,9 );
	CLR_BIT(MTIM2->CCMR1 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM2->CCMR1 ,14 );
	SET_BIT(MTIM2->CCMR1 ,13 );
	CLR_BIT(MTIM2->CCMR1 ,12 );
	SET_BIT(MTIM2->CCMR1 ,11 ); /* Set OC2PE*/


	CLR_BIT(MTIM2->CCER ,5 ); /* Set OC2 Active HIGH CC2P*/
	SET_BIT(MTIM2->CCER ,4 ); /* Set OC2EN CC2E*/

	SET_BIT(MTIM2->DIER ,2 ); /*  CC2 Interrupt Enabled */
	CLR_BIT(MTIM2->SR ,2 ); /* Clear CC2 Interrupt Flag */
#endif
#if MTIM2_PWM_CHANNEL3_STATUS   ==  ON
	/*channel3 is configured as output*/
	CLR_BIT(MTIM2->CCMR2 ,1 );
	CLR_BIT(MTIM2->CCMR2 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM2->CCMR2 ,6 );
	SET_BIT(MTIM2->CCMR2 ,5 );
	CLR_BIT(MTIM2->CCMR2 ,4 );
	SET_BIT(MTIM2->CCMR2 ,3 ); /* Set OC3PE*/


	CLR_BIT(MTIM2->CCER ,9 ); /* Set OC3 Active HIGH CC3P*/
	SET_BIT(MTIM2->CCER ,8 ); /* Set OC3EN CC3E*/

	SET_BIT(MTIM2->DIER ,3 ); /*  CC3 Interrupt Enabled */
	CLR_BIT(MTIM2->SR ,3 ); /* Clear CC3 Interrupt Flag */
#endif
#if MTIM2_PWM_CHANNEL4_STATUS   ==  ON
	/*channel4 is configured as output*/
	CLR_BIT(MTIM2->CCMR2 ,9 );
	CLR_BIT(MTIM2->CCMR2 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM2->CCMR2 ,14 );
	SET_BIT(MTIM2->CCMR2 ,13 );
	CLR_BIT(MTIM2->CCMR2 ,12 );
	SET_BIT(MTIM2->CCMR2 ,11 ); /* Set OC4PE*/


	CLR_BIT(MTIM2->CCER ,13 ); /* Set OC4 Active HIGH CC4P*/
	SET_BIT(MTIM2->CCER ,12 ); /* Set OC4EN CC4E*/

	SET_BIT(MTIM2->DIER ,4 ); /*  CC4 Interrupt Enabled */
	CLR_BIT(MTIM2->SR ,4 ); /* Clear CC4 Interrupt Flag */
#endif
	
	SET_BIT(MTIM2->DIER ,0 );
	CLR_BIT(MTIM2->SR ,0 );
#endif

	MTIM2->PSC = MTIM2_PRESCALER-1 ;

}



#if MTIM2_MODE        ==     PWM_MODE
/*
* Description : Output PWM on OC2REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM2_voidSetPWM(u8 Copy_u8ChannelNo ,u8 Copy_u8Percentage  )
{

	MTIM2->ARR = (u16)(( F_CPU / MTIM2_PRESCALER )/ (MTIM2_PWM_FREQ)) ;

	MTIM2->CCR[Copy_u8ChannelNo] =(u16) ((Copy_u8Percentage * MTIM2->ARR)/100);

	SET_BIT(MTIM2->CR1 ,0 ); /* Counter Enable*/

}
#endif

#if MTIM2_MODE        ==     OUTPUT_CAPTURE_MODE

/*
 * Description : Delay System By Waiting For Timer
 * Arguments   : Ticks
 * return      : None
*/
void MTIM2_voidSetBusyWaitus(u32 Copy_u32Ticks )
{
	f32 LOC_f32TickTime = ((f32)(MTIM2->PSC+1) / F_CPU );
	f32 LOC_f32OneCycleTick = LOC_f32TickTime * REG_MAX * 1000000;
	f32 LOC_f32CyclesNo = Copy_u32Ticks / LOC_f32OneCycleTick;
	CLR_BIT(MTIM2->DIER ,0 ); /* Update interrupt disabled */
	while(  LOC_f32CyclesNo > 0.0)
	{
		if(LOC_f32CyclesNo < 1.0)
		{
			MTIM2->ARR =(u16) (LOC_f32CyclesNo * REG_MAX );
			LOC_f32CyclesNo = 0;
		}
		else
		{
			MTIM2->ARR = REG_MAX ;
			LOC_f32CyclesNo--;
		}
		SET_BIT(MTIM2->CR1 ,0 ); /* Counter Enable*/
		while ( GET_BIT( MTIM2->SR , 0 ) == 0); /* Wait until Update occurs (Timer Finish) */
		CLR_BIT(MTIM2->CR1 ,0 ); /* Counter Disable*/
		CLR_BIT( MTIM2->SR , 0 );
	}
	MTIM2->ARR = 0 ;
}
/*
 * Description : Set Single Period of Time (One Time Count) Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM2_voidSetIntervalSingle(u16 Copy_u16Ticks , void(*ptr)(void) )
{
	MTIM2->ARR = Copy_u16Ticks ;
	SET_BIT(MTIM2->CR1 ,0 ); /* Counter Enable*/
	SET_BIT(MTIM2->DIER ,0 ); /* Update interrupt Enabled */
	TIM_CALLBACK[0] = ptr;
	MTIM2_Interval_Option = MTIM_Single_Interval;
}
/*
 * Description : Set Period of Time every time Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM2_voidSetIntervalPeriodic(u16 Copy_u16Ticks , void(*ptr)(void) )
{
	MTIM2->ARR = Copy_u16Ticks ;
	SET_BIT(MTIM2->CR1 ,0 ); /* Counter Enable*/
	SET_BIT(MTIM2->DIER ,0 ); /* Update interrupt Enabled */
	TIM_CALLBACK[0] = ptr;
	MTIM2_Interval_Option = MTIM_Periodic_Interval;
}
#endif
/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM2_voidStopTimer( void )
{
	MTIM2->ARR = 0 ;
	CLR_BIT(MTIM2->CR1 ,0 ); /* Counter Disable*/
	CLR_BIT(MTIM2->DIER ,0 ); /* Update interrupt Disabled */
}


#endif



#if MTIM3_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM3_voidInit(void)
{

	CLR_BIT( MTIM3->CR1 , 4 ); /* Set UPCounter*/
	SET_BIT( MTIM3->CR1 , 7 ); /* Set APRE*/

#if MTIM3_MODE        ==     PWM_MODE
	SET_BIT(MTIM3->CR1 ,2); /* Set URS*/
	SET_BIT(MTIM3->EGR ,0 ); /* Set UG*/

#if MTIM3_PWM_CHANNEL1_STATUS   ==  ON
	/*channel1 is configured as output*/
	CLR_BIT(MTIM3->CCMR1 ,1 );
	CLR_BIT(MTIM3->CCMR1 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM3->CCMR1 ,6 );
	SET_BIT(MTIM3->CCMR1 ,5 );
	CLR_BIT(MTIM3->CCMR1 ,4 );
	SET_BIT(MTIM3->CCMR1 ,3 ); /* Set OC1PE*/


	CLR_BIT(MTIM3->CCER ,1 ); /* Set OC1 Active HIGH CC1P*/
	SET_BIT(MTIM3->CCER ,0 ); /* Set OC1EN CC1E*/

	SET_BIT(MTIM3->DIER ,1 ); /*  CC1 Interrupt Enabled */
	CLR_BIT(MTIM3->SR ,1 ); /* Clear CC1 Interrupt Flag */
#endif
#if MTIM3_PWM_CHANNEL2_STATUS   ==  ON
	/*channel2 is configured as output*/
	CLR_BIT(MTIM3->CCMR1 ,9 );
	CLR_BIT(MTIM3->CCMR1 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM3->CCMR1 ,14 );
	SET_BIT(MTIM3->CCMR1 ,13 );
	CLR_BIT(MTIM3->CCMR1 ,12 );
	SET_BIT(MTIM3->CCMR1 ,11 ); /* Set OC2PE*/


	CLR_BIT(MTIM3->CCER ,5 ); /* Set OC2 Active HIGH CC2P*/
	SET_BIT(MTIM3->CCER ,4 ); /* Set OC2EN CC2E*/

	SET_BIT(MTIM3->DIER ,2 ); /*  CC2 Interrupt Enabled */
	CLR_BIT(MTIM3->SR ,2 ); /* Clear CC2 Interrupt Flag */
#endif
#if MTIM3_PWM_CHANNEL3_STATUS   ==  ON
	/*channel3 is configured as output*/
	CLR_BIT(MTIM3->CCMR2 ,1 );
	CLR_BIT(MTIM3->CCMR2 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM3->CCMR2 ,6 );
	SET_BIT(MTIM3->CCMR2 ,5 );
	CLR_BIT(MTIM3->CCMR2 ,4 );
	SET_BIT(MTIM3->CCMR2 ,3 ); /* Set OC3PE*/


	CLR_BIT(MTIM3->CCER ,9 ); /* Set OC3 Active HIGH CC3P*/
	SET_BIT(MTIM3->CCER ,8 ); /* Set OC3EN CC3E*/

	SET_BIT(MTIM3->DIER ,3 ); /*  CC3 Interrupt Enabled */
	CLR_BIT(MTIM3->SR ,3 ); /* Clear CC3 Interrupt Flag */
#endif
#if MTIM3_PWM_CHANNEL4_STATUS   ==  ON
	/*channel4 is configured as output*/
	CLR_BIT(MTIM3->CCMR2 ,9 );
	CLR_BIT(MTIM3->CCMR2 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM3->CCMR2 ,14 );
	SET_BIT(MTIM3->CCMR2 ,13 );
	CLR_BIT(MTIM3->CCMR2 ,12 );
	SET_BIT(MTIM3->CCMR2 ,11 ); /* Set OC4PE*/


	CLR_BIT(MTIM3->CCER ,13 ); /* Set OC4 Active HIGH CC4P*/
	SET_BIT(MTIM3->CCER ,12 ); /* Set OC4EN CC4E*/

	SET_BIT(MTIM3->DIER ,4 ); /*  CC4 Interrupt Enabled */
	CLR_BIT(MTIM3->SR ,4 ); /* Clear CC4 Interrupt Flag */
#endif

	SET_BIT(MTIM3->DIER ,0 );
	CLR_BIT(MTIM3->SR ,0 );
#endif

	MTIM3->PSC = MTIM3_PRESCALER-1 ;

}



#if MTIM3_MODE        ==     PWM_MODE
/*
* Description : Output PWM on OC3REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM3_voidSetPWM(u8 Copy_u8ChannelNo ,u8 Copy_u8Percentage  )
{

	MTIM3->ARR = (u16)(( F_CPU / MTIM3_PRESCALER )/ (MTIM3_PWM_FREQ)) ;

	MTIM3->CCR[Copy_u8ChannelNo] =(u16) ((Copy_u8Percentage * MTIM3->ARR)/100);

	SET_BIT(MTIM3->CR1 ,0 ); /* Counter Enable*/

}
#endif

#if MTIM3_MODE        ==     OUTPUT_CAPTURE_MODE

/*
 * Description : Delay System By Waiting For Timer
 * Arguments   : Ticks
 * return      : None
*/
void MTIM3_voidSetBusyWaitus(u32 Copy_u32Ticks )
{
	f32 LOC_f32TickTime = ((f32)(MTIM3->PSC+1) / F_CPU );
	f32 LOC_f32OneCycleTick = LOC_f32TickTime * REG_MAX * 1000000;
	f32 LOC_f32CyclesNo = Copy_u32Ticks / LOC_f32OneCycleTick;
	CLR_BIT(MTIM3->DIER ,0 ); /* Update interrupt disabled */
	while(  LOC_f32CyclesNo > 0.0)
	{
		if(LOC_f32CyclesNo < 1.0)
		{
			MTIM3->ARR =(u16) (LOC_f32CyclesNo * REG_MAX );
			LOC_f32CyclesNo = 0;
		}
		else
		{
			MTIM3->ARR = REG_MAX ;
			LOC_f32CyclesNo--;
		}
		SET_BIT(MTIM3->CR1 ,0 ); /* Counter Enable*/
		while ( GET_BIT( MTIM3->SR , 0 ) == 0); /* Wait until Update occurs (Timer Finish) */
		CLR_BIT(MTIM3->CR1 ,0 ); /* Counter Disable*/
		CLR_BIT( MTIM3->SR , 0 );
	}
	MTIM3->ARR = 0 ;
}
/*
 * Description : Set Single Period of Time (One Time Count) Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM3_voidSetIntervalSingle(u16 Copy_u16Ticks , void(*ptr)(void) )
{
	MTIM3->ARR = Copy_u16Ticks ;
	SET_BIT(MTIM3->CR1 ,0 ); /* Counter Enable*/
	SET_BIT(MTIM3->DIER ,0 ); /* Update interrupt Enabled */
	TIM_CALLBACK[1] = ptr;
	MTIM3_Interval_Option = MTIM_Single_Interval;
}
/*
 * Description : Set Period of Time every time Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM3_voidSetIntervalPeriodic(u16 Copy_u16Ticks , void(*ptr)(void) )
{
	MTIM3->ARR = Copy_u16Ticks ;
	SET_BIT(MTIM3->CR1 ,0 ); /* Counter Enable*/
	SET_BIT(MTIM3->DIER ,0 ); /* Update interrupt Enabled */
	TIM_CALLBACK[1] = ptr;
	MTIM3_Interval_Option = MTIM_Periodic_Interval;
}
#endif

/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM3_voidStopTimer( void )
{
	MTIM3->ARR = 0 ;
	CLR_BIT(MTIM3->CR1 ,0 ); /* Counter Disable*/
	CLR_BIT(MTIM3->DIER ,0 ); /* Update interrupt Disabled */
}




#endif



#if MTIM4_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM4_voidInit(void)
{

	CLR_BIT( MTIM4->CR1 , 4 ); /* Set UPCounter*/
	SET_BIT( MTIM4->CR1 , 7 ); /* Set APRE*/

#if MTIM4_MODE        ==     PWM_MODE
	SET_BIT(MTIM4->CR1 ,2); /* Set URS*/
	SET_BIT(MTIM4->EGR ,0 ); /* Set UG*/

#if MTIM4_PWM_CHANNEL1_STATUS   ==  ON
	/*channel1 is configured as output*/
	CLR_BIT(MTIM4->CCMR1 ,1 );
	CLR_BIT(MTIM4->CCMR1 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM4->CCMR1 ,6 );
	SET_BIT(MTIM4->CCMR1 ,5 );
	CLR_BIT(MTIM4->CCMR1 ,4 );
	SET_BIT(MTIM4->CCMR1 ,3 ); /* Set OC1PE*/


	CLR_BIT(MTIM4->CCER ,1 ); /* Set OC1 Active HIGH CC1P*/
	SET_BIT(MTIM4->CCER ,0 ); /* Set OC1EN CC1E*/

	SET_BIT(MTIM4->DIER ,1 ); /*  CC1 Interrupt Enabled */
	CLR_BIT(MTIM4->SR ,1 ); /* Clear CC1 Interrupt Flag */
#endif
#if MTIM4_PWM_CHANNEL2_STATUS   ==  ON
	/*channel2 is configured as output*/
	CLR_BIT(MTIM4->CCMR1 ,9 );
	CLR_BIT(MTIM4->CCMR1 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM4->CCMR1 ,14 );
	SET_BIT(MTIM4->CCMR1 ,13 );
	CLR_BIT(MTIM4->CCMR1 ,12 );
	SET_BIT(MTIM4->CCMR1 ,11 ); /* Set OC2PE*/


	CLR_BIT(MTIM4->CCER ,5 ); /* Set OC2 Active HIGH CC2P*/
	SET_BIT(MTIM4->CCER ,4 ); /* Set OC2EN CC2E*/

	SET_BIT(MTIM4->DIER ,2 ); /*  CC2 Interrupt Enabled */
	CLR_BIT(MTIM4->SR ,2 ); /* Clear CC2 Interrupt Flag */
#endif
#if MTIM4_PWM_CHANNEL3_STATUS   ==  ON
	/*channel3 is configured as output*/
	CLR_BIT(MTIM4->CCMR2 ,1 );
	CLR_BIT(MTIM4->CCMR2 ,0 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM4->CCMR2 ,6 );
	SET_BIT(MTIM4->CCMR2 ,5 );
	CLR_BIT(MTIM4->CCMR2 ,4 );
	SET_BIT(MTIM4->CCMR2 ,3 ); /* Set OC3PE*/


	CLR_BIT(MTIM4->CCER ,9 ); /* Set OC3 Active HIGH CC3P*/
	SET_BIT(MTIM4->CCER ,8 ); /* Set OC3EN CC3E*/

	SET_BIT(MTIM4->DIER ,3 ); /*  CC3 Interrupt Enabled */
	CLR_BIT(MTIM4->SR ,3 ); /* Clear CC3 Interrupt Flag */
#endif
#if MTIM4_PWM_CHANNEL4_STATUS   ==  ON
	/*channel4 is configured as output*/
	CLR_BIT(MTIM4->CCMR2 ,9 );
	CLR_BIT(MTIM4->CCMR2 ,8 );

	/* Select PWM Mode1 */
	SET_BIT(MTIM4->CCMR2 ,14 );
	SET_BIT(MTIM4->CCMR2 ,13 );
	CLR_BIT(MTIM4->CCMR2 ,12 );
	SET_BIT(MTIM4->CCMR2 ,11 ); /* Set OC4PE*/


	CLR_BIT(MTIM4->CCER ,13 ); /* Set OC4 Active HIGH CC4P*/
	SET_BIT(MTIM4->CCER ,12 ); /* Set OC4EN CC4E*/

	SET_BIT(MTIM4->DIER ,4 ); /*  CC4 Interrupt Enabled */
	CLR_BIT(MTIM4->SR ,4 ); /* Clear CC4 Interrupt Flag */
#endif

	SET_BIT(MTIM4->DIER ,0 );
	CLR_BIT(MTIM4->SR ,0 );
#endif

	MTIM4->PSC = MTIM4_PRESCALER-1 ;

}



#if MTIM4_MODE        ==     PWM_MODE
/*
* Description : Output PWM on OC4REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM4_voidSetPWM(u8 Copy_u8ChannelNo ,u8 Copy_u8Percentage  )
{

	MTIM4->ARR = (u16)(( F_CPU / MTIM4_PRESCALER )/ (MTIM4_PWM_FREQ)) ;

	MTIM4->CCR[Copy_u8ChannelNo] =(u16) ((Copy_u8Percentage * MTIM4->ARR)/100);

	SET_BIT(MTIM4->CR1 ,0 ); /* Counter Enable*/

}
#endif

#if MTIM4_MODE        ==     OUTPUT_CAPTURE_MODE

/*
 * Description : Delay System By Waiting For Timer
 * Arguments   : Ticks
 * return      : None
*/
void MTIM4_voidSetBusyWaitus(u32 Copy_u32Ticks )
{
	f32 LOC_f32TickTime = ((f32)(MTIM4->PSC+1) / F_CPU );
	f32 LOC_f32OneCycleTick = LOC_f32TickTime * REG_MAX * 1000000;
	f32 LOC_f32CyclesNo = Copy_u32Ticks / LOC_f32OneCycleTick;
	CLR_BIT(MTIM4->DIER ,0 ); /* Update interrupt disabled */
	while(  LOC_f32CyclesNo > 0.0)
	{
		if(LOC_f32CyclesNo < 1.0)
		{
			MTIM4->ARR =(u16) (LOC_f32CyclesNo * REG_MAX );
			LOC_f32CyclesNo = 0;
		}
		else
		{
			MTIM4->ARR = REG_MAX ;
			LOC_f32CyclesNo--;
		}
		SET_BIT(MTIM4->CR1 ,0 ); /* Counter Enable*/
		while ( GET_BIT( MTIM4->SR , 0 ) == 0); /* Wait until Update occurs (Timer Finish) */
		CLR_BIT(MTIM4->CR1 ,0 ); /* Counter Disable*/
		CLR_BIT( MTIM4->SR , 0 );
	}
	MTIM4->ARR = 0 ;
}
/*
 * Description : Set Single Period of Time (One Time Count) Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM4_voidSetIntervalSingle(u16 Copy_u16Ticks , void(*ptr)(void) )
{
	MTIM4->ARR = Copy_u16Ticks ;
	SET_BIT(MTIM4->CR1 ,0 ); /* Counter Enable*/
	SET_BIT(MTIM4->DIER ,0 ); /* Update interrupt Enabled */
	TIM_CALLBACK[2] = ptr;
	MTIM4_Interval_Option = MTIM_Single_Interval;
}
/*
 * Description : Set Period of Time every time Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM4_voidSetIntervalPeriodic(u16 Copy_u16Ticks , void(*ptr)(void) )
{
	MTIM4->ARR = Copy_u16Ticks ;
	SET_BIT(MTIM4->CR1 ,0 ); /* Counter Enable*/
	SET_BIT(MTIM4->DIER ,0 ); /* Update interrupt Enabled */
	TIM_CALLBACK[2] = ptr;
	MTIM4_Interval_Option = MTIM_Periodic_Interval;
}
#endif
/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM4_voidStopTimer( void )
{
	MTIM4->ARR = 0 ;
	CLR_BIT(MTIM4->CR1 ,0 ); /* Counter Disable*/
	CLR_BIT(MTIM4->DIER ,0 ); /* Update interrupt Disabled */
}

#endif



void MTIM4_voidICUInit(void)
{

	/*set the prescaler*/
	MTIM4->PSC=7;

	/* Reset Counter */
	MTIM4->CNT = 0;

	/*set the maximum value of the count*/
	MTIM4->ARR=0xFFFF;

	/* Select the active input: TIMx_CCR1 must be linked to the TI1 input */
	SET_BIT(MTIM4->CCMR2,0);
	CLR_BIT(MTIM4->CCMR2,1);



	  /* selects the trigger input to be used to synchronize the counter , 101:Filtered Timer Input 1 (TI1FP1)*/
	  SET_BIT(MTIM4->SMCR,4);
	  CLR_BIT(MTIM4->SMCR,5);
	  SET_BIT(MTIM4->SMCR,6);

	/* Enable capture from the counter into the capture register by setting the CC1E bit in the TIMx_CCER register */
	/* 0: Capture disabled.
       1: Capture enabled. */
	SET_BIT(MTIM4->CCER,8);

	/* Enable the related interrupt request by setting the CC1IE bit in the TIMx_DIER register, */
	/* Bit 1 CC1IE: Capture/Compare 1 interrupt enable
    0: CC1 interrupt disabled.
    1: CC1 interrupt enabled. */
	SET_BIT(MTIM4->DIER,3);

	/*enable timer to start count*/
	SET_BIT(MTIM4->CR1,0);
}
u16 MTIM4_GetCapture(void)
{
	/* If channel CC1is configured as input:
    CCR1 is the counter value transferred by the last input capture 1 event (IC1). The
    TIMx_CCR1 register is read-only and cannot be programmed */
	return MTIM4->CCR[2];
}

u16 MTIM4_GetDistance(void)
{
    distance=pulse_duration/59;
    return distance;
}

void MTIM4_voidSetEdgeDetectionType(u8 EDGE_TYPE)
{
    if(EDGE_TYPE == RISING_EDGE)
    {
    	CLR_BIT(MTIM4->CCER,9);
    }
    else if (EDGE_TYPE == FALLING_EDGE)
    {
    	SET_BIT(MTIM4->CCER,9);
    }
}

void TIM2_IRQHandler(void)
{
	if (MTIM2_Interval_Option == MTIM_Single_Interval)
	{
		MTIM2_voidStopTimer();
		TIM_CALLBACK[0]();
	}
	if (MTIM2_Interval_Option == MTIM_Periodic_Interval  )
	{
		TIM_CALLBACK[0]();
	}
	CLR_BIT( MTIM2->SR , 0 );
	CLR_BIT( MTIM2->SR , 1 );
	CLR_BIT( MTIM2->SR , 2 );
	CLR_BIT( MTIM2->SR , 3 );
	CLR_BIT( MTIM2->SR , 4 );
}


void TIM3_IRQHandler(void)
{
	if (MTIM3_Interval_Option == MTIM_Single_Interval)
	{
		MTIM3_voidStopTimer();
		TIM_CALLBACK[1]();
	}
	if (MTIM3_Interval_Option == MTIM_Periodic_Interval  )
	{
		TIM_CALLBACK[1]();
	}
	CLR_BIT( MTIM3->SR , 0 );
	CLR_BIT( MTIM3->SR , 1 );
	CLR_BIT( MTIM3->SR , 2 );
	CLR_BIT( MTIM3->SR , 3 );
	CLR_BIT( MTIM3->SR , 4 );
}


void TIM4_IRQHandler(void)
{
	/*
	if (MTIM4_Interval_Option == MTIM_Single_Interval)
	{
		MTIM4_voidStopTimer();
		TIM_CALLBACK[2]();
	}
	if (MTIM4_Interval_Option == MTIM_Periodic_Interval  )
	{
		TIM_CALLBACK[2]();
	}
	*/
	if (start_time == 0)
	{
	    // Save the start time of the pulse
	    start_time = MTIM4_GetCapture();
	    /* Detect falling edge */
	    MTIM4_voidSetEdgeDetectionType(FALLING_EDGE);
	}
	else
	{
	    // Save the end time of the pulse
	    end_time = MTIM4_GetCapture();

	    if(end_time > start_time)
	    {
	    // Calculate the pulse duration
	    pulse_duration = end_time - start_time;
	    }
	    else
	    {
	    	pulse_duration=(0xFFFF- start_time)+end_time;
	    }
		/* Detect rising edge */
	    MTIM4_voidSetEdgeDetectionType(RISING_EDGE);

	    /* Clear the timer counter register to start measurements again */
		MTIM4->CNT=0;
	    // Reset the start time
	    start_time = 0;
	    // Reset the end time
	    end_time = 0;
	}
	CLR_BIT( MTIM4->SR , 0 );
	CLR_BIT( MTIM4->SR , 1 );
	CLR_BIT( MTIM4->SR , 2 );
	CLR_BIT( MTIM4->SR , 3 );
	CLR_BIT( MTIM4->SR , 4 );
}

void TIM1_UP_IRQHandler(void)
{

	CLR_BIT( MTIM1->SR , 0 );
	CLR_BIT( MTIM1->SR , 1 );
	CLR_BIT( MTIM1->SR , 2 );
	CLR_BIT( MTIM1->SR , 3 );
	CLR_BIT( MTIM1->SR , 4 );
}
