#define   i2c__c
unsigned	long	coubywi=0,couerr=0;
char data 	loighi;
#include	<i2c.h>
unsigned char i2c_start(void){ 
	setsdaout();
	setsclout();
	// if(!sclint() )return 0;
	sclout(0);
	
	sdaout(1);
	sclout(1);
	
	sdaout(0);
	sclout(0);
	
	setsdaint();
	return 1;
}
void i2c_init(void){//chu yeu khoi tao cac chan vao ra
  setupi2c();
}
void i2c_stop(void){
	setsdaout();
	setsclout();
	
	sclout(0);
	
	sdaout(0);
	sclout(1);
	
	sdaout(1);                  
	setsdaint();
	setsclint();
}
unsigned char i2c_read(char ack){
	char x, d=0;
	setsdaint(); 
	setsclout();
	for(x=0; x<8; x++){
		d <<= 1;
		/*   do {
		sclout(1);
		}
		while(sclint()==0);    // wait for any SCL clock stretching    */
		sclout(1);    
		                                     
		if(sdaint()) d |= 1;
		sclout(0);
	} 
	setsdaout(); 
	if(ack) {sdaout(0);}
	else {sdaout(1); }
	sclout(1);
	
	sclout(0);
	
	setsdaint();
	return d;
}
unsigned char i2c_write(unsigned char d){
	char x;
	static bit b;
	setsdaout();
	setsclout();
	for(x=0;x<8; x++){
		if(d&0x80) {sdaout(1); }
		else sdaout(0);
		sclout(1);
		
		d <<= 1;
		sclout(0);	
	}
	setsdaint();
	sclout(1);
	coubywi++;
	
	b = sdaint();          // possible ACK bit
	sclout(0);
	if(b){
		if(!(loighi&bocheckloighi_)){
			couerr++;
			coubywi--;
/*			lcd_clr(lines);
			lcd_puts("Ghi EEprom Loi!!\nSBGL/TSBG=");
			lcd_vsprintf("%lu/%lu",couerr,coubywi);
			bell=lockbell;
			ring=0;
			delay_ms(2000);
			bell=offbell;
			ring=1;*/
		}
	}
	return !b;         //=1co ack. =o
}