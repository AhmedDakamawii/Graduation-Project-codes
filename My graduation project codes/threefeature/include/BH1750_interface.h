/***************************************************************************/
/*  Author     :   Andrew Ashraf                                           */
/*  Date       :   13/9/2023                                               */
/*  Version    :   V01                                                     */
/***************************************************************************/


#ifndef BH1750_INTERFACE_H
#define BH1750_INTERFACE_H

void BH1750_VoidInit (void);
void BH1750_VoidReadLeft (u16* Copy_u16Lux);
void BH1750_VoidReadRight (u16* Copy_u16Lux);
#endif
