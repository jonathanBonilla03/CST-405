#ifndef SYMTAB_H
#define SYMTAB_H

/* ============================================================
 * SYMBOL TABLE WITH SCOPING SUPPORT
 * Tracks declared variables and functions across nested scopes.
 * Manages stack offsets for parameters (+8, +12...) and locals (-4, -8...).
 * Used during semantic analysis and code generation.
 * ============================================================ */

#define MAX_VARS   1000   /* Max number of variables per scope */
#define MAX_PARAMS 20     /* Max number of parameters per function */

/* === Symbol Entry === */
typedef struct {
    char* name;           /* Identifier name */
    char* type;           /* Type (e.g., "int", "float", "bool") or return type for functions */
    int offset;           /* Stack offset from $fp (vars/params only) */
    int isFunction;       /* 1 = function, 0 = variable */
    int isArray;          /* 1 = array variable */
    int arraySize;        /* Array length (if isArray) */
    int paramCount;       /* Number of parameters (if function) */
    char** paramTypes;    /* Parameter type list (if function) */
} Symbol;

/* === Scope Structure === */
typedef struct Scope {
    Symbol vars[MAX_VARS];
    int count;             /* Number of symbols in this scope */

    /* Separate offset spaces relative to $fp */
    int nextLocalOffset;   /* Locals: -4, -8, -12... */
    int nextParamOffset;   /* Params: +8, +12, +16... */

    struct Scope* parent;  /* Link to enclosing scope */
} Scope;

/* === Symbol Table === */
typedef struct {
    Scope* currentScope;   /* Active scope (top of stack) */
    Scope* globalScope;    /* Persistent global scope */
} SymbolTable;

/* === Global Symbol Table Instance === */
extern SymbolTable symtab;

/* === Symbol Table Operations === */
void initSymTab();               /* Initialize global scope */
void enterScope();               /* Push new function/block scope */
void exitScope();                /* Pop current scope */

/* === Variable Operations === */
int addVar(char* name, char* type);                /* Add variable (local/global) */
int addArrayVar(char* name, char* type, int size); /* Add array variable */

/* === Function Operations === */
int addFunction(char* name, char* returnType,
                char** paramTypes, int paramCount); /* Add function to global scope */
int addParameter(char* name, char* type);          /* Add parameter to current scope */
void adjustLocalOffsetAfterParams(int paramBytes); /* Adjust local offset after params */

/* === Lookup Operations === */
Symbol* lookupSymbol(char* name);     /* Search current + parent scopes */
int isInCurrentScope(char* name);     /* Check for duplicates */
int getVarOffset(char* name);         /* Get stack offset for variable */
int isVarDeclared(char* name);        /* Check if variable is declared */
int isArrayVar(char* name);           /* Check if symbol is array */
int getArraySize(char* name);         /* Return array size */

/* === Debugging and Printing === */
void printCurrentScope();             /* Print symbols in current scope */
void printSymTab();                   /* Alias for printCurrentScope() */
void printAllScopes();                /* Print all nested scopes */

#endif
