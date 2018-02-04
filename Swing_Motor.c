#include "Swing_Motor.h"

U8 Swing_Motor_WCET_H = 0;
U8 Swing_Motor_WCET_L = 0;
static void Swing_Motor_Set_Swinging_Angle(void);

//initially the Swing Motor angle 0 degrees initially
static U8 swinging_angle;

//initializing the motor control signal pins direction(output) and setting the initial swing angle(0 degrees)
void Swing_Motor_Init(void)
{
    swinging_angle = Swing_Motor_0_Degrees;
    //Initializing the 4 pins for the swing motor as output to single the swing motor
    GPIO_InitPortPin(SWING_MOTOR_PORT_CR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,GPIO_OUT);//pin0
    GPIO_InitPortPin(SWING_MOTOR_PORT_CR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,GPIO_OUT);//pin1
    GPIO_InitPortPin(SWING_MOTOR_PORT_CR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,GPIO_OUT);//pin2
    GPIO_InitPortPin(SWING_MOTOR_PORT_CR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,GPIO_OUT);//pin3
    Swing_Motor_Stop();
}

//setting/changing the angle of swinging of the swing motor as desired from the values 0,45,90,135,180,225,270,315,360
void Swing_Motor_Set_Swinging_Angle(void)
{
    swinging_angle = (U8)(SLIDER_Reading/113);
}

//starting the swing motor P.S. the motor won't start swinging until this API is invoked
void Swing_Motor_Start(void)
{
    //output 4bits for the swing motor to operate (4 bit timer configuration is now invoked by timer_start)
     switch(swinging_angle)
    {
     case Swing_Motor_0_Degrees:
        //0...113.5 angle 0           (0)
        //0000
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,LOW_LEVEL);
        break;
     case Swing_Motor_45_Degrees:
         //113.5...113.5*2 angle 45   (1)
        //0001
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,HIGH_LEVEL);
        break;
     case Swing_Motor_90_Degrees:
       //113.5*2...113.5*3 angle 90  (2)
        //0010
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,HIGH_LEVEL);
        break;
    case Swing_Motor_135_Degrees:
        //113.5*3...113.5*4 angle 135 (3)
        //0011
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,HIGH_LEVEL);
        break;
    case Swing_Motor_180_Degrees:
        //113.5*4...113.5*5 angle 180 (4)
        //0100
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,LOW_LEVEL);
        break;
    case Swing_Motor_225_Degrees:
        //113.5*5...113.5*6 angle 225 (5)
        //0101
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,HIGH_LEVEL);
        break;
    case Swing_Motor_270_Degrees:
        //113.5*6...113.5*7 angle 270 (6)
        //0110
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,LOW_LEVEL);
        break;
    case Swing_Motor_315_Degrees:
        //113.5*7...113.5*8 angle 315 (7)
        //0111
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,HIGH_LEVEL);
        break;
    case Swing_Motor_360_Degrees:
        //113.5*8...113.5*9 angle 360 (8)
        //1xxx 1111
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,HIGH_LEVEL);
        GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,HIGH_LEVEL);
        break;
    }
}

//stopping the swing motor P.S. the motor won't stop swinging until this API is invoked
void Swing_Motor_Stop(void)
{
    //stop motor 4 bits => 0 angle
    GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_0,LOW_LEVEL);
    GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_1,LOW_LEVEL);
    GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_2,LOW_LEVEL);
    GPIO_WritePortPin(SWING_MOTOR_PORT_DR,SWING_MOTOR_CONTROL_SIGNAL_BIT_3,LOW_LEVEL);
}

void Swing_Motor_Task(void)
{
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Set_Start_value(0);
//    Timer1_Start();
//    #endif // CALC_EXEC_TIME
//    TIMER0_INTERRUPT_DISABLE();
    //start timer1 sandwich
    Timer1_Start_Timeout(768);//384 us in 768 ticks(0.5 per tick)
//

    if( (((sys_tick) % TICK_COUNTER_SWING_MOTOR) == 0 ) || (sys_tick ==0) )// 10ms * 1tick
    {
        if(GET_PROJECT_FLAG1(SLIDER_VALUE_CHANGED_FOR_SWING_MOTOR_FLAG) == 1)
        {
            Swing_Motor_Set_Swinging_Angle();
            SET_PROJECT_FLAG1(SLIDER_VALUE_CHANGED_FOR_SWING_MOTOR_FLAG, 0);
        }
    }
    if( (((sys_tick+1) % TICK_COUNTER_SWING_MOTOR) == 0 ) );//|| (sys_tick ==0) )// 10ms * 1tick
    {
       Swing_Motor_Start();
    }
    //
    //stop timer1 sandwich
    while(!TMR1IF);
    Timer1_Stop_Timeout();
//    TIMER0_INTERRUPT_ENABLE();
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Stop();
//    Swing_Motor_WCET_H = Timer1_Calculate_Execution_Time_TMR1H(Swing_Motor_WCET_H);
//    Swing_Motor_WCET_L = Timer1_Calculate_Execution_Time_TMR1L(Swing_Motor_WCET_L);
//    #endif // CALC_EXEC_TIME

}
