#ifndef __CRC8_H__
#define __CRC8_H__
void CRC8_InitChecksum( unsigned char *crcvalue );
void CRC8_UpdateChecksum( unsigned char *crcvalue, const void *poda, int length );
void CRC8_FinishChecksum( unsigned char *crcvalue );
unsigned char CRC8_BlockChecksum( const void *poda, int length );

#endif /* !__CRC8_H__ */
