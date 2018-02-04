#ifndef _LCD_H_
#define _LCD_H_

#include "Port.h"

#define LCD_WARM_UP_DELAY               15//ms
#define LCD_INIT_2ND_DELAY              4//ms
#define LCD_INIT_3RD_DELAY              1//ms//100us
#define CLEAR_DISPLAY_DELAY             2//1.64ms
#define CURSOR_HOME_DELAY               2//1.64ms

#define ENTRY_MODE_DELAY                1//ms//40us
#define DISPLAY_ON_OFF_CONTROL_DELAY    1//ms//40us
#define CURSOR_DISPLAY_SHIFT_DELAY      1//ms//40us
#define FUNCTION_SET_DELAY              1//ms//40us
#define SET_CGRAM_ADDRESS_DELAY         1//ms//40us
#define SET_DDRAM_ADDRESS_DELAY         1//ms//40us
//#define READ_BUSY_FLAG            undefined//
#define WRITE_TO_CGRAM_OR_DDRAM         1//ms//40us
#define READ_FROM_CGRAM_OR_DDRAM        1//ms//40us


#define LCD_LINE_WIDTH (16)
typedef enum{
    LCD_4bit_mode,
    LCD_8bit_mode
}tLCD_Mode;

void LCD_Init(tLCD_Mode mode);
void LCD_Write_Character( U8 ch);
void LCD_Write_String( U8* str);
void LCD_GoTo(U8 row, U8 column);
void LCD_Clear_Screen(void);

//there is no read mode because R/W connected to ground always in write mode

#endif // _LCD_H_
