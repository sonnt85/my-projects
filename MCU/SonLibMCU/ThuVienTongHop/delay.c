#define   delay__c
#include  <delay.h>
void delay_bcycle(unsigned char reg){                  //toi da 256+3=259 chu ky may
	while(reg){ _nop_();_nop_();reg--;};   //tre cycle*8+5 chu ky may
}

void delay_1000cycle(){                 //bot mot vai chu ky do no bi ham khac goi
	 delay_cycle(1000-4);                  //ham nay dung neu ham delay_cycle() thiet ke chuan
}

void delay_n1000cycle(unsigned char reg){
 while(reg){ delay_1000cycle();reg--;};
}  
void delay_1ms(){
  delay_cycle(us2cycles(1000)-4);
}

void delay_ms(unsigned int ms){
  while(ms){
    delay_1ms();
    ms--;
  }
}