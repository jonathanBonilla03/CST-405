#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Define the global symbol table */
SymbolTable symtab;

/* Initialize an empty symbol table */
void initSymTab() {
    for (int i = 0; i < HASH_SIZE; i++) {
        symtab.buckets[i] = NULL;
    }
    symtab.count = 0;
    symtab.nextOffset = 0;
    symtab.lookups = 0;
    symtab.collisions = 0;
    printf("SYMBOL TABLE: Initialized\n");
    printSymTab();
}

/* Add a new variable to the symbol table */
int addVar(char* name) {
    unsigned int h = hash(name);
    Symbol* curr = symtab.buckets[h];

    /* Check for duplicate declaration */
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return -1;  /* already exists */
        }
        curr = curr->next;
    }

    /* Create a new symbol */
    Symbol* sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->offset = symtab.nextOffset;
    sym->isArray = 0;
    sym->arraySize = 0;
    sym->next = symtab.buckets[h];

    /* Insert into bucket */
    if (symtab.buckets[h] != NULL) {
        symtab.collisions++;
    }
    symtab.buckets[h] = sym;

    symtab.nextOffset += 4; /* size of int */
    symtab.count++;

    printf("SYMBOL TABLE: Added variable '%s' at offset %d\n", 
           name, sym->offset);
    printSymTab();

    return sym->offset;
}

int addArrayVar(char* name, int size) {
    unsigned int h = hash(name);
    Symbol* curr = symtab.buckets[h];

    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            printf("SYMBOL TABLE: Failed to add array '%s' - already declared\n", name);
            return -1;
        }
        curr = curr->next;
    }

    Symbol* sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->offset = symtab.nextOffset;
    sym->isArray = 1;
    sym->arraySize = size;
    sym->next = symtab.buckets[h];

    if (symtab.buckets[h] != NULL) {
        symtab.collisions++;
    }
    symtab.buckets[h] = sym;

    symtab.nextOffset += size * 4;
    symtab.count++;

    printf("SYMBOL TABLE: Added array '%s[%d]' at offset %d\n",
           name, size, sym->offset);
    printSymTab();

    return sym->offset;
}

int isArrayVar(char* name) {
    unsigned int h = hash(name);
    Symbol* curr = symtab.buckets[h];
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr->isArray;
        }
        curr = curr->next;
    }
    return 0;
}

int getArraySize(char* name) {
    unsigned int h = hash(name);
    Symbol* curr = symtab.buckets[h];
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr->isArray ? curr->arraySize : -1;
        }
        curr = curr->next;
    }
    return 0;  /* not found */
}

/* Look up a variable's stack offset */
int getVarOffset(char* name) {
    symtab.lookups++;
    unsigned int h = hash(name);
    Symbol* curr = symtab.buckets[h];
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr->offset;
        }
        curr = curr->next;
    }
    printf("SYMBOL TABLE: Variable '%s' not found\n", name);
    return -1;
}

int isVarDeclared(char* name) {
    return getVarOffset(name) != -1;
}

/* djb2 hash */
unsigned int hash(char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

/* Print current symbol table contents */
void printSymTab() {
    printf("\n=== SYMBOL TABLE STATE ===\n");
    printf("Count: %d, Next Offset: %d\n", symtab.count, symtab.nextOffset);

    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol* curr = symtab.buckets[i];
        if (curr) {
            printf("Bucket[%d]:\n", i);
            while (curr) {
                if (curr->isArray) {
                    printf("  %s[%d] -> offset %d\n",
                           curr->name, curr->arraySize, curr->offset);
                } else {
                    printf("  %s -> offset %d\n", curr->name, curr->offset);
                }
                curr = curr->next;
            }
        }
    }
    printf("==========================\n\n");
}
