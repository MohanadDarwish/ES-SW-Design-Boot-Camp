#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "Port.h"
#include "SSD.h"
#include "LCD.h"
#include "SW.h"
#include "sEOS.h"
#include "Slider.h"
#include "Speed_Motor.h"

#define SW_TIMER_FIRST_PRESS     (1)
#define SW_TIMER_SECOND_PRESS    (0)

extern U8 Display_WCET_H;
extern U8 Display_WCET_L;
void Display_Init (tSSD, tLCD_Mode);
void Display_Calculate_Time(void);
void Display_Check_SW(void);
void Display_Update_SSD(void);
void Display_Enable_SSD(void);
void Display_Disable_SSD(void);
void Display_Clear_LCD(void);
void Display_LCD_Print_Character(U8* str,  U8 line, U8 column);
void Display_LCD_Print_asterisks(void);
void Display_Update_LCD(U8 *ch, U8 line,U8 Column);
void Display_Task(void);

#endif // _DISPLAY_H_
