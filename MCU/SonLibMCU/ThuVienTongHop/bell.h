#ifndef  __setbell__
#define __setbell__
unsigned 	char	setbell(unsigned char codebell);
unsigned 	char	getbell();
void		checkbellauto();
typedef enum{offbell=0,binhthuong,bellonoff,bellspace,bellerror,bellwarning,\
			bellsucsesful,bellarlam,lockbell,baodotnhap,diir_=0x80};
#include <THANHSONCHIP.H>
sbit  ring=P0^1;
#ifndef bell__c
	extern  unsigned char bell;
#else
	#include	<delay.h>
#endif
#endif