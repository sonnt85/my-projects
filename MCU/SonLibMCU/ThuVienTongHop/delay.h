#ifndef __delay__
#define __delay__                                                      
#include <intrins.h> //co lenh nop
//sochukycan=a+b*(bienvao)
//a= so chu ky ko nam trong vong lap bao gom loi goi ham, truyen tham so
//b=so chu ky trong 1 vong lap
#define		du		8L                       //a
#define		sochia	8L                      //b

#define		du1		10L                  //a
#define		sochia1	1006L               //b

#ifndef	delay__c
#endif 
//MACCRO CAC HANG SO LIEN QUAN DEN THOI GIAN
#if modex2==2
  #define delaytime2us      25000     //khoang thoi gian tran cho time 2 autoload 50ms
  #define cou1min (2000L)      //mac dinh chon 1000
#else
  #define delaytime2us      50000//khoang thoi gian tran cho time 2 autoload 50ms
  #define cou1min (1000L)      //mac dinh chon 1000
#endif

#define unittioutms_g         5000       //khoang thoi gian check dinh ky time out moi thu 5s
#define unittioutms(i)       ((i)/(delaytime2us/1000))//i thuong chon bang  unittioutms_g
#define tioums(ms)           (-(ms)/unittioutms_g)          
#define ndelaytime2usms(ms)  ((ms)/(delaytime2us/1000))
#define  cou1sec      (1000000L/cycles2us(-trandemphut))
#define  trandemphut  ((-us2cycles(60000000L-cycles2us(18)))/cou1min)

//MACRO CHUYEN DOI CHU KY SANG THOI GIAN VA NGUOC LAI
void delay_bcycle(unsigned char cycle);
void delay_1000cycle();
void delay_n1000cycle(unsigned char reg);
void delay_1ms();
void delay_ms(unsigned int ms);

#define ClockRes ((xtal*modex2)/(12))       /* Clock ticks per second tang khi tan so tang*/
#define nscycles (1000000000L / ClockRes)  //so nanogiay khi qua 1 chu ky giam khi tan so tang

#define us2cycles(x)   \
(((x) < (0xFFFFFFFFL/1000L)) ? ((1000L * (x)) / nscycles) : (((x) / nscycles )*1000L ))


#define cycles2us(x) \
(((x) < (0XFFFFFFFFL/nscycles)) ? ((x)*nscycles / 1000L) : (((x) / 1000L)*nscycles) )

#define nops(x)		                              ( \ 
	(((x) & 1) ? _nop_() : 0),                       \ 
	(((x) & 2) ? _nop_(),_nop_() : 0),                \ 
	(((x) & 4) ? _nop_(),_nop_(),_nop_(),_nop_() : 0), \ 
	(((x) & 8) ? _nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_() : 0))
 //so chu ky <  2052 x don vi la us

#define delay_cycle(x)   \
   (                      \
    ((x))                  \ 
      ?                     \
         (                   \
          (((x)-du)/sochia)?(delay_bcycle(((x)-du)/sochia)):0\
         ),                                                                      \
         (nops(((x)-du)%sochia))                                                  \
      : 0                                                                          \
   )      
#define   x_c(x)   (x)
#define delay_us(x)            ( \
    (us2cycles(x_c(x))<du)        \
       ? nops(us2cycles(x_c(x)))   \
       :                            \
        (                            \
          (us2cycles(x_c(x))<=2022L)       \
          ? (delay_cycle(us2cycles(x_c(x))))\
          : (delay_n1000cycle((us2cycles(x_c(x))-du1)/sochia1),delay_cycle((us2cycles(x_c(x))-du1)%sochia1))\
        ))

#endif