#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE
 * Tracks all declared variables during compilation
 * Maps variable names to their memory locations (stack offsets)
 * Used for semantic checking and code generation
 */

#define MAX_VARS 1000  /* Maximum number of variables supported */
#define HASH_SIZE 211 /* Size of hash table for variable lookup */

typedef struct Symbol {
    char* name;
    int type;
    int offset;
    int isArray;
    int arraySize;
    struct Symbol* next;  // linked list in each bucket
} Symbol;

/* SYMBOL TABLE STRUCTURE */
typedef struct {
    Symbol* buckets[HASH_SIZE]; /* Hash table for quick lookup */
    int count;              /* Number of variables declared */
    int nextOffset;         /* Next available stack offset */
    int lookups;
    int collisions;
} SymbolTable;

/* Global symbol table instance */
extern SymbolTable symtab;

/* SYMBOL TABLE OPERATIONS */
void initSymTab();               /* Initialize empty symbol table */
int addVar(char* name);          /* Add new variable, returns offset or -1 if duplicate */
int addArrayVar(char* name, int size); /* Add new array variable, returns offset or -1 if duplicate */
int isArrayVar(char* name); /* Check if variable is an array (1=yes, 0=no) */
int getArraySize(char* name); /* Get size of array variable, -1 if not an array or not found */
int getVarOffset(char* name);    /* Get stack offset for variable, -1 if not found */
int isVarDeclared(char* name);   /* Check if variable exists (1=yes, 0=no) */
void printSymTab();              /* Print current symbol table contents */
unsigned int hash(char* str); /* Hash function for variable names */

#endif