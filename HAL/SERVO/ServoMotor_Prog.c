



#include  <stdint.h>
#include  <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "ServoMotor_Interface.h"
#include "ServoMotor_Cfg.h"


/*The TM4C123GH6PM microcontroller contains two PWM modules
  each module have up to four generator block and control block
  Each PWM module provides four PWM generators, each providing two PWM outputs 
  that may be used in a wide variety of applications*/
  
//PWM1_Genrator1 have two PIN PWM_OUT_2 AND PWM_OUT_3 is PA6 AND PA7 ON J1 OF TIVA C Kit



void ServoMotor_Init(void)
{
	//enable clock for Module 1  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	/* This function sets the PWM clock divider as the PWM clock source.
	  It also configures the clock frequency to the PWM module as a division of the system clock*/
	//Assumed clock source 16MHZ  Divide by 2 so clock for Module 1 is 8MHZ Ticks 0.125 microsecond max freq 61HZ 
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
	//By Default GPIOA is Enable To use Module 1 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA6_M1PWM2);
    GPIOPinConfigure(GPIO_PA7_M1PWM3);
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_7);	

	//PWM1_GEN1 AND PWM1_GEN1 in UP_DOWN_MODE
	//PWM_GEN_MODE_NO_SYNC is used so that the generator gives immediate updates rather than synchronizing with the clock to update
    PWMGenConfigure(PWM1_BASE,PWM_GEN_1,PWM_GEN_MODE_UP_DOWN|PWM_GEN_MODE_NO_SYNC);
    
	 //set freq 50 hz 
	 ServoMotor_SetFreq_HZ(50); 
}


//Freq HZ for all pin of this generator which have two pins 
//ui8Freq from 0 to Max Freq 61 Hz
void ServoMotor_SetFreq_HZ(uint8_t ui8Freq)
{
  //Period specifies the period of PWM generator output, measured in clock ticks
  uint8_t Local_Freq=ui8Freq;
  uint32_t period;
  period =((uint32_t)1000000/Local_Freq);
  PWMGenPeriodSet(PWM1_BASE,PWM_GEN_1,period);
  //this function causes all queued updates to the period or
  //pulse width to be applied the next time the corresponding counter becomes zero  
  PWMSyncUpdate(PWM1_BASE,PWM_GEN_1);
}

//ui8Duty from 0 to 100
//for module 1 
//ui32PWMOut This parameter must be one of  PWM_OUT_2, PWM_OUT_3 that we used generator 1
void ServoMotor_SetDuty(uint32_t ui32PWMOut, uint8_t ui8Duty)
{
   //Period specifies the period of PWM generator output, measured in clock ticks
  uint8_t Local_Duty=ui8Duty;
  uint32_t Local_LoadValue;
  Local_LoadValue = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1);
  
  uint32_t ui32Width;
  ui32Width =((uint32_t)Local_LoadValue*Local_Duty)/100;
  PWMPulseWidthSet(PWM1_BASE, ui32PWMOut,  ui32Width);
  
  /*this function causes all queued updates to the period or
    pulse width to be applied the next time the corresponding counter becomes zero*/
	PWMSyncUpdate(PWM1_BASE,PWM_GEN_1_BIT);
  
}

//we use Module 1 Two Fuctions to Enable and Disable PWM Generator 1
void ServoMotor_PWM_EnableGen(void)
{
  //This function Enable the PWM clock from driving the timer/counter for the specified Generator block
  PWMGenEnable(PWM1_BASE,PWM_GEN_1);  
}
void ServoMotor_PWM_DisableGen(void)
{
  //This function blocks the PWM clock from driving the timer/counter for the specified Generator block
  PWMGenDisable(PWM1_BASE,PWM_GEN_1);  
}


// Enables or disables PWM outputs
//ui32PWMOut This parameter must be one of PWM_OUT_2_BIT, PWM_OUT_3_BIT that we used pwm Generator 1
void ServoMotor_PWM_EnableOutput(uint32_t ui32PWMOut)
{
   PWMOutputState(PWM1_BASE, ui32PWMOut, true);
}
void ServoMotor_PWM_DisableOutput(uint32_t ui32PWMOut)
{
   PWMOutputState(PWM1_BASE, ui32PWMOut, false);
}

// Enables or disables two PWM outputs in same genrator
// when use PWM_DisableOutputGen the timer not stop so preferd to use PWMSyncTimeBase to reset timer After enable
void ServoMotor_PWM_EnableOutputGen(void)
{
	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT|PWM_OUT_3_BIT, true);
}
void ServoMotor_PWM_DisableOutputGen(void)
{
	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT|PWM_OUT_3_BIT, false);
}

//this function synchronizes the time base of the generator blocks by causing the specified generator counters to be reset to zero
//Reset timer of generator 1 for module 1
void ServoMotor_PWM_ResetTimer(void)
{
	PWMSyncTimeBase(PWM1_BASE, PWM_GEN_1_BIT);
}

//ui32ServoName  Front_Servo    Back_Servo
//ui8Angle   0 or 45  or 90 or 145 or 180
void ServoMotor_Start(uint32_t ui32ServoName, uint8_t ui8Angle)
{
  uint8_t Local_ui8Duty=((((uint16_t)ui8Angle*9)/180)+3);
  ServoMotor_SetDuty(ui32ServoName,Local_ui8Duty);
  ServoMotor_PWM_ResetTimer();
  ServoMotor_PWM_EnableOutputGen();   //    PWM_EnableOutput(PWM_OUT_0_BIT);
  ServoMotor_PWM_EnableGen();
}

