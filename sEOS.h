#ifndef _SEOS_H_
#define _SEOS_H_

#include "Port.h"
#include "Timer0.h"

#include "SSD.h"
#include "LCD.h"

#include "SW.h"
#include "ADC.h"
#include "Buzzer.h"
#include "Speed_Motor.h"
#include "Swing_Motor.h"
#include "Display.h"
#include "Slider.h"

extern volatile U16 sys_tick;

//sys_tick = 10ms from timer 0
//Tasks Tick Counter Periods
#define TICK_COUNTER_SW          4

#define TICK_SOFT_SWITCHING      8

#define TICK_COUNTER_SLIDER      2

#define TICK_COUNTER_SSD         2
#define TICK_COUNTER_LCD         2
#define TICK_COUNTER_CALC        6000
#define TICK_COUNTER_SECONDS     100

#define TICK_COUNTER_SPEED_MOTOR 2

#define TICK_COUNTER_TRIAC_PULSE 1

#define TICK_COUNTER_SWING_MOTOR 2

void sEOS_Init(void);
void sEOS_Fan_Turn_Off(void);
void sEOS_IRQ_Handler(void) __interrupt 0 ;/* ISR @  vector 0 */


#endif // _SEOS_H_
