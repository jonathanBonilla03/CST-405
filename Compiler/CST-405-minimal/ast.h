#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdbool.h>

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

/* === ARITHMETIC & LOGICAL OPERATOR ENUMS === */
typedef enum {
    BINOP_ADD,   // +
    BINOP_SUB,   // -
    BINOP_MUL,   // *
    BINOP_DIV,   // /
    BINOP_MOD,   // %
    BINOP_AND,   // &&
    BINOP_OR     // ||
} BinOpKind;

typedef enum {
    UNOP_NEG,    // -x
    UNOP_NOT     // !x
} UnOpKind;

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
    NODE_BOOL,
    NODE_BINOP,
    NODE_UNOP,
    NODE_DECL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_STMT_LIST,
    NODE_ARRAY_DECL,
    NODE_ARRAY_ASSIGN,
    NODE_ARRAY_ACCESS,
    NODE_RELOP,
    NODE_IF,
} NodeType;

/* === AST NODE STRUCTURE === */
typedef struct ASTNode {
    NodeType type;
    union {
        // --- Literals & Variables ---
        int num;
        float decimal;
        char* name;
        bool boolean;

        // --- Expressions ---
        struct { BinOpKind op; struct ASTNode* left; struct ASTNode* right; } binop;
        struct { UnOpKind op; struct ASTNode* expr; } unop;
        struct { RelopKind op; struct ASTNode* left; struct ASTNode* right; } relop;

        // --- Statements ---
        struct { char* var; struct ASTNode* value; } assign;
        struct ASTNode* expr;  // For print
        struct { struct ASTNode* stmt; struct ASTNode* next; } stmtlist;
        struct { struct ASTNode* cond; struct ASTNode* thenBr; struct ASTNode* elseBr; } ifstmt;

        // --- Arrays ---
        struct { char* name; int size; } array_decl;
        struct { char* name; struct ASTNode* index; struct ASTNode* value; } array_assign;
        struct { char* name; struct ASTNode* index; } array_access;
    } data;
} ASTNode;

/* === FUNCTION DECLARATIONS === */
ASTNode* createNum(int value);
ASTNode* createFloat(float value);
ASTNode* createVar(char* name);
ASTNode* createBool(bool value);
ASTNode* createBinOp(BinOpKind op, ASTNode* left, ASTNode* right);
ASTNode* createUnaryOp(UnOpKind op, ASTNode* expr);
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
