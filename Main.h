#ifndef _MAIN_H_
#define _MAIN_H_

#include <pic16f877a.h>

/* Standard data types */
typedef unsigned char   U8;
typedef unsigned short  U16;
typedef unsigned long   U32;
typedef char   S8;
typedef short  S16;
typedef long   S32;
typedef float  F32;

#include "Util.h"
#include "Timer1.h"

extern volatile U8 project_flags1;
extern volatile U8 project_flags2;

extern U8 exec_val[5];

//Flags Macro Names in Project Flags1
#define DOT_TOGGLE_FLAG                               0
#define SW_200MS_FLAG                                 1
#define SLIDER_STATE_INFO                             2
#define START_COUNTDOWN_FLAG                          3
#define TIMER_SWITCH_PRESSED_DETECTED_FLAG            4
#define SLIDER_VALUE_CHANGED_FOR_SWING_MOTOR_FLAG     5
#define SLIDER_VALUE_CHANGED_FOR_DISPLAY_FLAG         6
#define DISPLAY_SWING_VALUE_PRINTED_FLAG              7

//Flags Macro Names in Project_Flags2
#define DISPLAY_SPEED_VALUE_PRINTED_FLAG              0
#define SPEED_MOTOR_VALUE_CHANGED_FOR_DISPLAY_FLAG    1
#define DISPLAY_LCD_PRINT_LINE1_THEN_LINE2            2
#define DISPLAY_SLIDER_ASTREIKS_PRINTING_IN_PROGRESS  3
#define DISPLAY_SW_SECOND_SMALL_PRESS_DETECTED        4
#define DISPLAY_MOTOR_SPEED_FULLY_PRINTED             5
#define DISPLAY_SWING_VALUE_FULLY_PRINTED             6
#define STARTUP_FLAG                                  7
//#define TASK_EXCEDED_ITS_TIMEOUT                    5
//#define SW_DISPLAY_200MS_DETECTED_FLAG  5

//Flag Macro Like Function For Setting and Getting
#define SET_PROJECT_FLAG1(FLAG_NAME , VALUE)  (  (project_flags1) = ( project_flags1 & (~(1 << FLAG_NAME)) ) | (VALUE << FLAG_NAME)  )
#define GET_PROJECT_FLAG1(FLAG_NAME)          (  ((project_flags1) & (1 << FLAG_NAME)) >> (FLAG_NAME)  )

#define SET_PROJECT_FLAG2(FLAG_NAME , VALUE)  (  (project_flags2) = ( project_flags2 & (~(1 << FLAG_NAME)) ) | (VALUE << FLAG_NAME)  )
#define GET_PROJECT_FLAG2(FLAG_NAME)          (  ((project_flags2) & (1 << FLAG_NAME)) >> (FLAG_NAME)  )


/*Calculate execution time*/
#define _CALC_EXEC_TIME 1

/* DEBUGGINNG MACRO*/
#define _DEBUG_L3   0
#define _DEBUG_L2   0
#define _DEBUG_L1   0
#define _DEBUG      0
#define _ERROR      1


#if _DEBUG_L3 == 1
#define LCD_DEBUG_L3(x,y,str)  /*LCD_Clear_Screen();*/ LCD_GoTo(x,y); LCD_Write_String(str)
#else
#define LCD_DEBUG_L3(x,y,str)
#endif // _DEBUG



#if _DEBUG_L2 == 1
#define LCD_DEBUG_L2(x,y,str)  /*LCD_Clear_Screen();*/ LCD_GoTo(x,y); LCD_Write_String(str)
#else
#define LCD_DEBUG_L2(x,y,str)
#endif // _DEBUG

#if _DEBUG_L1 == 1
#define LCD_DEBUG_L1(x,y,str)  LCD_Clear_Screen(); LCD_GoTo(x,y); LCD_Write_String(str)
#else
#define LCD_DEBUG_L1(x,y,str)
#endif // _DEBUG

#if _DEBUG == 1
#define LCD_DEBUG(x,y,str)  LCD_Clear_Screen(); LCD_GoTo(x,y); LCD_Write_String(str)
#else
#define LCD_DEBUG(x,y,str)
#endif // _DEBUG

#if _ERROR == 1
#define LCD_ERROR(x,y,str) /* LCD_Clear_Screen();*/ LCD_GoTo(x,y); LCD_Write_String(str)
#else
#define LCD_ERROR(x,y,str)
#endif // _ERROR

/* Bit Levels */
#define HIGH_LEVEL     (1)
#define LOW_LEVEL      (0)

/* Global Interrupt Control */
#define GLOBAL_INTERRUPT_ENABLE() ((GIE) = 1)
#define GLOBAL_INTERRUPT_DISABLE() ((GIE) = 0)

/* Peripheral Interrupt Control */
#define PHERIPHERAL_INTERRUPT_ENABLE() ((PEIE) = 1)
#define PHERIPHERAL_INTERRUPT_DISABLE() ((PEIE) = 0)

/* GPIO definitions */

/* GPIO Pins */
#define GPIO_PIN_0                           (0)
#define GPIO_PIN_1                           (1)
#define GPIO_PIN_2                           (2)
#define GPIO_PIN_3                           (3)
#define GPIO_PIN_4                           (4)
#define GPIO_PIN_5                           (5)
#define GPIO_PIN_6                           (6)
#define GPIO_PIN_7                           (7)

/* GPIO Analog Pins */
#define GPIO_PIN_AN0                           (0)
#define GPIO_PIN_AN1                           (1)
#define GPIO_PIN_AN2                           (2)
#define GPIO_PIN_AN3                           (3)
#define GPIO_PIN_AN4                           (4)
#define GPIO_PIN_AN5                           (5)
#define GPIO_PIN_AN6                           (6)
#define GPIO_PIN_AN7                           (7)
#define GPIO_PIN_AN8                           (0)
#define GPIO_PIN_AN9                           (1)
#define GPIO_PIN_AN10                          (2)
#define GPIO_PIN_AN11                          (3)

/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA                             (PORTA)
#define GPIO_PORTA_DIRECTION                        (TRISA)

#define GPIO_PORTB_DATA                             (PORTB)
#define GPIO_PORTB_DIRECTION                        (TRISB)

#define GPIO_PORTC_DATA                             (PORTC)
#define GPIO_PORTC_DIRECTION                        (TRISC)

#define GPIO_PORTD_DATA                             (PORTD)
#define GPIO_PORTD_DIRECTION                        (TRISD)

#define GPIO_PORTE_DATA                             (PORTE)
#define GPIO_PORTE_DIRECTION                        (TRISE)

#define GPIO_ANSEL                                  (ANSEL)
#define GPIO_ANSELH                                 (ANSELH)


/* GPIO direction setting */
#define GPIO_OUT                                    (0)
#define GPIO_IN                                     (1)

/* GPIO direction setting */

#define ADC_Set_Digital                                 (0)
#define ADC_Set_Analog                                  (1)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)           (  (CONTROL) = (DIRECTION)?(~GPIO_OUT):(GPIO_OUT)  )
#define GPIO_WritePort(PORT, DATA)                  (  (PORT) = (DATA)  )
#define GPIO_ReadPort(PORT)                         (  PORT  )

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   (  (CONTROL) = ( CONTROL & (~(1 << PIN)) ) | (DIRECTION << PIN)  )
#define GPIO_WritePortPin(PORT, PIN, DATA)          (  (PORT) = ( PORT & (~(1 << PIN)) ) | (DATA << PIN)  )
#define GPIO_ReadPortPin(PORT, PIN)                 (  ((PORT) & (1 << PIN)) >> (PIN)  )

#endif // _MAIN_H_
