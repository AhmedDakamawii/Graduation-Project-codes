/***************************************************************************/
/*  Author     :   Ahmed Atef                                              */
/*  Date       :   16/8/2023                                               */
/*  Version    :   V01                                                     */
/***************************************************************************/


#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

/*
 * Options For Timer Status :
 * ON
 * OFF
*/
#define MTIM1_STATUS                  ON
#define MTIM2_STATUS                  ON
#define MTIM3_STATUS                  ON
#define MTIM4_STATUS                  ON





#if MTIM1_STATUS         ==           ON
/*
 * Enter Value (1 -> 65536)
 */
#define MTIM1_PRESCALER               8

/*
 * Options For PWM Channels Status :
 * ON
 * OFF
 * Note(OC1REF) :
 *         CHANNEL1  A8
 *         CHANNEL2  A9
 *         CHANNEL3  A10
 *         CHANNEL4  A11
 */
#define MTIM1_PWM_CHANNEL1_STATUS     ON
#define MTIM1_PWM_CHANNEL2_STATUS     ON
#define MTIM1_PWM_CHANNEL3_STATUS     OFF
#define MTIM1_PWM_CHANNEL4_STATUS     OFF

/* Needed Working Frequency for PWM */
#define MTIM1_PWM_FREQ                50

#endif






#if MTIM2_STATUS         ==           ON
/*
 * Enter Value (1 -> 65536)
 */
#define MTIM2_PRESCALER               1000

/*
 * Options For Timer Modes :
 * PWM_MODE
 * OUTPUT_CAPTURE_MODE
 */
#define MTIM2_MODE                    PWM_MODE



#if MTIM2_MODE           ==           PWM_MODE
/*
 * Options For PWM Channels Status :
 * ON
 * OFF
 * Note(OC2REF) :
 *         CHANNEL1  A0
 *         CHANNEL2  A1
 *         CHANNEL3  A2
 *         CHANNEL4  A3
 */
#define MTIM2_PWM_CHANNEL1_STATUS     ON
#define MTIM2_PWM_CHANNEL2_STATUS     ON
#define MTIM2_PWM_CHANNEL3_STATUS     ON
#define MTIM2_PWM_CHANNEL4_STATUS     OFF

/* Needed Working Frequency for PWM */
#define MTIM2_PWM_FREQ                50

#endif

#endif


#if MTIM3_STATUS         ==           ON
/*
 * Enter Value (1 -> 65536)
 */
#define MTIM3_PRESCALER               1

/*
 * Options For Timer Modes :
 * PWM_MODE
 * OUTPUT_CAPTURE_MODE
 */
#define MTIM3_MODE                    OUTPUT_CAPTURE_MODE



#if MTIM3_MODE           ==           PWM_MODE
/*
 * Options For PWM Channels Status :
 * ON
 * OFF
 * Note(OC3REF) :
 *         CHANNEL1  A6
 *         CHANNEL2  A7
 *         CHANNEL3  B0
 *         CHANNEL4  B1
 */
#define MTIM3_PWM_CHANNEL1_STATUS     ON
#define MTIM3_PWM_CHANNEL2_STATUS     ON
#define MTIM3_PWM_CHANNEL3_STATUS     ON
#define MTIM3_PWM_CHANNEL4_STATUS     OFF

/* Needed Working Frequency for PWM */
#define MTIM3_PWM_FREQ                1000

#endif

#endif



#if MTIM4_STATUS         ==           ON
/*
 * Enter Value (1 -> 65536)
 */
#define MTIM4_PRESCALER               64

/*
 * Options For Timer Modes :
 * PWM_MODE
 * OUTPUT_CAPTURE_MODE
 */
#define MTIM4_MODE                    OUTPUT_CAPTURE_MODE



#if MTIM4_MODE      ==          PWM_MODE
/*
 * Options For PWM Channels Status :
 * ON
 * OFF
 * Note(OC4REF) :
 *         CHANNEL1  B6
 *         CHANNEL2  B7
 *         CHANNEL3  B8
 *         CHANNEL4  B9
 */
#define MTIM4_PWM_CHANNEL1_STATUS     OFF
#define MTIM4_PWM_CHANNEL2_STATUS     OFF
#define MTIM4_PWM_CHANNEL3_STATUS     OFF
#define MTIM4_PWM_CHANNEL4_STATUS     OFF

/* Needed Working Frequency for PWM */
#define MTIM4_PWM_FREQ                1000

#endif

#endif




#endif
