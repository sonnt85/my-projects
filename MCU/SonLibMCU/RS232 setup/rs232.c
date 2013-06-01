#include <reg52.h>
#include <stdio.h>

#define    XTAL 12000000	// CPU Oscillator Frequency
#define    baudrate 9600	// 9600 bps communication baudrate

#define    OLEN  8			// kich thuoc bo dem truyen
unsigned   char  ostart;	// chi so bat dau bo dem truyen
unsigned   char  oend;		// chi so cuoi dau bo dem truyen
char idata outbuf[OLEN];	// mang luu bo dem truyen

#define    ILEN  8			// kich thuoc bo dem thu
unsigned   char  istart; 	// chi so dau dau bo dem thu
unsigned   char  iend; 		// chi so cuoi dau bo dem thu
char idata inbuf[ILEN]; 	// mang luu bo dem thu

bit sendfull; 			    // co bao bo dem truyen day
bit sendactive; 			// co bao da truyen du lieu 

/*
 * Xu ly ngat noi tiep
 */
static void com_isr (void) interrupt 4 using 1 {   //ngat thu xong du lieu va ngat phat uart
char c;

/*----- khi thu xong du lieu luu trong sbuff thi co ngat RI bat len-----------------------------------*/
if (RI) {
  c = SBUF; 			       		// doc ky tu thu duoc
  RI = 0; 					   		// xoa co ngat thu do du lieu thu duoc da duoc su ly		
//  if (istart + ILEN != iend) {		//(istart + ILEN)!= iend
	if((istart!=iend+1)&&(istart + ILEN != iend)){
  /* neu do dai du lieu dang co trong bo dem =iend-istart be hon ( khac ILEN) thi ghi c vao bo dem neu khong thi vut du lieu thu duoc*/
  */
 //   inbuf[iend++ & (ILEN-1)] = c; 
	if(iend==ILEN)iend=0;inbuff[iend]=c; iend++;//tro toi tiep theo	
  }	  
}								

/*------ su ly ngat phat. ------------------------------------*/
  if (TI != 0) {
    TI = 0; 								// xoa co ngat phat xong
    if (ostart != oend) { 					// <=>neu co du lieu trong bo dem phat	
    //  SBUF = outbuf[ostart++ & (OLEN-1)]; 	// dat ky tu tiep theo vao bo dem truyen
	  if(ostart==OLEN)ostart=0;SBUF=outbuf[ostart]; ostart++;//tro toi tiep theo
      sendfull = 0; 						// xoa co bao da gui het du lieu (do van dang gui)
    }
    else { 									// neu du lieu da truyen di het
      sendactive = 0; 						// xoa co bao dang gui du lieu (do da het du lieu ostart == oend)
    }
  }
}

/*
 * Function to initialize the serial port and the UART baudrate.
 */
void com_initialize (void) {
  istart = 0; 			         // xoa bo dem phat
  iend = 0;
  ostart = 0; 			         // xoa bo dem thu
  oend = 0;
  sendactive = 0; 			         // xoa co bao dang gui
  sendfull = 0; 			         // xoa co bao gui het du lieu

                                      // Configure timer 1 as a baud rate generator
  PCON |= 0x80; 			         // 0x80=SMOD: set serial baudrate doubler
  TMOD |= 0x20; 			         // put timer 1 into MODE 2
  TH1 = (unsigned char) (256 - (XTAL / (16L * 12L * baudrate)));
  TR1 = 1; 				// start timer 1
  
  SCON = 0x50;			         // serial port MODE 1, enable serial receiver
  ES = 1; 				// enable serial interrupts
}

/*
 ghi ky tu toi thanh ghi phat Sbuf hoac truyen du lieu
 */

void putbuf (char c) {
  if (!sendfull) { 			// truyen ky tu neu bo dem khong day
    if (!sendactive) { 		// neu chua kich hoat truyen du lieu thi gui thang du lieu ko thong qua bo dem
      sendactive = 1; 		// kich hoat truyen du lieu
      SBUF = c; 			// gui du lieu can phat toi thanh ghi SBuf
    }
    else {
      ES = 0; 				// xoa ngat noi tiep khi update du lieu
      outbuf[oend++ & (OLEN-1)] = c; 	// put char to transmission buffer
      if (((oend ^ ostart) & (OLEN-1)) == 0) {	//<=> oend==ostart hoac oend^ostart=0b1000
	     // ostart + ILEN != oend
         sendfull = 1;
      } 				    // bat co sendfull neu bo dem phat day
      ES = 1; 				// ebat co ngat uart
    }
  }
}

/*
 * Replacement routine for the standard library putchar routine.
 * The printf function uses putchar to output a character.
 */

char putchar (char c) {
  if (c == '\n') { 			// expand new line character:
    while (sendfull); 			// wait until there is space in buffer
    putbuf (0x0D); 			// send CR before LF for <new line>
  }
  while (sendfull); 			// wait until there is space in buffer
  putbuf (c); 			         // place character into buffer
  return (c);
}

/*
 * Replacement routine for the standard library _getkey routine.
 * The getchar and gets functions uses _getkey to read a character.
 */

char _getkey (void) {
  char c;
  while (iend == istart); // cho toi khi co du lieu toihoac chinh la cho cho bo dem thuko rong
 
  ES = 0; 				  // tat ngat trong qua trinh lay du lieu tu bo dem
//  c = inbuf[istart++ & (ILEN-1)];  
  if(istart==ILEN)istart=0;
  c=inbuf[istart];
  istart++;
  ES = 1; 				  // bat ngat tro lai
  return (c);
}

/*
 * Main C function that start the interrupt-driven serial I/O.
 */

void main (void) {
  EA = 1;                                      /* enable global interrupts */
  com_initialize ();                           /* initialize interrupt driven serial I/O */
  while (1)   while (1) {
    char c;
    c = getchar ();
    printf ("\nYou typed the character %c.\n", c);
  }
}
