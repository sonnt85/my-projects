//---------------------------------------
// Delay function
// www.GetMicro.com
//---------------------------------------

//---------------------------------------
// Delay mS function
//---------------------------------------
void DelayMs(unsigned int count) 
{  // mSec Delay 11.0592 Mhz 
    unsigned int i;		       		// Keil v7.5a 
    while(count) 
	{
        i = 115; 
		while(i>0) i--;
        count--;
    }
}


//----------------------------------------
// DELAY at 11.0592MHz crystal.
// Calling the routine takes about 22us, and then
// each count takes another 17us.
// test with KEIL C51 V7.5
//----------------------------------------
void DelayUs(int us)
{
	int i;
	for (i=0; i<us; i++);
}



