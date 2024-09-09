/***************************************************************************/
/*  Author     :   Andrew Ashraf                                           */
/*  Date       :   1/9/2023                                                */
/*  Version    :   V01                                                     */
/***************************************************************************/

#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

#define NULL            ((void*)0)

typedef struct{
	volatile u32 CR1         ;
	volatile u32 CR2         ;
	volatile u32 OAR1        ;
	volatile u32 OAR2        ;
	volatile u32 DR          ;
	volatile u32 SR1         ;
	volatile u32 SR2         ;
	volatile u32 CCR         ;
	volatile u32 TRISE       ;
}I2C_t;


#define MI2C1           ((volatile I2C_t*)0x40005400)
#define MI2C2           ((volatile I2C_t*)0x40005800)


#define I2C_READY 					0
#define I2C_BUSY_IN_RX 				1
#define I2C_BUSY_IN_TX 				2

#define ON                1
#define OFF               0


#define MI2C_SCL_SM               0
#define MI2C_SCL_FM_DUTY_2        1
#define MI2C_SCL_FM_DUTY_16_9     2


/* Register CR1 */
#define MI2C_PE                    0
#define MI2C_SMBUS                 1
#define MI2C_ENPEC                 5
#define MI2C_START                 8
#define MI2C_STOP                  9
#define MI2C_ACK                   10
#define MI2C_POS                   11
#define MI2C_PEC                   12
#define MI2C_SWRST                 15

/* Register SR1 */
#define MI2C_SB                    0
#define MI2C_ADDR                  1
#define MI2C_BTF                   2
#define MI2C_RXNE                  6
#define MI2C_TXE                   7

/* Register SR2 */
#define MI2C_MSL                   0

/*Register CR2 */
#define MI2C_ITEVTEN               9
#define MI2C_ITBUFEN               10

/*Register OAR1 */
#define MI2C_ADDMODE               15
#define MI2C_RESERVED              14

/*Register OAR2 */
#define MI2C_ENDUAL                0

/*Register CCR */
#define MI2C_F_S                   0
#define MI2C_DUTY                  1

#define F_CPU                      8000000

#endif
