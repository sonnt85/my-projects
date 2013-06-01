#ifndef  __crc__
#define __crc__     //IBUTTON 0X8C DALLA INIT 0
#define crcxx 16
#define init_crc  0xFFFF
#define CRC_16    0XA001      //bit pattern (1)1000 0000 0000 0101 DISKDRIVER INIT FFFF
#define CRC_CCITT 0X8408      //bit pattern (1)0001 0000 0010 0001 PPP&IRDA INIT FFFF
#define CRC_32    0x04C11DB7L  //bit pattern (1)0000 0100 1100 0001 0001 1101 1011 0111

extern unsigned char generate_8bit_crc(char* poda, unsigned char length, unsigned char pattern);
extern unsigned int generate_16bit_crc(char * poda, unsigned char length, unsigned int pattern);
extern unsigned long generate_32bit_crc(char* poda, unsigned char length, unsigned long pattern);       
#endif