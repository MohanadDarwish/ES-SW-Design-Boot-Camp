#include "SW.h"

#define SW_MAX_NUMBER         (4)
#define SW_MAX_STATE_NUMBER   (4)

U8 SW_WCET_H = 0;
U8 SW_WCET_L = 0;

SW_States SW_State_Info;
static U8 buzzer_2sec_countdown;// 10ms*100(buzzer countdown)*(2)SW_tick = 2sec
typedef enum
{
    SW_Level_Low = 0,
    SW_Level_High,
}tSW_Level;

typedef struct
{
    tSW_Name  name;
    tSW_State current_state;//current state of the switch
    tSW_Level samples[3];
}SW_Info;

static U8 sw_state_lookup_table[4][3]={  {1,0,0},//released
                                         {0,0,0},//pre-press
                                         {0,0,1},//press
                                         {0,1,1},//pre-released
                                         };

volatile static SW_Info sw_info[SW_MAX_NUMBER];

void SW_Init (tSW_Name sw_name)
{
            buzzer_2sec_countdown = 100;
            GPIO_InitPortPin(SW_PORT_CR, sw_name, GPIO_IN);
            sw_info[sw_name].samples[0] = SW_Level_High;
            sw_info[sw_name].samples[1] = SW_Level_High;
            sw_info[sw_name].samples[2] = SW_Level_High;
            //initial state
            sw_info[sw_name].current_state = SW_Released;
}

tSW_State SW_Get_State (tSW_Name sw_name )
{
    return sw_info[sw_name].current_state ;
}

void SW_Set_State (tSW_Name sw_name ,tSW_State state)
{
    sw_info[sw_name].current_state = state;
}

void SW_Update_Plus(void)
{
        //////////////////////////////////////////////////////
    //current_state        | n-2 | n-1  | n | next_state//
    //--------------------------------------------------//
    //released     | 1   | x    | 0 | pre-pressed       //
    //pre-pressed  | x   | 0    | 0 | pressed           //
    //pressed      | 0   | x    | 1 | pre-released      //
    //pre-released | x   | 1    | 1 | released          //
    //////////////////////////////////////////////////////

    //shift the 3 old samples to the left adding the new sample to (n)
    sw_info[SW_Plus].samples[0] = sw_info[SW_Plus].samples[1] ;//left shifting to sample n-1
    sw_info[SW_Plus].samples[1] = sw_info[SW_Plus].samples[2] ;//left shifting to sample n

    //check for new sample "Acquire the new Sample from the GPIO_ReadPortPin(SW1_DR)
    sw_info[SW_Plus].samples[2] = GPIO_ReadPortPin(SW_PORT_DR,SW_Plus);

    //check if the current 3 samples matching the desired 3 samples corresponding to the current state from the Look Up Table
         if((sw_info[SW_Plus].current_state == SW_Released) || (sw_info[SW_Plus].current_state == SW_Pressed))
         {
            if(( sw_info[SW_Plus].samples[0] == sw_state_lookup_table[ sw_info[SW_Plus].current_state ][0] ) &&
                    (sw_info[SW_Plus].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Plus].current_state ][2] ) )
            {
                //go to the next corresponding state to the current state
                //if True change state
                SW_Set_State(SW_Plus,(sw_info[SW_Plus].current_state) +1); // updating state
                 if(sw_info[SW_Plus].current_state == SW_Pre_Released)
                {
                            SW_State_Info = SW_Plus_Detected;
                            SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,0);
                            LCD_DEBUG_L2(1,0,"SW_Plus");
                            LCD_DEBUG(1,0,"SW_Pre_Released");//0,2
                }
                else
                {
                    SW_State_Info = SW_None_Detected;
                }
            }
         }
         else if((sw_info[SW_Plus].current_state == SW_Pre_Released) || (sw_info[SW_Plus].current_state == SW_Pre_Pressed))
         {
            if(( sw_info[SW_Plus].samples[1] == sw_state_lookup_table[ sw_info[SW_Plus].current_state ][1] ) &&
                    (sw_info[SW_Plus].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Plus].current_state ][2] ) )
            {
                //go to the next corresponding state to the current state
                //if True change state
                 if(sw_info[SW_Plus].current_state == SW_Pre_Released)
                {
                    SW_Set_State(SW_Plus,SW_Released); // updating state
                    LCD_DEBUG(1,0,"SW_Released");//1,3
                }
                else
                {
                    LCD_DEBUG(1,0,"SW_Pressed");//1,3
                    SW_Set_State(SW_Plus,(sw_info[SW_Plus].current_state) +1); // updating state
                }
            }
         }
    return;
}

void SW_Update_Minus(void)
{
        //////////////////////////////////////////////////////
    //current_state        | n-2 | n-1  | n | next_state//
    //--------------------------------------------------//
    //released     | 1   | x    | 0 | pre-pressed       //
    //pre-pressed  | x   | 0    | 0 | pressed           //
    //pressed      | 0   | x    | 1 | pre-released      //
    //pre-released | x   | 1    | 1 | released          //
    //////////////////////////////////////////////////////

    //shift the 3 old samples to the left adding the new sample to (n)
    sw_info[SW_Minus].samples[0] = sw_info[SW_Minus].samples[1] ;//left shifting to sample n-1
    sw_info[SW_Minus].samples[1] = sw_info[SW_Minus].samples[2] ;//left shifting to sample n

    //check for new sample "Acquire the new Sample from the GPIO_ReadPortPin(SW1_DR)
    sw_info[SW_Minus].samples[2] = GPIO_ReadPortPin(SW_PORT_DR,SW_Minus);

    //check if the current 3 samples matching the desired 3 samples corresponding to the current state from the Look Up Table
         if((sw_info[SW_Minus].current_state == SW_Released) || (sw_info[SW_Minus].current_state == SW_Pressed))
         {
            if(( sw_info[SW_Minus].samples[0] == sw_state_lookup_table[ sw_info[SW_Minus].current_state ][0] ) &&
                    (sw_info[SW_Minus].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Minus].current_state ][2] ) )
            {
                //go to the next corresponding state to the current state
                //if True change state
                    SW_Set_State(SW_Minus,(sw_info[SW_Minus].current_state) +1); // updating state
                     if(sw_info[SW_Minus].current_state == SW_Pre_Released)
                    {
                        SW_State_Info = SW_Minus_Detected;
                        SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,0);
                        LCD_DEBUG_L2(1,0,"SW_Minus");
                    }
                    else
                    {
                        SW_State_Info = SW_None_Detected;
                    }
                        LCD_DEBUG(1,0,"SW_Pre_Released");//0,2
            }
        }

         else if((sw_info[SW_Minus].current_state == SW_Pre_Released) || (sw_info[SW_Minus].current_state == SW_Pre_Pressed))
         {
            if(( sw_info[SW_Minus].samples[1] == sw_state_lookup_table[ sw_info[SW_Minus].current_state ][1] ) &&
                    (sw_info[SW_Minus].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Minus].current_state ][2] ) )
            {
                //go to the next corresponding state to the current state
                //if True change state
                 if(sw_info[SW_Minus].current_state == SW_Pre_Released)
                {
                    SW_Set_State(SW_Minus,SW_Released); // updating state
                     LCD_DEBUG(1,0,"SW_Released");//1,3
                }
                else
                {
                    LCD_DEBUG(1,0,"SW_Pressed");//1,3
                    SW_Set_State(SW_Minus,(sw_info[SW_Minus].current_state) +1); // updating state
                }
            }
         }
    return;
}
void SW_Update_Timer(void)
{
    //////////////////////////////////////////////////////
    //current_state        | n-2 | n-1  | n | next_state//
    //--------------------------------------------------//
    //released     | 1   | x    | 0 | pre-pressed       //
    //pre-pressed  | x   | 0    | 0 | pressed           //
    //pressed      | 0   | x    | 1 | pre-released      //
    //pre-released | x   | 1    | 1 | released          //
    //////////////////////////////////////////////////////

    //shift the 3 old samples to the left adding the new sample to (n)
    sw_info[SW_Timer].samples[0] = sw_info[SW_Timer].samples[1] ;//left shifting to sample n-1
    sw_info[SW_Timer].samples[1] = sw_info[SW_Timer].samples[2] ;//left shifting to sample n

    //check for new sample "Acquire the new Sample from the GPIO_ReadPortPin(SW1_DR)
    sw_info[SW_Timer].samples[2] = GPIO_ReadPortPin(SW_PORT_DR,SW_Timer);

    //check if the current 3 samples matching the desired 3 samples corresponding to the current state from the Look Up Table
         if((sw_info[SW_Timer].current_state == SW_Released) || (sw_info[SW_Timer].current_state == SW_Pressed))
         {
            if(( sw_info[SW_Timer].samples[0] == sw_state_lookup_table[ sw_info[SW_Timer].current_state ][0] ) &&
                    (sw_info[SW_Timer].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Timer].current_state ][2] ) )
            {
                //go to the next corresponding state to the current state
                //if True change state
                SW_Set_State(SW_Timer,(sw_info[SW_Timer].current_state) +1); // updating state
                if(sw_info[SW_Timer].current_state == SW_Pre_Released)
                {
                    SW_State_Info = SW_Timer_Detected;
                    SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,0);
                    LCD_DEBUG_L2(1,0,"SW_Timer");
                }
                else
                {
                    SW_State_Info = SW_None_Detected;
                }
                    LCD_DEBUG(1,0,"SW_Pre_Released");//0,2
            }
         }
         else if((sw_info[SW_Timer].current_state == SW_Pre_Released) || (sw_info[SW_Timer].current_state == SW_Pre_Pressed))
         {
            if(( sw_info[SW_Timer].samples[1] == sw_state_lookup_table[ sw_info[SW_Timer].current_state ][1] ) &&
                    (sw_info[SW_Timer].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Timer].current_state ][2] ) )
            {
                //go to the next corresponding state to the current state
                //if True change state
                 if(sw_info[SW_Timer].current_state == SW_Pre_Released)
                {
                    SW_Set_State(SW_Timer,SW_Released); // updating state
                     LCD_DEBUG(1,0,"SW_Released");//1,3
                }
                else
                {
                    LCD_DEBUG(1,0,"SW_Pressed");//1,3
                    SW_Set_State(SW_Timer,(sw_info[SW_Timer].current_state) +1); // updating state
                }
            }
         }
    return;
}
void SW_Update_Display(void)
{
    //shift the 3 old samples to the left adding the new sample to (n)
    sw_info[SW_Display].samples[0] = sw_info[SW_Display].samples[1] ;//left shifting to sample n-1
    sw_info[SW_Display].samples[1] = sw_info[SW_Display].samples[2] ;//left shifting to sample n
    //check for new sample "Acquire the new Sample from the GPIO_ReadPortPin(SW1_DR)
    sw_info[SW_Display].samples[2] = GPIO_ReadPortPin(SW_PORT_DR,SW_Display);
        //check if the current 3 samples matching the desired 3 samples corresponding to the current state from the Look Up Table
         if((sw_info[SW_Display].current_state == SW_Released) || (sw_info[SW_Display].current_state == SW_Pressed))
         {
            if(( sw_info[SW_Display].samples[0] == sw_state_lookup_table[ sw_info[SW_Display].current_state ][0] ) &&
                    (sw_info[SW_Display].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Display].current_state ][2] ) )
            {
                    if(sw_info[SW_Display].current_state == SW_Released )
                    {
                        // updating state-->Pre-Pressed
                        SW_Set_State(SW_Display,SW_Pre_Pressed);
                        SW_State_Info = SW_Display_Detected;
                        //setting for the next print makes it line 2 then line 1 if (flag =0)
                        SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,0);
                        if (GET_PROJECT_FLAG1(SW_200MS_FLAG) == 1)
                        {
                            SET_PROJECT_FLAG2(DISPLAY_SW_SECOND_SMALL_PRESS_DETECTED,1);
                        }
                        LCD_DEBUG(1,0,"SW_Pre_Pressed");//0,2
                        LCD_DEBUG_L3(1,0,"SW_Pre_Pressed");
                    }
                    else if(sw_info[SW_Display].current_state == SW_Pressed)
                    {
                        // updating state-->Pre-Released
                        SW_Set_State(SW_Display,SW_Pre_Released);
                        SW_State_Info = SW_None_Detected;
                        LCD_DEBUG(1,0,"SW_Pre_Released");//0,2
                        LCD_DEBUG_L3(1,0,"SW_Pre_Released");
                    }
            }
         }
         else if((sw_info[SW_Display].current_state == SW_Pre_Released) || (sw_info[SW_Display].current_state == SW_Pre_Pressed))
         {
            if(( sw_info[SW_Display].samples[1] == sw_state_lookup_table[ sw_info[SW_Display].current_state ][1] ) &&
                    (sw_info[SW_Display].samples[2] ==  sw_state_lookup_table[ sw_info[SW_Display].current_state ][2] ) )
            {
                 if(sw_info[SW_Display].current_state == SW_Pre_Released)
                {
                    // updating state --> to SW_Released
                    SW_Set_State(SW_Display,SW_Released);
                    SW_State_Info = SW_None_Detected;
                    LCD_DEBUG_L1(1,0,"Display n detected");
                    LCD_DEBUG(1,0,"SW_Released");//1,3
                    LCD_DEBUG_L3(1,0,"SW_Released");
                }
                //SW_Pre_Pressed
                else if(sw_info[SW_Display].current_state == SW_Pre_Pressed)
                {
                    // updating state --> to SW_Pressed
                    SW_Set_State(SW_Display,SW_Pressed);
                    SW_State_Info = SW_Display_200ms_detected;
                    SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,0);
                    LCD_DEBUG_L1(1,0,"Display detected");
                    LCD_DEBUG(1,0,"SW_Pressed");//1,3
                    LCD_DEBUG_L3(1,0,"SW_Pressed");
                }
            }
         }
    return;
}
//
//void SW_Update(tSW_Name sw_name)
//{
    //////////////////////////////////////////////////////
    //current_state        | n-2 | n-1  | n | next_state//
    // --------------------------------------------------//
    //released     | 1   | x    | 0 | pre-pressed       //
    //pre-pressed  | x   | 0    | 0 | pressed           //
//    pressed      | 0   | x    | 1 | pre-released      //
//    pre-released | x   | 1    | 1 | released          //
//    ////////////////////////////////////////////////////
//
//    shift the 3 old samples to the left adding the new sample to (n)
//    sw_info[sw_name].samples[0] = sw_info[sw_name].samples[1] ;//left shifting to sample n-1
//    sw_info[sw_name].samples[1] = sw_info[sw_name].samples[2] ;//left shifting to sample n
//
////    check for new sample "Acquire the new Sample from the GPIO_ReadPortPin(SW1_DR)
//    sw_info[sw_name].samples[2] = GPIO_ReadPortPin(SW_PORT_DR,sw_name);
//
////    check if the current 3 samples matching the desired 3 samples corresponding to the current state from the Look Up Table
//         if((sw_info[sw_name].current_state == SW_Released) || (sw_info[sw_name].current_state == SW_Pressed))
//         {
//            if(( sw_info[sw_name].samples[0] == sw_state_lookup_table[ sw_info[sw_name].current_state ][0] ) &&
//                    (sw_info[sw_name].samples[2] ==  sw_state_lookup_table[ sw_info[sw_name].current_state ][2] ) )
//            {
////                go to the next corresponding state to the current state
////                if True change state
//
//                    SW_Set_State(sw_name,(sw_info[sw_name].current_state) +1); // updating state
//
//                    if(sw_info[sw_name].current_state == SW_Pre_Pressed)
//                    {
//                        if (sw_name == SW_Display)
//                        {
//                            SW_State_Info = SW_Display_Detected;
//                            SET_PROJECT_FLAG2(DISPLAY_SYNC_LINE1_AND_LINE2,0);
//                        }
//                        LCD_DEBUG(1,0,"SW_Pre_Pressed");//0,2
//                    }
//                    else if(sw_info[sw_name].current_state == SW_Pre_Released)
//                    {
//
//                        SW_State_Info = SW_None_Detected;
//
//                        LCD_DEBUG(1,0,"SW_Pre_Released");//0,2
//                    }
//            }
//         }
//         else if((sw_info[sw_name].current_state == SW_Pre_Released) || (sw_info[sw_name].current_state == SW_Pre_Pressed))
//         {
//            if(( sw_info[sw_name].samples[1] == sw_state_lookup_table[ sw_info[sw_name].current_state ][1] ) &&
//                    (sw_info[sw_name].samples[2] ==  sw_state_lookup_table[ sw_info[sw_name].current_state ][2] ) )
//            {
////                go to the next corresponding state to the current state
////                if True change state
//                 if(sw_info[sw_name].current_state == 3)
//                {
//                    SW_Set_State(sw_name,SW_Released); // updating state
//                     if(sw_name == SW_Display)
//                    {
//                        SW_State_Info = SW_None_Detected;
//                        LCD_DEBUG_L1(1,0,"Display n detected");
//                    }
//                     LCD_DEBUG(1,0,"SW_Released");//1,3
//                }
//                else
//                {
//                    if(sw_name == SW_Display)
//                    {
//                        SW_State_Info = SW_Display_200ms_detected;
//                        SET_PROJECT_FLAG2(DISPLAY_SYNC_LINE1_AND_LINE2,0);
//                        LCD_DEBUG_L1(1,0,"Display detected");
//                    }
//                    LCD_DEBUG(1,0,"SW_Pressed");//1,3
//                    SW_Set_State(sw_name,(sw_info[sw_name].current_state) +1); // updating state
//                }
//            }
//         }
//    return;
//}

//SW Task
void SW_Task(void)
{
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Set_Start_value(0);
//    Timer1_Start();
//    #endif // CALC_EXEC_TIME
//    TIMER0_INTERRUPT_DISABLE();
    //start timer1 sandwich
    Timer1_Start_Timeout(998);//499 us in 998 ticks(0.5 per tick)

    if( ( ((sys_tick) % TICK_COUNTER_SW) == 0 ) || (sys_tick ==0) )
    {
        SW_Update_Display();  //every 40 ms
        if (SW_State_Info != SW_None_Detected)
        {
            Buzzer_On();
            buzzer_2sec_countdown--;
        }
        if(buzzer_2sec_countdown < 100 &&  buzzer_2sec_countdown > 0)
        {
            buzzer_2sec_countdown--;
        }
        else if ( buzzer_2sec_countdown == 0 )
        {
            Buzzer_Off();
            buzzer_2sec_countdown = 100;
        }
    }
    if( ( ((sys_tick + 1) % TICK_COUNTER_SW  ) == 0 ) )//|| (sys_tick ==0) )
    {
        SW_Update_Minus();    //every 40 ms
    }
    if( ( ( (sys_tick + 2) % TICK_COUNTER_SW  ) == 0 )) //|| (sys_tick ==0) )
    {
        SW_Update_Timer();    //every 40 ms
    }
    if( ( ((sys_tick + 3) % TICK_COUNTER_SW  ) == 0 ) )
    {
        SW_Update_Plus();     //every 40 ms
    }

    //stop timer1 sandwich
    while(!TMR1IF);
    Timer1_Stop_Timeout();
//    TIMER0_INTERRUPT_ENABLE();
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Stop();
//    SW_WCET_H = Timer1_Calculate_Execution_Time_TMR1H(SW_WCET_H);
//    SW_WCET_L = Timer1_Calculate_Execution_Time_TMR1L(SW_WCET_L);
//    #endif // CALC_EXEC_TIME
}

