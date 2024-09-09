 /***************************************************************/
 /* Author :                                                    */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: Light System                                    */ 
/****************************************************************/
#ifndef _LS_INTER_H
#define _LS_INTER_H


void LS_VoidLightSystemINIT ();

void LS_VoidSetLightintensity (u8 Copy_1stledPwm , u8 Copy_2ndledPwm);

void FrontLight_voidTakeAction(void);



#define LED1_PIN1   1 //B1
#define LED1_PIN2   3//B3
#define LED2_PIN1   4 //B4
#define LED2_PIN2   5 //B5



#define CHANNEL_PWM_LED1 1
#define CHANNEL_PWM_LED2 2

#define LOW 0
#define HIGH 1

#endif
