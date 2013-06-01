#define  interup__c
#include < delay.h >
//static unsigned int demphut;
unsigned char idata demgiay,demtime2;
void ngattime0(void) interrupt TF0_VECTOR{// ngat dung cho dong ho he thong hoi lang phi nhung phai chap nhan 	 
  TR0=0; 
  TH0=trandemphut>>8;
  TL0=trandemphut; 
  TR0=1;//tu luc vao ngat den khi bat lai bi dem TR0mat 10 chu ky may
}
void ngattime2(void) interrupt TF2_VECTOR{ //ham ngat nay 20ms say ra mot lan
                                          //ham nay phuc vu hien thi va kiem tra cac thong so dinh ky 
   TF2=0;// phai xoa co tran do ham ngat ko tu xoa co nay
   EXF2=0;

}
void ngatngoai0(void) interrupt IE0_VECTOR{
//lcd_clr();lcd_puts("ngat ngoai 0");

//longjmp(env,221);
}
void ngatngoai1(void) interrupt IE1_VECTOR{
//longjmp(env,221);
//lcd_clr();lcd_puts("ngat ngoai 1");
}

void ngatnoitiep(void) interrupt SIO_VECTOR{
//lcd_clr();lcd_puts("ngat ngoai noi tiep");

//longjmp(env,221);
}