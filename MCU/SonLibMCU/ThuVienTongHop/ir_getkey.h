#ifndef __getkey__
#define __getkey__
#define    ir_init() (IRIN=1)
#define    ir_in() (IRIN)

#define    IRIN    (P3_2)
enum {flagtimeout_=0x01,chongat_=0x02,nodis_=0x04,bilink_=0x08,ngat2_=0x10,ngat0_=0x20,phimnong_=0x40,tattat_=0x80};
//cac bit trong	flagstatus 
enum {minmax_=0x01,phimtm_=0x02,PAXX_=0x04,eidl_=0x80,delay_=0x40};
typedef enum  PHIMCHUCNANG{tang0=0,tang1=1,tang2=2,tang3=3,ambao=10,tat=25,hienthoigian=12,admin=11,bat=19,giamthoigian=21,prev=21,\
ok=22,tangthoigian=23,next=23, menu=24,thoat=26,setupthietbi=18,khongchon=24,thoatlap=128,tathetthietbi=20,battatbaodong=13,,mokhoa=27,swchanel2=28,checkonoff=10,bbreak=27,khoa,datpass,checkeep=13}   ;

#ifndef ir_getkey__c
	extern char data flagstatus;
#else
	#include	<THANHSONCHIP.H>
	#include	<checktimeout.h>
	#include	<lcd.h>
	#include	<bell.h>
	#include	<stdio.h>
	#include	<delay.h>
	#include	<digi2text.h>
	#include	<stdarg.h>
#endif

unsigned char checkswchanel();
char ir_getkey(unsigned char codebell);   //bien x dung xac nhan dat timeout, va dieu khien coi cac loai
unsigned int getkeyab(unsigned int dmin,unsigned int dmax,unsigned char display)  ;
unsigned char ir_getkeytimeout(unsigned char maring,unsigned char indexjmp);
unsigned char nhappass(unsigned int pass);//pass la so nguyen 16 bit
void setclearflag(unsigned char codeset);
void waitsig(char indexjmp);  
#endif
