#include <REGX52.H>
#include <MT888_NTS.H>
#include <DelayUSMS_NTS.h>
//#define SPK P0_1
#define dedt  110
#define tredapmay  221				  //toi thieu 210ms

//#define dgbitthap
#define sbis(sfr,bit) ((sfr)|(1<<(bit)))
#define cbis(sfr,bit) ((sfr)&(~(1<<(bit))))
//unsigned char code phimso[]={10,1,2,3,4,5,6,7,8,9,
void WriteDT_MT(unsigned char temp,bit dat);
unsigned char ReadDT_MT(bit dat);
bit bnhacmay=0;
sbit nhacmay=P3^7 ;
sbit daocuc=P1^1 ;
//#pragma OT(11)
 
enum {BURST,TEST,SND,CNR,TOUT,CPNDTMF,IRQ,RSEL} bcrab; 
union 
{
		struct  
		{
		  unsigned char  BURST		:1  ;
		  unsigned char  TEST 		:1  ;
	      unsigned char  SND  		:1  ;	  
		  unsigned char  CNR  		:1  ;
		  unsigned char  TOUT 		:1  ;
		  unsigned char  CPNDTMF	:1	;
		  unsigned char  IRQ		:1	;
		  unsigned char  RSEL		:1	;
		} abbit;
		unsigned char abreg;

}bcrabk;

void main(void)
{ 
//bit btemp;
//unsigned char tempcra;	
	delayms(100);
	CS_NMT=0;									   
	int_MT();
	setup_MT(0Xd2);
//	setup_MT(cbis(bcrab,TOUT));
//	setup_MT(sbis(bcrab,CPNDTMF));
	tranmisDTMF(949109985,10);	  //39923571 ,01662576689
  delayms(10000);			 //toi thieu sau 4485 giay thi ben kia nhan dc tin hieu
 //	setup_MT(cbis(bcrab,TOUT));
	setup_MT(sbis(bcrab,CPNDTMF));

  nhacmay=0;Phi_MT=1;
  while(1);
  {P0=ReadDT_MT(0);delayms(1000);}
  nhacmay=0;
  
Phi_MT=1;
	while(1);
	setup_MT(sbis(bcrab,CPNDTMF)); //kiem tra che do call process
}
void int_MT()  // theo nha san xuat thoi cai nay chuan roi ko can chinh
{
	ReadDT_MT(0);
	WriteDT_MT(0,0);  //cra hoac crb nhung sau do nhat dinh fai la cra
	WriteDT_MT(0,0); //cra
	WriteDT_MT(0x8,0);//cra sau lan nay la crb
	WriteDT_MT(0,0);  //crb sau lan nay se tu quay ve cra
	ReadDT_MT(0);
}
void setup_MT(unsigned char crab)  // setup theo tham so truyen vao, chuan ko can chinh nua
{
	bcrab=crab;
	WriteDT_MT((crab>>4)|8,0); //dcra phat tone, dtmf (ko fai cp), cho tao ngat( noi dung ngat do bit b1(test) cua rcb) ,lan sau ghi vao crb
	WriteDT_MT(crab&0xF,0); //0crb, hat da tone khong
//	 test chon phat burs 50/50
}
unsigned char ReadDT_MT(bit dat)  //ham nay da ok, doi khi buon
{
	unsigned char temp;
	Data_MT=(Data_MT&Mark_MT)|(~Mark_MT); //cho lam dau vao va che bit khac ngoai b0-->b3
	RS0_MT=~dat;
	RW_MT=1;

	Phi_MT=1;
	datain(temp);
	Phi_MT=0;

		
	return temp;
}
void WriteDT_MT(unsigned char temp,bit dat)		// ham nay cung da ok
{
	if(dat){nhacmay=1;}
	RS0_MT=~dat;
	RW_MT=0;

	Phi_MT=1;
	dataout(temp);
	Phi_MT=0;
	if(dat){delayms(dedt);}
}


void tranmisDTMF(unsigned long digi,unsigned char scs)
{

	 char temp;
	 nhacmay=0;			//dap may truoc khi quay so moi
	 delayms(tredapmay);
	 nhacmay=1;
	 delayms(300);		//nhac may sau 280ms thi quay so moi co nghia voi 11 so, 10 so yeu cau nho hon
	if(scs==11)		 	//viet 0 vao dau so do neu la 11 so thi so dau luon la 0
		{
			WriteDT_MT(10,1);  //viet 0 vao dau so do neu la 11 so thi so dau luoon la 0
			scs--;
		}

	  { 
	   	unsigned char str[10],j;
		Number2bcd(str,scs,digi); //conver thanh chuoi so rieng biet luu trong mang str
		for(j=0;j<scs;j++)
			{	
				WriteDT_MT(str[j],1);
			}
	 }
}

/*void tranmis1diDTMF(unsigned char so)
{
		unsigned char temp;
		nhacmay=1;
//		do{temp=ReadDT_MT(0); }while(!(temp&(1<<1)));
		WriteDT_MT(so,1);  //viet 0 vao dau so do neu la 11 so thi so dau luoon la 0
}  */

unsigned char recDTMF(void)
{
		unsigned char temp;
		do{temp=ReadDT_MT(0);}while(!(temp&(1<<2)));  //kiem tra xem co ky tu moi chua
		return ReadDT_MT(1);
}

void Number2bcd(unsigned char *tpr,scs,unsigned long x)	 //ham nay chuan roai
{
unsigned long temp=x;
char k=0,pdu;
do{	
		   pdu=temp%10;
		   temp=temp/10;
		   if(pdu==0){*(tpr+scs-k-1)=10;}else{*(tpr+scs-k-1)=pdu;}	
		   k++;	
  }while(k!=scs);
}