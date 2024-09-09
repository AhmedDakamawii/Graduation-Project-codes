 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: IR                                           */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "IR_interface.h"
#include "DCMOTOR_interface.h"
#include "STK_interface.h"
#include "EXTI_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"

#include "CC_interface.h"

volatile u8 Data=0;
volatile u8 flag=0;
//this is to save the time of difference between each two adjacent falling edge in each index
volatile u32 Frame_data [50]={0};
//this is the variable that contain the index of each falling edge
volatile u8 Edge_counter=0;
//this is function for EXTI interrupt enters it when falling edge is come

extern u8 ACC_Mode;
extern u8 Light_Mode ;
extern u8 Sign_Mode ;
extern u16 Current_SPEED ;
extern u8 speed ;
extern u8 forward ;


u8 Mode_change ;
void IR_VoidINIT ( void)
{
	/*EXTI*/
	//ENABLE EXTI0 and use its ISR
	MNVIC_VidEnableInterrupts(6);
	MEXTI0_VidSetCallBack(voidGetFrame);
	MEXTI_VidSetSignalLatch(0,FALLING );//LINE 0 FALLING MODE
	MAFIO_VidSetEXTIConfig(0,AFIO_PORTB);//pin B0
}
void voidGetFrame( void)
{
	if (flag == 0)
	{
		//start timer
   MSTK_voidSetIntervalSinglems(300, Void_TakeAction);
   flag=1;
	}
	else
	{
		//each Frame_data index contains the time between two adjacent falling edge
		Frame_data[Edge_counter]=MSTK_u32GetElapsedTime();

		  MSTK_voidSetIntervalSinglems(300, Void_TakeAction);
		  Edge_counter++;
	}
}

void Void_TakeAction (void)
{
	//as address  of each remote is always constant we will focus on data from index 17
	Data=0;
	u8 i;
	//test for value of start bit which is should equal 13500
if (Frame_data[0] >= 10000 && Frame_data[0] <= 15000)
{
	for (i=0;i<8;i++)
	{
		//thats mean we send 1 which is should equal 2250
	if(Frame_data[17+i]>= 2000 && Frame_data[17+i]<= 2300)
	{
		SET_BIT(Data , i);
	}
	else
	{
		//thats mean we send 0 which is should equal 1125
		CLR_BIT(Data , i);
	}
}
	Void_Play();
}
//make all equal 0 to be ready for another click on the remote
flag=0;
Frame_data[0]=0;
Edge_counter=0;
}

void Void_Play (void)
{
switch (Data)
{
case 28://stop
	if(ACC_Mode ==0)
	{

		DCMOTOR_VidRotatestop();
	}
	else
	{
		ACC_Mode=0;
		DCMOTOR_VidRotatestop();
		Current_SPEED=0;
		Mode_change=1;
	}
	break;
case 24:  //for forward
	if (ACC_Mode==0)
	{DCMOTOR_VidRotateforward();
	ACC_Mode=0;
	}
	else
	{
		Mode_change=1;
		ACC_Mode=0;
		//Current_SPEED=0;
		DCMOTOR_VidRotateforward();
	}
	break;
case 82:
	DCMOTOR_VidRotatebackward();
	break;
case 90:
	if(ACC_Mode ==0)
	{
		DCMOTOR_VidRotateright();
	}
	else
	{
		CruiseControl_VoidRotateRight();
	}
	break;
case 8:
	if(ACC_Mode ==0)
	{
		DCMOTOR_VidRotateleft();
	}
	else
	{
		CruiseControl_VoidRotateLeft();
	}
	break;
case 69:     /* Button "1" */
	TOGGLE_BIT(ACC_Mode,0);
	Mode_change=1;
	if (ACC_Mode==1)
	{Current_SPEED=speed;
	}
	else if (ACC_Mode==0)
	{
		forward=0;
	}
	//Current_SPEED=0;
	break;
case 70:
	CruiseControl_VoidSelectOption();  /* Button "2" */
	break;
case 71:
	CruiseControl_VoidIncOption();    /* Button "3" */
	break;
case 68:
	CruiseControl_VoidDecOption();    /* Button "4" */
	break;
case 64:
	TOGGLE_BIT(Light_Mode,0);  /* Button "5" */
	Mode_change=1;
	break;
case 67:
	TOGGLE_BIT(Sign_Mode,0);  /* Button "6" */
	break;
}
if (Mode_change==1)
{
u8 Modes = (Light_Mode << 1) + ACC_Mode ;
Modes=Modes+1;
	u8 message[4];
	message[0] = 'M';
	message[1] = (Modes % 10) + '0';
	message[2] = (Modes / 10) + '0';
	message[3] = '\0';
	MUSART3_VidTransmit(message);
	Mode_change=0;
}

}
