#include <REGX52.H>
#include <delay.h>
#include <lcd.h>
char code font[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90};//duong chung
unsigned int xl;
unsigned char i;
#define  tre   20 
void outputallp(unsigned long x){   
 //  P1=x;
   P3=(x>>8);
   P2=(x>>16);
   P0=(x>>24);
}
void nhaydanled(unsigned char x){ 
unsigned char i;
          for(i=0;i<x;i++){              
              if(i%2)outputallp(0xffffffff);else outputallp(0);                
              delay_ms(tre);              
          }
}
void testled(){
unsigned long x;
          // Place your code here  
          x=1;
          for(i=0;i<32;i++){           
              outputallp(x);               
              delay_ms(tre);  
              x<<=1;                
          }  
          x=0x80000000;
          for(i=0;i<32;i++){           
             outputallp(x);             
              delay_ms(tre);  
              x>>=1;
              
          } 

          x=0x1;
          for(i=0;i<32;i++){           
              outputallp(x);            
              delay_ms(tre);  
              x<<=1;
              x=x|1;
              
          }  
             x=0xffffffff;
          for(i=0;i<32;i++){           
              outputallp(x);                
              delay_ms(tre);  
              x>>=1;              
          }  
          x=0xffffffff;              
          for(i=0;i<32;i++){           
             outputallp(x);                 
              delay_ms(tre*5);  
               x=~x;            
          }           
}
#define nhay	P0
#define dir P1_5
#define pwm P1_4

void main(){
pwm=1;
	lcd_init();
	lcd_puts("Son Xin Chao Ba Con");
	delay_ms(500);
	lcd_wcmd(xoadram);
	lcd_puts("Son Test");
while(1){	
	pwm=0;
	dir=0;
	delay_ms(5000);
	pwm=1;
	delay_ms(4000);
	pwm=0;
	dir=0;
	delay_ms(5000);
}

//	P3=~0XAA;
	while(1){
		nhay=0;;
		delay_ms(1000);
		nhay=0xff;
		delay_ms(1000);
	}
	delay_ms(65000);
	while(1){
		lcd_clr();
		lcd_puts("   Hello word \n     8051Kit");
		testled();
		        P3=(0xff);
		        for(xl=0;xl<(500);xl++){
		            for(i=0;i<8;i++){ 
		                P3=(0xff);
		                P3=(1<<i);
		                P2=(font[i]);
		                delay_ms(2);       
		             }
		      }

	}
}