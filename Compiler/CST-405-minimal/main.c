/* MINIMAL C COMPILER - EDUCATIONAL VERSION
 * Demonstrates all compilation phases for a simplified C subset
 * Supports: int/float variables, arrays, arithmetic, print, if/else, functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"
#include "tac.h"
#include "symtab.h"
#include "benchmark.c"

extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

int main(int argc, char* argv[]) {
    init_ast_memory();

    if (argc != 3) {
        printf("C-Minus Compiler - Educational Version\n");
        printf("Usage: %s <source.cm> <output.s>\n\n", argv[0]);
        printf("Arguments:\n");
        printf("  source.cm  - C-Minus source file to compile\n");
        printf("  output.s   - Output MIPS assembly file\n\n");
        printf("Examples:\n");
        printf("  %s test.cm test.s\n", argv[0]);
        printf("  %s simple_retry.cm output.s\n", argv[0]);
        printf("  %s test_functions_only.cm functions.s\n\n", argv[0]);
        printf("Note: Output file will be created/overwritten in current directory.\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "✗ File Error: Cannot open source file '%s'\n", argv[1]);
        fprintf(stderr, "Possible causes:\n");
        fprintf(stderr, "  • File does not exist in the current directory\n");
        fprintf(stderr, "  • Insufficient permissions to read the file\n");
        fprintf(stderr, "  • File path contains invalid characters\n");
        fprintf(stderr, "  • Current directory: Run 'dir' (Windows) or 'ls' (Linux) to see files\n");
        return 1;
    }

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║          MINIMAL C COMPILER - EDUCATIONAL VERSION          ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");

    /* === PHASE 1: Lexical and Syntax Analysis === */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ • Reading source file: %s\n", argv[1]);
    printf("│ • Tokenizing input (scanner.l)\n");
    printf("│ • Parsing grammar rules (parser.y)\n");
    printf("│ • Building Abstract Syntax Tree (AST)\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    if (yyparse() != 0) {
        printf("✗ Compilation failed during syntax analysis.\n");
        printf("Note: Specific error details are shown above with line numbers.\n");
        printf("\nQuick debugging tips:\n");
        printf("  • Check the line number mentioned in the error\n");
        printf("  • Look for missing semicolons after statements\n");
        printf("  • Ensure all braces { } are properly matched\n");
        printf("  • Verify variable names are declared before use\n");
        printf("  • Check function call syntax and parameter count\n");
        fclose(yyin);
        return 1;
    }

    printf("✓ Parse successful - syntax is valid!\n\n");

    /* === PHASE 2: AST Display === */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 2: ABSTRACT SYNTAX TREE (AST)                      │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Displaying program hierarchy...                          │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    printAST(root, 0);
    printf("\n");

    /* === PHASE 3: Intermediate Code (TAC) === */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 3: INTERMEDIATE CODE GENERATION (TAC)              │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Generating simplified three-address code instructions... │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    initTAC();
    generateTAC(root);
    printTAC();
    printf("\n");

    /* === PHASE 4: Optimization === */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 4: OPTIMIZATION                                   │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Applying simple optimizations:                           │\n");
    printf("│ • Constant folding\n");
    printf("│ • Copy propagation\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    optimizeTAC();
    printOptimizedTAC();
    printf("\n");

    /* === PHASE 5: MIPS Code Generation === */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 5: MIPS CODE GENERATION                            │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Translating optimized TAC into MIPS assembly...           │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    generateMIPS(root, argv[2]);

    FILE* check = fopen(argv[2], "r");
    if (check) {
        printf("✓ MIPS assembly generated: %s\n", argv[2]);
        fclose(check);
    } else {
        printf("✗ Code Generation Error: Failed to create output file '%s'\n", argv[2]);
        printf("Possible causes:\n");
        printf("  • Invalid output file path or directory\n");
        printf("  • Insufficient permissions to write in target directory\n");
        printf("  • Disk space full\n");
        printf("  • File may be open in another program\n");
        printf("  • Internal compiler error during MIPS generation\n");
        return 1;
    }

    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║              COMPILATION COMPLETED SUCCESSFULLY            ║\n");
    printf("║       Run the output file in a MIPS simulator (e.g. MARS)  ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");

    fclose(yyin);
    return 0;
}

/* === OPTIONAL: Symbol Table Performance Benchmark === */
void test_symbol_table_performance() {
    CompilerBenchmark* bench = start_compiler_benchmark();

    for (int i = 0; i < 1000; i++) {
        char varname[20];
        sprintf(varname, "var_%d", i);
        addVar(varname, "int");
    }

    for (int i = 0; i < 10000; i++) {
        char varname[20];
        sprintf(varname, "var_%d", rand() % 1000);
        getVarOffset(varname);
    }

    end_compiler_benchmark(bench, "Symbol Table Performance");

    // Removed the nonexistent field
    // printf("Collisions: %d\n", symtab.collisions);

    free(bench);
}
