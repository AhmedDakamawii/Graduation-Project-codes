 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
/****************************************************************/
#ifndef _RCC_CONFG_H
#define _RCC_CONFG_H

//choose sys clk
#define RCC_SYS_CLK      RCC_HSE_CRYSTAL


//if you choose PLL choose type of PLL clk and the value of MUL
#if  RCC_SYS_CLK == RCC_PLL

#define PLL_clk_type      PLL_HSE_DIV2

#define PLL_MUL_VAL      4


#endif

#endif