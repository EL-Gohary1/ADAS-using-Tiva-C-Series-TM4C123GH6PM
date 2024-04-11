
/***************************************************************
       NAME    :UART_0_interface.h
       create  :04/05/2024 2:21:40 PM
       version :_v1_
       Author  :mahmoud elgohary
****************************************************************/

#ifndef UART_0_UART_0_INTERFACE_H_
#define UART_0_UART_0_INTERFACE_H_

#include  <stdint.h>
#include  <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "stddef.h"

// - UART0 peripheral - As console to display debug messages.
//     - UART0RX - PA0
//     - UART0TX - PA1
//
// - UART parameters for the UART0 and UART7 port:
//     - Baud rate - 115,200
//     - 8-N-1 operation

void UART_0_Init(void);
void UART_0_SendString(uint8_t *ptr);

#endif /* UART_0_UART_0_INTERFACE_H_ */
