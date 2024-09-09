/***************************************************************************/
/*  Author     :   Andrew Ashraf                                           */
/*  Date       :   1/9/2023                                                */
/*  Version    :   V01                                                     */
/***************************************************************************/


#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

/*
*ON
*OFF
*/
#define MI2C1_STATUS                 ON
#define MI2C2_STATUS                 OFF


#if MI2C1_STATUS          ==      ON
/*
*MI2C_SCL_SM
*MI2C_SCL_FM_DUTY_2
*MI2C_SCL_FM_DUTY_16_9
*/
#define MI2C1_SCL_CLK                MI2C_SCL_SM

/*
*Up to 400000 Hz
*/
#define MI2C1_SCL_CLK_SPEED           100000

/*
*ON
*OFF
*/
#define MI2C1_ACK_STATUS               ON

/*
*ON
*OFF
*/
#define MI2C1_INTERRUPT_STATUS               OFF


#endif

#if MI2C2_STATUS          ==      ON

/*
*MI2C_SCL_SM
*MI2C_SCL_FM_DUTY_2
*MI2C_SCL_FM_DUTY_16/9
*/
#define MI2C2_SCL_CLK                MI2C_SCL_SM

/*
*Up to 400000 Hz
*/
#define MI2C2_SCL_CLK_SPEED           100000

/*
*ON
*OFF
*/
#define MI2C2_ACK_STATUS               ON

/*
*ON
*OFF
*/
#define MI2C2_INTERRUPT_STATUS               ON


#endif

#endif
