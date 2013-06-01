#include <i2c.h>
#include <eeprom24c.h>
#define bypa  typeeeprom
#if ((typeeeprom==at24c01)|(typeeeprom==at24c02)|(typeeeprom==at24c04)|(typeeeprom==at24c08)|(typeeeprom==at24c16))
	void write_idadeep(unsigned int address){
		if(address<=0xFF)i2c_write(EEPROM_BUS_ADDRESS);
		else i2c_write(EEPROM_BUS_ADDRESS|(address>>8));//dumpy write
		i2c_write(address);	
	}
//	#error "dhua Khai Bao Dung Loai Chip  typeeeprom"
#elif ((typeeeprom==at24c32)|(typeeeprom==at24c64)|(typeeeprom==at24c128)|(typeeeprom==at24c256)|(typeeeprom==at24c512))
	void write_idadeep(unsigned int address){
		i2c_write(EEPROM_BUS_ADDRESS);
		i2c_write(address>>8);	 
		i2c_write(address);  //dumpy write
	}
#else
	#error "Chua Khai Bao Dung Loai Chip  typeeeprom"
#endif 	

void eeprom_init(){
char	i;
 i2c_init();
 for (i=0;i<9;i++){
  sclout(1);
  sclout(0);
 }
 i2c_start(); 
}
char ack_polling(){
	unsigned int to=6000;
	do{i2c_start();to--;}while((!i2c_write(EEPROM_BUS_ADDRESS | 1))|(!to)); 
	i2c_read(0);
	i2c_stop();
	return WrOk;
}
/*
unsigned char eeprom_read(unsigned int address) {
	unsigned char dlieu;
	i2c_start();
	write_idadeep(address);
	i2c_start();
	i2c_write(EEPROM_BUS_ADDRESS | 1);
	dlieu=i2c_read(0);
	i2c_stop();
	return dlieu;
}
*/
/* write a byte to the EEPROM */
	 
char eeprom_reads(unsigned int address,unsigned char length,void *ptr) {
	unsigned char i;
//	,*ptr;
//	ptr=(unsigned char*)dest;
	//address=((address/32)<<5)&(address%32);		
	readagain:
	ack_polling();
	i2c_start();
	write_idadeep(address);
	i2c_start();
	i2c_write(EEPROM_BUS_ADDRESS | 1);
	for(i=0;i<length-1;i++){
	    if(!((address+1)%bypa))
	    {
	      *((unsigned char *)ptr)=i2c_read(0);
	      i2c_stop();
	      ((unsigned char *)ptr)++;
	      address++;
	      length=length-i-1;
	      goto readagain;
	    }
	    *((unsigned char *)ptr)=i2c_read(1);
	    address++;   
	    ((unsigned char *)ptr)++;
	}
	*((unsigned char *)ptr)=i2c_read(0);
	i2c_stop();
	return WrOk;
}
/*
void eeprom_write(unsigned int address, unsigned char dlieu) {
	//address=((address/32)<<5)&(address%32);
	ack_polling();
	i2c_start();
	write_idadeep(address);
	i2c_write(dlieu);
	i2c_stop();
}
*/

char eeprom_writes(unsigned int address,unsigned char length,void *ptr) {
	unsigned char i;
	//,*ptr;
//	ptr=(unsigned char*)dest;
	ack_polling();
	writeagain:
	i2c_start();
	write_idadeep(address);
	for(i=0;i<length;i++){
	  if(!((address+1)%bypa)){
	    i2c_write(*((unsigned char*)ptr));
	    i2c_stop();
	    ((unsigned char*)ptr)++;
	    address++;
	    length=length-i-1;
	    ack_polling();
	    goto writeagain;
	  }          
	   i2c_write(*((unsigned char*)ptr));
	   ((unsigned char*)ptr)++;
	   address++;	  
	}
	i2c_stop(); 
	return WrOk;
}