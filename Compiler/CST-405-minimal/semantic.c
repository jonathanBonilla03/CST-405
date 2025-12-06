#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "semantic.h"
#include "ast.h"
#include "symtab.h"

/* Global error counter */
int semantic_errors = 0;

/* === Error reporting functions === */
void semanticError(const char* message, ...) {
    semantic_errors++;
    printf("✗ Semantic Error: ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
}

void semanticWarning(const char* message, ...) {
    printf("⚠ Semantic Warning: ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
}

/* === Specific error reporting === */
void reportSpecificError(ErrorType errorType, const char* details, ...) {
    semantic_errors++;
    va_list args;
    va_start(args, details);
    
    switch (errorType) {
        case ERROR_DUPLICATE_VAR:
            printf("✗ Declaration Error: Variable '%s' is already declared in this scope\n", details);
            printf("   Solution: Use a different variable name or remove the duplicate declaration\n");
            break;
            
        case ERROR_TYPE_MISMATCH_ASSIGN:
            printf("✗ Type Error: Cannot assign %s to %s\n", details, (char*)va_arg(args, char*));
            printf("   Solution: Use explicit type casting or ensure compatible types\n");
            break;
            
        case ERROR_TYPE_MISMATCH_BINOP:
            printf("✗ Type Error: Cannot perform operation between %s and %s\n", details, (char*)va_arg(args, char*));
            printf("   Solution: Ensure both operands are of compatible types\n");
            break;
            
        case ERROR_WRONG_ARG_COUNT:
            printf("✗ Function Call Error: %s expects %d arguments, but %d provided\n", 
                   details, va_arg(args, int), va_arg(args, int));
            printf("   Solution: Check function signature and provide correct number of arguments\n");
            break;
            
        case ERROR_ARRAY_INDEX_TYPE:
            printf("✗ Array Error: Array index must be integer type, found %s\n", details);
            printf("   Solution: Use an integer expression for array indexing\n");
            break;
            
        case ERROR_UNDECLARED_VAR:
            printf("✗ Declaration Error: Variable '%s' is not declared\n", details);
            printf("   Solution: Declare the variable before using it\n");
            break;
            
        case ERROR_UNDECLARED_FUNC:
            printf("✗ Declaration Error: Function '%s' is not declared\n", details);
            printf("   Solution: Ensure the function is declared or defined before calling\n");
            break;
            
        case ERROR_MISSING_SEMICOLON:
            printf("✗ Syntax Error: Missing semicolon after statement\n");
            printf("   Solution: Add ';' at the end of the statement\n");
            break;
            
        case ERROR_MISMATCHED_BRACE:
            printf("✗ Syntax Error: %s\n", details);
            printf("   Solution: Check that every '{' has a matching '}'\n");
            break;
    }
    
    va_end(args);
}

/* === Type compatibility checking === */
int checkTypeCompatibility(char* type1, char* type2) {
    if (!type1 || !type2) return 0;
    
    /* Exact match */
    if (strcmp(type1, type2) == 0) return 1;
    
    /* Allow implicit int to float conversion */
    if ((strcmp(type1, "int") == 0 && strcmp(type2, "float") == 0) ||
        (strcmp(type1, "float") == 0 && strcmp(type2, "int") == 0)) {
        return 1;
    }
    
    return 0;
}

/* === Array index type checking === */
int checkArrayIndexType(char* indexType) {
    if (!indexType) return 0;
    
    /* Only int indices allowed */
    if (strcmp(indexType, "int") == 0) {
        return 1;
    }
    
    reportSpecificError(ERROR_ARRAY_INDEX_TYPE, indexType);
    return 0;
}

/* === Function call validation === */
int checkFunctionCall(char* funcName, ASTNode* args) {
    Symbol* func = lookupSymbol(funcName);
    
    if (!func || !func->isFunction) {
        reportSpecificError(ERROR_UNDECLARED_FUNC, funcName);
        return 0;
    }
    
    /* Count provided arguments */
    int providedArgs = countArguments(args);
    
    if (providedArgs != func->paramCount) {
        reportSpecificError(ERROR_WRONG_ARG_COUNT, funcName, func->paramCount, providedArgs);
        return 0;
    }
    
    return 1;
}

/* === Return type checking === */
int checkReturnType(char* expectedType, char* actualType) {
    if (!expectedType) expectedType = "void";
    if (!actualType) actualType = "void";
    
    if (!checkTypeCompatibility(expectedType, actualType)) {
        semanticError("Return type mismatch: expected '%s', found '%s'", 
                     expectedType, actualType);
        return 0;
    }
    
    return 1;
}

/* === Assignment type checking === */
int checkAssignmentType(char* varType, char* exprType) {
    if (!checkTypeCompatibility(varType, exprType)) {
        reportSpecificError(ERROR_TYPE_MISMATCH_ASSIGN, exprType, varType);
        return 0;
    }
    
    return 1;
}

/* === Utility: Get expression type === */
char* getExpressionType(ASTNode* expr) {
    if (!expr) return "void";
    
    switch (expr->type) {
        case NODE_NUM: return "int";
        case NODE_FLOAT: return "float";
        case NODE_BOOL: return "bool";
        case NODE_CHAR: return "char";
        case NODE_STRING: return "string";
        
        case NODE_VAR: {
            Symbol* sym = lookupSymbol(expr->data.name);  /* var name stored in data.name */
            return sym ? sym->type : "unknown";
        }
        
        case NODE_ARRAY_ACCESS: {
            Symbol* sym = lookupSymbol(expr->data.array_access.name);
            if (sym && sym->isArray) {
                /* Check array index type */
                char* indexType = getExpressionType(expr->data.array_access.index);
                checkArrayIndexType(indexType);
                return sym->type;
            }
            return "unknown";
        }
        
        case NODE_BINOP: {
            char* leftType = getExpressionType(expr->data.binop.left);
            char* rightType = getExpressionType(expr->data.binop.right);
            
            /* Type checking for binary operations */
            if (!checkTypeCompatibility(leftType, rightType)) {
                reportSpecificError(ERROR_TYPE_MISMATCH_BINOP, leftType, rightType);
            }
            
            /* Return type rules */
            if (strcmp(leftType, "float") == 0 || strcmp(rightType, "float") == 0) {
                return "float";
            }
            return "int";
        }
        
        case NODE_FUNC_CALL: {
            Symbol* func = lookupSymbol(expr->data.func_call.name);
            if (func && func->isFunction) {
                /* Check function arguments */
                checkFunctionCall(expr->data.func_call.name, expr->data.func_call.args);
                return func->type;
            }
            return "unknown";
        }
        
        case NODE_CAST:
            return expr->data.cast.targetType;
            
        default:
            return "unknown";
    }
}

/* === Utility: Count function arguments === */
int countArguments(ASTNode* args) {
    if (!args) return 0;
    
    /* If it's not an argument list, it's a single argument */
    if (args->type != NODE_ARG_LIST) {
        return 1;
    }
    
    /* For ARG_LIST: item = previous arguments, next = current argument */
    int count = 1; /* Count the next (current argument) */
    ASTNode* previous = args->data.list.item;
    
    /* Recursively count the previous arguments */
    if (previous) {
        count += countArguments(previous);
    }
    
    return count;
}