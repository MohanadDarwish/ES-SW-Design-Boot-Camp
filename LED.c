//#include "LED.h"
//
//void LED_Init(tLED led){
//    switch(led)
//    {
//        case LED1:
//            GPIO_InitPortPin( LED_1_PORT_CR , LED_1_PIN , GPIO_OUT );
//            break;
//
//        case LED2:
//            GPIO_InitPortPin( LED_2_PORT_CR , LED_2_PIN , GPIO_OUT );
//            break;
//
//        case LED3:
//            GPIO_InitPortPin( LED_3_PORT_CR , LED_3_PIN , GPIO_OUT );
//            break;
//
//        case LED4:
//            GPIO_InitPortPin( LED_4_PORT_CR , LED_4_PIN , GPIO_OUT );
//            break;
//
//        case LED_ALL:
//            GPIO_InitPortPin( LED_1_PORT_CR , LED_1_PIN , GPIO_OUT );
//            GPIO_InitPortPin( LED_2_PORT_CR , LED_2_PIN , GPIO_OUT );
//            GPIO_InitPortPin( LED_3_PORT_CR , LED_3_PIN , GPIO_OUT );
//            GPIO_InitPortPin( LED_4_PORT_CR , LED_4_PIN , GPIO_OUT );
//            break;
//    }
//}
//
//void LED_On(tLED led){
//    switch(led){
//        case LED1:
//            GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_ON);
//            break;
//        case LED2:
//            GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_ON);
//            break;
//        case LED3:
//            GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_ON);
//            break;
//        case LED4:
//            GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_ON);
//            break;
//        case LED_ALL:
//            GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_ON);
//            GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_ON);
//            GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_ON);
//            GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_ON);
//            break;
//    }
//}
////
//void LED_Off(tLED led){
//
//    switch(led){
//        case LED1:
//            GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_OFF);
//            break;
//        case LED2:
//            GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_OFF);
//            break;
//        case LED3:
//            GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_OFF);
//            break;
//        case LED4:
//            GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_OFF);
//            break;
//        case LED_ALL:
//            GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_OFF);
//            GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_OFF);
//            GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_OFF);
//            GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_OFF);
//            break;
//    }
//}
////
//void LED_Toggle(tLED led){
//    switch(led){
//        case LED1:
//            if( GPIO_ReadPortPin(LED_1_PORT_DR,LED_1_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_ON);
//            break;
//        case LED2:
//            if( GPIO_ReadPortPin(LED_2_PORT_DR,LED_2_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_ON);
//            break;
//        case LED3:
//            if( GPIO_ReadPortPin(LED_3_PORT_DR,LED_3_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_ON);
//            break;
//        case LED4:
//            if( GPIO_ReadPortPin(LED_4_PORT_DR,LED_4_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_ON);
//            break;
//        case LED_ALL:
//            if( GPIO_ReadPortPin(LED_1_PORT_DR,LED_1_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_1_PORT_DR,LED_1_PIN,LED_ON);
//            ////
//            if( GPIO_ReadPortPin(LED_2_PORT_DR,LED_2_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_2_PORT_DR,LED_2_PIN,LED_ON);
//            ////
//            if( GPIO_ReadPortPin(LED_3_PORT_DR,LED_3_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_3_PORT_DR,LED_3_PIN,LED_ON);
//            ////
//            if( GPIO_ReadPortPin(LED_4_PORT_DR,LED_4_PIN) == LED_ON)
//                GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_OFF);
//            else
//                GPIO_WritePortPin(LED_4_PORT_DR,LED_4_PIN,LED_ON);
//            break;
//    }
//}
