#include "Speed_Motor.h"

//sys_tick = 10ms from timer 0
//U8 Speed_Motor_WCET_H = 0;
//U8 Speed_Motor_WCET_L = 0;

U8 firing_angle ;
static U8 desired_angle;
static void Speed_Motor_Set_Firing_Angle(void);

void Speed_Motor_Init(void)
{
    firing_angle = Speed_Motor_Initial_Speed;
    desired_angle = Speed_Motor_Min_Speed;
    //configure speed motor (triac pin)
    GPIO_InitPortPin(SPEED_MOTOR_TRIAC_CR,SPEED_MOTOR_TRIAC_PIN,GPIO_OUT);
    SW_State_Info = SW_None_Detected;
    //initially the AC Motor speed is at 170degree from the sine wave
    Speed_Motor_Set_Firing_Angle();
    SET_PROJECT_FLAG2(STARTUP_FLAG,1);
}

void Speed_Motor_Start(void)
{
    firing_angle = Speed_Motor_Min_Speed;
    Speed_Motor_Set_Firing_Angle();
}

void Speed_Motor_Stop(void)
{
    firing_angle = Speed_Motor_Stop_Speed;
    //stopping the ac motor
    Speed_Motor_Set_Firing_Angle();
}
void Speed_Motor_Check_SW(void)
{
    if( (SW_State_Info == SW_Plus_Detected) && (GET_PROJECT_FLAG1(TIMER_SWITCH_PRESSED_DETECTED_FLAG) == 0 ) )
    {
        switch (desired_angle)
        {
            case (Speed_Motor_Min_Speed):
                desired_angle= Speed_Motor_Mid_Speed;//90
                break;
            case (Speed_Motor_Mid_Speed):
                desired_angle= Speed_Motor_Max_Speed;//10
                break;
            case Speed_Motor_Max_Speed:
                desired_angle= Speed_Motor_Max_Speed;//10
                break;
        }
        SW_State_Info = SW_None_Detected;
    }
    else if( (SW_State_Info == SW_Minus_Detected) && (GET_PROJECT_FLAG1(TIMER_SWITCH_PRESSED_DETECTED_FLAG) == 0 ) )
    {
        switch (desired_angle)
        {
            case Speed_Motor_Min_Speed:
                desired_angle= Speed_Motor_Min_Speed;//140
                break;
            case Speed_Motor_Mid_Speed:
                desired_angle= Speed_Motor_Min_Speed;//140
                break;
            case Speed_Motor_Max_Speed:
                desired_angle= Speed_Motor_Mid_Speed;//90
                break;
        }
        SW_State_Info = SW_None_Detected;
    }
}
//private function
static void Speed_Motor_Set_Firing_Angle(void)//called every 80ms+(firing_angle*55.5us)
{
    //difference between desired angle and current
    if(firing_angle > desired_angle)
    {
        firing_angle--;
        //output triac pule of 100us at corresponding Firing angle
        SET_PROJECT_FLAG2(SPEED_MOTOR_VALUE_CHANGED_FOR_DISPLAY_FLAG,1);
    }
    else if(firing_angle < desired_angle)
    {
        firing_angle++;
        //output triac pule of 100us at corresponding Firing angle
        SET_PROJECT_FLAG2(SPEED_MOTOR_VALUE_CHANGED_FOR_DISPLAY_FLAG,1);
    }
    else
    {
        firing_angle = desired_angle;
    }
    if ((firing_angle == 140) && GET_PROJECT_FLAG2(STARTUP_FLAG) == 1)
    {
        SET_PROJECT_FLAG2(STARTUP_FLAG, 0);
    }
}
void Speed_Motor_TRIAC_Output_Pulse(void)
{
    //1 triac pin
    GPIO_WritePortPin(SPEED_MOTOR_TRIAC_DR, SPEED_MOTOR_TRIAC_PIN,1);
    //timer1_start_100us_delay()
    Timer1_Start_Timeout(200);
    while(!TMR1IF);
    Timer1_Stop_Timeout();
    //wait 100us roughly 2 degrees
//    Delay_US(DELAY_100US);//needs to be replaced by a timer1 delay
    //0 traic pin
    //timer1_ovf_flag_detected()
    GPIO_WritePortPin(SPEED_MOTOR_TRIAC_DR, SPEED_MOTOR_TRIAC_PIN,0);
}
void Speed_Motor_Task(void)
{
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Set_Start_value(0);
//    Timer1_Start();
//    #endif // CALC_EXEC_TIME
    //start timer1 sandwich
//    TIMER0_INTERRUPT_DISABLE();
    Timer1_Start_Timeout((firing_angle-9)*111);//(140-10degree)7215 us in 14430 ticks(0.5 per tick)
    while(!TMR1IF);
    Timer1_Stop_Timeout();
    if  ( ((sys_tick % TICK_COUNTER_TRIAC_PULSE ) == 0 ) || (sys_tick ==0) )//10ms*2tick
    {
        Speed_Motor_TRIAC_Output_Pulse();
    }
    if ((GET_PROJECT_FLAG2(STARTUP_FLAG) == 1) )
    {
        Timer1_Start_Timeout(((160-(firing_angle-9))*111)-200);
    }
    else
    {
        Timer1_Start_Timeout(((130-(firing_angle-9))*111)-200);
    }
    if  ( ((sys_tick % TICK_COUNTER_SPEED_MOTOR ) == 0 ) || (sys_tick ==0) )//10ms*2tick
    {
        Speed_Motor_Check_SW();//2tick
    }
    if  ( ((sys_tick % TICK_SOFT_SWITCHING ) == 0 ) || (sys_tick ==0) )//10ms*2tick
    {
        Speed_Motor_Set_Firing_Angle();
    }

    //stop timer1 sandwich
    while(!TMR1IF);
    Timer1_Stop_Timeout();
//    TIMER0_INTERRUPT_ENABLE();
//    #if _CALC_EXEC_TIME ==1
//   // Timer1_Stop();
//   // Speed_Motor_WCET_H = Timer1_Calculate_Execution_Time_TMR1H(Speed_Motor_WCET_H);
//    //Speed_Motor_WCET_L = Timer1_Calculate_Execution_Time_TMR1L(Speed_Motor_WCET_L);
//    #endif // CALC_EXEC_TIME
}
