#include "sEOS.h"

volatile U16 sys_tick;//sys_tick = 10ms from timer 0
volatile U8 project_flags1;
volatile U8 project_flags2;

U8 exec_val[5]={'H','9','9','9',0};

void sEOS_Init()
{
    sys_tick=0;
    Timer0_Init(Timer0_Prescaler_128);// (256*4*n/*8MHz)
    Timer0_Set_Start_value(99);//      10.048ms                tick=9.984ms
    Timer0_Start();
}
void sEOS_Fan_Turn_Off(void)
{
   Timer0_Stop();
   TIMER0_INTERRUPT_FLAG_CLEAR();
   Speed_Motor_Stop();
   Swing_Motor_Stop();

   SSD_Disable();

   LCD_Clear_Screen();
   LCD_Write_String("Turning OFF ...");
   Delay_MS(2000);
   LCD_Clear_Screen();
}
void sEOS_IRQ_Handler(void) __interrupt 0
{
    if(sys_tick == 5999)
    {
//        #if _CALC_EXEC_TIME ==1
//            GLOBAL_INTERRUPT_DISABLE();
//                        LCD_Clear_Screen();
//            itoa(Speed_Motor_WCET_H,exec_val,4);//19.5us
//                        exec_val[0] = 'H';
//                        LCD_ERROR(0,0,exec_val);
//            itoa(Speed_Motor_WCET_L,exec_val,4);//19.5us
//                        exec_val[0] = 'L';
//                        LCD_ERROR(1,0,exec_val);
//            itoa(SW_WCET_H,exec_val,4);//2.56ms
//                        exec_val[0] = 'H';
//                        LCD_ERROR(0,0,exec_val);
//            itoa(SW_WCET_L,exec_val,4);//2.56ms
//                        exec_val[0] = 'L';
//                        LCD_ERROR(1,0,exec_val);
//            itoa(Display_WCET_H,exec_val,4);//60us
//                        exec_val[0] = 'H';
//                        LCD_ERROR(0,4,exec_val);
//            itoa(Display_WCET_L,exec_val,4);//60us
//                        exec_val[0] = 'L';
//                        LCD_ERROR(1,4,exec_val);
//            itoa(Swing_Motor_WCET_H,exec_val,4);//3.58ms
//                        exec_val[0] = 'H';
//                        LCD_ERROR(0,8,exec_val);
//            itoa(Swing_Motor_WCET_L,exec_val,4);//3.58ms
//                        exec_val[0] = 'L';
//                        LCD_ERROR(1,8,exec_val);
//            itoa(Slider_WCET_H,exec_val,4);//9.5us
//                        exec_val[0] = 'H';
//                        LCD_ERROR(0,12,exec_val);
//            itoa(Slider_WCET_L,exec_val,4);//9.5us
//                        exec_val[0] = 'L';
//                        LCD_ERROR(1,12,exec_val);
//                        Delay_MS(3000);
//        #else
        sys_tick = 0;
//        #endif // _CALC_EXEC_TIME
    }
    else
    {
      sys_tick++;
    }
    //run in first 0.55ms
    //
    if (GET_PROJECT_FLAG2(STARTUP_FLAG) == 0)
    {
        Swing_Motor_Task();//exec in 0.3ms
    }
    //
    //-------------------------------------------//
    //
    if (GET_PROJECT_FLAG2(STARTUP_FLAG) == 0)
    {
    Slider_Task();//exec in 0.1ms
    }
    //
    //-------------------------------------------//
    Speed_Motor_Task();
    //
    //-------------------------------------------//
    //start timer1 sandwich
//    Timer1_Start_Timeout(xxxx);//100 us in 200 ticks(0.5 per tick)
    //
    if (GET_PROJECT_FLAG2(STARTUP_FLAG) == 0)
    {
    SW_Task();
    }
    //
    //stop timer1 sandwich
//    while(! Timer1_Check_Timeout());
//    Timer1_Stop_Timeout();
    //-------------------------------------------//
    //start timer1 sandwich
//    Timer1_Start_Timeout(xxxx);//100 us in 200 ticks(0.5 per tick)
    //
    Display_Task();
    //
    //stop timer1 sandwich
//    while(! Timer1_Check_Timeout());
//    Timer1_Stop_Timeout();
    //-------------------------------------------//
    TIMER0_INTERRUPT_FLAG_CLEAR();
    Timer0_Set_Start_value(99);
}

