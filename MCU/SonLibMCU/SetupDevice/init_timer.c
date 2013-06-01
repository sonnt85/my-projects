#include  <allfuntion.h>
#include  <init_timer.h >
#include <delay.h>
#include <REGX52.H>
void init_timer()
{
		TMOD|=0x01; //16 bit time0, che do  dem c/t=0, khong chiu anh huong chan ngoai t0
		
    TH0=((unsigned int)(-(us2cyclesl(60000000)/1000L))>>8);
    TL0=(unsigned int)(-(us2cyclesl(60000000)/1000L)); 
		
		ET0=1;//cho ngat time 0

		PT0=1; //cai dat uu tien ngat

		TR0=1; // cho bo dem chay
	//cai dat time2

/*		T2MOD&=T2OE_; //bo nap ra t2, bo che do tu nap lai dcen-0( o anh huong chan ngoai)
    T2MOD&=DCEN_; // =0 dem tang
    EXEN2=1;//bo chan ngat reload T2EX

		RCAP2L=-(us2cyclesl(50000));
		RCAP2H=(-(us2cyclesl(50000)))>>8;
			
		ET2=1;
		
		PT2=0; //dat uu tien

		TR2=1;*/
    EA=1; // cho ngat toan cuc
}
void com_initialize (unsigned int baud) 
{
//#define baud  9600L
#define xtal1  12000000L        // Configure timer 1 as a baud rate generator
  TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
  PCON |= SMOD_; 			         // 0x80=SMOD: set serial baudrate doubler
  TMOD |= 0x20; 			         // put timer 1 into MODE 2
  TH1 =-(unsigned char)((xtal / 16L / 12L )/ baud);

  SCON = 0x53;			         // serial port MODE 1, enable serial receiver
// RI   = 0;
//TI   = 1;//bat buoc
//RB8  = 0;
//TB8  = 0;
//REN  = 1;
//SM2  = 0;
//SM1  = 1;
//SM0  = 0;
TR1 = 1; 				// start timer 1

}
void ouputtime2f(unsigned long f)
{
  TR2=0;
  TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
  T2MOD|=T2OE_; //set che do ouput xung
  C_T2=0;//dat che do time ko fai dem
  EXEN2=0;//bo chan ngat reload T2EX

  RCAP2L=-(unsigned int)((xtal/4)/f);
  RCAP2H=(-(unsigned int)((xtal/4)/f))>>8;
  TR2=1;
  ET2=0;
}