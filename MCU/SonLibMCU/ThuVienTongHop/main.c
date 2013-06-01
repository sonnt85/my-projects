#define   main__c //muc dich cac bien toan cuc dat o day
#include  <allfuntion.h>
#include  <typedef.h >
//[A]=a (toa do A)
//[A]B toa do cua A=[A] lay B lam moc b=[B]=0
//b-a= toa do cua B voi moc toa do la A ([A]=0) 
//a+x la toa do phan tu cuoi cung khi them x phan bat dau tu toa do a+1 
//a+x+1 la toa do ngay sau phan tu cuoi khi them nhu tren 

#include <SROM.H >
enum {caigiohethong_i=0,thaypass,idthietbi_i,datsothietbi_i,resetstttb_,backupstttb_,respstttb_,passkhoidong,varkhoidong,setuptuthbi,\
		khoahethong,donhaybaodong,quaylaitruocdo};
code char  code *txthuongdan1[quaylaitruocdo+1]={"Cai Gio He Thong","Thay Pass Bao Mat","Trao Doi So Thiet Bi","Dat So Thiet Bi",\
"Reset So Thu Tu Thiet Bi","Luu Tru Cai Dat STT Thiet Bi Hien Tai","Khoi Phuc Cai Dat STT Thiet Bi Da Luu Tru","Pass Khoi Dong",\
"Bien Khoi Dong","Cai Dat Tung TB","Khoa He Thong","Thay Doi Do Nhay Bat Bao Dong","Chon Lai Cai Dat"};
char code security[80]="Looked.! He Thong Bi Xam Pham Trai Phep! Moi Thac Mac Lien He 0949109985"	;
//unsigned char code infor[80]="DATN: ThietKe HeThong DieuKhien KhongDay. SinhVien Nguyen Thanh Son";
char code infor[80]="Designed :Nguyen ThanhSon.0949109985 Model: NTS-IRCT\nVertion:000.01.03";
code char * code setupbienkd[chonlai_+1]={"So Thu Tu Dat Mac Dinh La STT Vat Ly","Cho Phep Tu Dong Tat Khi Bat Thiet Bi","Reset Bo Dem So Lan Bat" ,"Mo Auto Check On Off",\
   "Cho Phep Tang Gio","Cho Phep Giam Gio","Tat Thiet Bi","Cho Phep Tat Thiet Bi","Cho Phep Bat Thiet Bi","Mac Dinh Nac Thoi Gian La 5'",\
   "Mac Dinh Thoi Gian Tat La 2h","Cai Dat Cac Bo Hen Gio Cua Tung Thiet Bi","Tat Kich Hoat Bat Kem Thiet Bi","So Thu Tu Bat Kem La Thiet Bi So 0",\
   "Cho Phep Thiet Bi Bat Kem Bao Dong","Tat Am Bao Khi Tat Cua Tat Tu Dong Khi Bat","Cho Phep Cac Hen Gio Hoat Dong",\
   "Tat Am Bao Bat","Tat Am Bao Tat","Cai Dat Hen Gio 0 La Tat, 1 La Bat","Bat Theo Phut Va Xoa Cac Phut","Bat Theo Gio Va Xoa Cac Gio",\
   "Tat Theo Thu Va Tat Cac Thu", "Tat Bat Theo Ngay Va Xoa Cac Ngay" ,"Tat Bat Theo Thang Va Xoa Cac Thang","Tat Bat Theo Nam Va Xoa Cac Nam",\
   "Tu Dong Tat Khi Hen Gio Bat Hoat Dong","Tat Cam Bat Thiet Bi Qua Nhieu","Khoang Thoi Gian Tat Dac Biet Khi Bat La 5\'","Cho Phep Nap Thoi Gian Dac Biet De Tat Thiet Bi",\
   "Cai Dat Ngay Chi Cho Thiet Bi Hien Tai","Nhan OK De Luu Cai Dat Sau Do Chon Lai Loai Cai Dat"};

unsigned char i=0;	 
void main(){
//memset(out4094,0xf0,sizeof(out4094)); 
//outputdevice(out4094);
char i=0,temvitricai=0;

lcd_init();	  
maphim=3;
eeprom_init();
eeprom_reads(adee_thoigian(0),sizeof(timesys),&timesys);//restore thoi gian he thong trong moi truong ho          
eeprom_reads(adee_khoidong(0),sizeof(pass32),&pass32);//doc bien khoi dong
eeprom_reads(adee_out4094,sizeof(out4094),out4094);//restore trang thai thiet bi output vao eeprom co dia chi adee_tatbat
outputdevice(out4094);
cousensorct=er(adee_cousen(0));	//khoi phuc bo dem bao dong, bat bd
clearbit(&pass32,setup1thietbi_);//che bit chi cai dat 1 thiet bi
caidatthietbi(pass32,0);
init_tiin();
testfuntion();
bell=binhthuong;
sensorct=1;//cai dat sensor
while(1){
   goto quapass;
   inputpass:
   setjmpeep(0);
   lcd_clr(lines);
   lcd_puts(security);
   eeprom_reads(adee_pass(1),sizeof(pass16),&pass16);//pass chuc nang cung la pass khoi dong
   waitsig(delay_);
   nhappass(pass16);// nhap sai timeou se dua chuong trinh ve dau
   quapass:
   setjmpeep(0);
   EA=1;
//   flagstatus|=(bilink_);
//   flagstatus&=(~nodis_); //cho hien thi trong ngat
   waitsig(delay_);
   lcd_clr(lines);
   lcd_puts(infor);
//   flagstatus&=(~bilink_);
//   flagstatus|=nodis_;
   maphim=getkeyab(tang0,tang0+sotang-1,0);//chon dung tang moi thoat sang lenh duoi dc
   
   tanghientai=maphim-tang0;
   chisothietbi=eeprom_read(adee_tangthietbi(tanghientai,eeprom_read(adee_stttbdangdungtang(tanghientai)))); //stt vat ly
   
   chonkenhtatbat:
        lcd_clr(lines);         
        lcd_gotoxy(0,0);  
        lcd_vsprintf("%bu[%bu,%bu]-ON=%bu-%bu:%bu",(uchar)chisothietbi,(uchar)thietbitemp.sothutudat/sothietbi1tang,(uchar)thietbitemp.sothutudat%sothietbi1tang 
		,(uchar)thietbitemp.status,(uchar)timesys.time.gio,(uchar)timesys.time.phut);
		lcd_gotoxy(0,1);
		lcd_vsprintf("GioTat=%bu:%bu-AmTat=%bu",(uchar)thietbitemp.timetat.gio,(uchar)thietbitemp.timetat.phut,(uchar)thietbitemp.ambaotat);
        lcd_gotoxy(0,2);
		lcd_vsprintf("SLB=%u-TDCHG=%bu",thietbitemp.couton,(uchar)thietbitemp.lockauto);
		lcd_gotoxy(nuli-3,2);lcd_vsprintf("K%bu",(uchar)thietbitemp.batkembaodong);//co bat kembao dong hay ko 
		lcd_gotoxy(0,3);
        poichar=(uchar*)&thietbitemp;//	loi tai day
        digi2textbin(lcd_buff,8,*poichar);
        lcd_puts(lcd_buff)  ;
		poichar++;
        digi2textbin(lcd_buff,3,*poichar);
        lcd_puts(lcd_buff) ;
		lcd_putchar('-');
        poichar=(uchar*)&thietbitemp.hengio[1];//thong tin 7 bit hen gio bat
        digi2textbin(lcd_buff,5,*poichar);
        lcd_puts(lcd_buff) ;//sau dau + o tren
		lcd_vsprintf("-%bu",thietbitemp.sttbatkem); //so thu tu bat 
    
	waitsig(0);
 	maphim=checkswchanel();
	if((flagstatus&phimnong_)||(maphim<=9)){
		flagstatus&=(~phimnong_);
        chisothietbi=eeprom_read(adee_tangthietbi(tanghientai,maphim));//chi so lay trong mang ao la gia tri that id cua thiet bi
        eeprom_write(adee_stttbdangdungtang(tanghientai),maphim);//ma phim chinh la stt trong mang tang //backup neu mat dien thi van con luu
        eeprom_reads(adee_thietbi(chisothietbi),sizeof(thietbitemp),&thietbitemp);//chep thong tin thiet bi vao thietbitemp
        goto chonkenhtatbat;     
    }
    //CHON XONG TANG 

   switch (maphim) {//kiem tra xem co phai nhung tinh nang co ban hayko
		case checkonoff: if(thietbitemp.status)nhaythietbi(chisothietbi);
		break; 
		case tangthoigian:if((thietbitemp.status)&&(thietbitemp.bitagi)&&(thietbitemp.tudongtat)){
				  tanggio:
		          congtrutime(&thietbitemp.timetat,&thietbitemp.nactime,1);//chi dung cho thoi gian tat va khi thiet bi dang bat 
//       if((memcmp(&thietbitemp.timetat,&timesys.time,sizeof(timesys.time))<0)&&
//		 !((thietbitemp.timetat.gio<=6)&&(timesys.time.gio>=18)) )
//       {thietbitemp.status=0;clearbit(out4094,chisothietbi);}//neu bam giam gio vuot be hon time hien tai thi tat thiet bi
		      } else {setbell(offbell);if(ir_getkeytimeout(binhthuong,ljmp0)==admin)goto tanggio;else bell=offbell;}
		      
		break;
		case giamthoigian: if((thietbitemp.status)&&(thietbitemp.bigigi)&&(thietbitemp.tudongtat)){
				 giamgio:
		          congtrutime(&thietbitemp.timetat,&thietbitemp.nactime,-1);//chi dung cho thoi gian tat va khi thiet bi dang bat 
				  if((memcmp(&thietbitemp.timetat,&timesys.time,sizeof(timesys.time))<=0)&&
				    (!((thietbitemp.timetat.gio<=6)&&(timesys.time.gio>=18)))){
				    thietbitemp.status=0;clearbit(out4094,chisothietbi);
				  }//neu bam giam gio vuot be hon time hien tai thi tat thiet bi
		      } else {setbell(offbell);if(ir_getkeytimeout(binhthuong,ljmp0)==admin)goto giamgio;else bell=offbell;}
		break;
		case tat: if(thietbitemp.bita&&thietbitemp.status){
		tatthietbi:
		thietbitemp.status=0;clearbit(out4094,chisothietbi);
		}else {setbell(offbell);if(ir_getkeytimeout(binhthuong,ljmp0)==admin)goto tatthietbi;else bell=offbell;}
		break;
		case bat: 
		
				if(!thietbitemp.status&&thietbitemp.biba) goto batthietbi;
				checkbat:
				setbell(offbell);
				delay_ms(100);
				if(ir_getkeytimeout(binhthuong,ljmp0)==admin)goto batok;
				else {bell=offbell;break;}
				
				batthietbi:
				if(thietbitemp.cambatnhieu){
				temptime=thietbitemp.timetat;
				congtrutime(&temptime,&thietbitemp.mdktimetat,1);
					if((memcmp(&temptime,&timesys.time,sizeof(timesys.time))>=0)&&((temptime.gio-timesys.time.gio)<3)){
					 bell=offbell; goto checkbat;
					}
				
				}
			    batok:
				thietbitemp.status=1;
				thietbitemp.couton++;
				setbit(out4094,chisothietbi);
				if(thietbitemp.tudongtat){//neu da kich hoat tu dong tat khi bat thiet bi thi su ly lenh nay
					thietbitemp.timetat=timesys.time; 
					congtrutime(&thietbitemp.timetat,&thietbitemp.mdktimetat,1);//timesys0
				}
				if(thietbitemp.kihobake){//su ly neu co bat kem thiet bi
					eeprom_reads(adee_thietbi(maphim=thietbitemp.sttbatkem),sizeof(thietbitemp0),&thietbitemp0);
					thietbitemp0.status=1;
					setbit(out4094,maphim);
					thietbitemp0.timetat=timesys.time;
					congtrutime(&thietbitemp0.timetat,&thietbitemp0.mdktimetat,1);
					eeprom_writes(adee_thietbi(maphim),sizeof(thietbitemp0),&thietbitemp0);
				}
			
		break;
		case	battatbaodong:maphim=((cousensorct!=nosensor)+0x30); while(1){
							   lcd_clr(lines);
							   lcd_puts("Canh Bao! Hay Phanh Cua Ra Khi Bat Tinh Nang Nay. Kaka\nBat Bao Dong:  ");
							   lcd_putchar(maphim);
							   i=ir_getkeytimeout(binhthuong,0);
							   if     (i==bat) {cousensorct=er(adee_cousen(0));maphim='1';}  
						       else if(i==tat) {cousensorct=nosensor;maphim='0';}
							   else if(i==ok) break;
							   else bell=offbell;
							 }
		break;
		case tathetthietbi:
		for(i=0;i<5;i++){if(ir_getkeytimeout(offbell,0)!=tathetthietbi){break;}else delay_ms(300);}
		bell=binhthuong;
		for(i=0;i<sothietbi;i++){
			eeprom_reads(adee_thietbi(i),sizeof(thietbitemp),&thietbitemp);
			thietbitemp.status=0;
			clearbit(out4094,i);
			eeprom_writes(adee_thietbi(i),sizeof(thietbitemp),&thietbitemp);
		}
		eeprom_reads(adee_thietbi(chisothietbi),sizeof(thietbitemp),&thietbitemp);
		break;
		case setupthietbi:
		for(i=0;i<10;i++){if(ir_getkeytimeout(offbell,0)!=tathetthietbi){break;}else delay_ms(300);}
			  bell=binhthuong;
		      caidattungthietbi();
			  break;
		case menu: goto menu_labp;
		break;
		default:setbell(offbell);goto chonkenhtatbat; //trong truong hop chua het time out thi quay lai con tat bat
  }
  eeprom_writes(adee_thietbi(chisothietbi),sizeof(thietbitemp),&thietbitemp); //save thong tin thiet bi vao eeprom
  outputdevice(out4094);//dieu khien tat bat thiet bi dua tren thanh ghi trong out4094
  ews(adee_out4094,out4094);//backup out4094;
  goto chonkenhtatbat;
 //================================
	menu_labp:
	eeprom_reads(adee_pass(0),sizeof(pass16),&pass16);
	setbell(bellsucsesful);
	nhappass(pass16);// nhap sai timeou se dua chuong trinh ve dau
	temvitricai=0;
	menu_lab:
	lcd_clr(lines);
	lcd_puts("Nhan Phim Tang Giam De Hien Thi List Cai Dat");//c
	flagstatus|=(chongat_|flagtimeout_);
	waitsig(0);
	maphim=temvitricai;   
	while(1){
	   lcd_clr(lines);;
	   lcd_puts(txthuongdan1[maphim]);//dong 1
	   lcd_putchar('\n');//dong 2
	   lcd_puts(huongdantanggiam); //ok	 da tro  dong 3
	   lcd_vsprintf("CD %bu",(uchar)maphim );//ham nay ko loi 
	   i=ir_getkeytimeout(binhthuong,0);
	   if(i==next){if(++maphim==quaylaitruocdo+1)maphim=0;} 
	   else if(i==prev){if(--maphim>quaylaitruocdo)maphim=quaylaitruocdo;}
	   else if(i==ok) break; else bell=offbell;
	}
	temvitricai=maphim;
	lcd_clr(lines); 
   //tinh nang cai dat he thong
   switch (maphim){	 
		case caigiohethong_i: 
		setthoigianugetkey(getkeyab,&timesys);
		break;
		case thaypass:
		eeprom_reads(adee_pass(0),sizeof(pass16),&pass16);
		lcd_vsprintf("Pass Cu %u\n",(uint)pass16);
		lcd_puts("Pass Moi ");
		pass16=getkeyab(0,65535,phimtm_|minmax_);
		eeprom_writes(adee_pass(0),sizeof(pass16),&pass16);
		break; 
		case idthietbi_i: doisothietbi();
		break;
		case datsothietbi_i: datsothietbi();
		break;
		
		case setuptuthbi: caidattungthietbi();
		break;
		case resetstttb_: 
		caidatthietbi(0x10000000L>>sothutudat_,0);// reset lai so thu tu tat ca cac thiet bi
		break;
		case backupstttb_: 
		for(i=0;i<sothietbi;i++){//theo mang ao
			maphim=eeprom_read((adee_tangthietbi(0,0)+i));
			lai:
			eeprom_reads(adee_thietbi(maphim),sizeof(thietbitemp),&thietbitemp);
			if(thietbitemp.sothutudat!=i){lcd_clr(lines);lcd_puts("Can Cai Lai Thiet Bi Co So Vat Ly ");
				lcd_vsprintf("%bu Sang STT %bu Cua Tang %bu",maphim,(i%sothietbi1tang),(i/sothietbi1tang));
				waitsig(delay_);
				datsothietbi();
				goto lai;}
			thietbitemp.bksothutudat=thietbitemp.sothutudat=i;
			eeprom_writes(adee_thietbi(maphim),sizeof(thietbitemp),&thietbitemp);
		}
		break;
		case respstttb_: 
		for(i=0;i<sothietbi;i++){//theo mang that
			eeprom_reads(adee_thietbi(i),sizeof(thietbitemp),&thietbitemp);
			eeprom_write(adee_tangthietbi(0,0)+(thietbitemp.sothutudat=thietbitemp.bksothutudat),i);
			eeprom_writes(adee_thietbi(i),sizeof(thietbitemp),&thietbitemp);
		}
		break;
		
		case varkhoidong:    
		eeprom_reads(adee_khoidong(0),sizeof(pass32),&pass32);
		lcd_clr(lines);
		lcd_puts("Nhan Phim Tang Giam De Hien Thi List Tinh Nang Bien Khoi Dong");//c
		waitsig(delay_);
		maphim=sothutudat_;   
		while(1){
		   lcd_clr(lines);;
		   lcd_puts(setupbienkd[maphim]);
		   lcd_vsprintf(" %bu - CD %bu",(uchar)getbit(&pass32,maphim),maphim); //in bit vua nhap 0 hoac 1
		
		   if(getbit(&pass32,setup1thietbi_)) {
		        lcd_clr(lines);
		        lcd_puts("Nhap Thiet Bi Muon Khoi Phuc Mac Dinh");
				delay_ms(200);
		   		caidatthietbi(pass32&(~(0x10000000L>>sothutudat_)),i=inputstttb());
		        clearbit(&pass32,setup1thietbi_);
				lcd_clr(lines);
		        lcd_puts("Da Khoi Phuc Thiet Bi");
				lcd_vsprintf("%bu Thanh Cong",i);
				lcd_puts("[Khong Khoi Phuc STT Thiet Bi]");
				delay_ms(200);
		   }
		
		   i=ir_getkeytimeout(binhthuong,0);
		   if     (i==next){if(++maphim==chonlai_+1)maphim=sothutudat_;} 
		   else if(i==prev){if(--maphim>chonlai_)maphim=chonlai_;}
		   else if(i==bat) {if(maphim!=chonlai_)setbit(&pass32,maphim);}  
		   else if(i==tat) {if(maphim!=chonlai_)clearbit(&pass32,maphim);}
		   else if(i==khongchon){ clearbit(&pass32,maphim);continue; }
		   else if(i==ok)break; 
		   else bell=offbell;
		}
		eeprom_writes(adee_khoidong(0),sizeof(pass32),&pass32);
						
		break; 
		case passkhoidong:
			eeprom_reads(adee_pass(1),sizeof(pass16),&pass16);
			lcd_vsprintf("Pass Khoi Dong Cu\n%u\n",(uint)pass16);
			lcd_puts("Pass Khoi Dong Moi\n");
			lcd_gotoxy(nuli-5,lines-1);	                    
		    pass16=getkeyab(0,65535,minmax_|phimtm_);  
		    eeprom_writes(adee_pass(1),sizeof(pass16),&pass16);
		break;
		case donhaybaodong: 
			maphim=er(adee_cousen(0));	//10x50=500ms
			lcd_puts("Do Nhay Tu 1->50, Khuyen Cao La 5\n");
			lcd_vsprintf("Do Nhay Cu %bu\n",0xFF-er(adee_cousen(0)));
			lcd_puts("Nhap Do Nhay Moi ");
		    ew(adee_cousen(0),0xFF-(cousensorct=getkeyab(1,50,phimtm_)));	//10x50=500ms
		break; 
		case khoahethong:    goto  inputpass;  
		case quaylaitruocdo: goto  menu_lab; //ko co gi khac ngoai may thu nay nen ko co defaule
  }
  lcd_clr(lines);
  lcd_puts(txtthanhcong); 
  setbell(bellsucsesful);
  delay_ms(1000);
  goto           menu_lab;
}
}