																					 #ifndef __delay__
#define __delay__                                                      
#include <intrins.h>
// sochukycan=a+b*(bienvao)
//a= so chu ky ko nam trong vong lap bao gom loi goi ham, truyen tham so
//b=so chu ky trong 1 vong lap
#define   du       8L                       //a
#define   sochia   8L                      //b

#define   du1       10L                  //a
#define   sochia1   1006L               //b

void delay_bcycle(unsigned char cycle);
void delay_1000cycle();
void delay_n1000cycle(unsigned char reg);

void delay_1ms();
void delay_ms(unsigned int ms);



//#define xtal  18432000L          /* xtal speed */
#define ClockRes (xtal/12L)       /* Clock ticks per second */
#define nscycles (1000000000L / ClockRes)
#define us2cyclesl(x) (((x) / nscycles)*1000L )
#define us2cycles(x) ((1000L * (x)) / nscycles)
#define cycles2us(x) ((nscycles * (x)) / 1000L)

#define nops(x)		                              ( \ 
	(((x) & 1) ? _nop_() : 0),                       \ 
	(((x) & 2) ? _nop_(),_nop_() : 0),                \ 
	(((x) & 4) ? _nop_(),_nop_(),_nop_(),_nop_() : 0), \ 
	(((x) & 8) ? _nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_() : 0))
 //so chu ky <  2052 x don vi la us
#define delay_cycle(x)   \
   (                      \
    ((x))         \
      ?                     \
         (                   \
          (((x)-du)/sochia)?(delay_bcycle(((x)-du)/sochia)):0\
         ),                                                                      \
         (nops(((x)-du)%sochia))                                         \
      : 0                                                                          \
   )      

//#define ndelay_1000cycle(x) delay_1000cycle()
       

#define delay_us(x)            ( \
    (us2cycles(x)<du)             \
       ? nops(x)                   \
       :                            \
        (                            \
          (us2cycles(x)<=2022L)       \
          ? (delay_cycle(us2cycles(x)))\
          : (delay_n1000cycle((us2cycles(x)-du1)/sochia1),delay_cycle((us2cycles(x)-du1)%sochia1))\
        ))

#endif