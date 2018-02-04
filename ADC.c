#include "ADC.h"
#include "LCD.h"

void ADC_Init(void)
{
//    GPIO_InitPort(ADC_CH1_PORT_CR, GPIO_IN);
//    GPIO_InitPortPin(ADC_CH1_PORT_CR, ADC_CH1_PIN, GPIO_IN);
    ADC_POWER(ADC_POWER_OFF);
    ADC_INTERRUPT_DISABLE();
    ADC_SELECT_CLOCK(ADC_FOSC_DIV_8);
    ADC_PORT_CONFIG(ADC_CONFIG_4DIGITAL_1ANALOG_1DIGITAL_2ANALOG);
    ADC_ADJUST_RESULT(ADC_RIGHT_JUSTIFIED);
    ADC_SELECT_CHANNEL(ADC_SELECT_CH1_AN1);
    ADC_CLEAR_GO_DONE();
}

void ADC_Update(void)
{
    //ADC_ON;
    ADC_PORT_CONFIG(ADC_CONFIG_4DIGITAL_1ANALOG_1DIGITAL_2ANALOG);
    ADC_POWER(ADC_POWER_ON);
    LCD_DEBUG(1,0,"ADON = 1");
    ADC_SET_GO_DONE();//SET =1, CLEAR = 0 ,RESET = reset value
    //
    while(ADC_GET_GO_DONE() == 1);
    LCD_DEBUG(1,0,"Conversion Ended");
}

U16 ADC_Read(void)
{
    //ADC_result -> range of possible values are  0--> 1023
    U16 ADC_result = 1024;
    LCD_DEBUG(1,0,"Enter Read");
    if (ADC_GET_GO_DONE() == 0)
    {
       ADC_result = ADC_READ_RESULT(ADC_RIGHT_JUSTIFIED);
       ADC_POWER(ADC_POWER_OFF);
    }
    //returning 1024 means that adc failed to read as thea range of possible values are  0--> 1023
    return ADC_result;
}

//U16 ADC_Convert(U8 channel, U8 adjustment)
//{
//    U16  ret = 0;
//    /* Add your code here ! */
//    /* Turn ADC ON, select result adjustment and channel then start conversion.
//       After conversion return result */
//    //ADC_ON;
//    ADON =1;
//    ADC_ADJUST_RESULT(adjustment);
//    //adjustment => 0,  when == left
//    ADC_SELECT_CHANNEL(channel);
//    ADC_START_CONVERSION;
//    ADC_WAIT_FOR_RESULT;
//    ret = ADC_READ_RESULT(adjustment);
//    //ADC_OFF;
//    ADON =0;
//    /* End of your code ! */
//    return ret;
//}
