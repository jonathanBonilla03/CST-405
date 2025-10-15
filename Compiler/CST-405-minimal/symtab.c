#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Define the global symbol table */
SymbolTable symtab;

/* Initialize an empty symbol table with global scope */
void initSymTab() {
    // Create global scope
    Scope* globalScope = malloc(sizeof(Scope));
    globalScope->count = 0;
    globalScope->nextOffset = 0;
    globalScope->parent = NULL;
    
    symtab.currentScope = globalScope;
    symtab.globalScope = globalScope;
    
    printf("SYMBOL TABLE: Initialized with global scope\n");
    printSymTab();
}

/* Push new scope (entering function) */
void enterScope() {
    Scope* newScope = malloc(sizeof(Scope));
    newScope->count = 0;
    newScope->nextOffset = 0;
    newScope->parent = symtab.currentScope;
    
    symtab.currentScope = newScope;
    
    printf("SYMBOL TABLE: Entered new scope\n");
}

/* Pop scope (leaving function) */
void exitScope() {
    if (symtab.currentScope == symtab.globalScope) {
        printf("SYMBOL TABLE: Warning - Cannot exit global scope\n");
        return;
    }
    
    Scope* oldScope = symtab.currentScope;
    symtab.currentScope = oldScope->parent;
    
    // Free parameter types for functions in this scope
    for (int i = 0; i < oldScope->count; i++) {
        if (oldScope->vars[i].isFunction && oldScope->vars[i].paramTypes) {
            for (int j = 0; j < oldScope->vars[i].paramCount; j++) {
                free(oldScope->vars[i].paramTypes[j]);
            }
            free(oldScope->vars[i].paramTypes);
        }
        free(oldScope->vars[i].name);
        free(oldScope->vars[i].type);
    }
    
    free(oldScope);
    printf("SYMBOL TABLE: Exited scope\n");
}

/* Add a new variable to current scope */
int addVar(char* name, char* type) {
    Scope* scope = symtab.currentScope;
    
    /* Check for duplicate declaration in current scope only */
    if (isInCurrentScope(name)) {
        printf("SYMBOL TABLE: Failed to add variable '%s' - already declared in current scope\n", name);
        return -1;
    }
    
    if (scope->count >= MAX_VARS) {
        printf("SYMBOL TABLE: Error - Maximum variables exceeded in scope\n");
        return -1;
    }
    
    /* Create new symbol */
    Symbol* sym = &scope->vars[scope->count];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->offset = scope->nextOffset;
    sym->isFunction = 0;
    sym->isArray = 0;
    sym->arraySize = 0;
    sym->paramCount = 0;
    sym->paramTypes = NULL;
    
    scope->nextOffset += 4; /* size of int/float/bool */
    scope->count++;
    
    printf("SYMBOL TABLE: Added variable '%s' (%s) at offset %d\n", 
           name, type, sym->offset);
    printCurrentScope();
    
    return sym->offset;
}

/* Add a new array variable to current scope */
int addArrayVar(char* name, char* type, int size) {
    Scope* scope = symtab.currentScope;
    
    /* Check for duplicate declaration in current scope only */
    if (isInCurrentScope(name)) {
        printf("SYMBOL TABLE: Failed to add array '%s' - already declared in current scope\n", name);
        return -1;
    }
    
    if (scope->count >= MAX_VARS) {
        printf("SYMBOL TABLE: Error - Maximum variables exceeded in scope\n");
        return -1;
    }
    
    /* Create new symbol */
    Symbol* sym = &scope->vars[scope->count];
    sym->name = strdup(name);
    sym->type = strdup(type);
    sym->offset = scope->nextOffset;
    sym->isFunction = 0;
    sym->isArray = 1;
    sym->arraySize = size;
    sym->paramCount = 0;
    sym->paramTypes = NULL;
    
    scope->nextOffset += size * 4;
    scope->count++;
    
    printf("SYMBOL TABLE: Added array '%s[%d]' (%s) at offset %d\n",
           name, size, type, sym->offset);
    printCurrentScope();
    
    return sym->offset;
}

/* Add function to global scope */
int addFunction(char* name, char* returnType, char** paramTypes, int paramCount) {
    Scope* globalScope = symtab.globalScope;
    
    /* Check for duplicate function declaration in global scope */
    for (int i = 0; i < globalScope->count; i++) {
        if (strcmp(globalScope->vars[i].name, name) == 0) {
            printf("SYMBOL TABLE: Failed to add function '%s' - already declared\n", name);
            return -1;
        }
    }
    
    if (globalScope->count >= MAX_VARS) {
        printf("SYMBOL TABLE: Error - Maximum symbols exceeded in global scope\n");
        return -1;
    }
    
    /* Create new function symbol */
    Symbol* sym = &globalScope->vars[globalScope->count];
    sym->name = strdup(name);
    sym->type = strdup(returnType);
    sym->offset = -1; /* Functions don't have stack offsets */
    sym->isFunction = 1;
    sym->isArray = 0;
    sym->arraySize = 0;
    sym->paramCount = paramCount;
    
    /* Copy parameter types */
    if (paramCount > 0) {
        sym->paramTypes = malloc(paramCount * sizeof(char*));
        for (int i = 0; i < paramCount; i++) {
            sym->paramTypes[i] = strdup(paramTypes[i]);
        }
    } else {
        sym->paramTypes = NULL;
    }
    
    globalScope->count++;
    
    printf("SYMBOL TABLE: Added function '%s' returning '%s' with %d parameters\n",
           name, returnType, paramCount);
    
    return 0; /* Success */
}

/* Add parameter to current scope (should be function scope) */
int addParameter(char* name, char* type) {
    return addVar(name, type); /* Parameters are just variables in function scope */
}

int isArrayVar(char* name) {
    Symbol* sym = lookupSymbol(name);
    return sym ? sym->isArray : 0;
}

int getArraySize(char* name) {
    Symbol* sym = lookupSymbol(name);
    return (sym && sym->isArray) ? sym->arraySize : -1;
}

/* Search current + parent scopes */
Symbol* lookupSymbol(char* name) {
    Scope* scope = symtab.currentScope;

    // Search from current scope up to global
    while (scope != NULL) {
        for (int i = 0; i < scope->count; i++) {
            if (strcmp(scope->vars[i].name, name) == 0) {
                return &scope->vars[i];  // Found it
            }
        }
        scope = scope->parent;  // Try parent scope
    }
    return NULL;  // Not found in any scope
}

/* Check only current scope */
int isInCurrentScope(char* name) {
    Scope* scope = symtab.currentScope;
    for (int i = 0; i < scope->count; i++) {
        if (strcmp(scope->vars[i].name, name) == 0) {
            return 1;  // Found in current scope
        }
    }
    return 0;  // Not in current scope
}

/* Look up a variable's stack offset */
int getVarOffset(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym && !sym->isFunction) {
        return sym->offset;
    }
    printf("SYMBOL TABLE: Variable '%s' not found\n", name);
    return -1;
}

int isVarDeclared(char* name) {
    Symbol* sym = lookupSymbol(name);
    return (sym && !sym->isFunction) ? 1 : 0;
}

/* Print current scope only */
void printCurrentScope() {
    Scope* scope = symtab.currentScope;
    printf("\n=== CURRENT SCOPE ===\n");
    printf("Count: %d, Next Offset: %d\n", scope->count, scope->nextOffset);
    
    for (int i = 0; i < scope->count; i++) {
        Symbol* sym = &scope->vars[i];
        if (sym->isFunction) {
            printf("  FUNC %s() -> %s (params: %d)\n",
                   sym->name, sym->type, sym->paramCount);
            for (int j = 0; j < sym->paramCount; j++) {
                printf("    param[%d]: %s\n", j, sym->paramTypes[j]);
            }
        } else if (sym->isArray) {
            printf("  ARRAY %s[%d] -> %s, offset %d\n",
                   sym->name, sym->arraySize, sym->type, sym->offset);
        } else {
            printf("  VAR %s -> %s, offset %d\n",
                   sym->name, sym->type, sym->offset);
        }
    }
    printf("====================\n\n");
}

/* Print current symbol table contents (current scope) */
void printSymTab() {
    printCurrentScope();
}

/* Print all scopes in the stack */
void printAllScopes() {
    printf("\n=== ALL SCOPES ===\n");
    Scope* scope = symtab.currentScope;
    int level = 0;
    
    while (scope != NULL) {
        printf("Scope Level %d %s:\n", level, 
               (scope == symtab.globalScope) ? "(GLOBAL)" : "");
        printf("  Count: %d, Next Offset: %d\n", scope->count, scope->nextOffset);
        
        for (int i = 0; i < scope->count; i++) {
            Symbol* sym = &scope->vars[i];
            if (sym->isFunction) {
                printf("    FUNC %s() -> %s (params: %d)\n",
                       sym->name, sym->type, sym->paramCount);
            } else if (sym->isArray) {
                printf("    ARRAY %s[%d] -> %s, offset %d\n",
                       sym->name, sym->arraySize, sym->type, sym->offset);
            } else {
                printf("    VAR %s -> %s, offset %d\n",
                       sym->name, sym->type, sym->offset);
            }
        }
        
        scope = scope->parent;
        level++;
    }
    printf("==================\n\n");
}
