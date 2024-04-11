

/***************************************************************
       NAME    :LCD_interface.h
       create  :04/02/2024 5:30:36 PM
       version :_v1_
       Author  :mahmoud elgohary
****************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_Init(void);
void LCD_SendCmd(uint8_t command);
void LCD_Write4bits(uint8_t data, uint8_t control);
void LCD_WriteString(uint8_t * str);
void LCD4bits_Char(uint8_t data);
void LCD_CLEAR_SCREEN(void);
void LCD_GOTOXY(uint8_t line,uint8_t position);
void LCD_voidWriteNumber(int32_t Copy_s32num );
void delayMs(uint32_t n);
void delayUs(uint32_t n);



#endif /* LCD_INTERFACE_H_ */
