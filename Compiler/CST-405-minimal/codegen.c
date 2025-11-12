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
    /* MIPS has $t0-$t9 (10 temp registers), use all of them to reduce conflicts */
    if (tempReg > 9) tempReg = 0;  /* Use $t0 through $t9 */
    return r;
}

/* ============================================================
 * EXPRESSION GENERATION
 * ============================================================ */
static int genExpr(ASTNode* node);
static void genStmt(ASTNode* node);
static int hasFloatCast(ASTNode* node);

/* Helper function to collect arguments from nested ARG_LIST structure */
static void collectArgumentsRecursive(ASTNode* argNode, int* argRegs, int* numArgs) {
    if (!argNode || *numArgs >= 4) return;
    
    if (argNode->type == NODE_ARG_LIST) {
        /* Process the item (left side) first, then the next (right side) */
        collectArgumentsRecursive(argNode->data.list.item, argRegs, numArgs);
        collectArgumentsRecursive(argNode->data.list.next, argRegs, numArgs);
    } else {
        /* This is an actual argument expression - generate code for it */
        int r;
        
        /* Special case: if this is an array variable being passed as argument,
           generate its address instead of loading its value */
        if (argNode->type == NODE_VAR && isArrayVar(argNode->data.name)) {
            int arrayOffset = getVarOffset(argNode->data.name);
            r = getNextTemp();
            fprintf(output, "    addi $t%d, $fp, %d   # get address of array %s\n", 
                   r, arrayOffset, argNode->data.name);
        } else {
            /* Regular argument - generate expression normally */
            r = genExpr(argNode);
        }
        
        argRegs[*numArgs] = r;
        (*numArgs)++;
    }
}

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
        if (s && s->type && strcmp(s->type, "float") == 0) {
            isFloatComparison = 1;
        }
    }
    /* If right is float variable and left is integer, use float comparison */ 
    if (right && right->type == NODE_VAR && left && left->type == NODE_NUM) {
        Symbol* s = lookupSymbol(right->data.name);
        if (s && s->type && strcmp(s->type, "float") == 0) {
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

/* Helper function to recursively check if an expression contains float casts */
static int hasFloatCast(ASTNode* node) {
    if (!node) return 0;
    
    if (node->type == NODE_CAST && node->data.cast.targetType && 
        strcmp(node->data.cast.targetType, "float") == 0) {
        return 1;
    }
    
    /* Recursively check child nodes */
    switch (node->type) {
        case NODE_BINOP:
            return hasFloatCast(node->data.binop.left) || hasFloatCast(node->data.binop.right);
        case NODE_CAST:
            return hasFloatCast(node->data.cast.expr);
        case NODE_FUNC_CALL:
            /* Check if function returns float */
            {
                Symbol* funcSym = lookupSymbol(node->data.func_call.name);
                if (funcSym && funcSym->type && strcmp(funcSym->type, "float") == 0) {
                    return 1;
                }
            }
            /* Also check arguments */
            if (node->data.func_call.args) {
                return hasFloatCast(node->data.func_call.args);
            }
            break;
        case NODE_ARG_LIST:
            return hasFloatCast(node->data.list.item) || hasFloatCast(node->data.list.next);
        default:
            break;
    }
    return 0;
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

        case NODE_FLOAT: {
            int r = getNextTemp();
            /* Convert float to IEEE 754 bit pattern and load it */
            /* For simplicity, we'll use the FPU to convert and then move to integer register */
            fprintf(output, "    li.s $f0, %f\n", node->data.decimal);
            fprintf(output, "    mfc1 $t%d, $f0\n", r);
            return r;
        }

        case NODE_STRING: {
            /* For string literals, we need to store them in the data section */
            /* and return a reference to them */
            int r = getNextTemp();
            static int string_counter = 0;
            
            /* Generate a unique label for this string */
            fprintf(output, "    .data\n");
            fprintf(output, "string_%d: .asciiz \"%s\"\n", string_counter, node->data.string);
            fprintf(output, "    .text\n");
            fprintf(output, "    la $t%d, string_%d\n", r, string_counter);
            string_counter++;
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
            /* Handle exponentiation specially for floating-point support */
            if (node->data.binop.op == BINOP_EXP) {
                int d = getNextTemp();
                
                /* Generate base value first and preserve it */
                int a = genExpr(node->data.binop.left);
                
                /* Save base to memory to prevent register conflicts */
                fprintf(output, "    addi $sp, $sp, -4   # allocate space for base\n");
                fprintf(output, "    sw $t%d, 0($sp)     # save base value\n", a);
                
                /* Generate exponent value */
                int b = genExpr(node->data.binop.right);
                
                /* Restore base from memory */
                int base_reg = getNextTemp();
                fprintf(output, "    lw $t%d, 0($sp)     # restore base value\n", base_reg);
                fprintf(output, "    addi $sp, $sp, 4    # deallocate space for base\n");
                
                /* Check if we have float cast anywhere in the expression */
                int hasFloats = hasFloatCast(node->data.binop.left) || hasFloatCast(node->data.binop.right);
                
                if (hasFloats) {
                    /* Simplified floating-point exponentiation for QtSPIM compatibility */
                    /* Use only basic floating-point operations to avoid QtSPIM issues */
                    
                    fprintf(output, "    mtc1 $t%d, $f0     # move base to float reg\n", base_reg);
                    fprintf(output, "    mtc1 $t%d, $f2     # move exponent to float reg\n", b);
                    
                    /* Extract integer and fractional parts of exponent */
                    fprintf(output, "    cvt.w.s $f4, $f2   # convert exponent to integer (truncates)\n");
                    fprintf(output, "    mfc1 $t1, $f4      # get integer exponent\n");
                    fprintf(output, "    cvt.s.w $f6, $f4   # convert integer back to float\n");
                    fprintf(output, "    sub.s $f8, $f2, $f6 # f8 = fractional part\n");
                    
                    /* Check if fractional part is approximately 0.5 (for square root) */
                    fprintf(output, "    li.s $f10, 0.5     # load 0.5\n");
                    fprintf(output, "    sub.s $f12, $f8, $f10 # frac - 0.5\n");
                    fprintf(output, "    mfc1 $t5, $f12     # get difference as bits\n");
                    fprintf(output, "    li $t6, 0x3A83126F  # small epsilon (0.001) as bits\n");
                    fprintf(output, "    slt $t7, $t5, $t6  # check if |frac - 0.5| < epsilon (approximate)\n");
                    
                    /* Handle special case: if integer exponent is 1 or 2, use simple multiplication */
                    char* loopLbl = newLabel("Lfexp_loop");
                    char* endLbl = newLabel("Lfexp_end"); 
                    char* zeroLbl = newLabel("Lfexp_zero");
                    char* oneLbl = newLabel("Lfexp_one");
                    char* twoLbl = newLabel("Lfexp_two");
                    int temp1 = getNextTemp();
                    
                    /* Check for special cases */
                    fprintf(output, "    beqz $t1, %s       # if exponent is 0, result is 1\n", zeroLbl);
                    fprintf(output, "    li $t5, 1\n");
                    fprintf(output, "    beq $t1, $t5, %s   # if exponent is 1, check for fractional part\n", oneLbl);
                    fprintf(output, "    li $t5, 2\n");
                    fprintf(output, "    beq $t1, $t5, %s   # if exponent is 2, result is base^2\n", twoLbl);
                    
                    /* General case: use integer-based loop for exponentiation */
                    fprintf(output, "    li.s $f8, 1.0      # result = 1.0\n");
                    fprintf(output, "    move $t%d, $t1     # counter = exponent\n", temp1);
                    
                    fprintf(output, "%s:\n", loopLbl);
                    fprintf(output, "    beqz $t%d, %s      # if counter is 0, exit loop\n", temp1, endLbl);
                    fprintf(output, "    mul.s $f8, $f8, $f0 # result *= base\n");
                    fprintf(output, "    addi $t%d, $t%d, -1 # counter--\n", temp1, temp1);
                    fprintf(output, "    j %s\n", loopLbl);
                    
                    /* Special cases */
                    fprintf(output, "%s:\n", zeroLbl);
                    fprintf(output, "    li.s $f8, 1.0      # result = 1.0 (base^0)\n");
                    fprintf(output, "    j %s\n", endLbl);
                    
                    fprintf(output, "%s:\n", oneLbl);
                    /* Check if we have fractional part ≈ 0.5 (for x^1.5 = x * sqrt(x)) */
                    fprintf(output, "    mfc1 $t8, $f8      # get fractional part as bits\n");
                    fprintf(output, "    li $t9, 0x3F000000  # 0.5 as IEEE 754 bits\n");
                    fprintf(output, "    li $t4, 0x3A83126F  # small epsilon\n");
                    fprintf(output, "    sub $t8, $t8, $t9  # frac - 0.5\n");
                    fprintf(output, "    slt $t6, $t8, $t4  # check if |frac - 0.5| < epsilon\n");
                    char* sqrtLbl = newLabel("Lfexp_sqrt");
                    char* normalLbl = newLabel("Lfexp_normal");
                    fprintf(output, "    bnez $t6, %s       # if close to 0.5, do square root\n", sqrtLbl);
                    
                    /* Normal case: base^1 */
                    fprintf(output, "    li.s $f9, 0.0      # load zero\n");
                    fprintf(output, "    add.s $f8, $f0, $f9 # result = base (base^1)\n");
                    fprintf(output, "    j %s\n", endLbl);
                    
                    /* Square root case: base^1.5 ≈ base * sqrt(base) */
                    fprintf(output, "%s:\n", sqrtLbl);
                    fprintf(output, "    sqrt.s $f10, $f0   # sqrt(base)\n");
                    fprintf(output, "    mul.s $f8, $f0, $f10 # result = base * sqrt(base)\n");
                    fprintf(output, "    j %s\n", endLbl);
                    
                    fprintf(output, "%s:\n", normalLbl);
                    
                    fprintf(output, "%s:\n", twoLbl);
                    fprintf(output, "    mul.s $f8, $f0, $f0 # result = base * base (base^2)\n");
                    
                    fprintf(output, "%s:\n", endLbl);
                    fprintf(output, "    mfc1 $t%d, $f8     # get float result as bits\n", d);
                    
                } else {
                    /* Integer exponentiation (fallback) */
                    char* loopLbl = newLabel("Lexp_loop");
                    char* endLbl = newLabel("Lexp_end");
                    char* zeroLbl = newLabel("Lexp_zero");
                    int temp1 = getNextTemp();
                    
                    fprintf(output, "    beqz $t%d, %s      # if exponent is 0, result is 1\n", b, zeroLbl);
                    fprintf(output, "    li $t%d, 1         # result = 1\n", d);
                    fprintf(output, "    move $t%d, $t%d    # counter = exponent\n", temp1, b);
                    
                    fprintf(output, "%s:\n", loopLbl);
                    fprintf(output, "    beqz $t%d, %s      # if counter is 0, exit loop\n", temp1, endLbl);
                    fprintf(output, "    mul $t%d, $t%d, $t%d  # result *= base\n", d, d, base_reg);
                    fprintf(output, "    addi $t%d, $t%d, -1   # counter--\n", temp1, temp1);
                    fprintf(output, "    j %s\n", loopLbl);
                    
                    fprintf(output, "%s:\n", zeroLbl);
                    fprintf(output, "    li $t%d, 1         # result = 1\n", d);
                    
                    fprintf(output, "%s:\n", endLbl);
                }
                return d;
            }

            /* For all other binary operations */
            int a = genExpr(node->data.binop.left);
            int b = genExpr(node->data.binop.right);
            int d = getNextTemp();

            /* Check if we're doing float arithmetic - detect if any operand involves casts to float */
            int isFloatArith = 0;
            ASTNode* left = node->data.binop.left;
            ASTNode* right = node->data.binop.right;
            
            /* Check for explicit float casts or expressions that would result in float bit patterns */
            if (hasFloatCast(left) || hasFloatCast(right)) isFloatArith = 1;
            
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
                        /* Assume operands are already IEEE 754 bit patterns from casts */
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
                        /* Assume operands are already IEEE 754 bit patterns from casts */
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
                        /* Assume operands are already IEEE 754 bit patterns from casts */
                        fprintf(output, "    mtc1 $t%d, $f0\n", a);
                        fprintf(output, "    mtc1 $t%d, $f2\n", b);
                        fprintf(output, "    mul.s $f4, $f0, $f2\n");
                        fprintf(output, "    mfc1 $t%d, $f4\n", d);
                    } else {
                        fprintf(output, "    mul $t%d, $t%d, $t%d\n", d, a, b);
                    }
                    break;
                case BINOP_DIV:
                    if (isFloatArith) {
                        /* Float division - use floating-point instructions */
                        fprintf(output, "    mtc1 $t%d, $f0\n", a);  /* move to float reg */
                        fprintf(output, "    mtc1 $t%d, $f2\n", b);  /* move to float reg */
                        fprintf(output, "    div.s $f4, $f0, $f2\n"); /* float divide */
                        fprintf(output, "    mfc1 $t%d, $f4\n", d);  /* move result back */
                    } else {
                        /* Integer division - use MIPS div instruction and get quotient */
                        fprintf(output, "    div $t%d, $t%d\n", a, b);  /* a / b */
                        fprintf(output, "    mflo $t%d\n", d);         /* quotient (truncated toward zero) */
                    }
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
            int baseReg = getNextTemp();
            int destReg = getNextTemp();
            fprintf(output, "    sll $t%d, $t%d, 2    # multiply index by 4\n", addrReg, indexReg);
            
            if (isArrayVar(node->data.array_access.name)) {
                // Local array: offset is the array location itself
                fprintf(output, "    addi $t%d, $fp, %d   # get array base address\n", baseReg, arrayOffset);
                fprintf(output, "    sub $t%d, $t%d, $t%d # subtract scaled index\n", addrReg, baseReg, addrReg);
            } else {
                // Array parameter: offset points to where array address is stored
                fprintf(output, "    lw $t%d, %d($fp)     # load array address from parameter\n", baseReg, arrayOffset);
                fprintf(output, "    add $t%d, $t%d, $t%d # add scaled index to array address\n", addrReg, baseReg, addrReg);
            }
            fprintf(output, "    lw $t%d, 0($t%d)     # load from array[index]\n", destReg, addrReg);
            return destReg;
        }

        case NODE_FUNC_CALL: {
            /* Handle built-in I/O functions with syscalls */
            if (strcmp(node->data.func_call.name, "input") == 0) {
                /* input() - read integer from user */
                fprintf(output, "    li $v0, 5      # syscall for read_int\n");
                fprintf(output, "    syscall\n");
                int dest = getNextTemp();
                fprintf(output, "    move $t%d, $v0\n", dest);
                return dest;
            }
            else if (strcmp(node->data.func_call.name, "output") == 0) {
                /* output(value) - print integer */
                ASTNode* arg = node->data.func_call.args;
                if (arg) {
                    ASTNode* cur = (arg->type == NODE_ARG_LIST) ? arg->data.list.item : arg;
                    int r = genExpr(cur);
                    fprintf(output, "    move $a0, $t%d\n", r);
                    fprintf(output, "    li $v0, 1      # syscall for print_int\n");
                    fprintf(output, "    syscall\n");
                    /* Print newline after each number for readability */
                    fprintf(output, "    la $a0, newline\n");
                    fprintf(output, "    li $v0, 4      # syscall for print_string\n");
                    fprintf(output, "    syscall\n");
                }
                int dest = getNextTemp();
                fprintf(output, "    li $t%d, 0     # output returns void (0)\n", dest);
                return dest;
            }
            else if (strcmp(node->data.func_call.name, "outputString") == 0) {
                /* outputString(string) - print string */
                ASTNode* arg = node->data.func_call.args;
                if (arg) {
                    ASTNode* cur = (arg->type == NODE_ARG_LIST) ? arg->data.list.item : arg;
                    int r = genExpr(cur);
                    fprintf(output, "    move $a0, $t%d\n", r);
                    fprintf(output, "    li $v0, 4      # syscall for print_string\n");
                    fprintf(output, "    syscall\n");
                }
                int dest = getNextTemp();
                fprintf(output, "    li $t%d, 0     # outputString returns void (0)\n", dest);
                return dest;
            }
            
            /* Regular user-defined function calls */
            /* Collect all arguments by properly handling nested ARG_LIST structure */
            ASTNode* arg = node->data.func_call.args;
            int argRegs[4]; /* Store temp registers for up to 4 arguments */
            int numArgs = 0;

            /* Collect all arguments recursively */
            collectArgumentsRecursive(arg, argRegs, &numArgs);

            /* Move temp registers to argument registers in order */
            for (int i = 0; i < numArgs; i++) {
                fprintf(output, "    move $a%d, $t%d\n", i, argRegs[i]);
            }

            /* Add _func suffix to avoid MIPS instruction conflicts, except for main */
            if (strcmp(node->data.func_call.name, "main") == 0) {
                fprintf(output, "    jal %s\n", node->data.func_call.name);
            } else {
                fprintf(output, "    jal %s_func\n", node->data.func_call.name);
            }

            /* All functions return via $v0 (bit pattern for floats) */
            int dest = getNextTemp();
            fprintf(output, "    move $t%d, $v0\n", dest);
            return dest;
        }

        case NODE_INIT_LIST:
            /* INIT_LIST should not be processed as standalone expression */
            fprintf(stderr, "Error: NODE_INIT_LIST should not be processed as expression\n");
            exit(1);

        case NODE_ARG_LIST:
            /* ARG_LIST should not be processed as standalone expression */
            fprintf(stderr, "DEBUG: NODE_ARG_LIST encountered in genExpr\n");
            fprintf(stderr, "       This indicates a problem in AST structure\n");
            
            /* Try to process the first item in the list as a workaround */
            if (node->data.list.item) {
                fprintf(stderr, "       Processing first item in arg list as workaround\n");
                return genExpr(node->data.list.item);
            } else {
                fprintf(stderr, "       Empty arg list - returning 0\n");
                return 0;
            }
            break;

        case NODE_BLOCK:
            /* NODE_BLOCK should not be processed as expression, treat as statement */
            printf("DEBUG: NODE_BLOCK found in genExpr(), converting to statement\n");
            fflush(stdout);
            genStmt(node);
            return 0; /* Return dummy value */

        default:
            fprintf(stderr, "Unsupported expression node type: %d\n", node->type);
            exit(1);
    }
}

/* ============================================================
 * ARRAY INITIALIZATION HELPER  
 * ============================================================ */
static int generateArrayInitCode(ASTNode* init_list, char* array_name, int start_index) {
    if (!init_list) return start_index;
    
    if (init_list->type == NODE_INIT_LIST) {
        // Process the left side (expr field) recursively  
        int next_index = generateArrayInitCode(init_list->data.init_list.expr, array_name, start_index);
        // Process the right side (next field)
        return generateArrayInitCode(init_list->data.init_list.next, array_name, next_index);
    } else {
        // Leaf node - generate code to store value
        int value_reg = genExpr(init_list);
        
        /* Calculate array element address and store value */
        int array_base_off = getVarOffset(array_name);
        if (array_base_off == -1) {
            fprintf(stderr, "Array initialization error for %s[%d]\n", array_name, start_index);
            exit(1);
        }
        // Calculate offset for this element: base_offset - (index * 4)
        int element_offset = array_base_off - (start_index * 4);
        fprintf(output, "    sw $t%d, %d($fp)   # %s[%d] = value\n", 
               value_reg, element_offset, array_name, start_index);
        
        return start_index + 1;
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
            int off = addVar(node->data.decl.name, node->data.decl.type);
            (void)off; /* offset already used by lw/sw with $fp */
            fprintf(output, "    addi $sp, $sp, -4   # alloc local %s (%s)\n", 
                   node->data.decl.name, node->data.decl.type);
            currentLocalBytes += 4;
            break;
        }

        case NODE_DECL_INIT: {
            /* Add to symtab, allocate space, and initialize */
            int off = addVar(node->data.decl_init.name, node->data.decl_init.type);
            fprintf(output, "    addi $sp, $sp, -4   # alloc local %s (%s)\n", 
                   node->data.decl_init.name, node->data.decl_init.type);
            currentLocalBytes += 4;
            
            /* Generate code for the initialization value and store it */
            int r = genExpr(node->data.decl_init.value);
            fprintf(output, "    sw $t%d, %d($fp)\n", r, off);
            break;
        }

        case NODE_ARRAY_DECL: {
            /* Add array to symtab and allocate size*4 bytes on stack */
            int arraySize = node->data.array_decl.size;
            int off = addArrayVar(node->data.array_decl.name, node->data.array_decl.type, arraySize);
            (void)off; /* offset already used by lw/sw with $fp */
            fprintf(output, "    addi $sp, $sp, -%d   # alloc array %s[%d] (%s)\n", 
                   arraySize * 4, node->data.array_decl.name, arraySize, node->data.array_decl.type);
            currentLocalBytes += arraySize * 4;
            break;
        }

        case NODE_ARRAY_INIT_DECL: {
            /* Add array to symtab and allocate size*4 bytes on stack */
            int arraySize = node->data.array_init_decl.size;
            int off = addArrayVar(node->data.array_init_decl.name, node->data.array_init_decl.type, arraySize);
            (void)off; /* offset already used by lw/sw with $fp */
            fprintf(output, "    addi $sp, $sp, -%d   # alloc array %s[%d] (%s)\n", 
                   arraySize * 4, node->data.array_init_decl.name, arraySize, node->data.array_init_decl.type);
            currentLocalBytes += arraySize * 4;

            /* Initialize array elements using helper */
            generateArrayInitCode(node->data.array_init_decl.init_list, node->data.array_init_decl.name, 0);
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
               and comparisons can treat it as float. Enhanced heuristic:
               function calls whose symbol return type is float, binary division,
               casts to float, exponentiation with float operands, or any
               expression containing float casts. */
            ASTNode* rhs = node->data.assign.value;
            int looksFloat = 0;
            if (rhs) {
                if (rhs->type == NODE_BINOP && rhs->data.binop.op == BINOP_DIV) looksFloat = 1;
                else if (rhs->type == NODE_BINOP && rhs->data.binop.op == BINOP_EXP && hasFloatCast(rhs)) looksFloat = 1;
                else if (rhs->type == NODE_FUNC_CALL) {
                    Symbol* s = lookupSymbol(rhs->data.func_call.name);
                    if (s && s->type && strcmp(s->type, "float") == 0) looksFloat = 1;
                } else if (rhs->type == NODE_CAST && rhs->data.cast.targetType && strcmp(rhs->data.cast.targetType, "float") == 0) {
                    looksFloat = 1;
                } else if (hasFloatCast(rhs)) {
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
            int baseReg = getNextTemp();
            fprintf(output, "    sll $t%d, $t%d, 2    # multiply index by 4\n", addrReg, indexReg);
            
            if (isArrayVar(node->data.array_assign.name)) {
                // Local array: offset is the array location itself
                fprintf(output, "    addi $t%d, $fp, %d   # get array base address\n", baseReg, arrayOffset);
                fprintf(output, "    sub $t%d, $t%d, $t%d # subtract scaled index\n", addrReg, baseReg, addrReg);
            } else {
                // Array parameter: offset points to where array address is stored
                fprintf(output, "    lw $t%d, %d($fp)     # load array address from parameter\n", baseReg, arrayOffset);
                fprintf(output, "    add $t%d, $t%d, $t%d # add scaled index to array address\n", addrReg, baseReg, addrReg);
            }
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
                    /* Variables marked as float in symbol table should be printed as float */
                    /* This relies on proper type tracking in assignments */
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

        case NODE_BLOCK:
            /* NODE_BLOCK uses same structure as NODE_STMT_LIST */
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        case NODE_FUNC_CALL: {
            /* Handle function calls as statements (e.g., output(x);) */
            genExpr(node);  // Reuse the expression handler which has syscall support
            break;
        }

        default:
            /* unhandled statement kind (arrays, etc.) */
            break;
    }
}

/* ============================================================
 * FUNCTION DECLARATION HANDLING
 * ============================================================ */
static void genFunc(ASTNode* func) {
    /* Label == function name; make 'main' visible from outside, add _func suffix to avoid MIPS instruction conflicts */
    if (strcmp(func->data.func_decl.name, "main") == 0) {
        fprintf(output, "\n%s:\n", func->data.func_decl.name);
    } else {
        fprintf(output, "\n%s_func:\n", func->data.func_decl.name);
    }

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
    
    /* Helper function to recursively count parameters */
    void countParams(ASTNode* paramNode) {
        if (!paramNode) return;
        
        if (paramNode->type == NODE_PARAM) {
            paramCount++;
        } else if (paramNode->type == NODE_PARAM_LIST) {
            countParams(paramNode->data.list.item);
            countParams(paramNode->data.list.next);
        }
    }
    
    countParams(p);

    /* Allocate stack space for parameters and any local arrays */
    currentParamBytes = paramCount * 4;
    if (currentParamBytes > 0) {
        fprintf(output, "    addi $sp, $sp, -%d   # alloc space for %d parameters\n", 
                currentParamBytes, paramCount);
    }

    /* Parameters: add to scope and store $aN into their negative offsets */
    p = func->data.func_decl.params;
    int argN = 0;
    
    /* Helper function to recursively process parameters */
    void processParams(ASTNode* paramNode, int* argIndex) {
        if (!paramNode) return;
        
        if (paramNode->type == NODE_PARAM) {
            char* pname = paramNode->data.param.name;
            addParameter(pname, paramNode->data.param.type);
            int off = getVarOffset(pname);
            fprintf(output, "    sw $a%d, %d($fp)\n", *argIndex, off);
            (*argIndex)++;
        } else if (paramNode->type == NODE_PARAM_LIST) {
            processParams(paramNode->data.list.item, argIndex);
            processParams(paramNode->data.list.next, argIndex);
        }
    }
    
    processParams(p, &argN);

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
