
%{
//extern int main(int argc, char* argv[]);
#include <stdio.h>
#include "param-parser.tab.h"
//[A-Za-z][a-zA-Z0-9]* pplval.s=strdup(pptext); return WORD;
//#[0-9]+ pplval.d=atoi(pptext); return NUMBER;
%}

%%
#[0-9]+     pplval.d=atoi(pptext); return NUMBER;
\#define    return POUNDDEF;
void        pplval.s=strdup(pptext); return VOID;
char        pplval.s=strdup(pptext); return CHAR;
int         pplval.s=strdup(pptext); return INT;
long        pplval.s=strdup(pptext); return LONG;
unsigned    return UNSIGNED;
const       return CONST;
struct      return STRUCT;
[a-z_]+_t   pplval.s=strdup(pptext); return ALIANS_T;
fd_set      pplval.s=strdup(pptext); return ALIANS_T;
\(          return TOKEN_LPAREN;
\)          return TOKEN_RPAREN;
\,          return TOKEN_COMMA;
\*          return TOKEN_STAR;
\;          return TOKEN_SEMI;
\#[a-zA-Z0-9]+
[A-Za-z_][a-zA-Z0-9_]*    pplval.s=strdup(pptext); return WORD;
.
\n
%%

int ppwrap(void)
{
    return 1;
}
