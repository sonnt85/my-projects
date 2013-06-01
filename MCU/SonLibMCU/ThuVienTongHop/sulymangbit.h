#ifndef  __sulymangbit__
#define __sulymangbit__
#ifndef sulymangbit__c
#endif
void setclearbit(void *souce,unsigned char vitri,unsigned char giatri);	   // da test

unsigned long nbit1positi   (unsigned  char  sobit,unsigned char vitri); 

unsigned long nbit0positi(unsigned  char  sobit,unsigned char vitri);

void clearbit(void *souce,unsigned char vitri);	   //da test
/* clear bit thu i (>=0) cua mang bit mt[] len muc 1 */

void setbit(void *souce,unsigned char vitri) ;   //datest
/* set bit thu i (>=0) cua mang bit mt[] len muc 1 */

bit getbit(void *souce,unsigned char vitri);	   // da test
/*lay bit co stt i trong mang bit mt[]*/

void putbits(void *souce,vitri,unsigned char sobit,unsigned long giatri);  	 // da test
	/*lay t bit tu mang bit mt[] bat dau tu bit thu i(>=0)*/

void putbits(void *souce,vitri,unsigned char sobit,unsigned long   giatri);// da test  
	/* ghi j bit chua trong x (byte) vao mang bit co mt[] co dia chi bat dau ghi la i*/
			
#endif
