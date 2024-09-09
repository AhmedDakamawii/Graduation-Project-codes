 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: GPIO                                            */ 
/****************************************************************/
#ifndef _DIO_INTER_H
#define _DIO_INTER_H


#define GPIOA  0
#define GPIOB  1
#define GPIOC  2


#define GPIO_HIGH  1
#define GPIO_LOW   0



#define PIN0  0
#define PIN1  1
#define PIN2  2
#define PIN3  3
#define PIN4  4
#define PIN5  5
#define PIN6  6
#define PIN7  7
#define PIN8  8
#define PIN9  9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

/*if the direction is output pin*/ 

#define OUT_SPEED_10MHZ_PUSHPULL           0b0001
#define OUT_SPEED_10MHZ_opendrain          0b0101
#define OUT_SPEED_10MHZ_alternativeFUN_PP  0b1001
#define OUT_SPEED_10MHZ_alternativeFUN_OD  0b1101

#define OUT_SPEED_2MHZ_PUSHPULL           0b0010
#define OUT_SPEED_2MHZ_opendrain          0b0110
#define OUT_SPEED_2MHZ_alternativeFUN_PP  0b1010
#define OUT_SPEED_2MHZ_alternativeFUN_OD  0b1110

#define OUT_SPEED_50MHZ_PUSHPULL           0b0011
#define OUT_SPEED_50MHZ_opendrain          0b0111
#define OUT_SPEED_50MHZ_alternativeFUN_PP  0b1011
#define OUT_SPEED_50MHZ_alternativeFUN_OD  0b1111

/*if the direction is input pin*/ 
#define INPUT_ANALOG            0b0000
#define INPUT_FLOATING          0b0100
#define INPUT_PULLUPDOWN        0b1000

/*FUNCTIONS*/
void MGPIO_VidSetPinDirection (u8 Copy_u8PORT, u8 Copy_u8PIN , u8 Copy_u8MODE);
void MGPIO_VidSetPinValue (u8 Copy_u8PORT, u8 Copy_u8PIN , u8 Copy_u8VALUE);
u8 MGPIO_U8GetPinValue (u8 Copy_u8PORT, u8 Copy_u8PIN);
void MGPIO_VidSetPinFaster (u8 Copy_u8PORT, u8 Copy_u8PIN );
void MGPIO_VidResetPinFaster (u8 Copy_u8PORT, u8 Copy_u8PIN );
void MGPIO_VidLockPin (u8 Copy_u8PORT, u8 Copy_u8PIN );
void MGPIO_voidSetPortDirection( u8 Copy_u8Port , u8 Copy_u8Mode );







#endif
