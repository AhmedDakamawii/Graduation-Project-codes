 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: RCC                                             */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_confg.h"

void MRCC_VidInitSysClock(void)
{
	//enable all the clks in all cases
	
#if RCC_SYS_CLK== RCC_HSE_CRYSTAL
 RCC_CR =0x01010001;   //no bypass as crystal
RCC_CFGR=0x00000001;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif RCC_SYS_CLK== RCC_HSE_RC
  RCC_CR=0x01050001;   // bypass as RC
RCC_CFGR=0x00000001;  // no output clk and processor clk speed = AHB=APB1=APB2




#elif RCC_SYS_CLK== RCC_HSI
  RCC_CR=0x01010081; //enable 5 bits of termination by 10000 and but it = 0
RCC_CFGR=0x00000000;  // no output clk and processor clk speed = AHB=APB1=APB2



#elif RCC_SYS_CLK== RCC_PLL
RCC_CR=0x01010001;

/* if we choose PLL WITH HSI/2 type */

#if PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 2
RCC_CFGR=0x00000002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 3
RCC_CFGR=0x00040002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 4
RCC_CFGR=0x00080002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 5
RCC_CFGR=0x000C0002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 6
RCC_CFGR=0x00100002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 7
RCC_CFGR=0x00140002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 8
RCC_CFGR=0x00180002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 9
RCC_CFGR=0x001C0002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 10
RCC_CFGR=0x00200002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSI_DIV2 && PLL_MUL_VAL == 11
RCC_CFGR=0x00240002;  // no output clk and processor clk speed = AHB=APB1=APB2

/* if we choose PLL WITH HSE type */
#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 2 
RCC_CFGR=0x00010002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 3 
RCC_CFGR=0x00050002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 4 
RCC_CFGR=0x00090002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 5
RCC_CFGR=0x000D0002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 6
RCC_CFGR=0x00110002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 7
RCC_CFGR=0x00150002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 8
RCC_CFGR=0x00190002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 9
RCC_CFGR=0x001D0002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 10
RCC_CFGR=0x00210002;  // no output clk and processor clk speed= AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE && PLL_MUL_VAL == 11
RCC_CFGR=0x00250002;  // no output clk and processor clk speed= AHB=APB1=APB2
/* if we choose PLL WITH HSE/2 type */

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 2
RCC_CFGR=0x00030002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 3
RCC_CFGR=0x00070002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 4
RCC_CFGR=0x000B0002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 5
RCC_CFGR=0x000F0002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 6
RCC_CFGR=0x00130002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 7
RCC_CFGR=0x00170002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 8
RCC_CFGR=0x001B0002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 9
RCC_CFGR=0x001F0002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 10
RCC_CFGR=0x00230002;  // no output clk and processor clk speed = AHB=APB1=APB2

#elif PLL_clk_type ==  PLL_HSE_DIV2 && PLL_MUL_VAL == 11
RCC_CFGR=0x00270002;  // no output clk and processor clk speed = AHB=APB1=APB2

#endif


#endif
}

void MRCC_VidEnableClock (u8 Copy_u8BusId ,u8 Copy_u8PerId )
{
if (Copy_u8PerId <= 31)
{
switch(Copy_u8BusId)
{
case RCC_AHB:
SET_BIT(RCC_AHBENR,Copy_u8PerId);
break;
case RCC_APB1:
SET_BIT(RCC_APB1ENR,Copy_u8PerId);
break;
case RCC_APB2:
SET_BIT(RCC_APB2ENR,Copy_u8PerId);
break;

}
}

}



void MRCC_VidDisableClock (u8 Copy_u8BusId ,u8 Copy_u8PerId )
{
if (Copy_u8PerId <= 31)
{
switch(Copy_u8BusId)
{
case RCC_AHB:
CLR_BIT(RCC_AHBENR,Copy_u8PerId);
break;
case RCC_APB1:
CLR_BIT(RCC_APB1ENR,Copy_u8PerId);
break;
case RCC_APB2:
CLR_BIT(RCC_APB2ENR,Copy_u8PerId);
break;

}
}

}


