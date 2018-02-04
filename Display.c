#include "Display.h"

U8 Display_WCET_H = 0;
U8 Display_WCET_L = 0;

static U16 swing_string_countdown;
static U8 SW_display_already_pressed;
static U8  current_hrs;
static U8  current_min;
static tSSD SSD_counter;
static U8 slider_read;
static U16 ssd_10sec_countdown;//10ms*500(10sec countdown)*2(ssd_period) = 10sec
static U8 asterisks_index =0;
static U8 str_index =0;
static U8 string_identifier;

U8 buf[4]={0x34};

typedef struct
{
    tSSD ssd_name;
    tSSD_Symbol ssd_symbol;
}tDisplay_SSD_Info;

static tDisplay_SSD_Info display_ssd_info[4];

void Display_Init(tSSD ssd, tLCD_Mode mode)
{
    swing_string_countdown = 0;
    SW_display_already_pressed = 0;
    current_hrs = 0;
    current_min = 0;
    SSD_counter = 0;
    slider_read = 0;
    ssd_10sec_countdown = 0;

    SSD_Init(ssd);//SSD_ALL
    LCD_Init(mode);
    SET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG, 1);

    SET_PROJECT_FLAG2(DISPLAY_SW_SECOND_SMALL_PRESS_DETECTED, 0);


    LCD_DEBUG_L1(1,0,"Disp_Init");
}

void Display_Check_SW(void)
{
    //logic for 200ms sw_display  detection//
    if (SW_State_Info == SW_Display_200ms_detected && SW_display_already_pressed == 10)
    {
        SET_PROJECT_FLAG1(SW_200MS_FLAG, 1);
        SET_PROJECT_FLAG1(DISPLAY_SWING_VALUE_PRINTED_FLAG, 1);
        SET_PROJECT_FLAG2(DISPLAY_SLIDER_ASTREIKS_PRINTING_IN_PROGRESS,1);
    }
    else if(SW_State_Info == SW_Display_200ms_detected && SW_display_already_pressed < 10)
    {
        SW_display_already_pressed++;
    }
    else if(SW_display_already_pressed != 10)
    {
        SW_display_already_pressed = 0;
    }
    else if( (GET_PROJECT_FLAG1(SW_200MS_FLAG) == 1) && (GET_PROJECT_FLAG2(DISPLAY_SW_SECOND_SMALL_PRESS_DETECTED) == 1))
    {

        SW_display_already_pressed = 0;
        SET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG, 1);
        SET_PROJECT_FLAG1(SW_200MS_FLAG, 0);
        swing_string_countdown = 0;
        SET_PROJECT_FLAG2(DISPLAY_SW_SECOND_SMALL_PRESS_DETECTED, 0);
    }
    //logic for 200ms sw_display  detection//
    //////////////////////////////////////////////////////////////
    if(SW_State_Info == SW_Timer_Detected)
    {
        if (GET_PROJECT_FLAG1(TIMER_SWITCH_PRESSED_DETECTED_FLAG) == 0)
        {
            SET_PROJECT_FLAG1(TIMER_SWITCH_PRESSED_DETECTED_FLAG, 1);//first iteration
            SET_PROJECT_FLAG1(START_COUNTDOWN_FLAG, 0);
        }
        else
        {
            SET_PROJECT_FLAG1(TIMER_SWITCH_PRESSED_DETECTED_FLAG, 0);

            if ( (current_hrs > 0) && (current_hrs <=4) )
            {
                SET_PROJECT_FLAG1(START_COUNTDOWN_FLAG, 1);
            }
            else
            {
                SET_PROJECT_FLAG1(START_COUNTDOWN_FLAG, 0);
            }
        }
        SW_State_Info = SW_None_Detected;
    }
    //////////////////////////////////////////////////////////////
    if(GET_PROJECT_FLAG1(TIMER_SWITCH_PRESSED_DETECTED_FLAG) == 1)
    {
        if(SW_State_Info == SW_Plus_Detected)
        {
            switch (current_hrs)
            {
                case 0:
                    current_hrs = 1;
                    current_min = 0;
                    break;
                case 1:
                    current_hrs = 2;
                    current_min = 0;
                    break;
                case 2:
                    current_hrs = 4;
                    current_min = 0;
                    break;
                case 3:
                case 4:
                    current_hrs = 0;
                    current_min = 0;
                    break;
            }
            SW_State_Info = SW_None_Detected;
        }
        //////////////////////////////////////////////////////////////
        else if(SW_State_Info == SW_Minus_Detected)
        {
            switch (current_hrs)
            {
                case 0:
                    current_hrs = 4;
                    current_min = 0;
                    break;
                case 1:
                    current_hrs = 0;
                    current_min = 0;
                    break;
                case 2:
                    current_hrs = 1;
                    current_min = 0;
                    break;
                case 3:
                case 4:
                    current_hrs = 2;
                    current_min = 0;
                    break;
            }
            SW_State_Info = SW_None_Detected;
        }
    }
}

void Display_Calculate_Time(void)
{
    if (GET_PROJECT_FLAG1(START_COUNTDOWN_FLAG) == 1)//cal_state was set from Display_Check_SW()
    {
        if ( (current_min != 0) && (current_min <= 59) )
        {
            current_min--;
        }
        else if( (current_hrs != 0) && (current_hrs <= 4) )
        {
            current_hrs--;
            current_min = 59;
        }
        else
        {
             sEOS_Fan_Turn_Off();
        }
    }
}

void Display_Update_SSD(void)
{
    if (ssd_10sec_countdown < 500 )
    {
        display_ssd_info[SSD_Hrs_Tens].ssd_symbol  = SSD_Symbol_Null;
        display_ssd_info[SSD_Hrs_Units].ssd_symbol = SSD_Symbol_H;//current_hrs;
        display_ssd_info[SSD_Min_Tens].ssd_symbol  = SSD_Symbol_I;
        display_ssd_info[SSD_Min_Units].ssd_symbol = SSD_Symbol_Null;
        ssd_10sec_countdown++;
    }
    else
    {
        display_ssd_info[SSD_Hrs_Tens].ssd_symbol  = SSD_Symbol_0;
        display_ssd_info[SSD_Hrs_Units].ssd_symbol = current_hrs;//current_hrs;
        display_ssd_info[SSD_Min_Tens].ssd_symbol  = current_min/10;
        display_ssd_info[SSD_Min_Units].ssd_symbol = current_min%10;
    }
    SSD_Write_Symbol(SSD_counter, display_ssd_info[SSD_counter].ssd_symbol);

    if (SSD_counter == 3)
    {
        SSD_counter = 0;
    }
    else
    {
        SSD_counter++;
    }
}
void Display_Enable_SSD(void)
{
    SSD_Enable();
}
void Display_Disable_SSD(void)
{
    SSD_Disable();
}
void Display_Clear_LCD(void)
{
    LCD_Clear_Screen();
}
void Display_Update_LCD(U8* str, U8 line,U8 Column)
{
    LCD_GoTo(line,Column);
    LCD_Write_String(str);
}
void Display_LCD_Print_Character(U8* str, U8 line, U8 column)
{
    if (string_identifier == str[2])
    {
        if( str[str_index]  != '\0')     //"  Speed Motor" "  Swing Value"
        {
        LCD_GoTo(line,str_index + column);
        LCD_Write_Character(str[str_index]);//str1[0]
        str_index++;
        }
        else
        {
            str_index = 0;
        }
    }
    else
    {
        str_index = 0;
        string_identifier = str[2];

        if( str[str_index]  != '\0')     //"  Speed Motor" "  Swing Value"
        {
            LCD_GoTo(line,str_index + column);
            LCD_Write_Character(str[str_index]);//str1[0]
            str_index++;
        }
        else
        {
            str_index = 0;
        }
    }
}

void Display_LCD_Print_asterisks(void)
{
    if(GET_PROJECT_FLAG2(DISPLAY_SLIDER_ASTREIKS_PRINTING_IN_PROGRESS) == 1)
    {
       slider_read = (U8)(SLIDER_Reading/114);//0-->8
       SET_PROJECT_FLAG2(DISPLAY_SLIDER_ASTREIKS_PRINTING_IN_PROGRESS,0);
    }
   // if(slider_read)
    if(asterisks_index < 8)
    {
         if(slider_read > asterisks_index)
        {
            Display_Update_LCD("*", 1,7-asterisks_index);   //7 6  5  4  3  2  1  0
            Display_Update_LCD("*", 1,8+asterisks_index);  //8 9 10 11 12 13 14 15
            asterisks_index++;
        }
        else if(asterisks_index >= slider_read)
        {
            Display_Update_LCD(" ", 1,7-asterisks_index);   //0  1  2  3  4  5  6 7
            Display_Update_LCD(" ", 1,8+asterisks_index);//15 14 13 12 11 10 9 8
            asterisks_index++;
        }
    }
    else
    {
        asterisks_index = 0;
        SET_PROJECT_FLAG2(DISPLAY_SLIDER_ASTREIKS_PRINTING_IN_PROGRESS,1);
    }
}
void Display_Task(void)
{
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Set_Start_value(0);
//    Timer1_Start();
//    #endif // CALC_EXEC_TIME
//    TIMER0_INTERRUPT_DISABLE();
//    start timer1 sandwich
    Timer1_Start_Timeout(3431);//1715.5us in 3431 ticks(0.5 per tick)
    if( (( (sys_tick +1) % TICK_COUNTER_SSD) == 0 ) )//|| (sys_tick ==0))// 10ms * 1tick//odd tick
    {
        if (GET_PROJECT_FLAG2(STARTUP_FLAG) == 0)
        {
            Display_Check_SW();
        }
        Display_Update_SSD();
    }
    //////////////////////////////////////////////////////////////

        if ( (((sys_tick+1) % TICK_COUNTER_SECONDS ) == 0 ) )//|| (sys_tick ==0) ) // 10ms * 100tick
        {
            if (GET_PROJECT_FLAG1(DOT_TOGGLE_FLAG) == 0)
            {
                SET_PROJECT_FLAG1(DOT_TOGGLE_FLAG, 1);
            }
            else
            {
                SET_PROJECT_FLAG1(DOT_TOGGLE_FLAG, 0);
            }
        }
    if (GET_PROJECT_FLAG2(STARTUP_FLAG) == 0)
    {
        //////////////////////////////////////////////////////////////
        if ( ( ((sys_tick) % TICK_COUNTER_CALC ) == 0 ) || (sys_tick ==0) ) // 10ms * 6000tick
        {
            Display_Calculate_Time();
        }
    ///////////////////////////////////////////////////////////////////////////// LCD even tick ////////////////////////////////////////////////////
        if  ( ((sys_tick % TICK_COUNTER_LCD ) == 0 ) || (sys_tick ==0) ) // 10ms * 2tick
        {
            if(GET_PROJECT_FLAG1(SW_200MS_FLAG) == 1)
            {
                if ((GET_PROJECT_FLAG1(DISPLAY_SWING_VALUE_PRINTED_FLAG) == 1) || (GET_PROJECT_FLAG1(SLIDER_VALUE_CHANGED_FOR_DISPLAY_FLAG) == 1))
                {
                    //
                    Display_Disable_SSD();
                    //
                    Display_LCD_Print_asterisks();
                    //
                    Display_Enable_SSD();
                    //
                    if (asterisks_index == 0);
                    {
                       //setting for the next print makes it line 1 then line 2 if (flag =1)
                       SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,1);
                    }
                }
                if (swing_string_countdown == 1000)
                {
                    SET_PROJECT_FLAG1(SW_200MS_FLAG, 0);
                    SW_display_already_pressed = 0;
                    swing_string_countdown = 0;
                    SET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG, 1);
                }
                else
                {
                    swing_string_countdown++;
                }
            }
            //----------------------------------------------------------------- LCD even tick ----------------------------------------------------------//
            else
            {
                if( ((GET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG) == 1) || (GET_PROJECT_FLAG2(SPEED_MOTOR_VALUE_CHANGED_FOR_DISPLAY_FLAG) == 1))&& GET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2) == 0)
                {
                    //
                    Display_Disable_SSD();
                    //
    //                Display_Clear_LCD();
                    //
    //                Display_Update_LCD("Speed=    degree",1,0);
                    Display_LCD_Print_Character("Speed=    degree",1, 0);
                    itoa((U16)firing_angle,buf,3);
                    Display_Update_LCD(buf,1,6);
                    //
                    Display_Enable_SSD();
                    //
                    if (str_index == 0)
                    {
                        if((GET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG) == 1))
                        {
    //                    SET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG, 0);
                        SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,1);
                        }
                        else
                        {
        //                    SET_PROJECT_FLAG2(SPEED_MOTOR_VALUE_CHANGED_FOR_DISPLAY_FLAG,0);
                            SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,1);
                        }
                    }


                }
            }
        }
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ LCD odd tick @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
        if  ( (((sys_tick+1) % TICK_COUNTER_LCD ) == 0 ) )//|| (sys_tick ==0) ) // 10ms * 2tick//odd
        {
            if(GET_PROJECT_FLAG1(SW_200MS_FLAG) == 1)
            {
                if ((((GET_PROJECT_FLAG1(DISPLAY_SWING_VALUE_PRINTED_FLAG) == 1) || (GET_PROJECT_FLAG1(SLIDER_VALUE_CHANGED_FOR_DISPLAY_FLAG) == 1)) && GET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2) == 1) )
                {
                    //
                    Display_Disable_SSD();

                   // Display_Update_LCD("Swing Value", 0,2);
                   if ((GET_PROJECT_FLAG2(DISPLAY_SWING_VALUE_FULLY_PRINTED) == 0) )
                   {
                       Display_LCD_Print_Character("  Swing Value",0,0);
                   }
                    Display_Enable_SSD();
                    //
                    if (str_index == 0)
                    {
                        SET_PROJECT_FLAG2(DISPLAY_SWING_VALUE_FULLY_PRINTED, 1);
                        SET_PROJECT_FLAG2(DISPLAY_MOTOR_SPEED_FULLY_PRINTED, 0);
                        if((GET_PROJECT_FLAG1(DISPLAY_SWING_VALUE_PRINTED_FLAG) == 1))
                        {
                            SET_PROJECT_FLAG1(DISPLAY_SWING_VALUE_PRINTED_FLAG, 0);
                        }
                        else
                        {
                            SET_PROJECT_FLAG1(SLIDER_VALUE_CHANGED_FOR_DISPLAY_FLAG, 0);
                        }
                        SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,0);
                    }
                }
            }
            //----------------------------------------------------------------LCD odd tick--------------------------------------------------------------//
            else
            {
                if( ((GET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG) == 1) || (GET_PROJECT_FLAG2(SPEED_MOTOR_VALUE_CHANGED_FOR_DISPLAY_FLAG) == 1))  && GET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2) == 1)
                {
                    //
                    Display_Disable_SSD();

    //                Display_Update_LCD("Motor Speed", 0,2);

                    if (GET_PROJECT_FLAG2(DISPLAY_MOTOR_SPEED_FULLY_PRINTED) == 0)
                    {
                        Display_LCD_Print_Character("  Motor Speed",0, 0);
                    }
                    //
                    Display_Enable_SSD();
                    //
                    if (str_index == 0)
                    {
                        SET_PROJECT_FLAG2(DISPLAY_MOTOR_SPEED_FULLY_PRINTED, 1);
                        SET_PROJECT_FLAG2(DISPLAY_SWING_VALUE_FULLY_PRINTED, 0);
                            if((GET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG) == 1))
                            {
                            SET_PROJECT_FLAG2(DISPLAY_SPEED_VALUE_PRINTED_FLAG, 0);
                            }
                            else
                            {
                                SET_PROJECT_FLAG2(SPEED_MOTOR_VALUE_CHANGED_FOR_DISPLAY_FLAG,0);
                            }
                            SET_PROJECT_FLAG2(DISPLAY_LCD_PRINT_LINE1_THEN_LINE2,0);
    //                    }
                    }
                }
            }
        }
    }
//    stop timer1 sandwich
    while(!TMR1IF);
    Timer1_Stop_Timeout();

//    TIMER0_INTERRUPT_ENABLE();
//    #if _CALC_EXEC_TIME ==1
//    Timer1_Stop();
//    Display_WCET_H = Timer1_Calculate_Execution_Time_TMR1H(Display_WCET_H);
//    Display_WCET_L = Timer1_Calculate_Execution_Time_TMR1L(Display_WCET_L);
//    #endif // CALC_EXEC_TIME
}
