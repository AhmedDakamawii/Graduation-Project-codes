 /***************************************************************/
 /* Author :                                                     */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: CRUISE CONTROL                                  */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "IR_interface.h"
#include "DCMOTOR_interface.h"
#include "CC_interface.h"
#include "TIMER_interface.h"
#include "ultrasonic_interface.h"
#include "UART_interface.h"


volatile u8 SAFE_DISTANCE= 55;
volatile u8 MAX_SPEED= 80;
volatile u8 Option=0;
extern u8 forward;
extern u8 stop;
extern u8 speed;

volatile u8 ready_flag=0;
u8 DeadDistance = 10;                 //Minimum distance
u16 Current_inputDistance = 0;         //distance take from ultra sonic at the current shot
u16 Prev_inputDistance = 0;            //distance take from ultra sonic at the previous shot
u16 Current_SPEED =0 ;
u16 Prev_Current_SPEED = 0;            //distance take from ultra sonic at the previous shot
u16 step =0;
u16 firstflag =0; //flag for first time to avoid first garbage value for Prev_inputDistance


void CruiseControl_Void_TakeAction (void)
{

	//put here a line to read from ultra sonic in Current_inputDistance
	Current_inputDistance=Ultrasonic_u16ReadDistance();

	/*stop if distance less than 15 cm*/
	if (Current_inputDistance <= DeadDistance)

{
	Current_SPEED=0;
	 DCMOTOR_voidULTRAstop();
	/*lcd appear*/
}

else
{ /*check if we are at a save distance do what ever driver want*/
if (Current_inputDistance >= SAFE_DISTANCE)
{
	ready_flag++;
	if(ready_flag > 5)
	{
		ready_flag=0;
	//if needed we should change while to IF or for or whatever (future)
if (Current_SPEED < MAX_SPEED)
{
	/*increase speed to max by increasing 5 pwwm by 5*/
	Current_SPEED+=20;
	DCMOTOR_VidRotateforwardByPWM(Current_SPEED);
/*lcd appear*/
}
else {
	DCMOTOR_VidRotateforwardByPWM(MAX_SPEED);
	Current_SPEED=MAX_SPEED;
}
/*now driver can ride by MAX speed*/
//DCMOTOR_VidRotateforwardByPWM(MAX_SPEED);
//Current_SPEED=MAX_SPEED;
/*lcd appear*/
	}
}
else
{

	/*an equation to get the rate of decaying */
	//we want each 10 cm equal 1 step
 step =((SAFE_DISTANCE-Current_inputDistance)/10)+(((SAFE_DISTANCE-Current_inputDistance)%10)!=0) ;
/* after making sure that it is not the first time check what distance is large current or previous */
// if ( Current_SPEED!=0)
 //{


	 if (Current_inputDistance > Prev_inputDistance && firstflag==1 )
	 {

		 if(step > Current_SPEED)
		 {
			 Current_SPEED=0;
		 }
		 else
		 {
			 /*if true decrease speed with small rate */
			 Current_SPEED=Current_SPEED -2* step;

		 }

		 DCMOTOR_VidRotateforwardByPWM(Current_SPEED);
		 /*lcd appear*/
	 }

	 else if (step>0)
	  {
 /*if true while current distance is small than previous distance decrease speed with
  large rate than upper condition */
		 if(3*step > Current_SPEED)
		 {
			 Current_SPEED=0;
		 }
		 else
		 {
			 /*if true decrease speed with small rate */
			 Current_SPEED=Current_SPEED - 3*step;

		 }

	 		DCMOTOR_VidRotateforwardByPWM(Current_SPEED);
	 		/*lcd appear*/
  }

 }
 }
//}
/*put here a line to read from Current_inputDistance in Prev_inputDistance */
firstflag=1;
/*put current in prev to compare*/
Prev_inputDistance=Current_inputDistance;

    if (Prev_Current_SPEED!=Current_SPEED)

    {
    	u8 message[4];
	if (Current_SPEED>=12 && Current_SPEED<=MAX_SPEED)
	{
		message[0]='P';
		message[1]=(Current_SPEED/10)+'0';
		message[2]=(Current_SPEED%10)+'0';
		message[3]='\0';


				MUSART3_VidTransmit(message);
	}
	else if (Current_SPEED>=MAX_SPEED)
	{
		message[0]='P';
			message[1]=(MAX_SPEED/10)+'0';
			message[2]=(MAX_SPEED%10)+'0';
			message[3]='\0';
					MUSART3_VidTransmit(message);
	}
				   else if (Current_SPEED<12)
				    {
						    message[0]='P';
							message[1]=(12/10)+'0';
							message[2]=(12%10)+'0';
							message[3]='\0';
				    				MUSART3_VidTransmit(message);
				    }

}
    Prev_Current_SPEED=Current_SPEED;
forward=1;
stop=0;
}
void CruiseControl_VoidSelectOption(void)
{
	/*
	 * OPTION = 3 means change will happen in OFF
	 * OPTION = 1 means change will happen in Max Speed
	 * OPTION = 2 means change will happen in safe Distance
	 */
	Option++;
		  if (Option==1)
		  {
			  u8* message="C10";
			  MUSART3_VidTransmit((u8*)message);
		  }
		  else if (Option==2)
		 {
			  u8* message="C20";
			  MUSART3_VidTransmit((u8*)message);
		 }
		  else if (Option==3)
				 {
					  u8* message="C30";
					  MUSART3_VidTransmit((u8*)message);
						Option=0;
				 }

}

void CruiseControl_VoidIncOption(void)
{
	if(Option == 2)
	{
		/* OPTION = 0 means change will happen in safe Distance*/
		if(SAFE_DISTANCE < 95)
		{
			SAFE_DISTANCE +=10;
		}
		if (DeadDistance<= SAFE_DISTANCE && SAFE_DISTANCE<=95)
			{
				u8 message[4];

						         	message[0]='D';
						   			message[1]=(SAFE_DISTANCE/10)+'0';
									message[2]=(SAFE_DISTANCE%10)+'0';
									message[3]='\0';
									MUSART3_VidTransmit(message);
			}
	}
	else if (Option == 1)
	{
		/* OPTION = 1 means change will happen in Max Speed*/
		if( MAX_SPEED <=95)
		{
			MAX_SPEED +=5;
		}
		else
		{
			MAX_SPEED =95;
		}

		if (45 <= MAX_SPEED && MAX_SPEED<=95)
			{
				u8 message[4];

						         	message[0]='V';
						   			message[1]=(MAX_SPEED/10)+'0';
									message[2]=(MAX_SPEED%10)+'0';
									message[3]='\0';
									MUSART3_VidTransmit(message);
			}
}
}
void CruiseControl_VoidDecOption(void)
{
	if(Option == 2)
	{
		/* OPTION = 0 means change will happen in safe Distance*/
		if(SAFE_DISTANCE > (DeadDistance+10))
		{
			SAFE_DISTANCE -=10;
		}
		else
		{
			SAFE_DISTANCE= DeadDistance;
		}

		if (DeadDistance<= SAFE_DISTANCE && SAFE_DISTANCE<=99)
		{
			u8 message[4];

					         	message[0]='D';
					   			message[1]=(SAFE_DISTANCE/10)+'0';
								message[2]=(SAFE_DISTANCE%10)+'0';
								message[3]='\0';
								MUSART3_VidTransmit(message);
		}


	}
	else if (Option == 1)
	{
		/* OPTION = 1 means change will happen in Max Speed*/
		if(MAX_SPEED >=50)
		{
			MAX_SPEED -=5;
		}
		else
		{
			MAX_SPEED= 45;
		}

		if (45 <= MAX_SPEED && MAX_SPEED<=95)
					{
						u8 message[4];

								         	message[0]='V';
								   			message[1]=(MAX_SPEED/10)+'0';
											message[2]=(MAX_SPEED%10)+'0';
											message[3]='\0';
											MUSART3_VidTransmit(message);
					}

}

}

void CruiseControl_VoidRotateRight(void)
{
	DCMOTOR_VidRotateright();
	DCMOTOR_VidRotateforwardByPWM(Current_SPEED);
}
void CruiseControl_VoidRotateLeft(void)
{
	DCMOTOR_VidRotateleft();
	DCMOTOR_VidRotateforwardByPWM(Current_SPEED);
}

