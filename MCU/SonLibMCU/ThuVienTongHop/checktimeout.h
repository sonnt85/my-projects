#ifndef  __checktimeout__
#define __checktimeout__
//typedef enum {timeout0_=0x01,timeout1_=0x02,timeout2_=0x04,timeout3_=0x08,timeout4_=0x10,timeout5_=0x20,timeout6_=0x40,timeout7_=0x80;};
unsigned 	char	checktimeout();//tra ve gia tri flagenv
unsigned 	char	settimeout(unsigned char vitri,unsigned char giatri);//vi tri tu 0->7
unsigned 	char	gettimeout(unsigned char vitri);//vi tri tu 0->7
void		writeenvtoeeprom(unsigned char vitri);
#define soenv	2
#define 	adee_env(i)			((i)*(sizeof(jmp_buf)+1))//them 1 la bien dem
#define  	setjmpeep(vitri)	setjmp(env),writeenvtoeeprom(vitri)
typedef enum  {ljmp0,ljmp1,ljmp2,ljmp3,ljmp4,ljmp5};

typedef 	enum  {notimeout=0,nosensor=1};
	#include  <setjmp.h>

#ifndef checktimeout__c
	extern jmp_buf        	  env; //bien toan cuc
	extern unsigned char data flagenv;
#else
//	#include  <retiao.h >  da viet ham nay trong day luon roi
	#include  <24c3264.h>
	#include  <setjmp.h>
	char code trongsoset[8]={ 1, 2, 4, 8, 16, 32, 64, 128}   ; //dung trong set bit phep or
	char code trongsoclear[8]={ ~1, ~2, ~4, ~8, ~16, ~32, ~64, ~128}   ; //dung trong set bit phep or
#endif
#endif