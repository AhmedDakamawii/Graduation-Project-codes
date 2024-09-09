 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: UART                                           */ 
/****************************************************************/
#ifndef _UART_CONFG_H
#define _UART_CONFG_H

 /*ENABLE OR DISABLE USART*/
 #define USART1_ENABLE  OFF
 #define USART2_ENABLE  OFF
 #define USART3_ENABLE  ON
/*8 BITS OR 9 BITS*/
 #define    USART1_WORD_LENGTH        USART1_8_BITS  
 #define    USART2_WORD_LENGTH        USART1_8_BITS  
 #define    USART3_WORD_LENGTH        USART1_8_BITS
  /*Parity control enable*/
 #define    USART1_PARITY_ENABLE      OFF
 #define    USART2_PARITY_ENABLE      OFF
 #define    USART3_PARITY_ENABLE      OFF
/*PARITY TYPE*/
 #define    USART1_PARITY_TYPE      USART1_EVEN  
 #define    USART2_PARITY_TYPE      USART1_EVEN  
 #define    USART3_PARITY_TYPE      USART1_EVEN
  /*Transmitter enable*/
 #define    USART1_TRANSMITTER_ENABLE     ON
 #define    USART2_TRANSMITTER_ENABLE     ON  
 #define    USART3_TRANSMITTER_ENABLE     ON
/*receiver enable*/
 #define    USART1_RECEIVER_ENABLE     ON  
 #define    USART2_RECEIVER_ENABLE     ON
 #define    USART3_RECEIVER_ENABLE     ON
 /*STOP BIT NUMBER */
 #define    USART1_STOPBIT_NUMBER    USART1_ONE_STOP  
 #define    USART2_STOPBIT_NUMBER    USART1_ONE_STOP  
 #define    USART3_STOPBIT_NUMBER    USART1_ONE_STOP

#endif
