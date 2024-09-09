 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: EXTI                                           */ 
/****************************************************************/
#ifndef _EXTI_INTER_H
#define _EXTI_INTER_H

void MEXTI_VidInit();
void MEXTI_VidEnableEXTI(u8 Copy_Line);
void MEXTI_VidDisableEXTI(u8 Copy_Line);
void MEXTI_VidSoftwareTrigger(u8 Copy_Line);
void MEXTI_VidSetSignalLatch(u8 Copy_Line ,u8 Copy_Mode);
void MEXTI0_VidSetCallBack(void (*Ptr)(void));
void MEXTI1_VidSetCallBack(void (*Ptr)(void));
void MEXTI2_VidSetCallBack(void (*Ptr)(void));


//modes for any external intterupt
#define RASING    0
#define FALLING   1
#define ON_CHANGE 2




#endif
