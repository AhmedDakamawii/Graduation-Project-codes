/******************************************************************************
 *
 * Module: ultrasonic
 *
 * File Name: ultrasonic_interface.h
 *
 * Description: interface header file for the ultrasonic driver
 *
 * Author: Rawan Mohamed
 *
 *******************************************************************************/
 #ifndef ULTRASONIC_INTERFACE_H
#define ULTRASONIC_INTERFACE_H
 
 #include "STD_TYPES.h"
 
 /*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description:
 * Initialize the ICU driver as required.
 *Setup the ICU call back function.
 * Setup the direction for the trigger pin as output pin through the GPIO driver
 */
void Ultrasonic_voidInit(void);
/*
 * Description:
 * Send the trigger pulse by using Ultrasonic_Trigger function.
 *Start the measurements by the ICU from this moment.
 */
u16 Ultrasonic_u16ReadDistance(void);

 #endif
