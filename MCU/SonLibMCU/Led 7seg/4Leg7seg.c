#include <REGX52.H>
//led noi voi port2 va p0_4,5,6,7
#include <4Leg7seg_NTS.h>

unsigned char	code toledhexa[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
unsigned char	code toledhexk[16]={~0xc0,~0xf9,~0xa4,~0xb0,~0x99,~0x92,~0x82,~0xf8,~0x80,~0x90,~0x88,~0x83,~0xc6,~0xa1,~0x86,~0x8e};

void hienthihex(unsigned int n)
{

	unsigned char	dv,ch,tr,ng;
	static 		    unsigned bdts;
  dv=n%coso;n=n/coso;
  ch=n%coso;n=n/coso;
  tr=n%coso;n=n/coso;
  ng=n%coso;n=n/coso;

	
	switch (bdts)
	{
 		case 0:{P0_5=1;P0_6=1;P0_7=1;bdts++;portled=toledhexa[dv];leddv=0;break;}
		case 1:{P0_4=1;P0_6=1;P0_7=1;bdts++;portled=toledhexa[ch];ledch=0;break;}
		case 2:{P0_4=1;P0_5=1;P0_7=1;bdts++;portled=toledhexa[tr];ledtr=0;P2_7=0;break;}
		case 3:{P0_4=1;P0_5=1;P0_6=1;bdts=0;	   P2=toledhexa[ng];ledng=0;break;}
		default:
		bdts=0;
	}	 
}
unsigned int   tobcd(unsigned int n)
		{
		unsigned char	dv,ch,tr,ng;
		bit ET2B=ET2;// da loai tru dc ngat lam anh huong den BCD
		ET2=0;
			ng=n/1000;
			n=n%(1000);
			tr=n/(100);
			n=n%(100);
			ch=n/10	;
			dv=n%10;
			{
				unsigned int tam=(((dv|(ch<<4))|(tr<<8))|(ng<<12));
				ET2=ET2B; 
				return tam;	
			}					
		}  
