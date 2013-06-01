#ifndef __sulythoigian__
#define __sulythoigian__

#ifndef sulythoigian__c
	extern unsigned char data gio,phut,giay,thu,ngay,thang,thoigianmoi;
	extern unsigned int  nam;
#else
	#include	<deftime.h >
	#define 	cnhapgiolcd
#endif

enum	{phutmoi_=0x01,giomoi_=0x02,ngaymoi_=0x04,thangmoi_=0x08,nammoi_=0x10};
unsigned char	nhichkim(thoigian *poithoi); //tra luon thu hien tai
unsigned char	date2thu(def_date *valdate);
unsigned char	getthoigianmoi();//ham nay tra ve da co nam moi troi qua
void 	clearthoigianmoi(unsigned char var);
void	congtrutime(def_time *poitime,def_time *poitimethem, char dauconggio)   ;
void	setthoigianugetkey(unsigned int (*f)(unsigned int ,unsigned int,unsigned char ),thoigian *trothoi);
void	settimeugetkey(unsigned int (*f)(unsigned int ,unsigned int ,unsigned char),def_time   *poitime);
void	hienthithoigian(thoigian *trothoi);
#endif