/////////////////////// Driver to generate CRC //////////////////////////
////                                                                 ////
////  generate_8bit_crc(poda, length, pattern)                       ////
////        Generates 8 bit crc from the poda using the pattern.     ////
////                                                                 ////
////  generate_16bit_crc(poda, length, pattern)                      ////
////        Generates 16 bit crc from the poda using the pattern.    ////
////                                                                 ////
////  generate_32bit_crc(poda, length, pattern)                      ////
////        Generates 32 bit crc from the poda using the pattern.    ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
#include  <allfuntion.h>
#include  <crc.h>
#if (crcxx==8)
unsigned char generate_8bit_crc(char* poda, unsigned char length, unsigned char pattern){
	unsigned char  j,i,crc;
	crc=init_crc;
	for(j=0;j<length;j++)    {
		crc^=poda[j];
		for(i=0;i<8;++i)if(crc&1){crc=(crc>>1)^pattern;}else crc>>=1; 
	}
	return crc;
}
#elif (crcxx==16)
unsigned int generate_16bit_crc(char * poda, unsigned char length, unsigned int pattern){
	unsigned int  crc;
	unsigned char i,j;
	crc=init_crc;
	for(j=0;j<length;j++){
		crc^=poda[j];
		for(i=0;i<8;++i)if(crc&1){crc=(crc>>1)^pattern;}else crc>>=1; 
	}
	return crc;
}
 

#elif (crcxx==32)
unsigned long generate_32bit_crc(char* poda, unsigned char length, unsigned long pattern){
    unsigned char  j,i;
    unsigned long  crc;
    crc=init_crc;
    for(j=0;j<length;j++){
      crc^=poda[j];
      for(i=0;i<8;++i)if(crc&1){crc=(crc>>1)^pattern;}else crc>>=1; 
    }
    return crc;   
}
#else
#endif
