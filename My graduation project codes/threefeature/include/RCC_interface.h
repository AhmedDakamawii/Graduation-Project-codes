 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
/****************************************************************/
#ifndef _RCC_INTER_H
#define _RCC_INTER_H

#define RCC_AHB 0
#define RCC_APB1 1
#define RCC_APB2 2

void MRCC_VidInitSysClock(void);
void MRCC_VidEnableClock (u8 Copy_u8BusId ,u8 Copy_u8BusPerId );
void MRCC_VidDisableClock (u8 Copy_u8BusId ,u8 Copy_u8BusPerId );






#endif
