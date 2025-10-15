#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

TACList tacList;
TACList optimizedList;
OptimizationStats opt_stats = {0};
static int labelCount = 0;

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
    printf("Starting TAC optimization...\n");
    
    // Step 1: Dead code elimination (easiest)
    eliminateDeadCode();
    
    // Step 2: Function inlining for small functions
    inlineSmallFunctions();
    
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
                free(third->arg1);  // Free old value
                third->arg1 = strdup(buffer);
                free(third->arg2);  // Free old value
                third->arg2 = NULL;

                // Mark redundant instructions for removal
                current->op = TAC_NOP;
                current->next->op = TAC_NOP;

                opt_stats.constant_folded++;
            }
        }

        // Pattern 2: Copy propagation
        // t0 = x; y = t0; => y = x;
        if (current->op == TAC_ASSIGN &&
            current->next->op == TAC_ASSIGN &&
            strcmp(current->next->arg1, current->result) == 0) {

            free(current->next->arg1);  // Free old value
            current->next->arg1 = strdup(current->arg1);
            current->op = TAC_NOP;
            opt_stats.eliminated_temps++;
        }

        current = current->next;
    }

    // Remove NOP instructions from the original list
    removeNOPs();

    // Copy optimized instructions to optimized list
    current = tacList.head;
    while (current) {
        if (current->op != TAC_NOP) {  // Skip any remaining NOPs
            TACInstr* copy = createTACWithParamCount(current->op, current->arg1, current->arg2, current->result, current->paramCount);
            appendOptimizedTAC(copy);
        }
        current = current->next;
    }
    
    printf("Optimization complete. Stats:\n");
    printf("  Temps eliminated: %d\n", opt_stats.eliminated_temps);
    printf("  Constants folded: %d\n", opt_stats.constant_folded);
    printf("  Dead code removed: %d\n", opt_stats.dead_code_removed);
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
            free(toDelete);  // Actually free the memory
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

char* newTACLabel() {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "L%d", labelCount++);
    return strdup(buffer);
}

TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op = op;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->paramCount = 0;  // Default to 0
    instr->next = NULL;
    return instr;
}

TACInstr* createTACWithParamCount(TACOp op, char* arg1, char* arg2, char* result, int paramCount) {
    TACInstr* instr = createTAC(op, arg1, arg2, result);
    instr->paramCount = paramCount;
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

        case NODE_BOOL: {
            return strdup(node->data.boolean ? "1" : "0");
        }
        
        case NODE_BINOP: {
            char* left = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp = newTemp();

            switch (node->data.binop.op) {
                case BINOP_ADD: appendTAC(createTAC(TAC_ADD, left, right, temp)); break;
                case BINOP_SUB: appendTAC(createTAC(TAC_SUB, left, right, temp)); break;
                case BINOP_MUL: appendTAC(createTAC(TAC_MUL, left, right, temp)); break;
                case BINOP_DIV: appendTAC(createTAC(TAC_DIV, left, right, temp)); break;
                case BINOP_MOD: appendTAC(createTAC(TAC_MOD, left, right, temp)); break;
                case BINOP_AND: appendTAC(createTAC(TAC_AND, left, right, temp)); break;
                case BINOP_OR:  appendTAC(createTAC(TAC_OR, left, right, temp)); break;
                default: break;
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

            switch (node->data.unop.op) {
                case UNOP_NEG:
                    appendTAC(createTAC(TAC_NEG, expr, NULL, temp));
                    break;
                case UNOP_NOT:
                    appendTAC(createTAC(TAC_NOT, expr, NULL, temp));
                    break;
            }
            return temp;
        }
        case NODE_RELOP: {
            char* left = generateTACExpr(node->data.relop.left);
            char* right = generateTACExpr(node->data.relop.right);
            char* temp = newTemp();

            switch (node->data.relop.op) {
                case RELOP_LT: appendTAC(createTAC(TAC_LT, left, right, temp)); break;
                case RELOP_GT: appendTAC(createTAC(TAC_GT, left, right, temp)); break;
                case RELOP_LE: appendTAC(createTAC(TAC_LE, left, right, temp)); break;
                case RELOP_GE: appendTAC(createTAC(TAC_GE, left, right, temp)); break;
                case RELOP_EQ: appendTAC(createTAC(TAC_EQ, left, right, temp)); break;
                case RELOP_NE: appendTAC(createTAC(TAC_NE, left, right, temp)); break;
            }
            return temp;
        }
        
        case NODE_FUNC_CALL: {
            // Generate TAC for each argument
            ASTNode* arg = node->data.func_call.args;
            int paramCount = 0;
            while (arg) {
                char* argVal = generateTACExpr(arg->data.list.item);
                appendTAC(createTAC(TAC_PARAM, argVal, NULL, NULL));
                paramCount++;
                arg = arg->data.list.next;
            }
            // Generate the call
            char* temp = newTemp();
            TACInstr* call = createTACWithParamCount(TAC_CALL, node->data.func_call.name,
                                                   NULL, temp, paramCount);
            appendTAC(call);
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

        case NODE_IF: {
            char* cond = generateTACExpr(node->data.ifstmt.cond);
            char* label_else = newTACLabel();
            char* label_end = newTACLabel();

            appendTAC(createTAC(TAC_IFZ, cond, NULL, label_else));
            generateTAC(node->data.ifstmt.thenBr);

            if (node->data.ifstmt.elseBr) {
                appendTAC(createTAC(TAC_JUMP, NULL, NULL, label_end));
                appendTAC(createTAC(TAC_LABEL, NULL, NULL, label_else));
                generateTAC(node->data.ifstmt.elseBr);
                appendTAC(createTAC(TAC_LABEL, NULL, NULL, label_end));
            } else {
                appendTAC(createTAC(TAC_LABEL, NULL, NULL, label_else));
            }
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
        
        case NODE_FUNC_DECL:
            appendTAC(createTAC(TAC_FUNC_BEGIN, NULL, NULL,
                                node->data.func_decl.name));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL,
                                node->data.func_decl.name));
            // Generate TAC for function body
            generateTAC(node->data.func_decl.body);
            appendTAC(createTAC(TAC_FUNC_END, NULL, NULL,
                                node->data.func_decl.name));
            break;

        case NODE_RETURN: {
            if (node->data.return_expr) {
                char* retVal = generateTACExpr(node->data.return_expr);
                appendTAC(createTAC(TAC_RETURN, retVal, NULL, NULL));
            } else {
                appendTAC(createTAC(TAC_RETURN, NULL, NULL, NULL));
            }
            break;
        }
        
        case NODE_FUNC_LIST:
            generateTAC(node->data.list.item);
            generateTAC(node->data.list.next);
            break;
            
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
            case TAC_IFZ:
                printf("IFZ %s GOTO %s\n", curr->arg1, curr->result);
                printf("          // If %s is zero, jump to %s\n", curr->arg1, curr->result);
                break;
            case TAC_JUMP:
                printf("JUMP %s\n", curr->result);
                printf("          // Unconditional jump to %s\n", curr->result);
                break;
            case TAC_LABEL:
                printf("%s:\n", curr->result);
                printf("          // Label %s\n", curr->result);
                break;
            case TAC_AND:
                printf("%s = %s && %s\n", curr->result, curr->arg1, curr->arg2);
                printf("          // Logical AND\n");
                break;
            case TAC_OR:
                printf("%s = %s || %s\n", curr->result, curr->arg1, curr->arg2);
                printf("          // Logical OR\n");
                break;
            case TAC_NOT:
                printf("%s = !%s\n", curr->result, curr->arg1);
                printf("          // Logical NOT\n");
                break;
            case TAC_NEG:
                printf("%s = -%s\n", curr->result, curr->arg1);
                break;
            case TAC_LT: printf("%s = (%s < %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GT: printf("%s = (%s > %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_LE: printf("%s = (%s <= %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GE: printf("%s = (%s >= %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_EQ: printf("%s = (%s == %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_NE: printf("%s = (%s != %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_FUNC_BEGIN:
                printf("FUNC_BEGIN %s", curr->result);
                printf("    // Start of function %s\n", curr->result);
                break;
            case TAC_FUNC_END:
                printf("FUNC_END %s", curr->result);
                printf("      // End of function %s\n", curr->result);
                break;
            case TAC_PARAM:
                printf("PARAM %s", curr->arg1);
                printf("         // Push parameter %s\n", curr->arg1);
                break;
            case TAC_CALL:
                printf("%s = CALL %s, %d", curr->result, curr->arg1, curr->paramCount);
                printf("  // Call function %s with %d parameters\n", curr->arg1, curr->paramCount);
                break;
            case TAC_RETURN:
                if (curr->arg1) {
                    printf("RETURN %s", curr->arg1);
                    printf("        // Return value %s\n", curr->arg1);
                } else {
                    printf("RETURN");
                    printf("            // Return void\n");
                }
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
            case TAC_IFZ:
                printf("IFZ %s GOTO %s\n", curr->arg1, curr->result);
                break;
            case TAC_JUMP:
                printf("JUMP %s\n", curr->result);
                break;
            case TAC_LABEL:
                printf("%s:\n", curr->result);
                break;
            case TAC_AND:
                printf("%s = %s && %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_OR:
                printf("%s = %s || %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_NOT:
                printf("%s = !%s\n", curr->result, curr->arg1);
                break;
            case TAC_NEG:
                printf("%s = -%s\n", curr->result, curr->arg1);
                break;
            case TAC_LT: printf("%s = (%s < %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GT: printf("%s = (%s > %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_LE: printf("%s = (%s <= %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GE: printf("%s = (%s >= %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_EQ: printf("%s = (%s == %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_NE: printf("%s = (%s != %s)\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_FUNC_BEGIN:
                printf("FUNC_BEGIN %s\n", curr->result);
                break;
            case TAC_FUNC_END:
                printf("FUNC_END %s\n", curr->result);
                break;
            case TAC_PARAM:
                printf("PARAM %s\n", curr->arg1);
                break;
            case TAC_CALL:
                printf("%s = CALL %s, %d\n", curr->result, curr->arg1, curr->paramCount);
                break;
            case TAC_RETURN:
                if (curr->arg1) {
                    printf("RETURN %s\n", curr->arg1);
                } else {
                    printf("RETURN\n");
                }
                break;
            default:
                break;
        }
        curr = curr->next;
    }
}

/* Dead code elimination - removes unused temporary variables */
void eliminateDeadCode() {
    TACInstr* current = tacList.head;
    
    // Mark all used variables
    char usedVars[1000][20];  // Simple array to track used variables
    int usedCount = 0;
    
    // First pass: collect all used variables from right-hand sides
    current = tacList.head;
    while (current) {
        if (current->arg1 && strncmp(current->arg1, "t", 1) == 0) {
            // Add to used list if not already there
            int found = 0;
            for (int i = 0; i < usedCount; i++) {
                if (strcmp(usedVars[i], current->arg1) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && usedCount < 999) {
                strcpy(usedVars[usedCount++], current->arg1);
            }
        }
        if (current->arg2 && strncmp(current->arg2, "t", 1) == 0) {
            // Add to used list if not already there
            int found = 0;
            for (int i = 0; i < usedCount; i++) {
                if (strcmp(usedVars[i], current->arg2) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && usedCount < 999) {
                strcpy(usedVars[usedCount++], current->arg2);
            }
        }
        current = current->next;
    }
    
    // Second pass: mark assignments to unused temps as NOP
    current = tacList.head;
    while (current) {
        if (current->op == TAC_ASSIGN && current->result && 
            strncmp(current->result, "t", 1) == 0) {
            // Check if this temp is used
            int used = 0;
            for (int i = 0; i < usedCount; i++) {
                if (strcmp(usedVars[i], current->result) == 0) {
                    used = 1;
                    break;
                }
            }
            if (!used) {
                current->op = TAC_NOP;
                opt_stats.dead_code_removed++;
            }
        }
        current = current->next;
    }
}

/* Check if a function is small enough for inlining */
int isSmallFunction(const char* funcName) {
    TACInstr* current = tacList.head;
    int instrCount = 0;
    int inFunction = 0;
    
    while (current) {
        if (current->op == TAC_FUNC_BEGIN && 
            strcmp(current->result, funcName) == 0) {
            inFunction = 1;
        } else if (current->op == TAC_FUNC_END && 
                   strcmp(current->result, funcName) == 0) {
            break;
        } else if (inFunction) {
            instrCount++;
            if (instrCount > 5) return 0;  // Too large to inline
        }
        current = current->next;
    }
    
    return instrCount <= 5;  // Only inline functions with 5 or fewer instructions
}

/* Function inlining for small functions */
void inlineSmallFunctions() {
    TACInstr* current = tacList.head;
    
    while (current) {
        if (current->op == TAC_CALL && isSmallFunction(current->arg1)) {
            // Find the function definition
            TACInstr* funcStart = tacList.head;
            while (funcStart && !(funcStart->op == TAC_FUNC_BEGIN && 
                                strcmp(funcStart->result, current->arg1) == 0)) {
                funcStart = funcStart->next;
            }
            
            if (funcStart) {
                // Simple inlining: replace call with function body
                // This is a basic implementation - could be much more sophisticated
                current->op = TAC_NOP;  // Remove the call
                printf("// Inlined function %s\n", current->arg1);
                // In a real implementation, we would copy the function body here
                // and substitute parameters with arguments
            }
        }
        current = current->next;
    }
}
