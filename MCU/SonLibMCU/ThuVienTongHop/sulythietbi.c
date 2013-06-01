#define  sulythietbi__c
#include  < sulythietbi.h>
#include  <allfuntion.h>
#include  < typedef.h>
#include  < 24c3264.h>
#include  <outputdevice.h>
#include  <sulymangbit.h>
#include <sulythoigian.h>
#include  <string.h>
#include  <stdio.h>
#include  <lcd.h>
char hthgtd;
void sulytudongthietbi(){
	unsigned char i,j,chang=0;
	timesys0=timesys;//copy thong tin thoi gian hien tai vao timesys0
	if(!(timesys0.time.phut%5 )){
		; //5 phut bat lcd 1 lan
		lcd_clr(lines);lcd_puts("Busy! Checking Auto On, Off, Arlam..v.v..");hienthithoigian(&timesys0);
		if((cousensorct==nosensor)&&((flagstatus&tattat_)||(timesys0.time.gio<=7)||(timesys0.time.gio>=23)))cousensorct=er(adee_cousen(0));
	}
	if(!cousensorct){//su ly hien thi coi bao dong
			lcd_clr(lines);
			lcd_puts("Ai Oi Nho Lay Cau Nay, Mot Dem An Trom Bang Nam Nam Cay.. ^_^ ^_^ ^_^ ");
		    bell=baodotnhap;
	}
flagstatus|=tattat_;	
for(i=0;i<sothietbi;i++){
    eeprom_reads(adee_thietbi(i),sizeof(thietbitemp0),&thietbitemp0);//luu thong tin 1 thiet bi vao mang thietbitemp de su ly
	if(thietbitemp0.status)flagstatus&=(~tattat_); //co kiem tra co phai tat ca cac thiet bi tat hay ko
    if(thoigianmoi&giomoi_){chang=1;setclearbit(out4094,i,thietbitemp0.status);}//update lai thong tin tat ca cac thiet bi
    if(((thietbitemp0.tudongtat)||(hengiotemp0.autooff))&&(!memcmp(&thietbitemp0.timetat,&timesys0.time,sizeof(timesys0.time)))){	//tu dong tat do bat bang dieu khien
    		chang=1;
			thietbitemp0.status=0;
			clearbit(out4094,i);
			if(thietbitemp0.ambaotat)bell=bellarlam;
		    if(!hthgtd){lcd_clr(lines);hthgtd=1;}
		    lcd_vsprintf("(%bu,%bu)T-",
		 	(uchar)(thietbitemp0.sothutudat/sothietbi1tang),(uchar)(thietbitemp0.sothutudat%sothietbi1tang));
	}  //check hen go tat do bat thiet bi bang dk hoac b
	if((!cousensorct)&&(thietbitemp0.batkembaodong)&&(!thietbitemp0.status)){//su ly tat bat thiet bi kem bao dong va hen gio tat sau khi bat
			thietbitemp0.status=1;
			setbit(out4094,i);
	 	    thietbitemp0.timetat=timesys0.time;//cai dat hen gio tat 
            congtrutime(&thietbitemp0.timetat,&mdtatbaodong,1);//
			chang=1; //bao cho ben duoi luu trang thai moi thiet bi
	}
    
	if(thietbitemp0.lockauto) continue;//thiet bi i khoa tu dong thi chuyen sang i+1
  
  for(j=0;j<solanhengio;j++){
     hengiotemp0=thietbitemp0.hengio[j];//luu thoi thong tin thoi gian hen gio vao bien thoi gian temp0
//   if(thoigianmoi&nammoi_)hengiotemp0.cacnam<<=1;//do cac nam o day la index tinh tu offset nam hien tai, 
     if(!hengiotemp0.kichhoat) continue; //chua kich hoat hen gio thi thoat ra kiem tra hen gio j+1  
 
     if(getbit((hengiotemp0.cacphut),battheophut)){if (!getbit(hengiotemp0.cacphut,timesys0.time.phut))continue;}
     if(getbit((hengiotemp0.cacgio),battheogio))  {if (!getbit(hengiotemp0.cacgio,timesys0.time.gio))continue;}
     if(getbit((hengiotemp0.cacthu),battheothu))  {if (!getbit(hengiotemp0.cacthu,date2thu(&timesys0.date)))continue;else goto checkthang;}
     if(getbit((hengiotemp0.cacngay),battheongay)){if (!getbit(hengiotemp0.cacngay,timesys0.date.ngay))continue;}
	 checkthang:
     if(getbit((hengiotemp0.cacthang),battheothang)){if (!getbit(hengiotemp0.cacthang,timesys0.date.thang))continue;} 
     if(getbit((hengiotemp0.cacnam),battheonam))    {if (!getbit(hengiotemp0.cacnam,timesys0.date.nam))continue;}
//   checkonoff:
     if(hengiotemp0.baobat&&(( hengiotemp0.battat &&(!thietbitemp0.status))||((!hengiotemp0.battat)&&thietbitemp0.status))) setbell(bellarlam);
	 chang=thietbitemp0.status;
     setclearbit(out4094,i,thietbitemp0.status=hengiotemp0.battat);
	 //hen gio tat neu la hen go bat
	 if((hengiotemp0.autooff)&&hengiotemp0.battat&&(!chang)){ //kiem tra tu dong tat khi hen gio bat theo gio mac dinh neu thiet bi dang bat thi thoi
	 	thietbitemp0.timetat=timesys.time; //dang bat san thi ko hen them gio tat
		if(hengiotemp0.tgtatdacbiet)congtrutime(&thietbitemp0.timetat,&thietbitemp0.ktimetatdacbiet,1);
        else congtrutime(&thietbitemp0.timetat,&thietbitemp0.mdktimetat,1);//timesys0
	 }
     if(!hthgtd){lcd_clr(lines);hthgtd=1;}
     lcd_vsprintf("[%bu,%bu]",(uchar)(thietbitemp0.sothutudat/sothietbi1tang),(uchar)(thietbitemp0.sothutudat%sothietbi1tang));
	 if(hengiotemp0.battat)lcd_puts("B-"); else lcd_puts("T-"); 
	 chang=1; 
	 //thietbitemp0.hengio[j]=hengiotemp0; thua
   } 														
  if(chang){eeprom_writes(adee_thietbi(i),sizeof(thietbitemp0),&thietbitemp0); chang=0;}//luu thong tin thiet bi da thay doi 
 }
  hthgtd=0;
  if(!cousensorct){cousensorct=er(adee_cousen(0));}	//khoi dong bo dem cho bo bao dong neu da check het
  clearthoigianmoi(phutmoi_|giomoi_|ngaymoi_|thangmoi_|nammoi_);
  //kiem tra xong tat ca cac thiet bi
  if(PCON&POF_){ //mat nguon thi restor trang thai moi thu can thiet
	  PCON&=(~POF_);
	  lcd_clr(lines);lcd_puts("Mat Dien. He Thong Da Tu Dong Cai Dat Cac Thong So Can Thiet");delay_ms(5000);
	  eeprom_reads(adee_out4094,sizeof(out4094),out4094);//restore trang thai thiet bi output vao eeprom co dia chi adee_tatbat
  }//ko mat nguon thi cackup he thong
  else {
	  eeprom_writes(adee_thoigian(0),sizeof(timesys),&timesys);// backup thoi gian he thong
	  eeprom_writes(adee_out4094,sizeof(out4094),out4094);//backup trang thai thiet bi
	  outputdevice(out4094);//xuat trang thai moi cua cac thiet bi ra ngoai
  }
}
void nhaythietbi(unsigned char stttb){
  unsigned char i,j=0,k=getbit(out4094,stttb);
  bell=lockbell;
  for (i=0;i<10;i++){
    j=!j;
    ring=j;
    setclearbit(out4094,stttb,j);
    outputdevice(out4094);
    delay_ms(200);
  }
 setclearbit(out4094,stttb,k);
 bell=offbell;

}
 