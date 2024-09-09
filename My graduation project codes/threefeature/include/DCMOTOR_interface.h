
#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_

void DCMOTOR1_VidInit(void);
void DCMOTOR_VidRotate(u8 direction,u8 direction2);
void DCMOTOR2_VidInit(void);
void DCMOTOR_VidRotateright(void);
void DCMOTOR_VidRotateleft(void);
void DCMOTOR_VidRotatebackward(void);
void DCMOTOR_VidRotateforward(void);
void DCMOTOR_VidRotate180(void);
void DCMOTOR_VidRotatestop(void);
void DCMOTOR_VidRotateforwardByPWM(u8 PWM_Speed);
void DCMOTOR_voidULTRAstop(void);

#endif /* DCMOTOR_INTERFACE_H_ */
