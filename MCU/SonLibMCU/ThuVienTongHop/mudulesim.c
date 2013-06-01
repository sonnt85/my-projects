char TSMS_PDUMsg[161];
void TextToSMS(void){
	char  shift = 0,c,w,n;
	
	TSMS_PDULen = 0;
	
	for (n=0; n<TSMS_TextLen; ++n){
		c = TSMS_TextMsg[n] & 0x7f;
		c >>= shift;
		w = TSMS_TextMsg[n+1] & 0x7f;
		w <<= (7-shift);
		shift += 1;
		c = c | w;
		if (shift == 7){
			shift = 0x00;
			n++;
		}
		TSMS_PDUMsg[TSMS_PDULen] = c;
		TSMS_PDULen++;
	}
}

/*
**---------------------------------------------------------------------------
**
** Abstract: Convert SMS to text
**
**
** Parameters:
**
**
** Returns:
**
**
**---------------------------------------------------------------------------
*/
char RSMS_TextMsg[161];
void SMSToText(void){
	char  r;
	
	char RSMS_TextLen = 0;
	
	for (r=0; r<RSMS_PDULen; r++){
		if (r%7 == 0){
			RSMS_TextMsg[RSMS_TextLen++] = ( RSMS_PDUMsg[r] << 0 ) & 0x7F;
		}
		else if (r%7 == 6){
			RSMS_TextMsg[RSMS_TextLen++]=((RSMS_PDUMsg[r]<<6)|(RSMS_PDUMsg[r-1]>>2))&0x7F;
			RSMS_TextMsg[RSMS_TextLen++]=(RSMS_PDUMsg[r]>>1)&0x7F;
		}
		else{
			RSMS_TextMsg[RSMS_TextLen++]=((RSMS_PDUMsg[r]<<(r%7))|(RSMS_PDUMsg[r-1]>>(7+1-(r%7))))&0x7F;
		}
	}
}