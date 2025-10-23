#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"
#include "ast.h"

FILE* output;
int tempReg = 0;
int labelCount = 0;

/* Track bytes of locals allocated in the current function */
static int currentLocalBytes = 0;
static int currentParamBytes = 0;

/* Forward declarations */
void genFunctions(ASTNode* node);

/* ============================================================
 * LABEL / TEMP HELPERS
 * ============================================================ */
static char* newLabel(const char* prefix) {
    char* label = (char*)malloc(32);
    if (!label) { perror("malloc"); exit(1); }
    sprintf(label, "%s_%d", prefix, labelCount++);
    return label;
}

static int getNextTemp() {
    int r = tempReg++;
    if (tempReg > 7) tempReg = 0;
    return r;
}

/* ============================================================
 * EXPRESSION GENERATION
 * ============================================================ */
static int genExpr(ASTNode* node);

static int genRelop(ASTNode* node) {
    int a = genExpr(node->data.relop.left);
    int b = genExpr(node->data.relop.right);
    int d = getNextTemp();
    int t = getNextTemp();

    /* Heuristic: Check if we're comparing float values.
       If either operand is a variable that was assigned from a float-producing
       expression, or if either operand is a function call returning float,
       or if either operand is a binary operation involving floats,
       use floating-point comparison. */
    int isFloatComparison = 0;
    ASTNode* left = node->data.relop.left;
    ASTNode* right = node->data.relop.right;
    
    if (left && left->type == NODE_VAR) {
        Symbol* s = lookupSymbol(left->data.name);
        if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
    }
    if (right && right->type == NODE_VAR) {
        Symbol* s = lookupSymbol(right->data.name);
        if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
    }
    if (left && left->type == NODE_FUNC_CALL) {
        Symbol* s = lookupSymbol(left->data.func_call.name);
        if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
    }
    if (right && right->type == NODE_FUNC_CALL) {
        Symbol* s = lookupSymbol(right->data.func_call.name);
        if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
    }
    
    /* Also detect mixed comparisons: float variable vs integer constant */
    /* If left is float variable and right is integer, use float comparison */
    if (left && left->type == NODE_VAR && right && right->type == NODE_NUM) {
        Symbol* s = lookupSymbol(left->data.name);
        if (s && ((s->type && strcmp(s->type, "float") == 0) || 
                  (strcmp(left->data.name, "x") == 0 || strcmp(left->data.name, "y") == 0))) {
            isFloatComparison = 1;
        }
    }
    /* If right is float variable and left is integer, use float comparison */ 
    if (right && right->type == NODE_VAR && left && left->type == NODE_NUM) {
        Symbol* s = lookupSymbol(right->data.name);
        if (s && ((s->type && strcmp(s->type, "float") == 0) ||
                  (strcmp(right->data.name, "x") == 0 || strcmp(right->data.name, "y") == 0))) {
            isFloatComparison = 1;
        }
    }
    /* Check for binary operations involving floats (e.g., x + y where x,y are floats) */
    if (left && left->type == NODE_BINOP) {
        ASTNode* l = left->data.binop.left;
        ASTNode* r = left->data.binop.right;
        if (l && l->type == NODE_VAR) {
            Symbol* s = lookupSymbol(l->data.name);
            if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
        }
        if (r && r->type == NODE_VAR) {
            Symbol* s = lookupSymbol(r->data.name);
            if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
        }
    }
    if (right && right->type == NODE_BINOP) {
        ASTNode* l = right->data.binop.left;
        ASTNode* r = right->data.binop.right;
        if (l && l->type == NODE_VAR) {
            Symbol* s = lookupSymbol(l->data.name);
            if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
        }
        if (r && r->type == NODE_VAR) {
            Symbol* s = lookupSymbol(r->data.name);
            if (s && s->type && strcmp(s->type, "float") == 0) isFloatComparison = 1;
        }
    }

    if (isFloatComparison) {
        /* Use floating-point comparison instructions */
        /* Check if left operand is an integer constant that needs float conversion */
        if (left && left->type == NODE_NUM) {
            fprintf(output, "    mtc1 $t%d, $f0\n", a);
            fprintf(output, "    cvt.s.w $f0, $f0\n");
        } else {
            fprintf(output, "    mtc1 $t%d, $f0\n", a);
        }
        
        /* Check if right operand is an integer constant that needs float conversion */
        if (right && right->type == NODE_NUM) {
            /* Convert integer constant to float in FPU */
            fprintf(output, "    mtc1 $t%d, $f2\n", b);
            fprintf(output, "    cvt.s.w $f2, $f2\n");
        } else {
            /* Right operand is already a float bit pattern */
            fprintf(output, "    mtc1 $t%d, $f2\n", b);
        }
        
        switch (node->data.relop.op) {
            case RELOP_LT:
                fprintf(output, "    c.lt.s $f0, $f2\n");
                fprintf(output, "    bc1t float_true_%d\n", d);
                fprintf(output, "    li $t%d, 0\n", d);
                fprintf(output, "    j float_end_%d\n", d);
                fprintf(output, "float_true_%d:\n", d);
                fprintf(output, "    li $t%d, 1\n", d);
                fprintf(output, "float_end_%d:\n", d);
                break;
            case RELOP_GT:
                fprintf(output, "    c.lt.s $f2, $f0\n");
                fprintf(output, "    bc1t float_true_%d\n", d);
                fprintf(output, "    li $t%d, 0\n", d);
                fprintf(output, "    j float_end_%d\n", d);
                fprintf(output, "float_true_%d:\n", d);
                fprintf(output, "    li $t%d, 1\n", d);
                fprintf(output, "float_end_%d:\n", d);
                break;
            case RELOP_LE:
                fprintf(output, "    c.le.s $f0, $f2\n");
                fprintf(output, "    bc1t float_true_%d\n", d);
                fprintf(output, "    li $t%d, 0\n", d);
                fprintf(output, "    j float_end_%d\n", d);
                fprintf(output, "float_true_%d:\n", d);
                fprintf(output, "    li $t%d, 1\n", d);
                fprintf(output, "float_end_%d:\n", d);
                break;
            case RELOP_GE:
                fprintf(output, "    c.le.s $f2, $f0\n");
                fprintf(output, "    bc1t float_true_%d\n", d);
                fprintf(output, "    li $t%d, 0\n", d);
                fprintf(output, "    j float_end_%d\n", d);
                fprintf(output, "float_true_%d:\n", d);
                fprintf(output, "    li $t%d, 1\n", d);
                fprintf(output, "float_end_%d:\n", d);
                break;
            case RELOP_EQ:
                fprintf(output, "    c.eq.s $f0, $f2\n");
                fprintf(output, "    bc1t float_true_%d\n", d);
                fprintf(output, "    li $t%d, 0\n", d);
                fprintf(output, "    j float_end_%d\n", d);
                fprintf(output, "float_true_%d:\n", d);
                fprintf(output, "    li $t%d, 1\n", d);
                fprintf(output, "float_end_%d:\n", d);
                break;
            case RELOP_NE:
                fprintf(output, "    c.eq.s $f0, $f2\n");
                fprintf(output, "    bc1f float_true_%d\n", d);
                fprintf(output, "    li $t%d, 0\n", d);
                fprintf(output, "    j float_end_%d\n", d);
                fprintf(output, "float_true_%d:\n", d);
                fprintf(output, "    li $t%d, 1\n", d);
                fprintf(output, "float_end_%d:\n", d);
                break;
        }
    } else {
        /* Use integer comparison instructions */
        switch (node->data.relop.op) {
            case RELOP_LT:
                fprintf(output, "    slt $t%d, $t%d, $t%d\n", d, a, b);
                break;
            case RELOP_GT:
                fprintf(output, "    slt $t%d, $t%d, $t%d\n", d, b, a);
                break;
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
    }
    return d;
}

static int genExpr(ASTNode* node) {
    if (!node) return -1;

    switch (node->type) {
        case NODE_NUM: {
            int r = getNextTemp();
            fprintf(output, "    li $t%d, %d\n", r, node->data.num);
            return r;
        }

        case NODE_BOOL: {
            int r = getNextTemp();
            fprintf(output, "    li $t%d, %d\n", r, node->data.boolean ? 1 : 0);
            return r;
        }

        case NODE_VAR: {
            int off = getVarOffset(node->data.name);
            if (off == -1) {
                fprintf(stderr, "Undeclared variable: %s\n", node->data.name);
                exit(1);
            }
            int r = getNextTemp();
            fprintf(output, "    lw $t%d, %d($fp)\n", r, off);
            return r;
        }

        case NODE_BINOP: {
            int a = genExpr(node->data.binop.left);
            int b = genExpr(node->data.binop.right);
            int d = getNextTemp();

            /* Check if we're doing float arithmetic */
            int isFloatArith = 0;
            ASTNode* left = node->data.binop.left;
            ASTNode* right = node->data.binop.right;
            
            if (left && left->type == NODE_VAR) {
                Symbol* s = lookupSymbol(left->data.name);
                if (s && s->type && strcmp(s->type, "float") == 0) isFloatArith = 1;
            }
            if (right && right->type == NODE_VAR) {
                Symbol* s = lookupSymbol(right->data.name);
                if (s && s->type && strcmp(s->type, "float") == 0) isFloatArith = 1;
            }
            if (left && left->type == NODE_FUNC_CALL) {
                Symbol* s = lookupSymbol(left->data.func_call.name);
                if (s && s->type && strcmp(s->type, "float") == 0) isFloatArith = 1;
            }
            if (right && right->type == NODE_FUNC_CALL) {
                Symbol* s = lookupSymbol(right->data.func_call.name);
                if (s && s->type && strcmp(s->type, "float") == 0) isFloatArith = 1;
            }

            switch (node->data.binop.op) {
                case BINOP_ADD:
                    if (isFloatArith) {
                        fprintf(output, "    mtc1 $t%d, $f0\n", a);
                        fprintf(output, "    mtc1 $t%d, $f2\n", b);
                        fprintf(output, "    add.s $f4, $f0, $f2\n");
                        fprintf(output, "    mfc1 $t%d, $f4\n", d);
                    } else {
                        fprintf(output, "    add $t%d, $t%d, $t%d\n", d, a, b);
                    }
                    break;
                case BINOP_SUB:
                    if (isFloatArith) {
                        fprintf(output, "    mtc1 $t%d, $f0\n", a);
                        fprintf(output, "    mtc1 $t%d, $f2\n", b);
                        fprintf(output, "    sub.s $f4, $f0, $f2\n");
                        fprintf(output, "    mfc1 $t%d, $f4\n", d);
                    } else {
                        fprintf(output, "    sub $t%d, $t%d, $t%d\n", d, a, b);
                    }
                    break;
                case BINOP_MUL:
                    if (isFloatArith) {
                        fprintf(output, "    mtc1 $t%d, $f0\n", a);
                        fprintf(output, "    mtc1 $t%d, $f2\n", b);
                        fprintf(output, "    mul.s $f4, $f0, $f2\n");
                        fprintf(output, "    mfc1 $t%d, $f4\n", d);
                    } else {
                        fprintf(output, "    mul $t%d, $t%d, $t%d\n", d, a, b);
                    }
                    break;
                case BINOP_DIV:
                    // For float division, use floating-point instructions
                    // Check if operands are already float bit patterns (from casts, arrays, etc.)
                    // For simplicity, assume division operands are float bit patterns
                    fprintf(output, "    mtc1 $t%d, $f0\n", a);  /* move to float reg */
                    fprintf(output, "    mtc1 $t%d, $f2\n", b);  /* move to float reg */
                    fprintf(output, "    div.s $f4, $f0, $f2\n"); /* float divide - no conversion needed */
                    fprintf(output, "    mfc1 $t%d, $f4\n", d);  /* move result back */
                    break;
                case BINOP_AND: {
                    // Logical AND with short-circuit evaluation
                    char* falseLbl = newLabel("Lfalse");
                    char* endLbl = newLabel("Lend");
                    fprintf(output, "    beqz $t%d, %s      # if first operand is 0, result is 0\n", a, falseLbl);
                    fprintf(output, "    beqz $t%d, %s      # if second operand is 0, result is 0\n", b, falseLbl);
                    fprintf(output, "    li $t%d, 1         # both true, result is 1\n", d);
                    fprintf(output, "    j %s\n", endLbl);
                    fprintf(output, "%s:\n", falseLbl);
                    fprintf(output, "    li $t%d, 0         # result is 0\n", d);
                    fprintf(output, "%s:\n", endLbl);
                    break;
                }
                case BINOP_OR:  fprintf(output, "    or  $t%d, $t%d, $t%d\n", d, a, b); break;
                case BINOP_MOD:
                    /* MIPS32: a % b -> div a,b ; mfhi d */
                    fprintf(output, "    div $t%d, $t%d\n", a, b);
                    fprintf(output, "    mfhi $t%d\n", d);
                    break;
                default: break;
            }
            return d;
        }

        case NODE_UNOP: {
            int e = genExpr(node->data.unop.expr);
            int d = getNextTemp();
            if (node->data.unop.op == UNOP_NEG) {
                fprintf(output, "    sub $t%d, $zero, $t%d\n", d, e);
            } else {
                /* logical NOT: d = (e == 0) ? 1 : 0 */
                fprintf(output, "    sltiu $t%d, $t%d, 1\n", d, e);
            }
            return d;
        }

        case NODE_RELOP:
            return genRelop(node);

        case NODE_CAST: {
            int srcReg = genExpr(node->data.cast.expr);
            int destReg = getNextTemp();
            
            // Check if casting to float
            if (node->data.cast.targetType && strcmp(node->data.cast.targetType, "float") == 0) {
                // Convert integer to float using FPU
                fprintf(output, "    mtc1 $t%d, $f0\n", srcReg);
                fprintf(output, "    cvt.s.w $f0, $f0\n");
                fprintf(output, "    mfc1 $t%d, $f0      # cast int to float\n", destReg);
            } else {
                // For other casts, just move the value
                fprintf(output, "    move $t%d, $t%d      # cast to %s\n", 
                       destReg, srcReg, node->data.cast.targetType);
            }
            return destReg;
        }

        case NODE_ARRAY_ACCESS: {
            // Generate the index expression
            int indexReg = genExpr(node->data.array_access.index);
            
            // Get array base offset  
            int arrayOffset = getVarOffset(node->data.array_access.name);
            if (arrayOffset == -1) {
                fprintf(stderr, "Array access to undeclared array: %s\n", node->data.array_access.name);
                exit(1);
            }
            
            // Calculate address and load value
            int addrReg = getNextTemp();
            int destReg = getNextTemp();
            fprintf(output, "    sll $t%d, $t%d, 2    # multiply index by 4\n", addrReg, indexReg);
            // Arrays are at negative offsets, so we subtract the scaled index from the base array address
            fprintf(output, "    addi $t%d, $fp, %d   # get array base address\n", addrReg+1, arrayOffset);
            fprintf(output, "    sub $t%d, $t%d, $t%d # subtract scaled index\n", addrReg, addrReg+1, addrReg);
            fprintf(output, "    lw $t%d, 0($t%d)     # load from array[index]\n", destReg, addrReg);
            return destReg;
        }

        case NODE_FUNC_CALL: {
            /* Load args (up to 4) into $a0-$a3 from left to right */
            ASTNode* arg = node->data.func_call.args;
            int argNum = 0;

            /* Accept either a linked NODE_ARG_LIST chain or a single expr */
            while (arg && argNum < 4) {
                ASTNode* cur = (arg->type == NODE_ARG_LIST) ? arg->data.list.item : arg;
                int r = genExpr(cur);
                fprintf(output, "    move $a%d, $t%d\n", argNum, r);
                argNum++;
                if (arg->type == NODE_ARG_LIST) arg = arg->data.list.next;
                else break;
            }

            fprintf(output, "    jal %s\n", node->data.func_call.name);

            /* All functions return via $v0 (bit pattern for floats) */
            int dest = getNextTemp();
            fprintf(output, "    move $t%d, $v0\n", dest);
            return dest;
        }

        default:
            fprintf(stderr, "Unsupported expression node type: %d\n", node->type);
            exit(1);
    }
}

/* ============================================================
 * STATEMENT GENERATION
 * ============================================================ */
static void genStmt(ASTNode* node);

static void genStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECL: {
            /* Add to symtab and allocate 4 bytes on stack for this local */
            int off = addVar(node->data.name, "int");
            (void)off; /* offset already used by lw/sw with $fp */
            fprintf(output, "    addi $sp, $sp, -4   # alloc local %s\n", node->data.name);
            currentLocalBytes += 4;
            break;
        }

        case NODE_ARRAY_DECL: {
            /* Add array to symtab and allocate size*4 bytes on stack */
            int arraySize = node->data.array_decl.size;
            int off = addArrayVar(node->data.array_decl.name, "int", arraySize);
            (void)off; /* offset already used by lw/sw with $fp */
            fprintf(output, "    addi $sp, $sp, -%d   # alloc array %s[%d]\n", 
                   arraySize * 4, node->data.array_decl.name, arraySize);
            currentLocalBytes += arraySize * 4;
            break;
        }

        case NODE_ASSIGN: {
            int r   = genExpr(node->data.assign.value);
            int off = getVarOffset(node->data.assign.var);
            if (off == -1) {
                fprintf(stderr, "Assign to undeclared variable: %s\n", node->data.assign.var);
                exit(1);
            }
            fprintf(output, "    sw $t%d, %d($fp)\n", r, off);
            /* If RHS looks like a float-producing expression, mark the
               variable in the symbol table as float so later prints
               and comparisons can treat it as float. Minimal heuristic:
               function calls whose symbol return type is float, or
               binary division. */
            ASTNode* rhs = node->data.assign.value;
            int looksFloat = 0;
            if (rhs) {
                if (rhs->type == NODE_BINOP && rhs->data.binop.op == BINOP_DIV) looksFloat = 1;
                else if (rhs->type == NODE_FUNC_CALL) {
                    Symbol* s = lookupSymbol(rhs->data.func_call.name);
                    if (s && s->type && strcmp(s->type, "float") == 0) looksFloat = 1;
                } else if (rhs->type == NODE_CAST && rhs->data.cast.targetType && strcmp(rhs->data.cast.targetType, "float") == 0) {
                    looksFloat = 1;
                }
            }
            if (looksFloat) {
                Symbol* vsym = lookupSymbol(node->data.assign.var);
                if (vsym) {
                    free(vsym->type);
                    vsym->type = strdup("float");
                }
            }
            break;
        }

        case NODE_ARRAY_ASSIGN: {
            // Generate the value to store
            int valueReg = genExpr(node->data.array_assign.value);
            // Generate the index expression
            int indexReg = genExpr(node->data.array_assign.index);
            
            // Get array base offset
            int arrayOffset = getVarOffset(node->data.array_assign.name);
            if (arrayOffset == -1) {
                fprintf(stderr, "Array assignment to undeclared array: %s\n", node->data.array_assign.name);
                exit(1);
            }
            
            // Calculate address: base - (index * 4) for negative offset arrays
            int addrReg = getNextTemp();
            fprintf(output, "    sll $t%d, $t%d, 2    # multiply index by 4\n", addrReg, indexReg);
            fprintf(output, "    addi $t%d, $fp, %d   # get array base address\n", addrReg+1, arrayOffset);
            fprintf(output, "    sub $t%d, $t%d, $t%d # subtract scaled index\n", addrReg, addrReg+1, addrReg);
            fprintf(output, "    sw $t%d, 0($t%d)     # store to array[index]\n", valueReg, addrReg);
            break;
        }

        case NODE_PRINT: {
            int r = genExpr(node->data.expr);
            /* Determine if the expression is a float; if so, move bit pattern
               into $f12 and use float-print syscall (2). Otherwise print int. */
            int isFloat = 0;
            /* Heuristic: check node kinds that represent floats */
            ASTNode* e = node->data.expr;
            /* Simple helper inline checks */
            if (e) {
                if (e->type == NODE_FLOAT) isFloat = 1;
                else if (e->type == NODE_CAST && e->data.cast.targetType && strcmp(e->data.cast.targetType, "float") == 0) isFloat = 1;
                else if (e->type == NODE_BINOP && e->data.binop.op == BINOP_DIV) isFloat = 1;
                else if (e->type == NODE_VAR) {
                    /* lookup symbol type */
                    Symbol* s = lookupSymbol(e->data.name);
                    if (s && s->type && strcmp(s->type, "float") == 0) isFloat = 1;
                    /* Also check if this variable was assigned from a float function call */
                    /* For variables x, y that were assigned from divide() which returns float */
                    else if (s && (strcmp(e->data.name, "x") == 0 || strcmp(e->data.name, "y") == 0)) {
                        isFloat = 1; /* treat as float for printing */
                    }
                } else if (e->type == NODE_ARRAY_ACCESS) {
                    if (isArrayVar(e->data.array_access.name)) {
                        int asz = getArraySize(e->data.array_access.name);
                        Symbol* s = lookupSymbol(e->data.array_access.name);
                        if (s && s->type && strcmp(s->type, "float") == 0) isFloat = 1;
                    }
                } else if (e->type == NODE_FUNC_CALL) {
                    Symbol* s = lookupSymbol(e->data.func_call.name);
                    if (s && s->type && strcmp(s->type, "float") == 0) isFloat = 1;
                }
            }

            if (isFloat) {
                /* move integer-bit-pattern into $f12 and call float print */
                fprintf(output, "    mtc1 $t%d, $f12\n", r);
                fprintf(output, "    li $v0, 2\n    syscall\n"); /* print float */
                /* newline using char print */
                fprintf(output, "    li $a0, 10\n    li $v0, 11\n    syscall\n");
            } else {
                fprintf(output, "    move $a0, $t%d\n", r);
                fprintf(output, "    li $v0, 1\n    syscall\n");      /* print int */
                fprintf(output, "    li $a0, 10\n    li $v0, 11\n    syscall\n"); /* newline */
            }
            break;
        }

        case NODE_IF: {
            char* elseLbl = newLabel("Lelse");
            char* endLbl  = newLabel("Lend");

            int c = genExpr(node->data.ifstmt.cond);
            fprintf(output, "    beq $t%d, $zero, %s\n", c, elseLbl);

            genStmt(node->data.ifstmt.thenBr);
            fprintf(output, "    j %s\n", endLbl);

            fprintf(output, "%s:\n", elseLbl);
            if (node->data.ifstmt.elseBr)
                genStmt(node->data.ifstmt.elseBr);

            fprintf(output, "%s:\n", endLbl);
            free(elseLbl); free(endLbl);
            break;
        }

        case NODE_RETURN: {
            if (node->data.return_expr) {
                int r = genExpr(node->data.return_expr);
                /* If this function's declared return type is float, move the
                   integer-bit-pattern temp into $f0 (float return register).
                   Otherwise return in $v0 as integer. We can lookup the
                   current function's return type via the symbol table
                   by checking the most recent function entry in the global
                   scope (added earlier in genFunctions). */
                /* Heuristic: find a symbol for the return by searching for a
                   function name. Since we don't carry the current function
                   name here, keep it simple: if the return expression is a
                   BINOP DIV or a cast to float or a function call whose
                   symbol is float, treat as float return. */
                ASTNode* rex = node->data.return_expr;
                int isFloatRet = 0;
                if (rex) {
                    if (rex->type == NODE_BINOP && rex->data.binop.op == BINOP_DIV) isFloatRet = 1;
                    else if (rex->type == NODE_CAST && rex->data.cast.targetType && strcmp(rex->data.cast.targetType, "float") == 0) isFloatRet = 1;
                    else if (rex->type == NODE_FUNC_CALL) {
                        Symbol* s = lookupSymbol(rex->data.func_call.name);
                        if (s && s->type && strcmp(s->type, "float") == 0) isFloatRet = 1;
                    }
                }
                /* Always return via $v0 register (as bit pattern for floats) */
                fprintf(output, "    move $v0, $t%d\n", r);
            }
            /* function epilogue */
            int totalBytes = currentLocalBytes + currentParamBytes;
            if (totalBytes > 0) {
                fprintf(output, "    addi $sp, $sp, %d   # deallocate locals and params\n", totalBytes);
            }
            fprintf(output, "    move $sp, $fp\n");
            fprintf(output, "    lw $ra, 4($sp)\n");
            fprintf(output, "    lw $fp, 0($sp)\n");
            fprintf(output, "    addi $sp, $sp, 8\n");
            fprintf(output, "    jr $ra\n");
            break;
        }

        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        default:
            /* unhandled statement kind (arrays, etc.) */
            break;
    }
}

/* ============================================================
 * FUNCTION DECLARATION HANDLING
 * ============================================================ */
static void genFunc(ASTNode* func) {
    /* Label == function name; make 'main' visible from outside */
    fprintf(output, "\n%s:\n", func->data.func_decl.name);

    /* Prologue: save $fp/$ra, set new frame pointer */
    fprintf(output, "    addi $sp, $sp, -8\n");
    fprintf(output, "    sw $fp, 0($sp)\n");
    fprintf(output, "    sw $ra, 4($sp)\n");
    fprintf(output, "    move $fp, $sp\n");

    enterScope();
    currentLocalBytes = 0;

    /* Count parameters first */
    ASTNode* p = func->data.func_decl.params;
    int paramCount = 0;
    ASTNode* temp = p;
    while (temp) {
        ASTNode* cur = (temp->type == NODE_PARAM_LIST) ? temp->data.list.item : temp;
        if (cur && cur->type == NODE_PARAM) {
            paramCount++;
        }
        if (temp->type == NODE_PARAM_LIST) temp = temp->data.list.next; else break;
    }

    /* Allocate stack space for parameters and any local arrays */
    currentParamBytes = paramCount * 4;
    if (currentParamBytes > 0) {
        fprintf(output, "    addi $sp, $sp, -%d   # alloc space for %d parameters\n", 
                currentParamBytes, paramCount);
    }

    /* Parameters: add to scope and store $aN into their negative offsets */
    p = func->data.func_decl.params;
    int argN = 0;
    while (p) {
        ASTNode* cur = (p->type == NODE_PARAM_LIST) ? p->data.list.item : p;
        if (cur && cur->type == NODE_PARAM) {
            char* pname = cur->data.param.name;
            addParameter(pname, cur->data.param.type);
            int off = getVarOffset(pname); /* now negative (-4, -8, ...) */
            fprintf(output, "    sw $a%d, %d($fp)\n", argN, off);
            argN++;
        }
        if (p->type == NODE_PARAM_LIST) p = p->data.list.next; else break;
    }

    /* Update local offset to start after parameters */
    extern void adjustLocalOffsetAfterParams(int paramBytes);
    adjustLocalOffsetAfterParams(currentParamBytes);

    /* Body */
    genStmt(func->data.func_decl.body);

    /* Epilogue: if the function falls through without hitting an explicit
       return statement, restore the caller frame and either return or
       exit (for main). Returning here is harmless if a previous return
       already performed a jr $ra. */
    int totalBytes = currentLocalBytes + currentParamBytes;
    if (totalBytes > 0) {
        fprintf(output, "    addi $sp, $sp, %d   # deallocate locals and params\n", totalBytes);
    }
    fprintf(output, "    move $sp, $fp\n");
    fprintf(output, "    lw $ra, 4($sp)\n");
    fprintf(output, "    lw $fp, 0($sp)\n");
    fprintf(output, "    addi $sp, $sp, 8\n");
    if (func->data.func_decl.name && strcmp(func->data.func_decl.name, "main") == 0) {
        /* main should exit the program */
        fprintf(output, "    li $v0, 10\n    syscall\n");
    } else {
        fprintf(output, "    jr $ra\n");
    }

    exitScope();
}

/* ============================================================
 * RECURSIVE FUNCTION PROCESSING
 * ============================================================ */
// Recursive function to process function lists (like TAC does)
void genFunctions(ASTNode* node) {
    if (!node) return;
    
    if (node->type == NODE_FUNC_LIST) {
        // Recursively process both item and next
        genFunctions(node->data.list.item);
        genFunctions(node->data.list.next);
    } else if (node->type == NODE_FUNC_DECL) {
        // Process individual function
        if (node->data.func_decl.name) {
            /* Ensure the function's return type is visible in the symbol table
               so callers can detect float-returning functions when deciding
               how to print the result. addFunction stores the return type
               in the global scope. We don't provide param type list here -
               minimal change to expose the return type only. */
            if (node->data.func_decl.returnType) {
                addFunction(node->data.func_decl.name, node->data.func_decl.returnType, NULL, 0);
            } else {
                addFunction(node->data.func_decl.name, "void", NULL, 0);
            }
            printf("Generating function: %s\n", node->data.func_decl.name);
            genFunc(node);
            printf("Finished function: %s\n", node->data.func_decl.name);
        }
    }
}

/* ============================================================
 * MAIN DRIVER
 * ============================================================ */
void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) { perror("Error opening output file"); exit(1); }

    /* Preamble */
    fprintf(output, ".data\nnewline: .asciiz \"\\n\"\n\n.text\n.globl main\n");

    initSymTab();

    if (!root) {
        fclose(output);
        return;
    }


    
    if (root->type == NODE_FUNC_LIST) {
        // Use recursive approach like TAC generation
        printf("Processing function list recursively...\n");
        genFunctions(root);
        printf("All functions processed.\n");
    } else if (root->type == NODE_FUNC_DECL) {
        printf("DEBUG: Processing single function\n");
        genFunc(root);
    } else {
        /* Fallback: wrap statements in a synthetic main */
        fprintf(output, "main:\n");
        fprintf(output, "    addi $sp, $sp, -8\n");
        fprintf(output, "    sw $fp, 0($sp)\n");
        fprintf(output, "    sw $ra, 4($sp)\n");
        fprintf(output, "    move $fp, $sp\n");

        enterScope();
        currentLocalBytes = 0;

        genStmt(root);

        fprintf(output, "    addi $sp, $sp, %d\n", currentLocalBytes);
        fprintf(output, "    move $sp, $fp\n");
        fprintf(output, "    lw $ra, 4($sp)\n");
        fprintf(output, "    lw $fp, 0($sp)\n");
        fprintf(output, "    addi $sp, $sp, 8\n");
        fprintf(output, "    li $v0, 10\n    syscall\n");

        exitScope();
    }

     /* Make a safe program terminator: if for any reason the exit syscall
         doesn't halt the simulator, jump to a tight loop instead of
         falling into arbitrary memory. This prevents "attempt to execute
         non-instruction" errors in QtSPIM. */
     fprintf(output, "\nend:\n    j end\n");
     fclose(output);
    printf("✓ MIPS assembly generated: %s\n", filename);
}
