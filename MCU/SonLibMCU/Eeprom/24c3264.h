#ifndef  __24c3264__
#define  __24c3264__
#define       EEPROM_BUS_ADDRESS  0xa0
void          eeprom_init();
void          delay_ms(unsigned int t);
unsigned char eeprom_read(unsigned int address);
void          eeprom_write(unsigned int address, unsigned char dlieu);
void          eeprom_reads(unsigned int address,unsigned int length,unsigned char idata *ptr);
void          eeprom_writes(unsigned int address,unsigned int length,unsigned char idata *ptr);
#endif