 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: STK                                            */ 
/****************************************************************/
#ifndef _STK_PRIV_H
#define _STK_PRIV_H
 
#include "STD_TYPES.h"

 /*STK Registers*/
 typedef struct
{
	volatile u32 CTRL  ;
	volatile u32 LOAD  ;
	volatile u32 VAL   ;
	volatile u32 CALIB   ;
}MSTK_Type;

#define     MSTK    ((volatile MSTK_Type*)0xE000E010)

//options for frequency
#define STK_AHB_DIV8   0
#define STK_AHB   1

#define     MSTK_SINGLE_INTERVAL    0
#define     MSTK_PERIOD_INTERVAL    1
 
#endif
