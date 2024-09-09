

#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H



#if MTIM1_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM1_voidInit(void);
/*
* Description : Output PWM on OC2REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM1_voidSetPWM(u8 Copy_u8ChannelNo ,u16 Copy_u8Percentage );
/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM1_voidStopTimer( void );
#endif





#if MTIM2_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM2_voidInit(void);
/*
* Description : Output PWM on OC2REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM2_voidSetPWM(u8 Copy_u8ChannelNo ,u8 Copy_u8Percentage  );
/*
 * Description : Delay System By Waiting For Timer
 * Arguments   : Ticks
 * return      : None
*/
void MTIM2_voidSetBusyWaitus(u32 Copy_u32Ticks );
/*
 * Description : Set Period of Time every time Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM2_voidSetIntervalPeriodic(u16 Copy_u16Ticks , void(*ptr)(void) );
/*
 * Description : Set Single Period of Time (One Time Count) Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM2_voidSetIntervalSingle(u16 Copy_u16Ticks , void(*ptr)(void) );
/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM2_voidStopTimer( void );
#endif


#if MTIM3_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM3_voidInit(void);
/*
* Description : Output PWM on OC3REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM3_voidSetPWM(u8 Copy_u8ChannelNo ,u8 Copy_u8Percentage );
/*
 * Description : Delay System By Waiting For Timer
 * Arguments   : Ticks
 * return      : None
*/
void MTIM3_voidSetBusyWaitus(u32 Copy_u32Ticks );
/*
 * Description : Set Period of Time every time Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM3_voidSetIntervalPeriodic(u16 Copy_u16Ticks , void(*ptr)(void) );
/*
 * Description : Set Single Period of Time (One Time Count) Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM3_voidSetIntervalSingle(u16 Copy_u16Ticks , void(*ptr)(void) );
/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM3_voidStopTimer( void );
#endif


#if MTIM4_STATUS         ==           ON
/*
 * Description : Initialize Timer Based on Configurations
 * Arguments   : None
 * return      : None
*/
void MTIM4_voidInit(void);
/*
* Description : Output PWM on OC4REF with duty cycle on Chosen Channel
* Arguments   : Channel No. , PWM duty cycle from 0 to 100
* return      : void
*/
void MTIM4_voidSetPWM(u8 Copy_u8ChannelNo ,u8 Copy_u8Percentage );
/*
 * Description : Delay System By Waiting For Timer
 * Arguments   : Ticks
 * return      : None
*/
void MTIM4_voidSetBusyWaitus(u32 Copy_u32Ticks );
/*
 * Description : Set Period of Time every time Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM4_voidSetIntervalPeriodic(u16 Copy_u16Ticks , void(*ptr)(void) );
/*
 * Description : Set Single Period of Time (One Time Count) Update event (Overflow/Underflow) happen, Interrupt System
 * Arguments   : Ticks , Pointer To Function (Interrupt Function)
 * return      : None
*/
void MTIM4_voidSetIntervalSingle(u16 Copy_u16Ticks , void(*ptr)(void) );
/*
 * Description : Stop Timer
 * Arguments   : None
 * return      : None
*/
void MTIM4_voidStopTimer( void );
#endif
void MTIM4_voidICUInit(void);
u16 MTIM4_GetDistance(void);
u16 MTIM4_GetCapture(void);
void MTIM4_voidSetEdgeDetectionType(u8 EDGE_TYPE);

#define RISING_EDGE          0
#define FALLING_EDGE          1


#define MTIM2_PWM_CHANNEL1                  0
#define MTIM2_PWM_CHANNEL2                  1
#define MTIM2_PWM_CHANNEL3                  2
#define MTIM2_PWM_CHANNEL4                  3

#define MTIM3_PWM_CHANNEL1                  0
#define MTIM3_PWM_CHANNEL2                  1
#define MTIM3_PWM_CHANNEL3                  2
#define MTIM3_PWM_CHANNEL4                  3

#define MTIM4_PWM_CHANNEL1                  0
#define MTIM4_PWM_CHANNEL2                  1
#define MTIM4_PWM_CHANNEL3                  2
#define MTIM4_PWM_CHANNEL4                  3


/* Options For Timer Status */
#define ON                         1
#define OFF                        0

/* Options For Timer Modes */
#define PWM_MODE                   0
#define OUTPUT_CAPTURE_MODE        1



#endif
