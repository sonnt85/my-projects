#ifndef  __sulymangbit__
#define __sulymangbit__


unsigned long nbit1positi   (unsigned  char  sobit,vitri); 

unsigned long nbit0positi(unsigned  char  sobit,vitri);

void clearbit(unsigned char idata *mt,vitri);	   //da test
	/* clear bit thu i (>=0) cua mang bit mt[] len muc 1 */

void setbit(unsigned char idata*mt,vitri) ;   //datest
	/* set bit thu i (>=0) cua mang bit mt[] len muc 1 */

bit getbit(unsigned char idata*mt,vitri);	   // da test
	/*lay bit co stt i trong mang bit mt[]*/

void putbits(unsigned char idata *mt,vitri,sobit,unsigned long giatri);  	 // da test
		/*lay t bit tu mang bit mt[] bat dau tu bit thu i(>=0)*/

void putbits(unsigned char idata *mt,vitri,sobit,unsigned long   giatri);// da test  
		/* ghi j bit chua trong x (byte) vao mang bit co mt[] co dia chi bat dau ghi la i*/

#endif
