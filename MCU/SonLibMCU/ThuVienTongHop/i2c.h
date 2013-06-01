#ifndef __i2c__
#define __i2c__
//#define  SCL  P3_6
//#define  SDA  P3_7
#include<THANHSONCHIP.H>
sbit  SCL=P0^3;
sbit  SDA=P0^2;

void          i2c_stop(void);
unsigned char i2c_read(unsigned char ack)  ;
unsigned char i2c_write(unsigned char dlieu) ;
unsigned char i2c_start(void)  ;
void          i2c_init(void)     ;
#define setloighi(setloi)   loighi|=setloi;
#define clearloighi(setloi) loighi&=(~setloi);

enum          {bocheckloighi_=0x02};


#ifndef	 i2c__c

extern char data loighi;
extern unsigned long      coubywi,couerr;

#endif 
#define	 setupi2c()
#define	 setsclout()
#define  sclout(a)     SCL=a

#define  setsclint()   SCL=1
#define  sclint()      SCL  

#define  setsdaout()
#define  sdaout(a)     SDA=a

#define  setsdaint()   SDA=1
#define  sdaint()      SDA

#endif