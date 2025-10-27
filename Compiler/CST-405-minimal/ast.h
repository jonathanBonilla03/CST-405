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
    BINOP_EXP,   // ** (exponentiation)
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

/* === BASIC TYPE ENUM (store return/param types) === */
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_UNKNOWN
} TypeKind;

/* === NODE TYPES === */
typedef enum {
    NODE_NUM,
    NODE_FLOAT,
    NODE_VAR,
    NODE_BOOL,
    NODE_BINOP,
    NODE_UNOP,
    NODE_DECL,
    NODE_DECL_INIT,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_STMT_LIST,
    NODE_ARRAY_DECL,
    NODE_ARRAY_INIT_DECL,
    NODE_ARRAY_ASSIGN,
    NODE_ARRAY_ACCESS,
    NODE_INIT_LIST,
    NODE_RELOP,
    NODE_CAST,
    NODE_IF,
    NODE_FUNC_DECL,    // Function declaration
    NODE_FUNC_CALL,    // Function call (in expressions)
    NODE_PARAM,        // Parameter declaration
    NODE_PARAM_LIST,   // List of parameters
    NODE_ARG_LIST,     // List of arguments in call
    NODE_RETURN,       // Return statement
    NODE_FUNC_LIST,    // List of function declarations
    NODE_BLOCK         // Compound statement (for scoping)
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
        struct { char* targetType; struct ASTNode* expr; } cast;

        // --- Statements ---
        struct { char* var; struct ASTNode* value; } assign;
        struct { char* type; char* name; } decl;
        struct { char* type; char* name; struct ASTNode* value; } decl_init;
        struct ASTNode* expr;  // For print
        struct { struct ASTNode* stmt; struct ASTNode* next; } stmtlist;
        struct { struct ASTNode* cond; struct ASTNode* thenBr; struct ASTNode* elseBr; } ifstmt;

        // --- Arrays ---
        struct { char* type; char* name; int size; } array_decl;
        struct { char* type; char* name; int size; struct ASTNode* init_list; } array_init_decl;
        struct { char* name; struct ASTNode* index; struct ASTNode* value; } array_assign;
        struct { char* name; struct ASTNode* index; } array_access;
        struct { struct ASTNode* expr; struct ASTNode* next; } init_list;
        // Function declaration
        struct {
            char* returnType;        // "int" or "void"
            char* name;              // Function name
            struct ASTNode* params;  // Parameter list
            struct ASTNode* body;    // Function body (stmt list)
        } func_decl;

        // Function call
        struct {
            char* name;              // Function name
            struct ASTNode* args;    // Argument list
        } func_call;

        // Parameter
        struct {
            char* type;              // Parameter type
            char* name;              // Parameter name
        } param;

        // Parameter/Argument list
        struct {
            struct ASTNode* item;    // Current param/arg
            struct ASTNode* next;    // Rest of list
        } list;

        // Return statement
        struct ASTNode* return_expr; // Expression to return (NULL for void)

    } data;
} ASTNode;

/* === FUNCTION DECLARATIONS === */
ASTNode* createNum(int value);
ASTNode* createFloat(float value);
ASTNode* createVar(char* name);
ASTNode* createBool(bool value);
ASTNode* createBinOp(BinOpKind op, ASTNode* left, ASTNode* right);
ASTNode* createUnaryOp(UnOpKind op, ASTNode* expr);
ASTNode* createDecl(char* type, char* name);
ASTNode* createDeclInit(char* type, char* name, ASTNode* value);
ASTNode* createAssign(char* var, ASTNode* value);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);
ASTNode* createArrayDecl(char* type, char* name, int size);
ASTNode* createArrayInitDecl(char* type, char* name, int size, ASTNode* init_list);
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value);
ASTNode* createArrayAccess(char* name, ASTNode* index);
ASTNode* createInitList(ASTNode* expr, ASTNode* next);
ASTNode* createRelop(RelopKind op, ASTNode* left, ASTNode* right);
ASTNode* createCast(char* targetType, ASTNode* expr);
ASTNode* createIf(ASTNode* cond, ASTNode* thenBr, ASTNode* elseBr);
ASTNode* createFuncDecl(char* returnType, char* name,
                        ASTNode* params, ASTNode* body);
ASTNode* createFuncCall(char* name, ASTNode* args);
ASTNode* createParam(char* type, char* name);
ASTNode* createParamList(ASTNode* param, ASTNode* next);
ASTNode* createArgList(ASTNode* arg, ASTNode* next);
ASTNode* createReturn(ASTNode* expr);
ASTNode* createFuncList(ASTNode* func, ASTNode* next);
void printAST(ASTNode* node, int level);
void init_ast_memory();
void* ast_alloc(size_t size);
char* ast_strdup(const char* s);
void ast_reset();      /* reset pools for reuse (keeps memory, resets used counters) */
void ast_free_all();   /* free all pools */

#endif
