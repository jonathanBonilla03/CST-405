#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST) */

#include <stddef.h>

#define POOL_SIZE 4096
#define MAX_POOLS 100

typedef struct MemPool {
    char* memory;
    size_t used;
    size_t size;
    struct MemPool* next;
} MemPool;

typedef struct {
    MemPool* current;
    MemPool* head;
    int total_allocations;
    int pool_count;
    size_t total_memory;
} ASTMemoryManager;

void init_ast_memory();
void* ast_alloc(size_t size);

/* NODE TYPES */
typedef enum {
    NODE_NUM,            /* integer literal */
    NODE_FLOAT,          /* float literal */
    NODE_VAR,            /* identifier use */
    NODE_BINOP,          /* binary operator (+,-,*,/,% ...) */
    NODE_UNOP,           /* unary operator (e.g., '-') */
    NODE_DECL,           /* int x; / float y; */
    NODE_ASSIGN,         /* x = expr; */
    NODE_PRINT,          /* print(expr); */
    NODE_STMT_LIST,      /* sequence of statements */
    NODE_ARRAY_DECL,     /* int a[N]; */
    NODE_ARRAY_ASSIGN,   /* a[i] = expr; */
    NODE_ARRAY_ACCESS    /* a[i] */
} NodeType;

/* AST NODE */
typedef struct ASTNode {
    NodeType type;
    union {
        /* literals */
        int   num;        /* NODE_NUM */
        float decimal;    /* NODE_FLOAT */

        /* names (var or decl) */
        char* name;       /* NODE_VAR, NODE_DECL */

        /* binary op */
        struct {
            char op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;

        /* unary op */
        struct {
            char op;
            struct ASTNode* expr;
        } unop;

        /* assignment */
        struct {
            char* var;               /* variable name (target) */
            struct ASTNode* value;   /* rhs expression */
        } assign;

        /* print */
        struct ASTNode* expr;        /* expression to print */

        /* statement list */
        struct {
            struct ASTNode* stmt;
            struct ASTNode* next;
        } stmtlist;

        /* array decl */
        struct {
            char* name;
            int   size;
        } array_decl;

        /* array assign */
        struct {
            char* name;
            struct ASTNode* index;
            struct ASTNode* value;
        } array_assign;

        /* array access */
        struct {
            char* name;
            struct ASTNode* index;
        } array_access;

    } data;
} ASTNode;

/* CONSTRUCTORS */
ASTNode* createNum(int value);
ASTNode* createFloat(float value);
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);
ASTNode* createUnaryOp(char op, ASTNode* expr);                 /* <-- added for unary minus */
ASTNode* createDecl(char* name);
ASTNode* createAssign(char* var, ASTNode* value);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);
ASTNode* createArrayDecl(char* name, int size);
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value);
ASTNode* createArrayAccess(char* name, ASTNode* index);

/* DEBUG / DISPLAY */
void printAST(ASTNode* node, int level);

#endif
