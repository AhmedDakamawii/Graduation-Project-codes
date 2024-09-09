/******************************************************************************
 *
 * Module: ultrasonic
 *
 * File Name: ultrasonic_config.h
 *
 * Description: config header file for the ultrasonic driver
 *
 * Author: Rawan Mohamed
 *
 *******************************************************************************/
 #ifndef ULTRASONIC_CONFIG_H
 #define ULTRASONIC_CONFIG_H
 
 #define ULTRASONIC_PORT_ID        GPIOB
 
 #define ULTRASONIC_PIN_ID         PIN12
 
 
 /* Sound velocity = 340.00 m/s = 34000 cm/s
 *The distance of Object (in cm) = 340000*Time/2 = 17000 * Time
 * the timer gets incremented after FCPU/ PRESCALER (assume 1 us) time elapse.
 * 17000 x (TIMER value) x FCPU/ PRESCALER (assume 1 x 10^-6) cm
 * (TIMER value) / 58.8 cm (CALCULATED_VALUE) */
 
 #define CALCULATED_VALUE         59
 
 #endif
