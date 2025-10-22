%debug
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char *yytext;
extern int yylineno;
void yyerror(const char* s);
ASTNode* root = NULL;
%}

/* === Union for semantic values === */
%union {
    int num;
    float floats;
    char* str;
    bool boolean;
    struct ASTNode* node;
}

/* === Tokens === */
%token <num> NUM
%token <floats> FLOAT_LITERAL
%token <str> ID
%token <boolean> BOOL_LITERAL
%token INT FLOAT BOOL PRINT IF ELSE RETURN VOID
%token EQ NE LE GE LT GT
%token AND OR NOT

/* === Operator precedence === */
%right '='
%left OR
%left AND
%right NOT
%left EQ NE
%left LT LE GT GE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS CAST

%expect 1

/* === Non-terminal types === */
%type <node> program func_list stmt_list stmt decl assign expr print_stmt if_stmt block func_decl param_list param arg_list return_stmt
%type <str> type

%%

/* === Grammar === */

program:
    func_list { root = $1; $$ = $1; }
    ;

func_list:
    func_decl                   { $$ = $1; }
    | func_list func_decl       { $$ = createFuncList($1, $2); }
    ;

func_decl:
    type ID '(' param_list ')' '{' stmt_list '}' {
        $$ = createFuncDecl($1, $2, $4, $7);
    }
    | type ID '(' ')' '{' stmt_list '}' {
        $$ = createFuncDecl($1, $2, NULL, $6);
    }
    ;

type:
      INT     { $$ = "int"; }
    | FLOAT   { $$ = "float"; }
    | BOOL    { $$ = "bool"; }
    | VOID    { $$ = "void"; }
    ;

param_list:
      param                     { $$ = $1; }
    | param_list ',' param      { $$ = createParamList($1, $3); }
    ;

param:
    type ID                     { $$ = createParam($1, $2); }
    ;

stmt_list:
      stmt                      { $$ = $1; }
    | stmt_list stmt            { $$ = createStmtList($1, $2); }
    ;

stmt:
      decl
    | assign
    | print_stmt
    | if_stmt
    | return_stmt
    ;

return_stmt:
      RETURN expr ';'           { $$ = createReturn($2); }
    | RETURN ';'                { $$ = createReturn(NULL); }
    ;

/* --- Block: { statements } or single stmt --- */
block:
      '{' stmt_list '}'         { $$ = $2; }
    | stmt                      { $$ = $1; }
    ;

/* --- Declarations --- */
decl:
      INT ID ';'                { $$ = createDecl($2); free($2); }
    | FLOAT ID ';'              { $$ = createDecl($2); free($2); }
    | INT ID '[' NUM ']' ';'    { $$ = createArrayDecl($2, $4); free($2); }
    | FLOAT ID '[' NUM ']' ';'  { $$ = createArrayDecl($2, $4); free($2); }
    | BOOL ID ';'               { $$ = createDecl($2); free($2); }
    ;

/* --- Assignments --- */
assign:
      ID '=' expr ';'           { $$ = createAssign($1, $3); free($1); }
    | ID '[' expr ']' '=' expr ';'
                                { $$ = createArrayAssign($1, $3, $6); free($1); }
    ;

/* --- If / Else statements --- */
if_stmt:
      IF '(' expr ')' block     { $$ = createIf($3, $5, NULL); }
    | IF '(' expr ')' block ELSE block
                                { $$ = createIf($3, $5, $7); }
    ;

/* --- Print --- */
print_stmt:
      PRINT '(' expr ')' ';'    { $$ = createPrint($3); }
    ;

/* --- Expressions --- */
expr:
      NUM                       { $$ = createNum($1); }
    | FLOAT_LITERAL             { $$ = createFloat($1); }
    | BOOL_LITERAL              { $$ = createBool($1); }
    | ID                        { $$ = createVar($1); free($1); }
    | ID '[' expr ']'           { $$ = createArrayAccess($1, $3); free($1); }
    | '(' expr ')'              { $$ = $2; }
    | '(' type ')' expr %prec CAST { $$ = createCast($2, $4); }

    /* Arithmetic */
    | expr '+' expr             { $$ = createBinOp(BINOP_ADD, $1, $3); }
    | expr '-' expr             { $$ = createBinOp(BINOP_SUB, $1, $3); }
    | expr '*' expr             { $$ = createBinOp(BINOP_MUL, $1, $3); }
    | expr '/' expr             { $$ = createBinOp(BINOP_DIV, $1, $3); }
    | expr '%' expr             { $$ = createBinOp(BINOP_MOD, $1, $3); }

    /* Logical */
    | expr AND expr             { $$ = createBinOp(BINOP_AND, $1, $3); }
    | expr OR expr              { $$ = createBinOp(BINOP_OR, $1, $3); }

    /* Relational */
    | expr LT expr              { $$ = createRelop(RELOP_LT, $1, $3); }
    | expr GT expr              { $$ = createRelop(RELOP_GT, $1, $3); }
    | expr LE expr              { $$ = createRelop(RELOP_LE, $1, $3); }
    | expr GE expr              { $$ = createRelop(RELOP_GE, $1, $3); }
    | expr EQ expr              { $$ = createRelop(RELOP_EQ, $1, $3); }
    | expr NE expr              { $$ = createRelop(RELOP_NE, $1, $3); }

    /* Unary */
    | '-' expr %prec UMINUS     { $$ = createUnaryOp(UNOP_NEG, $2); }
    | NOT expr                  { $$ = createUnaryOp(UNOP_NOT, $2); }

    /* Function calls */
    | ID '(' arg_list ')'       { $$ = createFuncCall($1, $3); }
    | ID '(' ')'                { $$ = createFuncCall($1, NULL); }
    ;

arg_list:
      expr                      { $$ = $1; }
    | arg_list ',' expr         { $$ = createArgList($1, $3); }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error at line %d: %s (near \"%s\")\n",
            yylineno, s, yytext ? yytext : "<null>");
}
