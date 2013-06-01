#ifndef __lcdthanhson__
#define __lcdthanhson__
#include <THANHSONCHIP.H>
//cac ham khong dung
//void move_CGRAM(unsigned char sttchar); // chuyen tro ve dau vi tri vung ram co ma asski la 	sttchar roi viet 8 byte lien tiep
#ifndef  lcd__c
	extern unsigned char lcdcode;
#else
	#include	<delay.h> 
	#include	<stdio.h>
	#include	<string.h>
	#include <stdarg.h>

#endif
	enum {chuyendong_=0x1,sulycach_=0x02};

void	cd_write_nibble (char byte);
char	read_char();			//KO THE SAI
void	lcd_write_char(char chr);  // viet du lieu toi lcd
void	lcd_writecmd (char chr) ;
uchar	lcd_wait();	 // sau ham nay thi WDR MCU-->LCD
char	Data_LCD_In();
void	Data_LCD_Out (char dlieu);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//cac ham hay dung
void	lcd_init()	;
void	lcd_clr(uchar x);
char	lcd_gotoxy(uchar x,uchar y);//tra lai gia tri ky tu tai toa do xy
void	lcd_puts(char *str);
void	lcd_putchar(char a);
void	lcd_putcharxy( char a,uchar b,uchar c);   //toa do bc ky tu a
void	lcd_putsxy( char *a,uchar b,uchar c);//toa do bc chuoi a
void	lcd_make_font(char  *str,uchar sttchar);	// sao chep phon toi cgram, sttchar la stt ma ascii (ty 0 den 7)
void	lcd_vsprintf(char *fmt, ...);
void	lcd_goto(x);
char	gotohome(char y);
char	checkhome();
/*void lcd_putsf(char code *str);*/
//void PutChar_CGRAM(unsigned char chr) ; //viet toi cgram la du lieu
#define	lcd_home()				 lcd_writecmd(0x02);	//ve dau dong ko xoa gi het	
#define	lcd_displayset(codedis)  lcd_writecmd(0x8|codedis);
#define	lcd_modeset(codemod)     lcd_writecmd(0x4|codemod);
#define	lcd_cursorset(codeset)   lcd_writecmd(0x10|codeset);
                      //Khai bao chan va cac macro
#define 		RS_LCD 		P2_5
#define 		RW_LCD 		P2_6
#define 		EN_LCD 		P2_7

#define     LED_LCD   P2_4

#define     D4_LCD    P2_3
#define     D5_LCD    P2_2
#define     D6_LCD    P2_1
#define     D7_LCD    P2_0

//NHOM CHAN DU LIEU
#define	lines	4
#define	nuli	20
#define	lcdthat
#define	setuppincontrol()  EN_LCD=0;

#define	SetDataIn()    D4_LCD=1,D5_LCD=1,D6_LCD=1,D7_LCD=1;
#define	SetDataOut() 																  
#endif