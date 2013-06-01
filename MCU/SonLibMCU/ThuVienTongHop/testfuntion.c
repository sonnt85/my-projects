#define  testfuntion__c
#include  <allfuntion.h>
#include <typedef.h>
#include  <testfuntion.h >
/*#define va_start(ap,v) ap = (va_list)&v + sizeof(v)
#define va_arg(ap,t) (((t *)ap)++[0])
#define va_end(ap)
*/
/*void error (char *fmt, ...) {
  va_list arg_ptr;
  va_start (arg_ptr, fmt); //format string arg_ptr=(va_list)&fmt+sizeof(v), con tro tro toi phan tiep theo 
  vprintf (fmt, arg_ptr);
  va_end (arg_ptr);
}*/
void testfuntion(){
char temp=0xf8;
uchar uh;
uh=temp;
printf("Test So Co Dau temp=%#Bd\n",temp<<1);
printf("Sizeof(NULL)=%u\nGia tri cua con tro NULL=%p\n",(uint)sizeof(NULL),NULL);
printf("Trang thai PCON: %#Bx\n",'3');
printf("Dung luong bo nho eeprom: %u Byte\n",(uint)sizeeeprom);
printf("Sobyte Eeprom su dung: %u Byte\n",(uint)adee_khac(0));
printf("Sobyte Eeprom con trong: %u Byte\n",(uint)(sizeeeprom-adee_khac(0)));
printf("Kich thuoc luu tru 1 thiet bi: %u Byte\n",(uint)(adee_thietbi(1)-adee_thietbi(0)));
printf("So thiet bi trong he thong quan ly: %u\n",(uint)sothietbi);
printf("So tang quy doi=%u\n",(uint)sotang);
printf("So thiet bi con co the quan ly them: %u\n",(uint)((sizeeeprom-adee_khac(0))/(adee_thietbi(1)-adee_thietbi(0))));
printf("Tong so thiet bi co the quan ly duoc: %u\n",(uint)(sothietbi+((sizeeeprom-adee_khac(0))/(adee_thietbi(1)-adee_thietbi(0)))));
}