#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "exec-all.h"
#include "gdbstub.h"
#include "qemu-common.h"

#include "syscall-trace.h"

#define ANDROID_SYSCALL_NUM 366
#define ANDROID_SYSCALL_HEADER "linux-arm-syscall.h"
#define ANDROID_SYSCALL_PARAM_HEADER "linux-arm-syscall-param.h"

target_ulong syscall_ret_addr = 0;

static struct syscall_prototype* android_syscalls[ANDROID_SYSCALL_NUM] = {NULL};

/* Syscall information */
static struct syscall_info g_syscall_info;

/* Arguments */
static unsigned long g_syscall_args[MAX_PARAM_COUNT];

static int syscall_initialized = 0;

int init_syscall_trace()
{
    fprintf(stderr, "Init syscall trace\n");

    if(init_syscalls(ANDROID_SYSCALL_NUM, android_syscalls, ANDROID_SYSCALL_HEADER, ANDROID_SYSCALL_PARAM_HEADER))
        return -1;

    syscall_initialized = 1;

    return 0;
}

void trace_syscall(CPUState *env)
{
    /* lazy initializing */
    if (unlikely(syscall_initialized == 0)) {

        if (init_syscall_trace()) {
            fprintf(stderr, "error initializing syscall trace\n");

            exit(1);
        }
    }

    /* Android uses EABI */
    uint16_t syscall_num = (uint16_t)env->regs[7];

    memset(&g_syscall_info, 0, sizeof(g_syscall_info));

    g_syscall_info.notification_type = SYSCALL_CALL;
    g_syscall_info.number = syscall_num;

    syscall_ret_addr = env->regs[15];

    //fprintf(stderr, "syscall num: %d, return addr: %x\n", syscall_num, syscall_ret_addr);
    
    struct syscall_prototype *prototype = android_syscalls[syscall_num];

    if (NULL != prototype) {
        
        /* Get parameters */
        uint16_t i;
        for (i = 0; i < prototype->parameter_count; i++) {
            g_syscall_args[i] = env->regs[i];
        }

        if (NULL != prototype->handler)
            (*prototype->handler)(&g_syscall_info, g_syscall_args);

        generic_syscall_handler(&g_syscall_info, g_syscall_args);
    }
}

void trace_syscall_ret(CPUState *env)
{
    /* Android uses EABI */
    uint16_t syscall_num = g_syscall_info.number;

    g_syscall_info.notification_type = SYSCALL_RET;
    g_syscall_info.return_value = env->regs[0];

    //fprintf(stderr, "syscall num: %d, return addr: %x\n", syscall_num, syscall_ret_addr);
    
    struct syscall_prototype *prototype = android_syscalls[syscall_num];

    if (NULL != prototype) {

        if (NULL != prototype->handler)
            (*prototype->handler)(&g_syscall_info, NULL);

        generic_syscall_handler(&g_syscall_info, NULL);
    }
}

