#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* THREE-ADDRESS CODE (TAC) */

/* Optimization statistics */
typedef struct {
    int eliminated_temps;
    int constant_folded;
    int dead_code_removed;
} OptimizationStats;

/* Declare global stats (defined in tac.c) */
extern OptimizationStats opt_stats;

/* TAC INSTRUCTION TYPES */
typedef enum {
    TAC_ADD,     
    TAC_SUB,     
    TAC_MUL,     
    TAC_DIV,     
    TAC_MOD,     
    TAC_ASSIGN,  
    TAC_PRINT,   
    TAC_DECL,     
    TAC_ARRAY_DECL,    
    TAC_ARRAY_ASSIGN,  
    TAC_ARRAY_ACCESS,
    TAC_NOP,
    TAC_NEG
} TACOp;

/* TAC INSTRUCTION STRUCTURE */
typedef struct TACInstr {
    TACOp op;
    char* arg1;
    char* arg2;
    char* result;
    struct TACInstr* next;
} TACInstr;

/* TAC LIST MANAGEMENT */
typedef struct {
    TACInstr* head;
    TACInstr* tail;
    int tempCount;
} TACList;

/* Global TAC lists (defined in tac.c) */
extern TACList tacList;
extern TACList optimizedList;

/* Function declarations */
void initTAC();
char* newTemp();
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result);
void appendTAC(TACInstr* instr);
void generateTAC(ASTNode* node);
char* generateTACExpr(ASTNode* node);

void printTAC();
void optimizeTAC();
void printOptimizedTAC();
void removeNOPs();
int isConstant(const char* s);


#endif
