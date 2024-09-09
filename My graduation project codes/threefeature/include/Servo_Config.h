/***************************************************/
/* Author  : Reem Alaa                             */
/* Date    : 17/8/2023                             */
/* Version : V01                                   */
/***************************************************/
#ifndef SERVO_CONFIG_H
#define SERVO_CONFIG_H

// The Number OF Servo Motors To Be Used In The Project
#define SERVO_NUM  2

#define SERVO_Motor1  0
#define SERVO_Motor2  1

//choose the port
#define SERVO_Motor1_PORT GPIOA
#define SERVO_Motor2_PORT GPIOA

//choose the pin
#define SERVO_Motor1_PIN 8
#define SERVO_Motor2_PIN 9

//choose the channel for pwm
#define SERVO_Motor1_PWMCHANNEL 0
#define SERVO_Motor2_PWMCHANNEL 1



#endif
