//---------------------------------------
// Serial prt driver
// KEIL C51 v7.5
// www.GetMicro.com
//---------------------------------------
#include<reg8252.h>


//---------------------------------------
// Initialize serial port
//---------------------------------------
void InitSerial(void)
{
  	SCON = 0x52;    // setup serial port control 
  	TMOD = 0x20;    // hardware (9600 BAUD @11.05592MHZ) 
  	TH1  = 0xFD;    // TH1
	TR1	 = 1;  		// Timer 1 on
}


