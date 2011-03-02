#ifndef PARAMS_H
#define PARAMS_H

#include "hashtable.h"

#define MAX_PARAM_COUNT 16

/* Parameter type info */
struct parameter_type {
    char *type;
    char indirection;
    unsigned char property;
#define PARAM_PROP_UNSIGNED 0x1
#define PARAM_PROP_CONST 0x2
#define PARAM_PROP_STRUCT 0x4
};

typedef int(*param_handler_func)(struct parameter_type *, unsigned long);

int parameter_handling_init(unsigned int handler_num);
int parameter_handler_add(char* type, param_handler_func fp);
int parameter_handler_do(struct parameter_type *param, unsigned long address);
int parameter_handler_cleanup(void);

#endif
