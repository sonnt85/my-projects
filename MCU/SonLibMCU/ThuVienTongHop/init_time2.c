#include <REGX52.H>
#include  <allfuntion.h>
#include  <typedef.h >
#include  <init_time2.h>
extern unsigned char demngat2;
void ouputtime2f(unsigned long f){////HAM NAY CHUAN
	TR2=0;
	TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
	T2MOD|=T2OE_;//set che do ouput xung
	C_T2=0;//dat che do time ko fai dem
	EXEN2=0;//bo chan ngat reload T2EX
	
	RCAP2L=-(unsigned int)(xtal/4/f);
	RCAP2H=(-(unsigned int)(xtal/4/f))>>8;
	TR2=1;
	// ET2=0; neu muon ngat ngoai thi cho bit nay bang 1
}

unsigned int  t2capture(){ //HAM NAY CHUAN
	TR2=0;
	TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
	T2MOD&=(~T2OE_); //bo che do ouput neu da cai
	
	C_T2=0;//lay xung trong dem thoi gian
	EXEN2=1;//se load bo dem vao rcap2 khi co ngat 1-0 tai T2EX dong thoi tao ngat EXF2
	//co ngat xay ra ta vao doc gia tri rcap2 chinh la so xung dem dc ke tu luc set
	while(!T2EX);//bat dau co tin hieu thi set cho tr2 chay
	TR2=1;
	while(!EXF2);
	return (RCAP2L+(unsigned int)RCAP2H<<8);
}

void t2autoreload(){  //HAM NAY CHUAN 
	TR2=0;
	TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
	T2MOD&=(~T2OE_); //bo nap ra t2, bo che do tu nap lai dcen-0( o anh huong chan ngoai)
	T2MOD&=(~DCEN_); // =0 dem tang
	EXEN2=0;//bo chan ngat reload T2EX
	
	RCAP2L=-(us2cyclesl(50000));//thay 50000 bang so chu ky may mong muon
	RCAP2H=(-(us2cyclesl(50000)))>>8;
	
	ET2=1;// cho ngat time 2
	
	PT2=0; //dat uu tien
	
	TR2=1;
}

void t2baud(unsigned int baud){////HAM NAY CHUAN 
	TR2=0;
	TCLK=1;RCLK=1;//ca thu phat uart dung time 2 tao baut cac che do khac se tu ko hoat dong
	/*	T2MOD&=T2OE_; //bo nap ra t2, bo che do tu nap lai dcen-0( o anh huong chan ngoai)
	T2MOD&=DCEN_; // =0 dem tang*/ //ko quan tam may thu nay do
	EXEN2=0;//bo chan ngat reload T2EX neu dat bang 1 thi co ngat nhung cung ko bi reload
	C_T2=0; //bat buoc clear bit nay bao cho dung time
	RCAP2L=-xtal/32/baud;
	RCAP2H=-xtal/32/baud>>8;
	
	ET2=1;//
	
	TR2=1;
} 

 void com_init (unsigned int baud) { // dung time1 //HAM NAY CHUAN 
	  // Configure timer 1 as a baud rate generator
	TCLK=0;RCLK=0;//tao baud thu fat deu dung time 1 mac dinh la 00 luon
	PCON |= SMOD_;// 0x80=SMOD: set serial baudrate doubler
	
	TMOD = T1_M0_&(~T1_M1_)&(~T1_CT_)&(~T1_GATE_);//tuong duong lenh duoi, lenh nay ro hon ve cau truc fan cung
	TMOD |= 0x20;// put timer 1 into MODE 2
	
	TH1 = (unsigned char) (- (xtal / (16L * 12L * baud)));
	TR1 = 1;// start timer 1
	//khoi lenh nay tuong duong lenh duoi nhung ro net hon
	{
		RI   = 1;//set khi co ngat thu phai set de co the thu dc ban dau
		TI   = 1;//set khi co ngat phat phai set de co the phat duoc ban dau
		RB8  = 0;//ko cho thu bit 8 chi set khi multi
		TB8  = 0;//ko cho truyen bit 8 chi set khi multi
		REN  = 1;//cho phep thu
		SM2  = 0;//ko phai che do multy
		SM1  = 1;
		SM0  = 0;  
	}
	SCON = 0x53;  // serial port MODE 1, enable serial receiver
	PS=1;//uu tien ngat noi tiep do co che do thu ngay nhien
	ET1=0;//ko ngat time 1 mac dinh la vay
	ES = 1;// enable serial interrupts
}


