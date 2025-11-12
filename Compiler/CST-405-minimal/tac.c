#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

TACList tacList;
TACList optimizedList;
OptimizationStats opt_stats = {0};
static int labelCount = 0;

/* === Helper: detect numeric constants === */
int isConstant(const char* s) {
    if (!s) return 0;
    if (!isdigit(s[0]) && !(s[0] == '-' && isdigit(s[1]))) return 0;
    for (int i = 1; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

/* === Initialize lists === */
void initTAC() {
    tacList.head = NULL;
    tacList.tail = NULL;
    tacList.tempCount = 0;
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
}

/* === Create new temp and label === */
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

/* === TAC constructors === */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op = op;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->paramCount = 0;
    instr->next = NULL;
    return instr;
}

TACInstr* createTACWithParamCount(TACOp op, char* arg1, char* arg2, char* result, int paramCount) {
    TACInstr* instr = createTAC(op, arg1, arg2, result);
    instr->paramCount = paramCount;
    return instr;
}

/* === Append === */
void appendTAC(TACInstr* instr) {
    if (!tacList.head)
        tacList.head = tacList.tail = instr;
    else {
        tacList.tail->next = instr;
        tacList.tail = instr;
    }
}

void appendOptimizedTAC(TACInstr* instr) {
    if (!optimizedList.head)
        optimizedList.head = optimizedList.tail = instr;
    else {
        optimizedList.tail->next = instr;
        optimizedList.tail = instr;
    }
}

/* ------------------------------------------------------------------------- */
/* === Robust Function Call Argument Emission === */
static void emitCallArgs(ASTNode* args) {
    if (!args) return;

    if (args->type == NODE_ARG_LIST) {
        emitCallArgs(args->data.list.item);
        emitCallArgs(args->data.list.next);
    } else {
        char* val = generateTACExpr(args);
        appendTAC(createTAC(TAC_PARAM, val, NULL, NULL));
    }
}

static int countArgs(ASTNode* n) {
    if (!n) return 0;
    if (n->type == NODE_ARG_LIST)
        return countArgs(n->data.list.item) + countArgs(n->data.list.next);
    return 1;
}
/* ------------------------------------------------------------------------- */

/* === Expression TAC generation === */
char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;

    switch (node->type) {
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
        case NODE_BOOL:
            return strdup(node->data.boolean ? "1" : "0");
        case NODE_STRING: {
            /* For strings, return the string literal as is (with quotes) */
            char* temp = malloc(strlen(node->data.string) + 3);
            sprintf(temp, "\"%s\"", node->data.string);
            return temp;
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
                case BINOP_EXP: appendTAC(createTAC(TAC_EXP, left, right, temp)); break;
                case BINOP_AND: appendTAC(createTAC(TAC_AND, left, right, temp)); break;
                case BINOP_OR:  appendTAC(createTAC(TAC_OR, left, right, temp)); break;
                default: break;
            }
            return temp;
        }

        case NODE_UNOP: {
            char* expr = generateTACExpr(node->data.unop.expr);
            char* temp = newTemp();
            switch (node->data.unop.op) {
                case UNOP_NEG: appendTAC(createTAC(TAC_NEG, expr, NULL, temp)); break;
                case UNOP_NOT: appendTAC(createTAC(TAC_NOT, expr, NULL, temp)); break;
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
            emitCallArgs(node->data.func_call.args);
            int paramCount = countArgs(node->data.func_call.args);

            char* temp = newTemp();
            TACInstr* call = createTACWithParamCount(
                TAC_CALL, node->data.func_call.name, NULL, temp, paramCount
            );
            appendTAC(call);
            return temp;
        }

        case NODE_CAST: {
            // For casting, just pass through the expression for now
            return generateTACExpr(node->data.cast.expr);
        }

        case NODE_ARRAY_ACCESS: {
            char* index = generateTACExpr(node->data.array_access.index);
            char* temp = newTemp();
            appendTAC(createTAC(TAC_ARRAY_ACCESS, node->data.array_access.name, index, temp));
            return temp;
        }

        default:
            return NULL;
    }
}

/* === Array initialization helper === */
static int generateArrayInitTAC(ASTNode* init_list, char* array_name, int start_index) {
    if (!init_list) return start_index;
    
    if (init_list->type == NODE_INIT_LIST) {
        // Process the left side (expr field) recursively  
        int next_index = generateArrayInitTAC(init_list->data.init_list.expr, array_name, start_index);
        // Process the right side (next field)
        return generateArrayInitTAC(init_list->data.init_list.next, array_name, next_index);
    } else {
        // Leaf node - generate assignment
        char* val = generateTACExpr(init_list);
        char indexStr[16];
        snprintf(indexStr, sizeof(indexStr), "%d", start_index);
        appendTAC(createTAC(TAC_ARRAY_ASSIGN, array_name, indexStr, val));
        return start_index + 1;
    }
}

/* === Top-level TAC generation (statements) === */
void generateTAC(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
            break;

        case NODE_DECL_INIT: {
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.decl_init.name));
            char* expr = generateTACExpr(node->data.decl_init.value);
            appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.decl_init.name));
            break;
        }

        case NODE_ARRAY_INIT_DECL: {
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.array_init_decl.name));
            // Generate TAC for each initialization value using recursive helper
            generateArrayInitTAC(node->data.array_init_decl.init_list, node->data.array_init_decl.name, 0);
            break;
        }

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

        case NODE_RETURN: {
            if (node->data.return_expr) {
                char* val = generateTACExpr(node->data.return_expr);
                appendTAC(createTAC(TAC_RETURN, val, NULL, NULL));
            } else {
                appendTAC(createTAC(TAC_RETURN, NULL, NULL, NULL));
            }
            break;
        }

        case NODE_FUNC_DECL:
            appendTAC(createTAC(TAC_FUNC_BEGIN, NULL, NULL, node->data.func_decl.name));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, node->data.func_decl.name));
            generateTAC(node->data.func_decl.body);
            appendTAC(createTAC(TAC_FUNC_END, NULL, NULL, node->data.func_decl.name));
            break;

        case NODE_FUNC_LIST:
            generateTAC(node->data.list.item);
            generateTAC(node->data.list.next);
            break;

        case NODE_STMT_LIST:
            generateTAC(node->data.stmtlist.stmt);
            generateTAC(node->data.stmtlist.next);
            break;

        case NODE_ARRAY_DECL:
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.array_decl.name));
            break;

        case NODE_ARRAY_ASSIGN: {
            char* index = generateTACExpr(node->data.array_assign.index);
            char* value = generateTACExpr(node->data.array_assign.value);
            appendTAC(createTAC(TAC_ARRAY_ASSIGN, node->data.array_assign.name, index, value));
            break;
        }

        default:
            break;
    }
}

/* ============================================================
 * TAC PRINTING AND OPTIMIZATION (Used by main.c)
 * ============================================================ */
void printTAC() {
    printf("\nUnoptimized TAC Instructions:\n");
    printf("─────────────────────────────\n");

    TACInstr* curr = tacList.head;
    int line = 1;
    while (curr) {
        printf("%2d: ", line++);
        switch (curr->op) {
            case TAC_DECL: printf("DECL %s\n", curr->result); break;
            case TAC_ASSIGN: printf("%s = %s\n", curr->result, curr->arg1); break;
            case TAC_ADD: printf("%s = %s + %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_SUB: printf("%s = %s - %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_MUL: printf("%s = %s * %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_DIV: printf("%s = %s / %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_MOD: printf("%s = %s %% %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_EXP: printf("%s = %s ** %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_AND: printf("%s = %s && %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_OR:  printf("%s = %s || %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_PRINT: printf("PRINT %s\n", curr->arg1); break;
            case TAC_RETURN: printf("RETURN %s\n", curr->arg1 ? curr->arg1 : ""); break;
            case TAC_IFZ: printf("IFZ %s GOTO %s\n", curr->arg1, curr->result); break;
            case TAC_JUMP: printf("JUMP %s\n", curr->result); break;
            case TAC_LABEL: printf("%s:\n", curr->result); break;
            case TAC_PARAM: printf("PARAM %s\n", curr->arg1); break;
            case TAC_CALL: printf("%s = CALL %s (%d params)\n", curr->result, curr->arg1, curr->paramCount); break;
            case TAC_FUNC_BEGIN: printf("FUNC_BEGIN %s\n", curr->result); break;
            case TAC_FUNC_END: printf("FUNC_END %s\n", curr->result); break;
            case TAC_ARRAY_ACCESS: printf("%s = %s[%s]\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_ARRAY_ASSIGN: printf("%s[%s] = %s\n", curr->arg1, curr->arg2, curr->result); break;
            case TAC_ARRAY_DECL: printf("ARRAY_DECL %s\n", curr->result); break;
            case TAC_LT: printf("%s = %s < %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GT: printf("%s = %s > %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_LE: printf("%s = %s <= %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_GE: printf("%s = %s >= %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_EQ: printf("%s = %s == %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_NE: printf("%s = %s != %s\n", curr->result, curr->arg1, curr->arg2); break;
            case TAC_NEG: printf("%s = -%s\n", curr->result, curr->arg1); break;
            case TAC_NOT: printf("%s = !%s\n", curr->result, curr->arg1); break;
            default: printf("(unknown)\n"); break;
        }
        curr = curr->next;
    }
}

void optimizeTAC() {
    printf("\nRunning basic TAC optimizations...\n");
    TACInstr* curr = tacList.head;

    while (curr && curr->next) {
        if (curr->op == TAC_ASSIGN && curr->next->op == TAC_ASSIGN &&
            isConstant(curr->arg1) && isConstant(curr->next->arg1)) {
            TACInstr* add = curr->next->next;
            if (add && (add->op == TAC_ADD || add->op == TAC_SUB) &&
                strcmp(add->arg1, curr->result) == 0 &&
                strcmp(add->arg2, curr->next->result) == 0) {
                int v1 = atoi(curr->arg1);
                int v2 = atoi(curr->next->arg1);
                int res = (add->op == TAC_ADD) ? v1 + v2 : v1 - v2;
                char buf[20]; sprintf(buf, "%d", res);
                add->op = TAC_ASSIGN;
                free(add->arg1); add->arg1 = strdup(buf);
                free(add->arg2); add->arg2 = NULL;
                curr->op = TAC_NOP;
                curr->next->op = TAC_NOP;
                opt_stats.constant_folded++;
            }
        }
        curr = curr->next;
    }
    printf("Optimization done. Constants folded: %d\n", opt_stats.constant_folded);
}

void printOptimizedTAC() {
    printf("\nOptimized TAC Instructions:\n");
    printf("───────────────────────────\n");

    TACInstr* curr = tacList.head;
    int line = 1;
    while (curr) {
        if (curr->op != TAC_NOP) {
            printf("%2d: ", line++);
            switch (curr->op) {
                case TAC_DECL: printf("DECL %s\n", curr->result); break;
                case TAC_ASSIGN: printf("%s = %s\n", curr->result, curr->arg1); break;
                case TAC_ADD: printf("%s = %s + %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_SUB: printf("%s = %s - %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_PRINT: printf("PRINT %s\n", curr->arg1); break;
                case TAC_RETURN: printf("RETURN %s\n", curr->arg1 ? curr->arg1 : ""); break;
                case TAC_CALL: printf("%s = CALL %s (%d params)\n", curr->result, curr->arg1, curr->paramCount); break;
                case TAC_FUNC_BEGIN: printf("FUNC_BEGIN %s\n", curr->result); break;
                case TAC_FUNC_END: printf("FUNC_END %s\n", curr->result); break;
                case TAC_ARRAY_ACCESS: printf("%s = %s[%s]\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_ARRAY_ASSIGN: printf("%s[%s] = %s\n", curr->arg1, curr->arg2, curr->result); break;
                case TAC_ARRAY_DECL: printf("ARRAY_DECL %s\n", curr->result); break;
                case TAC_LT: printf("%s = %s < %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_GT: printf("%s = %s > %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_LE: printf("%s = %s <= %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_GE: printf("%s = %s >= %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_EQ: printf("%s = %s == %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_NE: printf("%s = %s != %s\n", curr->result, curr->arg1, curr->arg2); break;
                case TAC_NEG: printf("%s = -%s\n", curr->result, curr->arg1); break;
                case TAC_NOT: printf("%s = !%s\n", curr->result, curr->arg1); break;
                default: printf("(unknown)\n"); break;
            }
        }
        curr = curr->next;
    }
}
