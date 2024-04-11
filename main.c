#include  <stdint.h>
#include  <stdbool.h>

#include <FreeRTOS.h>
#include <task.h>

// Application Logic
#include "Application/Application_interface.h"

// Drivers
#include "HAL/UART_0_Service/UART_0_interface.h"
#include "HAL/SERVO/ServoMotor_Interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/SERVO/ServoMotor_Interface.h"

uint32_t SystemCoreClock = 16000000;

// Tasks Implementation

int main()
{

    //Create Tasks

    // Startup of the FreeRTOS scheduler.  The program should block here.
    vTaskStartScheduler();

    // The following line should never be reached.  Failure to allocate enough
    //  memory from the heap would be one reason.
    for (;;)
        ;

}
