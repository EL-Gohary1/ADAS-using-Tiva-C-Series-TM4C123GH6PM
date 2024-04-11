/***************************************************************
       NAME    :GPIO.h
       create  :04/05/2024 1:24:36 PM
       version :_v1_
       Author  :mahmoud elgohary
****************************************************************/

#ifndef GPIO_H_
#define GPIO_H_






typedef enum
{
    PA=0,
    PB,
    PC,
    PD,
    PE,
    PF
}PORT_ID;


typedef enum
{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}PIN_ID;


typedef enum
{
    OUT=0,
    INPUT,
    INPULLUP,
    INPULLDOWN
}DIRECTION_ID;


typedef enum
{
    LOW=0,
    HIGH
}VOLTAGE_ID;


/******************************************************************************************************************************
 * \Syntax           : void GPIO_Init_Port(PORT_ID port)
 *
 * \Description      : Active Clock of each Port, Unlock Pins, Enable Pins of each Port, Disable Alternative Function Of each Port,
 *                     Enable Digital or Analog
 *
 * \Parameters (in)  : @ port: Specified Port to Enable
 *                       This parameter can be One of PORT_ID Enum Values to Select the Port:
 *                        @ PA: PORT A
 *                        @ PB: PORT B
 *                        @ PC: PORT C
 *                        @ PD: PORT D
 *                        @ PE: PORT E
 *                        @ PF: PORT F
 *
 * \Return value     : None
 ******************************************************************************************************************************/
void GPIO_Init_Port(PORT_ID port);

/******************************************************************************************************************************
 * \Syntax           : void GPIO_Set_Pin_Direction(PORT_ID port ,PIN_ID pin,DIRECTION_ID direction)
 *
 * \Description      : Select one Pin of any Port to Set its direction
 *
 * \Parameters (in)  : @ port: Specified Pin's Port
 *                       This parameter can be One of PORT_ID Enum Values to Select the Port:
 *                        @ PA: PORT A
 *                        @ PB: PORT B
 *                        @ PC: PORT C
 *                        @ PD: PORT D
 *                        @ PE: PORT E
 *                        @ PF: PORT F
 *
 *                     @ pin: Choose the Pin
 *                       This parameter can be One of PIN_ID Enum Values to Select the Pin:
 *                       @PIN0: PIN 0 of Selected Port
 *                       @PIN1: PIN 1 of Selected Port
 *                       @PIN2: PIN 2 of Selected Port
 *                       @PIN3: PIN 3 of Selected Port
 *                       @PIN4: PIN 4 of Selected Port
 *                       @PIN5: PIN 5 of Selected Port
 *                       @PIN6: PIN 6 of Selected Port
 *                       @PIN7: PIN 7 of Selected Port
 *                       @NOTE: PORTE has 5 Pins, PORTF has 4 Pins.
 *
 *                     @ direction: Specified Pin's Direction
 *                      This parameter can be One of DIRECTION_ID Enum Values to Select the Direction:
 *                      @OUT: Output
 *                      @INPUT: Input
 *                      @INPULLUP: Input Pull Up
 *                      @INPULLLDOWN: Input Pull Down
 *
 * \Return value     : None
 ******************************************************************************************************************************/
void GPIO_Set_Pin_Direction(PORT_ID port ,PIN_ID pin,DIRECTION_ID direction);

/******************************************************************************************************************************
 * \Syntax           : void GPIO_Set_Port_Direction(PORT_ID port,DIRECTION_ID direction)
 *
 * \Description      : Specified Direction of any Port
 *
 * \Parameters (in)  : @ port: Specified Port
 *                       This parameter can be One of PORT_ID Enum Values to Select the Port:
 *                        @ PA: PORT A
 *                        @ PB: PORT B
 *                        @ PC: PORT C
 *                        @ PD: PORT D
 *                        @ PE: PORT E
 *                        @ PF: PORT F
 *
 *                     @ direction: Specified Pin's Direction
 *                      This parameter can be One of DIRECTION_ID Enum Values to Select the Direction:
 *                      @OUT: Output
 *                      @INPUT: Input
 *                      @INPULLUP: Input Pull Up
 *                      @INPULLLDOWN: Input Pull Down
 *
 * \Return value     : None
 ******************************************************************************************************************************/
void GPIO_Set_Port_Direction(PORT_ID port,DIRECTION_ID direction);

/******************************************************************************************************************************
 * \Syntax           : void GPIO_Set_Pin_Value(PORT_ID port,PIN_ID pin,VOLTAGE_ID value)
 *
 * \Description      : Select one Pin of any Port to Set its Value
 *
 * \Parameters (in)  : @ port: Specified Pin's Port
 *                       This parameter can be One of PORT_ID Enum Values to Select the Port:
 *                        @ PA: PORT A
 *                        @ PB: PORT B
 *                        @ PC: PORT C
 *                        @ PD: PORT D
 *                        @ PE: PORT E
 *                        @ PF: PORT F
 *
 *                     @ pin: Choose the Pin
 *                       This parameter can be One of PIN_ID Enum Values to Select the Pin:
 *                       @PIN0: PIN 0 of Selected Port
 *                       @PIN1: PIN 1 of Selected Port
 *                       @PIN2: PIN 2 of Selected Port
 *                       @PIN3: PIN 3 of Selected Port
 *                       @PIN4: PIN 4 of Selected Port
 *                       @PIN5: PIN 5 of Selected Port
 *                       @PIN6: PIN 6 of Selected Port
 *                       @PIN7: PIN 7 of Selected Port
 *                       @NOTE: PORTE has 5 Pins, PORTF has 4 Pins.
 *
 *                     @ value: Specified Pin's Value
 *                       This parameter can be One of VOLTAGE_ID Enum Values to Select the Value:
 *                       @LOW: Low Volt
 *                       @HIGH: High Volt
 *
 * \Return value     : None
 ******************************************************************************************************************************/
void GPIO_Set_Pin_Value(PORT_ID port,PIN_ID pin,VOLTAGE_ID value);

/******************************************************************************************************************************
 * \Syntax           : void GPIO_Set_Port_Value(PORT_ID port,uint8_t value)
 *
 * \Description      : Specified Value of any Port
 *
 * \Parameters (in)  : @ port: Specified Port
 *                       This parameter can be One of PORT_ID Enum Values to Select the Port:
 *                        @ PA: PORT A
 *                        @ PB: PORT B
 *                        @ PC: PORT C
 *                        @ PD: PORT D
 *                        @ PE: PORT E
 *                        @ PF: PORT F
 *
 *                     @ value: Specified Port's Value
 *                       This parameter can be One of VOLTAGE_ID Enum Values to Select the Value:
 *                       @LOW: Low Volt
 *                       @HIGH: High Volt
 *
 * \Return value     : None
 ******************************************************************************************************************************/
void GPIO_Set_Port_Value(PORT_ID port,uint8_t value);

/******************************************************************************************************************************
 * \Syntax           : uint8_t GPIO_Get_Pin_Value(PORT_ID port,PIN_ID pin)
 *
 * \Description      : Select one Pin of any Port to Read its Value
 *
 * \Parameters (in)  : @ port: Specified Port
 *                       This parameter can be One of PORT_ID Enum Values to Select the Port:
 *                        @ PA: PORT A
 *                        @ PB: PORT B
 *                        @ PC: PORT C
 *                        @ PD: PORT D
 *                        @ PE: PORT E
 *                        @ PF: PORT F
 *
 *                     @ pin: Choose the Pin
 *                       This parameter can be One of PIN_ID Enum Values to Select the Pin:
 *                       @PIN0: PIN 0 of Selected Port
 *                       @PIN1: PIN 1 of Selected Port
 *                       @PIN2: PIN 2 of Selected Port
 *                       @PIN3: PIN 3 of Selected Port
 *                       @PIN4: PIN 4 of Selected Port
 *                       @PIN5: PIN 5 of Selected Port
 *                       @PIN6: PIN 6 of Selected Port
 *                       @PIN7: PIN 7 of Selected Port
 *                       @NOTE: PORTE has 5 Pins, PORTF has 4 Pins.
 *
 * \Return value     : u8
 ******************************************************************************************************************************/
uint8_t GPIO_Get_Pin_Value(PORT_ID port,PIN_ID pin);

/******************************************************************************************************************************
 * \Syntax           : void GPIO_Toggle_Pin_Value(PORT_ID port,PIN_ID pin)
 *
 * \Description      : Select one Pin of any Port to Toggle
 *
 * \Parameters (in)  : @ port: Specified Port
 *                       This parameter can be One of PORT_ID Enum Values to Select the Port:
 *                        @ PA: PORT A
 *                        @ PB: PORT B
 *                        @ PC: PORT C
 *                        @ PD: PORT D
 *                        @ PE: PORT E
 *                        @ PF: PORT F
 *
 *                     @ pin: Choose the Pin
 *                       This parameter can be One of PIN_ID Enum Values to Select the Pin:
 *                       @PIN0: PIN 0 of Selected Port
 *                       @PIN1: PIN 1 of Selected Port
 *                       @PIN2: PIN 2 of Selected Port
 *                       @PIN3: PIN 3 of Selected Port
 *                       @PIN4: PIN 4 of Selected Port
 *                       @PIN5: PIN 5 of Selected Port
 *                       @PIN6: PIN 6 of Selected Port
 *                       @PIN7: PIN 7 of Selected Port
 *                       @NOTE: PORTE has 5 Pins, PORTF has 4 Pins.
 *
 * \Return value     : None
 ******************************************************************************************************************************/
void GPIO_Toggle_Pin_Value(PORT_ID port,PIN_ID pin);



#endif /* GPIO_H_ */
