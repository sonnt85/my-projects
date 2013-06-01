//led noi voi port2 va p0_4,5,6,7
#define disnuled__c
#include <disnuled.h>
unsigned char	code toledhexa[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
unsigned char	code toledhexk[16]={~0xc0,~0xf9,~0xa4,~0xb0,~0x99,~0x92,~0x82,~0xf8,~0x80,~0x90,~0x88,~0x83,~0xc6,~0xa1,~0x86,~0x8e};
void hienthihex(unsigned int n){
	unsigned char	dv,ch,tr,ng;
	static	unsigned	char	bdts;
	ng=n/(coso*coso*coso);
	n=n%(coso*coso*coso);
	tr=n/(coso*coso);
	n=n%(coso*coso);
	ch=n/coso	;
	dv=n%coso;
	switch (bdts){
		case 0:{comled1=off;comled2=off;comled3=off;bdts++;portled=toledhexa[dv];comled0=on;break;}
		case 1:{comled0=off;comled2=off;comled3=off;bdts++;portled=toledhexa[ch];comled1=on;break;}
		case 2:{comled0=off;comled1=off;comled3=off;bdts++;portled=toledhexa[tr];comled2=on;break;}
		case 3:{comled0=off;comled1=off;comled2=off;bdts=0;portled=toledhexa[ng];comled3=on;break;}
		default:bdts=0;
	}	 
}
unsigned int   tobcd(unsigned int n){
	unsigned char	dv,ch,tr,ng;
	ng=n/1000;
	n=n%(1000);
	tr=n/(100);
	n=n%(100);
	ch=n/10	;
	dv=n%10;
	return	((((int)dv|((int)ch<<4))|((int)tr<<8))|((int)ng<<12));
}  
