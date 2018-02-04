#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "Port.h"
#include "sEOS.h"


#define BUZZER_ON   1
#define BUZZER_OFF  0

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
//void Buzzer_Toggle(void);

#endif // _BUZZER_H_
