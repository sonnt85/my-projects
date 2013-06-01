#include  <allfuntion.h>
#include <i2c.h>
#include <24c3264.h>

#define bypa  32
void eeprom_init()
{
 i2c_init();
}
void ack_polling()
{
do{i2c_start();}while(!i2c_write(EEPROM_BUS_ADDRESS | 1)); 
i2c_read(0);
i2c_stop();  
}
unsigned char eeprom_read(unsigned int address) {
unsigned char dlieu;
//address=((address/32)<<5)&(address%32);
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS);
i2c_write((unsigned int)address>>8);
i2c_write((unsigned char)address);
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 1);
dlieu=i2c_read(0);
i2c_stop();
return dlieu;
}
/* write a byte to the EEPROM */

void eeprom_reads(unsigned int address,unsigned int length,unsigned char idata *ptr) {
unsigned char i;
//address=((address/32)<<5)&(address%32);
readagain:
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS);
i2c_write(address>>8);
i2c_write(address);  //dumpy write
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS | 1);
for(i=0;i<length-1;i++)
  {
    if(!((address+1)%bypa))
    {
      *ptr=i2c_read(0);
      i2c_stop();
      ptr++;
      address++;
      length=length-i-1;
      goto readagain;
    }
    *ptr=i2c_read(1);
    address++;   
    ptr++;
  }
*ptr=i2c_read(0);
i2c_stop();
}
void eeprom_write(unsigned int address, uchar dlieu) {
//address=((address/32)<<5)&(address%32);
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS);
i2c_write((unsigned int)address>>8);
i2c_write((unsigned char)address);
i2c_write(dlieu);
i2c_stop();
/* 10ms delay to complete the write operation */
ack_polling();
}
void eeprom_writes(unsigned int address,unsigned int length,unsigned char idata *ptr) 
{
unsigned char i;
writeagain:
i2c_start();
i2c_write(EEPROM_BUS_ADDRESS);
i2c_write(address>>8);
i2c_write(address);
for(i=0;i<length;i++)
{
 //  if( address==500){lcd_putsfxy("sieuthanh",0,0);while(1);}
  if(!((address+1)%bypa))
  {
    i2c_write(*ptr);
    i2c_stop();
    ptr++;
    address++;
    length=length-i-1;
    ack_polling();
    goto writeagain;
  }          
   i2c_write(*ptr);
   ptr++;
   address++;
  
}
i2c_stop(); 
ack_polling();
}