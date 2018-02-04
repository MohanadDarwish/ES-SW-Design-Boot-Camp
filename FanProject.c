#include "Main.h"
#include "SSD.h"
#include "LCD.h"
#include "SW.h"
#include "ADC.h"
#include "Buzzer.h"
#include "Speed_Motor.h"
#include "Swing_Motor.h"
#include "Display.h"
#include "Slider.h"
#include "sEOS.h"
#include "Timer1.h"

U16 __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;

void main(void)
{
    Timer1_Init();
    SW_Init(SW_Plus);
    SW_Init(SW_Minus);
    SW_Init(SW_Timer);
    SW_Init(SW_Display);
    Display_Init(SSD_ALL,LCD_4bit_mode);
    Speed_Motor_Init();
    Swing_Motor_Init();
    Slider_Init();
    Buzzer_Init();
    sEOS_Init();
    while(1)
    {
        //do nothing
    }
}
