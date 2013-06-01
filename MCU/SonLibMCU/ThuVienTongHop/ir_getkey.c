/*
Mo ta: Thu tin hieu hong ngoai, tra lai gia tri la command cua tin hieu da duoc chuan hoa
Phan cung: mat nhan IR co chan out noi vao 1 chan cua dk*/
//#include <AT89X52.H>
#define  ir_getkey__c
#include <ir_getkey.h>

#define     loaidk   0xBFFB
#define     loailenh 0XFEFF
#define     chobit   700
char code lenhgoc[]={0x66,0xf6,0x76,0xb6,0x36,0xd6,0x56,0x96,0x16,0xe6,0x42,0x32,0x72,0x74,0xb2,
                     0x2e,0x0e,0xf4,0x12,0xd2,0xce,0x7a,0x6c,0xfa,0xb4,0x52,0x5e,0x62,0x22,
					 0x1e,0x9e}  ;//2 nut cuoi la cua da nang
char code lenhchuanhoa[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,
                          28,14};
union{
	long    ucommand ;
	int     uaddress ;
}u4;

#define   address u4.uaddress
#define   command u4.ucommand
unsigned      char     n;
char data flagstatus;
void waitsig(char indexjmp){  
	settimeout(indexjmp&(~(eidl_|delay_)),tioums(60000L));
	if(indexjmp&delay_)delay_ms(2000);
	flagstatus|=(chongat_|flagtimeout_);
	if(indexjmp&eidl_){while(ir_in())PCON|=IDL_;}else while(ir_in());
	flagstatus&=(~chongat_);
	//settimeout(0,notimeout);khong can thiet vi da xoa chongat thi 
}
char ir_getkey(unsigned char codebell){   //bien x dung xac nhan dat timeout, va dieu khien coi cac loai
	if((codebell&(~diir_))==offbell){bell=offbell;ring=1;}
	ir_init();
	thulai:
	flagstatus|=chongat_;
	//Hearder       3554  1637
	for ( n=0;n<100;n++){
		delay_us(20);
		if(ir_in())goto thulai;
	}
	//if((bell!=offbell)){bell=offbell;ring=1;}	
	
	while(!ir_in());
	for(n=0;n<10;n++){
		delay_us(100);
		if(!ir_in()){goto thulai;}
	}
	while (ir_in());
	flagstatus&=(~chongat_);//xoa ko cho ngat thuc hien ham fuc tap
	//Het Hearder bat dau thu address hay con goi predata
	address=0;
	for(n=0;n<16;n++){
		while(!ir_in());
		delay_us(chobit);
		address=(address<<1);
		if(ir_in()==0){address|=1;}
		while(ir_in());
	}
	if((int)loaidk!=address){goto thulai;}  //kiem tra toi day la dung toi phan sau thi sai ????
	//Thu xong dia chi tiep theo thu lenh
	for(n=0;n<32;n++){
		while(!ir_in());
		delay_us(chobit);
		command=(command<<1);
		if(ir_in()==0){command|=1;}
		while(ir_in());
	}
	
	if((int)(command>>16)!=loailenh){goto thulai;} //toi day van dang dung
	
	if( ((char)(((int)command)>>8))!=((char)command+1)){goto thulai;}
	
	for(n=0;n<sizeof(lenhgoc);n++){    //chuyen lenh sang lenh chuan hoa;
		if(lenhgoc[n]==(char)command){
			led_lcd=0;
			n=lenhchuanhoa[n];
			setbell(codebell);//cai dat am bao dua tren thong so truyen vao codebell
			if(codebell&diir_){sprintf(lcd_buff,"%02u",(uint)n);lcd_puts(lcd_buff);}
			if(n==hienthoigian){lcd_clr(lines);hienthithoigian(&timesys);}
			if(n==thoat){eeprom_reads(adee_env(0),sizeof(env),env);longjmp(env,'i');};
			//delay_ms(100);
			return n;
		}
	}
	goto thulai;
}
unsigned char ir_getkeytimeout(unsigned char maring,unsigned char indexjmp){  
	unsigned char temp;
	settimeout(indexjmp,tioums(60000L));
	//while(ir_in())PCON|=IDL_;
	temp=ir_getkey(maring);
	settimeout(0,notimeout);
	return temp;
}
unsigned int getkeyab(unsigned int dmin,unsigned int dmax,unsigned char display){   //bien x dung xac nhan dat timeout, nhap va0 so >=a <=b
	//unsigned char arrbuff[33];//so toi da 65536 la 5 chu + 1 null cua chuoi =6
	unsigned char i,strmax,strmin,sobam;
	unsigned long digi=0,temp,toadotruyen=lcd_wait();
	while(getbell()!=offbell);
	strmax=digi2text(lcd_buff,10,dmax)-1;//so chu so cua dmax, bi loi truyen tham so sai
	strmin=digi2text(lcd_buff,10,dmin)-1;
	if(display&minmax_){
		sprintf(lcd_buff,"%u->%u",dmin,dmax);
		lcd_putsxy(lcd_buff,0,lines-1);
		lcd_goto(toadotruyen);
	}
	
	if(display&PAXX_)for(i=0;i<strmax+1;i++){lcd_putchar('X');}
	lcd_goto(toadotruyen);
	
	for(i=(strmax);i!=0xFF;i--){
		//while(ir_in());
		thulaichuso:
		delay_ms(100);
		while((temp=ir_getkeytimeout(offbell&(~diir_),0))>9);//tranh tran so ma thoi
		sobam=(unsigned char)temp+0x30;
		temp=digi+temp*xpowy(10,i);
		if(strmin<i){if(temp>dmax)goto thulaichuso;}
		else {if((temp<dmin)||(temp>dmax)) goto thulaichuso;}
		
		if(display&phimtm_)lcd_putchar(sobam);
		//xongthem1chuso:
		digi=temp;
		setbell(binhthuong);
	}
	setbell(bellsucsesful);//da nhap thanh cong	
	while(getbell()!=offbell);
	return digi;
}
unsigned	char	cou=0;
unsigned	int	temp;
unsigned char nhappass(unsigned int pass){
	#define solannhap  5
	cou=0;		//pass da bi thay doi
	temp=0;
	lcd_clr(lines);lcd_puts("He Thong Duoc Bao Ve Nhap Ma Bao Ve!");
	while(++cou!=solannhap) {delay_ms(1500);
		lcd_clr(lines);sprintf(lcd_buff,"Lan Nhap Pass:%u\n",(uint)(cou));lcd_putsxy(lcd_buff,0,0);
		lcd_puts("InPuting..");
		temp=getkeyab(0,65535,phimtm_|PAXX_);
		lcd_clr(lines);
		if(temp==pass){lcd_puts("    Pass OK !!\nHello Boss Son");return 1;}
		else if(temp==1985) {lcd_puts(" Vao Loi He Thong!\nHello Boss NTS");return 1;}
		else {sprintf(lcd_buff,"Con:%bu Lan Nhap Pass",(uchar)(solannhap-cou));lcd_puts(lcd_buff);}
	}
	lcd_clr(lines);
	lcd_puts("Truy Cap Trai Phep\nKhong Thanh Cong!!");
	settimeout(ljmp0,tioums(60000L));//settime out
	flagstatus|=(chongat_|flagtimeout_);
	while(1);
}
unsigned char checkswchanel(){
	unsigned char keyir,temp;
	keyir=ir_getkeytimeout(binhthuong,ljmp0);
	flagstatus&=(~phimnong_);
	if(keyir==swchanel2){
		lcd_clr(lines);
		lcd_puts("So Byte Loi Ghi\n");
		lcd_vsprintf("%lu",couerr);
		lcd_puts("\nTong So Byte Ghi\n");
		lcd_vsprintf("%lu",coubywi);
		if(tanghientai==(sotang-1)){
			if((temp=sothietbi-sothietbi1tang*(sotang-1))<=10)return swchanel2 ;
		}else temp=sothietbi1tang;
		delay_ms(100);
		while((keyir=(ir_getkeytimeout(binhthuong,ljmp0)+10))>=temp){bell=offbell;ring=1;delay_ms(50);}
		flagstatus|=phimnong_;
	}
	return keyir;
}

