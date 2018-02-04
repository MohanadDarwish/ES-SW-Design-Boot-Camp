#ifndef _SLIDER_H_
#define _SLIDER_H_

#include "Port.h"
#include "ADC.h"
#include "sEOS.h"
//this typedef to be deleted when implementing the PROJECT_FLAGS
typedef enum{
    SLIDER_Not_Detected, //0
    SLIDER_Detected      //1
}SLIDER_States;

#define SLIDER_DETECTED 1
#define SLIDER_NOT_DETECTED 0

extern U8 Slider_WCET_H;
extern U8 Slider_WCET_L;
//extern SLIDER_States SLIDER_State_Info;
extern U16 SLIDER_Reading;

void Slider_Init(void);
void Slider_Get_Value(void);
void Slider_Task(void);

#endif // _SLIDER_H_
