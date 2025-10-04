%{
/* SYNTAX ANALYZER (PARSER)
 * This is the second phase of compilation - checking grammar rules
 * Bison generates a parser that builds an Abstract Syntax Tree (AST)
 * The parser uses tokens from the scanner to verify syntax is correct
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* External declarations for lexer interface */
extern int yylex();      /* Get next token from scanner */
extern int yyparse();    /* Parse the entire input */
extern FILE* yyin;       /* Input file handle */

void yyerror(const char* s);  /* Error handling function */
ASTNode* root = NULL;          /* Root of the Abstract Syntax Tree */
%}

/* SEMANTIC VALUES UNION */
%union {
    int num;                 /* For integer literals */
    float floats;            /* For float literals */
    char* str;               /* For identifiers */
    struct ASTNode* node;    /* For AST nodes */
}

/* TOKENS */
%token <num>   NUM
%token <floats> FLOAT
%token <str>   ID
%token         INT PRINT

/* NON-TERMINAL TYPES */
%type <node> program stmt_list stmt decl assign expr print_stmt

/* PRECEDENCE & ASSOCIATIVITY */
%right '='
%left '+' '-'
%left '*' '/'
%left '%'
%right UMINUS     /* unary minus has higher precedence than +,-,*./,% */

%%

/* PROGRAM */
program:
    stmt_list
    {
        root = $1;
    }
    ;

/* STATEMENT LIST */
stmt_list:
      stmt
    | stmt_list stmt { $$ = createStmtList($1, $2); }
    ;

/* STATEMENT */
stmt:
      decl
    | assign
    | print_stmt
    ;

/* DECLARATIONS */
decl:
      INT ID ';'
    {
        $$ = createDecl($2);
        free($2);
    }
    | INT ID '[' NUM ']' ';'
    {
        $$ = createArrayDecl($2, $4);
        free($2);
    }
    | FLOAT ID ';'
    {
        $$ = createDecl($2);
        free($2);
    }
    ;

/* ASSIGNMENTS */
assign:
      ID '=' expr ';'
    {
        $$ = createAssign($1, $3);
        free($1);
    }
    | ID '[' expr ']' '=' expr ';'
    {
        $$ = createArrayAssign($1, $3, $6);
        free($1);
    }
    ;

/* EXPRESSIONS */
expr:
      NUM                { $$ = createNum($1); }
    | FLOAT              { $$ = createFloat($1); }
    | ID                 { $$ = createVar($1); free($1); }
    | ID '[' expr ']'    { $$ = createArrayAccess($1, $3); free($1); }

    /* binary ops */
    | expr '+' expr      { $$ = createBinOp('+', $1, $3); }
    | expr '-' expr      { $$ = createBinOp('-', $1, $3); }
    | expr '*' expr      { $$ = createBinOp('*', $1, $3); }
    | expr '/' expr      { $$ = createBinOp('/', $1, $3); }
    | expr '%' expr      { $$ = createBinOp('%', $1, $3); }

    /* unary minus (negative numbers / negation) */
    | '-' expr %prec UMINUS { $$ = createUnaryOp('-', $2); }

    /* parentheses for grouping, e.g., -(x + 3) */
    | '(' expr ')'       { $$ = $2; }
    ;

/* PRINT */
print_stmt:
    PRINT '(' expr ')' ';'
    {
        $$ = createPrint($3);
    }
    ;

%%

/* ERROR HANDLING */
void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}
