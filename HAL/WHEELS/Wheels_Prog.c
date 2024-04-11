/***************************************************************
       NAME    :Wheels_Prog.c
	   create  :04/10/2024 1:24:36 PM
	   version :_v1_
	   Author  :mahmoud elgohary
****************************************************************/

#include  <stdint.h>
#include  <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "Wheels_Interface.h"

/*The TM4C123GH6PM microcontroller contains two PWM modules
  each module have up to four generator block and control block
  Each PWM module provides four PWM generators, each providing two PWM outputs 
  that may be used in a wide variety of applications*/
  
//PWM0_Genrator0 have two PIN PWM_OUT_0 AND PWM_OUT_1 is PB6 AND PB7 ON J2 OF TIVA C Kit
//PWM0_Genrator1 have two PIN PWM_OUT_2 AND PWM_OUT_3 is PB4 AND PB5 ON J1 OF TIVA C Kit

void Wheels_Init(void)
{
	//enable clock for Module 0  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	// Wait for the PWM0 module to be ready.
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
//    {
//    }
    /* This function sets the PWM clock divider as the PWM clock source.
      It also configures the clock frequency to the PWM module as a division of the system clock*/
      //Assumed clock source 16MHZ  Divide by 16 so clock for Module 0 is 1MHZ Ticks 1 microsecond
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
	//By Default GPIOB is Enable To use Module 0 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    GPIOPinConfigure(GPIO_PB5_M0PWM3);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
	//PWM0_GEN0 AND PWM0_GEN1 in UP_DOWN_MODE
	//PWM_GEN_MODE_NO_SYNC is used so that the generator gives immediate updates rather than synchronizing with the clock to update
	PWMGenConfigure(PWM0_BASE,PWM_GEN_0,PWM_GEN_MODE_UP_DOWN|PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE,PWM_GEN_1,PWM_GEN_MODE_UP_DOWN|PWM_GEN_MODE_NO_SYNC);

    Wheels_SetFreq_HZ(PWM_GEN_0,50);
    Wheels_SetFreq_HZ(PWM_GEN_1,50);
	//	By Default ports of two lm298  is Enable
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	//dir
	GPIOPinTypeGPIOOutput(H1_PORT,H1_IN1|H1_IN2|H1_IN3|H1_IN4);
	GPIOPinTypeGPIOOutput(H2_PORT,H2_IN1|H2_IN2|H2_IN3|H2_IN4);
}

//we use Module 0 Two Fuctions to Enable and Disable PWM Genrator 0 or 1
//ui32Gen This parameter must be one of PWM_GEN_0, PWM_GEN_1
void Wheels_DisableGen(uint32_t ui32Gen)
{
  //This function blocks the PWM clock from driving the timer/counter for the specified generator block
  PWMGenDisable(PWM0_BASE,ui32Gen);  
}
void Wheels_EnableGen(uint32_t ui32Gen)
{
  //This function Enable the PWM clock from driving the timer/counter for the specified generator block
  PWMGenEnable(PWM0_BASE,ui32Gen);  
}

//Freq HZ for all pin of this generator which have two pins 
//ui8Freq from 16HZ to Max Freq 1 MHz
//ui32Gen This parameter must be one of PWM_GEN_0, PWM_GEN_1
void Wheels_SetFreq_HZ(uint32_t ui32Gen,uint8_t ui8Freq)
{
  //Period specifies the period of PWM generator output, measured in clock ticks
  uint8_t Local_Freq=ui8Freq;
  uint32_t period;
  period =((uint32_t)1000000/Local_Freq);
  PWMGenPeriodSet(PWM0_BASE,ui32Gen,period);
  //this function causes all queued updates to the period or
  //pulse width to be applied the next time the corresponding counter becomes zero  
  PWMSyncUpdate(PWM0_BASE,ui32Gen);
}

//ui8Duty from 0 to 100
//for module 0 
//ui32PWMOut This parameter must be one of PWM_OUT_0, PWM_OUT_1, PWM_OUT_2, PWM_OUT_3 that we used
void Wheels_SetDuty(uint32_t ui32PWMOut, uint8_t ui8Duty)
{
  //Period specifies the period of PWM generator output, measured in clock ticks
  uint8_t Local_Duty=ui8Duty;
  uint32_t Local_LoadValue;
  uint8_t Local_GenNum;
  switch (ui32PWMOut)
  {
	  case PWM_OUT_0:
	  Local_LoadValue = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0);
	  Local_GenNum=0;
	  break;
	  case PWM_OUT_1:
	  Local_LoadValue = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0);
	  Local_GenNum=0;
	  break;
	  case PWM_OUT_2:
	  Local_LoadValue = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1);
	  Local_GenNum=1;
	  break;
	  case PWM_OUT_3:
	  Local_LoadValue = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1);
	  Local_GenNum=1;
	  break;
	  default :
	  //error use inactive generator 
	  break;
  }
  uint32_t ui32Width;
  ui32Width =((uint32_t)Local_LoadValue*Local_Duty)/100;
  PWMPulseWidthSet(PWM0_BASE, ui32PWMOut,  ui32Width);
  
  /*this function causes all queued updates to the period or
    pulse width to be applied the next time the corresponding counter becomes zero*/
  if (Local_GenNum==0)
  {
	 // PWMSyncUpdate(PWM0_BASE,PWM_GEN_0_BIT);
  }
  else
  {
	 // PWMSyncUpdate(PWM0_BASE,PWM_GEN_1_BIT);
  }
}

// Enables or disables PWM outputs
//ui32PWMOut This parameter must be one of PWM_OUT_0_BIT, PWM_OUT_1_BIT, PWM_OUT_2_BIT, PWM_OUT_3_BIT that we used
void Wheels_EnableOutput(uint32_t ui32PWMOut)
{
   PWMOutputState(PWM0_BASE, ui32PWMOut, true);
}
void Wheels_DisableOutput(uint32_t ui32PWMOut)
{
   PWMOutputState(PWM0_BASE, ui32PWMOut, false);
}

// Enables or disables two PWM outputs in same genrator
// when use PWM_DisableOutputGen the timer not stop so preferd to use PWMSyncTimeBase to reset timer After enable
//ui32Gen This parameter must be one of PWM_GEN_0, PWM_GEN_1 that we used
void Wheels_EnableOutputGen(uint32_t ui32Gen)
{
	switch (ui32Gen)
	{
		case PWM_GEN_0:
		PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT|PWM_OUT_1_BIT, true);
		break;
		case PWM_GEN_1:
		PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT|PWM_OUT_3_BIT, true);
		break;
		default :
	    //error use inactive generator 
	    break;
	}
}
void Wheels_DisableOutputGen(uint32_t ui32Gen)
{
   switch (ui32Gen)
	{
		case PWM_GEN_0:
		PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT|PWM_OUT_1_BIT, false);
		break;
		case PWM_GEN_1:
		PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT|PWM_OUT_3_BIT, false);
		break;
		default :
	    //error use inactive generator 
	    break;
	}
}
//this function synchronizes the time base of the generator blocks by causing the specified generator counters to be reset to zero
//ui32Gen This parameter must be one of PWM_GEN_0_BIT, PWM_GEN_1_BIT that we used
void Wheels_ResetTimer(uint32_t ui32Gen)
{
	switch (ui32Gen)
	{
		case PWM_GEN_0:
		PWMSyncTimeBase(PWM0_BASE, ui32Gen);
		break;
		case PWM_GEN_1:
		PWMSyncTimeBase(PWM0_BASE, ui32Gen);
		break;
		default :
	    //error use inactive generator 
	    break;
	}
}


//SPEED 0-100
void Wheels_GoForwardSpeed(uint8_t ui8Speed)
{
	// wheel on front right go forward
	GPIOPinWrite(H1_PORT,H1_IN1,H1_IN1);
	GPIOPinWrite(H1_PORT,H1_IN2,0x00);
	// wheel on back right go forward
	GPIOPinWrite(H1_PORT,H1_IN3,H1_IN3);
	GPIOPinWrite(H1_PORT,H1_IN4,0);
	// wheel on front left go forward
	GPIOPinWrite(H2_PORT,H2_IN1,H2_IN1);
	GPIOPinWrite(H2_PORT,H2_IN2,0);
	// wheel on back left go forward
	GPIOPinWrite(H2_PORT,H2_IN3,H2_IN3);
	GPIOPinWrite(H2_PORT,H2_IN4,0);	
	//set speed 
	//ui32PWMOut This parameter must be one of PWM_OUT_0, PWM_OUT_1, PWM_OUT_2, PWM_OUT_3 that we used
	Wheels_SetDuty(PWM_OUT_0, ui8Speed);
    Wheels_SetDuty(PWM_OUT_1, ui8Speed);
	Wheels_SetDuty(PWM_OUT_2, ui8Speed);
	Wheels_SetDuty(PWM_OUT_3, ui8Speed);
	Wheels_ResetTimer(PWM_GEN_0_BIT);
	Wheels_ResetTimer(PWM_GEN_1_BIT);
	Wheels_EnableOutputGen(PWM_GEN_0);
	Wheels_EnableOutputGen(PWM_GEN_1);
	Wheels_EnableGen(PWM_GEN_0);
	Wheels_EnableGen(PWM_GEN_1);
}
void Wheels_GoBackwardSpeed(uint8_t ui8Speed)
{
   	// wheel on front right go Backward
	GPIOPinWrite(H1_PORT,H1_IN1,0);
	GPIOPinWrite(H1_PORT,H1_IN2,H1_IN2);
	// wheel on back right go Backward
	GPIOPinWrite(H1_PORT,H1_IN3,0);
	GPIOPinWrite(H1_PORT,H1_IN4,H1_IN4);
	// wheel on front left go Backward
	GPIOPinWrite(H2_PORT,H2_IN1,0);
	GPIOPinWrite(H2_PORT,H2_IN2,H2_IN2);
	// wheel on back left go Backward
	GPIOPinWrite(H2_PORT,H2_IN3,0);
	GPIOPinWrite(H2_PORT,H2_IN4,H2_IN4);
	//set speed 
	//ui32PWMOut This parameter must be one of PWM_OUT_0, PWM_OUT_1, PWM_OUT_2, PWM_OUT_3 that we used
	Wheels_SetDuty(PWM_OUT_0, ui8Speed);
    Wheels_SetDuty(PWM_OUT_1, ui8Speed);
	Wheels_SetDuty(PWM_OUT_2, ui8Speed);
	Wheels_SetDuty(PWM_OUT_3, ui8Speed);
	Wheels_ResetTimer(PWM_GEN_0_BIT);
	Wheels_ResetTimer(PWM_GEN_1_BIT);
	Wheels_EnableOutputGen(PWM_GEN_0);
	Wheels_EnableOutputGen(PWM_GEN_1);
	Wheels_EnableGen(PWM_GEN_0);
	Wheels_EnableGen(PWM_GEN_1);	
}
void Wheels_Rotate(Rotate_t Dir , uint8_t ui8Speed)
{
    switch (Dir)
    {
       case Rigth:
           // wheel on front right go forward
           GPIOPinWrite(H1_PORT,H1_IN1,H1_IN1);
           GPIOPinWrite(H1_PORT,H1_IN2,0x00);
           // wheel on back right go forward
           GPIOPinWrite(H1_PORT,H1_IN3,H1_IN3);
           GPIOPinWrite(H1_PORT,H1_IN4,0);
           // wheel on front left go backward
           GPIOPinWrite(H2_PORT,H2_IN1,0);
           GPIOPinWrite(H2_PORT,H2_IN2,H2_IN2);
           // wheel on back left go backward
           GPIOPinWrite(H2_PORT,H2_IN3,0);
           GPIOPinWrite(H2_PORT,H2_IN4,H2_IN4);
           //set speed
           //ui32PWMOut This parameter must be one of PWM_OUT_0, PWM_OUT_1, PWM_OUT_2, PWM_OUT_3 that we used
           Wheels_SetDuty(PWM_OUT_0, ui8Speed);
           Wheels_SetDuty(PWM_OUT_1, ui8Speed);
           Wheels_SetDuty(PWM_OUT_2, ui8Speed);
           Wheels_SetDuty(PWM_OUT_3, ui8Speed);
           Wheels_ResetTimer(PWM_GEN_0_BIT);
           Wheels_ResetTimer(PWM_GEN_1_BIT);
           Wheels_EnableOutputGen(PWM_GEN_0);
           Wheels_EnableOutputGen(PWM_GEN_1);
           Wheels_EnableGen(PWM_GEN_0);
           Wheels_EnableGen(PWM_GEN_1);
       break;
       case Left:
           // wheel on front right go backward
              GPIOPinWrite(H1_PORT,H1_IN1,0);
              GPIOPinWrite(H1_PORT,H1_IN2,H1_IN2);
              // wheel on back right go backward
              GPIOPinWrite(H1_PORT,H1_IN3,0);
              GPIOPinWrite(H1_PORT,H1_IN4,H1_IN4);
              // wheel on front left go forward
              GPIOPinWrite(H2_PORT,H2_IN1,H2_IN1);
              GPIOPinWrite(H2_PORT,H2_IN2,0);
              // wheel on back left go forward
              GPIOPinWrite(H2_PORT,H2_IN3,H2_IN3);
              GPIOPinWrite(H2_PORT,H2_IN4,0);
              //set speed
              //ui32PWMOut This parameter must be one of PWM_OUT_0, PWM_OUT_1, PWM_OUT_2, PWM_OUT_3 that we used
              Wheels_SetDuty(PWM_OUT_0, ui8Speed);
              Wheels_SetDuty(PWM_OUT_1, ui8Speed);
              Wheels_SetDuty(PWM_OUT_2, ui8Speed);
              Wheels_SetDuty(PWM_OUT_3, ui8Speed);
              Wheels_ResetTimer(PWM_GEN_0_BIT);
              Wheels_ResetTimer(PWM_GEN_1_BIT);
              Wheels_EnableOutputGen(PWM_GEN_0);
              Wheels_EnableOutputGen(PWM_GEN_1);
              Wheels_EnableGen(PWM_GEN_0);
              Wheels_EnableGen(PWM_GEN_1);
       break;
    }
}
