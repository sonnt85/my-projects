#include <mega8.h>
//#include <stdio.h> 
#include <string.h> 
#include "kernel.h"              

volatile unsigned char _index; 
volatile unsigned char* _mem_ptr;
volatile unsigned char _task_count;							
volatile unsigned char _current_task,time_slide;     
volatile unsigned char _task_status[MAX_TASK];
volatile unsigned int  _task_system_stack[MAX_TASK];  
volatile unsigned int  _task_data_stack[MAX_TASK];
volatile unsigned int  _task_tick_count[MAX_TASK];
  
#define _save_context()\   
    #asm ("  PUSH R0   							");\
    #asm ("  PUSH R1   							");\ 
    #asm ("  PUSH R2   							");\ 
    #asm ("  PUSH R3   							");\ 
    #asm ("  PUSH R4   							");\ 
    #asm ("  PUSH R5   							");\ 
    #asm ("  PUSH R6   							");\ 
    #asm ("  PUSH R7   							");\ 
    #asm ("  PUSH R8   							");\ 
    #asm ("  PUSH R9   							");\ 
    #asm ("  PUSH R10   						");\  
    #asm ("  PUSH R11   						");\  
    #asm ("  PUSH R12   						");\  
    #asm ("  PUSH R13   						");\  
    #asm ("  PUSH R14   						");\  
    #asm ("  PUSH R15   						");\  
    #asm ("  PUSH R16   						");\  
    #asm ("  PUSH R17   						");\  
    #asm ("  PUSH R18   						");\  
    #asm ("  PUSH R19   						");\  
    #asm ("  PUSH R20   						");\  
    #asm ("  PUSH R21   						");\  
    #asm ("  PUSH R22   						");\  
    #asm ("  PUSH R23   						");\  
    #asm ("  PUSH R24   						");\  
    #asm ("  PUSH R25   						");\  
    #asm ("  PUSH R26   						");\  
    #asm ("  PUSH R27   						");\  
    #asm ("  PUSH R30   						");\  
    #asm ("  PUSH R31   						");\ 
    #asm ("  IN   R0,SREG                       ");\ 
    #asm ("  PUSH R0    						");\ 
    #asm ("  LDS  R30, __current_task           ");\      				//load direct from ram
    #asm ("  CLR  R31                           ");\
    #asm ("  LSL  R30						    ");\					//logiccal shift left  
    #asm ("  LDI  R26,LOW(__task_system_stack)  ");\ 					//load immediate
    #asm ("  LDI  R27,HIGH(__task_system_stack) ");\
	#asm ("  ADD  R26,R30                       ");\
    #asm ("  ADC  R27,R31                       ");\
    #asm ("  IN   R23,SPL                       ");\
    #asm ("  IN   R24,SPH                       ");\
    #asm ("  ST   X+,R23                        ");\
   	#asm ("  ST   X,R24                         ");\   
    #asm ("  LDI  R26,LOW(__task_data_stack)    ");\
    #asm ("  LDI  R27,HIGH(__task_data_stack)   ");\
	#asm ("  ADD  R26,R30                       ");\
    #asm ("  ADC  R27,R31                       ");\
  	#asm ("  ST   X+,R28                        ");\ 					//store Y (using to transmit parameters for functions)
   	#asm ("  ST   X,R29                         ");                                 
     
#define _restore_context()\   
    #asm (" LDS  R30, __current_task            ");\
    #asm (" CLR  R31                            ");\ 
    #asm (" LSL  R30						    ");\ 
    #asm (" LDI  R26,LOW(__task_data_stack)     ");\
    #asm (" LDI  R27,HIGH(__task_data_stack)    ");\
	#asm (" ADD  R26,R30                        ");\
    #asm (" ADC  R27,R31                        ");\
    #asm (" LD   R28,X+                         ");\
    #asm (" LD   R29,X                          ");\
    #asm (" LDI  R26,LOW(__task_system_stack)   ");\
    #asm (" LDI  R27,HIGH(__task_system_stack)  ");\
	#asm (" ADD  R26,R30                        ");\
    #asm (" ADC  R27,R31                        ");\
    #asm (" LD   R23,X+                         ");\
    #asm (" LD   R24,X                          ");\
    #asm (" OUT  SPL,R23                        ");\
    #asm (" OUT  SPH,R24                        ");\     
    #asm (" POP  R0                             ");\
    #asm (" OUT  SREG, R0                       ");\
    #asm (" POP  R31                            ");\
    #asm (" POP  R30                            ");\
    #asm (" POP  R27                            ");\
    #asm (" POP  R26                            ");\
    #asm (" POP  R25                            ");\
    #asm (" POP  R24                            ");\
    #asm (" POP  R23                            ");\
    #asm (" POP  R22                            ");\
    #asm (" POP  R21                            ");\
    #asm (" POP  R20                            ");\
    #asm (" POP  R19                            ");\
    #asm (" POP  R18                            ");\
    #asm (" POP  R17                            ");\
    #asm (" POP  R16                            ");\
    #asm (" POP  R15                            ");\
    #asm (" POP  R14                            ");\ 
    #asm (" POP  R13                            ");\
    #asm (" POP  R12                            ");\
    #asm (" POP  R11                            ");\ 
    #asm (" POP  R10                            ");\
    #asm (" POP  R9                             ");\
    #asm (" POP  R8                             ");\
    #asm (" POP  R7                             ");\
    #asm (" POP  R6                             ");\
    #asm (" POP  R5                             ");\
    #asm (" POP  R4                             ");\
    #asm (" POP  R3                             ");\
    #asm (" POP  R2                             ");\
    #asm (" POP  R1                             ");\  
    #asm (" POP  R0                             ");     		

#pragma savereg-
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{      
    _save_context();  
 //   TCNT1H=0x00;
//	TCNT1L=0x00;  
    TCNT0=-0x4E;      
    for (_index=0;_index<_task_count;_index++)									//xu ly cac task delay(tick)
    {
    	if (_task_status[_index] & TASK_WAIT_TIME)      						//check task waiting to run 
    	{
    		if (_task_tick_count[_index]) _task_tick_count[_index]--;      		// if timeout then set task to timeout state
    		if (_task_tick_count[_index]==0) _task_status[_index] = (TASK_TIMEOUT|TASK_READY);  
    	}                  
    } 	
    
    _index = 0;
    while (1)
    {
        if (++_current_task >=_task_count) _current_task = 1;					//start finding from task 1 to task n    
        if (_task_status[_current_task] & TASK_READY) break;  					//find a READY task 
        if(++_index > _task_count)                                				 
        {	
        	_current_task = 0;
        	break;	
        }
    }        
    _restore_context();
}           
#pragma savereg+  
                  

void _init_rtos()
{                                                                      
// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 7.813 kHz
    TCCR0=0x05;        // 10ms
    TCNT0=-0x4E;       
	TIMSK!=0x11;       
	          
    // init default state for tasks
    _task_count = 0;    	// notask to run   
    _current_task = 0;
    for (_index=0;_index<MAX_TASK;_index++)
        _task_status[_index] = TASK_SUSPEND; 
    
    // init starting RAM address for allocate system stack and data stack memory    
//   _mem_ptr = (unsigned char*)(R28+R29<<8);	        // store Y into _mem_ptr
#asm (" STS  __mem_ptr, R28            ");
#asm (" STS  __mem_ptr+1, R29           ");
_mem_ptr--;
#asm ("LDI R29,HIGH(0X45F)"); 
#asm ("LDI R28,LOW(0x45F)"); 

}                         

unsigned int _create_task(unsigned char tsk_no,void (*func)(void),unsigned char sys_size,unsigned char data_size,unsigned char state)
{    
    unsigned int i;
    for(i=0;i<(33+sys_size+data_size);i++){
     *(_mem_ptr-i)='@';   
    }           
     *(_mem_ptr--) = (unsigned int)func % 256;  				// task starting address 
     *(_mem_ptr--) = (unsigned int)func >> 8;  
     _mem_ptr-=31;
     memcpyf(_mem_ptr, "NGUYEN_THANH_SON^^DT:0949109985", 31 );         
    _task_system_stack[tsk_no] = (unsigned int)(_mem_ptr--);     
	_mem_ptr -= (sys_size>0)?(sys_size):DEFAULT_SYS_STACK_SIZE; 
    _task_data_stack[tsk_no] = (unsigned int) (_mem_ptr--);
    _mem_ptr -= (data_size>0)?(data_size):DEFAULT_DATA_STACK_SIZE; 
    
    _task_status[tsk_no] = state;
    _task_tick_count[tsk_no] = 0;
    
    tsk_no++;   								// increment this value for task_count
    if (_task_count < tsk_no) _task_count = tsk_no; 
    return 33+(unsigned int)sys_size+data_size;
}

                            
#pragma savereg-    
void _task_switch(void) 
{                        
// register unsigned char _index; 
	#asm("CLI"); 
    _save_context();            
    _index = 0;     															//find a ready task
     while (1)
     {
        if (++_current_task >=_task_count) _current_task = 1;					//start finding from task 1 to task n    
        if (_task_status[_current_task] & TASK_READY) break;  					//find a READY task 
        if(++_index > _task_count)                                				//neu ko thay task nao ready thi chay task idle  
        {	
        	_current_task = 0;
        	break;	
        }
    }        
     
    _restore_context(); 
 	#asm("SEI");       
}         
#pragma savereg+   
 
void _task_delay(unsigned int ticks)
{                 
	#asm("CLI");       
    _task_tick_count[_current_task] = ticks;
    _task_status[_current_task] = TASK_WAIT_TIME;
    _task_switch();     
}

void _run(void)
{    
    _current_task = 1; 
    _restore_context();  
                  
//	TIFR &=(~0x1);			//erase interrupt flag of timer ovt 0
	#asm("RETI") 
}
unsigned char _wait_semaphore(unsigned int ticks){
    if (_task_count){
        #asm("CLI");
        _task_status[_current_task] = TASK_WAIT_SEMA;
        if (ticks){
            _task_tick_count[_current_task] = ticks;
            _task_status[_current_task] |= TASK_WAIT_TIME; 
        }
        _task_switch();
    }
    return _task_status[_current_task]&TASK_TIMEOUT?TASK_TIMEOUT:_task_status[_current_task]>>4;
}
void _send_semaphore(unsigned char tsk_no,unsigned char param){
    if (_task_status[tsk_no]&TASK_WAIT_SEMA){
        _task_status[tsk_no] = param<<4 + TASK_READY;
    }
}

unsigned char _query_task(){
    return _task_status[_current_task] & (~TASK_TIMEOUT);
} 

void _set_task_status(unsigned char state){
    if (_current_task < _task_count){
        #asm("CLI");
        _task_status[_current_task] = state;
        _task_switch(); 
    }
}
void _set_taskn_status(unsigned char taskno, unsigned char state){
    if (taskno < _task_count){
        #asm("CLI");
        _task_status[taskno] = state;
        _task_switch(); 
    }
}
