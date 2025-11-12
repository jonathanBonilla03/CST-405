# C-Minus Compiler: Complete Language Grammar & Architecture Guide

## Table of Contents
1. [Language Overview](#language-overview)
2. [Grammar Specification](#grammar-specification)
3. [Compiler Architecture](#compiler-architecture)
4. [File-by-File Analysis](#file-by-file-analysis)
5. [Compilation Pipeline](#compilation-pipeline)
6. [QtSPIM Compatibility](#qtspim-compatibility)

---

## Language Overview

**C-Minus** is an educational programming language designed to demonstrate compiler construction principles. It supports:

### Data Types
- `int` - Integer numbers
- `float` - Floating-point numbers  
- `bool` - Boolean values (`true`, `false`)
- `string` - String literals
- `void` - Function return type for no value

### Language Features
- ✅ Function declarations and calls
- ✅ Variable declarations and assignments
- ✅ Array declarations and access
- ✅ Arithmetic expressions (`+`, `-`, `*`, `/`, `%`, `**`)
- ✅ Relational operators (`<`, `<=`, `>`, `>=`, `==`, `!=`)
- ✅ Logical operators (`&&`, `||`, `!`)
- ✅ Control flow (`if`/`else` statements)
- ✅ Input/output operations (`input()`, `output()`)
- ✅ Type casting
- ✅ Return statements
- ✅ Block scoping

---

## Grammar Specification

### Complete EBNF Grammar

```ebnf
program     ::= func_list

func_list   ::= func_decl
            |   func_list func_decl

func_decl   ::= type ID '(' param_list ')' '{' stmt_list '}'
            |   type ID '(' ')' '{' stmt_list '}'
            |   type ID '(' VOID ')' '{' stmt_list '}'

type        ::= 'int' | 'float' | 'bool' | 'string' | 'void'

param_list  ::= param
            |   param_list ',' param

param       ::= type ID
            |   type ID '[' ']'

stmt_list   ::= stmt
            |   stmt_list stmt

stmt        ::= decl
            |   assign
            |   print_stmt
            |   if_stmt
            |   return_stmt
            |   expr ';'
            |   block

decl        ::= type ID ';'
            |   type ID '=' expr ';'
            |   type ID '[' NUM ']' ';'
            |   type ID '[' NUM ']' '=' '{' init_list '}' ';'

assign      ::= ID '=' expr ';'
            |   ID '[' expr ']' '=' expr ';'

print_stmt  ::= 'print' '(' expr ')' ';'

if_stmt     ::= 'if' '(' expr ')' stmt
            |   'if' '(' expr ')' stmt 'else' stmt

return_stmt ::= 'return' ';'
            |   'return' expr ';'

block       ::= '{' stmt_list '}'

expr        ::= NUM | FLOAT_LITERAL | BOOL_LITERAL | STRING_LITERAL
            |   ID
            |   ID '[' expr ']'
            |   ID '(' arg_list ')'
            |   ID '(' ')'
            |   expr binop expr
            |   unop expr
            |   '(' type ')' expr
            |   '(' expr ')'

binop       ::= '+' | '-' | '*' | '/' | '%' | '**'
            |   '<' | '<=' | '>' | '>=' | '==' | '!='
            |   '&&' | '||'

unop        ::= '-' | '!'

arg_list    ::= expr
            |   arg_list ',' expr

init_list   ::= expr
            |   init_list ',' expr
```

### Operator Precedence (Highest to Lowest)

1. `**` (Exponentiation) - Right associative
2. Unary `-`, `!`, Type casting - Right associative  
3. `*`, `/`, `%` - Left associative
4. `+`, `-` - Left associative
5. `<`, `<=`, `>`, `>=` - Left associative
6. `==`, `!=` - Left associative
7. `&&` - Left associative
8. `||` - Left associative
9. `=` (Assignment) - Right associative

---

## Compiler Architecture

### 5-Phase Compilation Pipeline

```
┌─────────────────────┐
│   PHASE 1: LEXER    │ → Tokenization
│    (scanner.l)      │
└─────────────────────┘
           ↓
┌─────────────────────┐
│   PHASE 2: PARSER   │ → Syntax Analysis + AST Building
│    (parser.y)       │
└─────────────────────┘
           ↓
┌─────────────────────┐
│ PHASE 3: TAC GEN    │ → Three-Address Code Generation
│      (tac.c)        │
└─────────────────────┘
           ↓
┌─────────────────────┐
│ PHASE 4: OPTIMIZER  │ → Constant Folding & Copy Propagation
│   (tac.c/codegen)   │
└─────────────────────┘
           ↓
┌─────────────────────┐
│ PHASE 5: CODEGEN    │ → MIPS Assembly Generation
│    (codegen.c)      │
└─────────────────────┘
```

---

## File-by-File Analysis

### Core Compiler Files

#### `main.c` - Driver Program
**Purpose**: Orchestrates the compilation process
- **Input handling**: Parses command line arguments (source file, output file)
- **Phase coordination**: Calls lexer → parser → TAC generation → optimization → code generation
- **Error management**: Handles compilation errors and provides user feedback
- **Output management**: Controls verbose output and debugging information

#### `scanner.l` - Lexical Analyzer
**Purpose**: Converts source code text into tokens
- **Token recognition**: Identifies keywords (`int`, `if`, `return`), operators (`+`, `==`), literals, identifiers
- **Whitespace handling**: Ignores spaces, tabs, newlines
- **Comment processing**: Handles single-line (`//`) and multi-line (`/* */`) comments
- **String processing**: Handles string literals with escape sequences
- **Line tracking**: Maintains line numbers for error reporting
- **Key tokens**: `NUM`, `ID`, `FLOAT_LITERAL`, `BOOL_LITERAL`, `STRING_LITERAL`, operators

#### `parser.y` - Syntax Analyzer
**Purpose**: Builds Abstract Syntax Tree (AST) from tokens
- **Grammar enforcement**: Ensures source follows C-Minus syntax rules
- **AST construction**: Creates hierarchical program representation
- **Error recovery**: Provides meaningful syntax error messages
- **Precedence handling**: Manages operator precedence and associativity
- **Semantic actions**: Calls AST creation functions during parsing
- **Conflict resolution**: Uses `%expect 1` to handle known shift/reduce conflicts

#### `ast.c` & `ast.h` - Abstract Syntax Tree
**Purpose**: Defines and manages program structure representation
- **Node types**: `NODE_NUM`, `NODE_VAR`, `NODE_BINOP`, `NODE_FUNC_CALL`, etc.
- **Tree construction**: Functions like `createBinOp()`, `createFuncCall()`, `createStmtList()`
- **Tree traversal**: Utilities for walking and manipulating AST
- **Memory management**: Handles dynamic allocation of AST nodes
- **Type information**: Stores data types and semantic information
- **Debugging support**: Pretty-printing functions for AST visualization

#### `symtab.c` & `symtab.h` - Symbol Table Management
**Purpose**: Tracks variable and function declarations with scoping
- **Scope management**: Handles nested scopes with `enterScope()` / `exitScope()`
- **Symbol storage**: Maintains variable names, types, offsets, array sizes
- **Function tracking**: Stores function signatures, parameter counts, return types
- **Offset calculation**: Manages stack frame layout for variables and parameters
- **Type checking**: Validates variable usage and function calls
- **Array support**: Tracks array declarations and bounds

```c
typedef struct {
    char* name;           // Symbol name
    char* type;           // Data type
    int offset;           // Stack offset from $fp
    int isFunction;       // Function vs variable flag
    int isArray;          // Array flag
    int arraySize;        // Array element count
    int paramCount;       // Function parameter count
    char** paramTypes;    // Parameter type list
} Symbol;
```

#### `tac.c` & `tac.h` - Three-Address Code Generation
**Purpose**: Converts AST to simplified intermediate representation
- **TAC instruction types**: `ASSIGN`, `BINOP`, `FUNC_CALL`, `RETURN`, `PARAM`, etc.
- **Temporary variables**: Generates `t0`, `t1`, `t2` for intermediate computations
- **Control flow**: Handles function calls, returns, conditional jumps
- **Optimization preparation**: Creates linear instruction sequence for optimization
- **Function separation**: Processes each function into separate TAC blocks
- **Expression flattening**: Converts complex expressions into simple assignments

**Example TAC Output:**
```
t0 = a + b
t1 = t0 * c  
result = t1
PARAM result
t2 = CALL print (1 params)
```

#### `codegen.c` & `codegen.h` - MIPS Assembly Generation
**Purpose**: Converts optimized TAC to executable MIPS assembly
- **Register allocation**: Uses `$t0-$t9` temporary registers with cycling
- **Function generation**: Creates proper MIPS function prologue/epilogue
- **Stack management**: Handles parameter passing and local variable storage
- **System calls**: Implements `input()` and `output()` using MIPS syscalls
- **Array handling**: Distinguishes local arrays vs array parameters
- **QtSPIM compatibility**: Generates assembly that runs correctly in QtSPIM

**Key Features:**
- **Function naming**: Adds `_func` suffix to avoid MIPS instruction conflicts
- **Parameter passing**: Uses `$a0-$a3` for function arguments
- **Array parameters**: Passes array addresses, not values
- **Return values**: Uses `$v0` for function returns
- **Frame pointer**: Uses `$fp` for stack frame management

### Support Files

#### `stringpool.c` & `stringpool.h` - String Literal Management
**Purpose**: Manages string constants in generated assembly
- **Deduplication**: Ensures identical strings use same memory location
- **Label generation**: Creates unique labels for string literals
- **Memory layout**: Places strings in `.data` section

#### `benchmark.c` - Performance Testing
**Purpose**: Measures compiler performance and optimization effectiveness
- **Compilation timing**: Measures time for each compilation phase
- **Optimization metrics**: Tracks optimization pass effectiveness
- **Memory usage**: Monitors compiler memory consumption

---

## Compilation Pipeline

### Phase 1: Lexical Analysis
```c
// Input: "int x = 5;"
// Output tokens: INT ID('x') '=' NUM(5) ';'
```

### Phase 2: Syntax Analysis + AST
```
    DECL_INIT
    /    |    \
  type  name  value
  "int"  "x"   NUM(5)
```

### Phase 3: TAC Generation
```
// TAC Instructions:
DECL int
t0 = 5
x = t0
```

### Phase 4: Optimization
```
// Optimized TAC:
DECL int  
x = 5     // Constant folding: eliminated temporary
```

### Phase 5: Code Generation
```mips
# MIPS Assembly:
addi $sp, $sp, -4    # allocate local x
li $t0, 5            # load immediate 5
sw $t0, -4($fp)      # store to x
```

---

## QtSPIM Compatibility

### Special Considerations
1. **Function naming**: User functions get `_func` suffix (e.g., `main` stays `main`, but `add` becomes `add_func`)
2. **System calls**: Uses MIPS syscalls for I/O operations
3. **Integer division**: Uses `div`/`mflo` instructions for proper division
4. **Array parameters**: Correctly passes array addresses and uses positive indexing
5. **Stack management**: Proper frame pointer usage for debugging

### I/O Implementation
```mips
# input() function
li $v0, 5      # read_int syscall
syscall
move $t0, $v0  # store result

# output(value) function  
move $a0, $t0  # move value to $a0
li $v0, 1      # print_int syscall
syscall
```

### Memory Layout
```
Stack Frame Layout:
$fp + 8: Return Address ($ra)
$fp + 4: Previous Frame Pointer  
$fp + 0: Current Frame Pointer
$fp - 4: First parameter
$fp - 8: Second parameter
...
$fp - X: Local variables
$fp - Y: Local arrays
```

---

## Recent Fixes & Improvements

### Array Parameter Handling (Latest Fix)
**Problem**: Array parameters were treated like local arrays, causing address errors
**Solution**: 
- **Argument passing**: Generate array address when passing arrays to functions
- **Parameter access**: Load array address from parameter and use positive indexing
- **Type distinction**: Use `isArrayVar()` to distinguish local arrays from array parameters

### Function Call Argument Processing  
**Problem**: Nested `ARG_LIST` nodes caused incorrect argument handling
**Solution**: Implemented recursive argument collection to properly traverse AST structure

### Register Allocation
**Enhancement**: Expanded temp register pool from `$t0-$t7` to `$t0-$t9` to reduce conflicts

---

This compiler demonstrates the complete compilation process from source code to executable assembly, with particular attention to educational clarity and QtSPIM compatibility. Each phase is clearly separated and well-documented, making it an excellent learning tool for compiler construction principles.