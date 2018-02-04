#include "LCD.h"

/*private functions prototypes*/
static void LCD_Send_CMD(U8);
static void LCD_Send_Half_CMD(U8 cmd);
static void LCD_E_ON_OFF_ON_Pulse(void);
static tLCD_Mode lcd_mode=LCD_8bit_mode;
///////////
/*Constant Macros*/
#define ON 1
#define OFF 0

#define LCD_LINE_1_START_ADDRESS    0x00
#define LCD_LINE_2_START_ADDRESS    0x40
#define DDRAM_WIDTH                 0x28//40 decimal

#define I_D_INCREMENT               0b00000010
#define I_D_DECREMENT               0b00000000

#define R_L_SHIFT_RIGHT             0b00000100
#define R_L_SHIFT_LEFT              0b00000000

#define S_DISPLAY_SHIFT_ON          0b00000001
#define S_DISPLAY_SHIFT_OFF         0b00000000

#define DL_8_BIT_INTERFACE          0b00010000
#define DL_4_BIT_INTERFACE          0b00000000

#define D_DISPLAY_ON                0b00000100
#define D_DISPLAY_OFF               0b00000000

#define N_DISPLAY_IN_TWO_LINES      0b00001000
#define N_DISPLAY_IN_ONE_LINES      0b00000000

#define U_CURSOR_ON                 0b00000010
#define U_CURSOR_OFF                0b00000000

#define F_CHARACTER_FONT_5_10_DOTS  0b00000100
#define F_CHARACTER_FONT_5_7_DOTS   0b00000000

#define B_CURSOR_BLINK_ON           0b00000001
#define B_CURSOR_BLINK_OFF          0b00000000

#define D_C_DISPLAY_SHIFT           0b00001000
#define D_C_CURSOR_SHIFT            0b00000000

/*LCD commands*/
#define CLEAR_DISPLAY_CMD           0b00000001//no options
#define CURSOR_HOME_CMD             0b00000010//no options
#define ENTRY_MODE_CMD              0b00000100//I/D , S
#define DISPLAY_ON_OFF_CONTROL_CMD  0b00001000//D , U , B
#define CURSOR_DISPLAY_SHIFT_CMD    0b00010000//D/C , R/L
#define FUNCTION_SET_CMD            0b00100000//DL , N , F
#define SET_CGRAM_ADDRESS_CMD       0b01000000//CGRAM Address 6 bits
#define SET_DDRAM_ADDRESS_CMD       0b10000000//DDRAM Address 7 bits

void LCD_Init(tLCD_Mode mode)
{
    //////////////////////////////////////////
    //initialization starts here
    //////////////////////////////////////////
    lcd_mode=mode;
    GPIO_InitPortPin(LCD_E_PORT_CR,LCD_E_PIN,GPIO_OUT);
    GPIO_InitPortPin(LCD_RS_PORT_CR,LCD_RS_PIN,GPIO_OUT);
    GPIO_InitPort(LCD_DATA_PORT_CR,GPIO_OUT);

    GPIO_WritePortPin(LCD_RS_PORT_DR,LCD_RS_PIN,0);
    if(lcd_mode==LCD_8bit_mode)
    {
        Delay_MS(LCD_WARM_UP_DELAY);
        //
        LCD_Send_CMD( FUNCTION_SET_CMD|DL_8_BIT_INTERFACE|N_DISPLAY_IN_TWO_LINES|F_CHARACTER_FONT_5_10_DOTS);
        //
        Delay_MS(LCD_INIT_2ND_DELAY);
        //
        LCD_Send_CMD( FUNCTION_SET_CMD|DL_8_BIT_INTERFACE|N_DISPLAY_IN_TWO_LINES|F_CHARACTER_FONT_5_10_DOTS);
        //
        Delay_MS(LCD_INIT_3RD_DELAY);
        //
        LCD_Send_CMD( FUNCTION_SET_CMD|DL_8_BIT_INTERFACE );
    }
    else if (lcd_mode == LCD_4bit_mode)
    {
        Delay_MS(LCD_WARM_UP_DELAY);
        //
        LCD_Send_Half_CMD( FUNCTION_SET_CMD|DL_8_BIT_INTERFACE);
        //
        Delay_MS(LCD_INIT_2ND_DELAY);
        //
        LCD_Send_Half_CMD( FUNCTION_SET_CMD|DL_8_BIT_INTERFACE);
        //
        Delay_MS(LCD_INIT_3RD_DELAY);
        //
        LCD_Send_Half_CMD( FUNCTION_SET_CMD|DL_8_BIT_INTERFACE);
        //
        LCD_Send_Half_CMD( FUNCTION_SET_CMD|DL_4_BIT_INTERFACE);
        //
        LCD_Send_CMD( FUNCTION_SET_CMD|DL_4_BIT_INTERFACE|N_DISPLAY_IN_TWO_LINES|F_CHARACTER_FONT_5_10_DOTS);
    }
    //
    LCD_Send_CMD( DISPLAY_ON_OFF_CONTROL_CMD|D_DISPLAY_OFF|U_CURSOR_OFF|B_CURSOR_BLINK_OFF);
    //
    LCD_Send_CMD( CLEAR_DISPLAY_CMD );
    //
    LCD_Send_CMD( DISPLAY_ON_OFF_CONTROL_CMD|D_DISPLAY_ON|U_CURSOR_ON|B_CURSOR_BLINK_ON);
    //
    LCD_Send_CMD( ENTRY_MODE_CMD|I_D_INCREMENT|S_DISPLAY_SHIFT_OFF);
    //
    LCD_Send_CMD( CURSOR_DISPLAY_SHIFT_CMD|D_C_CURSOR_SHIFT|R_L_SHIFT_RIGHT );
    //
    LCD_Send_CMD(CURSOR_HOME_CMD);
    ///////////////////////////////
    LCD_Send_CMD( DISPLAY_ON_OFF_CONTROL_CMD|D_DISPLAY_ON|U_CURSOR_ON|B_CURSOR_BLINK_ON);

    //////////////////////////////////////////
    //initialization ends here
    //////////////////////////////////////////
}
static void LCD_Send_CMD(U8 cmd)
{
    GPIO_WritePortPin(LCD_RS_PORT_DR,LCD_RS_PIN,0);
    if(lcd_mode == LCD_4bit_mode)
    {
        //sending the cmd 4 bit by 4 bit first D7-->D4 then D3-->D0
        //cmd first half
        GPIO_WritePort(LCD_DATA_PORT_DR ,(LCD_DATA_PORT_DR&0x0f)|(cmd&0xf0) );//D7-->D4
        LCD_E_ON_OFF_ON_Pulse();
        //cmd second half
        GPIO_WritePort(LCD_DATA_PORT_DR ,(LCD_DATA_PORT_DR&0x0f)|((cmd<<4)&0xf0) );//D3-->D0
        LCD_E_ON_OFF_ON_Pulse();
    }
    else if(lcd_mode == LCD_8bit_mode)
    {
        GPIO_WritePort(LCD_DATA_PORT_DR,cmd);
        LCD_E_ON_OFF_ON_Pulse();
    }
    else
    {
        ;
    }
}

static void LCD_Send_Half_CMD(U8 cmd){
    GPIO_WritePortPin(LCD_RS_PORT_DR,LCD_RS_PIN,0);
    if(lcd_mode == LCD_4bit_mode)
    {
        //cmd first half
        GPIO_WritePort(LCD_DATA_PORT_DR ,(LCD_DATA_PORT_DR&0x0f)|(cmd&0xf0) );//D7-->D4
        LCD_E_ON_OFF_ON_Pulse();
    }
    else
    {
        LCD_GoTo(0,0);
        ;
    }
}

void LCD_Write_Character( U8 ch ){
    GPIO_WritePortPin(LCD_RS_PORT_DR,LCD_RS_PIN,1);
     if(lcd_mode == LCD_4bit_mode)
    {
        //sending the ch 4 bit by 4 bit first D7-->D4 then D3-->D0
        //ch first half
        GPIO_WritePort(LCD_DATA_PORT_DR,(LCD_DATA_PORT_DR&0x0f)|(ch&0xf0) );//D7-->D4
        LCD_E_ON_OFF_ON_Pulse();
        //ch second half
        GPIO_WritePort(LCD_DATA_PORT_DR,(LCD_DATA_PORT_DR&0x0f)|((ch<<4)&0xf0) );//D3-->D0
        LCD_E_ON_OFF_ON_Pulse();
    }
    else if(lcd_mode == LCD_8bit_mode)
    {
        GPIO_WritePort(LCD_DATA_PORT_DR,ch);
        LCD_E_ON_OFF_ON_Pulse();
    }
    else
    {
        LCD_GoTo(0,0);
    }

}

void LCD_Write_String( U8* str){

    while(*str != '\0')
    {
      LCD_Write_Character(*str++);
    }
}

void LCD_GoTo(U8 row, U8 column){
    //row 0->1 column 0-->15

    U8 address=0;
    if(column >16)
    {
        LCD_Send_CMD(CURSOR_HOME_CMD);
        ;
    }
    if(row ==0)
    {
        address= (LCD_LINE_1_START_ADDRESS+column)&0b01111111;
    }
    else if(row ==1)
    {
        address= (LCD_LINE_2_START_ADDRESS+column)&0b01111111;
    }
    else
    {
        LCD_Send_CMD(CURSOR_HOME_CMD);
        ;
    }
    LCD_Send_CMD(SET_DDRAM_ADDRESS_CMD|address);
}

void LCD_Clear_Screen(void){
    LCD_Send_CMD(CLEAR_DISPLAY_CMD);
}

static void LCD_E_ON_OFF_ON_Pulse(void){
    GPIO_WritePortPin(LCD_E_PORT_DR,LCD_E_PIN,1);
    GPIO_WritePortPin(LCD_E_PORT_DR,LCD_E_PIN,0);
    GPIO_WritePortPin(LCD_E_PORT_DR,LCD_E_PIN,1);
}
