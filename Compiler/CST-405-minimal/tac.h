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
    TAC_EXP,     
    TAC_ASSIGN,  
    TAC_PRINT,   
    TAC_DECL,     
    TAC_ARRAY_DECL,    
    TAC_ARRAY_ASSIGN,  
    TAC_ARRAY_ACCESS,
    TAC_NOP,
    TAC_NEG,
    TAC_IFZ,
    TAC_JUMP,
    TAC_LABEL,
    TAC_AND,
    TAC_OR,
    TAC_NOT,
    TAC_LT,
    TAC_GT,
    TAC_LE,
    TAC_GE,
    TAC_EQ,
    TAC_NE,
    TAC_PARAM,       // Pass parameter: PARAM arg
    TAC_CALL,        // Function call: result = CALL func_name, num_params
    TAC_RETURN,      // Return value: RETURN value
    TAC_FUNC_BEGIN,  // Mark function start: FUNC_BEGIN name
    TAC_FUNC_END     // Mark function end: FUNC_END name
} TACOp;

/* TAC INSTRUCTION STRUCTURE */
typedef struct TACInstr {
    TACOp op;
    char* arg1;
    char* arg2;
    char* result;
    int paramCount;  // For CALL instruction: number of params
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
TACInstr* createTACWithParamCount(TACOp op, char* arg1, char* arg2, char* result, int paramCount);
void appendTAC(TACInstr* instr);
void appendOptimizedTAC(TACInstr* instr);
void generateTAC(ASTNode* node);
char* generateTACExpr(ASTNode* node);

void printTAC();
void optimizeTAC();
void printOptimizedTAC();
void removeNOPs();
void eliminateDeadCode();
void inlineSmallFunctions();
int isConstant(const char* s);
int isSmallFunction(const char* funcName);
char* newTACLabel();


#endif
