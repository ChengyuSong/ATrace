#ifndef SYSCALL_H
#define SYSCALL_H

#include "cpu.h"
#include "qemu-common.h"
#include "hashtable.h"
#include "params.h"

enum syscall_notification_type {
   SYSCALL_CALL,
   SYSCALL_RET
};

struct syscall_info {
   /* syscall number */
   uint16_t number;

   /* the hardware id of a process
    *
    * e.g. cr3, the page directory address on x86,
    * can uniquely identify a running process 
    */
   unsigned long hid;
   
   /* the software id of the process executing the call */
   unsigned int pid;

   /* thread id of the executing thread */
   unsigned int tid;
   
   /* process name as a string */
   /* we have less than a page of memory to work with, so we might not
    * grab the full path. For now 1024 chars should be enough 
    */
   char process_name[1024];

   /*
    * signifies whether this is the call send or the call
    * return
    */
   enum syscall_notification_type notification_type;

   unsigned long return_value;
};

typedef void (* syscall_handler_func)(struct syscall_info *, unsigned long *);

/* Syscall info */
struct syscall_prototype {
    char* name;
    uint16_t number;
    uint8_t parameter_count;
    struct parameter_type params[MAX_PARAM_COUNT];
    syscall_handler_func handler;
};

extern unsigned int SYSCALL_COUNT;
extern struct syscall_prototype **current_syscalls;
extern struct hashtable *syscall_table;

int init_syscalls(unsigned int syscall_num, struct syscall_prototype **syscalls, char *syscall_header, char *param_header);

void free_syscalls(void);

void generic_syscall_handler(struct syscall_info *call, unsigned long *parameter_values);

#endif
