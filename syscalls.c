#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syscalls.h"
//#include "syscalls.tab.h"

/* Syscalls Parser*/
extern FILE *yyin;
extern void yyparse(void);

/* Syscall Parameters Parser*/
extern FILE *ppin;
extern void ppparse(void);

unsigned int SYSCALL_COUNT;
struct syscall_prototype** current_syscalls;
struct hashtable* syscall_table;

/* hash function taken from description in:
 * http://www.cse.yorku.ca/~oz/hash.html
 *
 * according to the site the code is in the public domain *
 */
unsigned int hash_fn(void *value)
{
    const char* s_value = (const char*)value;
    unsigned int hash = 0;
    int c; 
    while ((c = *s_value++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

int string_equality_fn(void *s1, void *s2)
{
    return ( 0 == strcmp((const char*)s1, (const char *)s2));
}

/* populate the system call map and table from
 * given header file
 */
static int populate_syscalls(char *syscall_header) 
{
    FILE *header_file = fopen(syscall_header, "r");

    if (header_file == NULL) {
        fprintf(stderr, "Could not open syscall header\n");
        return -1;
    }

    fprintf(stderr, "Populating syscalls\n");

    yyin = header_file;
    yyparse();
    fclose(header_file);

    fprintf(stderr, "Syscall populated, first call(%p)=%s\n",
		    current_syscalls[1], current_syscalls[1]->name);

    return 0;
}

/* parse the parameters to system call arguments */
static int parse_parameters(char *param_header) 
{
    FILE *syscall_params = fopen(param_header, "r");

    if (syscall_params == NULL) {
        fprintf(stderr, "Could not open syscall parameters header\n");
        return -1;
    }

    fprintf(stderr, "Parse parameters\n");

    ppin = syscall_params;
    ppparse();
    fclose(syscall_params);

    return 0;
}

/* create and populate a syscal table. Use this to map
 * from syscall# to syscall name
 * and to figure out the number of arguments
 * later this table can include more information about
 * the call arguments and derive their textual representation
 */
int init_syscalls(unsigned int syscall_num,
        struct syscall_prototype** syscalls,
        char *syscall_header,
        char *param_header) 
{
    
    syscall_table = create_hashtable(syscall_num, hash_fn, string_equality_fn);

    if(syscall_table == NULL)
        return -1;

    /* init variables for yyparse */
    SYSCALL_COUNT = syscall_num;
    current_syscalls = syscalls;

    if (0 != populate_syscalls(syscall_header)) {
            
        fprintf(stderr, "Could not populate the syscall table.\n");

        hashtable_destroy(syscall_table, 0);
        syscall_table = NULL;

        return -1;
    }

    if (0 != parse_parameters(param_header)) {
        fprintf(stderr, "Could not parse the syscall parameters.\n");

        hashtable_destroy(syscall_table, 0);
        syscall_table = NULL;

        return -2;
    }

    return 0;
}

void free_syscalls(void) {

    unsigned int i, j;
    
    for(i = 0; i < SYSCALL_COUNT; i++) {

           if(current_syscalls[i] != NULL) {

               for(j = 0; j < MAX_PARAM_COUNT; j++) {

                   if(current_syscalls[i]->params[j].type != NULL) {
                       
                       free(current_syscalls[i]->params[j].type);
                   }
               }

               free(current_syscalls[i]);
           }
    }

}

#if 0

/* read 32 bits from the guest hvm domain. I had
 * to write this function since neither the default
 * xen xc_translate_foreign_address or xenaccess
 * worked with 64bit hvm domains. I don't know why
 * the libxc calls didn't work, but this method
 * should work on any hvm domain. All this does is
 * call a function in the hypervisor to read the memory
 * using the current pagetable of the requested domain
 * as the base for translation of va->mfn
 */
int domain_read_32bits( int xc_iface, int domid, unsigned long va, uint32_t *dest)
{
    if(ether_readguest(xc_iface,
                domid,
                va,
                (unsigned char*)dest,
                sizeof(uint32_t)) != 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }

}

int domain_read_current(unsigned long va, void *dest, int length)
{
    if(ether_readguest(current_domain.xc_iface,
                current_domain.domid,
                va,
                (unsigned char*)dest,
                length) != 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

#endif

void generic_syscall_handler(struct syscall_info *call, unsigned long *parameter_values)
{
    if(call->notification_type == SYSCALL_CALL) {
        fprintf(stderr, "[ATRACE]");
    } else { 
        fprintf(stderr, " = 0x%lx\n", call->return_value);
        fflush(stderr);

        return;
    }

    fprintf(stderr, "[%s][0x%lx][%d][%d] %s(",
            call->process_name,
            call->hid,
            call->pid,
            call->tid,
            current_syscalls[call->number]->name);


    if (parameter_values != NULL) {
        
        uint8_t i;
        for(i = 0; i < current_syscalls[call->number]->parameter_count; i++) {

            unsigned long param = parameter_values[i];

            if(i != 0) {
                fprintf(stderr, ", ");
            }

            fprintf(stderr, "0x%lx", param);
            
            /* parameter_values = memory address of parameter */
            //parameter_handler_do(&(current_syscalls[call->number]->params[i]), param);

        }
    }

    fprintf(stderr, ")");
}

