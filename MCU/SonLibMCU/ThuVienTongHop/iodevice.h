#ifndef __iodevice__
#define __iodevice__
#include <AT89X52.H>
 /*   #define  diachimach  mcdao
    #if diachimach==mcdao
   //   sbit	IRIN=P3^3;//go va mach nap va cau dao chung tat   */
   //   sbit 	LED=P0^0; //cau dao
   //   sbit	IRIN=P3^2;//go va mach nap va cau dao chung tat
      sbit	IRIN=P0^0;
      
      sbit 	STRS=P0^5;//nha cau dao
      sbit 	DSS=P0^7; //nha cau dao
      sbit 	CPS=P0^6; //nha cau dao
      sbit 	sensorct=P0^4; //nha cau dao	thua vi luon cho =1 de xuat ra cac thiet bi
      						
	  sbit  ring=P0^1;
      
    //  sbit  SCL=P3^6;
   //   sbit  SDA=P3^7;
 
      sbit  SCL=P0^3;
      sbit  SDA=P0^2;
      
      sbit      led_lcd     =P2^4;
      sbit 		RS_LCD 		=P2^5;
      sbit 		RW_LCD 		=P2^6;
      sbit 		EN_LCD 		=P2^7;
      
      
      sbit     D4_LCD    =P2^3;
      sbit     D5_LCD    =P2^2;
      sbit     D6_LCD    =P2^1;
      sbit     D7_LCD    =P2^0;
 /*   #else  
      sbit 	LED=P0^1;//go va mach nap va go moi
      sbit  sensorc=P3^1;//go moi co
      sbit  sensorb=P3^2;//go moi co
    #endif   */
    /*#if diachimach==mcdao
sbit 	LED=P0^0; //cau dao
#else  
sbit 	LED=P0^1;//go va mach nap va go moi
#endif 
sbit	IRIN=P3^3;//go va mach nap va cau dao chung tat
//sbit	IRIN=P0^0;// IRIN mach go moi

//sbit 	SDA=P3^7; //mach nap va go
//sbit 	SCL=P3^6; //mach nap va go
//sbit 	LED=P0^1;//go va mach nap va go moi
sbit    sensorc=P3^1;//go moi co
sbit    sensorb=P3^2;// go moi co

//thong so chan cang ghi dich
sbit 	STRS=P0^1;//nha cau dao
sbit 	DSS=P0^2; //nha cau dao
sbit 	CPS=P0^3; //nha cau dao
#endif*/
#endif