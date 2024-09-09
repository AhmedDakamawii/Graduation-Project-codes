 /***************************************************************/
 /* Author : ahmed elsayed                                      */
 /*version:  V01                                                */
 /*Date:                                                        */ 
 /*Describtion: IR                                              */ 
/****************************************************************/
#ifndef _IR_INTER_H
#define _IR_INTER_H

void IR_VoidINIT (void);

void voidGetFrame( void);

//THIS IS INTTRUPT FOR systick that if we reach means that we ended our calculations
void Void_TakeAction (void);
//fun to do what ever you want with this values that we get from clicking a button
void Void_Play (void);


#endif
