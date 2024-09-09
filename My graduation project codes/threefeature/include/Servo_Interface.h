/*************************************************/
/* Author : Reem Alaa                            */
/*Date : 17/8/2023                               */
/*Version : V01                                  */
/*************************************************/
#ifndef SERVO_ITERFACE_H
#define SERVO_ITERFACE_H

#include "STD_TYPES.h"



void SERVO1_Init(void);
void SERVO2_Init(void);
void SERVO1_Direction(u16 Duty_Cycle1);
void SERVO2_Direction(u16 Duty_Cycle2);


//options for percentage of rotation
#define Left_Position    2000
#define Center_Position  1200
#define Right_Position   640

#endif
