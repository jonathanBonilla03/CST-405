.data
newline: .asciiz "\n"

.text
.globl main

factorial_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -4   # alloc space for 1 parameters
    sw $a0, -4($fp)
    .data
string_0: .asciiz "FACTORIAL_n:"
    .text
    la $t0, string_0
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t1, -4($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t2, -4($fp)
    li $t3, 1
    slt $t5, $t3, $t2
    xori $t4, $t5, 1
    beq $t4, $zero, Lelse_0
    .data
string_1: .asciiz "BASE_returning_1"
    .text
    la $t6, string_1
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 1
    move $v0, $t7
    addi $sp, $sp, 4   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    j Lend_1
Lelse_0:
    addi $sp, $sp, -4   # alloc local temp (int)
    lw $t8, -4($fp)
    li $t9, 1
    sub $t0, $t8, $t9
    move $a0, $t0
    jal factorial_func
    move $t1, $v0
    sw $t1, -8($fp)
    .data
string_2: .asciiz "AFTER_recursion_n_is:"
    .text
    la $t2, string_2
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t3, -4($fp)
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_3: .asciiz "temp_is:"
    .text
    la $t4, string_3
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t5, -8($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t6, -4($fp)
    lw $t7, -8($fp)
    mul $t8, $t6, $t7
    move $v0, $t8
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
Lend_1:
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

testWithoutArrays_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -4   # alloc local result (int)
    .data
string_4: .asciiz "TEST_WITHOUT_ARRAYS"
    .text
    la $t9, string_4
    move $a0, $t9
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 5
    move $a0, $t0
    jal factorial_func
    move $t1, $v0
    sw $t1, -4($fp)
    .data
string_5: .asciiz "RESULT:"
    .text
    la $t2, string_5
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t3, -4($fp)
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 4   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

testWithSmallArrays_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc array smallArray[3] (int)
    addi $sp, $sp, -4   # alloc local result (int)
    .data
string_6: .asciiz "TEST_WITH_SMALL_ARRAYS"
    .text
    la $t4, string_6
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t5, 1
    li $t6, 0
    sll $t7, $t6, 2    # multiply index by 4
    addi $t8, $fp, -4   # get array base address
    sub $t7, $t8, $t7 # subtract scaled index
    sw $t5, 0($t7)     # store to array[index]
    li $t9, 2
    li $t0, 1
    sll $t1, $t0, 2    # multiply index by 4
    addi $t2, $fp, -4   # get array base address
    sub $t1, $t2, $t1 # subtract scaled index
    sw $t9, 0($t1)     # store to array[index]
    li $t3, 3
    li $t4, 2
    sll $t5, $t4, 2    # multiply index by 4
    addi $t6, $fp, -4   # get array base address
    sub $t5, $t6, $t5 # subtract scaled index
    sw $t3, 0($t5)     # store to array[index]
    li $t7, 5
    move $a0, $t7
    jal factorial_func
    move $t8, $v0
    sw $t8, -16($fp)
    .data
string_7: .asciiz "RESULT:"
    .text
    la $t9, string_7
    move $a0, $t9
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t0, -16($fp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 16   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

testWithLargeArrays_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -80   # alloc array largeArray[20] (int)
    addi $sp, $sp, -40   # alloc array anotherArray[10] (int)
    addi $sp, $sp, -4   # alloc local result (int)
    addi $sp, $sp, -4   # alloc local i (int)
    .data
string_8: .asciiz "TEST_WITH_LARGE_ARRAYS"
    .text
    la $t1, string_8
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t2, 0
    sw $t2, -128($fp)
Lstart_2:
    lw $t3, -128($fp)
    li $t4, 20
    slt $t5, $t3, $t4
    beq $t5, $zero, Lend_3
    lw $t7, -128($fp)
    lw $t8, -128($fp)
    sll $t9, $t8, 2    # multiply index by 4
    addi $t0, $fp, -4   # get array base address
    sub $t9, $t0, $t9 # subtract scaled index
    sw $t7, 0($t9)     # store to array[index]
    lw $t1, -128($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sw $t3, -128($fp)
    j Lstart_2
Lend_3:
    li $t4, 0
    sw $t4, -128($fp)
Lstart_4:
    lw $t5, -128($fp)
    li $t6, 10
    slt $t7, $t5, $t6
    beq $t7, $zero, Lend_5
    lw $t9, -128($fp)
    li $t0, 2
    mul $t1, $t9, $t0
    lw $t2, -128($fp)
    sll $t3, $t2, 2    # multiply index by 4
    addi $t4, $fp, -84   # get array base address
    sub $t3, $t4, $t3 # subtract scaled index
    sw $t1, 0($t3)     # store to array[index]
    lw $t5, -128($fp)
    li $t6, 1
    add $t7, $t5, $t6
    sw $t7, -128($fp)
    j Lstart_4
Lend_5:
    li $t8, 5
    move $a0, $t8
    jal factorial_func
    move $t9, $v0
    sw $t9, -124($fp)
    .data
string_9: .asciiz "RESULT:"
    .text
    la $t0, string_9
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t1, -124($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 128   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    .data
string_10: .asciiz "MEMORY_CORRUPTION_DEBUG"
    .text
    la $t2, string_10
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    jal testWithoutArrays_func
    move $t3, $v0
    jal testWithSmallArrays_func
    move $t4, $v0
    jal testWithLargeArrays_func
    move $t5, $v0
    .data
string_11: .asciiz "DEBUG_COMPLETE"
    .text
    la $t6, string_11
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
