.data
newline: .asciiz "\n"

.text
.globl main

add_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t0, -4($fp)
    lw $t1, -8($fp)
    add $t2, $t0, $t1
    move $v0, $t2
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

subtract_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t3, -4($fp)
    lw $t4, -8($fp)
    sub $t5, $t3, $t4
    move $v0, $t5
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

multiply_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
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
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

divide_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t9, -4($fp)
    lw $t0, -8($fp)
    div $t9, $t0
    mflo $t1
    move $v0, $t1
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

complexExpression_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 3 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    addi $sp, $sp, -4   # alloc local temp (int)
    lw $t2, -4($fp)
    lw $t3, -8($fp)
    mul $t4, $t2, $t3
    lw $t5, -12($fp)
    add $t6, $t4, $t5
    lw $t7, -4($fp)
    lw $t8, -8($fp)
    div $t7, $t8
    mflo $t9
    sub $t0, $t6, $t9
    sw $t0, -16($fp)
    lw $t1, -16($fp)
    move $v0, $t1
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
    jr $ra

addAndMultiply_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 3 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    addi $sp, $sp, -4   # alloc local sum (int)
    lw $t2, -4($fp)
    lw $t3, -8($fp)
    move $a0, $t2
    move $a1, $t3
    jal add_func
    move $t4, $v0
    sw $t4, -16($fp)
    lw $t5, -16($fp)
    lw $t6, -12($fp)
    move $a0, $t5
    move $a1, $t6
    jal multiply_func
    move $t7, $v0
    move $v0, $t7
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
    jr $ra

nestedCalls_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 4 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    sw $a3, -16($fp)
    lw $t8, -4($fp)
    lw $t9, -8($fp)
    move $a0, $t8
    move $a1, $t9
    jal multiply_func
    move $t0, $v0
    lw $t1, -12($fp)
    lw $t2, -16($fp)
    move $a0, $t1
    move $a1, $t2
    jal subtract_func
    move $t3, $v0
    move $a0, $t0
    move $a1, $t3
    jal add_func
    move $t4, $v0
    move $v0, $t4
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
    jr $ra

average_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 3 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    addi $sp, $sp, -4   # alloc local total (int)
    addi $sp, $sp, -4   # alloc local result (int)
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    move $a0, $t5
    move $a1, $t6
    jal add_func
    move $t7, $v0
    lw $t8, -12($fp)
    move $a0, $t7
    move $a1, $t8
    jal add_func
    move $t9, $v0
    sw $t9, -16($fp)
    lw $t0, -16($fp)
    li $t1, 3
    move $a0, $t0
    move $a1, $t1
    jal divide_func
    move $t2, $v0
    sw $t2, -20($fp)
    lw $t3, -20($fp)
    move $v0, $t3
    addi $sp, $sp, 20   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 20   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

polynomial_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 4 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    sw $a3, -16($fp)
    addi $sp, $sp, -4   # alloc local xSquared (int)
    addi $sp, $sp, -4   # alloc local term1 (int)
    addi $sp, $sp, -4   # alloc local term2 (int)
    addi $sp, $sp, -4   # alloc local result (int)
    lw $t4, -8($fp)
    lw $t5, -8($fp)
    move $a0, $t4
    move $a1, $t5
    jal multiply_func
    move $t6, $v0
    sw $t6, -20($fp)
    lw $t7, -4($fp)
    lw $t8, -20($fp)
    move $a0, $t7
    move $a1, $t8
    jal multiply_func
    move $t9, $v0
    sw $t9, -24($fp)
    lw $t0, -12($fp)
    lw $t1, -8($fp)
    move $a0, $t0
    move $a1, $t1
    jal multiply_func
    move $t2, $v0
    sw $t2, -28($fp)
    lw $t3, -24($fp)
    lw $t4, -28($fp)
    move $a0, $t3
    move $a1, $t4
    jal add_func
    move $t5, $v0
    lw $t6, -16($fp)
    move $a0, $t5
    move $a1, $t6
    jal add_func
    move $t7, $v0
    sw $t7, -32($fp)
    lw $t8, -32($fp)
    move $v0, $t8
    addi $sp, $sp, 32   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 32   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

sumArray_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    addi $sp, $sp, -4   # alloc local total (int)
    li $t9, 0
    sll $t0, $t9, 2    # multiply index by 4
    lw $t1, -4($fp)     # load array address from parameter
    add $t0, $t1, $t0 # add scaled index to array address
    lw $t2, 0($t0)     # load from array[index]
    li $t3, 1
    sll $t4, $t3, 2    # multiply index by 4
    lw $t5, -4($fp)     # load array address from parameter
    add $t4, $t5, $t4 # add scaled index to array address
    lw $t6, 0($t4)     # load from array[index]
    add $t7, $t2, $t6
    li $t8, 2
    sll $t9, $t8, 2    # multiply index by 4
    lw $t0, -4($fp)     # load array address from parameter
    add $t9, $t0, $t9 # add scaled index to array address
    lw $t1, 0($t9)     # load from array[index]
    add $t2, $t7, $t1
    li $t3, 3
    sll $t4, $t3, 2    # multiply index by 4
    lw $t5, -4($fp)     # load array address from parameter
    add $t4, $t5, $t4 # add scaled index to array address
    lw $t6, 0($t4)     # load from array[index]
    add $t7, $t2, $t6
    li $t8, 4
    sll $t9, $t8, 2    # multiply index by 4
    lw $t0, -4($fp)     # load array address from parameter
    add $t9, $t0, $t9 # add scaled index to array address
    lw $t1, 0($t9)     # load from array[index]
    add $t2, $t7, $t1
    sw $t2, -12($fp)
    lw $t3, -12($fp)
    move $v0, $t3
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

arrayAverage_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    addi $sp, $sp, -4   # alloc local sum (int)
    lw $t4, -4($fp)
    lw $t5, -8($fp)
    move $a0, $t4
    move $a1, $t5
    jal sumArray_func
    move $t6, $v0
    sw $t6, -12($fp)
    lw $t7, -12($fp)
    lw $t8, -8($fp)
    move $a0, $t7
    move $a1, $t8
    jal divide_func
    move $t9, $v0
    move $v0, $t9
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

chainOperations_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -4   # alloc space for 1 parameters
    sw $a0, -4($fp)
    addi $sp, $sp, -4   # alloc local result (int)
    lw $t0, -4($fp)
    sw $t0, -8($fp)
    lw $t1, -8($fp)
    li $t2, 10
    move $a0, $t1
    move $a1, $t2
    jal add_func
    move $t3, $v0
    sw $t3, -8($fp)
    lw $t4, -8($fp)
    li $t5, 2
    move $a0, $t4
    move $a1, $t5
    jal multiply_func
    move $t6, $v0
    sw $t6, -8($fp)
    lw $t7, -8($fp)
    li $t8, 5
    move $a0, $t7
    move $a1, $t8
    jal subtract_func
    move $t9, $v0
    sw $t9, -8($fp)
    lw $t0, -8($fp)
    li $t1, 3
    move $a0, $t0
    move $a1, $t1
    jal divide_func
    move $t2, $v0
    sw $t2, -8($fp)
    lw $t3, -8($fp)
    move $v0, $t3
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

deepNesting_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 3 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    lw $t4, -4($fp)
    lw $t5, -8($fp)
    move $a0, $t4
    move $a1, $t5
    jal subtract_func
    move $t6, $v0
    lw $t7, -12($fp)
    move $a0, $t6
    move $a1, $t7
    jal add_func
    move $t8, $v0
    lw $t9, -4($fp)
    lw $t0, -12($fp)
    move $a0, $t9
    move $a1, $t0
    jal add_func
    move $t1, $v0
    lw $t2, -12($fp)
    lw $t3, -8($fp)
    move $a0, $t2
    move $a1, $t3
    jal subtract_func
    move $t4, $v0
    move $a0, $t1
    move $a1, $t4
    jal divide_func
    move $t5, $v0
    move $a0, $t8
    move $a1, $t5
    jal multiply_func
    move $t6, $v0
    move $v0, $t6
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

allOperators_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 4 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    sw $a3, -16($fp)
    addi $sp, $sp, -4   # alloc local part1 (int)
    addi $sp, $sp, -4   # alloc local part2 (int)
    addi $sp, $sp, -4   # alloc local result (int)
    lw $t7, -4($fp)
    lw $t8, -8($fp)
    mul $t9, $t7, $t8
    lw $t0, -12($fp)
    add $t1, $t9, $t0
    lw $t2, -16($fp)
    sub $t3, $t1, $t2
    sw $t3, -20($fp)
    lw $t4, -4($fp)
    lw $t5, -8($fp)
    div $t4, $t5
    mflo $t6
    lw $t7, -12($fp)
    sub $t8, $t6, $t7
    lw $t9, -16($fp)
    add $t0, $t8, $t9
    sw $t0, -24($fp)
    lw $t1, -20($fp)
    lw $t2, -24($fp)
    mul $t3, $t1, $t2
    sw $t3, -28($fp)
    lw $t4, -28($fp)
    move $v0, $t4
    addi $sp, $sp, 28   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 28   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

printCalculation_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    addi $sp, $sp, -4   # alloc local sum (int)
    addi $sp, $sp, -4   # alloc local product (int)
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    move $a0, $t5
    move $a1, $t6
    jal add_func
    move $t7, $v0
    sw $t7, -12($fp)
    lw $t8, -4($fp)
    lw $t9, -8($fp)
    move $a0, $t8
    move $a1, $t9
    jal multiply_func
    move $t0, $v0
    sw $t0, -16($fp)
    lw $t1, -12($fp)
    move $a0, $t1
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t2, 0     # output returns void (0)
    lw $t3, -16($fp)
    move $a0, $t3
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t4, 0     # output returns void (0)
    addi $sp, $sp, 16   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

printArraySum_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    addi $sp, $sp, -4   # alloc local total (int)
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    move $a0, $t5
    move $a1, $t6
    jal sumArray_func
    move $t7, $v0
    sw $t7, -12($fp)
    lw $t8, -12($fp)
    move $a0, $t8
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t9, 0     # output returns void (0)
    addi $sp, $sp, 12   # deallocate locals and params
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
    addi $sp, $sp, -4   # alloc local x (int)
    addi $sp, $sp, -4   # alloc local y (int)
    addi $sp, $sp, -4   # alloc local z (int)
    addi $sp, $sp, -4   # alloc local result (int)
    addi $sp, $sp, -20   # alloc array numbers[5] (int)
    addi $sp, $sp, -4   # alloc local arraySum (int)
    addi $sp, $sp, -4   # alloc local arrayAvg (int)
    addi $sp, $sp, -4   # alloc local poly (int)
    addi $sp, $sp, -4   # alloc local deep (int)
    addi $sp, $sp, -4   # alloc local chain (int)
    li $v0, 5      # syscall for read_int
    syscall
    move $t0, $v0
    sw $t0, -4($fp)
    li $v0, 5      # syscall for read_int
    syscall
    move $t1, $v0
    sw $t1, -8($fp)
    li $v0, 5      # syscall for read_int
    syscall
    move $t2, $v0
    sw $t2, -12($fp)
    lw $t3, -4($fp)
    lw $t4, -8($fp)
    move $a0, $t3
    move $a1, $t4
    jal add_func
    move $t5, $v0
    move $a0, $t5
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t6, 0     # output returns void (0)
    lw $t7, -4($fp)
    lw $t8, -8($fp)
    move $a0, $t7
    move $a1, $t8
    jal subtract_func
    move $t9, $v0
    move $a0, $t9
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t0, 0     # output returns void (0)
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    move $a0, $t1
    move $a1, $t2
    jal multiply_func
    move $t3, $v0
    move $a0, $t3
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t4, 0     # output returns void (0)
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    move $a0, $t5
    move $a1, $t6
    jal divide_func
    move $t7, $v0
    move $a0, $t7
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t8, 0     # output returns void (0)
    lw $t9, -4($fp)
    lw $t0, -8($fp)
    lw $t1, -12($fp)
    move $a0, $t9
    move $a1, $t0
    move $a2, $t1
    jal complexExpression_func
    move $t2, $v0
    sw $t2, -16($fp)
    lw $t3, -16($fp)
    move $a0, $t3
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t4, 0     # output returns void (0)
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    lw $t7, -12($fp)
    move $a0, $t5
    move $a1, $t6
    move $a2, $t7
    jal addAndMultiply_func
    move $t8, $v0
    sw $t8, -16($fp)
    lw $t9, -16($fp)
    move $a0, $t9
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t0, 0     # output returns void (0)
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    lw $t3, -12($fp)
    lw $t4, -4($fp)
    move $a0, $t1
    move $a1, $t2
    move $a2, $t3
    move $a3, $t4
    jal nestedCalls_func
    move $t5, $v0
    sw $t5, -16($fp)
    lw $t6, -16($fp)
    move $a0, $t6
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t7, 0     # output returns void (0)
    lw $t8, -4($fp)
    lw $t9, -8($fp)
    lw $t0, -12($fp)
    move $a0, $t8
    move $a1, $t9
    move $a2, $t0
    jal average_func
    move $t1, $v0
    sw $t1, -16($fp)
    lw $t2, -16($fp)
    move $a0, $t2
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t3, 0     # output returns void (0)
    lw $t4, -4($fp)
    lw $t5, -8($fp)
    move $a0, $t4
    move $a1, $t5
    jal add_func
    move $t6, $v0
    li $t7, 0
    sll $t8, $t7, 2    # multiply index by 4
    addi $t9, $fp, -20   # get array base address
    sub $t8, $t9, $t8 # subtract scaled index
    sw $t6, 0($t8)     # store to array[index]
    lw $t0, -4($fp)
    li $t1, 2
    move $a0, $t0
    move $a1, $t1
    jal multiply_func
    move $t2, $v0
    li $t3, 1
    sll $t4, $t3, 2    # multiply index by 4
    addi $t5, $fp, -20   # get array base address
    sub $t4, $t5, $t4 # subtract scaled index
    sw $t2, 0($t4)     # store to array[index]
    lw $t6, -8($fp)
    li $t7, 3
    move $a0, $t6
    move $a1, $t7
    jal subtract_func
    move $t8, $v0
    li $t9, 2
    sll $t0, $t9, 2    # multiply index by 4
    addi $t1, $fp, -20   # get array base address
    sub $t0, $t1, $t0 # subtract scaled index
    sw $t8, 0($t0)     # store to array[index]
    lw $t2, -12($fp)
    li $t3, 2
    move $a0, $t2
    move $a1, $t3
    jal divide_func
    move $t4, $v0
    li $t5, 3
    sll $t6, $t5, 2    # multiply index by 4
    addi $t7, $fp, -20   # get array base address
    sub $t6, $t7, $t6 # subtract scaled index
    sw $t4, 0($t6)     # store to array[index]
    lw $t8, -4($fp)
    lw $t9, -12($fp)
    move $a0, $t8
    move $a1, $t9
    jal add_func
    move $t0, $v0
    li $t1, 4
    sll $t2, $t1, 2    # multiply index by 4
    addi $t3, $fp, -20   # get array base address
    sub $t2, $t3, $t2 # subtract scaled index
    sw $t0, 0($t2)     # store to array[index]
    addi $t4, $fp, -20   # get address of array numbers
    li $t5, 5
    move $a0, $t4
    move $a1, $t5
    jal sumArray_func
    move $t6, $v0
    sw $t6, -40($fp)
    lw $t7, -40($fp)
    move $a0, $t7
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t8, 0     # output returns void (0)
    addi $t9, $fp, -20   # get address of array numbers
    li $t0, 5
    move $a0, $t9
    move $a1, $t0
    jal arrayAverage_func
    move $t1, $v0
    sw $t1, -44($fp)
    lw $t2, -44($fp)
    move $a0, $t2
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t3, 0     # output returns void (0)
    li $t4, 2
    lw $t5, -4($fp)
    li $t6, 3
    li $t7, 5
    move $a0, $t4
    move $a1, $t5
    move $a2, $t6
    move $a3, $t7
    jal polynomial_func
    move $t8, $v0
    sw $t8, -48($fp)
    lw $t9, -48($fp)
    move $a0, $t9
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t0, 0     # output returns void (0)
    lw $t1, -4($fp)
    move $a0, $t1
    jal chainOperations_func
    move $t2, $v0
    sw $t2, -56($fp)
    lw $t3, -56($fp)
    move $a0, $t3
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t4, 0     # output returns void (0)
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    lw $t7, -12($fp)
    move $a0, $t5
    move $a1, $t6
    move $a2, $t7
    jal deepNesting_func
    move $t8, $v0
    sw $t8, -52($fp)
    lw $t9, -52($fp)
    move $a0, $t9
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t0, 0     # output returns void (0)
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    lw $t3, -12($fp)
    li $t4, 10
    move $a0, $t1
    move $a1, $t2
    move $a2, $t3
    move $a3, $t4
    jal allOperators_func
    move $t5, $v0
    sw $t5, -16($fp)
    lw $t6, -16($fp)
    move $a0, $t6
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t7, 0     # output returns void (0)
    lw $t8, -4($fp)
    lw $t9, -8($fp)
    move $a0, $t8
    move $a1, $t9
    jal printCalculation_func
    move $t0, $v0
    addi $t1, $fp, -20   # get address of array numbers
    li $t2, 5
    move $a0, $t1
    move $a1, $t2
    jal printArraySum_func
    move $t3, $v0
    lw $t4, -4($fp)
    lw $t5, -8($fp)
    move $a0, $t4
    move $a1, $t5
    jal multiply_func
    move $t6, $v0
    lw $t7, -12($fp)
    lw $t8, -4($fp)
    move $a0, $t7
    move $a1, $t8
    jal subtract_func
    move $t9, $v0
    lw $t0, -8($fp)
    li $t1, 2
    move $a0, $t0
    move $a1, $t1
    jal add_func
    move $t2, $v0
    move $a0, $t9
    move $a1, $t2
    jal divide_func
    move $t3, $v0
    move $a0, $t6
    move $a1, $t3
    jal add_func
    move $t4, $v0
    move $a0, $t4
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t5, 0     # output returns void (0)
    lw $t6, -4($fp)
    li $t7, 5
    move $a0, $t6
    move $a1, $t7
    jal multiply_func
    move $t8, $v0
    lw $t9, -8($fp)
    li $t0, 10
    move $a0, $t9
    move $a1, $t0
    jal subtract_func
    move $t1, $v0
    move $a0, $t8
    move $a1, $t1
    jal add_func
    move $t2, $v0
    lw $t3, -12($fp)
    li $t4, 2
    move $a0, $t3
    move $a1, $t4
    jal divide_func
    move $t5, $v0
    add $t6, $t2, $t5
    sw $t6, -16($fp)
    lw $t7, -16($fp)
    move $a0, $t7
    li $v0, 1      # syscall for print_int
    syscall
    la $a0, newline
    li $v0, 4      # syscall for print_string
    syscall
    li $t8, 0     # output returns void (0)
    addi $sp, $sp, 56   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
