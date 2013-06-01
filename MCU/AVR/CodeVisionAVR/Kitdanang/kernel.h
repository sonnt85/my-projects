#ifndef _kenel_h
#define _kenel_h
#define     MAX_RAM_ADDRESS      (x045F)  
#define     MAX_TASK             (10)        

#define DEFAULT_SYS_STACK_SIZE  (10)
#define DEFAULT_DATA_STACK_SIZE (20)
#define CYCLE_TICK_US           (10000)

#define     TASK_SUSPEND    (0)                        
#define     TASK_READY      (1)
#define     TASK_WAIT_TIME  (2)
#define     TASK_WAIT_SEMA  (4)
#define     TASK_TIMEOUT    (8)

extern volatile unsigned char _current_task,time_slide;
void _init_rtos();
unsigned int _create_task(unsigned char tsk_no,void (*func)(void),unsigned char sys_size,unsigned char data_size,unsigned char state);
void _run(void);
void _task_delay(unsigned int ticks);
void _task_switch(void);

void _send_semaphore(unsigned char tsk_no,unsigned char param);
unsigned char _wait_semaphore(unsigned int ticks);
unsigned char _query_task();

void _set_task_status(unsigned char state);
void _set_taskn_status(unsigned char taskno, unsigned char state);
#endif 