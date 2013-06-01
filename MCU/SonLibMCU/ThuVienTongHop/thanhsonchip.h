/*--------------------------------------------------------------------------
P89V51Rx2.H
Registers definition for Philips P89V51Rx2

Copyright (c) 2007 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
------------------------------------------------------------------------ */
#ifndef  __thanhsonchip__
#define __thanhsonchip__
/* Byte Addresses */
sfr   P0   	 = 0x80;
sfr   SP   	 = 0x81;
sfr   DPL   	 = 0x82;
sfr   DPH   	 = 0x83;
sfr   WDTD   	 = 0x85;
sfr   SPDAT   	 = 0x86;
sfr   PCON   	 = 0x87;
sfr   TCON   	 = 0x88;
sfr   TMOD   	 = 0x89;
sfr   TL0   	 = 0x8A;
sfr   TL1   	 = 0x8B;
sfr   TH0   	 = 0x8C;
sfr   TH1   	 = 0x8D;
sfr   AUXR   	 = 0x8E;
sfr   P1   	 = 0x90;
sfr   SCON   	 = 0x98;
sfr   SBUF   	 = 0x99;
sfr   P2   	 = 0xA0;
sfr   AUXR1   	 = 0xA2;
sfr   IE   	 = 0xA8;
sfr   SADDR   	 = 0xA9;
sfr   SPCFG   	 = 0xAA;
sfr   P3   	 		= 0xB0;
sfr   FCF   	 = 0xB1;
sfr   FST   	 = 0xB6;
sfr   IP0H   	 = 0xB7;
sfr   IP0   	 = 0xB8;
sfr   SADEN   	 = 0xB9;
sfr   WDTC   	 = 0xC0;
sfr   T2CON   	 = 0xC8;
sfr   T2MOD   	 = 0xC9;
sfr   RCAP2L   	 = 0xCA;
sfr   RCAP2H   	 = 0xCB;
sfr   TL2   	 = 0xCC;
sfr   TH2        = 0xCD;
sfr   PSW   	 = 0xD0;
sfr   SPCTL   	 = 0xD5;
sfr   CCON   	 = 0xD8;
sfr   CMOD   	 = 0xD9;
sfr   CCAPM0   	 = 0xDA;
sfr   CCAPM1   	 = 0xDB;
sfr   CCAPM2   	 = 0xDC;
sfr   CCAPM3   	 = 0xDD;
sfr   CCAPM4   	 = 0xDE;
sfr   ACC   	 = 0xE0;
sfr   IEN1   	 = 0xE8;
sfr   CL   	 = 0xE9;
sfr   CCAP0L   	 = 0xEA;
sfr   CCAP1L   	 = 0xEB;
sfr   CCAP2L   	 = 0xEC;
sfr   CCAP3L   	 = 0xED;
sfr   CCAP4L   	 = 0xEE;
sfr   B   	 = 0xF0;
sfr   IP1H   	 = 0xF7;
sfr   IP1   	 = 0xF8;
sfr   CH   	 = 0xF9;
sfr   CCAP0H   	 = 0xFA;
sfr   CCAP1H   	 = 0xFB;
sfr   CCAP2H   	 = 0xFC;
sfr   CCAP3H   	 = 0xFD;
sfr   CCAP4H   	 = 0xFE;
sfr   WDTRST  =0xA6   ;// viet 1E roi sau do viet E1 vao thanh ghi nay thi se thiet lap kich hoat Wadog //8191  hu ky se reset 1 lan voi 52
/*------------------------------------------------
P0 Bit Registers
------------------------------------------------*/
sbit P0_0 = 0x80;
sbit P0_1 = 0x81;
sbit P0_2 = 0x82;
sbit P0_3 = 0x83;
sbit P0_4 = 0x84;
sbit P0_5 = 0x85;
sbit P0_6 = 0x86;
sbit P0_7 = 0x87;

/*------------------------------------------------
/*------------------------------------------------
P1 Bit Registers
------------------------------------------------*/
sbit P1_0 = 0x90;
sbit P1_1 = 0x91;
sbit P1_2 = 0x92;
sbit P1_3 = 0x93;
sbit P1_4 = 0x94;
sbit P1_5 = 0x95;
sbit P1_6 = 0x96;
sbit P1_7 = 0x97;
sbit T2   = 0x90;       /* External input to Timer/Counter 2, clock out */
/*------------------------------------------------
P2 Bit Registers
------------------------------------------------*/
sbit P2_0 = 0xA0;
sbit P2_1 = 0xA1;
sbit P2_2 = 0xA2;
sbit P2_3 = 0xA3;
sbit P2_4 = 0xA4;
sbit P2_5 = 0xA5;
sbit P2_6 = 0xA6;
sbit P2_7 = 0xA7;
/*------------------------------------------------/*------------------------------------------------
P3 Bit Registers (Mnemonics & Ports)
------------------------------------------------*/
sbit P3_0 = 0xB0;
sbit P3_1 = 0xB1;
sbit P3_2 = 0xB2;
sbit P3_3 = 0xB3;
sbit P3_4 = 0xB4;
sbit P3_5 = 0xB5;
sbit P3_6 = 0xB6;
sbit P3_7 = 0xB7;
/* Bit Addresses 

TMOD Bit Values
------------------------------------------------*/
#define T0_M0_   0x01
#define T0_M1_   0x02
#define T0_CT_   0x04
#define T0_GATE_ 0x08
#define T1_M0_   0x10
#define T1_M1_   0x20
#define T1_CT_   0x40
#define T1_GATE_ 0x80

#define T1_MASK_ 0xF0
#define T0_MASK_ 0x0F

/*------------------------------------------------
PCON Bit Values
------------------------------------------------*/
#define IDL_    0x01  //set bit nay thi chip di vao ilde

#define STOP_   0x02  //set bit nay chip se di vao powdown
#define PD_     0x02    /* Alternate definition */

#define POF_    0x10  //co nay bat khi mat dien powerup, ko bi set khi reset..vv..xoa bang mem
#define GF1_    0x08
#define SMOD_   0x80 //smod=1 thi toc do baud tang len 2 lan


#define  disale_  0x1   //=0(mac dinh) chan ale luon co xung ra 1/6 chu ky may
#define  disrto_  0x8   //tat(1) bat(0 mac dinh) tinh nag reset chan reset 
#define  wdidle_  0x10  //=0(mac dinh) bo wadog van hoat dong trong idle
/*=====================================================/
/*FST Bit values*/
//#define  EDC_    0x08 //set=1 thi double clock
/*AUX Bit values  */
/* bit AUXR */
#define   AO   	     0x1
#define   EXTRAM   	 0x2
/*AUX1 Bit values  */
#define IDSP_     4//=0 cho phep dao bit dsp khi tang thanh ghi aux1 (thay doi con tro)
#define DSP_      1 //=1 truy cap ram ngoai mac dinh bang 0 truy cap 768byte ram trong cai nay ko quan tam vi trinh dich se lam cho minh

/* TCON */
sbit   IT0   	 = TCON^0;
sbit   IE0   	 = TCON^1;
sbit   IT1   	 = TCON^2;
sbit   IE1   	 = TCON^3;
sbit   TR0   	 = TCON^4;
sbit   TF0   	 = TCON^5;
sbit   TR1   	 = TCON^6;
sbit   TF1   	 = TCON^7;

/* P1 */
sbit   T2EX   	 = P1^1;
sbit   ECI   	   = P1^2;
sbit   CEX0   	 = P1^3;
sbit   CEX1   	 = P1^4;
sbit   CEX2   	 = P1^5;
sbit   CEX3   	 = P1^6;
sbit   CEX4   	 = P1^7;

/* SCON */
sbit   RI   	 = SCON^0;
sbit   TI   	 = SCON^1;
sbit   RB8   	 = SCON^2;
sbit   TB8   	 = SCON^3;
sbit   REN   	 = SCON^4;
sbit   SM2   	 = SCON^5;
sbit   SM1   	 = SCON^6;
sbit   SM0   	 = SCON^7;


/* IE */
sbit   EX0   	 = IE^0;
sbit   ET0   	 = IE^1;
sbit   EX1   	 = IE^2;
sbit   ET1   	 = IE^3;
sbit   ES0   	 = IE^4;
sbit   ES   	 = IE^4;//cho phep ngat noi tiep
sbit   ET2   	 = IE^5;
sbit   EC   	 = IE^6;
sbit   EA   	 = IE^7;

/* P3 */
sbit   RxD   	 = P3^0;
sbit   TxD   	 = P3^1;
sbit   INT0   	 = P3^2;
sbit   INT1   	 = P3^3;
sbit   T0   	 = P3^4;
sbit   T1   	 = P3^5;
sbit   WR   	 = P3^6;
sbit   RD   	 = P3^7;

/* IP0 */
sbit   PX0   	 = IP0^0;
sbit   PT0   	 = IP0^1;
sbit   PX1   	 = IP0^2;
sbit   PT1       = IP0^3;
sbit   PS   	 = IP0^4;
sbit   PT2   	 = IP0^5;
sbit   PPC   	 = IP0^6;

/* WDTC */
sbit   SWDT   	 = WDTC^0;
sbit   WDT   	   = WDTC^1;
sbit   WDTS   	 = WDTC^2;
sbit   WDRE   	 = WDTC^3;
sbit   WDOUT   	 = WDTC^4;


/* T2CON */
sbit   RL2   	 = T2CON^0;
sbit   C_T2   	 = T2CON^1;
sbit   TR2   	 = T2CON^2;
sbit   EXEN2   	 = T2CON^3;
sbit   TCLK   	 = T2CON^4;
sbit   RCLK   	 = T2CON^5;
sbit   EXF2   	 = T2CON^6;
sbit   TF2   	 = T2CON^7;
/*T2MOD Bit Values
------------------------------------------------*/
#define DCEN_   0x01    /* 1=Timer 2 can be configured as up/down counter */
#define T2OE_   0x02    /* Timer 2 output enable */

/*------------------------------------------------
/* PSW */
sbit   P   	 = PSW^0;
sbit   F1   	 = PSW^1;
sbit   OV   	 = PSW^2;
sbit   RS0   	 = PSW^3;
sbit   RS1   	 = PSW^4;
sbit   F0   	 = PSW^5;
sbit   AC   	 = PSW^6;
sbit   CY   	 = PSW^7;

/* CCON */
sbit   CCF0   	 = CCON^0;
sbit   CCF1   	 = CCON^1;
sbit   CCF2   	 = CCON^2;
sbit   CCF3   	 = CCON^3;
sbit   CCF4   	 = CCON^4;
sbit   CR   	 = CCON^6;
sbit   CF   	 = CCON^7;

/* IEN1 */
sbit   EBO   	 = IEN1^3;

/* IP1 */
sbit   PBO   	 = IP1^3;

/*Interrupt Vectors:
Interrupt Address = (Number * 8) + 3
------------------------------------------------*/
#define IE0_VECTOR	0  /* 0x03 External Interrupt 0 */
#define TF0_VECTOR	1  /* 0x0B Timer 0 */
#define IE1_VECTOR	2  /* 0x13 External Interrupt 1 */
#define TF1_VECTOR	3  /* 0x1B Timer 1 */
#define SIO_VECTOR	4  /* 0x23 Serial port */

#define TF2_VECTOR	5  /* 0x2B Timer 2 */
#define EX2_VECTOR	5  /* 0x2B External Interrupt 2 */

#endif