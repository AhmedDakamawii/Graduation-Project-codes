/******************************************************************************
 *
 * Module: ultrasonic
 *
 * File Name: ultrasonic_program.c
 *
 * Description: program source file for the ultrasonic driver
 *
 * Author: Rawan Mohamed.
 *
 *******************************************************************************/
#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "ultrasonic_interface.h"
#include  "ultrasonic_config.h"
#include  "TIMER_interface.h"
#include  "DIO_interface.h"
#include  "STK_interface.h"
#include  "NVIC_interface.h"

volatile u32 dist =0;

void Ultrasonic_voidInit(void){
	/*Setup the direction for pin as input pin through the GPIO driver*/
	MGPIO_VidSetPinDirection(GPIOB,PIN8,INPUT_FLOATING);

	/*Tim4 */
	MNVIC_VidEnableInterrupts(30);

	MTIM4_voidICUInit();
	/*Setup the direction for the trigger pin as output pin through the GPIO driver*/
	MGPIO_VidSetPinDirection(ULTRASONIC_PORT_ID,ULTRASONIC_PIN_ID,OUT_SPEED_50MHZ_PUSHPULL);

}

u16 Ultrasonic_u16ReadDistance(void){
	/*Send the Trigger pulse to the ultrasonic.*/
	MGPIO_VidSetPinValue(ULTRASONIC_PORT_ID,ULTRASONIC_PIN_ID,GPIO_HIGH);
	MTIM3_voidSetBusyWaitus(40);
	MGPIO_VidSetPinValue(ULTRASONIC_PORT_ID,ULTRASONIC_PIN_ID,GPIO_LOW);

	// Wait for the measurement to complete
	MTIM3_voidSetBusyWaitus(200000);

	dist = MTIM4_GetDistance();

	return dist;
}

