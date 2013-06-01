#define  bell__c
#include  <bell.h >
//ndelaytime2usms
#undef  on
#undef  off
#define on  0
#define off 1
//typedef enum  {belloff,bellon,bellerror,bellwarning,bellsucsesful,bellarlam} bell;
unsigned char bell,belltemp,coutbell,coutrepeat;
unsigned char getbell(){
	return bell;
}
unsigned char setbell(unsigned char codebell){
	bell=codebell&(~diir_);
	return bell;
}

void checkbellauto(){	
	/*if((bell!=offbell)&&!IRIN){
	delay_us(100);
	if(!IRIN){bell=offbell;}
	}*/	
	if(bell==offbell){belltemp=offbell;coutbell=0;ring=off;coutrepeat=0;return;}
	else if(bell==lockbell){coutbell=0;coutrepeat=0;return;}
	if(belltemp!=bell){
		coutbell=0;ring=off;belltemp=bell;coutrepeat=0;
	};//belltemp luu trang thai kieu bell truoc do,neu co thay doi thi gan bien dem =0 ngay
	switch (bell){
		//typedef enum  {binhthuong,bellonoff,bellerror,bellwarning,bellsucsesful,bellarlam} bell;
		case binhthuong:
			switch(coutbell){
				case ndelaytime2usms(0)   :ring=on;break;
				case ndelaytime2usms(100) :ring=off;coutbell=0;break;
			}break;
		case bellonoff:
			switch(coutbell){
				case ndelaytime2usms(0)   :ring=on;break;
				case ndelaytime2usms(100) :ring=off;coutbell=0;break;
			}break;
		case bellwarning: 
			switch(coutbell){
				case ndelaytime2usms(0)   :ring=on;break;
				case ndelaytime2usms(100) :ring=off;break;
				case ndelaytime2usms(150) :ring=on;break;
				case ndelaytime2usms(250) :ring=off;break;
				case ndelaytime2usms(350) :ring=off;coutbell=0;break;
			}
			if((!coutbell)){if((++coutrepeat)>=15){coutrepeat=0;ring=off;}}break;
		case bellsucsesful:
			switch(coutbell){
				case ndelaytime2usms(0)   :ring=on;break;
				case ndelaytime2usms(200) :ring=off;coutbell=0;break;
				case ndelaytime2usms(250) :ring=off;break;
			}break;
		
		case bellarlam:
			switch(coutbell){
				case ndelaytime2usms(0)   :ring=on;break;
				case ndelaytime2usms(250) :ring=off;break;//250
				case ndelaytime2usms(500) :ring=on;break;
				case ndelaytime2usms(700) :ring=off;break;//200
				case ndelaytime2usms(950) :ring=on;break;
				case ndelaytime2usms(1050):ring=off;break;	//100
				case ndelaytime2usms(1500):ring=off;coutbell=0;break;
			}
			if(!coutbell){if((++coutrepeat)>100){coutrepeat=0;ring=off;}}break;
		case baodotnhap:
			switch(coutbell){
				case ndelaytime2usms(0)   :ring=on;break;
				case ndelaytime2usms(300) :ring=off;break;
				case ndelaytime2usms(350) :ring=on;break;
				case ndelaytime2usms(550) :ring=off;break;
				case ndelaytime2usms(650) :ring=off;coutbell=0;break;
			}
			if(!coutbell){if((++coutrepeat)>100){coutrepeat=0;ring=off;}}break;
		
		case offbell:coutrepeat=0;coutbell=0;ring=off;
		break;
	}
if((!coutbell)&&(!coutrepeat)&&(ring==off)){bell=offbell;}else coutbell++;//neu da xong am bao thi tat het cac bien
}