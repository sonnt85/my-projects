   #ifndef __MT888__
   #define  __MT888__
#define Data_MT     P2 // 4bit cao

//#define  dgbitthap
#ifdef  dgbitthap
	#define Mark_MT		0xF0  	 
	#define datain(x)   (x=Data_MT)
	#define dataout(x)  (Data_MT=(Data_MT&Mark_MT)|(x&(~Mark_MT)))
#else
	#define Mark_MT		0x0F
	#define datain(x)   (x=Data_MT>>4)	
	#define dataout(x)  (Data_MT=(Data_MT&Mark_MT)|((x<<4)&(~Mark_MT)))
#endif

#define	Phi_MT		P0_4  // ok Chinh  la RD trong MT8888 chuyen dung 8051
#define RS0_MT		P0_5		//ok
#define RW_MT  		P0_7			//ok
#define CS_NMT  	P0_7			  //ok thua
#define IRQ_NMT  	P0_6
   extern  void Number2bcd(unsigned char *tpr,scs,unsigned long x);
   extern  void tranmis1diDTMF(unsigned char so);
   extern  void tranmisDTMF(unsigned long digi,unsigned char scs);
   extern  void setup_MT(unsigned char crab);
   extern  void int_MT();

   #endif