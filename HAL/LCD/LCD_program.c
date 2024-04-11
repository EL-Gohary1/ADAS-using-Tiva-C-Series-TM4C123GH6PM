
/***************************************************************
       NAME    :LCD_program.c
       create  :04/02/2024 5:24:36 PM
       version :_v1_
       Author  :mahmoud elgohary
****************************************************************/
#include  <stdint.h>
#include  <stdbool.h>
#include "LCD_interface.h"
#include "tm4c123gh6pm.h"
#include "MCAL/GPIO/GPIO.h"
#include "LCD_config.h"
#include "LCD_private.h"

void LCD_Init(void)
{
    GPIO_Init_Port(LCD_DATA);    //SYSCTL_RCGCGPIO_R|= 0x02;    //enable clock for PORTA FOR DATA      //enable PORTA digital IO pins     //DISABLE ALTERNATVIVE FUNCTION FOR PORTA
    GPIO_Init_Port(LCD_CONTROL);     //enable clock for PORTA FOR control
    delayMs(10);  //delay 10 ms for enable the clock of PORTB
    GPIO_Set_Pin_Direction(LCD_DATA ,PIN4,OUT);   //let PORTA as output pins
    GPIO_Set_Pin_Direction(LCD_DATA ,PIN5,OUT);
    GPIO_Set_Pin_Direction(LCD_DATA ,PIN6,OUT);
    GPIO_Set_Pin_Direction(LCD_DATA ,PIN7,OUT);
    GPIO_Set_Pin_Direction(LCD_CONTROL ,PIN0,OUT);
    GPIO_Set_Pin_Direction(LCD_CONTROL ,PIN1,OUT);
    //LCD_SendCmd(LCD_CMD_RETURN_HOME);
    LCD_SendCmd(LCD_CMD_FUNCTION_4BIT_2LINES);          //2 lines and 5x7 character (4-bit data, D4 to D7)
    LCD_SendCmd(LCD_CMD_ENTRY_MODE);                    //Automatic Increment cursor (shift cursor to right)
    LCD_SendCmd(LCD_CMD_CLEAR_SCREEN);          //Clear display screen
    LCD_SendCmd(LCD_CMD_DISP_ON_CURSOR_BLINK);          //Display on, cursor blinking

}


void LCD_SendCmd(uint8_t command)
{
    LCD_Write4bits(command & 0xF0 , 0);    //upper nibble first and disable RS
    LCD_Write4bits(command << 4 , 0);      //then lower nibble and disable RS

    if(command < 4)
        delayMs(2);       //commands 1 and 2 need up to 1.64ms
    else
        delayUs(40);      //all others 40 us
}

void LCD_Write4bits(uint8_t data, uint8_t control)
{
    data &= 0xF0;                       //clear lower nibble for control
    control &= 0x0F;                    //clear upper nibble for data
    LCD_DATA_REG = data ;//Include RS value (command or data ) with data
    LCD_CONTROL_REG = control ;
    LCD_CONTROL_REG = control | EN;    //pulse EN
    delayUs(0);                                 //delay for pulsing EN
    LCD_CONTROL_REG = control;         //Turn off the pulse EN
    LCD_DATA_REG = 0;                      //Clear the Data
    LCD_CONTROL_REG = 0;
}

void LCD_WriteString(uint8_t * str)
{
    uint32_t i = 0;          //volatile is important

    while(*(str+i) != '\0')       //until the end of the string
    {
        LCD4bits_Char(*(str+i));    //Write each character of string
        i++;                        //increment for next character
    }
}
void LCD4bits_Char(uint8_t data)
{
    LCD_Write4bits(data & 0xF0 , RS);   //upper nibble first and enable RS
    LCD_Write4bits(data << 4 , RS);     //then lower nibble  and enable RS
    delayUs(40);                        //delay for LCD (MCU is faster than LCD)
}

void LCD_CLEAR_SCREEN(void)
{
    LCD_SendCmd(LCD_CMD_CLEAR_SCREEN);
}

void LCD_GOTOXY(uint8_t line,uint8_t position)
{
    if (line == 0)
    {
        if ((position < 16))
        {
            LCD_SendCmd(LCD_CMD_BEGIN_AT_FIRST_ROW + position);
        }
        else
        {

        }
    }
    else if (line == 1)
    {
        if ((position < 16))
        {
            LCD_SendCmd(LCD_CMD_BEGIN_AT_SECOND_ROW + position);
        }
        else
        {

        }
    }
    else
    {

    }
}


void LCD_voidWriteNumber(int32_t Copy_s32num )
{

    uint8_t str[10]={0},i=0 ,j;
    if(Copy_s32num==0)
    {
        LCD4bits_Char('0');
        return;
    }
    if(Copy_s32num<0)
    {
        Copy_s32num=Copy_s32num*(-1);
        LCD4bits_Char('-');
    }

    while(Copy_s32num!=0)
    {
        str[i]=Copy_s32num%10 +'0';
        Copy_s32num=Copy_s32num/10;
        i++;

    }

    for (j=i;j>0;j--)
    {
        LCD4bits_Char(str[j-1]);
    }
}


void delayMs(uint32_t n)
{
    uint32_t i,j;             //volatile is important for variables incremented in code
    for(i=0;i<n;i++)
        for(j=0;j<3180;j++)         //delay for 1 msec
        {}
}

void delayUs(uint32_t n)
{
    uint32_t i,j;                           //volatile is important for variables incremented in code
    for(i=0;i<n;i++)
        for(j=0;j<3;j++)            //delay for 1 micro second
        {}
}
