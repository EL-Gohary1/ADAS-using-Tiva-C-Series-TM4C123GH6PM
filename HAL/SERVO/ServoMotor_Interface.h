#ifndef  SERVO_MOTOR_INTERFACE_H_
#define  SERVO_MOTOR_INTERFACE_H_

#include "driverlib/pwm.h"
#include "ServoMotor_Cfg.h"


/*
   enable clock for Module 1  
   sets the PWM clock divider as the PWM clock source.
   PWM1_GEN1 AND PWM1_GEN1 in UP_DOWN_MODE
   Set freq 50 hz
*/
void ServoMotor_Init(void);

/*
  Freq HZ for all pin of this generator 1 which have two pins OUTPUT
  ui8Freq from 0 to Max Freq 61 Hz
*/
void ServoMotor_SetFreq_HZ(uint8_t ui8Freq);

//ui8Duty from 0 to 100
//for module 1 
//ui32PWMOut This parameter must be one of  PWM_OUT_2, PWM_OUT_3 that we used generator 1
void ServoMotor_SetDuty(uint32_t ui32PWMOut, uint8_t ui8Duty);


//we use Module 1 Two Fuctions to Enable and Disable PWM Generator 1
void ServoMotor_PWM_EnableGen(void);
void ServoMotor_PWM_DisableGen(void);


// Enables or disables PWM outputs
//ui32PWMOut This parameter must be one of PWM_OUT_2_BIT, PWM_OUT_3_BIT that we used pwm Generator 1
void ServoMotor_PWM_EnableOutput(uint32_t ui32PWMOut);
void ServoMotor_PWM_DisableOutput(uint32_t ui32PWMOut);


// Enables or disables two PWM outputs in same genrator
// when use PWM_DisableOutputGen the timer not stop so preferd to use PWMSyncTimeBase to reset timer After enable
void ServoMotor_PWM_EnableOutputGen(void);
void ServoMotor_PWM_DisableOutputGen(void);

/*
  this function synchronizes the time base of the generator blocks by causing the specified generator counters to be reset to zero
   Reset timer of generator 1 for module 1
*/
void ServoMotor_PWM_ResetTimer(void);


void ServoMotor_Start(uint32_t ui32ServoName, uint8_t ui8Angle);


#endif
