#include  <allfuntion.h>
#include  <sulymangbit.h>

  unsigned char code pobior[8]={1,2,4,8,16,32,64,128}   ; //dung trong set bit phep or
  unsigned char code pobian[8]={~1,~2,~4,~8,~16,~32,~64,~128}   ;  //dung cho xoa bit phep and

unsigned long nbit1positi(unsigned char sobit,vitri)
{
  unsigned char cou;
  unsigned long lval=0;
  for(cou=0;cou<sobit;cou++)
  {
    lval=lval<<1;
    lval=lval|1;
  }
  lval=lval<<vitri;
  return lval;
}

unsigned long nbit0positi(unsigned char sobit,vitri)
{
  return ~nbit1positi(sobit,vitri);
}

	void clearbit(unsigned char idata *mt,vitri)	   //da test
	/* clear bit thu i (>=0) cua mang bit mt[] len muc 1 */
		 {
      mt=mt+vitri/8; //tro vao vi tri byte chua bit cac xoa
      vitri=vitri%8;
			*(mt)=*(mt)&pobian[vitri];	
		 }			  
	void setbit(unsigned char idata*mt,vitri)   //datest
	/* set bit thu i (>=0) cua mang bit mt[] len muc 1 */
		 {
      mt=mt+vitri/8;//tro vao vi tri byte chua bit can set
      vitri=vitri%8;
			*(mt)= *(mt)|pobior[vitri];	
		 }
	bit getbit(unsigned char idata*mt,vitri)	   // da test
	/*lay bit co stt i trong mang bit mt[]*/
		 {
      mt=mt+vitri/8;
      vitri=vitri%8;
			return (*mt)&pobior[vitri];	
 		 }
	unsigned long getbits(unsigned char idata *mt,vitri,sobit)  	 // da test
		/*lay t bit tu mang bit mt[] bat dau tu bit thu i(>=0)*/
		 {	
		    unsigned long getint;
		    mt=mt+vitri/8;
        vitri=vitri%8;
        getint=*mt+(((unsigned long)*(mt+1))<<8)|(((unsigned long)*(mt+2))<<16)|(((unsigned long)*(mt+3))<<24);
        
        
        
        getint=getint<<(31-sobit-vitri);
        getint=getint>>(31-vitri);
        
        return getint;
     }

	void putbits(unsigned char idata *mt,vitri,sobit,unsigned long giatri)// da test  
		/* ghi j bit chua trong x (byte) vao mang bit co mt[] co dia chi bat dau ghi la i*/
		 {
		    unsigned long getint;
		    mt=mt+vitri/8;
        vitri=vitri%8;
         getint=*mt+(((unsigned long)*(mt+1))<<8)|(((unsigned long)*(mt+2))<<16)|(((unsigned long)*(mt+3))<<24);
        
        getint=getint&nbit0positi(sobit,vitri);
        giatri=giatri&nbit1positi(sobit,0);
        giatri=giatri<<vitri;
     
        getint=getint|giatri;
        
        *mt=getint;
        *(mt+1)=getint>>8;
        *(mt+2)=getint>>16;
        *(mt+3)=getint>>24;
     }
