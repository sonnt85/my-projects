#ifndef __CRC16_H__
#define __CRC16_H__

/*
===============================================================================

	Calculates a checksum for a block of data
	using the CCITT standard CRC-16.

===============================================================================
*/

void CRC16_InitChecksum( unsigned int *crcvalue );
void CRC16_UpdateChecksum( unsigned int *crcvalue, unsigned char *poda, uchar length );
void CRC16_FinishChecksum( unsigned int *crcvalue );
unsigned int CRC16_BlockChecksum( unsigned char *poda, uchar length );

#endif /* !__CRC16_H__ */
