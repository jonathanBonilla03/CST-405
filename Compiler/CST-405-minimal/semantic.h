#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symtab.h"

/* Error counting */
extern int semantic_errors;

/* Semantic analysis functions */
int checkTypeCompatibility(char* type1, char* type2);
int checkArrayIndexType(char* indexType);
int checkFunctionCall(char* funcName, ASTNode* args);
int checkReturnType(char* expectedType, char* actualType);
int checkAssignmentType(char* varType, char* exprType);

/* Error types for specific detection */
typedef enum {
    ERROR_DUPLICATE_VAR,
    ERROR_TYPE_MISMATCH_ASSIGN,
    ERROR_TYPE_MISMATCH_BINOP,
    ERROR_WRONG_ARG_COUNT,
    ERROR_ARRAY_INDEX_TYPE,
    ERROR_UNDECLARED_VAR,
    ERROR_UNDECLARED_FUNC,
    ERROR_MISSING_SEMICOLON,
    ERROR_MISMATCHED_BRACE
} ErrorType;

/* Error reporting */
void semanticError(const char* message, ...);
void semanticWarning(const char* message, ...);
void reportSpecificError(ErrorType errorType, const char* details, ...);

/* Type checking utilities */
char* getExpressionType(ASTNode* expr);
int countArguments(ASTNode* args);

#endif /* SEMANTIC_H */