#include <REGX52.H>
#include  <allfuntion.h>
#include  <i2c.h>

#define  doicho()      //tdelay        
              ////
#define  setsclout()
#define  sclout(a)     SCL=a;

#define  setsclint()   SCL=1;
#define  sclint()      SCL  
            /////
#define  setsdaout()
#define  sdaout(a)     SDA=a;

#define  setsdaint()   SDA=1;
#define  sdaint()      SDA

#define   setupi2c()  SCL=1;SDA=1;
void tdelay()
{
}
void i2c_init(void) ;
unsigned char i2c_start(void)  ;
void i2c_stop(void)      ;
unsigned char i2c_read(unsigned char ack)  ;
unsigned char i2c_write(unsigned char dlieu) ;


unsigned char i2c_start(void)  
{ 
  setsdaout();
  setsclout();
//  if(!sclint() )return 0;

  sclout(0);
  tdelay();
  sdaout(1);
  sclout(1);
  tdelay(); 
  sdaout(0);
  sclout(0);
  tdelay();
  setsdaint();
  return 1;
}
void i2c_init(void)
{
// uchar i;
  setupi2c();
/*  for (i=0;i<9;i++)
  {
  sclout(1);
  tdelay() ;
  sclout(0);
  tdelay();    
  }
 // i2c_start();  */

}
void i2c_stop(void)   
{
  setsdaout();
  setsclout();

  sclout(0);
  tdelay();
  sdaout(0);
  sclout(1);
  tdelay();
  sdaout(1);                  
  setsdaint();
  setsclint();
}
unsigned char i2c_read(char ack)
{
char x, d=0;
  setsdaint(); 
  setsclout();
  for(x=0; x<8; x++) {
    d <<= 1;
 /*   do {
      sclout(1);
    }
    while(sclint()==0);    // wait for any SCL clock stretching    */
    sclout(1);    
    tdelay();                                                 
    if(sdaint()) d |= 1;
    sclout(0)
  } 
  setsdaout(); 
  if(ack) {sdaout(0);}
  else {sdaout(1); }
  sclout(1);
  tdelay();
  sclout(0);
  tdelay();
  setsdaint();
  return d;
}
unsigned char i2c_write(unsigned char d)
{
char x;
static bit b;
setsdaout();
setsclout();
  for(x=0;x<8; x++) {
    if(d&0x80) {sdaout(1); }
    else sdaout(0);
    sclout(1);
    tdelay();
    d <<= 1;
    sclout(0);
    tdelay();
  }
  setsdaint();

  sclout(1);
  tdelay();
  b = sdaint();          // possible ACK bit
  sclout(0);
  return !b;
}

