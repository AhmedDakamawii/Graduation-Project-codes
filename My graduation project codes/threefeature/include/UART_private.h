 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: UART                                           */ 
/****************************************************************/
#ifndef _UART_PRIV_H
#define _UART_PRIV_H
 
 /*UART Registers*/
 
typedef struct{
	 volatile u32 SR ;
	 volatile u32 DR ;
	 volatile u32 BRR ;
	 volatile u32 CR1 ;
	 volatile u32 CR2 ;
	 volatile u32 CR3 ;
	 volatile u32 GTPR ;
	
 } MUART1_t;
 
 #define MUSART1 ((volatile MUART1_t *)0x40013800)
 #define MUSART2 ((volatile MUART1_t *)0x40004400)
#define MUSART3 ((volatile MUART1_t *)0x40004800)
 
  
#endif
