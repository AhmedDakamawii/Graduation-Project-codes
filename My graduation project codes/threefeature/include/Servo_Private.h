/*************************************************/
/* Author : Reem Alaa                            */
/*Date : 17/8/2023                               */
/*Version : V01                                  */
/*************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/********************************REGISTER DEFINITION*************************/
#define RCC_CR             *((u32*)0x40021000) /*CONTROL CLOCK ENTERING PROSCESSOR HSI,HSE,PLL*/
#define RCC_CFGR           *((u32*)0x40021004) /*CONTROL CLOCK ENTERING PROSCESSOR HSI,HSE,PLL*/
#define RCC_CIR            *((u32*)0x40021008)
#define RCC_APB2RSTR       *((u32*)0x4002100C)
#define RCC_APB1RSTR       *((u32*)0x40021010)
#define RCC_AHBENR         *((u32*)0x40021014) /*CONTROL CLOCK EN/DIS CLOCK ON PERIPHRAL*/
#define RCC_APB2ENR        *((u32*)0x40021018) /*CONTROL CLOCK EN/DIS CLOCK ON PERIPHRAL*/
#define RCC_APB1ENR        *((u32*)0x4002101C) /*CONTROL CLOCK EN/DIS CLOCK ON PERIPHRAL*/
#define RCC_BDCR           *((u32*)0x40021020)
#define RCC_CSR            *((u32*)0x40021024)


#endif
