/***************************************************************************/
/*  Author     :   Andrew Ashraf                                           */
/*  Date       :   1/9/2023                                                */
/*  Version    :   V01                                                     */
/***************************************************************************/


#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#define MI2C_1          0
#define MI2C_2          1

void MI2C_voidInit( void );
void MI2C_voidStart( u8 Copy_u8I2CId );
void MI2C_voidStop( u8 Copy_u8I2CId );
void MI2C_voidSetOwnAddress(u8 Copy_u8OwnAddress);
void MI2C_voidMasterTransmitIT( u8 Copy_u8I2CId , u8* Copy_u8TxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd );
void MI2C_voidMasterReceiveIT(  u8 Copy_u8I2CId , u8* Copy_u8RxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd );
void MI2C_voidMasterTransmit( u8 Copy_u8I2CId , u8 Copy_u8TxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd );
void MI2C_voidMasterReceive(  u8 Copy_u8I2CId , u8* Copy_u8RxData , u32 Copy_u32Len , u8 Copy_u8SlaveAdd );
static void MI2C_voidClearData(void);
void MI2C_voidDisableInterrupt (void);
void MI2C_voidEnableInterrupt (void);
void MI2C_voidClearADDR(void);

#endif
