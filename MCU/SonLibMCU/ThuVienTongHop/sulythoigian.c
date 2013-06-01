#define   sulythoigian__c
//#include <stdlib.h>  //ham nay da kiem tra, rat chuan
#include	<sulythoigian.h>
unsigned char code	songaytrongthang[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //so ngay trong thang cua nhung nam binh thuong
unsigned char data  gio,phut,giay,thu,ngay,thang,thoigianmoi=0;
unsigned int  nam;

unsigned char nhichkim(thoigian *poithoi){
	unsigned 	int		vartam=0;
	long    			templ;
	unsigned 	char	flag=0;
	unsigned 	char	ngaymaxtrongthang;

	#define		p(x)	(poithoi->time.x)    
	#define   	pd(x)	(poithoi->date.x)	
	#define   vartam1  ngaymaxtrongthang

	p(giay)=0; //ko xet den giay
	giay=0;
	if((pd(thang)>12)||(pd(thang)==0))pd(thang)=1;
	if((pd(ngay)>31)||(pd(ngay)==0))pd(ngay)=1;
	if(p(gio)>23)p(gio)=0;
	if(p(phut)>59)p(phut)=0;
	if(pd(nam)<2011)pd(nam)=2011;
	
	flag=((pd(thang)==2)&&((((pd(nam))%400)==0)||((((pd(nam))%4)==0)&&(((pd(nam))%100)!=0))));
	thoigianmoi|=phutmoi_;
	if((++p(phut))==60){
		p(phut)=0;
		thoigianmoi|=giomoi_;
		if((++p(gio))==24){
			p(gio)=0;
			thoigianmoi|=ngaymoi_;
			if(flag){ngaymaxtrongthang=29;}else {ngaymaxtrongthang=songaytrongthang[pd(thang)-1];}
			if((++pd(ngay))>ngaymaxtrongthang){
				pd(ngay)=1;
				thoigianmoi|=thangmoi_;
				if((++pd(thang)==13)){
					pd(thang)=1;
					pd(nam)++;
					thoigianmoi|=nammoi_;	
				}
			}
		}
	}
	vartam=0;
	for(vartam1=0;vartam1<(pd(thang)-1);vartam1++){vartam=vartam+songaytrongthang[vartam1];}
	if(flag){vartam++;};
	templ=pd(nam)-1;
	return((templ + templ/4 - templ/100 + templ/400 + p(gio)+vartam)%7+1  );
}

void clearthoigianmoi(unsigned char var){
	thoigianmoi&=(~var);
}
unsigned char date2thu(def_date *valdate){
	unsigned char i;
	unsigned int  vartam=0;
	unsigned long templ;
	
	for(i=0;i<(valdate->thang-1);i++){vartam+=songaytrongthang[i];};
	i=((valdate->thang==2)&&((((valdate->nam)%400)==0)||((((valdate->nam)%4)==0)&&(((valdate->nam)%100)!=0))));
	vartam+=i;
	templ=valdate->nam-1;
	return((templ + templ/4 - templ/100 + templ/400 + valdate->ngay+vartam)%7+1)  ;										
}

void  congtrutime(def_time *poitime,def_time *poitimethem, char dauconggio){	
	//cong hoac tru  (c0nggio=1 la cong conggio=-1 la tru) them thoi gian tro boi *poitimethem vaothoi gian tro boi poitime
	//oke datest
	long temp;
	temp=(long)poitime->giay+60*poitime->phut+(long)60*60*poitime->gio+
	dauconggio*((long)poitimethem->giay+60*poitimethem->phut+(long)60*60*poitimethem->gio);
	if(temp<0)temp=temp+(long)24*60*60;//cong them 1 ngay cho duong kim van o vi tri do
	poitime->giay=temp%60;
	temp=temp/60;
	poitime->phut=temp%60;
	poitime->gio=(temp/60)%24;     
}
#ifdef nhapgiolcd
	#include <lcd.h> 
	void setthoigianugetkey(unsigned int (*f)(unsigned int ,unsigned int,unsigned char ),thoigian *trothoi){ 
		//unsigned int (*ftemp)(unsigned int ,unsigned int,unsigned char )=f;
		demphut=0;
		lcd_clr(lines);
		lcd_puts("Nhap Gio:");  
		trothoi->time.gio=f(0,23,phimtm_|minmax_);demphut=0;
		
		//--------------------------------------   
		lcd_clr(lines);
		lcd_puts("Nhap Phut:");  
		trothoi->time.phut=f(0,59,phimtm_|minmax_);; //ham tro toi phut co van de ,tai sao lai vay??????????????????????????
		
		//-------------------------------   
		lcd_clr(lines);
		lcd_puts("Nhap Ngay:");  
		trothoi->date.ngay=f(1,31,phimtm_|minmax_);demphut=0;
		//-------------------------------   
		lcd_clr(lines);
		lcd_puts("Nhap Thang:");  
		(*trothoi).date.thang=f(1,12,phimtm_|minmax_);demphut=0;
		
		//-------------------------------   
		lcd_clr(lines);
		lcd_puts("Nhap Nam:");  
		trothoi->date.nam=f(1985,2201,phimtm_|minmax_);demphut=0;
		eeprom_writes(adee_thoigian(0),sizeof(timesys),&timesys);//backup thoi gian he thong ham nay de phong neu chuong trinh goi ham nay nhap 
		demphut=0;
		giay=0;
	}
	
	void settimeugetkey(unsigned int (*f)(unsigned int ,unsigned int,unsigned char ),def_time   *poitime){
	    lcd_clr(lines);
	    lcd_puts("Nhap Gio:");  
	    poitime->gio=f(0,23,phimtm_|minmax_);
	  
	//-------------------------------   
	    lcd_clr(lines);
	    lcd_puts("Nhap Phut:");  
	    poitime->phut=f(0,59,phimtm_|minmax_);
	    lcd_clr(lines);
	    lcd_puts(txtthanhcong); 
	}
	
	void hienthithoigian(thoigian *trothoi){ 
		getthoigian(*trothoi,gio,phut,giay,ngay,thang,nam);
		sprintf(lcd_buff,"T%bu-%02bu:%02bu",date2thu(&(trothoi->date)),(uchar)gio,(uchar)phut);
		lcd_putsxy(lcd_buff,nuli-strlen(lcd_buff),lines-2);
		sprintf(lcd_buff,"%bu/%bu/%4u",(uchar)ngay,(uchar)thang,(uint)nam);
		lcd_putsxy(lcd_buff,nuli-strlen(lcd_buff),lines-1);
	}
#endif