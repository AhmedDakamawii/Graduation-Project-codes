 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: UART                                            */ 
/****************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_confg.h"

void (*UART1_CallBack)(u8);
void (*UART2_CallBack)(u8);
void (*UART3_CallBack)(u8);
void MUSART1_VidInit(void)
 {
	 	/*	baud rate = 9600      BRR=0x341	*//*for bootloader and uart*/
	 	/*	baud rate = 115200    BRR=0x45	*//*for wifi*/
		/*WE choose 115200*/
		MUSART2->BRR = 0x341;
		/* Clearing status register */
		MUSART2 -> SR = 0;

		/*ENABLE OR DISABLE USART*/
		#if  USART1_ENABLE == ON
	 SET_BIT(MUSART1 -> CR1 , 13);
	 #elif  USART1_ENABLE == OFF
	 	 CLR_BIT(MUSART1 -> CR1 , 13);
	 #endif

	 	/*8 BITS OR 9 BITS*/
 #if    USART1_WORD_LENGTH     ==  USART1_8_BITS
		 	 	 CLR_BIT(MUSART2 -> CR1 , 12);
#elif   USART1_WORD_LENGTH     ==  USART1_9_BITS
	 	 SET_BIT(MUSART1 -> CR1 , 12);
	 #endif

 /*Parity control enable*/
 #if    USART2_PARITY_ENABLE   ==   ON
	 	 	 SET_BIT(MUSART1 -> CR1 , 10);
#if  USART1_PARITY_TYPE==USART1_EVEN
		 	 	 CLR_BIT(MUSART1 -> CR1 , 9);
#elif  USART1_PARITY_TYPE==USART1_ODD
		 SET_BIT(MUSART1 -> CR1 , 9);
	#endif
#elif  USART1_PARITY_ENABLE == OFF
	 	 	 CLR_BIT(MUSART1 -> CR1 , 10);
	 #endif
	 /*transmitter enable*/
 #if    USART1_TRANSMITTER_ENABLE  ==   ON
	 		 SET_BIT(MUSART1 -> CR1 , 3);
 #elif  USART2_TRANSMITTER_ENABLE == OFF
	 	 	CLR_BIT(MUSART1 -> CR1 , 3);
	 #endif

	  /*receiver enable*/
 #if    USART1_RECEIVER_ENABLE  ==   ON
	 		 SET_BIT(MUSART1 -> CR1 , 2);
 #elif  USART1_RECEIVER_ENABLE == OFF
	 	 	CLR_BIT(MUSART1 -> CR1 , 2);
	 #endif

	   /*STOP BIT NUMBER */
 #if    USART1_STOPBIT_NUMBER  ==  USART1_ONE_STOP
	 	 	 CLR_BIT(MUSART1 -> CR2 , 12);
	 	 	 CLR_BIT(MUSART1 -> CR2 , 13);

 #elif  USART1_STOPBIT_NUMBER ==   USART1_TWO_STOP
  CLR_BIT(MUSART1 -> CR2 , 12);
  SET_BIT(MUSART1 -> CR2 , 13);
	 #endif


 }
 void MUSART1_VidTransmit(u8 Copy_Transmit[])
 {
	 u8 i =0;
	 while (Copy_Transmit[i] != '\0')
	 {
		 MUSART1->DR=Copy_Transmit[i];
		 /*Wait till transmition is ended*/
		 while (GET_BIT( MUSART1->SR ,6 )==0)
		 {
			 ;
		 }
		 i++;
	 }
 }
 u8 MUSART1_U8Receive(void)
 {
	 
	 u8 Loc_u8ReceivedData=0;
	 u32 timeout=0;
	 /*Wait till receive is ended*/
		 while (GET_BIT( MUSART1->SR ,5 )==0)
		 {
			 timeout++;
			 if (timeout==3000000)
			 {
				 Loc_u8ReceivedData=255;
				 break;
			 }
		 }
		 if (Loc_u8ReceivedData==0)
		 {
	 Loc_u8ReceivedData = MUSART1 -> DR;
		 }
	return (Loc_u8ReceivedData);
	 
	 
 }
  u8 MUSART1_U8ReceiveBootLoader(u8* Copy_u8Data)
{
	u8 Local_u8Result = 1;

	if ( (GET_BIT((MUSART1 -> SR), 5)) == 1 )
	{
		*Copy_u8Data = MUSART1 -> DR;
	}
	else
	{
		Local_u8Result = 0;
	}
	
	return (Local_u8Result);
}
 

 void MUSART2_VidInit(void)
 {
	 	/*	baud rate = 9600      BRR=0x341	*//*for bootloader and uart*/
	 	/*	baud rate = 115200    BRR=0x45	*//*for wifi*/
		/*WE choose 115200*/
		MUSART2->BRR = 0x341;
		/* Clearing status register */
		MUSART2 -> SR = 0;
	 
		/*ENABLE OR DISABLE USART*/
		#if  USART2_ENABLE == ON
	 SET_BIT(MUSART2 -> CR1 , 13);
	 #elif  USART2_ENABLE == OFF
	 	 CLR_BIT(MUSART2 -> CR1 , 13) ;
	 #endif
	 
	 	/*8 BITS OR 9 BITS*/
 #if    USART2_WORD_LENGTH     ==  USART1_8_BITS  
		 	 	 CLR_BIT(MUSART2 -> CR1 , 12);
#elif   USART2_WORD_LENGTH     ==  USART1_9_BITS  
	 	 SET_BIT(MUSART2 -> CR1 , 12);
	 #endif
	 
 /*Parity control enable*/
 #if    USART2_PARITY_ENABLE   ==   ON  		
	 	 	 SET_BIT(MUSART2 -> CR1 , 10);
#if  USART2_PARITY_TYPE==USART1_EVEN
		 	 	 CLR_BIT(MUSART2 -> CR1 , 9);
#elif  USART2_PARITY_TYPE==USART1_ODD
		 SET_BIT(MUSART2 -> CR1 , 9);
	#endif
#elif  USART2_PARITY_ENABLE == OFF
	 	 	 CLR_BIT(MUSART2 -> CR1 , 10);
	 #endif
	 /*transmitter enable*/
 #if    USART2_TRANSMITTER_ENABLE  ==   ON  
	 		 SET_BIT(MUSART2 -> CR1 , 3);
 #elif  USART2_TRANSMITTER_ENABLE == OFF
	 	 	CLR_BIT(MUSART2 -> CR1 , 3);
	 #endif
	 
	  /*receiver enable*/
 #if    USART2_RECEIVER_ENABLE  ==   ON  
	 		 SET_BIT(MUSART2 -> CR1 , 2);
 #elif  USART2_RECEIVER_ENABLE == OFF
	 	 	CLR_BIT(MUSART2 -> CR1 , 2);
	 #endif
	 
	   /*STOP BIT NUMBER */
 #if    USART2_STOPBIT_NUMBER  ==  USART1_ONE_STOP
	 	 	 CLR_BIT(MUSART2 -> CR2 , 12);
	 	 	 CLR_BIT(MUSART2 -> CR2 , 13);
			 
 #elif  USART2_STOPBIT_NUMBER ==   USART1_TWO_STOP
  CLR_BIT(MUSART2 -> CR2 , 12);
  SET_BIT(MUSART2 -> CR2 , 13);
	 #endif
	 
	 
 }
 void MUSART2_VidTransmit(u8 Copy_Transmit[])
 {
	 u8 i =0;
	 while (Copy_Transmit[i] != '\0')
	 {
		 MUSART2->DR=Copy_Transmit[i];
		 /*Wait till transmition is ended*/
		 while (GET_BIT( MUSART2->SR ,6 )==0)
		 {
			 ;
		 }
		 i++;

	 }
 }
 u8 MUSART2_U8Receive(void)
 {
	 
	 u8 Loc_u8ReceivedData=0;
	 u32 timeout=0;
	 /*Wait till receive is ended*/
		 while (GET_BIT( MUSART2->SR ,5 )==0)
		 {
			 timeout++;
			 if (timeout==3000000)
			 {
				 Loc_u8ReceivedData=255;
				 break;
			 }
		 }
		 if (Loc_u8ReceivedData==0)
		 {
	 Loc_u8ReceivedData = MUSART2 -> DR;
		 }
	return (Loc_u8ReceivedData);
	 
	 
 }
  u8 MUSART2_U8ReceiveBootLoader(u8* Copy_u8Data)
{
	u8 Local_u8Result = 1;

	if ( (GET_BIT((MUSART2 -> SR), 5)) == 1 )
	{
		*Copy_u8Data = MUSART2 -> DR;
	}
	else
	{
		Local_u8Result = 0;
	}
	
	return (Local_u8Result);
}


  void MUSART3_VidInit(void)
  {
 	 	/*	baud rate = 9600      BRR=0x341	*//*for bootloader and uart*/
 	 	/*	baud rate = 115200    BRR=0x45	*//*for wifi*/
 		/*WE choose 115200*/
 		MUSART3->BRR = 0x341;
 		/* Clearing status register */
 		MUSART3 -> SR = 0;

 		/*ENABLE OR DISABLE USART*/
 		#if  USART3_ENABLE == ON
 	 SET_BIT(MUSART3 -> CR1 , 13);
 	 #elif  USART3_ENABLE == OFF
 	 	 CLR_BIT(MUSAR3 -> CR1 , 13);
 	 #endif

 	 	/*8 BITS OR 9 BITS*/
  #if    USART3_WORD_LENGTH     ==  USART1_8_BITS
 		 	 	 CLR_BIT(MUSART3 -> CR1 , 12);
 #elif   USART3_WORD_LENGTH     ==  USART1_9_BITS
 	 	 SET_BIT(MUSART3 -> CR1 , 12);
 	 #endif

  /*Parity control enable*/
  #if    USART3_PARITY_ENABLE   ==   ON
 	 	 	 SET_BIT(MUSART3 -> CR1 , 10);
 #if  USART3_PARITY_TYPE==USART1_EVEN
 		 	 	 CLR_BIT(MUSART3 -> CR1 , 9);
 #elif  USART3_PARITY_TYPE==USART1_ODD
 		 SET_BIT(MUSART3 -> CR1 , 9);
 	#endif
 #elif  USART3_PARITY_ENABLE == OFF
 	 	 	 CLR_BIT(MUSART3 -> CR1 , 10);
 	 #endif
 	 /*transmitter enable*/
  #if    USART3_TRANSMITTER_ENABLE  ==   ON
 	 		 SET_BIT(MUSART3 -> CR1 , 3);
  #elif  USART3_TRANSMITTER_ENABLE == OFF
 	 	 	CLR_BIT(MUSART3 -> CR1 , 3);
 	 #endif

 	  /*receiver enable*/
  #if    USART3_RECEIVER_ENABLE  ==   ON
 	 		 SET_BIT(MUSART3 -> CR1 , 2);
  #elif  USART3_RECEIVER_ENABLE == OFF
 	 	 	CLR_BIT(MUSART3 -> CR1 , 2);
 	 #endif

 	   /*STOP BIT NUMBER */
  #if    USART3_STOPBIT_NUMBER  ==  USART1_ONE_STOP
 	 	 	 CLR_BIT(MUSART3 -> CR2 , 12);
 	 	 	 CLR_BIT(MUSART3 -> CR2 , 13);

  #elif  USART3_STOPBIT_NUMBER ==   USART1_TWO_STOP
   CLR_BIT(MUSART3 -> CR2 , 12);
   SET_BIT(MUSART3 -> CR2 , 13);
 	 #endif


  }
  void MUSART3_VidTransmit(u8 Copy_Transmit[])
  {
 	 u8 i =0;
 	 while (Copy_Transmit[i] != '\0')
 	 {
 		 MUSART3->DR=Copy_Transmit[i];
 		 /*Wait till transmition is ended*/
 		 while (GET_BIT( MUSART3->SR ,6 )==0)
 		 {
 			 ;
 		 }
 		 i++;
 	 }
  }
  u8 MUSART3_U8Receive(void)
  {

 	 u8 Loc_u8ReceivedData=0;
 	 u32 timeout=0;
 	 /*Wait till receive is ended*/
 		 while (GET_BIT( MUSART3->SR ,5 )==0)
 		 {
 			 timeout++;
 			 if (timeout==3000000)
 			 {
 				 Loc_u8ReceivedData=255;
 				 break;
 			 }
 		 }
 		 if (Loc_u8ReceivedData==0)
 		 {
 	 Loc_u8ReceivedData = MUSART3 -> DR;
 		 }
 	return (Loc_u8ReceivedData);


  }
   u8 MUSART3_U8ReceiveBootLoader(u8* Copy_u8Data)
 {
 	u8 Local_u8Result = 1;

 	if ( (GET_BIT((MUSART3 -> SR), 5)) == 1 )
 	{
 		*Copy_u8Data = MUSART3 -> DR;
 	}
 	else
 	{
 		Local_u8Result = 0;
 	}

 	return (Local_u8Result);
 }

