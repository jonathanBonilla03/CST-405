#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* ============================================================
 * Symbol Table Implementation with Scoped Hierarchy
 * Supports variables, arrays, functions, and parameters.
 * ============================================================ */

SymbolTable symtab;

/* === Initialize global symbol table === */
void initSymTab() {
    Scope* globalScope = malloc(sizeof(Scope));
    globalScope->count = 0;
    globalScope->nextLocalOffset = 0;
    globalScope->nextParamOffset = 0;
    globalScope->parent = NULL;

    symtab.currentScope = globalScope;
    symtab.globalScope  = globalScope;

    /* Add built-in functions */
    char* inputParamTypes[] = {};
    addFunction("input", "int", inputParamTypes, 0);
    
    char* outputParamTypes[] = {"int"};
    addFunction("output", "void", outputParamTypes, 1);
    
    /* Add string I/O functions */
    addFunction("inputString", "string", inputParamTypes, 0);
    
    char* outputStringParamTypes[] = {"string"};
    addFunction("outputString", "void", outputStringParamTypes, 1);
    
    /* Add type conversion functions */
    char* charToStringParams[] = {"char"};
    addFunction("charToString", "string", charToStringParams, 1);
    
    char* intToStringParams[] = {"int"};
    addFunction("intToString", "string", intToStringParams, 1);
    
    char* floatToStringParams[] = {"float"};
    addFunction("floatToString", "string", floatToStringParams, 1);

    printf("SYMBOL TABLE: Initialized with global scope and built-in functions\n");
    printSymTab();
}

/* === Push new scope (e.g., entering a function) === */
void enterScope() {
    Scope* newScope = malloc(sizeof(Scope));
    newScope->count = 0;
    newScope->nextLocalOffset = -4;  /* Locals start below $fp */
    newScope->nextParamOffset = -4;   /* First parameter at -4($fp) */
    newScope->parent = symtab.currentScope;

    symtab.currentScope = newScope;
    printf("SYMBOL TABLE: Entered new scope\n");
}

/* === Pop scope (e.g., leaving a function) === */
void exitScope() {
    if (symtab.currentScope == symtab.globalScope) {
        printf("SYMBOL TABLE: Warning - Cannot exit global scope\n");
        return;
    }

    Scope* oldScope = symtab.currentScope;
    symtab.currentScope = oldScope->parent;

    /* Clean up memory for strings */
    for (int i = 0; i < oldScope->count; i++) {
        Symbol* sym = &oldScope->vars[i];
        free(sym->name);
        free(sym->type);
        if (sym->isFunction && sym->paramTypes) {
            for (int j = 0; j < sym->paramCount; j++)
                free(sym->paramTypes[j]);
            free(sym->paramTypes);
        }
    }

    free(oldScope);
    printf("SYMBOL TABLE: Exited scope\n");
}

/* === Add a variable to current scope === */
int addVar(char* name, char* type) {
    Scope* scope = symtab.currentScope;

    if (isInCurrentScope(name)) {
        printf("SYMBOL TABLE: Duplicate variable '%s'\n", name);
        return -1;
    }
    if (scope->count >= MAX_VARS) {
        printf("SYMBOL TABLE: Error - too many variables\n");
        return -1;
    }

    Symbol* sym = &scope->vars[scope->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isFunction = 0;
    sym->isArray = 0;
    sym->arraySize = 0;
    sym->paramCount = 0;
    sym->paramTypes = NULL;

    sym->offset = scope->nextLocalOffset;
    scope->nextLocalOffset -= 4;

    printf("SYMBOL TABLE: Added variable '%s' (%s) offset %d\n",
           name, type, sym->offset);
    return sym->offset;
}

/* === Add an array variable to current scope === */
int addArrayVar(char* name, char* type, int size) {
    Scope* scope = symtab.currentScope;

    if (isInCurrentScope(name)) {
        printf("SYMBOL TABLE: Duplicate array '%s'\n", name);
        return -1;
    }

    Symbol* sym = &scope->vars[scope->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isFunction = 0;
    sym->isArray = 1;
    sym->arraySize = size;
    sym->paramCount = 0;
    sym->paramTypes = NULL;

    sym->offset = scope->nextLocalOffset;
    scope->nextLocalOffset -= size * 4;

    printf("SYMBOL TABLE: Added array '%s[%d]' (%s) offset %d\n",
           name, size, type, sym->offset);
    return sym->offset;
}

/* === Add a function (always in global scope) === */
int addFunction(char* name, char* returnType,
                char** paramTypes, int paramCount) {
    Scope* globalScope = symtab.globalScope;

    for (int i = 0; i < globalScope->count; i++) {
        if (strcmp(globalScope->vars[i].name, name) == 0) {
            printf("SYMBOL TABLE: Duplicate function '%s'\n", name);
            return -1;
        }
    }

    Symbol* sym = &globalScope->vars[globalScope->count++];
    sym->name = strdup(name);
    sym->type = strdup(returnType);
    sym->isFunction = 1;
    sym->isArray = 0;
    sym->arraySize = 0;
    sym->offset = -1;
    sym->paramCount = paramCount;

    if (paramCount > 0) {
        sym->paramTypes = malloc(paramCount * sizeof(char*));
        for (int i = 0; i < paramCount; i++)
            sym->paramTypes[i] = strdup(paramTypes[i]);
    } else {
        sym->paramTypes = NULL;
    }

    printf("SYMBOL TABLE: Added function '%s' -> %s (%d params)\n",
           name, returnType, paramCount);
    return 0;
}

/* === Add a parameter (to current scope, positive offsets) === */
int addParameter(char* name, char* type) {
    Scope* scope = symtab.currentScope;

    if (isInCurrentScope(name)) {
        printf("SYMBOL TABLE: Duplicate parameter '%s'\n", name);
        return -1;
    }

    Symbol* sym = &scope->vars[scope->count++];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->isFunction = 0;
    sym->isArray = 0;
    sym->arraySize = 0;
    sym->paramCount = 0;
    sym->paramTypes = NULL;

    sym->offset = scope->nextParamOffset;
    scope->nextParamOffset -= 4;  /* Parameters go to lower addresses */

    printf("SYMBOL TABLE: Added parameter '%s' (%s) offset %d\n",
           name, type, sym->offset);
    return sym->offset;
}

/* === Lookup symbol in current + parent scopes === */
Symbol* lookupSymbol(char* name) {
    Scope* scope = symtab.currentScope;
    while (scope) {
        for (int i = 0; i < scope->count; i++)
            if (strcmp(scope->vars[i].name, name) == 0)
                return &scope->vars[i];
        scope = scope->parent;
    }
    return NULL;
}

/* === Check only current scope === */
int isInCurrentScope(char* name) {
    Scope* scope = symtab.currentScope;
    for (int i = 0; i < scope->count; i++)
        if (strcmp(scope->vars[i].name, name) == 0)
            return 1;
    return 0;
}

/* === Lookup variable offset === */
int getVarOffset(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym && !sym->isFunction)
        return sym->offset;
    printf("SYMBOL TABLE: Variable '%s' not found\n", name);
    return -1;
}

/* === Variable checks === */
int isVarDeclared(char* name) {
    Symbol* sym = lookupSymbol(name);
    return (sym && !sym->isFunction);
}

int isArrayVar(char* name) {
    Symbol* sym = lookupSymbol(name);
    return (sym && sym->isArray);
}

int getArraySize(char* name) {
    Symbol* sym = lookupSymbol(name);
    return (sym && sym->isArray) ? sym->arraySize : -1;
}

/* === Adjust local offset after parameters are allocated === */
void adjustLocalOffsetAfterParams(int paramBytes) {
    Scope* scope = symtab.currentScope;
    scope->nextLocalOffset = -(paramBytes + 4);  /* Start after params */
}

/* === Printing Functions === */
void printCurrentScope() {
    Scope* s = symtab.currentScope;
    printf("\n=== CURRENT SCOPE ===\n");
    printf("Count: %d | nextLocalOffset: %d | nextParamOffset: %d\n",
           s->count, s->nextLocalOffset, s->nextParamOffset);

    for (int i = 0; i < s->count; i++) {
        Symbol* sym = &s->vars[i];
        if (sym->isFunction)
            printf("FUNC %s() -> %s (%d params)\n",
                   sym->name, sym->type, sym->paramCount);
        else if (sym->isArray)
            printf("ARRAY %s[%d] : %s (offset %d)\n",
                   sym->name, sym->arraySize, sym->type, sym->offset);
        else
            printf("VAR %s : %s (offset %d)\n",
                   sym->name, sym->type, sym->offset);
    }
    printf("====================\n\n");
}

void printSymTab() {
    printCurrentScope();
}

void printAllScopes() {
    printf("\n=== ALL SCOPES ===\n");
    Scope* s = symtab.currentScope;
    int level = 0;
    while (s) {
        printf("Scope Level %d%s\n", level,
               (s == symtab.globalScope) ? " (GLOBAL)" : "");
        printf("Count: %d | nextLocalOffset: %d | nextParamOffset: %d\n",
               s->count, s->nextLocalOffset, s->nextParamOffset);
        for (int i = 0; i < s->count; i++) {
            Symbol* sym = &s->vars[i];
            if (sym->isFunction)
                printf("  FUNC %s() -> %s (%d params)\n",
                       sym->name, sym->type, sym->paramCount);
            else if (sym->isArray)
                printf("  ARRAY %s[%d] : %s (offset %d)\n",
                       sym->name, sym->arraySize, sym->type, sym->offset);
            else
                printf("  VAR %s : %s (offset %d)\n",
                       sym->name, sym->type, sym->offset);
        }
        s = s->parent;
        level++;
    }
    printf("====================\n\n");
}

/* === Comprehensive symbol table display for compiler output === */
void printSymbolTable() {
    printf("\n┌─── SYMBOL TABLE SUMMARY ────────────────────────────────┐\n");
    
    // Count totals across all scopes
    int totalSymbols = 0;
    int totalFunctions = 0;
    int totalVariables = 0;
    int totalArrays = 0;
    
    Scope* s = symtab.currentScope;
    while (s) {
        for (int i = 0; i < s->count; i++) {
            Symbol* sym = &s->vars[i];
            totalSymbols++;
            if (sym->isFunction) totalFunctions++;
            else if (sym->isArray) totalArrays++;
            else totalVariables++;
        }
        s = s->parent;
    }
    
    printf("│ Total Symbols: %d (Functions: %d, Variables: %d, Arrays: %d) │\n",
           totalSymbols, totalFunctions, totalVariables, totalArrays);
    printf("└──────────────────────────────────────────────────────────┘\n");
    
    // Display detailed scope information
    printAllScopes();
}
