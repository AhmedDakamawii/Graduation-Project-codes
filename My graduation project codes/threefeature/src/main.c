#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "EXTI_interface.h"
#include "AFIO_interface.h"
#include "IR_interface.h"
#include "DCMOTOR_interface.h"
#include "TIMER_interface.h"
#include "CC_interface.h"
#include "ultrasonic_interface.h"
#include "Light System_interface.h"
#include "I2C_interface.h"
#include "Servo_Interface.h"
#include "UART_interface.h"
#include "sign.h"
volatile u8 ACC_Mode =0;
volatile u8 Light_Mode =0;
volatile u8 Sign_Mode =0;
volatile u8 count =0;
void main ( void)


{


	MRCC_VidInitSysClock();
	/*enable RCC GPIOA in APB2*/
	MRCC_VidEnableClock(RCC_APB2, 2);
	/*enable RCC GPIOB in APB2*/
	MRCC_VidEnableClock(RCC_APB2, 3);
	/*enable AFIO CLK in APB2*/
	MRCC_VidEnableClock(RCC_APB2, 0);
	/*ENABLE TIMER1*/
	MRCC_VidEnableClock(RCC_APB2, 11);
/*enable TIMER2 CLK in APB1*/
	MRCC_VidEnableClock(RCC_APB1, 0);
	/*enable RCC tim3 in APB2*/
	MRCC_VidEnableClock(RCC_APB1, 1);
	/*enable RCC tim4 in APB2*/
   MRCC_VidEnableClock(RCC_APB1, 2);
   //I2C enable

	/*enable USART3 CLK in APB1*/
	MRCC_VidEnableClock(RCC_APB1, 18);

    /*INIT USART3*/
	   MUSART3_VidInit();
	     /*TX3*/
	   MGPIO_VidSetPinDirection(1, 10, OUT_SPEED_50MHZ_alternativeFUN_PP);
	   /*RX3 SHOULD BE INPUT FLOATING*/
	   MGPIO_VidSetPinDirection(1, 11, INPUT_FLOATING);

   MRCC_VidEnableClock(RCC_APB1,21);
	/*TIMER 2 INIT and interrupt */
	MTIM2_voidInit();
	MNVIC_VidEnableInterrupts(28);
	MNVIC_VidEnableInterrupts(29);

	MNVIC_VidEnableInterrupts(30);	/*TIMER 4 INTERRUPT*/
	MNVIC_VidEnableInterrupts(25);/* TIMER1 INTERRUPT*/
	MTIM1_voidInit();
	MTIM3_voidInit();
	MTIM4_voidInit();
 MI2C_voidInit();
MI2C_voidSetOwnAddress(0);
/*INIT STK Timer*/
     MSTK_voidInit();

     /*DC MOTOR*/
     DCMOTOR1_VidInit();
     DCMOTOR2_VidInit();
/*dont forget we use EXTI0  in IR used when ni cruise control*/
     IR_VoidINIT();

	 LS_VoidLightSystemINIT ();

     /*ultrasonic*/

    Ultrasonic_voidInit();

  /*LCD*/
   //  HLCD_voidInit();
/*OUTPUT*/

/*INPUT*/
    MGPIO_VidSetPinDirection(1, 0, INPUT_FLOATING);//input floating connected to output of IR
    MGPIO_VidSetPinDirection(0, 0, OUT_SPEED_2MHZ_alternativeFUN_PP);//PWM

    MGPIO_VidSetPinDirection(0, 6, OUT_SPEED_10MHZ_PUSHPULL);//LED for other sign


    MGPIO_VidSetPinDirection(1, 13, INPUT_PULLUPDOWN);//for sign-detect
    MGPIO_VidSetPinDirection(1, 14, INPUT_PULLUPDOWN);//for sign-detect
    MGPIO_VidSetPinDirection(1, 15, INPUT_PULLUPDOWN);//for sign-detec
    MGPIO_VidSetPinDirection(1, 9, INPUT_PULLUPDOWN);//for sign-detec

    MGPIO_VidSetPinDirection(0, 5, OUT_SPEED_10MHZ_PUSHPULL);//for Buzzer

while(1)
{
	TSR_signDetect();
			if(ACC_Mode==1)
			{
				CruiseControl_Void_TakeAction();
			}



if (Light_Mode)
	{
FrontLight_voidTakeAction();
	}
}
}



