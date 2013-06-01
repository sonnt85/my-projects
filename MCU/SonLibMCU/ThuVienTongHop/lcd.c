

//NHOM CHAN DIEU KHIEN NOI VOI 1 PORT
//#define K_LCD  P2_4	 //THUTU CHAN NOI DEN NEN
/*#define _BV(bit) (1<<(bit))
#define sbi(sfr,bit) sfr|=_BV(bit)
#define cbi(sfr,bit) sfr&=(~(_BV(bit)))
#define bit_is_clear(sfr,xbit) (!((bit)(sfr&(1<<(xbit)))))
#define bit_is_set(sfr,xbit) ((bit)(sfr&(1<<(xbit))))  */
#define	lcd__c
#define		BF_LCD   (1<<7)				   //phu thuoc vao nguoc bit ko va dung bit htap hay cao de noi, dung cho chek bf
#include	<lcd.h>
uchar		lcd_waitg();
char	checknewline();	
unsigned char lcdcode=0;
//enum {chuyendong_=0x1,sulycach_=0x02};
enum {daudong0=0,         daudong1=0x40,           daudong2=20,           daudong3=0x40+20,\
      cuoidong0=0+nuli-1,   cuoidong1=0x40+nuli-1,   cuoidong2=20+nuli-1,   cuoidong3=0x40+20+nuli-1} ;
unsigned char code daudong[]={daudong0,daudong1,daudong2,daudong3};
#if lines==4
 #define daudongcuoi daudong3
#elif lines==2 
 #define daudongcuoi daudong1
#else
 #error "Chua Khai Bao So Dong LCD"
#endif

//BINH THUONG CHAN RS=X; RW=0(VIET TOI LCD DO WAIT VIET) EN=0(DO READ, WRITE 2NIB VIET;

char  Data_LCD_In(){
   return( ((char)D4_LCD<<0)|((char)D5_LCD<<1)|((char)D6_LCD<<2)|((char)D7_LCD<<3));
}
void Data_LCD_Out(char dlieu){
	D4_LCD=((dlieu)&1); 
	D5_LCD=((dlieu)&2);
	D6_LCD=((dlieu)&4);
	D7_LCD=((dlieu)&8);
}

void lcd_write_nibble(char dlieu){
	SetDataOut();
	RW_LCD=0;	//Ghi(CMU->LCD
    EN_LCD = 1;
	Data_LCD_Out(dlieu);
	EN_LCD = 0;
}

char read_char(){
	char HNib,LNib;
	lcd_waitg();//RS=1; RW=0
	RW_LCD=1;	// doc LCD->MCU
	RS_LCD=0;	// IR
	SetDataIn();	// CHO DATA LAM DAU VAO
	
	EN_LCD=1;	//enable LCD BIET DAY LA DOC NEN LAY DU LIEU RA
	HNib=Data_LCD_In();//lay 4 bit cao cua datalcd, 4 bit cao=0
	EN_LCD=0;	//disable
	HNib<<=4; 
	
	EN_LCD=1; //enable LCD BIET DAY LA DOC NEN LAY DU LIEU RA
	LNib=Data_LCD_In()  ; 
	EN_LCD=0; //disable
	
	return (HNib|LNib);
}

void lcd_write_char(char chr){// viet du lieu toi lcd
	lcd_waitg();	 //WDR
	SetDataOut();
	RS_LCD=1; 
	lcd_write_nibble(chr>>4);
	lcd_write_nibble(chr);
}

void lcd_writecmd(char chr){
	lcd_waitg();	//RS=1; RW=0
	SetDataOut();
	RS_LCD=0;   //IR
	lcd_write_nibble(chr>>4);
	lcd_write_nibble(chr);
}

void lcd_writecmdnw(char chr){
	SetDataOut();
	RS_LCD=0;   //IR
	lcd_write_nibble(chr>>4);
	lcd_write_nibble(chr);
}

uchar lcd_waitg(){     // sau ham nay thi WDR MCU-->LCD cur_, blin_ 
	char  temp_hi=0,temp_low=0;
	unsigned int cout=0;
	SetDataIn(); //dat 4 bit cao lam dau vao,4 BIT THAP KO DOI
	RS_LCD=0; //chon thanh ghi lenh  ok
	RW_LCD=1; //chon doc tu lcd		ok
	delay_us(20);
	do{
		EN_LCD=1;     
		temp_hi=Data_LCD_In();
		EN_LCD=0;
		
		EN_LCD=1;
		temp_low=Data_LCD_In();
		EN_LCD=0;
		temp_hi=(temp_hi<<4)|temp_low;
		cout++;
	}while((temp_hi&BF_LCD)&&cout);
	RS_LCD=1; // DR
	RW_LCD=0; // MCU-->LCD
	// if(temp_hi==(0xf+1)){lcd_gotoxynw(0,1);temp_hi=0x4f;}
	// else if(temp_hi==(0x4f+1)){lcd_gotoxynw(0,0);temp_hi=0;}
	return temp_hi;
}

char gotoline(char y){ //tra lai toa do con tro dang dung o dau dong moi
	uchar x=lcd_waitg();
	if(y>=lines)y=lines-1;
	#if lines==2
	switch (y){
		case 0:	lcd_writecmdnw(x=daudong0|0x80);
		break;
		case 1:	lcd_writecmdnw(x=daudong1|0x80);
		break;
	}	
	#elif lines==4	
	switch (y){
		case 0:lcd_writecmdnw(x=daudong0|0x80);
		break;
		case 1:	lcd_writecmdnw(x=daudong1|0x80);
		break;
		case 2: lcd_writecmdnw(x=daudong2|0x80);
		break;
		case 3:lcd_writecmdnw(x=daudong3|0x80);
		break;
	}
	#endif	
	return x&(~0x80);
}

char gotohome(char y){ //tra lai toa do dau dong hien tai
	uchar x=lcd_waitg();
	#if lines==2
		if((x>=daudong0)&&(x<=cuoidong0))x=daudong0; 
		else if((x>=daudong1)&&(x<=cuoidong1))x=daudong1;		
	#elif lines==4
		if     ((x>=daudong0)&&(x<=cuoidong0))x=daudong0; 
		else if((x>=daudong1)&&(x<=cuoidong1))x=daudong1; 
		else if((x>=daudong2)&&(x<=(cuoidong2)))x=daudong2; 
		else if((x>=daudong3)&&(x<=(cuoidong3)))x=daudong3;		
	#endif
	if(y)lcd_writecmd(x|0x80);
	return x;
}
char checkhome(){
	uchar x=lcd_wait();
	#if lines==2
		if((x==daudong0)||(x==daudong1))return 1; 
		else return 0;	
	#elif lines==4
		if ((x==daudong0)||(x==daudong1)||(x==daudong2)||(x==daudong3))return 1; 
		else return 0;
	#endif
}

void  lcd_init(){	
	led_lcd=0;
	RW_LCD=0;   // W
	RS_LCD=0;   // IR
	setuppincontrol();
	delay_ms(45);
	//Function set------------------------------------------------------------------------------
	lcd_write_nibble(0x3); //ko co wati 
	delay_us(5000);
	lcd_write_nibble(0x3); //ko co wati 
	delay_us(5000);
	lcd_write_nibble(0x3); //ko co wati 
	delay_us(5000);
	lcd_write_nibble(0x2); //ko co wati 
	lcd_writecmd(0x28);//4 bit mode, 2 line, 5x8 font  // toi day da ok  2c fong 5x10
	
	//Display control------------------------------------------------------------------------- 
	lcd_writecmd(0x0C);	//hien thi man hinh, con tro ko nhap nhay      0eco tro nhay
	//Entry mode set------------------------------------------------------------------------
	lcd_writecmd(0x06);	   //ko dich man hinh, con tro tang moi lan doc hoac ghi (VIET TU TRAI QUA FAI)
	lcd_writecmd(0x01);		   //font so dong ko thay doi duoc sau lenh nay tru khi mat dien
}
char lcd_gotoxy(uchar x,uchar y){
	if(x>=nuli)x=nuli-1;	//vi tri xa nhat
	if(y>=lines)y=daudongcuoi; else y=daudong[y]; //dong lon nhat
	lcd_writecmd(0x80+x+y);
	lcdcode&=(~chuyendong_);
	return read_char();//
}

void lcd_goto(x){      	    
	lcd_writecmd(x|0x80);
	lcdcode&=(~chuyendong_);	  //sai lam neu xoa cai nay vi neu dung
}

void lcd_puts(char *str){
	char   pos,temp;
	while(*str){
		lcd_putchar(*str);
		str++;
		if(*(str-1)==' '){		
			if((pos=lcd_waitg())==(gotohome(0)+1)){
				if(*(str)!=' '){gotohome(1);}
		   	}//neu la dau dong thi ko put dau cach ra
		   	else{//vi tri hien tai ko fai dau dong
				if((*(str)!=0)&&(*(str)!='\n')){
					pos=strpos(str,' ');//chinh la so phan tu them vao ke tu sau dau cach dau
					temp=strpos(str,'\n');
					if(pos==temp)pos=strlen(str);	//chi bang khi ca hai =-1
					else if((pos==-1) || ((pos>=0)&&(temp>=0)&&(temp<pos))) pos=temp; 					
				
					if((lcd_waitg()-gotohome(0)+pos)>nuli){
						lcd_putchar('\n');//xuong dong
				    }
				}
			}	
		}	 
	}	
}
/*void move_CGRAM(unsigned char sttchar) // chuyen tro ve dau vi tri vung ram co ma asski la 	sttchar roi viet 8 dlieu lien tiep
{
       unsigned char Ad;			   //sttchar tu 0-->7
	   if(sttchar>0x40-1)Ad=0x40;else Ad=sttchar*8+0x40; // tinh toa do bat dau tu 0
	   lcd_writecmd(Ad);
}
void PutChar_CGRAM(unsigned char chr)  //viet toi cgram la du lieu
{ 
       WriteChr(chr);
}  */

/*void lcd_make_font(char *str,unsigned char sttchar)	// sao chep phon toi cgram, sttchar la stt ma ascii (ty 0 den 7)
{ 
       unsigned char i;
	   if(sttchar>7)i=0x40;else i=sttchar*8+0x40; // tinh toa do bat dau tu 0
     lcd_waitg();
	   lcd_writecmd(i);

       for (i=0; i<7; i++)	//khong ghi dlieu 8 vi dlieu nay la lua chon con tro
        {
     lcd_waitg(); 
		 lcd_write_char(str[i]); //ghi tung dlieu vao cgram
		}
}*/
char checknewline(){ //moi khi put cha can kiem tra ham nay	tra lai toa do chuyen doi xuong dong
	char temp=lcd_waitg();
	#if (lines==4)
		if      (temp==cuoidong0+1)		return 0x80|daudong1;
		else if (temp==cuoidong1+1)		return 0x80|daudong2;
		else if (temp==(cuoidong2+1))	return 0x80|daudong3;
		else if (temp==(cuoidong3+1))	return 0x80|daudong0;
		else return 0;
	#elif (lines==2)
		if      (temp==cuoidong0+1)		return 0x80|daudong1;
		else if (temp==cuoidong1+1)		return 0x80|daudong0;
		else return 0;
	#endif 
}

void lcd_putchar(char a){
	uchar temp;
	led_lcd=0;
	if(lcdcode&chuyendong_){
		lcd_writecmd(checknewline()); //co dong moi thi chuyen dong moi
		lcdcode&=(~chuyendong_); 
		if(a!='\n')lcd_write_char(a);//neu khac cuong dong thi put ky tu ra dau dong
	}else{
		//  lcdcode&=(~chuyendong_);
		if(a=='\n'){
			temp=gotohome(0);//ko co dong moi
			#if lines==4
				if      (temp==daudong0)   gotoline(1);
				else if (temp==daudong1)   gotoline(2);
				else if (temp==daudong2)   gotoline(3);
				else if (temp==daudong3)   gotoline(0);
			#elif lines==2
				if      (temp==daudong0)   gotoline(1);
				else if (temp==daudong1)   gotoline(0);
			#endif
		}else{
			lcd_write_char(a);
			if(checknewline())lcdcode|=chuyendong_;
		}//else bang 0 san ro
	}
}

void lcd_putcharxy(char a, uchar b, uchar c){    //toa do bc ky tu a
     lcd_gotoxy(b,c);
     lcd_putchar(a);
}

void lcd_putsxy(char *a, uchar b, uchar c){
      lcd_gotoxy(b,c);
      lcd_puts(a); 
}

void lcd_vsprintf(char *fmt, ...) {  
	if(strlen(fmt)>=sizeof(lcd_buff)){
		lcd_clr(lines);
		lcd_puts("Loi Tran Bo Dem lcd_buff. Loi Nay Nguy Hiem Vo Cung...");
		bell=lockbell;
		ring=0;
		delay_ms(10000);
		bell=offbell;
	}
	else{	
		va_list arg_ptr;
		va_start (arg_ptr, fmt); /* format string arg_ptr=&fmt+sizeof(fmt) tro toi tiep theo sau fmt*/
		vsprintf (lcd_buff, fmt, arg_ptr);//
		va_end (arg_ptr);
		lcd_puts(lcd_buff);
	}  
}

void lcd_clr(uchar x){
	char i;
	if(x>=lines)lcd_writecmd(0x01);//lon hon so dong lcd thi xoa toan bo man hinh va tro ve dau
	else {
		lcd_writecmd(x=(daudong[x]|0x80));
		for(i=0;i<nuli;i++)lcd_write_char(' ');
		lcd_writecmd(x);
	}
	lcdcode&=(~chuyendong_);
}

uchar lcd_wait()	{     // sau ham nay thi WDR MCU-->LCD cur_, blin_ 
	if(lcdcode&chuyendong_)return checknewline();
	else return (lcd_waitg()|0x80); //co dong moi thi chuyen dong moi
}


