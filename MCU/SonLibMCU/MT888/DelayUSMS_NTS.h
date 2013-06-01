#ifndef __DelayUSMS__
#define __DelayUSMS__
#include <absacc.h>
#include <REGX52.H>
extern void delayusg(void);
extern void delaymsg(void) ;
#define	delayus(timeus) TH1=(65536-timeus+24)>>8;TL1=(65536-timeus+24);delayusg();
#define	delayms(timems)	DBYTE[1]=(timems)>>8;DBYTE[2]=timems;delaymsg();
#endif