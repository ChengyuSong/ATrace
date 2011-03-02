%{
extern int main(int argc, char* argv[]);
#include <stdio.h>
#include "syscall-parser.tab.h"
%}

%%
[0-9]+	yylval.d=atoi(yytext); return NUMBER;
\#define	return POUNDDEF;
\#[a-zA-Z0-9]+
[A-Za-z_][a-zA-Z0-9_]*	yylval.s=strdup(yytext); return WORD;
.
\n
%%

int yywrap(void)
{
	return 1;
}
