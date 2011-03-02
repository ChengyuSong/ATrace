#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <errno.h>
#include <unistd.h>
#include "params.h"

extern unsigned int hash_fn(void *value);
extern int string_equality_fn(void *s1, void *s2);

static struct hashtable* parameter_handlers = NULL;

static void base16_print(const char *str)
{
    int length = strlen(str);
    int item, i;

    for(i = 0; i < length; i++) {
        item = (unsigned int)str[i];
        fprintf(stderr, "%02X", item);
    }
}

static int int_handler(struct parameter_type *param, unsigned long value)
{
    unsigned int indirection = param->indirection;
    unsigned long address;
    unsigned int real_value = 0;
    int did_read = -1;

    while (indirection > 1) {
        address = value;

        /* BAD address value, directly return */
        if (address == 0)
            return -1;

        //did_read = env->read_ulong(&value, address);
        //if (did_read)
        //    fprintf(stderr, ": 0x%lx", value);

        indirection--;
    }

    if (indirection == 1) {
        address = value;

        //did_read = env->read_uint(&real_value, address);
        //if (!did_read)
        //    return -1;

        if (param->property & PARAM_PROP_UNSIGNED) {
            fprintf(stderr, ": %u", real_value);
        } else {
            fprintf(stderr, ": %d", (int)real_value);
        }
    }

    return 0;
}

static int long_handler(struct parameter_type *param, unsigned long value)
{
    unsigned int indirection = param->indirection;
    unsigned long address;
    int did_read = -1;

    /* Do nothing if the value is a direct value. */
    if (indirection == 0)
        return 0;

    while (indirection > 1) {
        address = value;

        /* BAD address value, directly return */
        if (address == 0)
            return -1;

        //did_read = env->read_ulong(&value, address);
        //if (did_read)
        //    fprintf(stderr, ": 0x%lx", value);

        indirection--;
    }

    //did_read = env->read_ulong(&value, address);
    //if (!did_read)
    //    return -1;
    
    if (param->property & PARAM_PROP_UNSIGNED) {
        fprintf(stderr, ": %lu", value);
    } else {
        fprintf(stderr, ": %ld", (long)value);
    }

    return 0;
}

static int char_handler(struct parameter_type *param, unsigned long value)
{
    unsigned int indirection = param->indirection;
    unsigned long address;
    int did_read = -1;
    char c = 0;

    while (indirection > 1) {
        address = value;

        /* BAD address value, directly return */
        if (address == 0)
            return -1;

        //did_read = env->read_ulong(&value, address);
        //if (did_read)
        //    fprintf(stderr, ": 0x%lx", value);

        indirection--;
    }

    fprintf(stderr, ": ");

    if (indirection == 1) {
        address = value;

        /* dump string */
        while (1) {
            if (address == 0)
                return -1;

            //did_read = env->read_char(&c, address);
            //if (!did_read)
            //    return -1;

            if (c == '\0')
                break;

            fprintf(stderr, "%c", c);
            address++;
        }
    } else {
        if (param->property & PARAM_PROP_UNSIGNED) {
            fprintf(stderr, ": %c", (char)value);
        } else {
            fprintf(stderr, ": %u", (unsigned char)value);
        }
    }

    return 0;
}

static int void_handler(struct parameter_type *param, unsigned long value)
{
    if(param->indirection > 1) {
        return long_handler(param, value);
    }
    else {
        /* normal void* shouldn't
         * print anything extra
         * for now.
         *
         * this will be a data handler
         * (perhaps)
         */
        return 0;
    }
}

int parameter_handling_init(unsigned int handler_num)
{
    /* Add four internal handler for void, char, int and long. */
    handler_num += 4;

    parameter_handlers = create_hashtable(handler_num, hash_fn, string_equality_fn);

    if(parameter_handlers == NULL) {
        return -1;
    }

    /*parameter_handler_add("char", char_handler);
    parameter_handler_add("int", int_handler);
    parameter_handler_add("long", long_handler);
    parameter_handler_add("void", void_handler);
    */
    return 0;
}

int parameter_handler_add(char* type, param_handler_func fp)
{
    if (0 == hashtable_insert(parameter_handlers, type, fp)) {
        fprintf(stderr, "Could not insert parameter type handler in hashtable.\n");
        return -1;
    }
    return 0;
}

int parameter_handler_do(struct parameter_type *param, unsigned long address)
{
    /* look up the parameter name in a hash table to find
     * decoder function */
    param_handler_func fp;
    char real_type[64];

    if (param->property & PARAM_PROP_STRUCT) {
        strcpy(real_type, "struct ");
        strncat(real_type, param->type, 56);
    } else {
        strncpy(real_type, param->type, 64);
    }

    fp = (param_handler_func)hashtable_search(parameter_handlers, real_type);

    if(fp != NULL)     {
        return (*fp)(param, address);
    } else {
        return -1;
    }
}

int parameter_handler_cleanup(void)
{
    hashtable_destroy(parameter_handlers, 1);
    return 0;
}

