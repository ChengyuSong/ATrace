/* Header file for syscall tracing */

#ifndef SYSCALL_TRACE_H
#define SYSCALL_TRACE_H

#include "cpu.h"
#include "syscalls.h"

int init_syscall_trace();
void trace_syscall(CPUState *env);
void trace_syscall_ret(CPUState *env);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern target_ulong syscall_ret_addr;

#endif
