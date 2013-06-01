#ifndef __lcdthanhson__
#define __lcdthanhson__
#include <REGX52.H>
#include <delay.h>
//cac ham hay dung
void lcd_init();
//di toi cot x hang y
void lcd_gotoxy(unsigned char x,y);
enum {xoadram=0x01,tatman=0x8,batman=0xC,nhaytro=0xF,tattro=0xC};
#define    lcd_putchar(a)	       lcd_write_byte(a)
void lcd_puts(char *str) ;
void lcd_make_font(char  code *str,sttchar);// sao chep phon toi cgram, sttchar la stt ma ascii (ty 0 den 7)
void lcd_writecmd(unsigned char chr);
void lcd_write_byte(char chr);
#define lcd_wcmd(a) lcd_writecmd(a)

#define    lcd_home()	           lcd_writecmd(0x02)	//ve (0,0) ko xoa gi het
#define    lcd_clr()               lcd_writecmd(0x01)
//xoa man hinh va dua con tro ve dau dong 1

#define    lcd_putcharxy(a,b,c)    lcd_gotoxy(b,c),lcd_putchar(a);
#define    lcd_putsxy(a,b,c)       lcd_gotoxy(b,c),lcd_puts(a); 
#define    lcd_putsfxy(a,b,c)      lcd_gotoxy(b,c),lcd_putsf(a);
//khai bao loai LCD

#define	lines	4		  //so dong
#define	nuli	20 		  //so chu tren mot dong
                          //Khai bao chan va cac macro
#define		huongvao	1			 
#define		huongra		0
#define     LedLcd      			P2_4
//#define 	VITRI_RS_LCD			7		 	 //VI TRI
#define 	BIT_DDR_RS_LCD			P2_5	     //PORT DIEU KHIEN HUONG
#define 	BIT_OUT_RS_LCD			P2_5		 //PORT XUAT DU LIEU RA
#define 	BIT_IN_RS_LCD			P2_5		 //PORT NHAP DU LIEU VAO

//#define 	VITRI_RW_LCD			6		 	 //VI TRI
#define 	BIT_DDR_RW_LCD			P2_6	     //PORT DIEU KHIEN HUONG
#define 	BIT_OUT_RW_LCD			P2_6		 //PORT XUAT DU LIEU RA
#define 	BIT_IN_RW_LCD			P2_6		 //PORT NHAP DU LIEU VAO

//#define 	VITRI_EN_LCD			5		 	 //VI TRI
#define 	BIT_DDR_EN_LCD			P2_7     //PORT DIEU KHIEN HUONG
#define 	BIT_OUT_EN_LCD			P2_7		 //PORT XUAT DU LIEU RA
#define 	BIT_IN_EN_LCD			P2_7	 //PORT NHAP DU LIEU VAO

//#define 	VITRI_D4_LCD			3		 	 //VI TRI
#define 	BIT_DDR_D4_LCD			P2_3	     //PORT DIEU KHIEN HUONG
#define 	BIT_OUT_D4_LCD			P2_3		 //PORT XUAT DU LIEU RA
#define 	BIT_IN_D4_LCD			P2_3		 //PORT NHAP DU LIEU VAO

//#define 	VITRI_D5_LCD			2		 	 //VI TRI
#define 	BIT_DDR_D5_LCD			P2_2	     //PORT DIEU KHIEN HUONG
#define 	BIT_OUT_D5_LCD			P2_2		 //PORT XUAT DU LIEU RA
#define 	BIT_IN_D5_LCD			P2_2		 //PORT NHAP DU LIEU VAO

//#define 	VITRI_D6_LCD			1		 	 //VI TRI
#define 	BIT_DDR_D6_LCD			P2_1	     //PORT DIEU KHIEN HUONG
#define 	BIT_OUT_D6_LCD			P2_1		 //PORT XUAT DU LIEU RA
#define 	BIT_IN_D6_LCD			P2_1		 //PORT NHAP DU LIEU VAO

//#define 	VITRI_D7_LCD			0		 	 //VI TRI
#define 	BIT_DDR_D7_LCD			P2_0	     //PORT DIEU KHIEN HUONG
#define 	BIT_OUT_D7_LCD			P2_0		 //PORT XUAT DU LIEU RA
#define 	BIT_IN_D7_LCD			P2_0		 //PORT NHAP DU LIEU VAO

#endif