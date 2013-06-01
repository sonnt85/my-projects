
//#include <stdlib.h>  //ham nay da kiem tra, rat chuan
#include  <allfuntion.h>
#include  <typedef.h >

#include <sulythoigian.h>
unsigned char code songaytrongthang[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //so ngay trong thang cua nhung nam binh thuong
void nhichkim(thoigian *poithoi)                      
{
#define   poigiay   (poithoi->stru_thoigian.time.giay)
#define   poiphut   (poithoi->stru_thoigian.time.phut)
#define   poigio    (poithoi->stru_thoigian.time.gio)

#define   poithu    (poithoi->stru_thoigian.date.thu)
#define   poingay   (poithoi->stru_thoigian.date.ngay)
#define   poithang  (poithoi->stru_thoigian.date.thang)
#define   poinam    (poithoi->stru_thoigian.date.nam)
		unsigned int  vartam=0;
    signed long   templ;
    bit flag=0;
 		unsigned char ngaymaxtrongthang;
    #define   vartam1  ngaymaxtrongthang
    poigiay=0; //ko xet den giay
		poiphut++;
		   if(poiphut==60)
				{poiphut=0;poigio++;
					if(poigio==24)
					{
						poigio=0;
						poingay++;
            
            flag=((poithang==2)&&((((poinam)%400)==0)||((((poinam)%4)==0)&&((poinam)%100!=0))));
						if(flag){ngaymaxtrongthang=29;}else {ngaymaxtrongthang=songaytrongthang[poithang-1];}
						if(poingay>ngaymaxtrongthang)
						 {
						 	poingay=1;
						  poithang++;
							if(poithang==13)
							  {
                   poinam++;
						       poithang=1;
							  }
						 }
             //thinh thu
             vartam=0;
            for(vartam1=0;vartam1<(poithang-1);vartam1++){vartam=vartam+songaytrongthang[vartam1];}
            if(flag){vartam++;};
            templ=poinam-1;
            poithu=(templ + templ/4 - templ/100 + templ/400 + poingay+vartam)%7+1  ;										
					}
				}
}

void  congtrutime(def_time *poitime,def_time *poitimethem, char dauconggio)   

      //cong hoac tru  (c0nggio=1 la cong conggio=-1 la tru) them thoi gian tro boi *poitimethem vaothoi gian tro boi poitime
	{	  //oke datest
#undef  poigiay
#undef  poiphut
#undef  poigio
#define poigiay (poitime->giay)
#define poiphut (poitime->phut)
#define poigio (poitime->gio)

#define poigiaythem (poitimethem->giay)
#define poiphutthem (poitimethem->phut)
#define poigiothem (poitimethem->gio)
      long temp;
      temp=(long)poigiay+60*(long)poiphut+(long)60*60*poigio+
      (long)dauconggio*((long)poigiaythem+60*(long)poiphutthem+60*60*(long)poigiothem);
      if(temp<0)temp=temp+(long)24*60*60;
 
      poigiay=temp%60;
      temp=temp/60;
  
      poiphut=temp%60;

      poigio=(temp/60)%24;     
	}