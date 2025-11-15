%option yylineno
%{
#define _GNU_SOURCE
#include <stdbool.h>
#include <string.h>
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>

/* Function to process escape sequences in strings */
char* process_string_escapes(const char* str) {
    size_t len = strlen(str);
    char* result = malloc(len + 1);  /* Allocate enough space */
    if (!result) return NULL;
    
    int i = 0, j = 0;
    
    while (i < len) {
        if (str[i] == '\\' && i + 1 < len) {
            switch (str[i + 1]) {
                case 'n': result[j++] = '\n'; break;
                case 't': result[j++] = '\t'; break;
                case 'r': result[j++] = '\r'; break;
                case '\\': result[j++] = '\\'; break;
                case '"': result[j++] = '"'; break;
                case '0': result[j++] = '\0'; break;
                default: 
                    /* Unknown escape - keep both characters */
                    result[j++] = str[i];
                    result[j++] = str[i + 1];
                    break;
            }
            i += 2;
        } else {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    return result;
}
%}

/* Use a start condition for block comments */
%x COMMENT

/* === Regular Definitions === */
digit       [0-9]
letter      [a-zA-Z_]
identifier  {letter}({letter}|{digit})*
floatlit    {digit}+"."{digit}*
stringlit   \"([^\"\\\\]|\\\\.)*\"
charlit     '([^'\\\\]|\\\\.)'
whitespace  [ \t\r\n]+

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"bool"      { return BOOL; }
"char"      { return CHAR; }
"string"    { return STRING; }
"if"        { return IF; }
"else"      { return ELSE; }
"print"     { return PRINT; }
"return"    { return RETURN; }
"void"      { return VOID; }
"while"     { return WHILE; }
"retry"     { return RETRY; }
"break"     { return BREAK; }
"backoff"   { return BACKOFF; }
"onfail"    { return ONFAIL; }
","         { return ','; }

"//".*               { /* skip single-line comment */ }

"/*"                 { BEGIN(COMMENT); }

<COMMENT>[^*]+       { /* skip */ }
<COMMENT>"*"+[^*/]*  { /* skip */ }
<COMMENT>"*"+"/"     { BEGIN(INITIAL); }

"true"      { yylval.boolean = true; return BOOL_LITERAL; }
"false"     { yylval.boolean = false; return BOOL_LITERAL; }

{charlit} {
    /* Character literal: 'c' or '\n' etc. */
    char c;
    if (yytext[1] == '\\') {
        /* Handle escape sequences */
        switch (yytext[2]) {
            case 'n': c = '\n'; break;
            case 't': c = '\t'; break;
            case 'r': c = '\r'; break;
            case '\\': c = '\\'; break;
            case '\'': c = '\''; break;
            case '0': c = '\0'; break;
            default: c = yytext[2]; break;
        }
    } else {
        c = yytext[1];  /* Regular character */
    }
    yylval.character = c;
    return CHAR_LITERAL;
}

{stringlit} { 
    /* Remove quotes and store string - escape processing happens later */
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
