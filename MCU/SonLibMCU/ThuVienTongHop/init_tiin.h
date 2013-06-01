#ifndef  __init_tiin__
#define __init_tiin__
	void	init_tiin();
	unsigned	int	t2capture();//HAM NAY CHUAN 
	void	t2autoreload(unsigned int us);//HAM NAY CHUAN 
	void	ouputtime2f(unsigned long f);
	void	com_init_ti1 (unsigned int baud);//dung time1 //HAM NAY CHUAN 
	void	t2baud(unsigned long baud);//HAM NAY CHUAN
	void	init_time0();
#ifndef init_tiin__c
#else
	#include<THANHSONCHIP.H>
	#include <delay.h>
#endif
#endif