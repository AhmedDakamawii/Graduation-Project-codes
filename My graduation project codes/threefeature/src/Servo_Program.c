/*************************************************/
/* Author : Reem Alaa                            */
/*Date : 17/8/2023                               */
/*Version : V01                                  */
/*************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Servo_Interface.h"
#include "Servo_Config.h"
#include "DIO_interface.h"
#include "DIO_confg.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

void SERVO1_Init( void)
{


	/*set the pwm pin channel as output pin*/
	MGPIO_VidSetPinDirection(SERVO_Motor1_PORT,SERVO_Motor1_PIN,OUT_SPEED_10MHZ_alternativeFUN_PP);//A1
	/*let the first postion of servo at the beginning at the middle 90 degree*/

}
void SERVO2_Init( void)
{


		/*set the pwm pin channel as output pin*/
		MGPIO_VidSetPinDirection(SERVO_Motor2_PORT,SERVO_Motor2_PIN,OUT_SPEED_10MHZ_alternativeFUN_PP);//A2
		/*let the first postion of servo at the beginning at the middle 90 degree*/
		//MTIM2_voidSetPWM(SERVO_Motor2_PWMCHANNEL ,Duty_Cycle2  );

}

void SERVO1_Direction(u16 Duty_Cycle1)
{
	MTIM1_voidSetPWM(SERVO_Motor1_PWMCHANNEL , Duty_Cycle1 );



}
void SERVO2_Direction(u16 Duty_Cycle2)
{
	MTIM1_voidSetPWM(SERVO_Motor2_PWMCHANNEL , Duty_Cycle2 );

}
