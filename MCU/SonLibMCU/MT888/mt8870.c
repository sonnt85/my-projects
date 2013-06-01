				 
;#include <REGX52.H>

    STD       EQU    P3.0    ;DTMF OUTPUT; nhan biet da co phim duoc bam
    Q3        EQU    P3.1
    Q2        EQU    P3.2
    Q1        EQU    P3.3
    Q0        EQU    P3.4
    
    RING     EQU     P3.5    ; dung ngat neu co chuong thi tu nhac may,code nay chua

    DIS_A    EQU    P2.0    
    DIS_B    EQU    P2.1
    DIS_C    EQU    P2.2
    DIS_D    EQU    P2.3
    DIS_E    EQU    P2.4
    DIS_F    EQU    P2.5
    DIS_G    EQU    P2.6
	Dot_G    equ    p2.7
                              
DSEG         ; This is internal data memory
ORG     20H     ; Bit adressable memory

   DTMF:  DS  1
    D0    BIT    DTMF.0
    D1    BIT    DTMF.1
    D2    BIT    DTMF.2
    D3    BIT    DTMF.3    
CSEG        
 
;---------==========----------==========---------=========-- -------
;                PROCESSOR INTERRUPT AND RESET VECTORS  
;---------==========----------==========---------=========-- -------
 
    ORG     00H    ; Reset
       MOV SP,#60H ; Thay doi vi tri con tro stack
       MOV R2,#15H
       CALL DISP    ;Display - symbol on display
       SETB STD    ;Make STD pin as input
          
TOP:    
    JNB  STD,$    ;wait for new data
    CALL READ    ;Read Data
    MOV  R2,DTMF                
    CALL DISP    ;Display Dialled Data
    JB   STD,$        ;Wait until the key is released
    AJMP TOP    ;Repeat the function                    
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;        READ DTMF TONES
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        
READ:
    MOV  DTMF,#00H
    SETB Q0
    SETB Q1
    SETB Q2
    SETB Q3

    JNB  Q0,VB1
    SETB D0
VB1:    JNB Q1,VB2
    SETB D1        
VB2:    JNB Q2,VB3
    SETB D2
VB3:    JNB Q3,VB4
    SETB D3
VB4:    RET        
;&&&&&&&&&&&& ;&&&&&&&&&&&& ;&&&&&&&&&&&& ;&&&&&&&&&&&& ;&&&&&&&& 
;     7 SEGMENT DISPLAY ROUTINE
;&&&&&&&&&&&& ;&&&&&&&&&&&& ;&&&&&&&&&&&& ;&&&&&&&&&&&& ;&&&&&&&& 
DISP:
    CJNE R2,#00H,AAS1
    CLR DIS_A
    CLR DIS_B
    CLR DIS_C
    CLR DIS_D
    CLR DIS_E
    CLR DIS_F
    SETB DIS_G
    RET
 AAS1:   
    RET
;**********************************************************& nbsp;   
    END
