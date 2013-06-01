#include  <allfuntion.h>
#include  <digi2text.h >
#include  <typedef.h>
unsigned char digi2text(unsigned char *tpr,unsigned char coso,unsigned long x)
{
unsigned long temp=x;
char k=0,pdu=0;
do{

       pdu=temp%coso;
       temp=temp/coso;
       switch (pdu)
       {
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
  for(pdu=0;pdu<=(k/2);pdu++)
  {
    temp=*(tpr+pdu)  ;
   *(tpr+pdu)=*(tpr+k-pdu);
   *(tpr+k-pdu)=temp;
  }
  return (k-1);
 }
unsigned int xpowy(unsigned char x,y)
 {
  unsigned char i;
  long temp=1;
  for(i=0;i<y;i++)temp=temp*x;
  return temp;
 }