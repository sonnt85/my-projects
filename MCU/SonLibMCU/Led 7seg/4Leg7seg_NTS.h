#ifndef __4Leg7seg__ 
#define	__4Leg7seg__
#include <REGX52.H>
extern 	void hienthihex	(unsigned int n);
extern  unsigned int   	tobcd(unsigned int n);
#define	portled	P2
#define dosb    P2_7
#define	leddv	P0_4
#define	ledch	P0_5
#define	ledtr	P0_6
#define	ledng	P0_7
#define coso	16
#endif