
/***************************************************************
       NAME    :Wheels_Interface.h
	   create  :04/10/2024 1:24:36 PM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/

#ifndef  _WHEELS_INTERFACE_H_
#define  _WHEELS_INTERFACE_H_

typedef enum{
   Rigth,
   Left,   
}Rotate_t;


//PWM0_Genrator0 have two PIN PWM_OUT_0 AND PWM_OUT_1 is PB6 AND PB7 ON J2 OF TIVA C Kit
//RIGHT
#define H1_ENB1  PWM_OUT_0  //PB6
#define H1_ENA1  PWM_OUT_1  //PB7
#define H1_PORT  GPIO_PORTD_BASE
#define H1_IN1   GPIO_PIN_0
#define H1_IN2   GPIO_PIN_1
#define H1_IN3   GPIO_PIN_2
#define H1_IN4   GPIO_PIN_3

//PWM0_Genrator1 have two PIN PWM_OUT_2 AND PWM_OUT_3 is PB4 AND PB5 ON J1 OF TIVA C Kit
//LEFT
#define H2_ENB1  PWM_OUT_2  //PB4
#define H2_ENA1  PWM_OUT_3  //PB5
#define H2_PORT  GPIO_PORTC_BASE
#define H2_IN1   GPIO_PIN_4
#define H2_IN2   GPIO_PIN_5
#define H2_IN3   GPIO_PIN_6
#define H2_IN4   GPIO_PIN_7

/**********************************************Prief about PWM module on tiva c********************************************************************************/
/*
  The TM4C123GH6PM microcontroller contains two PWM modules
  each module have up to four generator block and control block
  Each PWM module provides four PWM generators, each providing two PWM outputs 
  that may be used in a wide variety of applications

PWM0_Genrator0 have two PIN PWM_OUT_0 AND PWM_OUT_1 is PB6 AND PB7 ON J2 OF TIVA C Kit
PWM0_Genrator1 have two PIN PWM_OUT_2 AND PWM_OUT_3 is PB4 AND PB5 ON J1 OF TIVA C Kit
*/
/******************************************************************************************************************************/



/******************************************************************************************************************************
* \Syntax           : void Wheels_Init(void)
* \Description      : Initialization function for the motor control. It configures the PWM
                      modules and GPIO pins to control the motors. enable clock for Module 0
                      Assumed clock source 16MHZ So Divide by 16 so clock for Module 0 is 1MHZ Ticks 1 microsecond MAX FREQ 1 MHZ and we set freq at 50HZ
                      we use two Generator PWM0_GEN0 AND PWM0_GEN1
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : NO parameter in
* \Return value     : None
******************************************************************************************************************************/
void Wheels_Init(void);

/******************************************************************************************************************************
* \Syntax           : void Wheels_GoForwardSpeed(uint8_t ui8Speed)
* \Description      : Sets the car to move forward at a specified speed.
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui8Speed: Desired speed for all motors (0-100).
* \Return value     : None
******************************************************************************************************************************/
void Wheels_GoForwardSpeed(uint8_t ui8Speed);

/******************************************************************************************************************************
* \Syntax           : void Wheels_GoBackwardSpeed(uint8_t ui8Speed)
* \Description      : Sets the car to move backward at a specified speed.
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui8Speed: Desired speed for all motors (0-100).
* \Return value     : None
******************************************************************************************************************************/
void Wheels_GoBackwardSpeed(uint8_t ui8Speed);

/******************************************************************************************************************************
* \Syntax           : void Wheels_Rotate(Rotate_t Dir , uint8_t ui8Speed)
* \Description      : Sets the car to rotate at a specified speed and direction .
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui8Speed: Desired speed for all motors (0-100).
*                     @Rotate_t Dir: Rotation direction (Right or Left).
* \Return value     : None
******************************************************************************************************************************/
void Wheels_Rotate(Rotate_t Dir , uint8_t ui8Speed);

/******************************************************************************************************************************
* \Syntax           : void Wheels_DisableGen(uint32_t ui32Gen)
* \Description      : Disables the specified PWM generator block we use generator 0 and 1 on Module 0
*                     This function blocks the PWM clock from driving the timer/counter for the specified generator block
* 
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : ui32Gen: Specifies the PWM generator block to disable This parameter must be one of PWM_GEN_0, PWM_GEN_1.
* \Return value     : None
******************************************************************************************************************************/
void Wheels_DisableGen(uint32_t ui32Gen);



/******************************************************************************************************************************
* \Syntax           : void Wheels_SetFreq_HZ(uint32_t ui32Gen,uint8_t ui8Freq)
* \Description      : Sets the frequency (in HZ) for all pins of the specified PWM generator.
*                     the Freq is applied the next time the corresponding counter becomes zero.
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui32Gen: Specifies the PWM generator block to disable. This parameter must be one of PWM_GEN_0, PWM_GEN_1.
*                     @ui8Freq: Desired frequency in Hertz from 16HZ to Max Freq 1000000 Hz
* \Return value     : None
******************************************************************************************************************************/
void Wheels_SetFreq_HZ(uint32_t ui32Gen,uint8_t ui8Freq);




/******************************************************************************************************************************
* \Syntax           : void Wheels_SetDuty(uint32_t ui32PWMOut, uint8_t ui8Duty)
* \Description      : Sets the duty cycle (in percentage) for For module 0 .
*                     the Duty is applied the next time the corresponding counter becomes zero.
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui32PWMOut: Specifies the PWM output. This parameter must be one of PWM_OUT_0, PWM_OUT_1, PWM_OUT_2, PWM_OUT_3 that we used
                      the Duty is applied the next time the corresponding counter becomes zero
*                     @ui8Duty: Desired duty cycle percentage (0-100).
* \Return value     : None
******************************************************************************************************************************/
void Wheels_SetDuty(uint32_t ui32PWMOut, uint8_t ui8Duty);



/******************************************************************************************************************************
* \Syntax           : void Wheels_EnableOutput(uint32_t ui32PWMOut)
* \Description      : Enables the specified PWM outputs (module 0).
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui32PWMOut: specifies the PWM output. This parameter must be one of PWM_OUT_0_BIT, PWM_OUT_1_BIT, PWM_OUT_2_BIT, PWM_OUT_3_BIT that we used
                      the Duty is applied the next time the corresponding counter becomes zero
* \Return value     : None
******************************************************************************************************************************/
void Wheels_EnableOutput(uint32_t ui32PWMOut);

/*
  disables PWM outputs
  ui32PWMOut This parameter must be one of PWM_OUT_0_BIT, PWM_OUT_1_BIT, PWM_OUT_2_BIT, PWM_OUT_3_BIT that we used two generator
*/
/******************************************************************************************************************************
* \Syntax           : void Wheels_DisableOutput(uint32_t ui32PWMOut)
* \Description      : Disables the specified PWM outputs (module 0).
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui32PWMOut: Specifies the PWM output. This parameter must be one of PWM_OUT_0_BIT, PWM_OUT_1_BIT, PWM_OUT_2_BIT, PWM_OUT_3_BIT that we used
                      We used two generator the Duty is applied the next time the corresponding counter becomes zero
* \Return value     : None
******************************************************************************************************************************/
void Wheels_DisableOutput(uint32_t ui32PWMOut);



/******************************************************************************************************************************
* \Syntax           : void Wheels_EnableOutputGen(uint32_t ui32Gen)
* \Description      : Enables the specified PWM outputs in the same generator block.
*                     when use PWM_DisableOutputGen the timer not stop so preferd to use PWMSyncTimeBase to reset timer Before use PWM_EnableOutputGen.
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui32Gen: Specifies the PWM generator block,This parameter must be one of PWM_GEN_0_BIT, PWM_GEN_1_BIT that we used
* \Return value     : None
******************************************************************************************************************************/
void Wheels_EnableOutputGen(uint32_t ui32Gen);


/*
  Disables two PWM outputs in same genrator
  when use PWM_DisableOutputGen the timer not stop so preferd to use PWMSyncTimeBase to reset timer Before use PWM_EnableOutputGen
  ui32Gen This parameter must be one of PWM_GEN_0, PWM_GEN_1 that we used
*/
/******************************************************************************************************************************
* \Syntax           : void Wheels_DisableOutputGen(uint32_t ui32Gen);
* \Description      : Disables the specified PWM outputs in the same generator block.
*                     when use PWM_DisableOutputGen the timer not stop so preferd to use PWMSyncTimeBase to reset timer Before use PWM_EnableOutputGen
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui32Gen: Specifies the PWM generator block, This parameter must be one of PWM_GEN_0, PWM_GEN_1 that we used.
* \Return value     : None
******************************************************************************************************************************/
void Wheels_DisableOutputGen(uint32_t ui32Gen);


/******************************************************************************************************************************
* \Syntax           : void Wheels_ResetTimer(uint32_t ui32Gen)
* \Description      : this function synchronizes the time base of the generator blocks by causing the specified generator counters to be reset to zero
* \Sync\Async       : Synchronous
* \Reenrancy        : None Reentrant
* \Parameters (in)  : @ui32Gen: Specifies the PWM generator block,This parameter must be one of PWM_GEN_0_BIT, PWM_GEN_1_BIT that we used
* \Return value     : None
******************************************************************************************************************************/
void Wheels_ResetTimer(uint32_t ui32Gen);






#endif


