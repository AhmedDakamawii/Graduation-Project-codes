
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "RCC_interface.h"

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"


u32 MI2C_u32TxLen; 
u32 MI2C_u32RxLen; 
u8  MI2C_u8TxRx; 
u8  MI2C_u8SlaveAdd; 
u32 MI2C_u32RxSize; 
u8 *MI2C_u8RxBuffer;
u8 *MI2C_u8TxBuffer;
u32 Loc_u32Bin=0;


void MI2C_voidInit(  void )
{
	#if MI2C1_STATUS          ==      ON

	SET_BIT(MI2C1->CR1 , MI2C_SWRST );
	CLR_BIT(MI2C1->CR1 , MI2C_SWRST ); /* Not Under Reset */
	//MRCC_VidEnableClock(RCC_APB1,21);
	MGPIO_VidSetPinDirection(GPIOB,PIN6,OUT_SPEED_50MHZ_alternativeFUN_OD);
	MGPIO_VidSetPinDirection(GPIOB,PIN7,OUT_SPEED_50MHZ_alternativeFUN_OD);
	
	MI2C1->CR2 = 0b011001; /* Set Peripheral Clk Freq to 8 MHz */
	
	#if MI2C1_INTERRUPT_STATUS     ==     ON
	//MNVIC_VidEnableInterrupts(31);
	SET_BIT(MI2C1->CR2 , MI2C_ITBUFEN );
	SET_BIT(MI2C1->CR2 , MI2C_ITEVTEN );
	#endif
	
	

	//CLR_BIT(MI2C1->CR1 , MI2C_PE ); /* Disable Peripheral */
	//CLR_BIT(MI2C1->CR1 , MI2C_SMBUS ); /* Choose I2C not SMBUS */
	//CLR_BIT(MI2C1->CR1 , MI2C_ENPEC ); /* Packet Error Checking Disable */
	//CLR_BIT(MI2C1->CR1 , MI2C_PEC ); /* No Packet Error Checking Transfer */
	//CLR_BIT(MI2C1->CR1 , MI2C_SWRST ); /* Not Under Reset */
	
	
	CLR_BIT(MI2C1->OAR1 , MI2C_ADDMODE ); /* 7 Bit Address */
	SET_BIT(MI2C1->OAR1 , MI2C_RESERVED ); /* Should always be kept at 1*/
	
	//CLR_BIT(MI2C1->OAR2 , MI2C_ENDUAL ); /* Not Dual Address */
	
	/* CCR and TRISE Calculations*/
	#if  MI2C1_SCL_CLK        ==        MI2C_SCL_SM
	CLR_BIT(MI2C1->CCR , MI2C_F_S );
	#elif  MI2C1_SCL_CLK        ==        MI2C_SCL_FM_DUTY_2
	SET_BIT(MI2C1->CCR , MI2C_F_S );
	CLR_BIT(MI2C1->CCR , MI2C_DUTY );
	
	#elif  MI2C1_SCL_CLK        ==        MI2C_SCL_FM_DUTY_16_9
	SET_BIT(MI2C1->CCR , MI2C_F_S );
	SET_BIT(MI2C1->CCR , MI2C_DUTY );
	
	#endif
	
	if(MI2C1_SCL_CLK_SPEED <= 100000)
	{
		MI2C1->CCR = (F_CPU / ( 2 * MI2C1_SCL_CLK_SPEED ) );
		MI2C1->TRISE =  (( (F_CPU ) / 1000000U ) + 1) ;
	}
	else if(MI2C1_SCL_CLK_SPEED <= 200000)
	{
		MI2C1->CCR = (F_CPU / ( 3 * MI2C1_SCL_CLK_SPEED ) );
		MI2C1->TRISE =  (( (F_CPU * 3) / 10000000U ) + 1) ;
	}
	else
	{
		MI2C1->CCR = (F_CPU / ( 25 * MI2C1_SCL_CLK_SPEED ) );
		MI2C1->TRISE =  (( (F_CPU * 3) / 10000000U ) + 1) ;
	}
	
	SET_BIT(MI2C1->CR1 , MI2C_PE ); /* Enable Peripheral */
	
    #if MI2C1_ACK_STATUS           ==    ON
	SET_BIT(MI2C1->CR1 , MI2C_ACK );
	#endif

	#endif
	
	#if MI2C2_STATUS          ==      ON
	MRCC_VidEnableClock(RCC_APB1,22);
	MGPIO_VidSetPinDirection(GPIOB,PIN10,OUT_SPEED_50MHZ_alternativeFUN_OD);
	MGPIO_VidSetPinDirection(GPIOB,PIN11,OUT_SPEED_50MHZ_alternativeFUN_OD);
	
	#if MI2C2_INTERRUPT_STATUS     ==     ON
	MNVIC_VidEnableInterrupts(33);
	SET_BIT(MI2C2->CR2 , MI2C_ITBUFEN );
	SET_BIT(MI2C2->CR2 , MI2C_ITEVTEN );
	#endif
	
	#if MI2C2_ACK_STATUS           ==    ON
	SET_BIT(MI2C2->CR1 , MI2C_ACK );
	#endif
	
	CLR_BIT(MI2C2->OAR1 , MI2C_ADDMODE ); /* 7 Bit Address */
	SET_BIT(MI2C2->OAR1 , MI2C_RESERVED );
	
	#endif
}

void MI2C_voidStart( u8 Copy_u8I2CId )
{
	switch ( Copy_u8I2CId )
	{
		case MI2C_1 : SET_BIT(MI2C1->CR1 , MI2C_START );    break;
		case MI2C_2 : SET_BIT(MI2C2->CR1 , MI2C_START );    break;
		default: break;
	}
}
void MI2C_voidStop( u8 Copy_u8I2CId )
{
	switch ( Copy_u8I2CId )
	{
		case MI2C_1 : SET_BIT(MI2C1->CR1 , MI2C_STOP );    break;
		case MI2C_2 : SET_BIT(MI2C2->CR1 , MI2C_STOP );    break;
		default: break;
	}
}

void MI2C_voidSetOwnAddress(u8 Copy_u8OwnAddress)
{
	MI2C1->OAR1 &= ~( 0x7f << 1);
	MI2C1->OAR1 |=  (Copy_u8OwnAddress << 1);
}


/*
void MI2C_voidMasterTransmit( u8 Copy_u8I2CId , u8* Copy_u8TxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd )
{
	MI2C_voidStart(MI2C_1);
	while( ! GET_BIT(MI2C1->SR1,MI2C_SB) );
	MI2C1->DR = (Copy_u8SlaveAdd << 1) ;
	while( ! GET_BIT(MI2C1->SR1,MI2C_ADDR) );
	Loc_u32Bin = MI2C1->SR1;
	Loc_u32Bin = MI2C1->SR2;
	while(Copy_u32Len >0)
	{
		while( ! GET_BIT(MI2C1->SR1,MI2C_TXE) );
		MI2C1->DR = *(Copy_u8TxData);
		Copy_u8TxData++;
		Copy_u32Len--;
	}
	while( ! GET_BIT(MI2C1->SR1,MI2C_TXE) );
	while( ! GET_BIT(MI2C1->SR1,MI2C_BTF) );
	MI2C_voidStop(MI2C_1);
}
*/
void MI2C_voidMasterTransmit( u8  Copy_u8I2CId , u8 Copy_u8TxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd )
{
	MI2C_voidStart(MI2C_1);
	while(  ! GET_BIT(MI2C1->SR1,MI2C_SB) );
	MI2C1->DR = (Copy_u8SlaveAdd << 1) ;
 	while( ! GET_BIT(MI2C1->SR1,MI2C_ADDR) );
	Loc_u32Bin = MI2C1->SR1;
	Loc_u32Bin = MI2C1->SR2;
		while( ! GET_BIT(MI2C1->SR1,MI2C_TXE) );
		MI2C1->DR = Copy_u8TxData;
	while( ! GET_BIT(MI2C1->SR1,MI2C_TXE) );
	while( ! GET_BIT(MI2C1->SR1,MI2C_BTF) );
	MI2C_voidStop(MI2C_1);
}

void MI2C_voidMasterReceive(  u8 Copy_u8I2CId , u8* Copy_u8RxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd)
{
	//SET_BIT(MI2C1->CR1,MI2C_POS);
	SET_BIT(MI2C1->CR1,MI2C_ACK);
	MI2C_voidStart(MI2C_1);
	while( ! GET_BIT(MI2C1->SR1,MI2C_SB) );
	u8 Address = (Copy_u8SlaveAdd << 1);
	Address |= 1 ;
	MI2C1->DR = Address;
	while( ! GET_BIT(MI2C1->SR1,MI2C_ADDR) );
	Loc_u32Bin = MI2C1->SR1;
	Loc_u32Bin = MI2C1->SR2;
	while( ! GET_BIT(MI2C1->SR1,MI2C_BTF) );
	while( ! GET_BIT(MI2C1->SR1,MI2C_RXNE) );
	*(Copy_u8RxData)=MI2C1->DR ;
	CLR_BIT(MI2C1->CR1,MI2C_ACK);
	MI2C_voidStop(MI2C_1);
	Copy_u8RxData++;
	while( ! GET_BIT(MI2C1->SR1,MI2C_RXNE) );
	*(Copy_u8RxData)=MI2C1->DR ;

#if MI2C1_ACK_STATUS           ==    ON
SET_BIT(MI2C1->CR1 , MI2C_ACK );
#endif
}





















void MI2C_voidMasterTransmitIT( u8 Copy_u8I2CId , u8* Copy_u8TxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd )
{
	u8 Loc_u8Busy =0;
	switch ( Copy_u8I2CId )
	{
		case MI2C_1 :
		Loc_u8Busy = MI2C_u8TxRx;
		if( (Loc_u8Busy != I2C_BUSY_IN_TX) && (Loc_u8Busy != I2C_BUSY_IN_RX))
		{
		MI2C_u8TxBuffer = Copy_u8TxData;
		MI2C_u32TxLen = Copy_u32Len;
		MI2C_u8SlaveAdd = Copy_u8SlaveAdd;
		MI2C_u8TxRx = I2C_BUSY_IN_TX;
		MI2C_voidStart(MI2C_1);
		SET_BIT(MI2C1->CR2 , MI2C_ITBUFEN );
		SET_BIT(MI2C1->CR2 , MI2C_ITEVTEN );
		}
		break;
		case MI2C_2 : 
		
		break;
		default: break;
	}
}
void MI2C_voidMasterReceiveIT(  u8 Copy_u8I2CId , u8* Copy_u8RxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd )
{
	u8 Loc_u8Busy =0;
	switch ( Copy_u8I2CId )
	{
		case MI2C_1 :
		Loc_u8Busy =  MI2C_u8TxRx;
		if( (Loc_u8Busy != I2C_BUSY_IN_TX) && (Loc_u8Busy != I2C_BUSY_IN_RX))
		{
		MI2C_u8RxBuffer = Copy_u8RxData;
		MI2C_u32RxLen = Copy_u32Len;
		MI2C_u32RxSize = Copy_u32Len;
		MI2C_u8SlaveAdd = Copy_u8SlaveAdd;
		MI2C_u8TxRx = I2C_BUSY_IN_RX;
		MI2C_voidStart(MI2C_1);
		SET_BIT(MI2C1->CR2 , MI2C_ITBUFEN );
		SET_BIT(MI2C1->CR2 , MI2C_ITEVTEN );
		//MI2C_voidEnableInterrupt();
		}
		break;
		case MI2C_2 : 
		
		break;
		default: break;
	}
}

void I2C1_EV_IRQHandler(void)
{
	u8 Loc_u8EveEn = GET_BIT(MI2C1->CR2,MI2C_ITEVTEN);
	u8 Loc_u8BufEn = GET_BIT(MI2C1->CR2,MI2C_ITBUFEN);
	u8 Loc_u8Val = GET_BIT(MI2C1->SR1,MI2C_SB);
	u8 Loc_u8Val2 =0;
	u8 Address = 0;
	u32 Loc_u32Bin = 0;
	if(Loc_u8EveEn && Loc_u8Val)
	{
		Loc_u32Bin = MI2C1->SR1;
		if(MI2C_u8TxRx == I2C_BUSY_IN_TX)
		{
			MI2C1->DR = (MI2C_u8SlaveAdd << 1) ;
		}
		else if(MI2C_u8TxRx == I2C_BUSY_IN_RX)
		{
			if(MI2C_u32RxSize == 2)
			{
				SET_BIT(MI2C1->CR1,MI2C_POS);
			}
			Address = (MI2C_u8SlaveAdd << 1);
			Address |= 1 ;
			MI2C1->DR = Address;
		}
	}
	/**************************************************/
	Loc_u8Val2 = GET_BIT(MI2C1->SR1,MI2C_ADDR);
	if(Loc_u8EveEn && Loc_u8Val2)
	{
		if(GET_BIT(MI2C1->SR2,MI2C_MSL) == 1)
		{
			if(MI2C_u8TxRx == I2C_BUSY_IN_RX)
			{
				if(MI2C_u32RxSize == 1)
				{
					CLR_BIT(MI2C1->CR1 , MI2C_ACK );

					Loc_u32Bin = MI2C1->SR1;
					Loc_u32Bin = MI2C1->SR2;
				}
			}
			else if(MI2C_u8TxRx == I2C_BUSY_IN_TX)
			{
				Loc_u32Bin = MI2C1->SR1;
				Loc_u32Bin = MI2C1->SR2;

			}

		   if(MI2C_u8TxRx == I2C_BUSY_IN_RX)
		    {
		    	if(MI2C_u32RxSize == 2)
		    	{
					Loc_u32Bin = MI2C1->SR1;
					Loc_u32Bin = MI2C1->SR2;
		    		CLR_BIT(MI2C1->CR1 , MI2C_ACK );
		    	}
		    }
		}
		
	}
	/*****************************************************/
	
	Loc_u8Val = GET_BIT(MI2C1->SR1,MI2C_TXE);
	if( Loc_u8EveEn && Loc_u8Val && Loc_u8BufEn)
	{
		if(GET_BIT(MI2C1->SR2,MI2C_MSL) == 1)
		{
			if(MI2C_u8TxRx == I2C_BUSY_IN_TX)
			{
				if(MI2C_u32TxLen > 0)
				{
					MI2C1->DR = *(MI2C_u8TxBuffer);
					MI2C_u32TxLen--;
					MI2C_u8TxBuffer++;
			    }
			}
		}
	}
	
	/***************************************************/
	
	Loc_u8Val = GET_BIT(MI2C1->SR1,MI2C_BTF);
	Loc_u8Val2 = GET_BIT(MI2C1->SR1,MI2C_TXE);
	if( Loc_u8EveEn && Loc_u8Val )
	{
		if(MI2C_u8TxRx == I2C_BUSY_IN_TX)
		{
			if(Loc_u8Val2)
			{
				if(MI2C_u32TxLen == 0)
				{
					MI2C_voidStop(MI2C_1);
					MI2C_voidClearData();
				}
			}
		}
		
	}
	
	/*****************************************************/
	
	Loc_u8Val2 = GET_BIT(MI2C1->SR1,MI2C_RXNE);
	Loc_u8Val = GET_BIT(MI2C1->SR1,MI2C_BTF);
	if( Loc_u8EveEn && Loc_u8Val2 && Loc_u8BufEn)
	{
		if(GET_BIT(MI2C1->SR2,MI2C_MSL) == 1)
		{
			if(MI2C_u8TxRx == I2C_BUSY_IN_RX)
			{
				if(MI2C_u32RxSize == 1)
				{
					*(MI2C_u8RxBuffer) = MI2C1->DR;
					MI2C_u32RxLen--;
				}
				/*else if (MI2C_u32RxSize == 2)
				{
					CLR_BIT(MI2C1->CR1 , MI2C_ACK );
					MI2C_voidStop(MI2C_1);
					*(MI2C_u8RxBuffer) = MI2C1->DR;
					MI2C_u8RxBuffer++;
					//while (! GET_BIT(MI2C1->SR1,MI2C_BTF));
					Loc_u32Bin=MI2C1->SR1;
					*(MI2C_u8RxBuffer) = MI2C1->DR;
					MI2C_u32RxLen=0;
				}*/
				else if ( MI2C_u32RxSize > 1)
				{
					if( MI2C_u32RxLen == 2 )
					{
						CLR_BIT(MI2C1->CR1 , MI2C_ACK );

					}

					if(MI2C_u32RxSize == 2 )
					{
						MI2C_voidStop(MI2C_1);
						*(MI2C_u8RxBuffer) = MI2C1->DR;
						MI2C_u32RxLen--;
						MI2C_u8RxBuffer++;
					}

					*(MI2C_u8RxBuffer) = MI2C1->DR;
					MI2C_u32RxLen--;
					MI2C_u8RxBuffer++;
				}
				if( MI2C_u32RxLen == 0 )
				{
					//MI2C_voidStop(MI2C_1);
					MI2C_voidClearData();
					//MI2C_voidDisableInterrupt();
				}
			}
		}
		
	}
	/****************************************************/
	/*Loc_u8Val = GET_BIT(MI2C1->SR1,MI2C_BTF);
	Loc_u8Val2 = GET_BIT(MI2C1->SR1,MI2C_RXNE);
	if( Loc_u8EveEn && Loc_u8Val && Loc_u8Val2)
	{
		MI2C_voidStop(MI2C_1);
		*(MI2C_u8RxBuffer) = MI2C1->DR;
		MI2C_u8RxBuffer++;
		*(MI2C_u8RxBuffer) = MI2C1->DR;
		MI2C_voidClearData();
	}*/
	
}


static void MI2C_voidClearData(void)
{
	MI2C_u32TxLen=0; 
	MI2C_u32RxLen=0; 
	MI2C_u8TxRx=0; 
	MI2C_u8SlaveAdd=0; 
	MI2C_u32RxSize=0; 
	MI2C_u8RxBuffer = NULL; 
	MI2C_u8TxBuffer = NULL; 
	CLR_BIT(MI2C1->CR2 , MI2C_ITBUFEN );
	CLR_BIT(MI2C1->CR2 , MI2C_ITEVTEN );
	
	#if MI2C1_ACK_STATUS           ==    ON
	SET_BIT(MI2C1->CR1 , MI2C_ACK );
	#endif
}


void MI2C_voidDisableInterrupt (void)
{

	MNVIC_VidDisableInterrupts(31);
	CLR_BIT(MI2C1->CR2 , MI2C_ITBUFEN );
	CLR_BIT(MI2C1->CR2 , MI2C_ITEVTEN );
}
void MI2C_voidEnableInterrupt (void)
{

	#if MI2C1_INTERRUPT_STATUS     ==     ON
	MNVIC_VidEnableInterrupts(31);
	SET_BIT(MI2C1->CR2 , MI2C_ITBUFEN );
	SET_BIT(MI2C1->CR2 , MI2C_ITEVTEN );
	#endif
}

void MI2C_voidClearADDR(void)
{
	if(GET_BIT(MI2C1->SR2,MI2C_MSL) == 1)
		{
			if(MI2C_u8TxRx == I2C_BUSY_IN_RX)
			{
				if(MI2C_u32RxSize == 1)
					{
						CLR_BIT(MI2C1->CR1 , MI2C_ACK );

						Loc_u32Bin = MI2C1->SR1;
						Loc_u32Bin = MI2C1->SR2;
					}
			}
			else if(MI2C_u8TxRx == I2C_BUSY_IN_TX)
				{
					Loc_u32Bin = MI2C1->SR1;
					Loc_u32Bin = MI2C1->SR2;

				}
		}
}
