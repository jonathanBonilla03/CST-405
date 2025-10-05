#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"
#include "ast.h"

FILE* output;
int tempReg = 0;
RegisterAllocator reg_alloc;

/* ========== Label Management ========== */
int labelCount = 0;
char* newLabel(const char* prefix) {
    char* label = (char*)malloc(32);
    if (!label) {
        fprintf(stderr, "Memory allocation failed for label.\n");
        exit(1);
    }
    sprintf(label, "%s_%d", prefix, labelCount++);
    return label;
}

/* ========== Register Allocator ========== */
void init_register_allocator() {
    for (int i = 0; i < 8; i++) {
        char name[5];
        sprintf(name, "$t%d", i);
        reg_alloc.temp_regs[i].reg_name = strdup(name);
        reg_alloc.temp_regs[i].is_free = 1;
        reg_alloc.temp_regs[i].var_name = NULL;
        reg_alloc.temp_regs[i].last_used = 0;
    }
    reg_alloc.clock = 0;
}

char* allocate_register(char* var) {
    // Check if variable already in a register
    for (int i = 0; i < 8; i++) {
        if (reg_alloc.temp_regs[i].var_name &&
            strcmp(reg_alloc.temp_regs[i].var_name, var) == 0) {
            reg_alloc.temp_regs[i].last_used = reg_alloc.clock++;
            return reg_alloc.temp_regs[i].reg_name;
        }
    }

    // Allocate a free register
    for (int i = 0; i < 8; i++) {
        if (reg_alloc.temp_regs[i].is_free) {
            reg_alloc.temp_regs[i].is_free = 0;
            reg_alloc.temp_regs[i].var_name = strdup(var);
            reg_alloc.temp_regs[i].last_used = reg_alloc.clock++;
            return reg_alloc.temp_regs[i].reg_name;
        }
    }

    // Use LRU if none free
    int lru_idx = 0;
    int min_time = reg_alloc.temp_regs[0].last_used;
    for (int i = 1; i < 8; i++) {
        if (reg_alloc.temp_regs[i].last_used < min_time) {
            min_time = reg_alloc.temp_regs[i].last_used;
            lru_idx = i;
        }
    }

    // Save old variable to stack
    if (reg_alloc.temp_regs[lru_idx].var_name) {
        int offset = getVarOffset(reg_alloc.temp_regs[lru_idx].var_name);
        fprintf(output, "    sw %s, %d($fp)\n",
                reg_alloc.temp_regs[lru_idx].reg_name, offset);
        free(reg_alloc.temp_regs[lru_idx].var_name);
    }

    reg_alloc.temp_regs[lru_idx].var_name = strdup(var);
    reg_alloc.temp_regs[lru_idx].last_used = reg_alloc.clock++;

    if (isVarDeclared(var)) {
        int offset = getVarOffset(var);
        fprintf(output, "    lw %s, %d($fp)\n",
                reg_alloc.temp_regs[lru_idx].reg_name, offset);
    }

    return reg_alloc.temp_regs[lru_idx].reg_name;
}

/* ========== Temporary Register Handling ========== */
int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;
    return reg;
}

/* ========== Expression Code Generation ========== */
int genExpr(ASTNode* node) {
    if (!node) return -1;

    switch (node->type) {
        case NODE_NUM: {
            int reg = getNextTemp();
            fprintf(output, "    li $t%d, %d\n", reg, node->data.num);
            return reg;
        }

        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s not declared.\n", node->data.name);
                exit(1);
            }
            int reg = getNextTemp();
            fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
            return reg;
        }

        case NODE_BINOP: {
            int leftReg  = genExpr(node->data.binop.left);
            int rightReg = genExpr(node->data.binop.right);
            int destReg = getNextTemp();
            switch (node->data.binop.op) {
                case '+': fprintf(output, "    add $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg); break;
                case '-': fprintf(output, "    sub $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg); break;
                case '*': fprintf(output, "    mul $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg); break;
                case '/':
                    fprintf(output, "    div $t%d, $t%d\n", leftReg, rightReg);
                    fprintf(output, "    mflo $t%d\n", destReg);
                    break;
                default:
                    fprintf(stderr, "Unknown binary operator %c\n", node->data.binop.op);
                    exit(1);
            }
            return destReg;
        }

        case NODE_UNOP: {
            int exprReg = genExpr(node->data.unop.expr);
            int destReg = getNextTemp();
            if (node->data.unop.op == '-')
                fprintf(output, "    sub $t%d, $zero, $t%d\n", destReg, exprReg);
            return destReg;
        }

        case NODE_RELOP: {
            int a = genExpr(node->data.relop.left);
            int b = genExpr(node->data.relop.right);
            int d = getNextTemp();      
            int t = getNextTemp();      

            switch (node->data.relop.op) {
                case RELOP_LT: fprintf(output, "    slt $t%d, $t%d, $t%d\n", d, a, b); break;
                case RELOP_GT: fprintf(output, "    slt $t%d, $t%d, $t%d\n", d, b, a); break;
                case RELOP_LE:
                    fprintf(output, "    slt $t%d, $t%d, $t%d\n", t, b, a);
                    fprintf(output, "    xori $t%d, $t%d, 1\n", d, t);
                    break;
                case RELOP_GE:
                    fprintf(output, "    slt $t%d, $t%d, $t%d\n", t, a, b);
                    fprintf(output, "    xori $t%d, $t%d, 1\n", d, t);
                    break;
                case RELOP_EQ:
                    fprintf(output, "    subu $t%d, $t%d, $t%d\n", t, a, b);
                    fprintf(output, "    sltiu $t%d, $t%d, 1\n", d, t);
                    break;
                case RELOP_NE:
                    fprintf(output, "    subu $t%d, $t%d, $t%d\n", t, a, b);
                    fprintf(output, "    sltu  $t%d, $zero, $t%d\n", d, t);
                    break;
            }
            return d;
        }

        default:
            fprintf(stderr, "Unsupported expression type: %d\n", node->type);
            exit(1);
    }
}

/* ========== Statement Code Generation ========== */
void genStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECL: {
            int offset = addVar(node->data.name);
            fprintf(output, "    # Declared %s at offset %d\n", node->data.name, offset);
            break;
        }

        case NODE_ASSIGN: {
            int offset = getVarOffset(node->data.assign.var);
            int valueReg = genExpr(node->data.assign.value);
            fprintf(output, "    sw $t%d, %d($sp)\n", valueReg, offset);
            break;
        }

        case NODE_PRINT: {
            int exprReg = genExpr(node->data.expr);
            fprintf(output, "    move $a0, $t%d\n", exprReg);
            fprintf(output, "    li $v0, 1\n");
            fprintf(output, "    syscall\n");
            fprintf(output, "    li $v0, 11\n");
            fprintf(output, "    li $a0, 10\n");
            fprintf(output, "    syscall\n");
            break;
        }

        case NODE_IF: {
            char* elseLbl = newLabel("L_else");
            char* endLbl = newLabel("L_end");
            int condReg = genExpr(node->data.ifstmt.cond);

            fprintf(output, "    beq $t%d, $zero, %s\n", condReg, elseLbl);
            genStmt(node->data.ifstmt.thenBr);
            fprintf(output, "    j %s\n", endLbl);
            fprintf(output, "%s:\n", elseLbl);

            if (node->data.ifstmt.elseBr)
                genStmt(node->data.ifstmt.elseBr);

            fprintf(output, "%s:\n", endLbl);
            free(elseLbl);
            free(endLbl);
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

/* ========== Main Program Generation ========== */
void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "Cannot open output file %s\n", filename);
        exit(1);
    }

    initSymTab();

    fprintf(output, ".data\nnewline: .asciiz \"\\n\"\n\n.text\n.globl main\nmain:\n");
    fprintf(output, "    addi $sp, $sp, -400  # stack space\n");

    genStmt(root);

    fprintf(output, "\n    addi $sp, $sp, 400\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
    fclose(output);
}
