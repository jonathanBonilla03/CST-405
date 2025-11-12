%option yylineno
%{
#define _GNU_SOURCE
#include <stdbool.h>
#include <string.h>
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

/* Use a start condition for block comments */
%x COMMENT

/* === Regular Definitions === */
digit       [0-9]
letter      [a-zA-Z_]
identifier  {letter}({letter}|{digit})*
floatlit    {digit}+"."{digit}*
stringlit   \"([^\"\\\\]|\\\\.)*\"
whitespace  [ \t\r\n]+

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"bool"      { return BOOL; }
"string"    { return STRING; }
"if"        { return IF; }
"else"      { return ELSE; }
"print"     { return PRINT; }
"return"    { return RETURN; }
"void"      { return VOID; }
","         { return ','; }

"//".*               { /* skip single-line comment */ }

"/*"                 { BEGIN(COMMENT); }

<COMMENT>[^*]+       { /* skip */ }
<COMMENT>"*"+[^*/]*  { /* skip */ }
<COMMENT>"*"+"/"     { BEGIN(INITIAL); }

"true"      { yylval.boolean = true; return BOOL_LITERAL; }
"false"     { yylval.boolean = false; return BOOL_LITERAL; }

{stringlit} { 
    /* Remove quotes and store string */
    char* str = strdup(yytext + 1);  /* Skip opening quote */
    str[strlen(str) - 1] = '\0';     /* Remove closing quote */
    yylval.str = str; 
    return STRING_LITERAL; 
}
{floatlit}  { yylval.floats = atof(yytext); return FLOAT_LITERAL; }
{digit}+    { yylval.num = atoi(yytext); return NUM; }
{identifier} { yylval.str = strdup(yytext); return ID; }

"=="        { return EQ; }
"!="        { return NE; }
"<="        { return LE; }
">="        { return GE; }
"<"         { return LT; }
">"         { return GT; }
"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }

";"         { return ';'; }
"="         { return '='; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
"["         { return '['; }
"]"         { return ']'; }
"+"         { return '+'; }
"-"         { return '-'; }
"**"        { return EXPONENT; }
"*"         { return '*'; }
"/"         { return '/'; }
"%"         { return '%'; }

{whitespace}  { /* ignore */ }

.           { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() { return 1; }
