 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: UART                                           */ 
/****************************************************************/
#ifndef _UART_INTER_H
#define _UART_INTER_H
 
 #define LOW 0
 #define HIGH 1
 
 /*ENABLE OR DISABLE*/
 #define OFF  0
 #define ON  1
 
 /*8 BITS OR 9 BITS*/
 #define USART1_8_BITS  0
 #define USART1_9_BITS  1
 /*PARITY TYPE*/
 #define USART1_EVEN  0
 #define USART1_ODD  1
 /*STOP BIT NUMBER */
 #define USART1_ONE_STOP  0
 #define USART1_TWO_STOP  1
 
 
 
 
 void MUSART1_VidInit(void);
 void MUSART1_VidTransmit(u8 Copy_Transmit[]);
 u8 MUSART1_U8Receive(void);
  u8 MUSART1_U8ReceiveBootLoader(u8* Copy_u8Data);
void MUSART2_VidInit(void);
 void MUSART2_VidTransmit(u8 Copy_Transmit[]);
 u8 MUSART2_U8Receive(void);
  u8 MUSART2_U8ReceiveBootLoader(u8* Copy_u8Data);
  void MUSART3_VidInit(void);
   void MUSART3_VidTransmit(u8 Copy_Transmit[]);
   u8 MUSART3_U8Receive(void);
    u8 MUSART3_U8ReceiveBootLoader(u8* Copy_u8Data);
 
#endif
