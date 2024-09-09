/***************************************************************/
/* Author :                                                     */
/*version:  V01                                                */
/*Date:                                                        */
/*Describtion: Light System*/
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "Light System_interface.h"
#include "DCMOTOR_interface.h"
#include "BH1750_interface.h"
#include "Servo_Interface.h"
#include "CC_Interface.h"


/* Servo 1 : LEFT Servo    -----------   Servo 2 : RIGHT Servo */
/* LED 1   : LEFT LED      -----------   LED 2   : RIGHT LED */

u8 ALS_MAX_SPEED        = 80;
//volatile u8 ALS_CURRENT_SPEED   = 60;
u8 ALS_MAX_PWM         = 80;
u8 ALS_MED_PWM         = 40;
u8 ALS_LOW_PWM         = 20;
u16 ALS_SENSOR_READ1   = 0;
u16 ALS_SENSOR_READ2    = 0;
u8 ALS_MIN_SPEED       = 20;
 u16 ALS_MAX_INTENSTY    = 250;

 extern u8 ACC_Mode;
 extern u8 speed;//manual
 extern u8 Current_SPEED;//cruise


volatile u8 G_PWMPercentage;


void LS_VoidLightSystemINIT ()
{
	/*1ST LED*/
	MGPIO_VidSetPinDirection(GPIOB,LED1_PIN1,OUT_SPEED_10MHZ_PUSHPULL);//B1
	MGPIO_VidSetPinDirection(GPIOB,LED1_PIN2,OUT_SPEED_10MHZ_PUSHPULL);//B3
	/*2ND LED*/
	MGPIO_VidSetPinDirection(GPIOB,LED2_PIN1,OUT_SPEED_10MHZ_PUSHPULL);//B4
	MGPIO_VidSetPinDirection(GPIOB,LED2_PIN2,OUT_SPEED_10MHZ_PUSHPULL);//B5

	/*LEDS PWM*/
	/*PWM1*/
	MGPIO_VidSetPinDirection(0, 1 ,OUT_SPEED_10MHZ_alternativeFUN_PP);//A1
	/*PWM2*/
	MGPIO_VidSetPinDirection(0, 2 ,OUT_SPEED_10MHZ_alternativeFUN_PP);//A2
	/*put all the pins LOW at first */

	/*1ST H-BRIDGE*/
	MGPIO_VidSetPinValue(GPIOB , LED1_PIN1 , LOW);
	MGPIO_VidSetPinValue(GPIOB , LED1_PIN2 , LOW);
	/*2ND H-BRIDGE*/
	MGPIO_VidSetPinValue(GPIOB , LED2_PIN1 , LOW);
	MGPIO_VidSetPinValue(GPIOB , LED2_PIN2 , LOW);


BH1750_VoidInit();
SERVO1_Init();
SERVO2_Init();

}

void LS_VoidSetLightintensity (u8  Copy_1stledPwm , u8 Copy_2ndledPwm)
{
	/*1st led CLK WISE*/
	MTIM2_voidSetPWM(CHANNEL_PWM_LED1,Copy_1stledPwm);

	MGPIO_VidSetPinValue(GPIOB , LED1_PIN1 , LOW);
	MGPIO_VidSetPinValue(GPIOB , LED1_PIN2 , HIGH);

	/*2ND led CLK WISE*/
	MTIM2_voidSetPWM(CHANNEL_PWM_LED2,Copy_2ndledPwm);

	MGPIO_VidSetPinValue(GPIOB , LED2_PIN1 , LOW);
	MGPIO_VidSetPinValue(GPIOB , LED2_PIN2 , HIGH);

}

void FrontLight_voidTakeAction( void)
{

	if (ACC_Mode==1)
	{
		G_PWMPercentage = Current_SPEED;

	}
	else
	{
		G_PWMPercentage = speed ;

	}
	//G_PWMPercentage=80;

	BH1750_VoidReadRight(&ALS_SENSOR_READ1 );
	BH1750_VoidReadLeft(&ALS_SENSOR_READ2 );

	//ALS_SENSOR_READ2=3000;
	//ALS_SENSOR_READ1=1000;


	/*yb2a awl case 3andy el hya bta3t check of speed from dc motor if it exceeds the limited speed make the intensity
		high and by decrease the speed decrease the intensity of light */
	if (G_PWMPercentage >= ALS_MAX_SPEED)
	{
		/*case 2 check on the light intensity if car from the left side decrease the intensity of the left led and move sero downward
		 * or toward right direction*/
		if(ALS_SENSOR_READ1 >= ALS_MAX_INTENSTY && ALS_SENSOR_READ2 <= ALS_MAX_INTENSTY)
		{
			LS_VoidSetLightintensity(ALS_LOW_PWM , ALS_MAX_PWM);



			SERVO1_Direction(Right_Position);
			SERVO2_Direction(Center_Position);

		}

		/*case 3 check on the light intensity if car from the right side decrease the intensity of the right led and move sero downward
		 * or toward left direction*/

		if(ALS_SENSOR_READ2 >= ALS_MAX_INTENSTY && ALS_SENSOR_READ1 <= ALS_MAX_INTENSTY)
		{
			LS_VoidSetLightintensity( ALS_MAX_PWM, ALS_LOW_PWM);

			SERVO1_Direction(Center_Position);
			SERVO2_Direction(Left_Position);
		}

		/*case 4 both 3&2 toghether*/
		if(ALS_SENSOR_READ1 >= ALS_MAX_INTENSTY && ALS_SENSOR_READ2 >= ALS_MAX_INTENSTY)
		{

			LS_VoidSetLightintensity(ALS_LOW_PWM , ALS_LOW_PWM);

			SERVO1_Direction(Right_Position);
			SERVO2_Direction(Left_Position);
		}

		/* No Cars */
		if(ALS_SENSOR_READ1 <= ALS_MAX_INTENSTY && ALS_SENSOR_READ2 <= ALS_MAX_INTENSTY)
		{
			/* max light */
			LS_VoidSetLightintensity(ALS_MAX_PWM , ALS_MAX_PWM);

			SERVO1_Direction(Center_Position);
			SERVO2_Direction(Center_Position);
		}
	}


	else if ((G_PWMPercentage >= ALS_MIN_SPEED) && (G_PWMPercentage <= ALS_MAX_SPEED))
	{
		/*case 2 check on the light intensity if car from the left side decrease the intensity of the left led and move sero downward
		 * or toward right direction*/
		if(ALS_SENSOR_READ1 >= ALS_MAX_INTENSTY && ALS_SENSOR_READ2 <= ALS_MAX_INTENSTY)
		{
			LS_VoidSetLightintensity(ALS_LOW_PWM , ALS_MED_PWM);



			SERVO1_Direction(Right_Position);
			SERVO2_Direction(Center_Position);

		}

		/*case 3 check on the light intensity if car from the right side decrease the intensity of the right led and move sero downward
		 * or toward left direction*/

		if(ALS_SENSOR_READ2 >= ALS_MAX_INTENSTY && ALS_SENSOR_READ1 <= ALS_MAX_INTENSTY)
		{
			LS_VoidSetLightintensity( ALS_MED_PWM, ALS_LOW_PWM);

			SERVO1_Direction(Center_Position);
			SERVO2_Direction(Left_Position);
		}


		/*case 4 both 3&2 toghether*/
		if(ALS_SENSOR_READ1 >= ALS_MAX_INTENSTY && ALS_SENSOR_READ2 >= ALS_MAX_INTENSTY)
		{
			LS_VoidSetLightintensity(ALS_LOW_PWM , ALS_LOW_PWM);


			SERVO1_Direction(Right_Position);
			SERVO2_Direction(Left_Position);
		}

		/* No Cars */
		if(ALS_SENSOR_READ1 <= ALS_MAX_INTENSTY && ALS_SENSOR_READ2 <= ALS_MAX_INTENSTY)
		{
			/* max light */

			LS_VoidSetLightintensity(ALS_MED_PWM , ALS_MED_PWM);

			SERVO1_Direction(Center_Position);
			SERVO2_Direction(Center_Position);
		}
	}

	else
	{

	}

	/*case 5 when car rotates rotate the servo in the same direction of car rotation */
	// we can change it later

}
