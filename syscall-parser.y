%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "syscalls.h"
    #include "hashtable.h"

    int yylex(void);
    void yyerror(char*);
%}

%union {char *s; int d;}

%token POUNDDEF POUNDUNK 
%token <s> WORD 
%token <d> NUMBER

%%

lines:
    lines goodline
    | error 
    ;

goodline: POUNDDEF WORD NUMBER    
    {
        if($3 < SYSCALL_COUNT) {
            struct syscall_prototype* new_info = (struct syscall_prototype*)malloc(sizeof(struct syscall_prototype));

            if (NULL == new_info){
                fprintf(stderr, "Could not allocate syscall prototype info\n");
                exit(-1);
            }

            new_info->name = $2;
            new_info->number = $3;
            new_info->parameter_count = 0;
            new_info->handler = NULL;
            
            current_syscalls[$3] = new_info;

            if(0 == hashtable_insert(syscall_table, $2, new_info))
            {
                fprintf(stderr, "Could not insert syscall info in hashtable\n");
                exit(-1);
            }
            
        }
    }
    ;

%%

void yyerror(char *s) 
{
    /*fprintf(stderr, "error: %s\n", s);*/
}

