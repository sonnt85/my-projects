
#define  outputdevice__c 
#include <allfuntion.h>
#include <outputdevice.h>
#include <typedef.h>
#include <iodevice.h>

void outputdevice(unsigned char idata *ptr)	  //ham nay dung moi trong kiem tra tat bat dinh ky	 ham nay da chek
{
#ifdef ghidich
  unsigned char data i=sochip4094,countbit=8,temp;
//  EOS=1;
  STRS=1;
  ptr+=(i-1); 
  while(i--){
    temp=*ptr;
    countbit=8;
    while(countbit--){
          CPS=0; //bit du lieu tu bit7 truyen sang o'
          DSS=temp&0x80;//nhap bien dich vao day
          CPS=1;   //day du lieu ra DSS

          DSS=1; // cho dss=1 de chuan bi day bit7 moi( tu b6 chuyen sang) ra o'
      //    CPS=0;
          temp<<=1;
      }
   ptr--;			   
  } 
  STRS=0;    //cps=1;dss=1
#else
P1=*ptr;
P3=ptr[1];	
#endif
}

/*void shiffbit(unsigned char bits)
{       //trang thai roi cps=1, dss=1,strs=0
  STRS=1; 

  CPS=0;
  DSS=bits;//nhap bien dich vao day
  CPS=1;   //day du lieu ra DSS
  
  DSS=1; // cho dss=1 de chuan bi day bit7 moi( tu b6 chuyen sang) ra o'
  CPS=0;  // bit 7 moi dc day ra

  STRS=0;
  CPS=1;    //trang thai roi cps=DSS=1, strs=0

}
void shiffbyte(unsigned char varin)	  //ham nay dung moi trong kiem tra tat bat dinh ky	 ham nay da chek
{
  register unsigned char countbit=8;
  EOS=1;
  STRS=1;
    while(countbit--)
      {
          CPS=0;         //bit du lieu tu bit7 truyen sang o'
          DSS=varin&0x80;//nhap bien dich vao day
          CPS=1;   //day du lieu ra DSS
          DSS=1; // cho dss=1 de chuan bi day bit7 moi( tu b6 chuyen sang) ra o'
      //    CPS=0;
          varin<<=1;
      }
   STRS=0;    //cps=1;dss=1
}*/

