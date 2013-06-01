/***********************************************************************
MODULE		:   UART	 
Chuc nang	:  	Khoi tao ngoai vi va toc do Baud cho UART giua MCU va PC
Tac gia		: 	Bui Trung Hieu - Webmaster: http://www.khvt.com
Su dung		:   Co the su dung voi moi muc dich ma khong can xin phep 
				tac gia ve tac quyen, tac gia khong chiu moi trach nhiem ve 
				cac tac hai gay ra va khong doi hoi cac loi ich co the co
Khoi tao	:	Ngay 31 thang 1 nam 2006 luc 9h15'PM
Hoan thanh	:	Ngay 31 thang 1 nam 2006 luc 10h15'PM

Ghi chu them:	-Modul nay duoc tao ra de tich hop voi ham printf("") san co.
				-Ham ngat dat o bank 0 va khong co uu tien ngat				
***********************************************************************/
#ifndef _UARTH_
#define _UARTH_
/***********************************************************************
Chuc nang	:    Khoi tao UART o mode 1, 
				-Su dung nguon sinh toc do baud la Timer 2
				-BAUDRATE:	 19200
Gia tri tra ve:		Khong co
Luu y		:	De dung ket hop voi ngat uart, phai dat EA=1
************************************************************************/
extern void uart_init(void);

#endif // _UARTH_