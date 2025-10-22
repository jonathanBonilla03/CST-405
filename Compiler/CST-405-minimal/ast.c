#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ast.h"

/* === MEMORY MANAGEMENT === */
static ASTMemoryManager ast_manager;

/* alignment helper */
static size_t align_size(size_t size) {
    size_t a = sizeof(void*);
    return (size + a - 1) & ~(a - 1);
}

void init_ast_memory() {
    ast_manager.head = NULL;
    ast_manager.current = NULL;
    ast_manager.total_allocations = 0;
    ast_manager.pool_count = 0;
    ast_manager.total_memory = 0;

    /* allocate first pool */
    MemPool* p = malloc(sizeof(MemPool));
    p->memory = malloc(POOL_SIZE);
    p->used = 0;
    p->size = POOL_SIZE;
    p->next = NULL;
    ast_manager.head = ast_manager.current = p;
    ast_manager.pool_count = 1;
    ast_manager.total_memory = POOL_SIZE;
}

/* allocate memory from pool (aligned). If request > POOL_SIZE, create a dedicated pool sized to the request. */
void* ast_alloc(size_t size) {
    size = align_size(size);
    if (!ast_manager.head) init_ast_memory();

    MemPool* cur = ast_manager.current;

    /* if request doesn't fit current pool, find or create next pool */
    if (cur->used + size > cur->size) {
        /* if size is larger than POOL_SIZE, create a dedicated pool for this allocation */
        size_t new_pool_size = (size > POOL_SIZE) ? size : POOL_SIZE;
        MemPool* np = malloc(sizeof(MemPool));
        np->memory = malloc(new_pool_size);
        np->used = 0;
        np->size = new_pool_size;
        np->next = NULL;

        cur->next = np;
        ast_manager.current = np;
        ast_manager.pool_count++;
        ast_manager.total_memory += new_pool_size;
        cur = np;
    }

    void* ptr = cur->memory + cur->used;
    cur->used += size;
    ast_manager.total_allocations++;
    return ptr;
}

/* duplicate string into AST pool */
char* ast_strdup(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char* p = (char*)ast_alloc(len);
    memcpy(p, s, len);
    return p;
}

/* reset used counters so pools can be reused without freeing memory */
void ast_reset() {
    MemPool* p = ast_manager.head;
    while (p) {
        p->used = 0;
        p = p->next;
    }
    ast_manager.current = ast_manager.head;
}

/* free all pools (call on program shutdown) */
void ast_free_all() {
    MemPool* p = ast_manager.head;
    while (p) {
        MemPool* nxt = p->next;
        free(p->memory);
        free(p);
        p = nxt;
    }
    ast_manager.head = ast_manager.current = NULL;
    ast_manager.pool_count = 0;
    ast_manager.total_allocations = 0;
    ast_manager.total_memory = 0;
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
    node->data.name = ast_strdup(name);
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
    node->data.name = ast_strdup(name);
    return node;
}

ASTNode* createAssign(char* var, ASTNode* value) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var = ast_strdup(var);
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
    node->data.array_decl.name = ast_strdup(name);
    node->data.array_decl.size = size;
    return node;
}

ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ASSIGN;
    node->data.array_assign.name = ast_strdup(name);
    node->data.array_assign.index = index;
    node->data.array_assign.value = value;
    return node;
}

ASTNode* createArrayAccess(char* name, ASTNode* index) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->data.array_access.name = ast_strdup(name);
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

ASTNode* createCast(char* targetType, ASTNode* expr) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_CAST;
    node->data.cast.targetType = ast_strdup(targetType);
    node->data.cast.expr = expr;
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

ASTNode* createReturn(ASTNode* expr) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.return_expr = expr;
    return node;
}

ASTNode* createFuncDecl(char* returnType, char* name, ASTNode* params, ASTNode* body) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_FUNC_DECL;
    node->data.func_decl.returnType = ast_strdup(returnType);
    node->data.func_decl.name = ast_strdup(name);
    node->data.func_decl.params = params;
    node->data.func_decl.body = body;
    return node;
}

ASTNode* createFuncCall(char* name, ASTNode* args) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_FUNC_CALL;
    node->data.func_call.name = ast_strdup(name);
    node->data.func_call.args = args;
    return node;
}

ASTNode* createParam(char* type, char* name) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->data.param.type = ast_strdup(type);
    node->data.param.name = ast_strdup(name);
    return node;
}

ASTNode* createParamList(ASTNode* param, ASTNode* next) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_PARAM_LIST;
    node->data.list.item = param;
    node->data.list.next = next;
    return node;
}

ASTNode* createArgList(ASTNode* arg, ASTNode* next) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_ARG_LIST;
    node->data.list.item = arg;
    node->data.list.next = next;
    return node;
}

ASTNode* createFuncList(ASTNode* existingList, ASTNode* newFunc) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));
    node->type = NODE_FUNC_LIST;
    node->data.list.item = existingList; // The existing list/function becomes item
    node->data.list.next = newFunc;      // The new function becomes next  
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
        case NODE_CAST:
            printf("CAST(%s)\n", node->data.cast.targetType);
            printAST(node->data.cast.expr, level + 1);
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
        case NODE_RETURN:
            printf("RETURN\n");
            printAST(node->data.return_expr, level + 1);
            break;
        case NODE_FUNC_DECL:
            printf("FUNC_DECL(%s) returns=%s\n", node->data.func_decl.name,
                   node->data.func_decl.returnType ? node->data.func_decl.returnType : "<null>");
            if (node->data.func_decl.params) {
                for (int i = 0; i < level + 1; i++) printf("  ");
                printf("PARAMS:\n");
                printAST(node->data.func_decl.params, level + 2);
            }
            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("BODY:\n");
            printAST(node->data.func_decl.body, level + 2);
            break;
        case NODE_FUNC_CALL:
            printf("FUNC_CALL(%s)\n", node->data.func_call.name);
            if (node->data.func_call.args) {
                for (int i = 0; i < level + 1; i++) printf("  ");
                printf("ARGS:\n");
                printAST(node->data.func_call.args, level + 2);
            }
            break;
        case NODE_PARAM:
            printf("PARAM(%s %s)\n", node->data.param.type, node->data.param.name);
            break;
        case NODE_PARAM_LIST:
            printf("PARAM_LIST\n");
            printAST(node->data.list.item, level + 1);
            printAST(node->data.list.next, level + 1);
            break;
        case NODE_ARG_LIST:
            printf("ARG_LIST\n");
            printAST(node->data.list.item, level + 1);
            printAST(node->data.list.next, level + 1);
            break;
        case NODE_FUNC_LIST:
            printf("FUNC_LIST\n");
            printAST(node->data.list.item, level + 1);
            printAST(node->data.list.next, level + 1);
            break;
        case NODE_BLOCK:
            printf("BLOCK\n");
            /* block uses stmt_list representation in parser; print it */
            printAST(node->data.stmtlist.stmt, level + 1);
            printAST(node->data.stmtlist.next, level + 1);
            break;
        default:
            printf("UNKNOWN NODE TYPE %d\n", node->type);
            break;
    }
}