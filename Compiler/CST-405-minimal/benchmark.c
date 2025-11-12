#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "ast.h"
#include "tac.h"

#ifdef __APPLE__
    #include <mach/mach.h>
    #include <mach/mach_time.h>
#else
    #include <unistd.h>
#endif

typedef struct {
    double cpu_time;
    double wall_time;
    long memory_usage;
    long peak_memory;
    int constants_folded;
    int dead_code_removed;
    int tac_instructions;
} CompilerBenchmark;

extern OptimizationStats opt_stats;
extern TACList tacList;

// Platform-specific memory measurement
long get_memory_usage() {
#ifdef __APPLE__
    struct task_basic_info info;
    mach_msg_type_number_t size = sizeof(info);
    kern_return_t kerr = task_info(mach_task_self(),
                                    TASK_BASIC_INFO,
                                    (task_info_t)&info, &size);
    if(kerr == KERN_SUCCESS) {
        return info.resident_size;
    }
#else
    FILE* file = fopen("/proc/self/status", "r");
    if (file) {
        char line[128];
        while (fgets(line, 128, file)) {
            if (strncmp(line, "VmRSS:", 6) == 0) {
                long memory;
                sscanf(line, "VmRSS: %ld", &memory);
                fclose(file);
                return memory * 1024; // Convert KB to bytes
            }
        }
        fclose(file);
    }
#endif
    return 0;
}

int count_tac_instructions() {
    TACInstr* curr = tacList.head;
    int count = 0;
    while (curr) {
        if (curr->op != TAC_NOP) {
            count++;
        }
        curr = curr->next;
    }
    return count;
}

CompilerBenchmark* start_compiler_benchmark() {
    CompilerBenchmark* result = malloc(sizeof(CompilerBenchmark));

    // Get initial CPU time
    clock_t start_cpu = clock();

    // Get initial wall time
    struct timeval start_wall;
    gettimeofday(&start_wall, NULL);

    // Store in result (temporarily using these fields)
    result->cpu_time = (double)start_cpu;
    result->wall_time = start_wall.tv_sec + start_wall.tv_usec / 1000000.0;
    result->memory_usage = get_memory_usage();
    
    // Initialize optimization stats
    result->constants_folded = 0;
    result->dead_code_removed = 0;
    result->tac_instructions = 0;

    return result;
}

void end_compiler_benchmark(CompilerBenchmark* result, const char* phase) {
    // Get final times
    clock_t end_cpu = clock();
    struct timeval end_wall;
    gettimeofday(&end_wall, NULL);

    // Calculate elapsed times
    double start_cpu = result->cpu_time;
    result->cpu_time = ((double)(end_cpu - start_cpu)) / CLOCKS_PER_SEC;

    double start_wall = result->wall_time;
    double end_wall_time = end_wall.tv_sec + end_wall.tv_usec / 1000000.0;
    result->wall_time = end_wall_time - start_wall;

    // Get final memory
    long final_memory = get_memory_usage();
    result->peak_memory = final_memory - result->memory_usage;
    
    // Capture optimization stats
    result->constants_folded = opt_stats.constant_folded;
    result->dead_code_removed = opt_stats.dead_code_removed;
    result->tac_instructions = count_tac_instructions();

    // Print results
    printf("\n=== %s Performance ===\n", phase);
    printf("CPU Time: %.6f seconds\n", result->cpu_time);
    printf("Wall Time: %.6f seconds\n", result->wall_time);
    printf("Memory Delta: %.2f KB\n", result->peak_memory / 1024.0);
    printf("TAC Instructions: %d\n", result->tac_instructions);
    printf("Constants Folded: %d\n", result->constants_folded);
    printf("Dead Code Removed: %d\n", result->dead_code_removed);
    
    if (result->constants_folded > 0 || result->dead_code_removed > 0) {
        double optimization_ratio = ((double)(result->constants_folded + result->dead_code_removed) / result->tac_instructions) * 100.0;
        printf("Optimization Efficiency: %.2f%%\n", optimization_ratio);
    }
}

void compare_optimization_performance(CompilerBenchmark* before, CompilerBenchmark* after) {
    printf("\n=== Optimization Comparison ===\n");
    printf("CPU Time Improvement: %.6f -> %.6f seconds (%.2f%% %s)\n", 
           before->cpu_time, after->cpu_time,
           fabs((after->cpu_time - before->cpu_time) / before->cpu_time) * 100.0,
           after->cpu_time < before->cpu_time ? "faster" : "slower");
           
    printf("Wall Time Improvement: %.6f -> %.6f seconds (%.2f%% %s)\n", 
           before->wall_time, after->wall_time,
           fabs((after->wall_time - before->wall_time) / before->wall_time) * 100.0,
           after->wall_time < before->wall_time ? "faster" : "slower");
           
    printf("TAC Instructions: %d -> %d (reduced by %d)\n",
           before->tac_instructions, after->tac_instructions,
           before->tac_instructions - after->tac_instructions);
           
    if (after->constants_folded > 0 || after->dead_code_removed > 0) {
        printf("Optimizations Applied: %d constants folded, %d dead code removed\n",
               after->constants_folded, after->dead_code_removed);
    }
}