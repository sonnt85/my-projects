#define   digi2text__c
#include  <digi2text.h >
unsigned char digi2text(void *tprg,unsigned char coso,unsigned long temp){  //tra lai so ohan tu trong chuoi tru null
	char k=0,pdu=0,*tpr=(char *)tprg;
	do{	
		pdu=temp%coso;
		temp=temp/coso;
		switch (pdu){
			case 10:*(tpr+k)='A';
			break;
			case 11:*(tpr+k)='B';
			break;
			case 12:*(tpr+k)='C';
			break;
			case 13:*(tpr+k)='D';
			break;
			case 14:*(tpr+k)='E';
			break;
			case 15:*(tpr+k)='F';
			break;
			case 16:*(tpr+k)='G';
			break;
			case 17:*(tpr+k)='H';
			break;
			case 18:*(tpr+k)='I';
			break;
			case 19:*(tpr+k)='J';
			break;
			case 20:*(tpr+k)='K';
			break;
			case 21:*(tpr+k)='L';
			break;
			case 22:*(tpr+k)='O';
			break;
			default: *(tpr+k)=0x30+pdu;
			break;
		}
		k++;
	}while(temp);
	*(tpr+k)=0;
	k--;
	for(pdu=0;pdu<=(k/2);pdu++)	{
		temp=*(tpr+pdu)  ;
		*(tpr+pdu)=*(tpr+k-pdu);
		*(tpr+k-pdu)=temp;
	}
	return (++k);
}
unsigned int xpowy(unsigned char x,unsigned char y){
	unsigned char i;
	long temp=1;
	for(i=0;i<y;i++)temp=temp*x;
	return temp;
}
void digi2textbin(void *tpr,unsigned char len,unsigned long x){
	unsigned char temp=digi2text(tpr,2,x);//co the temp=len
	if(len>=temp){memmove((uchar*)tpr+len-temp,tpr,temp+1);memset(tpr,'0',len-temp);}
	else memmove(tpr,(uchar*)tpr+temp-len,len+1);	
}
 