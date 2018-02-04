#ifndef _SWING_MOTOR_H_
#define _SWING_MOTOR_H_

#include "Port.h"
#include "Slider.h"
#include "sEOS.h"

extern U8 Swing_Motor_WCET_H;
extern U8 Swing_Motor_WCET_L;
typedef enum{
    Swing_Motor_0_Degrees = 0,  //0
    Swing_Motor_45_Degrees ,    //1
    Swing_Motor_90_Degrees ,    //2
    Swing_Motor_135_Degrees,    //3
    Swing_Motor_180_Degrees,    //4
    Swing_Motor_225_Degrees,    //5
    Swing_Motor_270_Degrees,    //6
    Swing_Motor_315_Degrees,    //7
    Swing_Motor_360_Degrees     //0b00001xxx //8
}tSwing_Motor_Angle;

void Swing_Motor_Init(void);
void Swing_Motor_Start(void);
void Swing_Motor_Stop(void);
void Swing_Motor_Task(void);

#endif // _SWING_SWING_H_
