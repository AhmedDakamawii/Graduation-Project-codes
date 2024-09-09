/***************************************************************************/
/*  Author     :   Andrew Ashraf                                           */
/*  Date       :   13/9/2023                                               */
/*  Version    :   V01                                                     */
/***************************************************************************/

#ifndef BH1750_PRIVATE_H
#define BH1750_PRIVATE_H

#define BH1750_POWER_DOWN         0b00000000
#define BH1750_POWER_ON           0b00000001
#define BH1750_RESET              0b00000111

#define BH1750_CONT_H_RES         0b00010000
#define BH1750_CONT_H_RES2        0b00010001
#define BH1750_CONT_L_RES         0b00010011
#define BH1750_ONE_H_RES          0b00100000
#define BH1750_ONE_H_RES2         0b00100001
#define BH1750_ONE_L_RES          0b00100011


#define BH1750_ADDR_L             0b0100011    /* Right BH1750 Sensor */
#define BH1750_ADDR_H             0b1011100     /* Left BH1750 Sensor */

#endif
