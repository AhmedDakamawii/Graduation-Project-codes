 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: AFIO                                           */ 
/****************************************************************/
#ifndef _AFIO_INTER_H
#define _AFIO_INTER_H

// to determine which port will use with the line
void MAFIO_VidSetEXTIConfig(u8 Copy_Line, u8 Copy_Portmap );


//this is what should we send in Copy_Portmap to determine the port will use as external interrupt
#define AFIO_PORTA 0b0000
#define AFIO_PORTB 0b0001
#define AFIO_PORTC 0b0010




#endif
