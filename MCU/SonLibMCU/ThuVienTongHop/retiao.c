#define  retiao__c
#include  <retiao.h >
void retiao(){
    #pragma asm
    sjmp backupaddlongjmp;
    goiretiao:
    reti;
    backupaddlongjmp:
    acall goiretiao;
    #pragma endasm;
}