#define   e24c3264__c
#include <24c3264.h>
#define bypa  32
void eeprom_init(){
	unsigned char i;
	i2c_init();
	for (i=0;i<9;i++){
		ival2=10;
		sclout(1);
		sclout(0);
	}
	i2c_start();  
}
void ack_polling(){
	loighi|=bocheckloighi_;
	do{i2c_start();}while(!i2c_write(EEPROM_BUS_ADDRESS | 1)); 
	loighi&=(~bocheckloighi_);
	i2c_read(0);
	i2c_stop();  
}
char eeprom_read(unsigned int address) {
	char dlieu;
	//address=((address/32)<<5)&(address%32);
	ack_polling();
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
void eeprom_reads(unsigned int address,unsigned int length,void  *dest) {
	unsigned char i,*ptr;
	ptr=(unsigned char*)dest;
	//address=((address/32)<<5)&(address%32);
	readagain:
	ack_polling();
	i2c_start();
	i2c_write(EEPROM_BUS_ADDRESS);
	i2c_write(address>>8);
	i2c_write(address);  //dumpy write
	i2c_start();
	i2c_write(EEPROM_BUS_ADDRESS | 1);
	for(i=0;i<length-1;i++){
		if(!((address+1)%bypa)){
		*ptr=i2c_read(0);
		i2c_stop();
		ptr++;
		address++;
		length=length-i-1;
		//     ack_polling();
		goto readagain;
		}
		*ptr=i2c_read(1);
		address++;   
		ptr++;
	}
	*ptr=i2c_read(0);
	i2c_stop();
}

void eeprom_write(unsigned int address, char dlieu){
//address=((address/32)<<5)&(address%32);
	ack_polling();
	i2c_start();
	i2c_write(EEPROM_BUS_ADDRESS);
	i2c_write((unsigned int)address>>8);
	i2c_write((unsigned char)address);
	i2c_write(dlieu);
	i2c_stop();
	/* 10ms delay to complete the write operation */
}

void eeprom_writes(unsigned int address,unsigned int length,void  *soure) {
	unsigned char i,*ptr;
	ptr=(unsigned char*)soure;
	writeagain:
	ack_polling();
	i2c_start();
	i2c_write(EEPROM_BUS_ADDRESS);
	i2c_write(address>>8);
	i2c_write(address);
	for(i=0;i<length;i++){
		if(!((address+1)%bypa)){
			i2c_write(*ptr);
			i2c_stop();
			ptr++;
			address++;
			length=length-i-1;
			//    ack_polling();
			goto writeagain;
		}          
		i2c_write(*ptr);
		ptr++;
		address++;
	}
	i2c_stop(); 
//ack_polling();
}