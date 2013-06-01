#ifndef __deftime__
#define __deftime__

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
// DINH NGHIA CAC MACRO TRUY CAP VAO CAU TRUC

#define   thoigiangio(poit)		((poit).time.gio)  
#define   thoigianphut(poit)	((poit).time.phut) 
#define   thoigiangiay(poit)	((poit).time.giay)
#define   thoigianngay(poit) 	((poit).date.ngay)
#define   thoigianthang(poit) 	((poit).date.thang)
#define   thoigiannam(poit) 	((poit).date.nam)

#define   setthoigian(poit,gio,phut,giay,ngay,thang,nam)\
          thoigiangio(poit)=gio;\
          thoigianphut(poit)=phut;\
          thoigiangiay(poit)=giay;\
          thoigianngay(poit)=ngay;\
          thoigianthang(poit)=thang;\
          thoigiannam(poit)=nam;
          
#define   timegio(poit)		((poit).gio)  
#define   timephut(poit) 	((poit).phut) 
#define   timegiay(poit)	((poit).giay)
#define   datengay(poit)	((poit).ngay)
#define   datethang(poit)	((poit).thang)
#define   datenam(poit)		((poit).nam)
          
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
#endif