#include <REGX52.H>
#include <delay.h>
#define  tre   50 
void outputallp(unsigned long x){   
   P1=x;
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
char code font[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90};//duong chung
void main(){
   unsigned char i,j;
   unsigned long x;
   bit huong=1;
   unsigned int xl;
   
    while(1){ 
         P3=(0xff);
   /*      for(xl=0;xl<(1000);xl++){
            for(i=0;i<8;i++){ 
                output_d(0xff);
                output_c(1<<i);
                output_d(font[i]);
                delay_ms(1);       
             }
         }*/
         
         for(j=0;j<4;j++){
          x=1;
          huong=0;
          for(i=0;i<64;i++){           
              outputallp(x);               
              delay_ms(tre);  
              if(i==32) huong=1; 
              if(huong)rotate_right (&x,sizeof(x));else rotate_left (&x,sizeof(x));
          } 
     }	
     nhaydanled(16);
      for(j=0;j<4;j++){
          x=0x1;
          huong=0;
          for(i=0;i<64;i++){           
              outputallp(x);            
              delay_ms(tre);  
              if(i==32) huong=1; 
              if(huong){shift_right (&x, sizeof(x),0);}else {rotate_left (&x,sizeof(x));x=x|1;}         
                            
          } 
      }    
     nhaydanled(16);    
          #define dimer 50         
 
          for(j=0;j<4;j++){ 
          huong=0;
          x=0xffffff00;
          for(i=0;i<54;i++){ 
             if(huong)rotate_right (&x,sizeof(x));else rotate_left (&x,sizeof(x));
             outputallp(x); 
             delay_ms(tre);
             if(i==32) huong=1;              
          }
          
         }
         nhaydanled(16);
      //    x=0x000000;
          for(j=0;j<4;j++){
             huong=0;
             x=0x000000;
             for(i=0;i<32;i++){ 
                if(i==16) huong=1;
                if(huong){ bit_clear(x,i-16);bit_clear(x,47-i);}else{ bit_set(x,15-i);bit_set(x,16+i);}
                outputallp(x); 
                delay_ms(tre);               
             }
          }
          nhaydanled(16);
    
          for(j=0;j<4;j++){
             huong=0;
             x=0x000000;
             for(i=0;i<32;i++){ 
                if(i==16) huong=1;
                if(huong){ bit_clear(x,31-i);bit_clear(x,47-i);}else{ bit_set(x,i);bit_set(x,16+i);}
                outputallp(x); 
                delay_ms(tre);               
             }
          }
          nhaydanled(16);
          for(j=0;j<4;j++){
             huong=0;
             x=0x000000;
             for(i=0;i<32;i++){ 
                if(i==16) huong=1;
                x=0;
                if(huong){ bit_set(x,31-i);bit_set(x,47-i);}else{ bit_set(x,i);bit_set(x,16+i);}
                outputallp(x); 
                delay_ms(tre);               
             }
          }
          nhaydanled(32); 
    }
}