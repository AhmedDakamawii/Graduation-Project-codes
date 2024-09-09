 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: NVIC                                            */ 
/****************************************************************/
#ifndef _NVIC_PRIV_H
#define _NVIC_PRIV_H
 
 /*NVIC Registers*/
 /*base address 0xE000E100*/
 
 #define    NVIC_ISER0   *((volatile u32*)0xE000E100) /*enable external intrupts from 0  to 31*/
 #define    NVIC_ISER1   *((volatile u32*)0xE000E104) /*enable external intrupts from 32 to 63*/
 #define    NVIC_ICER0   *((volatile u32*)0xE000E180) /*disable external intrupts from 0 to 31*/
 #define    NVIC_ICER1   *((volatile u32*)0xE000E184) /*disable external intrupts from 32 to 63*/
 
 #define    NVIC_ISPR0   *((volatile u32*)0xE000E200) /*SET PENDING FLAG from 0 to 31*/
 #define    NVIC_ISPR1   *((volatile u32*)0xE000E204) /*SET PENDING FLAG from 32 to 63*/
 #define    NVIC_ICPR0   *((volatile u32*)0xE000E280) /*CLEAR PENDING FLAG from 0 to 31*/
 #define    NVIC_ICPR1   *((volatile u32*)0xE000E284) /*CLEAR PENDING FLAG from 32 to 63*/
 
 #define    NVIC_IABR0   *((volatile u32*)0xE000E300) /*READ ACTIVE FLAG from 0 to 31*/
 #define    NVIC_IABR1   *((volatile u32*)0xE000E304) /*READ ACTIVE FLAG from 32 to 63*/
 
 #define    NVIC_IPR     ((volatile u8*)0xE000E400) /*to divide the regisres into bytes*/
 
 #define    SCB_AIRCR   *((volatile u32*)0xE000ED0C) /*to determine number of bit used for group priorty and for sub priorty*/


#endif