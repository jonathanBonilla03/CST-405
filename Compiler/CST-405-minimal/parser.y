%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
ASTNode* root = NULL;
%}

/* === Union for semantic values === */
%union {
    int num;
    float floats;
    char* str;
    struct ASTNode* node;
}

/* === Tokens === */
%token <num> NUM
%token <floats> FLOAT_LITERAL
%token <str> ID
%token INT FLOAT PRINT IF ELSE
%token EQ NE LE GE LT GT

/* === Operator precedence === */
%right '='
%left EQ NE
%left LT LE GT GE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS

/* === Non-terminal types === */
%type <node> program stmt_list stmt decl assign expr print_stmt if_stmt rel_expr block

%%

/* === Grammar === */

program:
    stmt_list                     { root = $1; }
    ;

stmt_list:
    stmt                          { $$ = $1; }
    | stmt_list stmt              { $$ = createStmtList($1, $2); }
    ;

stmt:
      decl
    | assign
    | print_stmt
    | if_stmt
    ;

/* --- Block: { statements } or single stmt --- */
block:
      '{' stmt_list '}'           { $$ = $2; }
    | stmt                        { $$ = $1; }
    ;

/* --- Declarations --- */
decl:
      INT ID ';'                  { $$ = createDecl($2); free($2); }
    | FLOAT ID ';'                { $$ = createDecl($2); free($2); }
    | INT ID '[' NUM ']' ';'      { $$ = createArrayDecl($2, $4); free($2); }
    ;

/* --- Assignments --- */
assign:
      ID '=' expr ';'             { $$ = createAssign($1, $3); free($1); }
    | ID '[' expr ']' '=' expr ';'{ $$ = createArrayAssign($1, $3, $6); free($1); }
    ;

/* --- If / Else statements --- */
if_stmt:
      IF '(' expr ')' block
          { $$ = createIf($3, $5, NULL); }
    | IF '(' expr ')' block ELSE block
          { $$ = createIf($3, $5, $7); }
    ;

/* --- Print --- */
print_stmt:
      PRINT '(' expr ')' ';'      { $$ = createPrint($3); }
    ;

/* --- Expressions --- */
expr:
      NUM                         { $$ = createNum($1); }
    | FLOAT_LITERAL               { $$ = createFloat($1); }
    | ID                          { $$ = createVar($1); free($1); }
    | ID '[' expr ']'             { $$ = createArrayAccess($1, $3); free($1); }
    | expr '+' expr               { $$ = createBinOp('+', $1, $3); }
    | expr '-' expr               { $$ = createBinOp('-', $1, $3); }
    | expr '*' expr               { $$ = createBinOp('*', $1, $3); }
    | expr '/' expr               { $$ = createBinOp('/', $1, $3); }
    | expr '%' expr               { $$ = createBinOp('%', $1, $3); }
    | '-' expr %prec UMINUS       { $$ = createUnaryOp('-', $2); }
    | rel_expr                    { $$ = $1; }
    ;

/* --- Relational Expressions --- */
rel_expr:
      expr LT expr                { $$ = createRelop(RELOP_LT, $1, $3); }
    | expr GT expr                { $$ = createRelop(RELOP_GT, $1, $3); }
    | expr LE expr                { $$ = createRelop(RELOP_LE, $1, $3); }
    | expr GE expr                { $$ = createRelop(RELOP_GE, $1, $3); }
    | expr EQ expr                { $$ = createRelop(RELOP_EQ, $1, $3); }
    | expr NE expr                { $$ = createRelop(RELOP_NE, $1, $3); }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}
