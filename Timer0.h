#ifndef     _TIMER_0_
#define     _TIMER_0_

#include "Port.h"
/* Public Timer0 Macros */

/* --------INTCON_reg-----------------*/

#define TIMER0_INTERRUPT_ENABLE()  ((TMR0IE) = 1)

#define TIMER0_INTERRUPT_DISABLE() ((TMR0IE) = 0)

#define TIMER0_INTERRUPT_FLAG_CLEAR() ((TMR0IF) = 0)

/* -------- Option_reg_Functions----------*/

#define TIMER0_ASSIGN_PORTB_PULL_UP(VALUE)   ((NOT_RBPU) = (VALUE))

#define TIMER0_ASSIGN_INTERRUPT_EDGE(VALUE)   ((INTEDG) = (VALUE))

#define TIMER0_ASSIGN_CLOCK_SOURCE(VALUE)   ((T0CS) = (VALUE))

#define TIMER0_ASSIGN_SOURCE_EDGE(VALUE)    ((T0SE) = (VALUE))

#define TIMER0_ASSIGN_PRESCALER(VALUE)      ((PSA) = (VALUE))

#define TIMER0_SET_PRESCALER(VALUE)         (PS2 = ((VALUE & 0x4) >> 2));\
                                            (PS1 = ((VALUE & 0x2) >> 1));\
                                            (PS0 = (VALUE & 0x1))

/* -------- Option_reg_Commands/Values ----------*/
#define TIMER0_PORTB_PULL_UP_ENABLE       (HIGH_LEVEL)
#define TIMER0_PORTB_PULL_UP_DISABLE      (LOW_LEVEL)

#define TIMER0_INTERRUPT_EDGE_FALLING     (HIGH_LEVEL)
#define TIMER0_INTERRUPT_EDGE_RISING      (LOW_LEVEL)

#define TIMER0_CLOCK_SOURCE_INTERNAL     (LOW_LEVEL)
#define TIMER0_CLOCK_SOURCE_EXTERNAL     (HIGH_LEVEL)

#define TIMER0_SOURCE_EDGE_FALLING      (HIGH_LEVEL)
#define TIMER0_SOURCE_EDGE_RISING       (LOW_LEVEL)

#define TIMER0_PRESCALER_TO_WATCHDOG     (HIGH_LEVEL)
#define TIMER0_PRESCALER_TO_TIMER        (LOW_LEVEL)

typedef enum tTMR0_Prescaler_Value{
    Timer0_Prescaler_2  ,
    Timer0_Prescaler_4  ,
    Timer0_Prescaler_8  ,
    Timer0_Prescaler_16 ,
    Timer0_Prescaler_32 ,
    Timer0_Prescaler_64 ,
    Timer0_Prescaler_128,
    Timer0_Prescaler_256
}tTMR0_Prescaler_Value;

void Timer0_Init(tTMR0_Prescaler_Value);
void Timer0_Set_Start_value(U8 value);
void Timer0_Start(void);
void Timer0_Stop(void);
//void Timer0_IRQ_Handler(void) __interrupt 0;  /* ISR @  vector 0 */

#endif // _TIMER_0_
