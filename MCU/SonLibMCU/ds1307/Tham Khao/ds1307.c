//---------------------------------------
// DS1307 driver
// www.GetMicro.com
//---------------------------------------
#include<reg8252.h>
#include<delay.h>
#include<intrins.h>

#define ACK		1
#define NO_ACK	0
#define SLAVE	0xD0
#define WRITE   0x00
#define READ    0x01
#define ERR_ACK 0x01


unsigned char i;

const unsigned char * DayStr[7]  =     {{"Sun"},
				   						{"Mon"},
				   						{"Tue"},
				   						{"Wen"},
				   						{"The"},
				   						{"Fri"},
				   						{"Sat"}};


const unsigned char * MonthStr[12]    ={{"Jan"},
										{"Feb"},
										{"Mar"},
										{"Apr"},
										{"May"},
										{"Jun"},
										{"Jul"},
										{"Aug"},
										{"Sep"},
										{"Oct"},
										{"Nov"},
										{"Dec"}};


sbit SDA  =  P2^1;	// connect to SDA pin (Data)
sbit SCL  =  P2^0;	// connect to SCL pin (Clock)



//-------------------------------
// Convert BCD 1 byte to HEX 1 byte
//-------------------------------
unsigned char BCD2HEX(unsigned int bcd)
{
	unsigned char temp;
	temp=((bcd>>8)*100)|((bcd>>4)*10)|(bcd&0x0f);
	return temp;
	
}

//-------------------------------
// start I2C
//-------------------------------
void Start(void)
{
    SDA = 1;
	SCL = 1;
	_nop_();_nop_();
	SDA = 0;
	_nop_();_nop_();
	SCL = 0;
	_nop_();_nop_();
}

//-------------------------------
// stop I2C
//-------------------------------
void Stop(void)
{
	SDA = 0;	    	
	_nop_();_nop_();
	SCL = 1;
	_nop_();_nop_();
	SDA = 1;	
}

//-------------------------------
// Write I2C
//-------------------------------
void WriteI2C(unsigned char Data)
{    

	for (i=0;i<8;i++)
	{
        SDA = (Data & 0x80) ? 1:0;
		SCL=1;SCL=0;
		Data<<=1;
	}

  	SCL = 1; 
	_nop_();_nop_();
	SCL = 0;

}

//-------------------------------
// Read I2C
//-------------------------------
unsigned char ReadI2C(bit ACK_Bit)
{
    
    unsigned char Data=0;

    SDA = 1;	
	for (i=0;i<8;i++)
	{
		SCL   = 1;		
		Data<<= 1;
		Data  = (Data | SDA);		
		SCL   = 0;
		_nop_();
	}
    
 	if (ACK_Bit == 1)
	SDA = 0; // Send ACK		
	else		
	SDA = 1; // Send NO ACK				

	_nop_();_nop_();
	SCL = 1;		
	_nop_();_nop_();
	SCL = 0;
	
	return Data;
}

//-------------------------------
// Read 1 byte form I2C
//-------------------------------
unsigned char ReadBYTE(unsigned char Addr)
{
   	unsigned char Data;
	Start();
	WriteI2C(0xD0);
	WriteI2C(Addr);
	Start();
	WriteI2C(0xD1);
	Data = ReadI2C(NO_ACK);
	Stop();
   	return(Data);
}

//-------------------------------
// Write 1 byte to I2C
//-------------------------------
void WriteBYTE(unsigned char Addr,unsigned char Data)
{
	Start();
	WriteI2C(0xD0);
	WriteI2C(Addr);
	WriteI2C(Data);
	Stop();	
}

//-------------------------------
// Read RTC (all real time)
//-------------------------------
void ReadRTC(unsigned char * buff)
{
	
	
	Start();
	WriteI2C(0xD0);
	WriteI2C(0x00);

	Start();
	WriteI2C(0xD1);	
	*(buff+0)=ReadI2C(ACK);	// Second
	*(buff+1)=ReadI2C(ACK);	// Minute
	*(buff+2)=ReadI2C(ACK);	// hour
	*(buff+3)=ReadI2C(ACK);	// Day
	*(buff+4)=ReadI2C(ACK);	// date
	*(buff+5)=ReadI2C(ACK);	// month
	*(buff+6)=ReadI2C(NO_ACK);	// year
	Stop();		
}

//-------------------------------
// Write RTC
//-------------------------------
void WriteRTC(unsigned char *buff)
{

	Start();
	WriteI2C(0xD0);
	WriteI2C(0x00);	
	WriteI2C(*(buff+0));	
	WriteI2C(*(buff+1));
	WriteI2C(*(buff+2));
	WriteI2C(*(buff+3));
	WriteI2C(*(buff+4));
	WriteI2C(*(buff+5));
	WriteI2C(*(buff+6));	
	Stop();	
}

//-------------------------------
// Convert date (BCD) to string of Day
// 1=Sanday
// 2=Monday
// And so on
//------------------------------- 
char * Int2Day(unsigned char day)
{
	return DayStr[day-1];
}

//-------------------------------
// Convert month (BCD) to string of Month
// 0x01=January
// 0x02=February
// ...........
// 0x12 = December
// And so on
//------------------------------- 
char * Int2Month(unsigned char month)
{
  return MonthStr[BCD2HEX(month)-1];
}
