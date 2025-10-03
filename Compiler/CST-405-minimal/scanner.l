%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

#define YY_BUF_SIZE 32768

struct keyword {
    char* word;
    int token;
};

#define NUM_KEYWORDS 3
static struct keyword keywords[] = {
    {"int", INT},
    {"float", FLOAT},
    {"print", PRINT}
    /* add {"return", RETURN} if you also declare %token RETURN in parser.y */
};

int check_keyword(const char* str) {
    for(int i = 0; i < NUM_KEYWORDS; i++) {
        if(strcmp(keywords[i].word, str) == 0) {
            return keywords[i].token;
        }
    }
    return ID;
}
%}

%option nounput noinput

%%

[0-9]+          { yylval.num = atoi(yytext); return NUM; }
[0-9]+\.[0-9]+  { yylval.floats = atof(yytext); return FLOAT; }

[a-zA-Z_][a-zA-Z0-9_]* {
    int token = check_keyword(yytext);
    if(token == ID) {
        yylval.str = strdup(yytext);
    }
    return token;
}

"+"   { return '+'; }
"*"   { return '*'; }
"="   { return '='; }
";"   { return ';'; }
"("   { return '('; }
")"   { return ')'; }
"["   { return '['; }
"]"   { return ']'; }
"/"   { return '/'; }
"%"   { return '%'; }

[ \t\r\n]       { /* ignore whitespace */ }
"//"[^\n]*      { /* ignore single-line comments */ }

.               { printf("Lexical Error: Unknown character '%c'\n", *yytext); }

%%

int yywrap(void) { return 1; }
