#ifndef  _SW_H_
#define  _SW_H_

#include "Port.h"
#include "sEOS.h"
//for debugging purposes
#include "LCD.h"

#define SW_BOUNCING_TIME_MS       (20)
#define SW_SAMPLE_TIME_MS         (30)

#if SW_SAMPLE_TIME_MS < SW_BOUNCING_TIME_MS
#warning "Sampling time must be Greater than Bouncing time"
#endif

extern U8 SW_WCET_H;
extern U8 SW_WCET_L;

typedef enum
{
    SW_Released,    //0
    SW_Pre_Pressed, //1
    SW_Pressed,     //2
    SW_Pre_Released //3
}tSW_State;

typedef enum
{
    SW_Plus,    //0
    SW_Minus,   //1
    SW_Timer,   //2
    SW_Display  //3
}tSW_Name;

typedef enum{
    SW_None_Detected,           //0
    SW_Plus_Detected ,          //1
    SW_Minus_Detected ,         //2
    SW_Timer_Detected ,         //3
    SW_Display_Detected,        //4
    SW_Display_200ms_detected   //5
}SW_States;

extern SW_States SW_State_Info;

void SW_Init (tSW_Name);
tSW_State SW_Get_State (tSW_Name name);
void SW_Set_State (tSW_Name name ,tSW_State state);
//void SW_Update(tSW_Name name);
void SW_Update_Plus(void);
void SW_Update_Minus(void);
void SW_Update_Timer(void);
void SW_Update_Display(void);
void SW_Task(void);

#endif // _SW_H_
