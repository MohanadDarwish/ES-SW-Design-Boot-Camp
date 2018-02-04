#ifndef _SPEED_MOTOR_H_
#define _SPEED_MOTOR_H_

#include "Port.h"
#include "SW.h"

extern U8 Speed_Motor_WCET_H;
extern U8 Speed_Motor_WCET_L;
extern U8 firing_angle;
typedef enum{
    Speed_Motor_Max_Speed = 10,
    Speed_Motor_Mid_Speed = 90,
    Speed_Motor_Min_Speed = 140,
    Speed_Motor_Initial_Speed = 170,
    Speed_Motor_Stop_Speed = 180
}tSpeed_Motor_Speeds;

void Speed_Motor_Init(void);
void Speed_Motor_Start(void);
void Speed_Motor_Stop(void);
void Speed_Motor_Set_Speed(tSpeed_Motor_Speeds);

void Speed_Motor_TRIAC_Output_Pulse(void);

void Speed_Motor_Task(void);

#endif // _SPEED_MOTOR_H_
