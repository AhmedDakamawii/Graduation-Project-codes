 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: NVIC                                           */ 
/****************************************************************/
#ifndef _NVIC_INTER_H
#define _NVIC_INTER_H

void MNVIC_VidEnableInterrupts (u8 Copy_InterruptNum);
void MNVIC_VidDisableInterrupts (u8 Copy_InterruptNum);
void MNVIC_VidSetPendingFlag (u8 Copy_InterruptNum);
void MNVIC_VidClearPendingFlag (u8 Copy_InterruptNum);
u8 MNVIC_U8GetActiveFlag (u8 Copy_InterruptNum);
void MNVIC_VidSetPriorty (s8 Copy_ID , u8 Copy_GroupPriorty , u8 Copy_SubPriorty , u32 Copy_GroupNum );



#define NVIC_GROUP4_SUB0 0x05FA0300 /*4 bits for group (IPR)-> group*/
#define NVIC_GROUP3_SUB1 0x05FA0400 /*3 bits for group 1 bit for sub*/
#define NVIC_GROUP2_SUB2 0x05FA0500 /*2 bits for group 2 bit for sub*/
#define NVIC_GROUP1_SUB3 0x05FA0600 /*1 bits for group 3 bit for sub*/
#define NVIC_GROUP0_SUB4 0x05FA0700 /*0 bits for group 4 bit for sub*/





#endif
