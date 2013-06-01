#define	checktimeout__c 
#define	checktimeout__
jmp_buf		env;//poienv dung duy nhat trong ham ngat ko can thiet vi sac xuat dung chung bang 0 vi chi khi phan dau ham getir thi ngat moi dc goi
unsigned	char data flagenv=0; //chua cac bit bao tung time oute da bat
#include	<checktimeout.h >
void retiao(){
	#pragma asm
	sjmp backupaddlongjmp;
	goiretiao:
	reti;
	backupaddlongjmp:
	acall goiretiao;
	#pragma endasm;
}
unsigned	char checktimeout(){//ham tra lai gia tri flagenv
	unsigned char temp,i ;
	if(flagenv){
		for(i=0;i<soenv;i++){ //soenv =8
			if(trongsoset[i]& flagenv){ //kiem tra flag co bat hay ko
				temp=eeprom_read(adee_env(i+1)-1);//doc bo dem de tang gia tri
				++temp;eeprom_write(adee_env(i+1)-1,temp);//luu gia tri bo dem moi sau khi tang
				if(temp==notimeout){//kiem tra xem = notimeout hay ko
					flagenv&=(~trongsoset[i]);// neu co xoa ngay co tuong ung khi gap lenh nhay
					eeprom_reads(adee_env(i),sizeof(env),env);//lay gia tri luu tru thong tin nhay vao bien poienv
					retiao();//ham goi tu ngat nen fai co reti ao
					longjmp(env,i);//nhay di toi vi tri da dinh trong poienv
				}
			}
		}
	}else	flagstatus&=(~flagtimeout_); //chi khi flagenv=0 ko co timeout nao duoc dat thi ham nay moi xoa co nay
	return flagenv;//co timeout de check flagenv dag duoc bat, chua co longjmp nao duoc bat
}

unsigned char settimeout(unsigned char vitri,unsigned char giatri){//env la bien toan cuc truyen dia chi
	unsigned char temp; 
	if(vitri&0x80){vitri&=(~0x80); eeprom_writes(adee_env(vitri),sizeof(env),env);}//ghi vi tri nhat vao epprom neu nhu env duoc truyen ngay tu vi tri goi
	temp=eeprom_read(adee_env(vitri+1)-1);//doc thong tin bo dem luu vao temp de return =0 tuong duong flag tat
	eeprom_write(adee_env(vitri+1)-1,giatri);//viet gia tri bo so dem moi moi vao eppro
	vitri=trongsoset[vitri];
	flagstatus|=flagtimeout_;
	flagenv|=vitri;//set co tai vi tri truong ung
	return temp;//co timeout de check flagenv dag duoc bat, chua co longjmp nao duoc bat
}

unsigned char gettimeout(unsigned char vitri){//lay gia tri bo dem timeou neu 
	return eeprom_read(adee_env(vitri+1)-1);
}

void writeenvtoeeprom(unsigned char vitri){
	eeprom_writes(adee_env(vitri),sizeof(env),env);//an phim thoat thi ctrinh se nhay ve day chi nhat tu ham getkey
}