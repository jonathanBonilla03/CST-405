%debug
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "semantic.h"
#include "symtab.h"

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
    char character;
    bool boolean;
    struct ASTNode* node;
}

/* === Tokens === */
%token <num> NUM
%token <floats> FLOAT_LITERAL
%token <str> ID STRING_LITERAL
%token <character> CHAR_LITERAL
%token <boolean> BOOL_LITERAL
%token INT FLOAT BOOL CHAR STRING PRINT IF ELSE RETURN VOID WHILE RETRY BACKOFF ONFAIL BREAK
%token EQ NE LE GE LT GT
%token AND OR NOT EXPONENT

/* === Operator precedence === */
%right '='
%left OR
%left AND
%right NOT
%left EQ NE
%left LT LE GT GE
%left '+' '-'
%left '*' '/' '%'
%right EXPONENT
%right UMINUS CAST

%expect 3

/* === Non-terminal types === */
%type <node> program func_list stmt_list stmt decl assign expr print_stmt if_stmt while_stmt block func_decl param_list param arg_list return_stmt break_stmt init_list retry_stmt
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
    | type ID '(' VOID ')' '{' stmt_list '}' {
        $$ = createFuncDecl($1, $2, NULL, $7);
    }
    ;

type:
      INT     { $$ = "int"; }
    | FLOAT   { $$ = "float"; }
    | BOOL    { $$ = "bool"; }
    | CHAR    { $$ = "char"; }
    | STRING  { $$ = "string"; }
    | VOID    { $$ = "void"; }
    | INT '[' ']'     { $$ = "int[]"; }
    | FLOAT '[' ']'   { $$ = "float[]"; }
    | BOOL '[' ']'    { $$ = "bool[]"; }
    | CHAR '[' ']'    { $$ = "char[]"; }
    | STRING '[' ']'  { $$ = "string[]"; }
    ;

param_list:
      param                     { $$ = $1; }
    | param_list ',' param      { $$ = createParamList($1, $3); }
    ;

param:
    type ID                     { $$ = createParam($1, $2); }
    | type ID '[' ']'           { $$ = createArrayParam($1, $2); }
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
    | while_stmt
    | return_stmt
    | retry_stmt
    | break_stmt
    | expr ';'                  { $$ = $1; }  /* Allow function calls as statements */
    | error ';'                 { 
          reportSpecificError(ERROR_MISSING_SEMICOLON, "");
          yyerrok; 
          $$ = NULL; 
      }
    ;

return_stmt:
      RETURN expr ';'           { $$ = createReturn($2); }
    | RETURN ';'                { $$ = createReturn(NULL); }
    ;

break_stmt:
      BREAK ';'                 { $$ = createBreak(); }
    ;

/* --- Block: { statements } or single stmt --- */
block:
      '{' stmt_list '}'         { $$ = $2; }
    | stmt                      { $$ = $1; }
    ;

/* --- Declarations --- */
decl:
      INT ID ';'                { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createDecl("int", $2); 
          free($2); 
      }
    | FLOAT ID ';'              { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createDecl("float", $2); 
          free($2); 
      }
    | BOOL ID ';'               { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createDecl("bool", $2); 
          free($2); 
      }
    | CHAR ID ';'               { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createDecl("char", $2); 
          free($2); 
      }
    | STRING ID ';'             { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createDecl("string", $2); 
          free($2); 
      }
    | INT ID '=' expr ';'       { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          char* exprType = getExpressionType($4);
          checkAssignmentType("int", exprType);
          $$ = createDeclInit("int", $2, $4); 
          free($2); 
      }
    | FLOAT ID '=' expr ';'     { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          char* exprType = getExpressionType($4);
          checkAssignmentType("float", exprType);
          $$ = createDeclInit("float", $2, $4); 
          free($2); 
      }
    | BOOL ID '=' expr ';'      { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          char* exprType = getExpressionType($4);
          checkAssignmentType("bool", exprType);
          $$ = createDeclInit("bool", $2, $4); 
          free($2); 
      }
    | CHAR ID '=' expr ';'      { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          char* exprType = getExpressionType($4);
          checkAssignmentType("char", exprType);
          $$ = createDeclInit("char", $2, $4); 
          free($2); 
      }
    | STRING ID '=' expr ';'    { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          char* exprType = getExpressionType($4);
          checkAssignmentType("string", exprType);
          $$ = createDeclInit("string", $2, $4); 
          free($2); 
      }
    | INT ID '[' NUM ']' ';'    { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createArrayDecl("int", $2, $4); 
          free($2); 
      }
    | FLOAT ID '[' NUM ']' ';'  { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createArrayDecl("float", $2, $4); 
          free($2); 
      }
    | CHAR ID '[' NUM ']' ';'   { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createArrayDecl("char", $2, $4); 
          free($2); 
      }
    | INT ID '[' NUM ']' '=' '{' init_list '}' ';'    { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createArrayInitDecl("int", $2, $4, $8); 
          free($2); 
      }
    | FLOAT ID '[' NUM ']' '=' '{' init_list '}' ';'  { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createArrayInitDecl("float", $2, $4, $8); 
          free($2); 
      }
    | CHAR ID '[' NUM ']' '=' '{' init_list '}' ';'   { 
          if (isInCurrentScope($2)) {
              reportSpecificError(ERROR_DUPLICATE_VAR, $2);
          }
          $$ = createArrayInitDecl("char", $2, $4, $8); 
          free($2); 
      }
    ;

/* --- Assignments --- */
assign:
      ID '=' expr ';'           { 
          Symbol* sym = lookupSymbol($1);
          if (!sym) {
              reportSpecificError(ERROR_UNDECLARED_VAR, $1);
          } else {
              char* exprType = getExpressionType($3);
              checkAssignmentType(sym->type, exprType);
          }
          $$ = createAssign($1, $3); 
          free($1); 
      }
    | ID '[' expr ']' '=' expr ';'  { 
          Symbol* sym = lookupSymbol($1);
          if (!sym) {
              reportSpecificError(ERROR_UNDECLARED_VAR, $1);
          } else if (!sym->isArray) {
              reportSpecificError(ERROR_UNDECLARED_VAR, $1);
          } else {
              char* indexType = getExpressionType($3);
              checkArrayIndexType(indexType);
              char* exprType = getExpressionType($6);
              checkAssignmentType(sym->type, exprType);
          }
          $$ = createArrayAssign($1, $3, $6); 
          free($1); 
      }
    ;

/* --- Initialization Lists --- */
init_list:
      expr                      { $$ = $1; }
    | init_list ',' expr        { $$ = createInitList($1, $3); }
    ;

/* --- If / Else statements --- */
if_stmt:
      IF '(' expr ')' block     { $$ = createIf($3, $5, NULL); }
    | IF '(' expr ')' block ELSE block
                                { $$ = createIf($3, $5, $7); }
    ;

/* --- While statements --- */
while_stmt:
      WHILE '(' expr ')' block  { $$ = createWhile($3, $5); }
    ;

/* --- Retry statements --- */
retry_stmt:
      RETRY '(' NUM ')' block                           { $$ = createRetry($3, 0, $5, NULL); }
    | RETRY '(' NUM ',' BACKOFF '=' NUM ')' block       { $$ = createRetry($3, $7, $9, NULL); }
    | RETRY '(' NUM ')' block ONFAIL block              { $$ = createRetry($3, 0, $5, $7); }
    | RETRY '(' NUM ',' BACKOFF '=' NUM ')' block ONFAIL block  { $$ = createRetry($3, $7, $9, $11); }
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
    | CHAR_LITERAL              { $$ = createChar($1); }
    | STRING_LITERAL            { $$ = createString($1); free($1); }
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
    | expr EXPONENT expr        { $$ = createBinOp(BINOP_EXP, $1, $3); }

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
    | ID '(' arg_list ')'       { 
          checkFunctionCall($1, $3);
          $$ = createFuncCall($1, $3); 
      }
    | ID '(' ')'                { 
          checkFunctionCall($1, NULL);
          $$ = createFuncCall($1, NULL); 
      }
    ;

arg_list:
      expr                      { $$ = $1; }
    | arg_list ',' expr         { $$ = createArgList($1, $3); }
    ;

%%

void yyerror(const char* s) {
    semantic_errors++;
    
    /* Specific error detection based on context */
    if (yytext) {
        if (strcmp(yytext, "}") == 0) {
            reportSpecificError(ERROR_MISMATCHED_BRACE, "Unexpected closing brace - missing opening brace or extra closing brace");
        } else if (strcmp(yytext, "{") == 0) {
            reportSpecificError(ERROR_MISSING_SEMICOLON, "");
            printf("   Location: Before '{' - missing semicolon at end of previous statement\n");
        } else if (strstr(yytext, "\n") || strlen(yytext) == 0) {
            reportSpecificError(ERROR_MISSING_SEMICOLON, "");
            printf("   Location: Line %d - statement not properly terminated\n", yylineno);
        } else {
            /* Generic syntax error for other cases */
            printf("✗ Syntax Error at line %d: %s (near \"%s\")\n",
                   yylineno, s, yytext);
            printf("   Check syntax rules for the C-Minus language\n");
        }
    } else {
        printf("✗ Syntax Error at line %d: %s\n", yylineno, s);
    }
}
