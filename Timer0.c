#include "Timer0.h"

volatile static U8 Start_Value;

/* Public Timer0 Functions */
void Timer0_Init(tTMR0_Prescaler_Value prescaler_value)
{
    Start_Value = 0;
    //Disable timer 0 interrupt
    TIMER0_INTERRUPT_DISABLE();
    //Disable the Timer0 HW module by selecting external clock source which isn't assigned to anything
    TIMER0_ASSIGN_CLOCK_SOURCE(TIMER0_CLOCK_SOURCE_EXTERNAL);
    TIMER0_ASSIGN_PORTB_PULL_UP(TIMER0_PORTB_PULL_UP_DISABLE);
    TIMER0_ASSIGN_INTERRUPT_EDGE(TIMER0_INTERRUPT_EDGE_FALLING);
    TIMER0_ASSIGN_PRESCALER(TIMER0_PRESCALER_TO_TIMER);
    TIMER0_SET_PRESCALER(prescaler_value);
    TIMER0_ASSIGN_SOURCE_EDGE(TIMER0_SOURCE_EDGE_RISING);
    GLOBAL_INTERRUPT_ENABLE();
}

void Timer0_Start(void)
{
    TIMER0_ASSIGN_CLOCK_SOURCE(TIMER0_CLOCK_SOURCE_INTERNAL);

    TIMER0_INTERRUPT_ENABLE();
}

void Timer0_Stop(void)
{
    TIMER0_ASSIGN_CLOCK_SOURCE(TIMER0_CLOCK_SOURCE_EXTERNAL);
    TIMER0_INTERRUPT_DISABLE();
    Timer0_Set_Start_value(0);
}

void Timer0_Set_Start_value(U8 value)
{
    Start_Value = value ;
    TMR0 = Start_Value;
}
