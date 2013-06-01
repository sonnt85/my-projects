#define		init_tiin__c
#include	<init_tiin.h >
//extern unsigned char demngat2;
#ifndef modex2
	#error "Chua Khai Bao Mode"
#endif
void init_tiin(){
	// FST|=*EDC_;
	//CAI DAT TIME0
	init_time0();
	//CAI DAT TIME2
	t2autoreload(delaytime2us) ;  //HAM NAY CHUAN
	//CAI DAT CONG NOI TIEP
	com_init_ti1 (9600);// dung time1 //HAM NAY CHUAN 
	//t2baud(9600);
	//CAI NGAT NGOAI X CHI CAN CAI EXX VA ITX(LOAI NGAT MUC SUON) LA XONG
	EA=1; // cho ngat toan cuc
}

void init_time0(){
	TR0=0; 
	//TMOD|=0x01; //16 bit time0, MODE 1 che do  dem c/t=0, khong chiu anh huong chan ngoai t0
	TMOD=TMOD &(~T0_GATE_)&(~T0_CT_)&(~T0_M1_)|(T0_M0_);//tuong duong lenh duoi, lenh nay ro hon ve cau truc fan cung
	
	TH0=((-(unsigned int)((us2cycles(60000000L-cycles2us(18)))/cou1min))>>8);
	TL0=-((us2cycles(60000000L-cycles2us(18)))/cou1min); 
	
	PT0=1; //cai dat uu tien ngat
	ET0=1;//cho ngat time 0
	TR0=1; // cho bo dem chay	
}

void ouputtime2f(unsigned long f){
	TR2=0;
	TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
	T2MOD|=T2OE_; //set che do ouput xung
	C_T2=0;//dat che do time ko fai dem
	// RL2=0;// ko can quan tam bit nay
	EXEN2=1;//bo chan ngat reload T2EX HOAC KICH HOAT 
	// con 1 bit tmod trong pcon lam tang baud
	RCAP2L=-((xtal*modex2/4)/f);
	RCAP2H=(unsigned int)(-((xtal*modex2/4)/f))>>8;
	TR2=1;
	ET2=1;  // cho ngat ngoai time 2 dong thoi ngat time tran cung kich hoat, tru khi rclk hoac tclk set thi se ko co ngat tran time
	RCLK=1; //muc dich bo ngat tran timer neu khong no se cu bi tran
}

unsigned int  t2capture(){ //HAM NAY CHUAN ngat ngoai capture do chant2ex 1-0 do do rong xung +
	//ko tao ngat ma cho
	TR2=0;
	TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
	T2MOD&=(~T2OE_);//bo che do ouput neu da cai
	
	C_T2=0;//lay xung trong dem thoi gian
	RL2=1;// dat che do capture
	TH2=0;
	TL2=0;
	EXEN2=1;//se load bo dem vao rcap2 khi co suon 1-0 tai T2EX 
			//dong thoi bat co EXF2( tao ngat), bat buoc set 1 neu muon che do capture
	TR2=1; //bo dem tran thi co TF2 cung dc set neu cho ET2=1 thi se cho tao ngat
	ET2=1;
//	return (RCAP2L+(unsigned int)RCAP2H<<8)/modex2;
}

void t2baud(unsigned long baud){////HAM NAY CHUAN 
	TR2=0;
	TCLK=1;RCLK=1;//ca thu phat uart dung time 2 tao baut cac che do khac se tu ko hoat dong
	T2MOD=T2MOD&(~T2OE_)&(~DCEN_); //bo nap ra t2, bo che do tu nap lai dcen-0( o anh huong chan ngoai)
	//DCEN_ =0 dem tang fai quan tam vi neu truoc do cho bo dem giam la loi ngay
	EXEN2=0;//bo chan ngat reload T2EX neu dat bang 1 thi co ngat nhung cung ko bi reload
	C_T2=0;//bat buoc clear bit nay bao cho dung time
	//if(PCON&(SMOD_)) baud/=2; ko phu thuoc smod_ chi co time 1 fu thuoc ma thoi
	baud=-(xtal*modex2/32/baud);
	RCAP2L=baud;
	RCAP2H=baud>>8;
	//RCAP2H=0xFF;
	//RCAP2L=0xD9;
	ET2=1;//
	TR2=1;
	/*{
	RI   = 1;//set khi co ngat thu phai set de co the thu dc ban dau
	TI   = 1;//set khi co ngat phat phai set de co the phat duoc ban dau
	RB8  = 0;//ko cho thu bit 8 chi set khi multi
	TB8  = 0;//ko cho truyen bit 8 chi set khi multi
	REN  = 1;//cho phep thu
	SM2  = 0;//ko phai che do multy
	SM1  = 1;
	SM0  = 0;  
	}*/
	SCON=0x53;// serial port MODE 1, enable serial receiver
	//PS=1;//uu tien ngat noi tiep do co che do thu ngay nhien
	//ET1=0;//ko ngat time 1 mac dinh la vay
	//ES =1;// enable serial interrupts
}

void t2autoreload(unsigned int us){   //HAM NAY CHUAN 
	TR2=0;
	TCLK=0;RCLK=0;//2 bit nay phai bang 0 neu ko phai tao baut
	T2MOD&=(~T2OE_); //bo nap ra t2, bo che do tu nap lai dcen-0( o anh huong chan ngoai)
	T2MOD&=(~DCEN_); // =0 dem tang nhu binh thuong ko fu thuoc t2ex
	EXEN2=0;//bo chan ngat reload T2EX neu khong se tu loat khi chua tran neu fat hien xung 1-->0 tai chan t2ex
	
	C_T2=0;//lay xung trong bo dao dong 
	RL2=0;//de che do autoreload khi tran time tf2
	us=-us2cycles(us);;
	RCAP2L=us;//thay 50000 bang so chu ky may mong muon
	RCAP2H=us>>8;
	
	//EXF2 se tu dong togle khi co trao time 2--> ko can quan tam bit nay trong ngat vi no ko tao ra ngat (ko can xoa)
	PT2=0; //dat uu tien
	TR2=1;
	ET2=1;// cho ngat time 2
}

void com_init_ti1 (unsigned int baud){ // dung time1 //HAM NAY CHUAN	
	TR1 = 0; 	        // Configure timer 1 as a baud rate generator
	TCLK=0;RCLK=0;//tao baud thu fat deu dung time 1 mac dinh la 00 luon
	PCON |=(SMOD_); // bo che do double baud; 0x80=SMOD: set serial baudrate doubler chi tac dung voi time 1
	//PCON &=(~SMOD_); //
	TMOD=TMOD &(~T1_GATE_)&(~T1_CT_)|(T1_M1_)&(~T1_M0_);//tuong duong lenh duoi, lenh nay ro hon ve cau truc fan cung
	//TMOD |= 0x20; 			         // put timer 1 into MODE 2
	if(PCON&SMOD_)baud/=2;
	baud/=modex2; //do time c0 anh huong toi
	baud=-((xtal/384 )/ baud);
	TH1 =baud; 
	TR1 = 1; 				// start timer 1
	//khoi lenh nay tuong duong lenh duoi nhung ro net hon
	/* {
	RI   = 1;//set khi co ngat thu phai set de co the thu dc ban dau
	TI   = 1;//set khi co ngat phat phai set de co the phat duoc ban dau
	RB8  = 0;//ko cho thu bit 8 chi set khi multi
	TB8  = 0;//ko cho truyen bit 8 chi set khi multi
	REN  = 1;//cho phep thu
	SM2  = 0;//ko phai che do multy
	SM1  = 1;
	SM0  = 0;  
	}*/
	SCON=0x53;// serial port MODE 1, enable serial receiver
	//PS=1;//uu tien ngat noi tiep do co che do thu ngay nhien
	//ET1=0;//ko ngat time 1 mac dinh la vay
	//ES =1;// enable serial interrupts
}