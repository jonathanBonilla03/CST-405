#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"
#include "symtab.h"
#include <string.h>

FILE* output;
int tempReg = 0;
RegisterAllocator reg_alloc;

/* Register allocator init */
void init_register_allocator() {
    for(int i = 0; i < 8; i++) {
        char name[4];
        sprintf(name, "$t%d", i);
        reg_alloc.temp_regs[i].reg_name = strdup(name);
        reg_alloc.temp_regs[i].is_free = 1;
        reg_alloc.temp_regs[i].var_name = NULL;
        reg_alloc.temp_regs[i].last_used = 0;
    }
    reg_alloc.clock = 0;
}

char* allocate_register(char* var) {
    // First check if variable already in register
    for(int i = 0; i < 8; i++) {
        if(reg_alloc.temp_regs[i].var_name &&
           strcmp(reg_alloc.temp_regs[i].var_name, var) == 0) {
            reg_alloc.temp_regs[i].last_used = reg_alloc.clock++;
            return reg_alloc.temp_regs[i].reg_name;
        }
    }

    // Find free register
    for(int i = 0; i < 8; i++) {
        if(reg_alloc.temp_regs[i].is_free) {
            reg_alloc.temp_regs[i].is_free = 0;
            reg_alloc.temp_regs[i].var_name = strdup(var);
            reg_alloc.temp_regs[i].last_used = reg_alloc.clock++;
            return reg_alloc.temp_regs[i].reg_name;
        }
    }

    // Evict LRU
    int lru_idx = 0;
    int min_time = reg_alloc.temp_regs[0].last_used;
    for(int i = 1; i < 8; i++) {
        if(reg_alloc.temp_regs[i].last_used < min_time) {
            min_time = reg_alloc.temp_regs[i].last_used;
            lru_idx = i;
        }
    }

    // Spill old variable to stack
    if(reg_alloc.temp_regs[lru_idx].var_name) {
        int offset = getVarOffset(reg_alloc.temp_regs[lru_idx].var_name);
        fprintf(output, "    sw %s, %d($fp)\n",
                reg_alloc.temp_regs[lru_idx].reg_name, offset);
    }

    // Allocate to new variable
    reg_alloc.temp_regs[lru_idx].var_name = strdup(var);
    reg_alloc.temp_regs[lru_idx].last_used = reg_alloc.clock++;

    // Load from stack if needed
    if(isVarDeclared(var)) {
        int offset = getVarOffset(var);
        fprintf(output, "    lw %s, %d($fp)\n",
                reg_alloc.temp_regs[lru_idx].reg_name, offset);
    }

    return reg_alloc.temp_regs[lru_idx].reg_name;
}

int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;  // reuse $t0-$t7
    return reg;
}

/* Generate code for expressions */
int genExpr(ASTNode* node) {
    if (!node) return -1;

    switch (node->type) {
        case NODE_NUM: {
            int reg = getNextTemp();
            fprintf(output, "    li $t%d, %d\n", reg, node->data.num);
            return reg;
        }

        case NODE_FLOAT: {
            int reg = getNextTemp();
            fprintf(output, "    li.s $f%d, %f\n", reg, node->data.decimal);
            return reg;
        }

        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s not declared\n", node->data.name);
                exit(1);
            }
            int reg = getNextTemp();
            fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
            return reg;
        }

        case NODE_BINOP: {
            int leftReg  = genExpr(node->data.binop.left);
            int rightReg = genExpr(node->data.binop.right);
            if (leftReg < 0 || rightReg < 0) {
                fprintf(stderr, "Error: failed to generate subexpressions for BINOP\n");
                exit(1);
            }
            int destReg = getNextTemp();
            switch (node->data.binop.op) {
                case '+':
                    fprintf(output, "    add $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
                    break;
                case '-':
                    fprintf(output, "    sub $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
                    break;
                case '*':
                    fprintf(output, "    mul $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
                    break;
                case '/':
                    fprintf(output, "    div $t%d, $t%d\n", leftReg, rightReg);
                    fprintf(output, "    mflo $t%d\n", destReg);
                    break;
                default:
                    fprintf(stderr, "Error: Unknown binary operator %c\n", node->data.binop.op);
                    exit(1);
            }
            return destReg;
        }

        case NODE_UNOP: {
            int exprReg = genExpr(node->data.unop.expr);
            if (exprReg < 0) {
                fprintf(stderr, "Error: failed to generate unary op expression\n");
                exit(1);
            }
            int destReg = getNextTemp();
            if (node->data.unop.op == '-') {
                fprintf(output, "    sub $t%d, $zero, $t%d   # negate\n", destReg, exprReg);
            }
            return destReg;
        }

        case NODE_ARRAY_ACCESS: {
            if (!isArrayVar(node->data.array_access.name)) {
                fprintf(stderr, "Error: %s is not an array\n", node->data.array_access.name);
                exit(1);
            }
            int idxReg = genExpr(node->data.array_access.index);
            if (idxReg < 0) {
                fprintf(stderr, "Error: failed to generate index expression\n");
                exit(1);
            }

            int baseOffset = getVarOffset(node->data.array_access.name);
            int offsetReg = getNextTemp();
            int addrReg   = getNextTemp();

            fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", offsetReg, idxReg);
            fprintf(output, "    add $t%d, $sp, $t%d # base + offset\n", addrReg, offsetReg);
            if (baseOffset != 0) {
                fprintf(output, "    addi $t%d, $t%d, %d  # apply baseOffset\n", addrReg, addrReg, baseOffset);
            }
            fprintf(output, "    lw $t%d, 0($t%d)     # load element\n", addrReg, addrReg);
            return addrReg;
        }

        default:
            fprintf(stderr, "Error: Unsupported expression node type %d\n", node->type);
            exit(1);
    }
    return -1;
}

/* Generate code for statements */
void genStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECL: {
            int offset = addVar(node->data.name);
            if (offset == -1) { fprintf(stderr, "Error: Variable %s already declared\n", node->data.name); exit(1); }
            fprintf(output, "    # Declared %s at offset %d\n", node->data.name, offset);
            break;
        }

        case NODE_ASSIGN: {
            int offset = getVarOffset(node->data.assign.var);
            if (offset == -1) { fprintf(stderr, "Error: Variable %s not declared\n", node->data.assign.var); exit(1); }

            int valueReg = genExpr(node->data.assign.value);
            if (valueReg < 0) { fprintf(stderr, "Error: failed to generate RHS of assignment\n"); exit(1); }

            fprintf(output, "    sw $t%d, %d($sp)\n", valueReg, offset);
            tempReg = 0;
            break;
        }

        case NODE_ARRAY_DECL: {
            int offset = addArrayVar(node->data.array_decl.name, node->data.array_decl.size);
            if (offset == -1) { fprintf(stderr, "Error: Array %s already declared\n", node->data.array_decl.name); exit(1); }
            fprintf(output, "    # Declared array %s[%d] at offset %d\n", node->data.array_decl.name, node->data.array_decl.size, offset);
            break;
        }

        case NODE_ARRAY_ASSIGN: {
            if (!isArrayVar(node->data.array_assign.name)) { fprintf(stderr, "Error: %s is not an array\n", node->data.array_assign.name); exit(1); }

            int idxReg = genExpr(node->data.array_assign.index);
            int valReg = genExpr(node->data.array_assign.value);
            if (idxReg < 0 || valReg < 0) { fprintf(stderr, "Error: failed to generate array assignment parts\n"); exit(1); }

            int baseOffset = getVarOffset(node->data.array_assign.name);
            int offsetReg = getNextTemp();
            int addrReg   = getNextTemp();

            fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", offsetReg, idxReg);
            fprintf(output, "    add $t%d, $sp, $t%d  # base + offset\n", addrReg, offsetReg);
            if (baseOffset != 0) {
                fprintf(output, "    addi $t%d, $t%d, %d  # apply baseOffset\n", addrReg, addrReg, baseOffset);
            }
            fprintf(output, "    sw $t%d, 0($t%d)     # store value\n", valReg, addrReg);

            tempReg = 0;
            break;
        }

        case NODE_PRINT: {
            int exprReg = genExpr(node->data.expr);
            if (exprReg < 0) { fprintf(stderr, "Error: failed to generate print expr\n"); exit(1); }
            fprintf(output, "    # Print integer\n");
            fprintf(output, "    move $a0, $t%d\n", exprReg);
            fprintf(output, "    li $v0, 1\n");
            fprintf(output, "    syscall\n");
            fprintf(output, "    li $v0, 11\n");
            fprintf(output, "    li $a0, 10\n");
            fprintf(output, "    syscall\n");

            tempReg = 0;
            break;
        }

        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        default:
            break;
    }
}

/* Generate full program */
void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "Cannot open output file %s\n", filename);
        exit(1);
    }
    
    initSymTab();
    
    fprintf(output, ".data\n");
    fprintf(output, "\n.text\n");
    fprintf(output, ".globl main\n");
    fprintf(output, "main:\n");
    
    fprintf(output, "    # Allocate stack space\n");
    fprintf(output, "    addi $sp, $sp, -400\n\n");
    
    genStmt(root);
    
    fprintf(output, "\n    # Exit program\n");
    fprintf(output, "    addi $sp, $sp, 400\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
    
    fclose(output);
}
