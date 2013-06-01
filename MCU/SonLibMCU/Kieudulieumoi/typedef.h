#ifndef __typedef__
#define __typedef__
#include <setjmp.h>

//*******************************************************************
typedef struct
  {        
    unsigned char gio:5; 
    unsigned char phut:6; 
    unsigned char giay:6;
  }def_time;       //dinh nghia cau truc kieu thoi gian gio phut giay 
//*******************************************************************
typedef struct 
  { 
    unsigned char thu:3;    //1(cn) 2-3-4-5-6-7 
    unsigned char ngay:6;   //1-2-3-.........31
    unsigned char thang:4; 
    unsigned int  nam;    //00-1-2-3.......6
  }def_date;            //dinh nghia cau truc kieu moi ngay thang nam
//*******************************************************************
typedef   struct
  {   
    unsigned char status:1; //trang thai thiet bi dang bat hoac tat
      
    unsigned char giotat:5; 
    unsigned char phuttat:6; 
    unsigned char bithengiotat:1;
    unsigned char bihegitaad:1;
                                                                                  
    unsigned char giobat:5; 
    unsigned char phutbat:6; 
    unsigned char bithengiobat:1; 
    unsigned char bihegibaad:1;
    unsigned char sothutudat;
    unsigned char idthietbi;
  } def_catrbimothbi; //dinh nghia kieu moi cau truc bit mot thiet bi
//*******************************************************************
typedef union    // khai bao union cho de chep mang
  {
     def_catrbimothbi stru_thtimothbi;
     unsigned char    uni_mgbythbbi[sizeof(def_catrbimothbi)];
  } thtimothbi;   //khai bao kieu union thong tin 1 thiet bi tien cho 
                                          //viec sao chep sang eeprom
//*******************************************************************
typedef union
  {                                                                     
    struct
    {
      def_time    time;
      def_date    date;
    } stru_thoigian;
    unsigned char uni_thoigian[sizeof(def_time)+sizeof(def_date)]; 
  }thoigian;                     // khai bao kieu union cho thoi gian
 //#define   thoigian2time(x) 
//*******************************************************************
typedef enum  {dt1_4=0, oc_1_4, dtho, tip_1_4, tip1_1_3, nc5=5, dh2_5_3, tip2_1_3, oc1_1_3, dh3_5_2, tip1_1_2, nc11=11, oc1_1_2, tip1_1_1, \
			 dh2_4_1, dh1_4_1, tip2_1_2, quat_1_2, dh1_5_3, oc2_1_3, oc2_1_2, tip2_1_1, dnc, oc_1_1, nc24, dn_2_3, tip2_2_3, \
			 tip1_3_3, tip_4_3, oc1_3_3, oc2_3_3, tip2_3_3, oc_2_2, quat_2_2, tip1_2_2, ct_2, nc36, tip1_3_2, dn_2_2,tip2_2_2, dt2_4, \
			 quat_2_3, tip_2_4, oc_2_3, tip2_a, tip1_2_3, tip1_2_1, dh1_5_2, bnl_4_3, oc_4_2, bnl_4_2, tip3_3_2, tip_4_2, oc2_3_2, tip2_3_2, \
			 dh2_5_2, oc1_3_2, tip2_2_1, oc_2_1, tip1_a, oc_4_3, oc_a, tip_3_4, ct_1}; // thu tu that cua thiet bi
typedef enum  {belloff,bellon,bellerror,bellwarning,bellsucsesful,bellarlam} bell;
//*******************************************************************
typedef enum  phimchucnang{tat,bat,tangthoigian,giamthoigian,thoat,quaylai,ambao,khoa,datpass,tathet,mokhoa, \
              tang1,tang2,tang3,tang4}   ;
typedef enum  {timeout,notimeout};
typedef enum  {ljmp1,ljmp2,ljmp3,ljmp4,ljmp5,ljmp6};

typedef union {
unsigned int   ival;
        float  fval;
unsigned char  ch[2];
unsigned char  cval;
}val;
//
//#include <iodevice.h>
#define sizeeeprom   8192                   //kich thuoc eeprom
#define sothietbi    40                    //so thiet bi trong mang
#define sochip4094   (sothietbi/8+((sothietbi%8)!=0))                    //so thiet bi trong mang
#define kithmothbi  (sizeof(thtimothbi))    //kich thuoc byte 1 thiet bi
#define kiththbi    (sothietbi*(sizeof(thtimothbi)))  //kich thuoc byte tat ca thiet bi
#define kiththgi    (sizeof(thoigian))         //kich thuoc bien cau truc thoi gian
    // THIET LAP DIA CHI CAC BIEN VA DU LIEU TRONG EEPROM
#define adee_thietbi  0
#define adee_thietbin(i)(adee_thietbi + i*kithmothbi) 
#define adee_tatbat    (adee_thietbi+kiththbi)

#define adee_thoigian (adee_tatbat+sochip4094) 
#define adee_env(i)   (adee_thoigian+i*kithenv)
#define kithenv       (sizeof(jmp_buf))
#define adee_khac     (adee_thoigian+kiththgi)
   
  //DINH NGHIA CAC BIEN TOAN CUC, CAC BIEN CHO NHIEU HAM DUNG CHUNG
#ifdef  main__c
char idata lcd_buff[10]={0x1,0x02,0x03,0x04,0x05,0x06};
char idata buff1[]={0x0,0x1,0x02,0x03,0x04,0x05,0x06};
char idata  gio,phut,giay,thu,ngay,thang,cval1,cval2,phutmoi;
unsigned char ucval1,ucval2;
int    idata nam,ival1,ival2;
unsigned char idata tanghientai,maphim;
unsigned long idata lval1;

uchar    code  lcd_font[]={0x01,0x02,0x03,0x04,0x05,0x06} ;
thoigian idata timesys;
def_time idata tigo={22,1,22},tith={1,5,5} ;
def_date idata ting={2,22,1,1985};
jmp_buf  idata env,envtemp;

#else
extern char idata lcd_buff[10];
extern char idata buff1[];
extern char idata  gio,phut,giay,thu,ngay,thang,cval1,cval2,phutmoi;
extern unsigned char ucval1,ucval2;
extern int    idata nam,ival1,ival2;
extern unsigned char idata tanghientai,maphim;
extern unsigned long idata lval1;

extern uchar    code  lcd_font[6];
extern thoigian idata timesys;
extern def_time idata tigo,tith;
extern def_date idata ting;
extern jmp_buf  idata env,envtemp;

#endif

#endif