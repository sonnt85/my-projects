#include <reg52.h>
#include <stdio.h>

#define    XTAL 11059200 		         // CPU Oscillator Frequency
#define    baudrate 9600 		         // 9600 bps communication baudrate

#define    OLEN  4 			// size of serial transmission buffer
unsigned   char  ostart; 		         // transmission buffer start index
                                     // ostart++ & (OLEN-1) xoa va tang boi ham nay o phuc vu ngat
unsigned   char  oend; 		         // transmission buffer end index
                                    //oend++ & (OLEN-1) xoa va tang boi ham nay trong ham putbuf
char idata outbuf[OLEN];	 	         // storage for transmission buffer

#define    ILEN  4 			// size of serial receiving buffer
unsigned   char  istart; 		         // receiving buffer start index
                                     //(istart + ILEN != iend) xoa va tang boi ham nay trong phuc vu ngat
unsigned   char  iend; 		         // receiving buffer end index
                                   //[iend++ & (ILEN-1)] xoa va tang boi ham nay trong phuc vu ngat
char idata inbuf[ILEN]; 		         // storage for receiving buffer

bit sendfull; 			         // flag: marks transmit buffer full
                              //ostart != oend la chua full kiem tra bang ham ngat
                              //set boi ham putbuf xoa boi ham ngat moi khi gui 1 kytu thi buff het full
bit sendactive; 			         // flag: marks transmitter active
                                //co nay xoa khi ostart == oend, kiem tra bang ham nggat
/*
 * Serial Interrupt Service Routine
 */
static void com_isr (void) interrupt 4 using 1 {
char c;

/*----- Received data interrupt. ----------------------------------------*/
if (RI) {
  c = SBUF; 			          // read character
  RI = 0; // clear interrupt request flag
  if (istart + ILEN != iend) {
    inbuf[iend++ & (ILEN-1)] = c; 	          // but character into buffer
  }
}

/*------ Transmitted data interrupt. ------------------------------------*/
  if (TI != 0) {
    TI = 0; 				// clear interrupt request flag
    if (ostart != oend) { 		         // if characters in buffer and
      SBUF = outbuf[ostart++ & (OLEN-1)]; 	// transmit character
      sendfull = 0; 			// clear 'sendfull' flag
    }
    else { 				// if all characters transmitted
      sendactive = 0; 			// clear 'sendactive'
    }
  }
}

/*
 * Function to initialize the serial port and the UART baudrate.
 */
void com_initialize (void) {
  istart = 0; 			         // empty transmit buffers
  iend = 0;
  ostart = 0; 			         // empty transmit buffers
  oend = 0;
  sendactive = 0; 			         // transmitter is not active
  sendfull = 0; 			         // clear 'sendfull' flag

                                              // Configure timer 1 as a baud rate generator
  PCON |= 0x80; 			         // 0x80=SMOD: set serial baudrate doubler
  TMOD |= 0x20; 			         // put timer 1 into MODE 2
  TH1 = (unsigned char) (256 - (xtal / (16L * 12L * baudrate)));
  TR1 = 1; 				// start timer 1
  
  SCON = 0x50;			         // serial port MODE 1, enable serial receiver
  ES = 1; 				// enable serial interrupts
}

/*
 * putbuf: write a character to SBUF or transmission buffer
 */

void putbuf (char c) {
  if (!sendfull) { 			// transmit only if buffer not full
    if (!sendactive) { 		         // if transmitter not active:
      sendactive = 1; 			// transfer first character direct
      SBUF = c; 			         // to SBUF to start transmission
    }
    else {
      ES = 0; 				// disable serial interrupts during buffer update
      outbuf[oend++ & (OLEN-1)] = c; 	// put char to transmission buffer
      if (((oend ^ ostart) & (OLEN-1)) == 0) {
         sendfull = 1;
      } 				         // set flag if buffer is full
      ES = 1; 				// enable serial interrupts again
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
  while (iend == istart) {
     ; 				         // wait until there are characters
  }
  ES = 0; 				// disable serial interrupts during buffer update
  c = inbuf[istart++ & (ILEN-1)];
  ES = 1; 				// enable serial interrupts again
  return (c);
}

/*
 * Main C function that start the interrupt-driven serial I/O.
 */

void main1 (void) {									 "\nYou typed the character %c.\n"
  EA = 1;                                      /* enable global interrupts */
  com_initialize ();                           /* initialize interrupt driven serial I/O */
  while (1) {
    char c;
    c = getchar ();
    printf (, c);
  }
}
