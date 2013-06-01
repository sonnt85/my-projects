//---------------------------------------
// DS1307 driver
// KEIL C51 v7.5
// www.GetMicro.com
//---------------------------------------

#ifndef _DS1307_H
#define _DS1307_H

extern unsigned char ReadBYTE(unsigned char Addr);
extern void WriteBYTE(unsigned char Addr,unsigned char Data);
extern void ReadRTC(unsigned char * buff);
extern void WriteRTC(unsigned char * buff);
extern char * Int2Day(unsigned char day);
extern char * Int2Month(unsigned char month);

#endif


