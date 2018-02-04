#include "Slider.h"

U8 Slider_WCET_H = 0;
U8 Slider_WCET_L = 0;
U16 SLIDER_Reading;

void Slider_Init(void)
{
    SLIDER_Reading = 0;
    ADC_Init();
    //idk if we need to init the slider pin direction or not depends on the adc config if it is enough or not
    GPIO_InitPortPin(SLIDER_PORT_CR,SLIDER_PIN,GPIO_IN);
}
void Slider_Get_Value(void)
{
    U16 new_value = 1024;
    ADC_Update();
    new_value = ADC_Read();

    if(new_value != SLIDER_Reading )
    {
        SET_PROJECT_FLAG1(SLIDER_VALUE_CHANGED_FOR_SWING_MOTOR_FLAG, 1);
        SET_PROJECT_FLAG1(SLIDER_VALUE_CHANGED_FOR_DISPLAY_FLAG, 1);
    }
    SLIDER_Reading=new_value;
}
void Slider_Task(void)
{
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Set_Start_value(0);
//    Timer1_Start();
//    #endif // CALC_EXEC_TIME
//    TIMER0_INTERRUPT_DISABLE();
    //start timer1 sandwich
    Timer1_Start_Timeout(333);//166.5 us in 333 ticks(0.5 per tick)
    //
    if( ((sys_tick % TICK_COUNTER_SLIDER) == 0 ) || (sys_tick ==0) )// 10ms * 1tick
    {
            Slider_Get_Value();
    }
    //
    //stop timer1 sandwich
    while(!TMR1IF);
    Timer1_Stop_Timeout();
//    TIMER0_INTERRUPT_ENABLE();
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Stop();
//    Slider_WCET_H = Timer1_Calculate_Execution_Time_TMR1H(Slider_WCET_H);
//    Slider_WCET_L = Timer1_Calculate_Execution_Time_TMR1L(Slider_WCET_L);
//    #endif // CALC_EXEC_TIME

    //0 , 45 , 90 , 135 , 180 , 225 , 270 , 315 , 360

}


