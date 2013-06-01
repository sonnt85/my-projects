#include <REGX52.H>	  //bat buoc vi dung den dinh nghia cac thanh ghi
//extern unsigned char   AR1,AR2;
#include <DelayUSMS_NTS.h>


void delayusg(void)	 //ham tao tre don vi thoi gian micro giay (174-->

{
//tre tinh theo miligiay, toi da 65535ms 

#pragma asm
using   0
ORL  	TMOD,#010H
CLR  	TF1
SETB    TR1
JNB  	TF1,$
CLR  	TF1
CLR  	TR1
#pragma endasm 
}
void delaymsg(void)//tre tinh theo miligiay, toi da 65535ms 
{
#pragma asm
USING 	0
LAP1:

MOV     TL1,#low 64558
MOV     Th1,#high 64558
ORL  	TMOD,#010H
CLR  	TF1
SETB 	TR1
JNB  	TF1,$
CLR  	TF1
CLR  	TR1

CLR		C
MOV     A,AR2
SUBB    A,#1
MOV     AR2,A

MOV		A,AR1
SUBB	A,#0
MOV		AR1,A

MOV		A,AR2
JNZ    	LAP1
MOV		A,AR1
JNZ		LAP1
#pragma endasm 
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
