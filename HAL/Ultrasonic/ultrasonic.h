
/***************************************************************
       NAME    :ultrasonic.h
       create  :04/06/2024 3:30:36 PM
       version :_v1_
       Author  :mahmoud elgohary
****************************************************************/
#ifndef ULTASONIC_H_
#define ULTASONIC_H_

void Ultrasonic_Init(void);

void TIMER0A_voidCaptureInit(void);

uint32_t Ultrasonic_u32GetDistance(void);

void Delay_MicroSecond(uint32_t time);

void Delay(uint32_t counter);



#endif /* ULTASONIC_H_ */
