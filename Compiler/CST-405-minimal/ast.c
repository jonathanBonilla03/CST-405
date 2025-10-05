#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* === MEMORY MANAGEMENT === */
static ASTMemoryManager ast_manager;

void init_ast_memory() {
    ast_manager.head = malloc(sizeof(MemPool));
    ast_manager.head->memory = malloc(POOL_SIZE);
    ast_manager.head->used = 0;
    ast_manager.head->size = POOL_SIZE;
    ast_manager.head->next = NULL;
    ast_manager.current = ast_manager.head;
}

void* ast_alloc(size_t size) {
    if (!ast_manager.current || ast_manager.current->used + size > ast_manager.current->size) {
        MemPool* new_pool = malloc(sizeof(MemPool));
        new_pool->memory = malloc(POOL_SIZE);
        new_pool->used = 0;
        new_pool->size = POOL_SIZE;
        new_pool->next = NULL;
        ast_manager.current->next = new_pool;
        ast_manager.current = new_pool;
    }

    void* ptr = ast_manager.current->memory + ast_manager.current->used;
    ast_manager.current->used += size;
    return ptr;
}

/* === NODE CONSTRUCTORS === */
ASTNode* createNum(int value) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->data.num = value;
    return node;
}

ASTNode* createFloat(float value) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_FLOAT;
    node->data.decimal = value;
    return node;
}

ASTNode* createVar(char* name) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->data.name = strdup(name);
    return node;
}

ASTNode* createBool(bool value) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_BOOL;
    node->data.boolean = value;
    return node;
}

ASTNode* createBinOp(BinOpKind op, ASTNode* left, ASTNode* right) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

ASTNode* createUnaryOp(UnOpKind op, ASTNode* expr) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_UNOP;
    node->data.unop.op = op;
    node->data.unop.expr = expr;
    return node;
}

ASTNode* createDecl(char* name) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->data.name = strdup(name);
    return node;
}

ASTNode* createAssign(char* var, ASTNode* value) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var = strdup(var);
    node->data.assign.value = value;
    return node;
}

ASTNode* createPrint(ASTNode* expr) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.expr = expr;
    return node;
}

ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.stmtlist.stmt = stmt1;
    node->data.stmtlist.next = stmt2;
    return node;
}

ASTNode* createArrayDecl(char* name, int size) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_DECL;
    node->data.array_decl.name = strdup(name);
    node->data.array_decl.size = size;
    return node;
}

ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ASSIGN;
    node->data.array_assign.name = strdup(name);
    node->data.array_assign.index = index;
    node->data.array_assign.value = value;
    return node;
}

ASTNode* createArrayAccess(char* name, ASTNode* index) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->data.array_access.name = strdup(name);
    node->data.array_access.index = index;
    return node;
}

ASTNode* createRelop(RelopKind op, ASTNode* left, ASTNode* right) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_RELOP;
    node->data.relop.op = op;
    node->data.relop.left = left;
    node->data.relop.right = right;
    return node;
}

ASTNode* createIf(ASTNode* cond, ASTNode* thenBr, ASTNode* elseBr) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->data.ifstmt.cond = cond;
    node->data.ifstmt.thenBr = thenBr;
    node->data.ifstmt.elseBr = elseBr;
    return node;
}

/* === AST PRINT FUNCTION === */
void printAST(ASTNode* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_NUM:
            printf("NUM(%d)\n", node->data.num);
            break;
        case NODE_FLOAT:
            printf("FLOAT(%f)\n", node->data.decimal);
            break;
        case NODE_VAR:
            printf("VAR(%s)\n", node->data.name);
            break;
        case NODE_BOOL:
            printf("BOOL(%s)\n", node->data.boolean ? "true" : "false");
            break;
        case NODE_BINOP:
            printf("BINOP(");
            switch (node->data.binop.op) {
                case BINOP_ADD: printf("+"); break;
                case BINOP_SUB: printf("-"); break;
                case BINOP_MUL: printf("*"); break;
                case BINOP_DIV: printf("/"); break;
                case BINOP_MOD: printf("%%"); break;
                case BINOP_AND: printf("&&"); break;
                case BINOP_OR:  printf("||"); break;
            }
            printf(")\n");
            printAST(node->data.binop.left, level + 1);
            printAST(node->data.binop.right, level + 1);
            break;
        case NODE_UNOP:
            printf("UNOP(");
            switch (node->data.unop.op) {
                case UNOP_NEG: printf("-"); break;
                case UNOP_NOT: printf("!"); break;
            }
            printf(")\n");
            printAST(node->data.unop.expr, level + 1);
            break;
        case NODE_RELOP:
            printf("RELOP(");
            switch (node->data.relop.op) {
                case RELOP_LT: printf("<"); break;
                case RELOP_GT: printf(">"); break;
                case RELOP_LE: printf("<="); break;
                case RELOP_GE: printf(">="); break;
                case RELOP_EQ: printf("=="); break;
                case RELOP_NE: printf("!="); break;
            }
            printf(")\n");
            printAST(node->data.relop.left, level + 1);
            printAST(node->data.relop.right, level + 1);
            break;
        case NODE_DECL:
            printf("DECL(%s)\n", node->data.name);
            break;
        case NODE_ASSIGN:
            printf("ASSIGN(%s)\n", node->data.assign.var);
            printAST(node->data.assign.value, level + 1);
            break;
        case NODE_PRINT:
            printf("PRINT\n");
            printAST(node->data.expr, level + 1);
            break;
        case NODE_ARRAY_DECL:
            printf("ARRAY_DECL(%s[%d])\n", node->data.array_decl.name, node->data.array_decl.size);
            break;
        case NODE_ARRAY_ASSIGN:
            printf("ARRAY_ASSIGN(%s)\n", node->data.array_assign.name);
            printAST(node->data.array_assign.index, level + 1);
            printAST(node->data.array_assign.value, level + 1);
            break;
        case NODE_ARRAY_ACCESS:
            printf("ARRAY_ACCESS(%s)\n", node->data.array_access.name);
            printAST(node->data.array_access.index, level + 1);
            break;
        case NODE_IF:
            printf("IF\n");
            printAST(node->data.ifstmt.cond, level + 1);
            for (int i = 0; i < level; i++) printf("  ");
            printf("THEN:\n");
            printAST(node->data.ifstmt.thenBr, level + 1);
            if (node->data.ifstmt.elseBr) {
                for (int i = 0; i < level; i++) printf("  ");
                printf("ELSE:\n");
                printAST(node->data.ifstmt.elseBr, level + 1);
            }
            break;
        case NODE_STMT_LIST:
            printf("STMT_LIST\n");
            printAST(node->data.stmtlist.stmt, level + 1);
            printAST(node->data.stmtlist.next, level + 1);
            break;
        default:
            printf("UNKNOWN NODE TYPE %d\n", node->type);
            break;
    }
}