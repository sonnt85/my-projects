#ifndef  __24c3264__
#define  __24c3264__

#ifndef 	  e24c3264__c
#else
	#include <i2c.h>
#endif

#define       EEPROM_BUS_ADDRESS  0xa0
#define       ews(x,y)    		eeprom_writes(x,sizeof(y),y)
#define       er(x)    	  		eeprom_read(x)
#define       ew(x,y)     		eeprom_write(x,y)
#define       ers(x,y)    		eeprom_reads(x,sizeof(y),y)

#define       ewsstr(x,y,z)    	eeprom_writes(x,y,z)
#define       ersstr(x,y,z)    	eeprom_reads(x,y,z)

void          eeprom_init();
char          eeprom_read(unsigned int address);
void          eeprom_write(unsigned int address,  char dlieu);
void          eeprom_reads(unsigned int address,unsigned int length,void  *dest);
void          eeprom_writes(unsigned int address,unsigned int length,void  *soure);


#endif