/* SYMBOL TABLE IMPLEMENTATION
 * Manages variable declarations and lookups
 * Essential for semantic analysis (checking if variables are declared)
 * Provides memory layout information for code generation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Global symbol table instance */
SymbolTable symtab;

/* Initialize an empty symbol table */
void initSymTab() {
    symtab.count = 0;       /* No variables yet */
    symtab.nextOffset = 0;  /* Start at stack offset 0 */
    printf("SYMBOL TABLE: Initialized\n");
    printSymTab();
}

/* Add a new variable to the symbol table */
int addVar(char* name) {
    /* Check for duplicate declaration */
    if (isVarDeclared(name)) {
        return -1;  /* Error: variable already exists */
    }
    
    /* Add new symbol entry */
    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    
    /* Advance offset by 4 bytes (size of int in MIPS) */
    symtab.nextOffset += 4;
    symtab.count++;

    printf("SYMBOL TABLE: Added variable '%s' at offset %d\n", name, symtab.vars[symtab.count - 1].offset);
    printSymTab();
    
    /* Return the offset for this variable */
    return symtab.vars[symtab.count - 1].offset;
}

int addArrayVar(char* name, int size) {
    /* Check for duplicate declaration */
    if (isVarDeclared(name)) {
        printf("SYMBOL TABLE: Failed to add array '%s' - already declared\n", name);
        return -1;  /* Error: variable already exists */
    }
    
    /* Add new symbol entry */
    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].isArray = 1;  /* Mark as array */
    symtab.vars[symtab.count].arraySize = size; /* Store array size */
    
    /* Advance offset by size * 4 bytes (size of int in MIPS) */
    symtab.nextOffset += size * 4;
    symtab.count++;

    printf("SYMBOL TABLE: Added array '%s[%d]' at offset %d\n",
           name, size, symtab.vars[symtab.count - 1].offset);
    printSymTab();
    
    /* Return the offset for this array variable */
    return symtab.vars[symtab.count - 1].offset;
}

int isArrayVar(char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0) {
            return symtab.vars[i].isArray;  /* Return 1 if array, 0 if not */
        }
    }
    return 0;  /* Not found, treat as non-array */
}

int getArraySize(char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0) {
            if (symtab.vars[i].isArray) {
                return symtab.vars[i].arraySize;  /* Return array size */
            } else {
                return -1;  /* Not an array */
            }
        }
    }
    return 0;  /* Not found */
}

/* Look up a variable's stack offset */
int getVarOffset(char* name) {
    /* Linear search through symbol table */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0) {
            return symtab.vars[i].offset;  /* Found it */
        }
    }
    printf("SYMBOL TABLE: Variable '%s' not found\n", name);
    return -1;  /* Variable not found - semantic error */
}

/* Check if a variable has been declared */
int isVarDeclared(char* name) {
    return getVarOffset(name) != -1;  /* True if found, false otherwise */
}

/* Print current symbol table contents for debugging/tracing */
void printSymTab() {
    printf("\n=== SYMBOL TABLE STATE ===\n");
    printf("Count: %d, Next Offset: %d\n", symtab.count, symtab.nextOffset);
    if (symtab.count == 0) {
        printf("(empty)\n");
    } else {
        printf("Variables:\n");
        for (int i = 0; i < symtab.count; i++) {
    if (symtab.vars[i].isArray) {
        printf("  [%d] %s[%d] -> offset %d\n", i, symtab.vars[i].name, symtab.vars[i].arraySize, symtab.vars[i].offset);
    } else {
        printf("  [%d] %s -> offset %d\n", i, symtab.vars[i].name, symtab.vars[i].offset);
    }
}
    }
    printf("==========================\n\n");
}