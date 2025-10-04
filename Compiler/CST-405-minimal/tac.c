#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

TACList tacList;
TACList optimizedList;
OptimizationStats opt_stats = {0};

int isConstant(const char* s) {
    if (!s) return 0;
    if (!isdigit(s[0]) && !(s[0] == '-' && isdigit(s[1]))) return 0;
    for (int i = 1; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}


void initTAC() {
    tacList.head = NULL;
    tacList.tail = NULL;
    tacList.tempCount = 0;
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
}

void optimizeTAC() {
    TACInstr* current = tacList.head;

    while (current && current->next) {
        // Pattern 1: Constant folding
        // t0 = 5; t1 = 10; t2 = t0 + t1; => t2 = 15;
        if (current->op == TAC_ASSIGN &&
            current->next->op == TAC_ASSIGN &&
            isConstant(current->arg1) &&
            isConstant(current->next->arg1)) {

            TACInstr* third = current->next->next;
            if (third && third->op == TAC_ADD &&
                strcmp(third->arg1, current->result) == 0 &&
                strcmp(third->arg2, current->next->result) == 0) {

                int val1 = atoi(current->arg1);
                int val2 = atoi(current->next->arg1);
                char buffer[20];
                sprintf(buffer, "%d", val1 + val2);

                // Replace with single assignment
                third->op = TAC_ASSIGN;
                third->arg1 = strdup(buffer);
                third->arg2 = NULL;

                // Remove redundant instructions
                current->op = TAC_NOP;  // Mark for removal
                current->next->op = TAC_NOP;

                opt_stats.constant_folded++;
            }
        }

        // Pattern 2: Copy propagation
        // t0 = x; y = t0; => y = x;
        if (current->op == TAC_ASSIGN &&
            current->next->op == TAC_ASSIGN &&
            strcmp(current->next->arg1, current->result) == 0) {

            current->next->arg1 = strdup(current->arg1);
            current->op = TAC_NOP;
            opt_stats.eliminated_temps++;
        }

        current = current->next;
    }

    // Remove NOP instructions
    removeNOPs();
}

void removeNOPs() {
    TACInstr* current = tacList.head;
    TACInstr* prev = NULL;

    while (current) {
        if (current->op == TAC_NOP) {
            TACInstr* toDelete = current;
            if (prev) {
                prev->next = current->next;
                current = current->next;
            } else {
                tacList.head = current->next;
                current = current->next;
            }
            opt_stats.dead_code_removed++;
            // Note: In production, should free toDelete
        } else {
            prev = current;
            current = current->next;
        }
    }
}

char* newTemp() {
    char* temp = malloc(10);
    sprintf(temp, "t%d", tacList.tempCount++);
    return temp;
}

TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op = op;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->next = NULL;
    return instr;
}

void appendTAC(TACInstr* instr) {
    if (!tacList.head) {
        tacList.head = tacList.tail = instr;
    } else {
        tacList.tail->next = instr;
        tacList.tail = instr;
    }
}

void appendOptimizedTAC(TACInstr* instr) {
    if (!optimizedList.head) {
        optimizedList.head = optimizedList.tail = instr;
    } else {
        optimizedList.tail->next = instr;
        optimizedList.tail = instr;
    }
}

char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;
    
    switch(node->type) {
        case NODE_NUM: {
            char* temp = malloc(20);
            sprintf(temp, "%d", node->data.num);
            return temp;
        }
        case NODE_FLOAT: {
            char* temp = malloc(20);
            sprintf(temp, "%f", node->data.decimal);
            return temp;
        }
        
        case NODE_VAR:
            return strdup(node->data.name);
        
        case NODE_BINOP: {
            char* left = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp = newTemp();
            
            if (node->data.binop.op == '+') {
                appendTAC(createTAC(TAC_ADD, left, right, temp));
            } else if (node->data.binop.op == '*') {
                appendTAC(createTAC(TAC_MUL, left, right, temp));
            }
            
            return temp;
        }

        case NODE_ARRAY_ACCESS: {
            char* indexExpr = generateTACExpr(node->data.array_access.index);
            char* temp = newTemp();
            appendTAC(createTAC(TAC_ARRAY_ACCESS, indexExpr, NULL, temp));
            return temp;
        }
        case NODE_UNOP: {
        char* expr = generateTACExpr(node->data.unop.expr);
        char* temp = newTemp();
        if (node->data.unop.op == '-') {
            appendTAC(createTAC(TAC_NEG, expr, NULL, temp));
        }
    return temp;
}

        default:
            return NULL;
            
    }
    
}

void generateTAC(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
            break;
            
        case NODE_ASSIGN: {
            char* expr = generateTACExpr(node->data.assign.value);
            appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var));
            break;
        }
        
        case NODE_PRINT: {
            char* expr = generateTACExpr(node->data.expr);
            appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
            break;
        }
        
        case NODE_STMT_LIST:
            generateTAC(node->data.stmtlist.stmt);
            generateTAC(node->data.stmtlist.next);
            break;

        case NODE_ARRAY_DECL:
            appendTAC(createTAC(TAC_ARRAY_DECL, NULL, NULL, node->data.array_decl.name));
            break;

        case NODE_ARRAY_ASSIGN: {
            char* indexExpr = generateTACExpr(node->data.array_assign.index);
            char* valueExpr = generateTACExpr(node->data.array_assign.value);
            appendTAC(createTAC(TAC_ARRAY_ASSIGN, indexExpr, valueExpr,
                                node->data.array_assign.name));
            break;
        }
            
        default:
            break;
    }
}

void printTAC() {
    printf("Unoptimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = tacList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s", curr->result);
                printf("          // Declare variable '%s'\n", curr->result);
                break;
            case TAC_ADD:
                printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Add: store result in %s\n", curr->result);
                break;
            case TAC_MUL:
                printf("%s = %s * %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Mul: store result in %s\n", curr->result);
                break;
            case TAC_ASSIGN:
                printf("%s = %s", curr->result, curr->arg1);
                printf("           // Assign value to %s\n", curr->result);
                break;
            case TAC_PRINT:
                printf("PRINT %s", curr->arg1);
                printf("          // Output value of %s\n", curr->arg1);
                break;
            case TAC_ARRAY_DECL:
                printf("ARRAY_DECL %s", curr->result);
                printf("     // Declare array '%s'\n", curr->result);
                break;
            case TAC_ARRAY_ASSIGN:
                printf("%s[%s] = %s", curr->result, curr->arg1, curr->arg2);
                printf("   // Array assignment\n");
                break;
            case TAC_ARRAY_ACCESS:
                printf("%s = array[%s]", curr->result, curr->arg1);
                printf("  // Array access\n");
                break;
            default:
                break;
        }
        curr = curr->next;
    }
}

void printOptimizedTAC() {
    printf("Optimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s\n", curr->result);
                break;
            case TAC_ADD:
                printf("%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ASSIGN:
                printf("%s = %s\n", curr->result, curr->arg1);
                break;
            case TAC_PRINT:
                printf("PRINT %s\n", curr->arg1);
                break;
            case TAC_ARRAY_DECL:
                printf("ARRAY_DECL %s\n", curr->result);
                break;
            case TAC_ARRAY_ASSIGN:
                printf("%s[%s] = %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ARRAY_ACCESS:
                printf("%s = array[%s]\n", curr->result, curr->arg1);
                break;
            default:
                break;
        }
        curr = curr->next;
    }
}
