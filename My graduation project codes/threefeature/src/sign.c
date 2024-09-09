/*
 * sign.c
 *
 *  Created on: Mar 4, 2024
 *      Author: DELL
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "DCMOTOR_interface.h"
#include "UART_interface.h"

/* Round - Parking - No Parking - U-Turn - No U-Turn - No Entry - No Waiting */


extern u8 speed;
//extern u8 Current_SPEED;
extern u8 forward;
u8 TSR_flag =0;
u8 fla=0;

void TSR_signDetect( void)

{

	/* STOP Sign*/
	if(MGPIO_U8GetPinValue(1,9) == 1 &&MGPIO_U8GetPinValue(1,13) == 0 && MGPIO_U8GetPinValue(1,14) ==  0 && MGPIO_U8GetPinValue(1,15) ==  0  )
	{

		DCMOTOR_voidULTRAstop();
		forward=0;
		speed=0;



//				for (u32 j = 0; j < 1000000; j++) {
//						asm("NOP");
//						}
		fla =0 ;

		u8* message="S10";
		MUSART3_VidTransmit((u8*)message);

	}



	/* Speed Limit 80 */
	else if(MGPIO_U8GetPinValue(1,9) == 1 &&MGPIO_U8GetPinValue(1,13) == 1 && MGPIO_U8GetPinValue(1,14) ==  0 && MGPIO_U8GetPinValue(1,15) ==  0  )
	{
		//TSR_flag = 0;
if(speed>50)
{
	speed=50;
	DCMOTOR_VidRotateforwardByPWM(speed);
}
forward=1;
fla =0 ;

u8* message="S30";
MUSART3_VidTransmit(message);
	}
	/* Speed Limit 60 */
	else if(MGPIO_U8GetPinValue(1,9) == 0 &&MGPIO_U8GetPinValue(1,13) == 1 && MGPIO_U8GetPinValue(1,14) ==  0 && MGPIO_U8GetPinValue(1,15) ==  0  )
	{
		if(speed>40)
		{
			speed=40;
			DCMOTOR_VidRotateforwardByPWM(speed);
		}
		//TSR_flag = 0;
		forward=0;

		fla =0 ;

		u8* message="S20";
		MUSART3_VidTransmit((u8*)message);
	}
	/*Uturn*/
	else if(MGPIO_U8GetPinValue(1,9) ==  0 &&MGPIO_U8GetPinValue(1,13) == 0 && MGPIO_U8GetPinValue(1,14) ==  1 && MGPIO_U8GetPinValue(1,15) ==  0  )
		{
		if(speed<20)
		{
			MGPIO_VidSetPinValue(0,5,1);
			for(u32 Buzzer=0 ;Buzzer<100000; Buzzer++ );
			MGPIO_VidSetPinValue(0,5,0);
		}
		fla =0 ;
		u8* message="S40";
		MUSART3_VidTransmit((u8*)message);
		}
//parkiing
	else if(MGPIO_U8GetPinValue(1,9) ==  1 &&MGPIO_U8GetPinValue(1,13) == 0 && MGPIO_U8GetPinValue(1,14) ==  1 && MGPIO_U8GetPinValue(1,15) ==  0  )
			{
			if(speed<20)
			{
				MGPIO_VidSetPinValue(0,5,1);
				for(u32 Buzzer=0 ;Buzzer<100000; Buzzer++ );
				MGPIO_VidSetPinValue(0,5,0);
			}
			fla =0 ;
			u8* message="S50";
			MUSART3_VidTransmit((u8*)message);
			}
	//no waiting
	else if(MGPIO_U8GetPinValue(1,9) ==  0 &&MGPIO_U8GetPinValue(1,13) == 0 && MGPIO_U8GetPinValue(1,14) == 1 && MGPIO_U8GetPinValue(1,15) ==  1  )
			{
			if(speed<20)
			{
				MGPIO_VidSetPinValue(0,5,1);
				for(u32 Buzzer=0 ;Buzzer<100000; Buzzer++ );
				MGPIO_VidSetPinValue(0,5,0);
			}
			fla =0 ;
			u8* message="S60";
			MUSART3_VidTransmit((u8*)message);
			}
	//no parking
	else if(MGPIO_U8GetPinValue(1,9) ==  1 &&MGPIO_U8GetPinValue(1,13) == 1 && MGPIO_U8GetPinValue(1,14) ==  1 && MGPIO_U8GetPinValue(1,15) ==  0  )
			{
			if(speed<20)
			{
				MGPIO_VidSetPinValue(0,5,1);
				for(u32 Buzzer=0 ;Buzzer<100000; Buzzer++ );
				MGPIO_VidSetPinValue(0,5,0);
			}
			fla =0 ;
			u8* message="S70";
			MUSART3_VidTransmit((u8*)message);
			}
	//no entry
	else if(MGPIO_U8GetPinValue(1,9) ==  0 &&MGPIO_U8GetPinValue(1,13) == 0 && MGPIO_U8GetPinValue(1,14) ==  0 && MGPIO_U8GetPinValue(1,15) ==  1  )
			{
			if(speed<20)
			{
				MGPIO_VidSetPinValue(0,5,1);
				for(u32 Buzzer=0 ;Buzzer<100000; Buzzer++ );
				MGPIO_VidSetPinValue(0,5,0);
			}
			fla =0 ;
			u8* message="S80";
			MUSART3_VidTransmit((u8*)message);
			}
		else if(MGPIO_U8GetPinValue(1,9) ==  1 &&MGPIO_U8GetPinValue(1,13) == 0 && MGPIO_U8GetPinValue(1,14) ==  0 && MGPIO_U8GetPinValue(1,15) ==  1  )
			{

				if (fla==0)
				{
					u8* message="S81";
					MUSART3_VidTransmit((u8*)message);
fla =1 ;
				}
			}















	/*led for other sign*/
//	else if(MGPIO_U8GetPinValue(1,13) == 1 && MGPIO_U8GetPinValue(1,14) ==  0 && MGPIO_U8GetPinValue(1,15) ==  1)
//		{
//		MGPIO_VidSetPinValue(0,6,1);
//			for(u32 led=0 ;led<1000000; led++ );
//			MGPIO_VidSetPinValue(0,6,0);
//			}
//
//	MUSART3_VidTransmit((u8*)"A");
//


}

