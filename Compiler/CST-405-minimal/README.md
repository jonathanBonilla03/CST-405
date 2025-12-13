# C-Minus Compiler - Educational Version

A minimal C compiler that demonstrates all phases of compilation from source code to MIPS assembly. This educational compiler supports a simplified subset of C syntax with educational features for learning compiler construction.

## Features

- **Multi-phase compilation**: Lexical analysis, parsing, semantic analysis, intermediate code generation, optimization, and MIPS code generation
- **Type system**: Support for `int`, `float`, `bool`, `char`, `string`, and `void` types
- **Arrays**: Static array declarations with initialization
- **Control flow**: `if`/`else` statements, `while` loops, function calls
- **Error handling**: Detailed syntax and semantic error reporting with helpful suggestions
- **Educational output**: Displays AST, TAC (Three-Address Code), optimizations, and symbol tables
- **Performance metrics**: Compilation timing for each phase

## Installation and Usage

### Prerequisites

- **GCC**: C compiler
- **Flex**: Lexical analyzer generator  
- **Bison**: Parser generator (YACC-compatible)
- **Make**: Build automation tool

#### Windows Installation:
```bash
# Using MinGW or MSYS2
pacman -S gcc flex bison make
```

#### Linux/Ubuntu Installation:
```bash
sudo apt update
sudo apt install gcc flex bison make
```

#### macOS Installation:
```bash
# Using Homebrew
brew install gcc flex bison make
```

### Building the Compiler

```bash
# Clone or navigate to the compiler directory
cd CST-405-minimal

# Build the compiler
make

# This creates the 'minicompiler' executable
```

### Usage

#### Basic Compilation
```bash
# Compile a C-Minus source file to MIPS assembly
./minicompiler source.cm output.s
```

#### Command Line Options
```bash
# Show help
./minicompiler --help

# Show only specific compilation phases
./minicompiler --ast source.cm output.s          # Show AST only
./minicompiler --tac source.cm output.s          # Show unoptimized TAC
./minicompiler --opt source.cm output.s          # Show optimized TAC  
./minicompiler --symbols source.cm output.s      # Show symbol table

# Minimal output (quiet mode)
./minicompiler --quiet source.cm output.s

# Default: shows all phases (AST + TAC + optimization + symbols + timing)
./minicompiler source.cm output.s
```

### Running MIPS Assembly

The compiler generates MIPS assembly compatible with simulators like:
- **MARS** (MIPS Assembler and Runtime Simulator)
- **QtSPIM** 
- **SPIM**

```bash
# Example with MARS
java -jar mars.jar output.s
```

### Example Usage

```bash
# Compile project4.cm and show all phases
./minicompiler project4.cm project4.s

# Compile with only timing information
./minicompiler --quiet project4.cm project4.s

# Show only the abstract syntax tree
./minicompiler --ast project4.cm project4.s
```

## C-Minus Language Grammar

The compiler supports the C-Minus language, a simplified subset of C designed for educational purposes.

### Complete Grammar (BNF)

```bnf
program     := func_list

func_list   := func_decl
             | func_list func_decl

func_decl   := type ID '(' param_list ')' '{' stmt_list '}'
             | type ID '(' ')' '{' stmt_list '}'
             | type ID '(' VOID ')' '{' stmt_list '}'

type        := INT | FLOAT | BOOL | CHAR | STRING | VOID
             | INT '[' ']' | FLOAT '[' ']' | BOOL '[' ']' 
             | CHAR '[' ']' | STRING '[' ']'

param_list  := param
             | param_list ',' param

param       := type ID
             | type ID '[' ']'

stmt_list   := stmt
             | stmt_list stmt

stmt        := decl | assign | print_stmt | if_stmt | while_stmt 
             | return_stmt | retry_stmt | break_stmt | expr ';'

decl        := type ID ';'
             | type ID '=' expr ';'
             | type ID '[' NUM ']' ';'
             | type ID '[' NUM ']' '=' '{' init_list '}' ';'

assign      := ID '=' expr ';'
             | ID '[' expr ']' '=' expr ';'

init_list   := expr
             | init_list ',' expr

if_stmt     := IF '(' expr ')' block
             | IF '(' expr ')' block ELSE block

while_stmt  := WHILE '(' expr ')' block

retry_stmt  := RETRY '(' NUM ')' block
             | RETRY '(' NUM ',' BACKOFF '=' NUM ')' block  
             | RETRY '(' NUM ')' block ONFAIL block
             | RETRY '(' NUM ',' BACKOFF '=' NUM ')' block ONFAIL block

print_stmt  := PRINT '(' expr ')' ';'

return_stmt := RETURN expr ';'
             | RETURN ';'

break_stmt  := BREAK ';'

block       := '{' stmt_list '}'
             | stmt

expr        := NUM | FLOAT_LITERAL | BOOL_LITERAL | CHAR_LITERAL 
             | STRING_LITERAL | ID | ID '[' expr ']'
             | '(' expr ')' | '(' type ')' expr
             | expr '+' expr | expr '-' expr | expr '*' expr 
             | expr '/' expr | expr '%' expr | expr '**' expr
             | expr AND expr | expr OR expr
             | expr LT expr | expr GT expr | expr LE expr 
             | expr GE expr | expr EQ expr | expr NE expr
             | '-' expr | NOT expr
             | ID '(' arg_list ')' | ID '(' ')'

arg_list    := expr
             | arg_list ',' expr
```

### Operator Precedence (Highest to Lowest)

1. `**` (exponentiation) - right associative
2. `-` (unary minus), `NOT`, `(type)` (cast) - right associative  
3. `*`, `/`, `%` - left associative
4. `+`, `-` (binary) - left associative
5. `<`, `<=`, `>`, `>=` - left associative
6. `==`, `!=` - left associative
7. `NOT` - right associative
8. `AND` - left associative
9. `OR` - left associative
10. `=` (assignment) - right associative

### Language Features

#### Data Types
```c
int x = 42;              // Integer
float pi = 3.14;         // Floating-point  
bool flag = true;        // Boolean (true/false)
char c = 'A';           // Character
string name = "hello";   // String literal
```

#### Arrays
```c
int numbers[5];                     // Array declaration
int data[3] = {1, 2, 3};           // Array with initialization
float values[4] = {1.1, 2.2, 3.3, 4.4};  // Float array
```

#### Control Structures
```c
// If-else statements  
if (x > 0) {
    print(x);
} else {
    print(-x);
}

// While loops
while (i <= 10) {
    sum = sum + i;
    i = i + 1;
}
```

#### Functions
```c
int add(int a, int b) {
    return a + b;
}

void printMessage() {
    print("Hello World");
}

// Function calls
int result = add(5, 3);
printMessage();
```

#### Expressions
```c
// Arithmetic
result = a + b * c - d / e;      // Operator precedence
power = base ** exponent;         // Exponentiation

// Logical  
flag = (x > 0) && (y < 10);      // AND operation
condition = (a == b) || (c != d); // OR operation

// Relational
bool test = (x <= y) && (y >= z);

// Type casting
float f = (float) intValue;
```

#### Educational Features
```c
// Retry blocks with exponential backoff
retry (3, backoff = 100) {
    // Attempt operation
} onfail {
    // Handle failure after all retries
}

// Break statements in loops
while (true) {
    if (condition) break;
}
```

## Error Handling

The compiler provides detailed error messages with suggested fixes:

### Syntax Errors
```
✗ Syntax Error at line 5: Missing semicolon
   Suggestion: Add ';' after statement on line 5
   Example: int x = 5;  // <- semicolon required
```

### Semantic Errors  
```
✗ Semantic Error at line 8: Undeclared variable 'count'
   Suggestion: Declare 'count' before using it
   Example: int count;  // Add this declaration
```

### Type Errors
```
✗ Type Error at line 12: Cannot assign float to int variable
   Suggestion: Use type casting or change variable type
   Example: int x = (int) floatValue;
```

## Output Phases

When run in default mode, the compiler shows:

1. **Lexical & Syntax Analysis**: Tokenization and parsing
2. **Abstract Syntax Tree**: Hierarchical program structure
3. **Three-Address Code**: Intermediate representation  
4. **Optimization**: Constant folding and copy propagation
5. **MIPS Code Generation**: Final assembly output
6. **Symbol Table**: Variables, functions, and scopes
7. **Timing Metrics**: Performance of each compilation phase

## Example Programs

### Simple Function Example
```c
int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

void main() {
    int result = factorial(5);
    print(result);
}
```

### Array Processing Example  
```c
int sumArray(int arr[], int size) {
    int sum = 0;
    int i = 0;
    while (i < size) {
        sum = sum + arr[i];
        i = i + 1;
    }
    return sum;
}

void main() {
    int numbers[4] = {10, 20, 30, 40};
    int total = sumArray(numbers, 4);
    print(total);  // Expected output: 100
}
```

## Troubleshooting

### Build Issues
```bash
# Clean and rebuild
make clean
make

# Check tool versions
gcc --version
flex --version  
bison --version
```

### Runtime Issues
- Ensure input files have `.cm` extension
- Check that output directory is writable
- Verify MIPS simulator compatibility

### Common Syntax Issues
- Missing semicolons after statements
- Unmatched braces `{}`  
- Undeclared variables
- Type mismatches in assignments
- Incorrect function parameter counts

## Educational Goals

This compiler demonstrates:
- **Lexical Analysis**: How source code becomes tokens
- **Syntax Analysis**: How grammar rules create parse trees  
- **Semantic Analysis**: How type checking and symbol tables work
- **Intermediate Code**: How high-level constructs become simple operations
- **Optimization**: How compilers improve code efficiency
- **Code Generation**: How portable code becomes machine-specific assembly

Perfect for computer science courses in:
- Compiler Construction
- Programming Language Theory  
- Computer Architecture
- Systems Programming

## License

Educational use only. See course materials for specific licensing terms.

That's it! No loops, no conditions, no functions - just the bare essentials.

## 🔧 Compiler Architecture

### Complete Compilation Pipeline

```
Source Code (.c)
      ↓
┌─────────────────┐
│ LEXICAL ANALYSIS│ → Tokens (INT, ID, NUM, +, =, etc.)
│   (scanner.l)   │
└─────────────────┘
      ↓
┌─────────────────┐
│ SYNTAX ANALYSIS │ → Abstract Syntax Tree (AST)
│   (parser.y)    │
└─────────────────┘
      ↓
┌─────────────────┐
│  AST BUILDING   │ → Hierarchical program structure
│    (ast.c)      │
└─────────────────┘
      ↓
┌─────────────────┐
│ SEMANTIC CHECK  │ → Symbol table, type checking
│   (symtab.c)    │
└─────────────────┘
      ↓
┌─────────────────┐
│ INTERMEDIATE    │ → Three-Address Code (TAC)
│ CODE (tac.c)    │
└─────────────────┘
      ↓
┌─────────────────┐
│  OPTIMIZATION   │ → Constant folding, propagation
│   (tac.c)       │
└─────────────────┘
      ↓
┌─────────────────┐
│ CODE GENERATION │ → MIPS Assembly (.s)
│  (codegen.c)    │
└─────────────────┘
      ↓
MIPS Assembly (.s)
```

## 💾 Understanding the Stack

### What is the Stack?

The stack is a **real region of memory** that every program uses for storing local variables. It's not just an educational concept - it's how actual computers work!

### Stack Memory Layout

```
High Memory Address (0xFFFFFFFF)
         ↑
    ┌──────────┐
    │          │
    │  UNUSED  │
    │          │
    ├──────────┤
    │          │
    │  STACK   │ ← Your variables live here!
    │    ↓     │   (grows downward)
    │          │
$sp →├──────────┤ ← Stack Pointer points to top
    │          │
    │   FREE   │
    │  SPACE   │
    │          │
    ├──────────┤
    │    ↑     │
    │   HEAP   │ ← Dynamic memory (malloc)
    │          │   (grows upward)
    ├──────────┤
    │  GLOBALS │ ← Global variables
    ├──────────┤
    │   CODE   │ ← Your program
    └──────────┘
         ↓
Low Memory Address (0x00000000)
```

### How Our Compiler Uses the Stack

For this program:
```c
int x;
int y; 
int z;
x = 10;
y = 20;
z = x + y;
```

The stack layout becomes:

```
        Stack Memory
    ┌─────────────────┐
    │      ...        │
    ├─────────────────┤ ← Old $sp (before allocation)
    │   z (offset 8)  │ → Will store 30
    ├─────────────────┤
    │   y (offset 4)  │ → Stores 20
    ├─────────────────┤
    │   x (offset 0)  │ → Stores 10
    └─────────────────┘ ← $sp after "addi $sp, $sp, -400"
```

### MIPS Instructions for Stack Operations

```mips
# Allocate space (at program start)
addi $sp, $sp, -400    # Move stack pointer down 400 bytes

# Store value 10 in variable x (offset 0)
li $t0, 10            # Load immediate 10 into register $t0
sw $t0, 0($sp)        # Store Word: memory[$sp + 0] = $t0

# Load variable x into register
lw $t1, 0($sp)        # Load Word: $t1 = memory[$sp + 0]

# Deallocate space (at program end)
addi $sp, $sp, 400    # Restore stack pointer
```

## 🚀 Build & Run

### Prerequisites
- `flex` (lexical analyzer generator)
- `bison` (parser generator)
- `gcc` (C compiler)
- MIPS simulator (MARS, SPIM, or QtSPIM) for running output

### Compilation
```bash
# Build the compiler
make

# Compile a source file
./minicompiler test.c output.s

# Clean build files
make clean
```

### Example Session
```bash
$ ./minicompiler test.c output.s

╔════════════════════════════════════════════════════════════╗
║          MINIMAL C COMPILER - EDUCATIONAL VERSION         ║
╚════════════════════════════════════════════════════════════╝

┌──────────────────────────────────────────────────────────┐
│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │
├──────────────────────────────────────────────────────────┤
│ • Reading source file: test.c
│ • Tokenizing input (scanner.l)
│ • Parsing grammar rules (parser.y)
│ • Building Abstract Syntax Tree
└──────────────────────────────────────────────────────────┘
✓ Parse successful - program is syntactically correct!

[... followed by AST, TAC, optimizations, and MIPS generation ...]
```

## 📝 Example Programs

### Simple Addition
```c
int a;
int b;
int sum;
a = 5;
b = 7;
sum = a + b;
print(sum);    // Output: 12
```

### Multiple Operations
```c
int x;
int y;
int z;
x = 10;
y = 20;
z = x + y;     // z = 30
print(z);
x = z + 5;     // x = 35
print(x);
```

## 🎓 Educational Features

### 1. **Extensive Comments**
Every source file contains detailed explanations of:
- What each component does
- Why design decisions were made
- How pieces fit together

### 2. **Visual Output**
The compiler shows:
- Beautiful ASCII boxes for each phase
- Line-by-line TAC with explanations
- Optimization steps clearly marked
- Success/error messages with helpful tips

### 3. **Phase Separation**
Each compilation phase is clearly separated:
- Lexical Analysis → Tokens
- Syntax Analysis → AST
- Intermediate Code → TAC
- Optimization → Improved TAC
- Code Generation → MIPS

### 4. **Real-World Concepts**
Students learn:
- How variables are stored in memory
- What three-address code looks like
- How optimizations work (constant folding)
- How high-level code becomes assembly

## 📁 File Structure

```
CST-405-minimal/
├── scanner.l      # Lexical analyzer (tokenizer)
├── parser.y       # Grammar rules and parser
├── ast.h/c        # Abstract Syntax Tree
├── symtab.h/c     # Symbol table for variables
├── tac.h/c        # Three-address code generation
├── codegen.h/c    # MIPS code generator
├── main.c         # Driver program
├── Makefile       # Build configuration
├── test.c         # Example program
└── README.md      # This file
```

## 🔍 Understanding the Output

### Three-Address Code (TAC)
```
1: DECL x          // Declare variable 'x'
2: x = 10          // Assign value to x
3: t0 = x + y      // Add: store result in t0
4: z = t0          // Assign temp result to z
5: PRINT z         // Output value of z
```

### Optimized TAC
```
1: DECL x
2: x = 10          // Constant value: 10
3: t0 = 30         // Folded: 10 + 20 = 30
4: z = 30          // Propagated constant
5: PRINT 30        // Direct constant print
```

## 🎯 Learning Objectives

Students will understand:
1. **Lexical Analysis**: How text becomes tokens
2. **Parsing**: How tokens become syntax trees
3. **Semantic Analysis**: How meaning is verified
4. **Intermediate Representations**: Platform-independent code
5. **Optimization**: Improving code efficiency
6. **Code Generation**: Creating real machine code
7. **Memory Management**: How variables are stored
8. **Compilation Pipeline**: How phases connect

## 🤝 Contributing

This is an educational project. Suggestions for making concepts clearer are welcome!

## 📜 License

Educational use - free to use and modify for teaching purposes.