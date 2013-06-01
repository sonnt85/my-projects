#include <ds1307.h>
#include <i2c.h>

unsigned char  BCD2Dec(unsigned char x){
	return	((x&0x0F)+(x>>4)*10);
}
/*
unsigned char  Dec2BCD(unsigned char x){
   return	x%10+((x/10)<<4);	
} */
void rtc_init(unsigned char rs, unsigned char sqwe, unsigned char out){
	i2c_init();
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x07);
	i2c_write(rs|(sqwe<<4)|(out<<7));
	i2c_stop();
}
void rtc_get_time(void *hourg, void *ming, void *secg){
	i2c_start();
	i2c_write(0xD0); 
	i2c_write(0x00);

	i2c_start();
	i2c_write(0xD1);
	*(unsigned char *)secg=(BCD2Dec(i2c_read(1)));
	*(unsigned char *)ming=(BCD2Dec(i2c_read(1)));
	*(unsigned char *)hourg=(BCD2Dec(i2c_read(0)));
	i2c_stop();	 
}
/*
void rtc_set_time(unsigned char hour, unsigned char min, unsigned char sec){
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x00);

	i2c_write(Dec2BCD(sec));
	i2c_write(Dec2BCD(min));
	i2c_write(Dec2BCD(hour));
	i2c_stop();
}
*/
void rtc_get_date(void *dateg, void *monthg, void *yearg){
	i2c_start();
	i2c_write(0xD0); 
	i2c_write(0x4);

	i2c_start();
	i2c_write(0xD1);
*(unsigned char *)dateg=(BCD2Dec(i2c_read(1)));
*(unsigned char *)monthg=(BCD2Dec(i2c_read(1)));
*(unsigned char *)yearg=(BCD2Dec(i2c_read(0)));
	i2c_stop();
} 
/*
void rtc_set_date(unsigned char date, unsigned char month, unsigned char year){
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x4);

	i2c_write(Dec2BCD(date));
	i2c_write(Dec2BCD(month));
	i2c_write(Dec2BCD(year));
	i2c_stop();
}*/