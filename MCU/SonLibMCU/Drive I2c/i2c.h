#ifndef __i2c___
#define __i2c__
#define  SCL  P3_6
#define  SDA  P3_7
void          i2c_stop(void);
unsigned char i2c_read(unsigned char ack)  ;
unsigned char i2c_write(unsigned char dlieu) ;
unsigned char i2c_start(void)  ;
void          i2c_init(void)     ;
#endif