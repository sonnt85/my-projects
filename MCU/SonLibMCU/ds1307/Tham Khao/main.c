//---------------------------------------
// Example read and write DS1307
// KEIL C51 v7.5
// www.GetMicro.com
//---------------------------------------
#include<reg8252.h>
#include<stdio.h>
#include<ds1307.h>
#include<serial.h>
#include<delay.h>

unsigned char  RTC_ARR[7];  // Buffer for second,minute,.....,year

unsigned char p;

//---------------------------------------
// Main program
//---------------------------------------
void main(void)
{


	InitSerial();  		// Initialize serial port
	
	//printf("%s",&Int2Day(1));

	
	//-----------------------------------
	// Setup time and enable oscillator
	//-----------------------------------
	
	ReadRTC(&RTC_ARR[0]);        
	RTC_ARR[0] = RTC_ARR[0] & 0x7F;	// enable oscillator (bit 7=0)
	RTC_ARR[1] = 0x59;	// minute = 59
	RTC_ARR[2] = 0x23;	// hour = 05 ,24-hour mode(bit 6=0)
	RTC_ARR[3] = 0x04;	// Day = 1 or sunday
	RTC_ARR[4] = 0x31;	// Date = 30
	RTC_ARR[5] = 0x10;	// month = August
	RTC_ARR[6] = 0x05;	// year = 05 or 2005
	WriteRTC(&RTC_ARR[0]);	// Set RTC

	//-----------------------------------
    
	while(1)
	{
		ReadRTC(&RTC_ARR[0]);        
		putchar(0x0C);  // clear Hyper terminal
		printf("Day  : %s\r\n",Int2Day(RTC_ARR[3]));		
        printf("Time : %02bX:%02bX:%02bX\r\n",RTC_ARR[2],RTC_ARR[1],RTC_ARR[0]);	    
		printf("Data : %02bX-%s-20%02bX",RTC_ARR[4],Int2Month(RTC_ARR[5]),RTC_ARR[6]);	    		
		//
		DelayMs(1000);	// delay about 1 second
	}
}


