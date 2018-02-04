#ifndef _PORT_H_
#define _PORT_H_

#include "Main.h"

/* LEDs Pins */

#define LED_1_PORT_DR                       (GPIO_PORTB_DATA)
#define LED_1_PORT_CR                       (GPIO_PORTB_DIRECTION)
#define LED_1_PIN                           (GPIO_PIN_0)

#define LED_2_PORT_DR                       (GPIO_PORTB_DATA)
#define LED_2_PORT_CR                       (GPIO_PORTB_DIRECTION)
#define LED_2_PIN                           (GPIO_PIN_1)

#define LED_3_PORT_DR                       (GPIO_PORTB_DATA)
#define LED_3_PORT_CR                       (GPIO_PORTB_DIRECTION)
#define LED_3_PIN                           (GPIO_PIN_2)

#define LED_4_PORT_DR                       (GPIO_PORTB_DATA)
#define LED_4_PORT_CR                       (GPIO_PORTB_DIRECTION)
#define LED_4_PIN                           (GPIO_PIN_3)

/* Switches Pins */

#define SW_PORT_DR                          (GPIO_PORTB_DATA)
#define SW_PORT_CR                          (GPIO_PORTB_DIRECTION)
//#define SW_TIMER_PIN                        (GPIO_PIN_0)

//#define SW_SET_PORT_DR                      (GPIO_PORTB_DATA)
//#define SW_SET_PORT_CR                      (GPIO_PORTB_DIRECTION)
//#define SW_SET_PIN                          (GPIO_PIN_1)
//
//#define SW_PLUS_PORT_DR                     (GPIO_PORTB_DATA)
//#define SW_PLUS_PORT_CR                     (GPIO_PORTB_DIRECTION)
//#define SW_PLUS_PIN                         (GPIO_PIN_2)
//
//#define SW_MINUS_PORT_DR                    (GPIO_PORTB_DATA)
//#define SW_MINUS_PORT_CR                    (GPIO_PORTB_DIRECTION)
//#define SW_MINUS_PIN                        (GPIO_PIN_3)

/* SSD Pins */

#define SSD_DATA_PORT_DR                    (GPIO_PORTD_DATA)
#define SSD_DATA_PORT_CR                    (GPIO_PORTD_DIRECTION)
#define SSD_DOT_PIN           (GPIO_PIN_7)

#define SSD_HOURS_TENS_COMMON_DR            (GPIO_PORTB_DATA)
#define SSD_HOURS_TENS_COMMON_CR            (GPIO_PORTB_DIRECTION)
#define SSD_HOURS_TENS_COMMON_PIN           (GPIO_PIN_7)
#define SSD_HOURS_TENS_DOT_PIN              (GPIO_PIN_7)

#define SSD_HOURS_UNITS_COMMON_DR           (GPIO_PORTB_DATA)
#define SSD_HOURS_UNITS_COMMON_CR           (GPIO_PORTB_DIRECTION)
#define SSD_HOURS_UNITS_COMMON_PIN          (GPIO_PIN_6)
#define SSD_HOURS_UNITS_DOT_PIN             (GPIO_PIN_7)

#define SSD_MINUTES_TENS_COMMON_DR          (GPIO_PORTB_DATA)
#define SSD_MINUTES_TENS_COMMON_CR          (GPIO_PORTB_DIRECTION)
#define SSD_MINUTES_TENS_COMMON_PIN         (GPIO_PIN_5)
#define SSD_MINUTES_TENS_DOT_PIN            (GPIO_PIN_7)

#define SSD_MINUTES_UNITS_COMMON_DR         (GPIO_PORTB_DATA)
#define SSD_MINUTES_UNITS_COMMON_CR         (GPIO_PORTB_DIRECTION)
#define SSD_MINUTES_UNITS_COMMON_PIN        (GPIO_PIN_4)
#define SSD_MINUTES_UNITS_DOT_PIN           (GPIO_PIN_7)


/* LCD Pins */

#define LCD_DATA_PORT_DR                    (GPIO_PORTD_DATA)
#define LCD_DATA_PORT_CR                    (GPIO_PORTD_DIRECTION)

#define LCD_RS_PORT_DR                      (GPIO_PORTE_DATA)
#define LCD_RS_PORT_CR                      (GPIO_PORTE_DIRECTION)
#define LCD_RS_PIN                          (GPIO_PIN_0)

#define LCD_E_PORT_DR                       (GPIO_PORTE_DATA)
#define LCD_E_PORT_CR                       (GPIO_PORTE_DIRECTION)
#define LCD_E_PIN                           (GPIO_PIN_1)

/* ADC Pins (Always Inputs) */

//#define ADC_CH1_PORT_DR                     (GPIO_PORTA_DATA)
//#define ADC_CH1_PORT_CR                     (GPIO_PORTA_DIRECTION)
//#define ADC_CH1_PIN                         (GPIO_PIN_1)

/* Swing Motor Pins */
#define SWING_MOTOR_PORT_DR                 (GPIO_PORTC_DATA)
#define SWING_MOTOR_PORT_CR                 (GPIO_PORTC_DIRECTION)
#define SWING_MOTOR_CONTROL_SIGNAL_BIT_0    (GPIO_PIN_0)
#define SWING_MOTOR_CONTROL_SIGNAL_BIT_1    (GPIO_PIN_1)
#define SWING_MOTOR_CONTROL_SIGNAL_BIT_2    (GPIO_PIN_2)
#define SWING_MOTOR_CONTROL_SIGNAL_BIT_3    (GPIO_PIN_3)

/* Speed Motor Pins*/
#define SPEED_MOTOR_TRIAC_DR                (GPIO_PORTC_DATA)
#define SPEED_MOTOR_TRIAC_CR                (GPIO_PORTA_DIRECTION)
#define SPEED_MOTOR_TRIAC_PIN               (GPIO_PIN_4)

/* Buzzer Pins */
#define BUZZER_PORT_DR                      (GPIO_PORTA_DATA)
#define BUZZER_PORT_CR                      (GPIO_PORTA_DIRECTION)
#define BUZZER_PIN                          (GPIO_PIN_5)

/* Slider Pins */
#define SLIDER_PORT_DR                      (GPIO_PORTA_DATA)
#define SLIDER_PORT_CR                      (GPIO_PORTA_DIRECTION)
#define SLIDER_PIN                          (GPIO_PIN_1)


#endif // _PORT_H_
