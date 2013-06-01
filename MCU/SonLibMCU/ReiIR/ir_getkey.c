/*
Mo ta: Thu tin hieu hong ngoai, tra lai gia tri la command cua tin hieu da duoc chuan hoa
Phan cung: mat nhan IR co chan out noi vao 1 chan cua dk*/
#include  <allfuntion.h>
#include <REGX52.H>
#include <delay.h>
#include <ir_getkey.h>


#include  <digi2text.h>
#define     loaidk   0xBFFB
#define     loailenh 0XFEFF
#define     chobit   700
char code lenhgoc[]={0x66,0xf6,0x76,0xb6,0x36,0xd6,0x56,0x96,0x16,0xe6,0x42,0x32,0x72,0x74,0xb2,
                             0x2e,0x0e,0xf4,0x12,0xd2,0xce,0x7a,0x6c,0xfa,0xb4,0x52,0x5e,0x62,0x22,
                                0x1e,0x9e}  ;    //2 nut cuoi la cua da nang
char code lenhchuanhoa[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,
                             28,14};
char ir_getkey(unsigned char x)   //bien x dung xac nhan dat timeout, va dieu khien coi cac loai
{
   union
   {
      long    ucommand ;
      int     uaddress ;
   }  u4 ;
#define   address u4.uaddress
#define   command u4.ucommand
unsigned      char     n;
ir_init();
while(x==9);
thulai:
 //Hearder       3554  1637
    for ( n=0;n<100;n++)
    {
        delay_us(20);
        if(IRIN){goto thulai;};
    }

    while(!IRIN);
    for(n=0;n<10;n++)
    {
         delay_us(100);
         if(!IRIN){goto thulai;}
    }

    while (IRIN);

//Het Hearder bat dau thu address hay con goi predata
    address=0;
    for(n=0;n<16;n++)
    {
        while(!IRIN);
        delay_us(chobit);
        address=(address<<1);
        if(IRIN==0){address=(address|1);}
        while(IRIN);
    }
    if((int)loaidk!=address){goto thulai;}  //kiem tra toi day la dung toi phan sau thi sai ????

   //Thu xong dia chi tiep theo thu lenh
    for(n=0;n<32;n++)
    {
        while(!IRIN);
        delay_us(chobit);
        command=(command<<1);
        if(IRIN==0){command=(command|1);}
        while(IRIN);
    }

    if((int)(command>>16)!=loailenh){goto thulai;} // toi day van dang dung

    if( ((char)(((int)command)>>8))!=((char)command+1)){goto thulai;}

 for(n=0;n<sizeof(lenhgoc);n++)    //chuyen lenh sang lenh chuan hoa;
   {
     if(lenhgoc[n]==(char)command)
      {
         if(lenhchuanhoa[n]==thoat){eeprom_reads(adee_env(ljmp1),kithenv,env);};
         return lenhchuanhoa[n];
      }
   }
  goto thulai;
}
unsigned int getkeyab(unsigned char dmin,dmax)   //bien x dung xac nhan dat timeout, nhap va0 so >=a <=b
{
 unsigned char code arrbuff[5];
 unsigned char i,strmax;
 unsigned long digi=0,temp;
 strmax=digi2text(arrbuff,10,dmax);  //so chu so cua dmax
 for(i=strmax;i!=0;i--)
 {
   do{temp=digi+ir_getkey(0)*xpowy(10,i);} while((temp<dmin)|(temp>dmax)) ;
   digi=temp;
 }	
 return digi;
}
