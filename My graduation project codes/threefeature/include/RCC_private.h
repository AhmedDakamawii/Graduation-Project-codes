 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
/****************************************************************/
#ifndef _RCC_PRIV_H
#define _RCC_PRIV_H

/* Register Definitions */
#define RCC_CR          *((volatile u32*)0x40021000) /*FOR CHOOSING CLK TYPE FOR MC*/
#define RCC_CFGR        *((volatile u32*)0x40021004) /*FOR CHOOSING CLK TYPE FOR MC*/
#define RCC_CIR         *((volatile u32*)0x40021008) 
#define RCC_APB2RSTR    *((volatile u32*)0x4002100C)
#define RCC_APB1RSTR    *((volatile u32*)0x40021010)
#define RCC_AHBENR      *((volatile u32*)0x40021014) /*FOR EN OR DIS CLOCK ON prefirals on AHB*/
#define RCC_APB2ENR     *((volatile u32*)0x40021018) /*FOR EN OR DIS CLOCK ON prefirals ON APB2*/
#define RCC_APB1ENR     *((volatile u32*)0x4002101C) /*FOR EN OR DIS CLOCK ON prefirals ON APB1*/
#define RCC_BDCR        *((volatile u32*)0x40021020)
#define RCC_CSR         *((volatile u32*)0x40021024)

/*TYPE OF SYS CLOCK*/
#define RCC_HSE_CRYSTAL 0
#define RCC_HSE_RC 1
#define RCC_HSI 2
#define RCC_PLL 3

/*TYPE OF PLL CLK*/
#define PLL_HSI_DIV2 0
#define PLL_HSE 1
#define PLL_HSE_DIV2 2



#endif