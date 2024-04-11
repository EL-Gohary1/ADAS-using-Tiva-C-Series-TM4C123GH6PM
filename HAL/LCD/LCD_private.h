
/***************************************************************
       NAME    :LCD_private.h
       create  :04/02/2024 5:24:40 PM
       version :_v1_
       Author  :mahmoud elgohary
****************************************************************/
#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_


// Commands of LCD
#define LCD_CMD_FUNCTION_8BIT_1LINES                    (0x30)
#define LCD_CMD_FUNCTION_8BIT_2LINES                    (0x38)
#define LCD_CMD_FUNCTION_4BIT_1LINES                    (0x20)
#define LCD_CMD_FUNCTION_4BIT_2LINES                    (0x28)
#define LCD_CMD_MOVE_DISP_RIGHT                         (0x1C)
#define LCD_CMD_MOVE_DISP_LEFT                          (0x18)
#define LCD_CMD_MOVE_CURSOR_RIGHT                       (0x14)
#define LCD_CMD_MOVE_CURSOR_LEFT                        (0x10)
#define LCD_CMD_DISP_OFF_CURSOR_OFF                     (0x08)
#define LCD_CMD_DISP_ON_CURSOR_ON                       (0x0E)
#define LCD_CMD_DISP_ON_CURSOR_BLINK                    (0x0F)
#define LCD_CMD_DISP_ON_BLINK                           (0x0D)
#define LCD_CMD_DISP_ON_CURSOR_OFF                      (0x0C)
#define LCD_CMD_BEGIN_AT_FIRST_ROW                      (0x80)
#define LCD_CMD_BEGIN_AT_SECOND_ROW                     (0xC0)
#define LCD_CMD_CLEAR_SCREEN                            (0x01)
#define LCD_CMD_ENTRY_MODE                              (0x06)
#define LCD_CMD_RETURN_HOME                             (0x02)


#endif /* LCD_PRIVATE_H_ */
