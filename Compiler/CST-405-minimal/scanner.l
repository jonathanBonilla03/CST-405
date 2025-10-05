%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"print"         { return PRINT; }
"if"            { return IF; }
"else"          { return ELSE; }

[0-9]+\.[0-9]+  { yylval.floats = atof(yytext); return FLOAT_LITERAL; }
[0-9]+           { yylval.num = atoi(yytext); return NUM; }

"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }

"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
"["             { return '['; }
"]"             { return ']'; }
";"             { return ';'; }
","             { return ','; }
"="             { return '='; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }

[ \t\r\n]+      ;   /* ignore whitespace */

.               { printf("Unknown token: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
