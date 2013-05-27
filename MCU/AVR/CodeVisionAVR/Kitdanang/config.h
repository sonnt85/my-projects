#ifndef __board__h
#define __board__h
#define CTRL_ADC_0   PORTD.0
#define CTRL_ADC_1   PORTD.1
#define CTRL_ADC_EN  PORTD.2

#define CTRL_UART_0  PORTB.5
#define CTRL_UART_1  PORTB.4
#define CTRL_UART_EN PORTB.3

#define CTRL_I2C_0   PORTB.6
#define CTRL_I2C_1   PORTB.7
#define CTRL_I2C_EN  PORTD.6

#define CTRL_PROG_1  PORTB.1
#define CTRL_PROG_0  PORTB.0
#define CTRL_PROG_EN PORTB.2

#define CTRL_VMCU    PORTC.3    
#define VRESET       PORTD.4 

#define LED_8051     PORTC.0 
#define LED_AVR      PORTC.1
#define LED_PIC      PORTC.2


#define BUT_RESET    PIND.3 
#define BUT_ATMEGA8  PINC.5 
 
 
#define SENSOR_DETECT_PIC         PINC.4 
#define SENSOR_DETECT_AVR         PIND.7
//#define SENSOR_DETECT_8051        PIND.5
#endif