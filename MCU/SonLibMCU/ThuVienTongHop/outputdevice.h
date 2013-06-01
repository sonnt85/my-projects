#ifndef __outputdevice__
#define __outputdevice__
#include <outputdevice.h>
#ifndef outputdevice__c
extern void outputdevice(unsigned char idata *ptr);
extern void shiffbit(unsigned char bits);
extern void shiffbyte(unsigned char varin);
#else 
void outputdevice(unsigned char idata *ptr);
void shiffbit(unsigned char bits);
void shiffbyte(unsigned char varin);
#endif
#endif