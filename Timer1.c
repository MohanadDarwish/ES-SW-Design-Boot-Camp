#include "Timer1.h"

/* Public Timer1 Functions */
void Timer1_Init()//tTMR1_Prescaler_Value prescale_value
{
    //Disable timer 1 interrupt
    TIMER1_INTERRUPT_DISABLE();
    PHERIPHERAL_INTERRUPT_DISABLE();
    //Stop Timer1 by assigning external clock source
    TIMER1_CLOCK_SOURCE_EXTERNAL();
    //Note:The prescaler counter is cleared on writes to the TMR1H or TMR1L registers.
    TIMER1_SET_PRESCALER(Timer1_Prescaler_1);

    /* Clear interrupt flag */
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TIMER1_EXTERNAL_CLOCK_INPUT_SYNC_DISABLE();
    //GLOBAL_INTERRUPT_ENABLE();
    //enabling the timer1 oscilliator
    T1OSCEN = 1;
    //Clear the Timer1 register
    TMR1H=0x00; TMR1L=0x00;

}
void Timer1_Set_Start_value(U16 value)
{
    TMR1L =value&0x00ff;
    TMR1H =(value>>8)&0x00ff;
}
//U16 Timer1_Read_TMR1_Register(void)
//{
//    return( (((U16)TMR1H)<<8) | (TMR1L) );
//}
void Timer1_Start(void)
{
    /* Clear interrupt flag */
    TIMER1_INTERRUPT_FLAG_CLEAR();
    //internal clock source 8MHz/4
    TIMER1_CLOCK_SOURCE_INTERNAL();
    /* Start Timer */
    TIMER1_ENABLE();
}
void Timer1_Stop(void)
{
    //external clock is not connected so it's shut off
    TIMER1_CLOCK_SOURCE_EXTERNAL();
    TIMER1_DISABLE();
}
U8 Timer1_Calculate_Execution_Time_TMR1H(U8 caclulated_exec_time)
{
    if(TMR1H > caclulated_exec_time)
    {
        caclulated_exec_time=TMR1H;
    }
    return caclulated_exec_time;
}
U8 Timer1_Calculate_Execution_Time_TMR1L(U8 caclulated_exec_time)
{
    if(TMR1L > caclulated_exec_time)
    {
        caclulated_exec_time=TMR1L;
    }
    return caclulated_exec_time;
}
/* Public Timer1 Additional Functions */
void Timer1_Start_Timeout(const U16 ticks_till_ovf)
{
        Timer1_Set_Start_value(65535 - (ticks_till_ovf) );

        TIMER1_CLOCK_SOURCE_INTERNAL();
        /* Start Timer */
        TIMER1_ENABLE();
}
//U8 Timer1_Check_Timeout(void)
//{
//    return TMR1IF;
//}
//
void Timer1_Stop_Timeout(void)
{
     //Clear interrupt flag
    TIMER1_INTERRUPT_FLAG_CLEAR();
    //
    TIMER1_CLOCK_SOURCE_EXTERNAL();
    //
    TIMER1_DISABLE();
}

//void Timer1_Set_Sandwich_MS(U8 SANDWICH_DELAY)
//{
//
//    if (SANDWICH_DELAY > 0 && SANDWICH_DELAY <= 250 )
//    {
//        /* Select Prescalar = 1/8 */
//        T1CKPS1 = T1CKPS0 = 1;
//
//        /* Set initial value of timer */
//        TMR1H = (65536 -(250 * (U16)SANDWICH_DELAY))/256;
//        TMR1L = (65536 -(250 * (U16)SANDWICH_DELAY))%256;
//        //TMR1 = 65536 - (SANDWITCH_DELAY * 250);
//
//        /* Select internal clock source */
//        TIMER1_CLOCK_SOURCE_INTERNAL();
//
//        /* Clear interrupt flag */
//        TIMER1_INTERRUPT_FLAG_CLEAR();
//
//        /* Start Timer */
//        TIMER1_ENABLE();
//    }
//}
//
//void Timer1_Wait_For_Sandwich(void)
//{
//     /* Wait for Overflow */
//    while (TIMER1_INTERRUPT_GET_FLAG() == 0);
//    TIMER1_INTERRUPT_FLAG_CLEAR();
//
//    /* Stop Timer */
//    TIMER1_DISABLE();
//}
//
