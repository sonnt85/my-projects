#ifndef __eeprom24c___
#define __eeprom24c___
#define at24c01  8
#define at24c02  8
#define at24c04  16
#define at24c08  16
#define at24c16  16
#define at24c32  32
#define at24c64  32
#define at24c128 64
#define at24c256 64
#define at24c512  128
#define at24c1024 256
//enum	    {at24c01=8`at24c02=8,at24c04=16,at24c08=16,at24c16=16,\
//			 at24c32=32,at24c64=32,at24c128=64,at24c256=64,at24c512=128};
#define		typeeeprom	 at24c64
#define     EEPROM_BUS_ADDRESS  0xA0
void          eeprom_init();
extern char	WrOk;
unsigned char eeprom_read(unsigned int address);
void          eeprom_write(unsigned int address, unsigned char dlieu);

char         eeprom_reads(unsigned int address,unsigned char length,void *ptr);
char 		 eeprom_writes(unsigned int address,unsigned char length,void *ptr);

#endif