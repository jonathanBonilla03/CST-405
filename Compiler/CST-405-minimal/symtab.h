#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE WITH SCOPING SUPPORT
 * Tracks all declared variables and functions during compilation
 * Supports nested scopes for proper variable shadowing and function scoping
 * Maps names to their memory locations and type information
 * Used for semantic checking and code generation
 */

#define MAX_VARS 1000  /* Maximum number of variables per scope */
#define MAX_PARAMS 20  /* Maximum number of function parameters */

/* Enhanced symbol entry */
typedef struct {
    char* name;
    char* type;      // Variable type ("int", "float", "bool") or function signature
    int offset;      // Stack offset (for variables)
    int isFunction;  // 1 if this is a function, 0 if variable
    int isArray;     // 1 if this is an array variable
    int arraySize;   // Size of array (if isArray = 1)
    int paramCount;  // Number of parameters (if function)
    char** paramTypes; // Array of parameter types (if function)
} Symbol;

/* Scope structure */
typedef struct Scope {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;
    struct Scope* parent;  // Link to enclosing scope
} Scope;

/* Symbol table with scope stack */
typedef struct {
    Scope* currentScope;   // Top of scope stack
    Scope* globalScope;    // Always points to global
} SymbolTable;

/* Global symbol table instance */
extern SymbolTable symtab;

/* SYMBOL TABLE OPERATIONS */
void initSymTab();               /* Initialize empty symbol table with global scope */
void enterScope();               /* Push new scope (entering function) */
void exitScope();                /* Pop scope (leaving function) */

/* Variable operations */
int addVar(char* name, char* type);          /* Add variable to current scope, returns offset or -1 if duplicate */
int addArrayVar(char* name, char* type, int size); /* Add array variable, returns offset or -1 if duplicate */

/* Function operations */
int addFunction(char* name, char* returnType,
                char** paramTypes, int paramCount); /* Add function to global scope */
int addParameter(char* name, char* type);    /* Add parameter to current scope */

/* Lookup operations */
Symbol* lookupSymbol(char* name);            /* Search current + parent scopes */
int isInCurrentScope(char* name);            /* Check only current scope */
int getVarOffset(char* name);                /* Get stack offset for variable, -1 if not found */
int isVarDeclared(char* name);               /* Check if variable exists (1=yes, 0=no) */
int isArrayVar(char* name);                  /* Check if variable is an array (1=yes, 0=no) */
int getArraySize(char* name);                /* Get size of array variable, -1 if not array or not found */

/* Debug and utility */
void printSymTab();                          /* Print current symbol table contents */
void printCurrentScope();                    /* Print only current scope */
void printAllScopes();                       /* Print all scopes in the stack */

#endif