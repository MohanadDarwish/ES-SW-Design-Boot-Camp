#ifndef     _ADC_H_
#define     _ADC_H_

#include "Port.h"

/* ---------------------------ADC----------------------------*/
#define ADC_START_CONVERSION    (GO = 1)
#define ADC_WAIT_FOR_RESULT     while(GO == 1)
/* ADC CONFIG_Registers */

#define ADC_ADCON0_REG              (ADCON0)
#define ADC_ADCON1_REG              (ADCON1)

#define ADC_ADRESL_REG              (ADRESL)
#define ADC_ADRESH_REG              (ADRESH)

/* ADC Micro like functions*/

/* Set Justification */
#define ADC_ADJUST_RESULT(adjustment)   (ADFM = adjustment)

/* Set A/D Port Configuration */
#define ADC_PORT_CONFIG(Config)         (PCFG3 = ((Config) & 0x8 ) >> 3);\
                                        (PCFG2 = ((Config) & 0x4 ) >> 2);\
                                        (PCFG1 = ((Config) & 0x2 ) >> 1);\
                                        (PCFG0 = (Config) & 0x1)

/* Set Frequency */
#define ADC_SELECT_CLOCK(clock) (ADCS2 = ((clock) & 0x4 ) >> 2);\
                                (ADCS1 = ((clock) & 0x2 ) >> 1);\
                                (ADCS0 = (clock) & 0x1)

/* Select Channel */
#define ADC_SELECT_CHANNEL(channel)     (CHS2 = ((channel & 0x4) >> 2));\
                                        (CHS1 = ((channel & 0x2) >> 1));\
                                        (CHS0 = (channel & 0x1))
/* Set Power to A/D */
#define ADC_POWER(state)         ((ADON) = (state))

/* Set Go-Done */
#define ADC_SET_GO_DONE()           ((GO) = (1))
#define ADC_CLEAR_GO_DONE()         ((GO) = (0))
#define ADC_GET_GO_DONE()           ((ADC_ADCON0_REG & 0x04) >> (GO))

/* Adjust Data */
#define ADC_READ_RESULT(adjustment) (adjustment)?(((U16)((U16)ADRESH)<<8)|(ADRESL)):((((U16)ADRESH)<<2)|(ADRESL>>6))


/* ADC Interrupt Configure*/
#define ADC_INTERRUPT_ENABLE()   ((ADIE)= (1));\
                                  ((PEIE)=(1))
#define ADC_INTERRUPT_DISABLE() ((ADIE)= (0));\
                                  ((PEIE)=(0))

/*  ADC Macros */

#define ADC_FOSC_DIV_2           (0X00)
#define ADC_FOSC_DIV_8           (0X01)
#define ADC_FOSC_DIV_32          (0X02)
#define ADC_Extern_OSC           (0X03)
#define ADC_FOSC_DIV_4           (0X04)
#define ADC_FOSC_DIV_16          (0X05)
#define ADC_FOSC_DIV_64          (0X06)

#define ADC_SELECT_CH0_AN0          (0)
#define ADC_SELECT_CH1_AN1          (1)
#define ADC_SELECT_CH2_AN2          (2)
#define ADC_SELECT_CH3_AN3          (3)
#define ADC_SELECT_CH4_AN4          (4)
#define ADC_SELECT_CH5_AN5          (5)
#define ADC_SELECT_CH6_AN6          (6)
#define ADC_SELECT_CH7_AN7          (7)

#define ADC_RIGHT_JUSTIFIED      (0x01)
#define ADC_LEFT_JUSTIFIED       (0x00)

#define ADC_CONFIG_ALL_ANALOG          (0X00)
#define ADC_CONFIG_ALL_DIGITAL         (0X06)
#define ADC_CONFIG_3DIGITAL_5ANALOG    (0X02)
#define ADC_CONFIG_4DIGITAL_1ANALOG_1DIGITAL_2ANALOG    (0X04)

#define ADC_POWER_ON         (0x01)
#define ADC_POWER_OFF        (0x00)

//#define ADC_CLEAR_FLAG      (0x00)

void ADC_Init(void);

void ADC_Update(void);
U16 ADC_Read(void);
//U16 ADC_Convert(U8 , U8);

#endif // _ADC_H_
