# C-Minus Compiler: Development TODO List

## Overview
This document outlines the remaining development tasks and enhancements needed to complete the C-Minus compiler project. The compiler currently has a fully functional compilation pipeline that successfully generates QtSPIM-compatible MIPS assembly code.

---

## Priority Levels
- 🔴 **HIGH**: Critical missing features affecting core functionality
- 🟡 **MEDIUM**: Important improvements for production readiness  
- 🟢 **LOW**: Nice-to-have features and polish

---

## 🔴 HIGH PRIORITY Tasks

### 1. Optimization Engine Enhancement
**Current Status**: Basic optimization framework exists but limited implementation

**Required Work**:
- [ ] **Dead code elimination**: Remove unreachable code blocks and unused variables
- [ ] **Constant propagation**: Replace variables with constant values when possible
- [ ] **Copy propagation**: Eliminate redundant variable assignments
- [ ] **Loop optimization**: Implement loop unrolling and invariant code motion
- [ ] **Register allocation**: Improve temporary register usage and spill code
- [ ] **Peephole optimization**: Local instruction pattern improvements

**Files to Modify**: `tac.c`, `codegen.c`, potentially new `optimize.c`

### 2. Comprehensive Benchmarking Suite
**Current Status**: Basic `benchmark.c` exists but minimal functionality

**Required Work**:
- [ ] **Performance metrics**: Measure compilation time, memory usage, generated code size
- [ ] **Test suite integration**: Automated benchmarking of all test programs
- [ ] **Optimization comparison**: Before/after optimization performance analysis
- [ ] **Memory profiling**: Track compiler memory allocation and leaks
- [ ] **Code quality metrics**: Lines of generated assembly, register usage efficiency

**Files to Create/Modify**: `benchmark.c`, `test_performance.sh`, new benchmark test files

### 3. Unique Language Feature Implementation
**Current Status**: Standard C-Minus implementation, no distinctive features

**Potential Features to Add** (choose one):
- [ ] **First-class functions**: Function pointers and higher-order functions
- [ ] **Pattern matching**: Switch-like constructs with pattern destructuring
- [ ] **Coroutines**: Lightweight threading with yield/resume
- [ ] **Memory safety**: Automatic bounds checking for arrays
- [ ] **Type inference**: Automatic type deduction for variable declarations
- [ ] **Closures**: Lexical scoping with captured variables

**Impact**: Major parser, AST, and code generation changes required

---

## 🟡 MEDIUM PRIORITY Tasks

### 4. Error Handling & Diagnostics
**Current Status**: Basic error reporting, limited context

**Required Work**:
- [ ] **Enhanced error messages**: Include source location, context, and suggestions
- [ ] **Warning system**: Implement compiler warnings for suspicious code
- [ ] **Error recovery**: Continue parsing after syntax errors
- [ ] **Semantic error detection**: Type mismatches, undeclared variables, etc.
- [ ] **Line/column tracking**: Precise error location reporting

### 5. Advanced Language Features
**Current Status**: Basic C-Minus subset implemented

**Required Work**:
- [ ] **For loops**: Add `for (init; condition; increment)` syntax
- [ ] **While loops**: Add `while (condition) { body }` support
- [ ] **Switch statements**: Add `switch/case/default` constructs
- [ ] **Struct types**: User-defined data structures
- [ ] **Pointers**: Memory addresses and indirection
- [ ] **Dynamic memory**: `malloc`/`free` equivalent functions

### 6. Standard Library Expansion
**Current Status**: Only `input()` and `output()` functions

**Required Work**:
- [ ] **Math functions**: `abs()`, `sqrt()`, `pow()`, trigonometric functions
- [ ] **String operations**: `strlen()`, `strcpy()`, `strcmp()`, `strcat()`
- [ ] **File I/O**: `fopen()`, `fread()`, `fwrite()`, `fclose()`
- [ ] **Memory utilities**: `memcpy()`, `memset()`, `memcmp()`
- [ ] **Type conversion**: `itoa()`, `atoi()`, `ftoa()`, `atof()`

### 7. Code Generation Improvements
**Current Status**: Functional but not optimized

**Required Work**:
- [ ] **Better register allocation**: Graph coloring algorithm
- [ ] **Instruction scheduling**: Optimize instruction ordering
- [ ] **Branch optimization**: Reduce unnecessary jumps
- [ ] **Constant pool**: Optimize constant loading
- [ ] **Stack optimization**: Minimize stack frame size

---

## 🟢 LOW PRIORITY Tasks

### 8. Development Tools & Utilities
- [ ] **Pretty printer**: Format C-Minus source code
- [ ] **Syntax highlighter**: VS Code extension for C-Minus
- [ ] **Debugger integration**: Support for source-level debugging
- [ ] **IDE integration**: Language server protocol implementation
- [ ] **Documentation generator**: Extract comments into docs

### 9. Testing & Validation
- [ ] **Fuzzing**: Automated random input generation
- [ ] **Regression testing**: Comprehensive test suite expansion
- [ ] **Cross-platform testing**: Linux, macOS, Windows validation
- [ ] **MIPS simulator testing**: Test with other MIPS simulators
- [ ] **Performance regression**: Track performance over time

### 10. Code Quality & Maintenance
- [ ] **Code review**: Systematic review of all source files
- [ ] **Static analysis**: Use tools like `clang-static-analyzer`
- [ ] **Memory leak detection**: Valgrind integration
- [ ] **Coding standards**: Establish and enforce style guide
- [ ] **Documentation**: Inline code documentation and API docs

---

## Implementation Roadmap

### Phase 1: Foundation (Weeks 1-2)
1. Implement comprehensive optimization passes
2. Create robust benchmarking system
3. Design and begin unique language feature

### Phase 2: Enhancement (Weeks 3-4)  
1. Complete unique language feature implementation
2. Improve error handling and diagnostics
3. Add advanced language constructs (for/while loops)

### Phase 3: Polish (Weeks 5-6)
1. Expand standard library functions
2. Optimize code generation algorithms
3. Create development tools and utilities

### Phase 4: Validation (Week 7)
1. Comprehensive testing and validation
2. Performance analysis and optimization
3. Documentation completion and review

---

## Technical Notes

### Optimization Implementation Strategy
```c
// Suggested optimization pipeline
typedef struct OptPass {
    char* name;
    bool (*optimize)(TAC* tac);
    int priority;
} OptPass;

OptPass optimizations[] = {
    {"constant_folding", constantFold, 1},
    {"dead_code", deadCodeElim, 2}, 
    {"copy_prop", copyPropagate, 3},
    {"register_alloc", allocateRegs, 4}
};
```

### Benchmarking Metrics
- **Compilation time**: Total time from source to assembly
- **Code size**: Generated assembly instruction count
- **Register pressure**: Peak register usage
- **Optimization effectiveness**: Code improvement percentage
- **Memory usage**: Compiler peak memory consumption

### Testing Strategy
- **Unit tests**: Individual component testing
- **Integration tests**: Full compilation pipeline
- **Performance tests**: Benchmarking with various inputs
- **Regression tests**: Ensure existing functionality preserved
- **Stress tests**: Large input files and edge cases

---

## Files to Create/Modify

### New Files Needed
- `src/optimize.c` - Advanced optimization algorithms
- `tests/benchmark/` - Performance test suite
- `tests/regression/` - Automated regression tests
- `docs/API.md` - API documentation
- `tools/pretty_print.c` - Code formatting utility

### Existing Files to Enhance
- `tac.c` - Add optimization infrastructure
- `codegen.c` - Improve register allocation and instruction selection
- `symtab.c` - Add support for new language features
- `parser.y` - Extend grammar for new constructs
- `scanner.l` - Add new keywords and tokens
- `Makefile` - Update build process for new components

---

## Success Metrics

### Completion Criteria
- [ ] All optimization passes implemented and tested
- [ ] Benchmarking suite produces meaningful metrics
- [ ] Unique language feature fully functional
- [ ] Test suite passes 100% of cases
- [ ] Documentation complete and accurate
- [ ] Performance meets or exceeds baseline expectations

### Quality Gates
- **Code coverage**: Minimum 85% test coverage
- **Performance**: No more than 10% performance regression
- **Documentation**: All public APIs documented
- **Error handling**: Graceful failure for all error conditions
- **Memory safety**: No memory leaks detected by tools

---

This TODO list provides a clear roadmap for completing the C-Minus compiler development. Each task includes specific deliverables and success criteria to ensure systematic progress toward a production-ready compiler.