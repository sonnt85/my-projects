#define   caidatthietbi__c
#include  <caidatthietbi.h >
#include  <typedef.h>
#include <allfuntion.h>
 code char code   *huongdanonoffbit="Dung OK,Bat,Tat Huy";//2 dong
 code char code   *huongdantanggiam="Dung OK,Tang,Giam";//2 dong

void caidatthietbi(unsigned long codecai,char thietbicai){
unsigned char i,j;
if(!codecai)return;//cai lai het tat ca ve mac dinh
for (i=0;i<sothietbi;i++){//su ly thiet bi thong qua thietbiFtemp0 roi ghi vao eeprom ung voi thiet bi do
if(getbit(&codecai,setup1thietbi_))i=thietbicai;
eeprom_reads(adee_thietbi(i),sizeof(thietbitemp),&thietbitemp);//luu thong tin thiet bi vua cai dat
if(getbit(&codecai,kihobake_))thietbitemp.kihobake=0;
if(getbit(&codecai,sttbatkem_))thietbitemp.sttbatkem=0;
if(getbit(&codecai,recou_))thietbitemp.couton=0;//reset bo dem neu co lenh
if(getbit(&codecai,status_))thietbitemp.status=0; //trang thai thiet bi dang bat hoac tat 
if(getbit(&codecai,bitagi_))thietbitemp.bitagi=1;//cho phet tang thoi gian hen gio tat
if(getbit(&codecai,bigigi_))thietbitemp.bigigi=1;//cho phep giam thoi gian hen gio tat
if(getbit(&codecai,ktimetatdacbiet_))settime(thietbitemp.ktimetatdacbiet,0,5,0); //thoi gian tat dac biet la 5phut
if(getbit(&codecai,bita_))thietbitemp.bita=1;// cho phep su dung dieu khien tat thiet bi
if(getbit(&codecai,biba_))thietbitemp.biba=1; //cho phep dung dieu khien bat thiet bi 
if(getbit(&codecai,lockauto_))thietbitemp.lockauto=0;// cho phep tu tat bat thiet bi
if(getbit(&codecai,nactime_))settime(thietbitemp.nactime,0,5,0);//mac dinh moi nac thoi gian la 5 phut
if(getbit(&codecai,tudongtat_))thietbitemp.tudongtat=1;
if(getbit(&codecai,mdktimetat_))settime(thietbitemp.mdktimetat,2,0,0);
if(getbit(&codecai,batkembaodong_))thietbitemp.batkembaodong=0;
if(getbit(&codecai,ambaotat_))thietbitemp.ambaotat=0;  
if(getbit(&codecai,cambatnhieu_))thietbitemp.cambatnhieu=0;    
if(getbit(&codecai,sothutudat_)) {
      thietbitemp.sothutudat=i;// ANH XA DAT DE CHO DE NHO CHI DUNG DUY NHAT 1 LAN DAU
      eeprom_write((adee_tangthietbi(0,0)+i),i);// cac gia tri trong con tro mang tro dung thu tu
      }
if(getbit(&codecai,hengio_))
      for(j=0;j<solanhengio;j++){// dung hengiotemp su ly hen gio roi ghi lai vao thiet bi do ko fai con tro(toc do cao)
		hengiotemp= thietbitemp.hengio[j];
		if(getbit(&codecai,kichhoat_))hengiotemp.kichhoat=1;	//mac dinh cho phep hen gio nhung chua hen
		if(getbit(&codecai,battat_)){
			if(j)hengiotemp.battat=1;else hengiotemp.battat=0; // 0 la tat 1 la bat
			if(getbit(&codecai,autooff_))hengiotemp.autooff=1; //mac dinh cho tu dong tat
		}
		if(getbit(&codecai,battheophut_)){
			memset(hengiotemp.cacphut,0,sizeof(hengiotemp.cacphut));
			setbit((hengiotemp.cacphut),battheophut) ;	//cho bat theo put
		}
		if(getbit(&codecai,battheogio_)){
			memset(hengiotemp.cacgio,0,sizeof(hengiotemp.cacgio));
			setbit((hengiotemp.cacgio),battheogio) ; //bat theo gio
		}
		if(getbit(&codecai,battheothu_)){
			memset(hengiotemp.cacthu,0,sizeof(hengiotemp.cacthu));
			clearbit((hengiotemp.cacthu),battheothu) ;	//ko bat theo thu
		}
		if(getbit(&codecai,battheongay_)){
			memset(hengiotemp.cacngay,0,sizeof(hengiotemp.cacngay));
			clearbit((hengiotemp.cacngay),battheongay) ;//ko bat theo ngay
		}
		if(getbit(&codecai,battheothang_)){
			memset(hengiotemp.cacthang,0,sizeof(hengiotemp.cacthang));
			clearbit((hengiotemp.cacthang),battheothang); //khong bat theo thang
		}

		if(getbit(&codecai,tgtatdacbiet_)){
			setbit(&hengiotemp,vitritgtatdacbiet) ; //mac dinh bat time dac biet	 5 phut
	    }	 

		if(getbit(&codecai,battheonam_)){
			memset(hengiotemp.cacnam,0,sizeof(hengiotemp.cacnam));
			clearbit((hengiotemp.cacnam),battheonam) ;	   //ko bat theo nam
		}
		if(getbit(&codecai,baobat_))hengiotemp.baobat=0;//ko do chuong khi tu bat
		if(getbit(&codecai,baotat_))hengiotemp.baotat=0;//ko do chuong khi tat
		thietbitemp.hengio[j]=hengiotemp;//ghi nguoc thong tin lai vi hengiotemp ko fai la con tro
     } 
   setclearbit(out4094,i,thietbitemp.status);
   eeprom_writes(adee_thietbi(i),sizeof(thietbitemp),&thietbitemp);//luu thong tin thiet bi vua cai dat
   if(getbit(&codecai,setup1thietbi_))i=sothietbi-1;//thoat ngay khi cai song thiet bi can cai

}

}

unsigned char inputstttb(){
    unsigned char sodat1,id1,temp;
    lcd_clr(lines);
    lcd_puts("Chon Tang: ");
    id1=(getkeyab(tang0,tang0+sotang-1,phimtm_|minmax_))-tang0;

	if(id1==(sotang-1)){temp=sothietbi-sothietbi1tang*(sotang-1);}else temp=sothietbi1tang; 

	lcd_putchar('\n');
	lcd_puts("Chon TTTB: ");
    sodat1=getkeyab(0,temp-1,phimtm_|minmax_);//so dat 1 chua sthu tu trong tang maphim =id1
    
    sodat1=sothietbi1tang*id1+sodat1;//sodat1=&id1 // so dat 1 chua dia chi con tro tro toi thiet bi, chinh la gia tri &id1
    id1=eeprom_read(adee_tangthietbi(0,0)+sodat1);//id1=&sodat1
    return id1;
}

unsigned char inputincdec(int *var, int max ){//bam ok ham thoat da chon var tra lai ofset
    char tempchar,temp1=0,temp2=max-*var,vtlcd=lcd_wait();//temp2 chua gia tri max cua tem1 hay 
   while(1){		//*var!=0 thi loi
       lcd_goto(vtlcd);
       lcd_vsprintf("%-4u",(int)*var);//in gia tri hien tai bien 
	   tempchar=ir_getkeytimeout(binhthuong,0);
	   if(tempchar==next){ ++temp1 ;if( ++(*var)>max){(*var)=max-temp2;temp1=0;}}
	   else if(tempchar==prev){--temp1;if(--(*var)<(max-temp2)){(*var)=max;temp1=temp2;}} 
	   else if(tempchar==ok) return temp1; 
	   else if(tempchar==khongchon) return thoatlap; 
	   else bell=offbell;
   }
}

unsigned char inputonoffbit(void *mang,unsigned char vitri ){	  // tra lai gia tri cai dat cho bit	
    unsigned char maphim,vtlcd=lcd_wait(),tempbit=getbit(mang,vitri); 
	while(1) {  
	     lcd_goto(vtlcd);
	     lcd_vsprintf("%bu",(uchar)getbit(mang,vitri)); //in bit vua nhap 0 hoac 1
	     maphim=ir_getkeytimeout(binhthuong,ljmp0);
	     if(maphim==bat)     {setbit(mang,vitri);}  
	     else if(maphim==tat){clearbit(mang,vitri);}
	     else if(maphim==ok) return getbit(mang,vitri);
	     else if(maphim==khongchon){ setclearbit(mang,vitri,tempbit);return thoatlap; }
		 else bell=offbell;
     }
}
//((void (code *) (void)) 0x0000) ();
//con tro dat code-tro toi cac fan tu off mag xau
code char code *datadis[]=        {" Nam",     " Thang",    " Ngay",     " Thu",     " Gio",     " Phut" } ;
unsigned char code addmang[]={&(hengiotemp.cacnam)-&hengiotemp,&(hengiotemp.cacthang)-&hengiotemp,
                          &(hengiotemp.cacngay)-&hengiotemp,&(hengiotemp.cacthu)-&hengiotemp,
						  &(hengiotemp.cacgio)-&hengiotemp,&(hengiotemp.cacphut)-&hengiotemp};

unsigned char code vitribitkichhoat[]={battheonam,battheothang,battheongay,battheothu,battheogio,battheophut}	  ;
unsigned char code minnhap[]=         { 0,1 ,1 ,1,0 ,0}	  ;
unsigned char code maxnhap[]=         {15,11,30,6,23,59}	  ;//offset

void caidathengio(void *mangg){					//i la chi so mang text
    int valdoi;
	unsigned char i,temp1;
	unsigned char *mang;
	for(i=0;i<sizeof(minnhap);i++){
		mang=(unsigned char *)mangg+addmang[i];	
	    lcd_clr(lines);
	    lcd_puts("Cai Dat ");
		if(getbit(mangg,vitribattat)) lcd_puts("Bat");else lcd_puts("Tat");;//lu vi tri sau ky tu tat theo nam
	    lcd_puts(" Theo");lcd_puts(datadis[i]);//lu vi tri sau ky tu tat theo nam
		if(!checkhome())lcd_putchar(' ');
		temp1=lcd_wait();
		lcd_putchar('\n');
	    lcd_puts(huongdanonoffbit); //in huong dan dung phim tat bat bit
		lcd_goto(temp1);
		//toi day ok
	    if(inputonoffbit(mang,vitribitkichhoat[i])){
			while(1){
			    if(!i)valdoi=timesys.date.nam;else valdoi=minnhap[i]; 
				lcd_clr(lines);//xoa man
				lcd_gotoxy(0,1);
				lcd_puts(huongdantanggiam); //1 dong
				lcd_putsxy("Nhap",0,0);lcd_puts(datadis[i]);
				if(getbit(mangg,vitribattat)) lcd_puts(" Bat ");else lcd_puts(" Tat ");//lu vi tri sau ky tu tat theo nam
				if((temp1=inputincdec(&valdoi,valdoi+maxnhap[i]+1))==thoatlap)break;
				else if(temp1==maxnhap[i]+1){
					   lcd_clr(lines);
					   lcd_puts("Da Xoa Tat Ca");lcd_puts(datadis[i]); lcd_puts(" Hen. Nhan Phim Bat Ky De Tiep Tuc");
					
					   for(temp1=minnhap[i];temp1<=(minnhap[i]+maxnhap[i]);temp1++){//chuan da check
					   clearbit(mang,temp1);
					   }
					   waitsig(delay_);
					   continue;
					 }
				temp1+=minnhap[i]; 
				lcd_clr(2);
				lcd_clr(3);
				lcd_clr(1);//xoa man
				lcd_puts(huongdanonoffbit);//2 dong
				lcd_puts(" De Cai Dat Cho Gia Tri Tren ");
				if(inputonoffbit(mang,temp1)==thoatlap) break;	  //truyen ham
            }
	    }
	}
}
void caidattungthietbi(){
unsigned char i,tempchar,id1,temvitricai;
enum {lockauto_i,bitagi_i,bigigi_i,bita_i,biba_i,tudongtat_i,couton_i,nactime_i,mdktimetat_i,ktimetatdacbiet_i,tgtatdacbiet_i,thutugoc_,\
kihobake_i ,sttbatkem_i,hengiotat_i,hengiobat_i,batkembaodong_i,ambaotat_i,cambatnhieu_i,thoatcaidat_i,quaylaitruocdo_i};

code unsigned char code *txtcaithietbi[quaylaitruocdo_i+1]={"EnAuto Check Tat Bat","Cho Phep Tang Gio Tat","Cho Phep Giam Gio Tat","Cho Phep Tat",\
"Cho Phep Bat","Tu Dong Tat Khi Bat Bang Dieu Khien Khi Bat","Cai Dat Bo Dem So Lan Bat","Gia Tri Phim Tang Giam","Khoang Tat Mac Dinh Khi Bat Thiet Bi",\
"Khoang Tat Dac Biet Thiet Bi Tu Bat","Bat Lay ThoiGian Tat DacBiet Khi AutoOn","Cho Ve Mac Dinh STT Thiet Bi",\
"Cho Phep Thiet Bi Khac Bat Kem Khi Thiet Bi Duoc Bat" ,"Cai Dat So Cua Thiet Bi Bat Kem","Cai Dat Hen Gio 0 [Mac Dinh La Hen Gio Tat]","Cai Dat Hen Gio 1 [Mac Dinh La Hen Gio bat]",\
"Cho Phep Bat Kem Bao Dong","Am Bao Thiet Bi Da Tu Tat[Dung DK Bat]","Khong Cho Bat Qua Nhieu Dac Biet BNL","Thoat Cai Dat","Chon Lai Thiet Bi Can Cai Dat"};
temvitricai=0;
while(1){  
		chonthietbi:
		id1=inputstttb();//bat buoc fai nhap dung tang stt thiet bi    
		bochonthietbi:
		eeprom_reads(adee_thietbi(id1),sizeof(thietbitemp),&thietbitemp);//chep thong tin thiet bi vao thietbitemp de chinh sua
		lcd_clr(lines);
		lcd_puts("Nhan Phim Tang Giam\nDe Lua Chon Cai Dat");//c
		waitsig(delay_);
		i=temvitricai;
		while(1){
		lcd_clr(lines);
		lcd_puts(txtcaithietbi[i]);
		lcd_vsprintf(" %bu[%bu,%bu]-%bu",id1,(uchar)((uchar)thietbitemp.sothutudat/(uchar)sothietbi1tang),(uchar)(thietbitemp.sothutudat%sothietbi1tang),i );
		tempchar=ir_getkeytimeout(binhthuong,0);
		if(tempchar==next){if(++i==quaylaitruocdo_i+1)i=0;}
		else if(tempchar==prev){if(--i==0xFF)i=quaylaitruocdo_i;} 
		else if(tempchar==ok) break;
		else bell=offbell;
		}
		lcd_clr(lines);
		lcd_puts(txtcaithietbi[i]);
		if(!checkhome())lcd_putchar(' ');
		tempchar=lcd_wait();//lay toa do hien tai
		lcd_putchar('\n'); //loi ko xuong dong
		lcd_puts(huongdanonoffbit);//con tro dang o duoi cung ben phai sau dong down
		lcd_goto(tempchar);
   switch (temvitricai=i){
		case lockauto_i:inputonoffbit(&hengiotemp,vitrilockauto); 
		break;
		case bitagi_i:inputonoffbit(&thietbitemp,vitribitagi);
		break;
		case bigigi_i:inputonoffbit(&thietbitemp,vitribigigi);
		break;
		case bita_i:inputonoffbit(&thietbitemp,vitribita);
		break;
		case biba_i:inputonoffbit(&thietbitemp,vitribiba);
		break;
		case tudongtat_i:inputonoffbit(&thietbitemp,vitritudongtat);
		break;
		case batkembaodong_i:inputonoffbit(&thietbitemp,vitribatkembaodong);
		break;
		case ambaotat_i:inputonoffbit(&thietbitemp,vitriambaotat);
		break;
		case cambatnhieu_i:inputonoffbit(&thietbitemp,vitricambatnhieu);
		break;
		case tgtatdacbiet_i:inputonoffbit(&thietbitemp,vitritgtatdacbiet);
		break;
		case couton_i:
			lcd_clr(lines);
			lcd_puts("Gia Tri Cu Bo Dem So Lan Bat ");
			lcd_vsprintf("%u\n",(uint)thietbitemp.couton);	//gia tri cu
			lcd_puts("Gia Tri Moi ");thietbitemp.couton=getkeyab(0,65535,phimtm_|minmax_);//gia tri moi nhap vao
		break;
		case nactime_i:
		    lcd_clr(lines);
			lcd_puts("Gia Tri Phim Tang Giam Cu ");
			lcd_vsprintf("%bu\"%bu\'",(uchar)thietbitemp.nactime.gio,(uchar)thietbitemp.nactime.phut);
			lcd_puts("\nNhap Gia Tri Phim Tang Giam Moi");
			waitsig(delay_) ;
			settimeugetkey(getkeyab,&thietbitemp.nactime);
		break;
		case ktimetatdacbiet_i:
		    lcd_clr(lines);
			lcd_puts("Khoang Thoi Gian Tat Dac Biet Khi AutoOn Thiet Bi ");
			lcd_vsprintf("%bu\"%bu\'",(uchar)thietbitemp.ktimetatdacbiet.gio,(uchar)thietbitemp.ktimetatdacbiet.phut);
		    lcd_puts("\nNhap Gia Tri Moi");
			waitsig(delay_) ;
			settimeugetkey(getkeyab,&thietbitemp.ktimetatdacbiet);
		break;
		
		case mdktimetat_i:
		    lcd_clr(lines);
			lcd_puts("Khoang Thoi Gian Tat Mac Dinh Khi Bat Thiet Bi ");
			lcd_vsprintf("%bu\"%bu\'",(uchar)thietbitemp.mdktimetat.gio,(uchar)thietbitemp.mdktimetat.phut);
		    lcd_puts("\nNhap Gia Tri Moi");
			waitsig(delay_) ;
			settimeugetkey(getkeyab,&thietbitemp.mdktimetat);
		break;
		case thutugoc_: caidatthietbi(0x10000000L>>sothutudat_,0);
		break;
		case hengiotat_i: i=0;goto tiep;
		break;
		case hengiobat_i:i=1;goto tiep ;
		break;
		case kihobake_i: inputonoffbit(&thietbitemp,vitrikihobake);
		break;
		case sttbatkem_i: 
		    lcd_clr(lines);
			lcd_puts("Thiet Bi Bat Kem Ban Dau ");
		   
		   for(i=0;i<sothietbi;i++){
				if( eeprom_read((adee_tangthietbi(0,0))+i)==thietbitemp.sttbatkem){
			  		lcd_vsprintf("[%bu,%bu]",
			   		(uchar)(i/(uchar)sothietbi1tang),
			   		(uchar)(i%sothietbi1tang));
					break;//thoat vong for
			    }
		   }


			lcd_puts("\nNhap Thiet Bi Moi");
			waitsig(delay_);
		    thietbitemp.sttbatkem=inputstttb();
		break;
		case quaylaitruocdo_i: goto chonthietbi;
		case thoatcaidat_i: return;
    }			 //ID1 LA CUA thietbitemp.sttbatkem
    eeprom_writes(adee_thietbi(id1),sizeof(thietbitemp),&thietbitemp);//chep thong tin thiet bi da chinh sua luu tru
	lcd_clr(lines);
    lcd_puts(txtthanhcong); 
    bell=bellsucsesful;
  	delay_ms(1000);
    goto bochonthietbi;
    tiep:; //cai dat ngay thang nam thu hen gio
 //   hengiotemp=thietbitemp.hengio[i];//lu vao bien nay de su ly
    lcd_clr(lines);
	lcd_putsxy(huongdanonoffbit,0,1);
    lcd_putsxy("Loai Hen Gio Bat ",0,0);
    
    inputonoffbit(&(thietbitemp.hengio[i]),vitribattat ) ;  

    lcd_clr(lines);
	lcd_putsxy(huongdanonoffbit,0,1);
    lcd_putsxy("Bat Hen Gio ",0,0);
    if(thietbitemp.hengio[i].battat) lcd_puts("Bat ");else lcd_puts("Tat ");
    inputonoffbit(&(thietbitemp.hengio[i]),vitrikichhoat ) ;  

if(thietbitemp.hengio[i].battat) {//hen giio tat ko co muc nay	
    lcd_clr(lines);
	lcd_putsxy(huongdanonoffbit,0,2);
    lcd_putsxy("Bat Autooff Khi Tu Dong Bat ",0,0);
    inputonoffbit(&(thietbitemp.hengio[i]),vitriautooff ) ;  

    lcd_clr(lines);
	lcd_putsxy(huongdanonoffbit,0,2);
    lcd_putsxy("Bat Thoi Gian Tat Dac Biet Khi Tu Dong Bat ",0,0);
    inputonoffbit(&(thietbitemp.hengio[i]),vitritgtatdacbiet ) ;  

    }

	lcd_clr(lines);
	lcd_putsxy(huongdanonoffbit,0,1);
    lcd_putsxy("Am Bao Khi Tu Bat ",0,0);
    inputonoffbit(&(thietbitemp.hengio[i]),vitribaobat ) ;  

	lcd_clr(lines);
	lcd_putsxy(huongdanonoffbit,0,1);
    lcd_putsxy("Am Bao Khi Tu Tat ",0,0);
    inputonoffbit(&(thietbitemp.hengio[i]),vitribaotat ) ;  

    eeprom_writes(adee_thietbi(id1),sizeof(thietbitemp),&thietbitemp);//chep thong tin thiet bi da chinh sua luu tru

	lcd_clr(lines);
	lcd_puts(txtthanhcong);
	bell=bellsucsesful;
	delay_ms(1000);

    if(!(thietbitemp.hengio[i].kichhoat)) {lcd_clr(lines);lcd_puts("Chuc Nang Hen Gio Da Khong Duoc Kich Hoat\nNhan Phim Bat Ky De Tiep Tuc Cai Dat.");waitsig(delay_);goto bochonthietbi;}

	caidathengio(&thietbitemp.hengio[i]);	//toi day moi xog
    eeprom_writes(adee_thietbi(id1),sizeof(thietbitemp),&thietbitemp);
	lcd_clr(lines);
	lcd_puts(txtthanhcong); 
	bell=bellsucsesful;
	delay_ms(1000);
	goto bochonthietbi;
    }
}    
void datsothietbi(){          
	  unsigned char id,tang,temp;
      while(1){ 
		  while(1){
		   lcd_clr(lines);
		   eeprom_reads(adee_thietbi(id),sizeof(thietbitemp),&thietbitemp);
		   lcd_vsprintf("OK: Chon Thiet Bi Dat So %bu[%bu,%bu]-",id,
		   (uchar)((uchar)thietbitemp.sothutudat/(uchar)sothietbi1tang),
		   (uchar)(thietbitemp.sothutudat%sothietbi1tang));
		    for(tang=0;tang<sothietbi;tang++){
				if( eeprom_read((adee_tangthietbi(0,0))+tang)==id){
			  		lcd_vsprintf("(%bu,%bu)-",
			   		(uchar)(tang/(uchar)sothietbi1tang),
			   		(uchar)(tang%sothietbi1tang));
				}
		   }
		   nhaythietbi(id);
		   temp=ir_getkeytimeout(binhthuong,0);
		   if     (temp==next){if(++id==sothietbi)id=0;}
		   else if(temp==prev){if(--id==0xFF)id=sothietbi-1;} 
		   else if(temp==ok) break;
		   else bell=offbell;
          }
	      lcd_clr(lines);
          lcd_puts("Nhan OK:Thoat, Menu Cai Dat Nhu Thong So, Phim Khac: Tiep Tuc");
		  lcd_vsprintf("%bu[%bu,%bu]",id,
   		  (uchar)((uchar)thietbitemp.sothutudat/(uchar)sothietbi1tang),
   		  (uchar)(thietbitemp.sothutudat%sothietbi1tang));

		  if((temp=ir_getkeytimeout(binhthuong,ljmp0))==ok)return;
		  else if(temp==khongchon){tang=thietbitemp.sothutudat/(uchar)sothietbi1tang;
		  	temp=thietbitemp.sothutudat%sothietbi1tang;goto tat;
		  }
          lcd_clr(lines);
		  lcd_vsprintf("SoVatLy %bu[%bu,%bu]\n",id,
   		  (uchar)((uchar)thietbitemp.sothutudat/(uchar)sothietbi1tang),
   		  (uchar)(thietbitemp.sothutudat%sothietbi1tang));

		  lcd_clr(3);
		  lcd_putsxy("Dat Thanh Tang ",0,1);
		  
          tang=getkeyab(tang0,tang0+sotang-1,phimtm_|minmax_)-tang0;//ma phim chua tang muon su ly
	      if(tang==(sotang-1)){temp=sothietbi-sothietbi1tang*(sotang-1);}else temp=sothietbi1tang; 
          lcd_clr(3);
		  lcd_putsxy("Dat Thanh STT ",0,2);
          temp=getkeyab(0,temp-1,phimtm_|minmax_);//so dat 1 chua sthu tu trong tang maphim =id1
		  
		  thietbitemp.sothutudat=tang*sothietbi1tang+temp;
		  tat:
		  eeprom_write((adee_tangthietbi(tang,temp)),id);
		  eeprom_writes(adee_thietbi(id),sizeof(thietbitemp),&thietbitemp);
          lcd_clr(lines);
          lcd_puts(txtthanhcong); 
          setbell(bellsucsesful);
      }
}
void doisothietbi(){          
	  unsigned char sodat1,id1,sodat2,id2;
      while(1){ 
	      lcd_clr(lines);
          lcd_puts(" Nhan OK De Thoat, Nhan Phim Khac De Tiep Tuc Doi So Thiet Bi");
		  if(ir_getkeytimeout(binhthuong,ljmp0)==ok)return;
		  waitsig(delay_);
 
          lcd_clr(lines);
          lcd_puts("Tang Can Doi ");
          maphim=(getkeyab(tang0,tang0+sotang-1-tang0,phimtm_|minmax_))-tang0;//ma phim chua tang muon su ly
		  lcd_putchar('\n');
          lcd_puts("So Thu Tu Can Doi ");
          sodat1=getkeyab(0,sothietbi1tang-1,phimtm_|minmax_);//so dat 1 chua sthu tu trong tang maphim =id1
          
          sodat1=sothietbi1tang*maphim+sodat1;//sodat1=&id1 // so dat 1 chua so thu tu that cua thiet bi, chinh la gia tri id1
          id1=eeprom_read(adee_tangthietbi(0,0)+sodat1);//id1=&sodat1
          
          eeprom_reads(adee_thietbi(id1),sizeof(thietbitemp),&thietbitemp);//chep thong tin thiet bi vao thietbitemp de chinh sua
          nhaythietbi(id1); //cho nhay thiet bi id1 nham biet no la thiet bi nao

 //         lcd_clr(lines);
          lcd_puts("\nChuyen Sang Tang->");
          maphim=(getkeyab(tang0,tang0+sotang-1-tang0,phimtm_|minmax_));
		  lcd_putchar('\n');
          lcd_puts("Sang So Thu Tu->");
          sodat2=getkeyab(0,sothietbi1tang-1,phimtm_|minmax_);
         
          sodat2=sothietbi1tang*maphim+sodat2;//sodat2=&id2
          thietbitemp.sothutudat=sodat2;//sodat1'=sodat2
         
          eeprom_writes(adee_thietbi(id1),sizeof(thietbitemp),&thietbitemp);//sao luu thong tin thiet bi 1 da chinh sua          
  //thietbitemp da xong nhiem vu voi thiet bi 1 co the dung soa chep thiet bi 2
          id2=eeprom_read(adee_tangthietbi(0,0)+sodat2);//id2=&sodat2
          nhaythietbi(id2); //cho nhay thiet bi id1 nham biet no la thiet bi nao

          eeprom_reads(adee_thietbi(id2),sizeof(thietbitemp),&thietbitemp);//chep thong tin thiet bi vao thietbitemp de chinh sua
          thietbitemp.sothutudat=sodat1;//sodat2'=id1(sodat1)
          eeprom_writes(adee_thietbi(id2),sizeof(thietbitemp),&thietbitemp);//chep thong tin thiet bi vao thietbitemp de chinh sua

          eeprom_write((adee_tangthietbi(0,0)+sodat1),id2);//id1=id2
          eeprom_write((adee_tangthietbi(0,0)+sodat2),id1);//id2=id1
  lcd_clr(lines);
  lcd_puts(txtthanhcong); 
  setbell(bellsucsesful);
      }
    }  