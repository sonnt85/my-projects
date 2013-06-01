#include  <allfuntion.h>
#include <delay.h>
#include <intrins.h>
void delay_bcycle(unsigned char reg)                  //toi da 256+3=259 chu ky may
{
    while(reg){ _nop_();_nop_();reg--;};   //tre cycle*8+5 chu ky may
}

void delay_1000cycle()                 //bot mot vai chu ky do no bi ham khac goi
{
  delay_cycle(1000-4);                  //ham nay dung neu ham delay_cycle() thiet ke chuan
}

void delay_n1000cycle(unsigned char reg)
{
 while(reg){ delay_1000cycle();reg--;};
}

void delay_1ms()
{
  delay_cycle(us2cycles(1000)-4);
}

void delay_ms(unsigned int ms)
{
  while(ms)
  {
    delay_1ms();
    ms--;
  }
}

void delay_test(unsigned int ms)
{
  while(--ms);
}


/*{      
//tre tinh theo miligiay, toi da 65535ms 
  TH1=(unsigned int)(xtal/12.0*(65536+24)-xtal/12.0*x)>>8;
  TL1=(unsigned char)(xtal/12.0*(65536+24)-xtal/12.0*x);
  TMOD|=0x10; // che do 1 16 bit co tran
  TF1=0;
  TR1=1;
  while(!TF1);
  TF1=0;
  TR1=0;
}
/*unsigned int demus(void)	 //ham tao tre don vi thoi gian micro giay (174-->
{
	TMOD=TMOD|0x90; //chon che do dinh thoi 16 bit CUA TIME 1 dieu khien ngoai gate1=1,ct=0 dung xung dong ho trong, m01m00=1 che do 16 bit 
	TH1=0;
	TL1=0;
	TF1=0;	//xoa co tran TF0
	TR1=1; //cho bo dem time 1 duoc chay
//	ET1=1;// cho phep ngat time 1
	while(T1==1);		//T1 thay bang chan nao do cua vi dieu khien, co the do xug + hoac am
	TR1=0;
	TF1=0;
	return (((unsigned int)TH1<<8)+((unsigned int)TL1));   return 0;
} 	*/
