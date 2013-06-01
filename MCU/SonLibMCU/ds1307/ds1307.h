#ifndef __ds1307__
#define __ds1307__
void rtc_init(unsigned char rs, unsigned char sqwe, unsigned char out) ;
void rtc_get_time(void *hour, void *min, void *sec)	 ;
void rtc_set_time(unsigned char hour, unsigned char min, unsigned char sec)		 ;
void rtc_get_date(void *date, void *month, void *year) ; 
void rtc_set_date(unsigned char date, unsigned char month, unsigned char year)	  ;
#endif