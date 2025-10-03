#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

typedef struct {
    char* reg_name;
    char* var_name;  // Variable currently in this register
    int is_free;
    int last_used;   // For LRU eviction
} Register;

typedef struct {
    Register temp_regs[8];  // $t0-$t7
    Register saved_regs[8]; // $s0-$s7
    int clock;              // For LRU tracking
} RegisterAllocator;

extern RegisterAllocator reg_alloc;

void generateMIPS(ASTNode* root, const char* filename);

#endif