#include "SSD.h"

/*Private constants*/
#define SSD_NULL 0b00000000
static tSSD ssd_current;
static tSSD_Symbol ssd_current_symbol;

static U8 SSD_DATA [SYMBOLS_MAX_NUMBER] =
{
    0b00111111,//0
    0b00000110,//1
    0b01011011,//2
    0b01001111,//3
    0b01100110,//4
    0b01101101,//5
    0b01111101,//6
    0b00000111,//7
    0b01111111,//8
    0b01101111,//9
    0b10000000,//dot
    0b01110110,//H
    0b00110000,//I
    0b00000000//Null
};
//
void SSD_Init(tSSD ssd)
{
    ssd_current_symbol = 0;
    ssd_current = 0;
    GPIO_InitPort( SSD_DATA_PORT_CR , GPIO_OUT );
    GPIO_WritePort( SSD_DATA_PORT_DR , SSD_NULL );
    switch(ssd)
    {
        case SSD_Hrs_Tens:
            GPIO_InitPortPin( SSD_HOURS_TENS_COMMON_CR , SSD_HOURS_TENS_COMMON_PIN , GPIO_OUT);
            break;
        case SSD_Hrs_Units:
            GPIO_InitPortPin( SSD_HOURS_UNITS_COMMON_CR , SSD_HOURS_UNITS_COMMON_PIN , GPIO_OUT);
            break;
        case SSD_Min_Tens:
            GPIO_InitPortPin( SSD_MINUTES_TENS_COMMON_CR , SSD_MINUTES_TENS_COMMON_PIN , GPIO_OUT);
            break;
        case SSD_Min_Units:
            GPIO_InitPortPin( SSD_MINUTES_UNITS_COMMON_CR , SSD_MINUTES_UNITS_COMMON_PIN , GPIO_OUT);
            break;
        case SSD_ALL:
            GPIO_InitPortPin( SSD_HOURS_TENS_COMMON_CR , SSD_HOURS_TENS_COMMON_PIN , GPIO_OUT);
            GPIO_InitPortPin( SSD_HOURS_UNITS_COMMON_CR , SSD_HOURS_UNITS_COMMON_PIN , GPIO_OUT);
            GPIO_InitPortPin( SSD_MINUTES_TENS_COMMON_CR , SSD_MINUTES_TENS_COMMON_PIN , GPIO_OUT);
            GPIO_InitPortPin( SSD_MINUTES_UNITS_COMMON_CR , SSD_MINUTES_UNITS_COMMON_PIN , GPIO_OUT);
            break;
    }
}
//
void SSD_Write_Symbol(tSSD ssd , tSSD_Symbol symbol)
{
    ssd_current = ssd;
    ssd_current_symbol = symbol;
    if (GET_PROJECT_FLAG1(DOT_TOGGLE_FLAG) == 0)
    {
        switch(ssd)
        {
            case SSD_Hrs_Tens:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[symbol]);
                break;
            case SSD_Hrs_Units:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[symbol]);
                break;
            case SSD_Min_Tens:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[symbol]);
                break;
            case SSD_Min_Units:
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[symbol]);
                break;
        }
    }
    else if(GET_PROJECT_FLAG1(DOT_TOGGLE_FLAG) == 1)
    {
         switch(ssd)
        {
            case SSD_Hrs_Tens:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[symbol]);
                break;
            case SSD_Hrs_Units:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,(SSD_DATA[symbol] | SSD_DATA[SSD_Symbol_dot]));
                break;
            case SSD_Min_Tens:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[symbol]);
                break;
            case SSD_Min_Units:
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_OFF);
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[symbol]);
                break;
        }
    }
}
//
void SSD_Disable(void)
{
        GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_OFF);
        GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_OFF);
        GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_OFF);
        GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_OFF);
        GPIO_WritePortPin(SSD_DATA_PORT_CR,SSD_DOT_PIN,SSD_OFF);
}
//
void SSD_Enable(void)
{
    if (GET_PROJECT_FLAG1(DOT_TOGGLE_FLAG) == 0)
    {
        switch(ssd_current)
        {
            case SSD_Hrs_Tens:
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[ssd_current_symbol]);
                break;
            case SSD_Hrs_Units:
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[ssd_current_symbol]);
                break;
            case SSD_Min_Tens:
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[ssd_current_symbol]);
                break;
            case SSD_Min_Units:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[ssd_current_symbol]);
                break;
        }
    }
    else if (GET_PROJECT_FLAG1(DOT_TOGGLE_FLAG) == 1)
    {
        switch(ssd_current)
        {
            case SSD_Hrs_Tens:
                GPIO_WritePortPin(SSD_HOURS_TENS_COMMON_DR,SSD_HOURS_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[ssd_current_symbol]);
                break;
            case SSD_Hrs_Units:
                GPIO_WritePortPin(SSD_HOURS_UNITS_COMMON_DR,SSD_HOURS_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,(SSD_DATA[ssd_current_symbol] | SSD_DATA[SSD_Symbol_dot]));
                break;
            case SSD_Min_Tens:
                GPIO_WritePortPin(SSD_MINUTES_TENS_COMMON_DR,SSD_MINUTES_TENS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[ssd_current_symbol]);
                break;
            case SSD_Min_Units:
                GPIO_WritePortPin(SSD_MINUTES_UNITS_COMMON_DR,SSD_MINUTES_UNITS_COMMON_PIN,SSD_ON);
                GPIO_WritePort(SSD_DATA_PORT_DR,SSD_DATA[ssd_current_symbol] );
                break;
        }
    }
}
