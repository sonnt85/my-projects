#ifndef __typedef__
#define __typedef__
#include <setjmp.h>
#define  EDC_     0x02//dinh nghia EDC_ nghia la tang toc do clock len 2
#define  ghidich   //dung ghi dich
//*******************************************************************
typedef struct{        
	unsigned char gio; 
	unsigned char phut; 
	unsigned char giay;
}def_time;       //dinh nghia cau truc kieu thoi gian gio phut giay 
//*******************************************************************
typedef struct{ 
	//unsigned char thu:3;    //1(cn) 2-3-4-5-6-7 
	unsigned int  nam;    //00-1-2-3.......6
	unsigned char thang; 
	unsigned char ngay;   //1-2-3-.........31
}def_date;            //dinh nghia cau truc kieu moi ngay thang nam
//*******************************************************************
typedef struct{ 
	def_date    date;                                                                    
	def_time    time;
}thoigian;                     // khai bao kieu union cho thoi gian
 //#define   thoigian2time(x) 
//*******************************************************************
 
typedef struct {
	char     kichhoat:1;//ko kich hoat thi ko check
	char     baobat:1;
	char     baotat:1;
	char     battat:1;
	char     autooff:1; 
	char     tgtatdacbiet:1;
	
	
	char     cacgio[4]; 
	char     cacphut[8];
	char     cacnam[2];//  16 nam tu offset thua 0 bit
	char     cacthang[2];// 12/16 thang thua 4 bit
	char     cacngay[4];//   31/32 ngay thua 1 bit 
	char     cacthu[1]; //  7/8 thu su dung thua 1 bit           
}def_hengio;            //dinh nghia cau truc kieu moi ngay thang nam
#define     battheogio    (8*sizeof(hengiotemp.cacgio)-1)
#define     battheophut   (8*sizeof(hengiotemp.cacphut)-1)
#define     battheothu    (8*sizeof(hengiotemp.cacthu)-1)
#define     battheothang  (8*sizeof(hengiotemp.cacthang)-1)
#define     battheongay   (8*sizeof(hengiotemp.cacngay)-1)
#define     battheonam    (8*sizeof(hengiotemp.cacnam)-1)
#define     vitrikichhoat 7//ko kich hoat thi ko check
#define     vitribaobat   6
#define     vitribaotat   5
#define     vitribattat   4
#define	  	vitriautooff  3
#define	  	vitritgtatdacbiet  2
       
#define     vitrilockauto    7 //tat che do tu kiem tra gio tat bat
#define     vitribitagi      6//cho phep tang thoi gian tat thiet bi bang dieu khien
#define     vitribigigi      5//cho phep dung dieu khien giam thoi gian tat thiet bi
#define     vitristatus      4 //trang thai thiet bi dang bat hoac tat 
#define     vitribita        3//cho phep dung dieu khien de tat thiet bi
#define     vitribiba        2 //cho phep dung dieu khien bat thiet bi 
#define     vitritudongtat   1//kich hoat mac dinh tat khi bat thiet bi bang dieu khien
#define     vitrikihobake    0//kich hoat tinh nag bat kem thiet bi khac
#define     vitribatkembaodong 15
#define     vitriambaotat	   14
#define		vitricambatnhieu   13
//*****************
#define solanhengio   2  //chi 2 la du, mot lan cho bat va 1 lan cho tat
typedef   struct{  //01110110000   
	char          lockauto:1; //tat che do tu kiem tra gio tat bat		ok
	char 		  bitagi:1;//cho phep tang thoi gian tat thiet bi bang dieu khien	ok
	char          bigigi:1;//cho phep dung dieu khien giam thoi gian tat thiet bi	ok
	char          status:1; //trang thai thiet bi dang bat hoac tat    ok
	char 		  bita:1;//cho phep dung dieu khien de tat thiet bi	   ok
	char 		  biba:1; //cho phep dung dieu khien bat thiet bi 	   ok
	char          tudongtat:1;//kich hoat mac dinh tat khi bat thiet bi bang dieu khien	ok
	char          kihobake:1;//kich hoat tinh nag bat kem thiet bi khac	  ok
	
	char 		  batkembaodong:1;	
	char		  ambaotat:1;
	char		  cambatnhieu:1;	  
	
	unsigned char sothutudat;//la dia chi o nho trong mang chua stt 	ok		idthiet bi toa do tinh bang (tang,stttbtrong tang)
	unsigned char bksothutudat;
	unsigned char sttbatkem;//so thu tu thiet bi bat kem thiet bi nay	ok
	unsigned int  couton;//dem so lan dung dieu khien bat thiet bi		ok
	
	def_time      timetat; //bien luu thoi gian tat    
	def_time      nactime;//khoang thoi gian khi moi lan bam tang gaim	 ok
	def_time      mdktimetat,ktimetatdacbiet; //khoang thoi gian mac dinh tu tat thiet bi	ok
	def_hengio    hengio[solanhengio];//hen gio[0]1 la mac dinh khi dieu khien tat ban can thiep vao
    								//  ok
}thtimothbi; //dinh nghia kieu moi cau truc bit mot thiet bi
//#define timetat   hengio[0] // hengio0 dung cho hen gio tat thiet bi
#define timebat   hengio[1] // hengio1 dung cho hen gio bat thiet bi

//*******************************************************************
typedef enum  caudao{dt1_4=0, oc_1_4, dtho, tip_1_4, tip1_1_3, nc5=5, dh2_5_3, tip2_1_3, oc1_1_3, dh3_5_2, tip1_1_2, nc11=11, oc1_1_2, tip1_1_1, \
			 dh2_4_1, dh1_4_1, tip2_1_2, quat_1_2, dh1_5_3, oc2_1_3, oc2_1_2, tip2_1_1, dnc, oc_1_1, nc24, dn_2_3, tip2_2_3, \
			 tip1_3_3, tip_4_3, oc1_3_3, oc2_3_3, tip2_3_3, oc_2_2, quat_2_2, tip1_2_2, ct_2, nc36, tip1_3_2, dn_2_2,tip2_2_2, dt2_4, \
			 quat_2_3, tip_2_4, oc_2_3, tip2_a, tip1_2_3, tip1_2_1, dh1_5_2, bnl_4_3, oc_4_2, bnl_4_2, tip3_3_2, tip_4_2, oc2_3_2, tip2_3_2, \
			 dh2_5_2, oc1_3_2, tip2_2_1, oc_2_1, tip1_a, oc_4_3, oc_a, tip_3_4, ct_1}; // thu tu that cua thiet bi
typedef enum   godongda{mohan,maybom,maygiat,tivi,binhnonglanh,densau,tuyp3,tuyp1,chuadung1,chuadung2,dieuhoa,tuyp4,tuyp2,\
				gacxep,com,beptu,sensorc1,sensorb2}; // thu tu that cua thiet bi

typedef enum  {offbell=0,binhthuong,bellonoff,bellspace,bellerror,bellwarning,bellsucsesful,bellarlam,lockbell,baodotnhap,diir_=0x80};
//*******************************************************************
typedef enum  PHIMCHUCNANG{tang0=0,tang1=1,tang2=2,tang3=3,ambao=10,tat=25,hienthoigian=12,admin=11,bat=19,giamthoigian=21,prev=21,\
ok=22,tangthoigian=23,next=23, menu=24,thoat=26,setupthietbi=18,khongchon=24,thoatlap=128,tathetthietbi=20,battatbaodong=13,,mokhoa=27,swchanel2=28,checkonoff=10,bbreak=27,khoa,datpass,checkeep=13}   ;
typedef enum  {notimeout=0,nosensor=1};
typedef enum  {ljmp0,ljmp1,ljmp2,ljmp3,ljmp4,ljmp5};

typedef enum  {sothutudat_,tudongtat_,recou_,lockauto_,bitagi_,bigigi_,\
               status_,bita_,biba_,nactime_,mdktimetat_,hengio_,kihobake_,sttbatkem_,batkembaodong_,ambaotat_,kichhoat_,\
			   baobat_,baotat_,battat_,battheophut_,battheogio_,battheothu_,battheongay_,battheothang_,battheonam_,autooff_,\
			   cambatnhieu_,ktimetatdacbiet_,tgtatdacbiet_,setup1thietbi_,chonlai_}; //31
typedef union {
unsigned int   ival;
        float  fval;
unsigned char  ch[2];
unsigned char  cval;
}val;
//
//#include <iodevice.h>
#define sizeeeprom            8192                   //kich thuoc eeprom
#define sobienthoigian        1
#define soenv                 8                       //so bien ljmp luu trong eeprom
#define sothietbi             32                      //so thiet bi trong mang
#define sochip4094            (sothietbi/8+((sothietbi%8)!=0))                    //so thiet bi trong mang
#define sochar                10    
#define solong                10    
#define soint                 10   
#define sokhoidong            1
#define sosenser			  2
#if sothietbi<20
#define sothietbi1tang       sothietbi
#else 
#define sothietbi1tang  20
#endif
#define sotang       (sothietbi/sothietbi1tang+((sothietbi%sothietbi1tang)!=0)) 
#define sopass      5     //moi pass gom 2 byte
//====================================================

    // THIET LAP DIA CHI CAC BIEN VA DU LIEU TRONG EEPROM
#define adee_start        0

#define adee_cousen(i)	  (adee_start+i)

#define adee_pass(i)      (adee_cousen(sosenser)+2*i)

#define adee_khoidong(i)  (adee_pass(sopass)+i*4)//16 lua chon cho khoi dong

#define adee_thietbi(i)   (adee_khoidong(sokhoidong) + (i)*(sizeof(thtimothbi))) 

#define adee_out4094      (adee_thietbi(sothietbi))

#define adee_thoigian(i)  (adee_out4094+sochip4094+(i)*(sizeof(thoigian))) 

#define adee_env(i)       (adee_thoigian(sobienthoigian)+(i)*(sizeof(jmp_buf)+1))//them 1 la bien dem

#define adee_char(i)      (adee_env(soenv)+i*(sizeof(char)))

#define adee_int(i)       (adee_char(sochar)+(sizeof(int))*(i))

#define adee_long(i)      (adee_int(soint)+(sizeof(long))*(i))

#define adee_stttbdangdungtang(i) (adee_long(solong)+(i))       //noi dung indextang chinh la stt trong mang ao cua tung tang
                                                       //i chinh la noi dung cua adee_tang hien tai 

#define adee_tangthietbi(sttt,stttb)     (adee_stttbdangdungtang(sotang)+sothietbi1tang*sttt+stttb)

#define adee_khac(i)      (adee_tangthietbi(sotang,sothietbi1tang))
//cai dat cac hang so thoi gian
#if modex2==2
  #define delaytime2us      25000     //khoang thoi gian tran cho time 2 autoload 50ms
  #define cou1min (2000L)      //mac dinh chon 1000
#else
  #define delaytime2us      50000     //khoang thoi gian tran cho time 2 autoload 50ms
  #define cou1min (1000L)      //mac dinh chon 1000
#endif

#define unittioutms_g         5000       //khoang thoi gian check dinh ky time out moi thu 5s
#define unittioutms(i)       ((i)/(delaytime2us/1000))//i thuong chon bang  unittioutms_g
#define tioums(ms)           (-(ms)/unittioutms_g)          
#define ndelaytime2usms(ms)  ((ms)/(delaytime2us/1000))

// DINH NGHIA CAC MACRO TRUY CAP VAO CAU TRUC

#define   thoigiangio(poit) ((poit).time.gio)  
#define   thoigianphut(poit) ((poit).time.phut) 
#define   thoigiangiay(poit) ((poit).time.giay)
#define   thoigianngay(poit) ((poit).date.ngay)
#define   thoigianthang(poit) ((poit).date.thang)
#define   thoigiannam(poit) ((poit).date.nam)

#define   setthoigian(poit,gio,phut,giay,ngay,thang,nam) \
          thoigiangio(poit)=gio;\
          thoigianphut(poit)=phut;\
          thoigiangiay(poit)=giay;\
          thoigianngay(poit)=ngay;\
          thoigianthang(poit)=thang;\
          thoigiannam(poit)=nam;
          
#define   timegio(poit) ((poit).gio)  
#define   timephut(poit) ((poit).phut) 
#define   timegiay(poit) ((poit).giay)
#define   datengay(poit) ((poit).ngay)
#define   datethang(poit) ((poit).thang)
#define   datenam(poit) ((poit).nam)
          
#define   getthoigian(poit,gio,phut,giay,ngay,thang,nam) \
          gio=thoigiangio(poit);\
          phut=thoigianphut(poit);\
          giay=thoigiangiay(poit);\
          ngay=thoigianngay(poit);\
          thang=thoigianthang(poit);\
          nam=thoigiannam(poit);
          
#define   gettime(poit,gio,phut,giay) \
          gio=timegio(poit);\
          phut=timephut(poit);\
          giay=timegiay(poit);
          
#define   settime(poit,gio,phut,giay) \
          timegio(poit)=gio;\
          timephut(poit)=phut;\
          timegiay(poit)=giay;

#define   getdate(poit,ngay,thang,nam) \
          ngay=datengay(poit);\
          thang=datethang(poit);\
          nam=datenam(poit);
          
#define   setdate(poit,ngay,thang,nam) \
          datengay(poit)=ngay;\
          datethang(poit)=thang;\
          datenam(poit)=nam; 
        /////////////////////////////////////////////
   
  //DINH NGHIA CAC BIEN TOAN CUC, CAC BIEN CHO NHIEU HAM DUNG CHUNG
#ifdef  main__c
	char  lcd_buff[41]={0x1,0x02,0x03,0x04,0x05,0x06};
	//unsigned char idata buff1[]={0x0,0x1,0x02,0x03,0x04,0x05,0x06};
	unsigned char code *txtthanhcong="  Du Lieu Cap Nhat\n.....Thanh Cong.....";
	unsigned char idata  out4094[sochip4094];
	unsigned char   cval1,phutmoi=0,*poichar;
	unsigned char   ucval1,ucval2,cousensorct;
	unsigned int     ival1,ival2,timeout,timeout1,pass16,*poiint;
	unsigned int idata  demphut;
	unsigned char  tanghientai,maphim,chisothietbi;
	unsigned long pass32;
	//unsigned long idata lval1;
	void *poivoid;
	
	uchar    code  lcd_font[]={0x01,0x02,0x03,0x04,0x05,0x06} ;
	char code trongsoset[8]={ 1, 2, 4, 8, 16, 32, 64, 128}   ; //dung trong set bit phep or
	char code trongsoclear[8]={ ~1, ~2, ~4, ~8, ~16, ~32, ~64, ~128}   ; //dung trong set bit phep or
	
	thoigian  timesys,timesys0;
	//def_time idata tigo={22,1,22},tith={1,5,5} ;
	//def_date idata ting={2,22,1,1985};
	thtimothbi     thietbitemp,thietbitemp0; 
	def_hengio     hengiotemp,hengiotemp0;
	def_time	   code   mdtatbaodong={0,5,0};
	def_time	   temptime;
	//(thietbitemp code *) 0;

#else
	extern  char  lcd_buff[41];
	//extern unsigned char idata buff1[];
	extern unsigned char code *txtthanhcong;
	extern unsigned char  idata out4094[sochip4094];
	extern unsigned char   cval1,phutmoi,*poichar;
	extern unsigned char ucval1,ucval2,cousensorct;
	extern unsigned int  ival1,ival2,timeout,timeout1,pass16,*poiint;
	extern unsigned int idata demphut;
	
	extern unsigned char  tanghientai,maphim,chisothietbi;
	extern	unsigned long pass32;
	//extern unsigned long idata lval1;
	extern void *poivoid;
	extern	uchar	code 	lcd_font[6];
	extern  char	code 	trongsoset[8] ; //dung trong set bit phep or
	extern  char	code 	trongsoclear[8] ; //dung trong set bit phep or
	
	extern	thoigian		timesys,timesys0;
	//extern def_time idata tigo,tith;
	//extern def_date idata ting;
	extern thtimothbi     	thietbitemp,thietbitemp0; 
	extern def_hengio     	hengiotemp,hengiotemp0;
	extern def_time code	mdtatbaodong;
	extern def_time			temptime;

#endif

#endif