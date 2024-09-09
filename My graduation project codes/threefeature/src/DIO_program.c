 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: GPIO                                            */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_confg.h"

void MGPIO_VidSetPinDirection (u8 Copy_u8PORT, u8 Copy_u8PIN , u8 Copy_u8MODE)
{
	switch (Copy_u8PORT)
	{
		case GPIOA:
		 if ( Copy_u8PIN <= 7 )
		 {
			 /*WE SHOULD PUT ZEROS FIRST AT THE FOUR BITS OF OUR PIN THEN PUT THE NEW VALUE */
			GPIOA_CRL &= ~((0b1111)<<(Copy_u8PIN*4));
			GPIOA_CRL |= (Copy_u8MODE<<(Copy_u8PIN*4));
		 }
		else if (Copy_u8PIN <= 15 )
		{
			Copy_u8PIN = Copy_u8PIN - 8;
			GPIOA_CRH &= ~((0b1111) << (Copy_u8PIN*4 ));
			GPIOA_CRH |= ( Copy_u8MODE <<(Copy_u8PIN*4));
		}
		break;
		case GPIOB:
		 if (Copy_u8PIN <= 7 )
		 {
			GPIOB_CRL &= ~((0b1111)<<(Copy_u8PIN*4));
			GPIOB_CRL |= (Copy_u8MODE<<(Copy_u8PIN*4));
		 }
			else if (Copy_u8PIN <= 15 ) 
		{
						Copy_u8PIN = Copy_u8PIN - 8;
		    GPIOB_CRH &= ~((0b1111) << (Copy_u8PIN*4));
			GPIOB_CRH |= (Copy_u8MODE << (Copy_u8PIN*4) );
		}
		
		break;
		case GPIOC:
		 if (Copy_u8PIN <= 7 )
		 {
			GPIOC_CRL &= ~((0b1111)<<(Copy_u8PIN*4));
			GPIOC_CRL |= (Copy_u8MODE<<(Copy_u8PIN*4));
		 }
		 	else if (Copy_u8PIN <= 15 &&  Copy_u8PIN >= 8) 
		{
						Copy_u8PIN = Copy_u8PIN-8;
			GPIOC_CRH &= ~((0b1111)<<(Copy_u8PIN*4));
			GPIOC_CRH |= (Copy_u8MODE<<(Copy_u8PIN*4));
		}
		
		break;
		default: break;
		
	}
	
	
}

void MGPIO_VidSetPinValue (u8 Copy_u8PORT, u8 Copy_u8PIN , u8 Copy_u8VALUE)
{
	switch (Copy_u8PORT)
	{
		case GPIOA: 
		 if (Copy_u8VALUE == GPIO_HIGH )
		 {
			SET_BIT(GPIOA_ODR,Copy_u8PIN);
		 }
		else if (Copy_u8VALUE == GPIO_LOW)
		{
			CLR_BIT(GPIOA_ODR,Copy_u8PIN);
		}
		break;
		case GPIOB:
		 if (Copy_u8VALUE == GPIO_HIGH )
		 {
			SET_BIT(GPIOB_ODR,Copy_u8PIN);
		 }
		else if (Copy_u8VALUE == GPIO_LOW)
		{
			CLR_BIT(GPIOB_ODR,Copy_u8PIN);
		}
		
		break;
		case GPIOC:
		 if (Copy_u8VALUE == GPIO_HIGH )
		 {
			SET_BIT(GPIOC_ODR,Copy_u8PIN);
		 }
		else if (Copy_u8VALUE == GPIO_LOW)
		{
			CLR_BIT(GPIOC_ODR,Copy_u8PIN);
		}
		
		break;
		default: break;
		
	}
	
	
}

u8 MGPIO_U8GetPinValue (u8 Copy_u8PORT, u8 Copy_u8PIN)
{
	u8 LOC_U8value=0;
	switch (Copy_u8PORT)
	{
	
		case GPIOA: 
		LOC_U8value=GET_BIT(GPIOA_IDR,Copy_u8PIN);
		break;
		case GPIOB:
		LOC_U8value=GET_BIT(GPIOB_IDR,Copy_u8PIN);
		break;
		case GPIOC:
		LOC_U8value=GET_BIT(GPIOC_IDR,Copy_u8PIN);
		break;
		default: break;

	}
	 
					return LOC_U8value;

}

void MGPIO_VidSetPinFaster (u8 Copy_u8PORT, u8 Copy_u8PIN )
{
	switch (Copy_u8PORT)
	{
	
		case GPIOA: 
		GPIOA_BSRR=(1<<Copy_u8PIN);
		break;
		case GPIOB:
		GPIOB_BSRR=(1<<Copy_u8PIN);
		break;
		case GPIOC:
		GPIOC_BSRR=(1<<Copy_u8PIN);
		break;
		default: break;

	}
}
void MGPIO_VidResetPinFaster (u8 Copy_u8PORT, u8 Copy_u8PIN )
{
		switch (Copy_u8PORT)
	{
	
		case GPIOA: 
		GPIOA_BRR=(1<<Copy_u8PIN);
		break;
		case GPIOB:
		GPIOB_BRR=(1<<Copy_u8PIN);
		break;
		case GPIOC:
		GPIOC_BRR=(1<<Copy_u8PIN);
		break;
		default: break;

	}
}
void MGPIO_VidLockPin (u8 Copy_u8PORT, u8 Copy_u8PIN )
{
		switch (Copy_u8PORT)
	{
	
		case GPIOA: 
		GPIOA_LCKR=(1<<Copy_u8PIN);
		break;
		case GPIOB:
		GPIOB_LCKR=(1<<Copy_u8PIN);
		break;
		case GPIOC:
		GPIOC_LCKR=(1<<Copy_u8PIN);
		break;
		default: break;

	}
}



void MGPIO_voidSetPortDirection( u8 Copy_u8Port , u8 Copy_u8Mode )
{
	/* According to Port Input go to GPIOx_CRL and GPIOx_CRH */
	switch(Copy_u8Port)
	{
	case GPIOA :
		GPIOA_CRL =  0x00000000;
		GPIOA_CRH =  0x00000000;                 /* Reset Value of Registers  */
		GPIOA_CRL = Copy_u8Mode * 0x11111111;    /* Add Mode Input (New Value) in each 4 Configuration Bits */
		GPIOA_CRH = Copy_u8Mode * 0x11111111;
	break;
	case GPIOB :
		GPIOB_CRL =  0x00000000;
		GPIOB_CRH =  0x00000000;                 /* Reset Value of Registers  */
		GPIOB_CRL = Copy_u8Mode * 0x11111111;    /* Add Mode Input (New Value) in each 4 Configuration Bits */
		GPIOB_CRH = Copy_u8Mode * 0x11111111;

	break;
	case GPIOC :
		GPIOC_CRL =  0x00000000;
		GPIOC_CRH =  0x00000000;                 /* Reset Value of Registers  */
		GPIOC_CRL = Copy_u8Mode * 0x11111111;    /* Add Mode Input (New Value) in each 4 Configuration Bits */
		GPIOC_CRH = Copy_u8Mode * 0x11111111;

	break;
	default : /* Return ERROR */ break;
	}
}

