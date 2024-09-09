#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "STK_INTERFACE.h"
#include "DCMOTOR_INTERFACE.h"
#include "DCMOTOR_PRIVATE.h"
#include "DCMOTOR_CONFG.h"
#include "TIMER_INTERFACE.h"
#include "UART_interface.h"

u8 backward=0;
u8 forward=0;
u8 stop=0;
u8 speed=0;

void DCMOTOR1_VidInit(    void )
{
	/*set the direction of the two input pins of the dc motor to be OUT_SPEED_50MHZ_PUSHPULL pins */
	MGPIO_VidSetPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN1 ,0b0011 );//IF ERROR HAPPEN try to make it 10MHZ 
	MGPIO_VidSetPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN2 ,0b0011 );

		/*initialize the dc motor to be stop at the beginning*/
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);

}
void DCMOTOR2_VidInit(void)
{
	/*set the direction of the two input pins of the dc motor to be OUT_SPEED_50MHZ_PUSHPULL pins */
	MGPIO_VidSetPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN3 , 0b0011);
	MGPIO_VidSetPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN4 , 0b0011);

		/*initialize the dc motor to be stop at the beginning*/
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);

}

//not used
void DCMOTOR_VidRotate(u8 direction,u8 direction2)
{

//	 TIMER2_SetOCROPWM(100);
{switch(direction){
	case STOP:
		/*make the dc motor stop*/
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
		break;
	case CLK_WISE:
		/*make the dc motor start in CLOCK_WISE direction*/
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , HIGH);

		break;
	case ANTI_CLK_WISE:
		/*make the dc motor start in ANTI_CLOCK_WISE  direction*/
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , HIGH);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);

		break;
	}
switch(direction2){
	case STOP:
		/*make the dc motor stop*/
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
		break;
	case CLK_WISE:
		/*make the dc motor start in CLOCK_WISE direction*/
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , HIGH);
		break;
	case ANTI_CLK_WISE:
		/*make the dc motor start in ANTI_CLOCK_WISE  direction*/
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , HIGH);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
		break;
	}
}
//TIMER2_SetOCROPWM(100);

}




void DCMOTOR_VidRotateright(void)
{
	MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,80);

	//right wheel stop


	//left wheel clk wise
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , HIGH);

	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
	//then after some delay return stop
	MTIM3_voidSetBusyWaitus(2000000);
//stop
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);

MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,0);

//to make sure that you will start from first speed
forward=0;
backward=0;
stop=0;
speed=20;

}
void DCMOTOR_VidRotateleft(void)
{

	MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,80);

	//left wheel stop
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);

	//right wheel clk wise
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , HIGH);

	//then after some delay return stop
	MTIM3_voidSetBusyWaitus(2000000);

	//stop
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);

MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,0);

//to make sure that you will start from first speed
forward=0;
backward=0;
stop=0;
speed=20;

}
void DCMOTOR_VidRotatestop(void)
{
	MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,40);
	speed=20;

	if (stop==0 && forward==0 && backward==0  )
	{
		//then stop
		MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,0);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
	}
else if (stop==0 && backward==0)
{
		MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,20);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , HIGH);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , HIGH);
		stop++;
}
else if (stop==0 && forward==0)
{
		MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,30);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , HIGH);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , HIGH);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
		stop++;
}
//then
	else if (stop==1)
	{
		speed=0;

		//then stop
		MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,0);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
			stop++;

	}
	else if (stop>1)
	{
		MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,0);
				MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
				MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
				MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
				MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
					speed=0;
	}
	u8 message[4];
	if (speed>=12)
	{
		message[0]='P';
		message[1]=(speed/10)+'0';
		message[2]=(speed%10)+'0';
		message[3]='\0';


				MUSART3_VidTransmit(message);
	}
				   else if (speed<=12)
				    {
						    message[0]='P';
							message[1]=(12/10)+'0';
							message[2]=(12%10)+'0';
							message[3]='\0';
				    				MUSART3_VidTransmit(message);
				    }

forward=0;
backward=0;
}
void DCMOTOR_VidRotateforward(void)
{
	
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , HIGH);

	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , HIGH);
			if (forward == 0)
			{
				MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,80);
				MTIM3_voidSetBusyWaitus(10000);
				MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,40);
				speed=40;

			forward++;
			backward=0;
			stop=0;}
			else if( forward == 1)
			{MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,60);
			speed=60;

			forward++;
			backward=0;
			stop=0;}
			else if (forward == 2)
			{MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,80);
			speed=80;

			backward=0;
			forward++;
			stop=0;}

			u8 message[4];
				if (speed>=12)
				{
					message[0]='P';
					message[1]=(speed/10)+'0';
					message[2]=(speed%10)+'0';
					message[3]='\0';


							MUSART3_VidTransmit(message);
				}
							   else
							    {
									    message[0]='P';
										message[1]=(12/10)+'0';
										message[2]=(12%10)+'0';
										message[3]='\0';
							    				MUSART3_VidTransmit(message);
							    }

			}



void DCMOTOR_VidRotatebackward(void)
{
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , HIGH);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , HIGH);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);
		if (backward == 0)
		{
			MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,80);
			MTIM3_voidSetBusyWaitus(10000);
			MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,60);
		backward++;
		forward=0;
		stop=0;}
		else if (backward == 1)
		{MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,80);
		backward++;
		forward=0;
		stop=0;}
		else if (backward == 2)
		{MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,98);
		backward++;
		forward=0;
		stop=0;}
		
		

}
//not used
void DCMOTOR_VidRotate180(void)
{
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , HIGH);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , HIGH);
}

void DCMOTOR_VidRotateforwardByPWM(u8 PWM_Speed)
{


	if(PWM_Speed <5)
	{
		DCMOTOR_voidULTRAstop();
	}
	else
	{
		MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,PWM_Speed);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , HIGH);

		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
		MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , HIGH);
	}

}


void DCMOTOR_voidULTRAstop(void)
{

	MTIM2_voidSetPWM(DC_MOTOR_PWMCHANNEL,0);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN1 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN2 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN3 , LOW);
	MGPIO_VidSetPinValue(DC_MOTOR_PORT , DC_MOTOR_PIN4 , LOW);

}

