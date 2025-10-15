/* MINIMAL C COMPILER - EDUCATIONAL VERSION
 * Demonstrates all compilation phases for a simplified C subset
 * Supports: int/float variables, arrays, arithmetic, print, if/else
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
        printf("Usage: %s <input.c> <output.s>\n", argv[0]);
        printf("Example: ./minicompiler test.c output.s\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[1]);
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
        printf("✗ Parse failed - check syntax errors.\n");
        printf("Common issues:\n");
        printf("  • Missing semicolons\n");
        printf("  • Unclosed braces\n");
        printf("  • Invalid variable usage\n");
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
        printf("✗ Error: Failed to generate output file '%s'\n", argv[2]);
    }

    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║              COMPILATION COMPLETED SUCCESSFULLY            ║\n");
    printf("║       Run the output file in a MIPS simulator (e.g. MARS)  ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");

    fclose(yyin);
    // Remove this duplicate yyparse() call - it's causing the segfault
    // yyparse();
    return 0;
}

/* === OPTIONAL: Symbol Table Performance Benchmark === */
void test_symbol_table_performance() {
    BenchmarkResult* bench = start_benchmark();

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

    end_benchmark(bench, "Symbol Table Performance");
    printf("Collisions: %d\n", symtab.collisions);
    free(bench);
}
