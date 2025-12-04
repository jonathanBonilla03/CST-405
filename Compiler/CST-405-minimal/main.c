/* MINIMAL C COMPILER - EDUCATIONAL VERSION
 * Demonstrates all compilation phases for a simplified C subset
 * Supports: int/float variables, arrays, arithmetic, print, if/else, functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"
#include "tac.h"
#include "symtab.h"
#include "benchmark.c"

extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

/* Output control flags */
typedef struct {
    int show_ast;
    int show_unoptimized_tac;
    int show_optimized_tac;
    int show_symbols;
    int quiet_mode;
    int show_help;
} OutputFlags;

void print_usage(char* program_name) {
    printf("C-Minus Compiler - Educational Version\n");
    printf("Usage: %s [OPTIONS] <source.cm> <output.s>\n\n", program_name);
    printf("Arguments:\n");
    printf("  source.cm  - C-Minus source file to compile\n");
    printf("  output.s   - Output MIPS assembly file\n\n");
    printf("Options:\n");
    printf("  --ast      - Display Abstract Syntax Tree\n");
    printf("  --tac      - Display unoptimized Three-Address Code\n");
    printf("  --opt      - Display optimized Three-Address Code\n");
    printf("  --symbols  - Display Symbol Table information\n");
    printf("  --quiet    - Minimal output (only success/failure)\n");
    printf("  --help     - Display this help message\n\n");
    printf("Examples:\n");
    printf("  %s test.cm test.s                    # Default: show all phases\n", program_name);
    printf("  %s --ast --tac test.cm test.s        # Show only AST and unoptimized TAC\n", program_name);
    printf("  %s --opt test.cm test.s              # Show only optimized TAC\n", program_name);
    printf("  %s --quiet test.cm test.s            # Minimal output\n", program_name);
    printf("\nNote: Output file will be created/overwritten in current directory.\n");
    printf("      Compilation success/failure is always displayed.\n");
}

int parse_arguments(int argc, char* argv[], OutputFlags* flags, char** input_file, char** output_file) {
    // Initialize flags - default shows all phases
    flags->show_ast = 1;
    flags->show_unoptimized_tac = 1;
    flags->show_optimized_tac = 1;
    flags->show_symbols = 1;
    flags->quiet_mode = 0;
    flags->show_help = 0;
    
    *input_file = NULL;
    *output_file = NULL;
    
    int has_flags = 0;
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            flags->show_help = 1;
            return 1;
        } else if (strcmp(argv[i], "--ast") == 0) {
            if (!has_flags) {
                // First flag - reset all to 0, then enable specific ones
                flags->show_ast = 0;
                flags->show_unoptimized_tac = 0;
                flags->show_optimized_tac = 0;
                flags->show_symbols = 0;
                has_flags = 1;
            }
            flags->show_ast = 1;
        } else if (strcmp(argv[i], "--tac") == 0) {
            if (!has_flags) {
                flags->show_ast = 0;
                flags->show_unoptimized_tac = 0;
                flags->show_optimized_tac = 0;
                flags->show_symbols = 0;
                has_flags = 1;
            }
            flags->show_unoptimized_tac = 1;
        } else if (strcmp(argv[i], "--opt") == 0) {
            if (!has_flags) {
                flags->show_ast = 0;
                flags->show_unoptimized_tac = 0;
                flags->show_optimized_tac = 0;
                flags->show_symbols = 0;
                has_flags = 1;
            }
            flags->show_optimized_tac = 1;
        } else if (strcmp(argv[i], "--symbols") == 0) {
            if (!has_flags) {
                flags->show_ast = 0;
                flags->show_unoptimized_tac = 0;
                flags->show_optimized_tac = 0;
                flags->show_symbols = 0;
                has_flags = 1;
            }
            flags->show_symbols = 1;
        } else if (strcmp(argv[i], "--quiet") == 0) {
            flags->quiet_mode = 1;
            flags->show_ast = 0;
            flags->show_unoptimized_tac = 0;
            flags->show_optimized_tac = 0;
            flags->show_symbols = 0;
        } else if (argv[i][0] == '-') {
            printf("Unknown option: %s\n", argv[i]);
            printf("Use --help for usage information.\n");
            return -1;
        } else if (*input_file == NULL) {
            *input_file = argv[i];
        } else if (*output_file == NULL) {
            *output_file = argv[i];
        } else {
            printf("Too many file arguments provided.\n");
            printf("Use --help for usage information.\n");
            return -1;
        }
    }
    
    if (flags->show_help) {
        return 1;
    }
    
    if (*input_file == NULL || *output_file == NULL) {
        printf("Error: Both input and output files must be specified.\n");
        printf("Use --help for usage information.\n");
        return -1;
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    OutputFlags flags;
    char* input_file;
    char* output_file;
    
    init_ast_memory();

    int parse_result = parse_arguments(argc, argv, &flags, &input_file, &output_file);
    
    if (parse_result == 1) {
        print_usage(argv[0]);
        return 0;
    }
    
    if (parse_result == -1) {
        return 1;
    }

    yyin = fopen(input_file, "r");
    if (!yyin) {
        fprintf(stderr, "✗ File Error: Cannot open source file '%s'\n", input_file);
        fprintf(stderr, "Possible causes:\n");
        fprintf(stderr, "  • File does not exist in the current directory\n");
        fprintf(stderr, "  • Insufficient permissions to read the file\n");
        fprintf(stderr, "  • File path contains invalid characters\n");
        fprintf(stderr, "  • Current directory: Run 'dir' (Windows) or 'ls' (Linux) to see files\n");
        return 1;
    }

    if (!flags.quiet_mode) {
        printf("\n");
        printf("╔════════════════════════════════════════════════════════════╗\n");
        printf("║          MINIMAL C COMPILER - EDUCATIONAL VERSION          ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n\n");

        /* === PHASE 1: Lexical and Syntax Analysis === */
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ • Reading source file: %s\n", input_file);
        printf("│ • Tokenizing input (scanner.l)\n");
        printf("│ • Parsing grammar rules (parser.y)\n");
        printf("│ • Building Abstract Syntax Tree (AST)\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
    }

    if (yyparse() != 0) {
        printf("✗ Compilation failed during syntax analysis.\n");
        if (!flags.quiet_mode) {
            printf("Note: Specific error details are shown above with line numbers.\n");
            printf("\nQuick debugging tips:\n");
            printf("  • Check the line number mentioned in the error\n");
            printf("  • Look for missing semicolons after statements\n");
            printf("  • Ensure all braces { } are properly matched\n");
            printf("  • Verify variable names are declared before use\n");
            printf("  • Check function call syntax and parameter count\n");
        }
        fclose(yyin);
        return 1;
    }

    if (!flags.quiet_mode) {
        printf("✓ Parse successful - syntax is valid!\n\n");
    }

    /* === PHASE 2: AST Display === */
    if (flags.show_ast && !flags.quiet_mode) {
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 2: ABSTRACT SYNTAX TREE (AST)                      │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Displaying program hierarchy...                          │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        printAST(root, 0);
        printf("\n");
    }

    /* === PHASE 3: Intermediate Code (TAC) === */
    initTAC();
    generateTAC(root);
    
    if (flags.show_unoptimized_tac && !flags.quiet_mode) {
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 3: INTERMEDIATE CODE GENERATION (TAC)              │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Generating simplified three-address code instructions... │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        printTAC();
        printf("\n");
    }

    /* === PHASE 4: Optimization === */
    optimizeTAC();
    
    if (flags.show_optimized_tac && !flags.quiet_mode) {
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 4: OPTIMIZATION                                   │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Applying simple optimizations:                           │\n");
        printf("│ • Constant folding\n");
        printf("│ • Copy propagation\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        printOptimizedTAC();
        printf("\n");
    }

    /* === PHASE 5: MIPS Code Generation === */
    if (!flags.quiet_mode) {
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 5: MIPS CODE GENERATION                            │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Translating optimized TAC into MIPS assembly...           │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
    }

    generateMIPS(root, output_file);

    FILE* check = fopen(output_file, "r");
    if (check) {
        printf("✓ MIPS assembly generated: %s\n", output_file);
        fclose(check);
    } else {
        printf("✗ Code Generation Error: Failed to create output file '%s'\n", output_file);
        if (!flags.quiet_mode) {
            printf("Possible causes:\n");
            printf("  • Invalid output file path or directory\n");
            printf("  • Insufficient permissions to write in target directory\n");
            printf("  • Disk space full\n");
            printf("  • File may be open in another program\n");
            printf("  • Internal compiler error during MIPS generation\n");
        }
        return 1;
    }

    /* === Symbol Table Display === */
    if (flags.show_symbols && !flags.quiet_mode) {
        printf("\n┌──────────────────────────────────────────────────────────┐\n");
        printf("│ SYMBOL TABLE INFORMATION                                  │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Final symbol table state:                                │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        // Note: You'll need to implement printSymbolTable() in symtab.c if it doesn't exist
        // For now, just show that we would display it
        printf("Symbol table display would go here (implement printSymbolTable() function)\n");
        printf("\n");
    }

    if (!flags.quiet_mode) {
        printf("\n╔════════════════════════════════════════════════════════════╗\n");
        printf("║              COMPILATION COMPLETED SUCCESSFULLY            ║\n");
        printf("║       Run the output file in a MIPS simulator (e.g. MARS)  ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n");
    } else {
        printf("✓ Compilation completed successfully\n");
    }

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
