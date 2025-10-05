#ifndef AST_H
#define AST_H

#include <stddef.h>

/* === MEMORY POOL STRUCTURES === */
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

/* === RELATIONAL OPERATOR ENUM === */
typedef enum {
    RELOP_LT,   // <
    RELOP_GT,   // >
    RELOP_LE,   // <=
    RELOP_GE,   // >=
    RELOP_EQ,   // ==
    RELOP_NE    // !=
} RelopKind;

/* === NODE TYPES === */
typedef enum {
    NODE_NUM,
    NODE_FLOAT,
    NODE_VAR,
    NODE_BINOP,
    NODE_UNOP,
    NODE_DECL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_STMT_LIST,
    NODE_ARRAY_DECL,
    NODE_ARRAY_ASSIGN,
    NODE_ARRAY_ACCESS,
    NODE_RELOP,   // Relational expression (a < b, etc.)
    NODE_IF       // If / else statement
} NodeType;

/* === AST NODE STRUCTURE === */
typedef struct ASTNode {
    NodeType type;
    union {
        int num;
        float decimal;
        char* name;

        struct {
            char op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;

        struct {
            char op;
            struct ASTNode* expr;
        } unop;

        struct {
            char* var;
            struct ASTNode* value;
        } assign;

        struct ASTNode* expr;  // For print

        struct {
            struct ASTNode* stmt;
            struct ASTNode* next;
        } stmtlist;

        struct {
            char* name;
            int size;
        } array_decl;

        struct {
            char* name;
            struct ASTNode* index;
            struct ASTNode* value;
        } array_assign;

        struct {
            char* name;
            struct ASTNode* index;
        } array_access;

        struct {
            RelopKind op;
            struct ASTNode* left;
            struct ASTNode* right;
        } relop;

        struct {
            struct ASTNode* cond;
            struct ASTNode* thenBr;
            struct ASTNode* elseBr;
        } ifstmt;

    } data;
} ASTNode;

/* === FUNCTION DECLARATIONS === */
ASTNode* createNum(int value);
ASTNode* createFloat(float value);
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);
ASTNode* createUnaryOp(char op, ASTNode* expr);
ASTNode* createDecl(char* name);
ASTNode* createAssign(char* var, ASTNode* value);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);
ASTNode* createArrayDecl(char* name, int size);
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value);
ASTNode* createArrayAccess(char* name, ASTNode* index);
ASTNode* createRelop(RelopKind op, ASTNode* left, ASTNode* right);
ASTNode* createIf(ASTNode* cond, ASTNode* thenBr, ASTNode* elseBr);
void printAST(ASTNode* node, int level);

#endif
