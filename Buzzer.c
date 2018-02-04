#include "Buzzer.h"

void Buzzer_Init(void)
{
    GPIO_InitPortPin(BUZZER_PORT_CR,BUZZER_PIN,GPIO_OUT);

}
void Buzzer_On(void)
{
//    GPIO_WritePortPin(BUZZER_PORT_DR,BUZZER_PIN,BUZZER_ON);
        GPIO_WritePortPin(BUZZER_PORT_DR,BUZZER_PIN,BUZZER_OFF);

}
void Buzzer_Off(void)
{
    GPIO_WritePortPin(BUZZER_PORT_DR,BUZZER_PIN,BUZZER_OFF);
}
//void Buzzer_Toggle(void)
//{
//   if(GPIO_ReadPortPin(BUZZER_PORT_DR,BUZZER_PIN) == BUZZER_ON)
//   {
//        GPIO_WritePortPin(BUZZER_PORT_DR,BUZZER_PIN,BUZZER_OFF);
//   }
//   else
//   {
//        GPIO_WritePortPin(BUZZER_PORT_DR,BUZZER_PIN,BUZZER_ON);
//   }
//}

