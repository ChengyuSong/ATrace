
%{
    #include <stdio.h>
    #include "syscalls.h"
    #include "params.h"
    #include "hashtable.h"

    int pplex(void);
    void pperror(char*);

    struct parameter_type params[MAX_PARAM_COUNT];
    int pcount = 0;
    extern int pplineno;
%}

%union {char *s; int d;}

%token POUNDDEF
%token <s> VOID CHAR INT LONG
%token CONST UNSIGNED STRUCT
%token <s> ALIANS_T
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_COMMA TOKEN_STAR TOKEN_SEMI
%token <s> WORD 
%token <d> NUMBER

%%

goodline: goodline line
    | line
    ;

line: return_type pointer apidec
    | return_type apidec
    ;

return_type: type_specifier return_type
    | type_specifier
    ;

type_specifier: VOID
    {
       params[pcount].type = $1;
    }
    | CHAR
    {
       params[pcount].type = $1;
    }
    | INT
    {
       params[pcount].type = $1;
    }
    | LONG
    {
       params[pcount].type = $1;
    }
    | CONST
    {
        params[pcount].property |= PARAM_PROP_CONST;
    }
    | UNSIGNED
    {
        params[pcount].property |= PARAM_PROP_UNSIGNED;
    }
    | struct_specifier
    | ALIANS_T
    {
       params[pcount].type = $1;
    }
    ;

struct_specifier: STRUCT WORD
    {
        params[pcount].type = $2;
        params[pcount].property |= PARAM_PROP_STRUCT;
    }
    ;

apidec: WORD TOKEN_LPAREN paramlist TOKEN_RPAREN TOKEN_SEMI
    {
        int i;
        struct syscall_prototype *call_info = NULL;

        /*fprintf(stderr, "%s: %d params\n", $1, pcount);*/

        call_info = (struct syscall_prototype*)hashtable_search(syscall_table, $1);

        if(call_info != NULL) {
            call_info->parameter_count = pcount;
            for(i = 0; i < pcount; i++) {
                call_info->params[i].type = params[i].type;
                call_info->params[i].indirection = params[i].indirection;

                /*fprintf(stderr, "Param %d, Type: %s, indirections: %d\n",
                        i,
                        call_info->params[i].type,
                        call_info->params[i].indirection);*/
            }
        } else {
            fprintf(stderr, "syscall %s not find in hash table\n", $1);
        }

        pcount = 0;
    }
    ;

paramlist: paramlist TOKEN_COMMA param
    | param
    | VOID
    ;

param: param_type name
    {
        pcount++;
    }

param_type: type_specifier param_type
    | type_specifier
    {
        params[pcount].indirection = 0;
    }
    ;

name: pointer WORD
    | WORD
    ;

pointer: TOKEN_STAR
    {
        params[pcount].indirection++;
    }
    | TOKEN_STAR pointer
    ;

%%

void pperror(char *s) 
{
    fprintf(stderr, "error: %s, line: %d\n", s, pplineno);
}

