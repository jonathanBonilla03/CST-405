.data
newline: .asciiz "\n"

.text
.globl main

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    .data
string_0: .asciiz "=== C-Minus Retry Loop Demonstration ==="
    .text
    la $t0, string_0
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_1: .asciiz "Note: Each attempt includes a 5-second backoff delay"
    .text
    la $t1, string_1
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_2: .asciiz ""
    .text
    la $t2, string_2
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_3: .asciiz "=== Demo 1: Retry with Success Detection ==="
    .text
    la $t3, string_3
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_4: .asciiz "Simulating network connection attempts..."
    .text
    la $t4, string_4
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_5: .asciiz ""
    .text
    la $t5, string_5
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, -4   # alloc local connection_status (int)
    addi $sp, $sp, -4   # alloc local attempt (int)
    li $t6, 0
    sw $t6, -4($fp)
    li $t7, 0
    sw $t7, -8($fp)
    addi $sp, $sp, -4   # alloc retry counter
    li $t0, 0
    sw $t0, -12($fp)    # initialize counter = 0
retry_loop_0:
    lw $t0, -12($fp)    # load counter
    li $t1, 5          # load max attempts
    bge $t0, $t1, retry_fail_1    # if counter >= attempts, goto fail
    addi $t0, $t0, 1    # increment counter
    sw $t0, -12($fp)    # store counter
    lw $t8, -8($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -8($fp)
    .data
string_6: .asciiz ">>> Attempting connection - Try #"
    .text
    la $t1, string_6
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t2, -8($fp)
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_7: .asciiz "    Connecting to server..."
    .text
    la $t3, string_7
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t4, -8($fp)
    li $t5, 3
    slt $t7, $t4, $t5
    xori $t6, $t7, 1
    beq $t6, $zero, Lelse_3
    li $t8, 1
    sw $t8, -4($fp)
    .data
string_8: .asciiz "    SUCCESS: Connection established!"
    .text
    la $t9, string_8
    move $a0, $t9
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_9: .asciiz "    Breaking out of retry loop..."
    .text
    la $t0, string_9
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j retry_end_2    # break from retry loop
    j Lend_4
Lelse_3:
    .data
string_10: .asciiz "    FAILED: Connection refused"
    .text
    la $t1, string_10
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_11: .asciiz "    Waiting 5 seconds before retry..."
    .text
    la $t2, string_11
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_12: .asciiz ""
    .text
    la $t3, string_12
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lend_4:
    li $t2, 5000000          # load delay cycles
delay_loop_5:
    addi $t2, $t2, -1   # decrement delay counter
    bgt $t2, $zero, delay_loop_5  # continue delay if > 0
    j retry_loop_0
retry_fail_1:
    .data
string_13: .asciiz "ERROR: All connection attempts exhausted"
    .text
    la $t4, string_13
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_14: .asciiz "CRITICAL: Unable to establish connection"
    .text
    la $t5, string_14
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j retry_end_2
retry_end_2:
    addi $sp, $sp, 4    # deallocate retry counter
    .data
string_15: .asciiz ""
    .text
    la $t6, string_15
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_16: .asciiz "--- Demo 1 Results ---"
    .text
    la $t7, string_16
    move $a0, $t7
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_17: .asciiz "Final connection status:"
    .text
    la $t8, string_17
    move $a0, $t8
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t9, -4($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_18: .asciiz "Total attempts made:"
    .text
    la $t0, string_18
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t1, -8($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_19: .asciiz "========================"
    .text
    la $t2, string_19
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_20: .asciiz ""
    .text
    la $t3, string_20
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_21: .asciiz "=== Demo 2: Retry with Guaranteed Failure ==="
    .text
    la $t4, string_21
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_22: .asciiz "Simulating service calls that always fail..."
    .text
    la $t5, string_22
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_23: .asciiz ""
    .text
    la $t6, string_23
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, -4   # alloc local service_status (int)
    addi $sp, $sp, -4   # alloc local tries (int)
    li $t7, 0
    sw $t7, -12($fp)
    li $t8, 0
    sw $t8, -16($fp)
    addi $sp, $sp, -4   # alloc retry counter
    li $t0, 0
    sw $t0, -20($fp)    # initialize counter = 0
retry_loop_6:
    lw $t0, -20($fp)    # load counter
    li $t1, 3          # load max attempts
    bge $t0, $t1, retry_fail_7    # if counter >= attempts, goto fail
    addi $t0, $t0, 1    # increment counter
    sw $t0, -20($fp)    # store counter
    lw $t9, -16($fp)
    li $t0, 1
    add $t1, $t9, $t0
    sw $t1, -16($fp)
    .data
string_24: .asciiz ">>> Calling remote service - Try #"
    .text
    la $t2, string_24
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t3, -16($fp)
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_25: .asciiz "    Contacting API endpoint..."
    .text
    la $t4, string_25
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_26: .asciiz "    FAILED: Service unavailable (500 error)"
    .text
    la $t5, string_26
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t6, -16($fp)
    li $t7, 3
    slt $t8, $t6, $t7
    beq $t8, $zero, Lelse_9
    .data
string_27: .asciiz "    Waiting 5 seconds before retry..."
    .text
    la $t0, string_27
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_28: .asciiz ""
    .text
    la $t1, string_28
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_10
Lelse_9:
Lend_10:
    li $t2, 5000000          # load delay cycles
delay_loop_11:
    addi $t2, $t2, -1   # decrement delay counter
    bgt $t2, $zero, delay_loop_11  # continue delay if > 0
    j retry_loop_6
retry_fail_7:
    .data
string_29: .asciiz "    ERROR: Service permanently unavailable"
    .text
    la $t2, string_29
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_30: .asciiz "    RECOVERY: Switching to backup service"
    .text
    la $t3, string_30
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j retry_end_8
retry_end_8:
    addi $sp, $sp, 4    # deallocate retry counter
    .data
string_31: .asciiz ""
    .text
    la $t4, string_31
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_32: .asciiz "--- Demo 2 Results ---"
    .text
    la $t5, string_32
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_33: .asciiz "Service attempts made:"
    .text
    la $t6, string_33
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t7, -16($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_34: .asciiz "========================"
    .text
    la $t8, string_34
    move $a0, $t8
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_35: .asciiz ""
    .text
    la $t9, string_35
    move $a0, $t9
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_36: .asciiz "=== All Demonstrations Complete ==="
    .text
    la $t0, string_36
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_37: .asciiz "Both demos show retry loops with 5-second backoff delays"
    .text
    la $t1, string_37
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t2, 0
    move $v0, $t2
    addi $sp, $sp, 16   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 16   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
