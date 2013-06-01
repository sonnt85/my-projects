

/*#define _BV(bit) (1<<(bit))
#define sbi(sfr,bit) sfr|=_BV(bit)
#define cbi(sfr,bit) sfr&=(~(_BV(bit)))
#define setupbi(sfr,bit,giatri)	if(giatri){ sbi(sfr,bit);}else{cbi(sfr,bit);}
#define bit_is_clear(sfr,xbit) (!((bit)(sfr&(1<<(xbit)))))
#define bit_is_set(sfr,xbit) ((bit)(sfr&(1<<(xbit))))  		 */
#include <lcd.h>
#ifndef __delay__
void delay_ms(unsigned int x){
	unsigned y=113;
	while(x--){
		y=113;
		while(y--);
	}
}
#endif
unsigned char lcd_wait();
unsigned char TroLcd,FunctionSet,EntryModeSet,DisplayControl;
void lcd_writecmd(unsigned char chr);
enum {daudong0=0,         	daudong1=0x40,           daudong2=20,           daudong3=0x40+20,\
      cuoidong0=0+nuli-1,   cuoidong1=0x40+nuli-1,   cuoidong2=20+nuli-1,   cuoidong3=0x40+20+nuli-1};
unsigned char code daudong[]={daudong0,daudong1,daudong2,daudong3};
#if 	lines==4
	#define daudongcuoi daudong3
#elif 	lines==2 
	#define daudongcuoi daudong1
#elif 	lines==1
	#define daudongcuoi daudong0
#else
	#error "Khai Bao So Dong LCD Khong Phu Hop Thuc Te (Khac 1,2,4)"
#endif
	
//BINH THUONG CHAN RS=X; RW=0(VIET TOI LCD DO WAIT VIET) EN=0(DO READ, WRITE 2NIB VIET;
	  /*cai dat huong vao ra cua chan d4-d7 lam dau xuat hoac nhap lieu
	   sau ham nay neu la vao thi thanh ghi in se la gia tri chan d4-d7,
	   sau ham nay neu la ra  thi chan d4-d7 se la gia tri thanh ghi out  */
lcd_setupout(bit i){
	if(i){
		BIT_DDR_D7_LCD=huongra;
		BIT_DDR_D6_LCD=huongra;
		BIT_DDR_D5_LCD=huongra;
		BIT_DDR_D4_LCD=huongra;
	}else{
		BIT_DDR_D7_LCD=huongvao;
		BIT_DDR_D6_LCD=huongvao;
		BIT_DDR_D5_LCD=huongvao;
		BIT_DDR_D4_LCD=huongvao;
	}
}	 

// ham tra lai gia tri cua chan d4-d7
unsigned char  lcd_nhap(){ 
// cai dat du lieu la vao
	lcd_setupout(0);
	return(	((unsigned char)BIT_IN_D4_LCD)|(((unsigned char)BIT_IN_D5_LCD)<<1)|\
			(((unsigned char)BIT_IN_D6_LCD)<<2)|(((unsigned char)BIT_IN_D7_LCD)<<3)\
	);
}

//ham nay xuat gia tri dlieu ra chan d4-d7
void lcd_xuat(unsigned char dlieu){	  
	 lcd_setupout(1);
	 BIT_OUT_D4_LCD=(dlieu)&(1<<0);
	 BIT_OUT_D5_LCD=(dlieu)&(1<<1);
	 BIT_OUT_D6_LCD=(dlieu)&(1<<2);
	 BIT_OUT_D7_LCD=(dlieu)&(1<<3);
}

//sau ham nay thanh ghi cua lcd se nhan duoc phan thap cua dlieu
void lcd_write_nibble(unsigned char dlieu){
	BIT_DDR_EN_LCD=huongra;
	BIT_OUT_EN_LCD=1;
	lcd_xuat(dlieu);
	BIT_OUT_EN_LCD=0;
	lcd_setupout(0); //set lam chan vao tranh xung dot vao ra lan lon
}

// viet du lieu (ky tu) toi lcd, ham nay da su ly xuong dong tu dong
void lcd_write_byte(char chr){
	unsigned char x,FlagGanCuoiDong=0,ToaDoChuyenDong;  
	x=lcd_wait();	 //WDR
	#if(lines==4)
		switch (x){
			case cuoidong0: ToaDoChuyenDong=daudong1,FlagGanCuoiDong=1;
				break;
			case cuoidong1: ToaDoChuyenDong=daudong2,FlagGanCuoiDong=1;
				break;
			case cuoidong2: ToaDoChuyenDong=daudong3,FlagGanCuoiDong=1;
				break;
			case cuoidong3: ToaDoChuyenDong=daudong0,FlagGanCuoiDong=1;
				break;
			default:break;
	}

	#elif (lines==2)

		switch (x){
			case cuoidong0: ToaDoChuyenDong=daudong1;FlagGanCuoiDong=1;
				break;
			case cuoidong1: ToaDoChuyenDong=daudong0;FlagGanCuoiDong=1;
				break;
			default:break;
		}

	#elif (lines==1)
		switch (x){
			case cuoidong0: ToaDoChuyenDong=daudong0;FlagGanCuoiDong=1;
				break;
			default: break;
		}
	#endif
	   if(chr=='\n'){
			#if lines==2
				if(x>=daudong1)x=daudong0; 
				else if(x>=daudong0)x=daudong1;		
			#elif lines==4
				if     ((x>=daudong3))x=daudong0;
				else if((x>=daudong1))x=daudong2; 
				else if((x>=daudong2))x=daudong3; 
				else if((x>=daudong0))x=daudong1; 	
			#elif lines==1
				x=daudong0;
			#endif
			    lcd_writecmd(0x80|x); 
			return;
	   }else{
			BIT_DDR_RS_LCD=huongra;
			BIT_OUT_RS_LCD=1;	//GHI DU LIEU
			lcd_write_nibble(chr>>4);
			lcd_write_nibble(chr);	    
			if((FlagGanCuoiDong)){lcd_writecmd(0x80+ToaDoChuyenDong);}
	}
} 
// viet du lieu (lenh) toi lcd neu lenh xao man thi tre 2ms (lenh nay thuc hien `1.64ms)
void lcd_writecmd(unsigned char chr){	    
	lcd_wait();			//RS=0; RW=0
	BIT_DDR_RS_LCD=huongra;
	BIT_OUT_RS_LCD=0;	//GHI LENH
	lcd_write_nibble(chr>>4);
	lcd_write_nibble(chr);
//	if((chr==1)||(chr==3))delay_ms(3);
}

//dung tre 100us thay kiem tra co ban
void lcd_init(){

	lcd_setupout(0);
//Function set------------------------------------------------------------------------------
	BIT_DDR_EN_LCD=huongra;
	BIT_OUT_EN_LCD=1;		//
	BIT_DDR_RW_LCD=huongra;
	BIT_OUT_RW_LCD=0;		//ghi
	BIT_DDR_RS_LCD=huongra;	
	BIT_OUT_RS_LCD=0;		//chon thanh ghi lenh  
	delay_ms(500);
	//Cai dat mode 4 bit bang cach gui 0x20 theo mode 8 bit
	// moi khoi dong mac dinh la 8 bit nen
    lcd_write_nibble(0x3);//LA 0X3 LA CHE DO 8 BIT
	delay_ms(1);				//bat buoc
	lcd_write_nibble(0x3);	//lenh gui van theo mode 8 bit
	//toi day chac chan la 8 bit
	//toi day chac chan la 8 bit
	delay_ms(1);// bat buoc	  
	//toi day da chac chan dang la mode 8 bit
	lcd_write_nibble(0x2);//lenh gui 8 bit nhung chi quan tam may bit dau nen 
//	delay_ms(5);// bat buoc					   
	//Function set------------------------------------------------------------------------------
    lcd_writecmd(0x28);//4 bit mode, 2 line, 5x8 font  // toi day da ok  2c fong 5x10
	//Display control------------------------------------------------------------------------- 
    lcd_writecmd(0x0C);//hien thi man hinh, con tro ko nhap nhay      0eco tro nhay
	//Entry mode set------------------------------------------------------------------------
    lcd_writecmd(0x06);//ko dich man hinh, con tro tang moi lan doc hoac ghi (VIET TU TRAI QUA FAI)
	lcd_writecmd(0x01);
}
//di chuyen con tro toi toa do cot x hang y
void lcd_gotoxy(unsigned char x,y){
	if(y>=nuli)y=nuli-1;	//vi tri xa nhat
	y=daudong[y];
	if(x>=lines)x=lines-1;  //dong lon nhat
	lcd_writecmd(0x80+x+y);
}
//ghi chuoi ky tu *str len man lcd, *str la bo nho gi cung ok
void lcd_puts(char *str){
       unsigned char i=0,x;
       while(x=str[i]){
//		   //x=lcd_wait();	 	  
		   #if (lines==2)
		    if(((x==daudong0)||(x==daudong1))&&(x==' ')&&(str[i+1]!=' ')) 
		   #elif (lines==4)		   
		   if(((x==daudong0)||(x==daudong1)||(x==daudong2)||(x==daudong3))&&(x==' ')&&(str[i+1]!=' ')) 		     
		   #elif (lines==1)
		    if((x==daudong0)&&(x==' ')&&(str[i+1]!=' '))
		   #endif 
			{i++;continue;}	else {lcd_write_byte(x);i++;}
	   }
}
//ghi font luu trong chuoi *str vao vung cgram co dia chi 0-7
void lcd_make_font(char  code *str,sttchar){	// sao chep font toi cgram, sttchar la stt ma ascii (ty 0 den 7)
	unsigned char i;
	if(sttchar>7)i=0x40;else i=sttchar*8+0x40; // tinh toa do bat dau tu 0
	lcd_wait();
	lcd_writecmd(i);// di chuyen con tro toi vung cgram
	for (i=0; i<7; i++){	//khong ghi dlieu 8 vi dlieu nay la lua chon con tro
		lcd_wait(); 
		lcd_write_byte(str[i]); //ghi tung dlieu vao cgram
	}
}
//ham tra lai gia tri vi tri con tro
unsigned char lcd_wait(){  // sau ham nay thi WDR MCU-->LCD 
	unsigned char x=0;
	unsigned int cou=2000; 
//	delay_us(2000);//170us la du
		
	BIT_DDR_EN_LCD=huongra;

	BIT_DDR_RW_LCD=huongra;
  	BIT_OUT_RW_LCD=1; //chon doc tu lcd

	BIT_DDR_RS_LCD=huongra;
  	BIT_OUT_RS_LCD=0; //chon thanh ghi lenh 
 	
	do{
		cou--;
		BIT_OUT_EN_LCD=1;     
		x=lcd_nhap()<<4;
		BIT_OUT_EN_LCD=0;
		
		BIT_OUT_EN_LCD=1;     
		x|=lcd_nhap();
		BIT_OUT_EN_LCD=0;
	}while((x&(1<<7))&&cou);
	BIT_OUT_RS_LCD=1;// DR
	BIT_OUT_RW_LCD=0;   // MCU-->LCD
	return x;	//ko can xoa bit co ban thu 7 vi duong nhien se ko ban (bang 0)
}