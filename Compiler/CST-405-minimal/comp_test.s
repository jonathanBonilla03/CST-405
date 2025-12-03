.data
newline: .asciiz "\n"

.text
.globl main

testArithmetic_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -28   # alloc space for 2 params + 5 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t0, -4($fp)
    lw $t1, -8($fp)
    add $t2, $t0, $t1
    sw $t2, -12($fp)
    lw $t3, -4($fp)
    lw $t4, -8($fp)
    sub $t5, $t3, $t4
    sw $t5, -16($fp)
    lw $t6, -4($fp)
    lw $t7, -8($fp)
    mul $t8, $t6, $t7
    sw $t8, -20($fp)
    lw $t9, -4($fp)
    lw $t0, -8($fp)
    div $t9, $t0
    mflo $t1
    sw $t1, -24($fp)
    li $t2, 2
    li $t3, 3
    li $t4, 4
    mul $t5, $t3, $t4
    add $t6, $t2, $t5
    sw $t6, -28($fp)
    li $t7, 2
    li $t8, 3
    add $t9, $t7, $t8
    li $t0, 4
    mul $t1, $t9, $t0
    sw $t1, -28($fp)
    lw $t2, -4($fp)
    lw $t3, -8($fp)
    mul $t4, $t2, $t3
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    div $t5, $t6
    mflo $t7
    add $t8, $t4, $t7
    lw $t9, -4($fp)
    sub $t0, $t8, $t9
    lw $t1, -8($fp)
    add $t2, $t0, $t1
    sw $t2, -28($fp)
    lw $t3, -12($fp)
    lw $t4, -16($fp)
    add $t5, $t3, $t4
    lw $t6, -20($fp)
    add $t7, $t5, $t6
    lw $t8, -24($fp)
    mtc1 $t7, $f0
    mtc1 $t8, $f2
    add.s $f4, $f0, $f2
    mfc1 $t9, $f4
    move $v0, $t9
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

testRelational_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 2 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t0, 0
    sw $t0, -12($fp)
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    slt $t3, $t1, $t2
    beq $t3, $zero, Lelse_0
    lw $t5, -12($fp)
    li $t6, 1
    add $t7, $t5, $t6
    sw $t7, -12($fp)
    j Lend_1
Lelse_0:
Lend_1:
    lw $t8, -4($fp)
    lw $t9, -8($fp)
    slt $t1, $t9, $t8
    xori $t0, $t1, 1
    beq $t0, $zero, Lelse_2
    lw $t2, -12($fp)
    li $t3, 10
    add $t4, $t2, $t3
    sw $t4, -12($fp)
    j Lend_3
Lelse_2:
Lend_3:
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    slt $t7, $t6, $t5
    beq $t7, $zero, Lelse_4
    lw $t9, -12($fp)
    li $t0, 100
    add $t1, $t9, $t0
    sw $t1, -12($fp)
    j Lend_5
Lelse_4:
Lend_5:
    lw $t2, -4($fp)
    lw $t3, -8($fp)
    slt $t5, $t2, $t3
    xori $t4, $t5, 1
    beq $t4, $zero, Lelse_6
    lw $t6, -12($fp)
    li $t7, 1000
    add $t8, $t6, $t7
    sw $t8, -12($fp)
    j Lend_7
Lelse_6:
Lend_7:
    lw $t9, -4($fp)
    lw $t0, -8($fp)
    subu $t2, $t9, $t0
    sltiu $t1, $t2, 1
    beq $t1, $zero, Lelse_8
    lw $t3, -12($fp)
    li $t4, 10000
    add $t5, $t3, $t4
    sw $t5, -12($fp)
    j Lend_9
Lelse_8:
Lend_9:
    lw $t6, -4($fp)
    lw $t7, -8($fp)
    subu $t9, $t6, $t7
    sltu  $t8, $zero, $t9
    beq $t8, $zero, Lelse_10
    lw $t0, -12($fp)
    li $t1, 100000
    add $t2, $t0, $t1
    sw $t2, -12($fp)
    j Lend_11
Lelse_10:
Lend_11:
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

testIfElse_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 1 params + 1 locals
    sw $a0, -4($fp)
    lw $t4, -4($fp)
    li $t5, 0
    slt $t6, $t5, $t4
    beq $t6, $zero, Lelse_12
    li $t8, 1
    sw $t8, -8($fp)
    j Lend_13
Lelse_12:
Lend_13:
    lw $t9, -4($fp)
    li $t0, 0
    slt $t1, $t9, $t0
    beq $t1, $zero, Lelse_14
    li $t3, 1
    sub $t4, $zero, $t3
    sw $t4, -8($fp)
    j Lend_15
Lelse_14:
    li $t5, 0
    sw $t5, -8($fp)
Lend_15:
    lw $t6, -4($fp)
    li $t7, 100
    slt $t8, $t7, $t6
    beq $t8, $zero, Lelse_16
    lw $t0, -4($fp)
    li $t1, 200
    slt $t2, $t1, $t0
    beq $t2, $zero, Lelse_18
    li $t4, 200
    sw $t4, -8($fp)
    j Lend_19
Lelse_18:
    li $t5, 100
    sw $t5, -8($fp)
Lend_19:
    j Lend_17
Lelse_16:
    lw $t6, -4($fp)
    li $t7, 50
    slt $t8, $t7, $t6
    beq $t8, $zero, Lelse_20
    li $t0, 50
    sw $t0, -8($fp)
    j Lend_21
Lelse_20:
    li $t1, 0
    sw $t1, -8($fp)
Lend_21:
Lend_17:
    lw $t2, -8($fp)
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

testWhileLoop_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 1 params + 2 locals
    sw $a0, -4($fp)
    li $t3, 0
    sw $t3, -8($fp)
    li $t4, 1
    sw $t4, -12($fp)
Lstart_22:
    lw $t5, -12($fp)
    lw $t6, -4($fp)
    slt $t8, $t6, $t5
    xori $t7, $t8, 1
    beq $t7, $zero, Lend_23
    lw $t9, -8($fp)
    lw $t0, -12($fp)
    add $t1, $t9, $t0
    sw $t1, -8($fp)
    lw $t2, -12($fp)
    li $t3, 1
    add $t4, $t2, $t3
    sw $t4, -12($fp)
    j Lstart_22
Lend_23:
    lw $t5, -8($fp)
    move $v0, $t5
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

testNestedLoops_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -20   # alloc space for 2 params + 3 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t6, 0
    sw $t6, -12($fp)
    li $t7, 0
    sw $t7, -16($fp)
Lstart_24:
    lw $t8, -16($fp)
    lw $t9, -4($fp)
    slt $t0, $t8, $t9
    beq $t0, $zero, Lend_25
    li $t2, 0
    sw $t2, -20($fp)
Lstart_26:
    lw $t3, -20($fp)
    lw $t4, -8($fp)
    slt $t5, $t3, $t4
    beq $t5, $zero, Lend_27
    lw $t7, -12($fp)
    li $t8, 1
    add $t9, $t7, $t8
    sw $t9, -12($fp)
    lw $t0, -20($fp)
    li $t1, 1
    add $t2, $t0, $t1
    sw $t2, -20($fp)
    j Lstart_26
Lend_27:
    lw $t3, -16($fp)
    li $t4, 1
    add $t5, $t3, $t4
    sw $t5, -16($fp)
    j Lstart_24
Lend_25:
    lw $t6, -12($fp)
    move $v0, $t6
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

testArrayOperations_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 2 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t7, 0
    sw $t7, -12($fp)
Lstart_28:
    lw $t8, -12($fp)
    lw $t9, -8($fp)
    slt $t0, $t8, $t9
    beq $t0, $zero, Lend_29
    lw $t2, -12($fp)
    li $t3, 2
    mul $t4, $t2, $t3
    lw $t5, -12($fp)
    sll $t6, $t5, 2    # multiply index by 4
    lw $t7, -4($fp)     # load array address from parameter
    sub $t6, $t7, $t6 # subtract scaled index for consistency
    sw $t4, 0($t6)     # store to array[index]
    lw $t8, -12($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -12($fp)
    j Lstart_28
Lend_29:
    li $t1, 0
    sw $t1, -12($fp)
Lstart_30:
    lw $t2, -12($fp)
    lw $t3, -8($fp)
    slt $t4, $t2, $t3
    beq $t4, $zero, Lend_31
    lw $t6, -12($fp)
    sll $t7, $t6, 2    # multiply index by 4
    lw $t8, -4($fp)     # load array address from parameter
    sub $t7, $t8, $t7 # subtract scaled index for consistency
    lw $t9, 0($t7)     # load from array[index]
    li $t0, 1
    add $t1, $t9, $t0
    lw $t2, -12($fp)
    sll $t3, $t2, 2    # multiply index by 4
    lw $t4, -4($fp)     # load array address from parameter
    sub $t3, $t4, $t3 # subtract scaled index for consistency
    sw $t1, 0($t3)     # store to array[index]
    lw $t5, -12($fp)
    li $t6, 1
    add $t7, $t5, $t6
    sw $t7, -12($fp)
    j Lstart_30
Lend_31:
    addi $sp, $sp, 12   # deallocate locals and params
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
    addi $sp, $sp, -16   # alloc space for 2 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t8, 0
    sw $t8, -12($fp)
    li $t9, 0
    sw $t9, -16($fp)
Lstart_32:
    lw $t0, -16($fp)
    lw $t1, -8($fp)
    slt $t2, $t0, $t1
    beq $t2, $zero, Lend_33
    lw $t4, -12($fp)
    lw $t5, -16($fp)
    sll $t6, $t5, 2    # multiply index by 4
    lw $t7, -4($fp)     # load array address from parameter
    sub $t6, $t7, $t6 # subtract scaled index for consistency
    lw $t8, 0($t6)     # load from array[index]
    add $t9, $t4, $t8
    sw $t9, -12($fp)
    lw $t0, -16($fp)
    li $t1, 1
    add $t2, $t0, $t1
    sw $t2, -16($fp)
    j Lstart_32
Lend_33:
    lw $t3, -12($fp)
    move $v0, $t3
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

factorial_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 1 params + 1 locals
    sw $a0, -4($fp)
    lw $t4, -4($fp)
    li $t5, 1
    slt $t7, $t5, $t4
    xori $t6, $t7, 1
    beq $t6, $zero, Lelse_34
    li $t8, 1
    sw $t8, -8($fp)
    j Lend_35
Lelse_34:
    lw $t9, -4($fp)
    addi $sp, $sp, -4   # preserve left operand
    sw $t9, 0($sp)     # save left operand
    lw $t0, -4($fp)
    li $t1, 1
    sub $t2, $t0, $t1
    move $a0, $t2
    jal factorial_func
    move $t3, $v0
    lw $t4, 0($sp)     # restore left operand
    addi $sp, $sp, 4    # deallocate preservation space
    mul $t5, $t4, $t3
    sw $t5, -8($fp)
Lend_35:
    lw $t6, -8($fp)
    move $v0, $t6
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

fibonacci_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 1 params + 1 locals
    sw $a0, -4($fp)
    lw $t7, -4($fp)
    li $t8, 1
    slt $t0, $t8, $t7
    xori $t9, $t0, 1
    beq $t9, $zero, Lelse_36
    lw $t1, -4($fp)
    sw $t1, -8($fp)
    j Lend_37
Lelse_36:
    lw $t2, -4($fp)
    li $t3, 1
    sub $t4, $t2, $t3
    move $a0, $t4
    jal fibonacci_func
    move $t5, $v0
    addi $sp, $sp, -4   # preserve left operand
    sw $t5, 0($sp)     # save left operand
    lw $t6, -4($fp)
    li $t7, 2
    sub $t8, $t6, $t7
    move $a0, $t8
    jal fibonacci_func
    move $t9, $v0
    lw $t0, 0($sp)     # restore left operand
    addi $sp, $sp, 4    # deallocate preservation space
    add $t1, $t0, $t9
    sw $t1, -8($fp)
Lend_37:
    lw $t2, -8($fp)
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

power_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 2 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t3, -8($fp)
    li $t4, 0
    subu $t6, $t3, $t4
    sltiu $t5, $t6, 1
    beq $t5, $zero, Lelse_38
    li $t7, 1
    sw $t7, -12($fp)
    j Lend_39
Lelse_38:
    lw $t8, -4($fp)
    addi $sp, $sp, -4   # preserve left operand
    sw $t8, 0($sp)     # save left operand
    lw $t9, -4($fp)
    lw $t0, -8($fp)
    li $t1, 1
    sub $t2, $t0, $t1
    move $a0, $t9
    move $a1, $t2
    jal power_func
    move $t3, $v0
    lw $t4, 0($sp)     # restore left operand
    addi $sp, $sp, 4    # deallocate preservation space
    mul $t5, $t4, $t3
    sw $t5, -12($fp)
Lend_39:
    lw $t6, -12($fp)
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

gcd_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 2 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
Lstart_40:
    lw $t7, -8($fp)
    li $t8, 0
    subu $t0, $t7, $t8
    sltu  $t9, $zero, $t0
    beq $t9, $zero, Lend_41
    lw $t1, -4($fp)
    lw $t2, -4($fp)
    lw $t3, -8($fp)
    div $t2, $t3
    mflo $t4
    lw $t5, -8($fp)
    mul $t6, $t4, $t5
    sub $t7, $t1, $t6
    sw $t7, -12($fp)
    lw $t8, -8($fp)
    sw $t8, -4($fp)
    lw $t9, -12($fp)
    sw $t9, -8($fp)
    j Lstart_40
Lend_41:
    lw $t0, -4($fp)
    move $v0, $t0
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

linearSearch_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -20   # alloc space for 3 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    li $t1, 0
    sw $t1, -16($fp)
    li $t2, 1
    sub $t3, $zero, $t2
    sw $t3, -20($fp)
Lstart_42:
    lw $t4, -16($fp)
    lw $t5, -8($fp)
    slt $t6, $t4, $t5
    beq $t6, $zero, Lend_43
    lw $t8, -16($fp)
    sll $t9, $t8, 2    # multiply index by 4
    lw $t0, -4($fp)     # load array address from parameter
    sub $t9, $t0, $t9 # subtract scaled index for consistency
    lw $t1, 0($t9)     # load from array[index]
    lw $t2, -12($fp)
    subu $t4, $t1, $t2
    sltiu $t3, $t4, 1
    beq $t3, $zero, Lelse_44
    lw $t5, -16($fp)
    sw $t5, -20($fp)
    lw $t6, -8($fp)
    sw $t6, -16($fp)
    j Lend_45
Lelse_44:
    lw $t7, -16($fp)
    li $t8, 1
    add $t9, $t7, $t8
    sw $t9, -16($fp)
Lend_45:
    j Lstart_42
Lend_43:
    lw $t0, -20($fp)
    move $v0, $t0
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

bubbleSort_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -20   # alloc space for 2 params + 3 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t1, 0
    sw $t1, -12($fp)
Lstart_46:
    lw $t2, -12($fp)
    lw $t3, -8($fp)
    li $t4, 1
    sub $t5, $t3, $t4
    slt $t6, $t2, $t5
    beq $t6, $zero, Lend_47
    li $t8, 0
    sw $t8, -16($fp)
Lstart_48:
    lw $t9, -16($fp)
    lw $t0, -8($fp)
    lw $t1, -12($fp)
    sub $t2, $t0, $t1
    li $t3, 1
    sub $t4, $t2, $t3
    slt $t5, $t9, $t4
    beq $t5, $zero, Lend_49
    lw $t7, -16($fp)
    sll $t8, $t7, 2    # multiply index by 4
    lw $t9, -4($fp)     # load array address from parameter
    sub $t8, $t9, $t8 # subtract scaled index for consistency
    lw $t0, 0($t8)     # load from array[index]
    lw $t1, -16($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sll $t4, $t3, 2    # multiply index by 4
    lw $t5, -4($fp)     # load array address from parameter
    sub $t4, $t5, $t4 # subtract scaled index for consistency
    lw $t6, 0($t4)     # load from array[index]
    slt $t7, $t6, $t0
    beq $t7, $zero, Lelse_50
    lw $t9, -16($fp)
    sll $t0, $t9, 2    # multiply index by 4
    lw $t1, -4($fp)     # load array address from parameter
    sub $t0, $t1, $t0 # subtract scaled index for consistency
    lw $t2, 0($t0)     # load from array[index]
    sw $t2, -20($fp)
    lw $t3, -16($fp)
    li $t4, 1
    add $t5, $t3, $t4
    sll $t6, $t5, 2    # multiply index by 4
    lw $t7, -4($fp)     # load array address from parameter
    sub $t6, $t7, $t6 # subtract scaled index for consistency
    lw $t8, 0($t6)     # load from array[index]
    lw $t9, -16($fp)
    sll $t0, $t9, 2    # multiply index by 4
    lw $t1, -4($fp)     # load array address from parameter
    sub $t0, $t1, $t0 # subtract scaled index for consistency
    sw $t8, 0($t0)     # store to array[index]
    lw $t2, -20($fp)
    lw $t3, -16($fp)
    li $t4, 1
    add $t5, $t3, $t4
    sll $t6, $t5, 2    # multiply index by 4
    lw $t7, -4($fp)     # load array address from parameter
    sub $t6, $t7, $t6 # subtract scaled index for consistency
    sw $t2, 0($t6)     # store to array[index]
    j Lend_51
Lelse_50:
Lend_51:
    lw $t8, -16($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -16($fp)
    j Lstart_48
Lend_49:
    lw $t1, -12($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sw $t3, -12($fp)
    j Lstart_46
Lend_47:
    addi $sp, $sp, 20   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

findMax_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 2 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t4, 0
    sll $t5, $t4, 2    # multiply index by 4
    lw $t6, -4($fp)     # load array address from parameter
    sub $t5, $t6, $t5 # subtract scaled index for consistency
    lw $t7, 0($t5)     # load from array[index]
    sw $t7, -12($fp)
    li $t8, 1
    sw $t8, -16($fp)
Lstart_52:
    lw $t9, -16($fp)
    lw $t0, -8($fp)
    slt $t1, $t9, $t0
    beq $t1, $zero, Lend_53
    lw $t3, -16($fp)
    sll $t4, $t3, 2    # multiply index by 4
    lw $t5, -4($fp)     # load array address from parameter
    sub $t4, $t5, $t4 # subtract scaled index for consistency
    lw $t6, 0($t4)     # load from array[index]
    lw $t7, -12($fp)
    slt $t8, $t7, $t6
    beq $t8, $zero, Lelse_54
    lw $t0, -16($fp)
    sll $t1, $t0, 2    # multiply index by 4
    lw $t2, -4($fp)     # load array address from parameter
    sub $t1, $t2, $t1 # subtract scaled index for consistency
    lw $t3, 0($t1)     # load from array[index]
    sw $t3, -12($fp)
    j Lend_55
Lelse_54:
Lend_55:
    lw $t4, -16($fp)
    li $t5, 1
    add $t6, $t4, $t5
    sw $t6, -16($fp)
    j Lstart_52
Lend_53:
    lw $t7, -12($fp)
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

findMin_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 2 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t8, 0
    sll $t9, $t8, 2    # multiply index by 4
    lw $t0, -4($fp)     # load array address from parameter
    sub $t9, $t0, $t9 # subtract scaled index for consistency
    lw $t1, 0($t9)     # load from array[index]
    sw $t1, -12($fp)
    li $t2, 1
    sw $t2, -16($fp)
Lstart_56:
    lw $t3, -16($fp)
    lw $t4, -8($fp)
    slt $t5, $t3, $t4
    beq $t5, $zero, Lend_57
    lw $t7, -16($fp)
    sll $t8, $t7, 2    # multiply index by 4
    lw $t9, -4($fp)     # load array address from parameter
    sub $t8, $t9, $t8 # subtract scaled index for consistency
    lw $t0, 0($t8)     # load from array[index]
    lw $t1, -12($fp)
    slt $t2, $t0, $t1
    beq $t2, $zero, Lelse_58
    lw $t4, -16($fp)
    sll $t5, $t4, 2    # multiply index by 4
    lw $t6, -4($fp)     # load array address from parameter
    sub $t5, $t6, $t5 # subtract scaled index for consistency
    lw $t7, 0($t5)     # load from array[index]
    sw $t7, -12($fp)
    j Lend_59
Lelse_58:
Lend_59:
    lw $t8, -16($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -16($fp)
    j Lstart_56
Lend_57:
    lw $t1, -12($fp)
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

isPrime_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 1 params + 2 locals
    sw $a0, -4($fp)
    lw $t2, -4($fp)
    li $t3, 1
    slt $t5, $t3, $t2
    xori $t4, $t5, 1
    beq $t4, $zero, Lelse_60
    li $t6, 0
    sw $t6, -12($fp)
    j Lend_61
Lelse_60:
    li $t7, 1
    sw $t7, -12($fp)
    li $t8, 2
    sw $t8, -8($fp)
Lstart_62:
    lw $t9, -8($fp)
    lw $t0, -4($fp)
    slt $t1, $t9, $t0
    beq $t1, $zero, Lend_63
    lw $t3, -4($fp)
    lw $t4, -8($fp)
    div $t3, $t4
    mflo $t5
    lw $t6, -8($fp)
    mul $t7, $t5, $t6
    lw $t8, -4($fp)
    subu $t0, $t7, $t8
    sltiu $t9, $t0, 1
    beq $t9, $zero, Lelse_64
    li $t1, 0
    sw $t1, -12($fp)
    lw $t2, -4($fp)
    sw $t2, -8($fp)
    j Lend_65
Lelse_64:
    lw $t3, -8($fp)
    li $t4, 1
    add $t5, $t3, $t4
    sw $t5, -8($fp)
Lend_65:
    j Lstart_62
Lend_63:
Lend_61:
    lw $t6, -12($fp)
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

countPrimes_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 1 params + 2 locals
    sw $a0, -4($fp)
    li $t7, 0
    sw $t7, -8($fp)
    li $t8, 2
    sw $t8, -12($fp)
Lstart_66:
    lw $t9, -12($fp)
    lw $t0, -4($fp)
    slt $t2, $t0, $t9
    xori $t1, $t2, 1
    beq $t1, $zero, Lend_67
    lw $t3, -12($fp)
    move $a0, $t3
    jal isPrime_func
    move $t4, $v0
    li $t5, 1
    subu $t7, $t4, $t5
    sltiu $t6, $t7, 1
    beq $t6, $zero, Lelse_68
    lw $t8, -8($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -8($fp)
    j Lend_69
Lelse_68:
Lend_69:
    lw $t1, -12($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sw $t3, -12($fp)
    j Lstart_66
Lend_67:
    lw $t4, -8($fp)
    move $v0, $t4
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

reverseArray_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -20   # alloc space for 2 params + 3 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t5, 0
    sw $t5, -12($fp)
    lw $t6, -8($fp)
    li $t7, 1
    sub $t8, $t6, $t7
    sw $t8, -16($fp)
Lstart_70:
    lw $t9, -12($fp)
    lw $t0, -16($fp)
    slt $t1, $t9, $t0
    beq $t1, $zero, Lend_71
    lw $t3, -12($fp)
    sll $t4, $t3, 2    # multiply index by 4
    lw $t5, -4($fp)     # load array address from parameter
    sub $t4, $t5, $t4 # subtract scaled index for consistency
    lw $t6, 0($t4)     # load from array[index]
    sw $t6, -20($fp)
    lw $t7, -16($fp)
    sll $t8, $t7, 2    # multiply index by 4
    lw $t9, -4($fp)     # load array address from parameter
    sub $t8, $t9, $t8 # subtract scaled index for consistency
    lw $t0, 0($t8)     # load from array[index]
    lw $t1, -12($fp)
    sll $t2, $t1, 2    # multiply index by 4
    lw $t3, -4($fp)     # load array address from parameter
    sub $t2, $t3, $t2 # subtract scaled index for consistency
    sw $t0, 0($t2)     # store to array[index]
    lw $t4, -20($fp)
    lw $t5, -16($fp)
    sll $t6, $t5, 2    # multiply index by 4
    lw $t7, -4($fp)     # load array address from parameter
    sub $t6, $t7, $t6 # subtract scaled index for consistency
    sw $t4, 0($t6)     # store to array[index]
    lw $t8, -12($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -12($fp)
    lw $t1, -16($fp)
    li $t2, 1
    sub $t3, $t1, $t2
    sw $t3, -16($fp)
    j Lstart_70
Lend_71:
    addi $sp, $sp, 20   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

testComplexExpressions_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 3 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    lw $t4, -4($fp)
    lw $t5, -8($fp)
    lw $t6, -12($fp)
    mul $t7, $t5, $t6
    add $t8, $t4, $t7
    lw $t9, -4($fp)
    lw $t0, -8($fp)
    div $t9, $t0
    mflo $t1
    sub $t2, $t8, $t1
    sw $t2, -16($fp)
    lw $t3, -4($fp)
    lw $t4, -8($fp)
    add $t5, $t3, $t4
    lw $t6, -12($fp)
    lw $t7, -4($fp)
    sub $t8, $t6, $t7
    mul $t9, $t5, $t8
    lw $t0, -8($fp)
    li $t1, 1
    add $t2, $t0, $t1
    div $t9, $t2
    mflo $t3
    sw $t3, -16($fp)
    lw $t4, -4($fp)
    lw $t5, -8($fp)
    mul $t6, $t4, $t5
    lw $t7, -12($fp)
    lw $t8, -4($fp)
    mul $t9, $t7, $t8
    add $t0, $t6, $t9
    lw $t1, -8($fp)
    lw $t2, -12($fp)
    div $t1, $t2
    mflo $t3
    sub $t4, $t0, $t3
    lw $t5, -4($fp)
    add $t6, $t4, $t5
    lw $t7, -8($fp)
    sub $t8, $t6, $t7
    lw $t9, -12($fp)
    add $t0, $t8, $t9
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

testVoidFunction_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 1 params + 1 locals
    sw $a0, -4($fp)
    lw $t2, -4($fp)
    li $t3, 2
    mul $t4, $t2, $t3
    sw $t4, -8($fp)
    lw $t5, -8($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

printArray_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 2 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t6, 0
    sw $t6, -12($fp)
Lstart_72:
    lw $t7, -12($fp)
    lw $t8, -8($fp)
    slt $t9, $t7, $t8
    beq $t9, $zero, Lend_73
    lw $t1, -12($fp)
    sll $t2, $t1, 2    # multiply index by 4
    lw $t3, -4($fp)     # load array address from parameter
    sub $t2, $t3, $t2 # subtract scaled index for consistency
    lw $t4, 0($t2)     # load from array[index]
    move $a0, $t4
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t5, -12($fp)
    li $t6, 1
    add $t7, $t5, $t6
    sw $t7, -12($fp)
    j Lstart_72
Lend_73:
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

multiply3_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 3 params + 0 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    lw $t8, -4($fp)
    lw $t9, -8($fp)
    mul $t0, $t8, $t9
    lw $t1, -12($fp)
    mul $t2, $t0, $t1
    move $v0, $t2
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

add4_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 4 params + 0 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    sw $a3, -16($fp)
    lw $t3, -4($fp)
    lw $t4, -8($fp)
    add $t5, $t3, $t4
    lw $t6, -12($fp)
    add $t7, $t5, $t6
    lw $t8, -16($fp)
    add $t9, $t7, $t8
    move $v0, $t9
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

max3_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 3 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    lw $t0, -4($fp)
    sw $t0, -16($fp)
    lw $t1, -8($fp)
    lw $t2, -16($fp)
    slt $t3, $t2, $t1
    beq $t3, $zero, Lelse_74
    lw $t5, -8($fp)
    sw $t5, -16($fp)
    j Lend_75
Lelse_74:
Lend_75:
    lw $t6, -12($fp)
    lw $t7, -16($fp)
    slt $t8, $t7, $t6
    beq $t8, $zero, Lelse_76
    lw $t0, -12($fp)
    sw $t0, -16($fp)
    j Lend_77
Lelse_76:
Lend_77:
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

fillArray_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 3 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    li $t2, 0
    sw $t2, -16($fp)
Lstart_78:
    lw $t3, -16($fp)
    lw $t4, -8($fp)
    slt $t5, $t3, $t4
    beq $t5, $zero, Lend_79
    lw $t7, -12($fp)
    lw $t8, -16($fp)
    sll $t9, $t8, 2    # multiply index by 4
    lw $t0, -4($fp)     # load array address from parameter
    sub $t9, $t0, $t9 # subtract scaled index for consistency
    sw $t7, 0($t9)     # store to array[index]
    lw $t1, -16($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sw $t3, -16($fp)
    j Lstart_78
Lend_79:
    addi $sp, $sp, 16   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

copyArray_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 3 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    li $t4, 0
    sw $t4, -16($fp)
Lstart_80:
    lw $t5, -16($fp)
    lw $t6, -12($fp)
    slt $t7, $t5, $t6
    beq $t7, $zero, Lend_81
    lw $t9, -16($fp)
    sll $t0, $t9, 2    # multiply index by 4
    lw $t1, -4($fp)     # load array address from parameter
    sub $t0, $t1, $t0 # subtract scaled index for consistency
    lw $t2, 0($t0)     # load from array[index]
    lw $t3, -16($fp)
    sll $t4, $t3, 2    # multiply index by 4
    lw $t5, -8($fp)     # load array address from parameter
    sub $t4, $t5, $t4 # subtract scaled index for consistency
    sw $t2, 0($t4)     # store to array[index]
    lw $t6, -16($fp)
    li $t7, 1
    add $t8, $t6, $t7
    sw $t8, -16($fp)
    j Lstart_80
Lend_81:
    addi $sp, $sp, 16   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

arrayEqual_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -20   # alloc space for 3 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    li $t9, 1
    sw $t9, -20($fp)
    li $t0, 0
    sw $t0, -16($fp)
Lstart_82:
    lw $t1, -16($fp)
    lw $t2, -12($fp)
    slt $t3, $t1, $t2
    beq $t3, $zero, Lend_83
    lw $t5, -16($fp)
    sll $t6, $t5, 2    # multiply index by 4
    lw $t7, -4($fp)     # load array address from parameter
    sub $t6, $t7, $t6 # subtract scaled index for consistency
    lw $t8, 0($t6)     # load from array[index]
    lw $t9, -16($fp)
    sll $t0, $t9, 2    # multiply index by 4
    lw $t1, -8($fp)     # load array address from parameter
    sub $t0, $t1, $t0 # subtract scaled index for consistency
    lw $t2, 0($t0)     # load from array[index]
    subu $t4, $t8, $t2
    sltu  $t3, $zero, $t4
    beq $t3, $zero, Lelse_84
    li $t5, 0
    sw $t5, -20($fp)
    lw $t6, -12($fp)
    sw $t6, -16($fp)
    j Lend_85
Lelse_84:
    lw $t7, -16($fp)
    li $t8, 1
    add $t9, $t7, $t8
    sw $t9, -16($fp)
Lend_85:
    j Lstart_82
Lend_83:
    lw $t0, -20($fp)
    move $v0, $t0
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

absoluteValue_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 1 params + 1 locals
    sw $a0, -4($fp)
    lw $t1, -4($fp)
    li $t2, 0
    slt $t3, $t1, $t2
    beq $t3, $zero, Lelse_86
    li $t5, 0
    lw $t6, -4($fp)
    sub $t7, $t5, $t6
    sw $t7, -8($fp)
    j Lend_87
Lelse_86:
    lw $t8, -4($fp)
    sw $t8, -8($fp)
Lend_87:
    lw $t9, -8($fp)
    move $v0, $t9
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

sign_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 1 params + 1 locals
    sw $a0, -4($fp)
    lw $t0, -4($fp)
    li $t1, 0
    slt $t2, $t0, $t1
    beq $t2, $zero, Lelse_88
    li $t4, 1
    sub $t5, $zero, $t4
    sw $t5, -8($fp)
    j Lend_89
Lelse_88:
    lw $t6, -4($fp)
    li $t7, 0
    slt $t8, $t7, $t6
    beq $t8, $zero, Lelse_90
    li $t0, 1
    sw $t0, -8($fp)
    j Lend_91
Lelse_90:
    li $t1, 0
    sw $t1, -8($fp)
Lend_91:
Lend_89:
    lw $t2, -8($fp)
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

sumOfSquares_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 1 params + 2 locals
    sw $a0, -4($fp)
    li $t3, 0
    sw $t3, -8($fp)
    li $t4, 1
    sw $t4, -12($fp)
Lstart_92:
    lw $t5, -12($fp)
    lw $t6, -4($fp)
    slt $t8, $t6, $t5
    xori $t7, $t8, 1
    beq $t7, $zero, Lend_93
    lw $t9, -8($fp)
    lw $t0, -12($fp)
    lw $t1, -12($fp)
    mul $t2, $t0, $t1
    add $t3, $t9, $t2
    sw $t3, -8($fp)
    lw $t4, -12($fp)
    li $t5, 1
    add $t6, $t4, $t5
    sw $t6, -12($fp)
    j Lstart_92
Lend_93:
    lw $t7, -8($fp)
    move $v0, $t7
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

sumOfCubes_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 1 params + 2 locals
    sw $a0, -4($fp)
    li $t8, 0
    sw $t8, -8($fp)
    li $t9, 1
    sw $t9, -12($fp)
Lstart_94:
    lw $t0, -12($fp)
    lw $t1, -4($fp)
    slt $t3, $t1, $t0
    xori $t2, $t3, 1
    beq $t2, $zero, Lend_95
    lw $t4, -8($fp)
    lw $t5, -12($fp)
    lw $t6, -12($fp)
    mul $t7, $t5, $t6
    lw $t8, -12($fp)
    mul $t9, $t7, $t8
    add $t0, $t4, $t9
    sw $t0, -8($fp)
    lw $t1, -12($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sw $t3, -12($fp)
    j Lstart_94
Lend_95:
    lw $t4, -8($fp)
    move $v0, $t4
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

calculateMean_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 2 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t5, 0
    sw $t5, -12($fp)
    li $t6, 0
    sw $t6, -16($fp)
Lstart_96:
    lw $t7, -16($fp)
    lw $t8, -8($fp)
    slt $t9, $t7, $t8
    beq $t9, $zero, Lend_97
    lw $t1, -12($fp)
    lw $t2, -16($fp)
    sll $t3, $t2, 2    # multiply index by 4
    lw $t4, -4($fp)     # load array address from parameter
    sub $t3, $t4, $t3 # subtract scaled index for consistency
    lw $t5, 0($t3)     # load from array[index]
    add $t6, $t1, $t5
    sw $t6, -12($fp)
    lw $t7, -16($fp)
    li $t8, 1
    add $t9, $t7, $t8
    sw $t9, -16($fp)
    j Lstart_96
Lend_97:
    lw $t0, -12($fp)
    lw $t1, -8($fp)
    div $t0, $t1
    mflo $t2
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
    jr $ra

countOccurrences_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -20   # alloc space for 3 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    li $t3, 0
    sw $t3, -16($fp)
    li $t4, 0
    sw $t4, -20($fp)
Lstart_98:
    lw $t5, -20($fp)
    lw $t6, -8($fp)
    slt $t7, $t5, $t6
    beq $t7, $zero, Lend_99
    lw $t9, -20($fp)
    sll $t0, $t9, 2    # multiply index by 4
    lw $t1, -4($fp)     # load array address from parameter
    sub $t0, $t1, $t0 # subtract scaled index for consistency
    lw $t2, 0($t0)     # load from array[index]
    lw $t3, -12($fp)
    subu $t5, $t2, $t3
    sltiu $t4, $t5, 1
    beq $t4, $zero, Lelse_100
    lw $t6, -16($fp)
    li $t7, 1
    add $t8, $t6, $t7
    sw $t8, -16($fp)
    j Lend_101
Lelse_100:
Lend_101:
    lw $t9, -20($fp)
    li $t0, 1
    add $t1, $t9, $t0
    sw $t1, -20($fp)
    j Lstart_98
Lend_99:
    lw $t2, -16($fp)
    move $v0, $t2
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

leftShift_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 2 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t3, -4($fp)
    sw $t3, -12($fp)
    li $t4, 0
    sw $t4, -16($fp)
Lstart_102:
    lw $t5, -16($fp)
    lw $t6, -8($fp)
    slt $t7, $t5, $t6
    beq $t7, $zero, Lend_103
    lw $t9, -12($fp)
    li $t0, 2
    mul $t1, $t9, $t0
    sw $t1, -12($fp)
    lw $t2, -16($fp)
    li $t3, 1
    add $t4, $t2, $t3
    sw $t4, -16($fp)
    j Lstart_102
Lend_103:
    lw $t5, -12($fp)
    move $v0, $t5
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

rightShift_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 2 params + 2 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t6, -4($fp)
    sw $t6, -12($fp)
    li $t7, 0
    sw $t7, -16($fp)
Lstart_104:
    lw $t8, -16($fp)
    lw $t9, -8($fp)
    slt $t0, $t8, $t9
    beq $t0, $zero, Lend_105
    lw $t2, -12($fp)
    li $t3, 2
    div $t2, $t3
    mflo $t4
    sw $t4, -12($fp)
    lw $t5, -16($fp)
    li $t6, 1
    add $t7, $t5, $t6
    sw $t7, -16($fp)
    j Lstart_104
Lend_105:
    lw $t8, -12($fp)
    move $v0, $t8
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

arrayLength_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 2 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    li $t9, 0
    sw $t9, -12($fp)
Lstart_106:
    lw $t0, -12($fp)
    lw $t1, -8($fp)
    slt $t2, $t0, $t1
    beq $t2, $zero, Lend_107
    lw $t4, -12($fp)
    sll $t5, $t4, 2    # multiply index by 4
    lw $t6, -4($fp)     # load array address from parameter
    sub $t5, $t6, $t5 # subtract scaled index for consistency
    lw $t7, 0($t5)     # load from array[index]
    li $t8, 0
    subu $t0, $t7, $t8
    sltiu $t9, $t0, 1
    beq $t9, $zero, Lelse_108
    lw $t1, -8($fp)
    sw $t1, -12($fp)
    j Lend_109
Lelse_108:
    lw $t2, -12($fp)
    li $t3, 1
    add $t4, $t2, $t3
    sw $t4, -12($fp)
Lend_109:
    j Lstart_106
Lend_107:
    lw $t5, -12($fp)
    move $v0, $t5
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

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -64   # alloc space for 0 params + 16 locals
    li $t6, 0
    sw $t6, -64($fp)
    .data
string_0: .asciiz "Test 1 - 72"
    .text
    la $t7, string_0
    move $a0, $t7
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t8, 10
    li $t9, 5
    move $a0, $t8
    move $a1, $t9
    jal testArithmetic_func
    move $t0, $v0
    sw $t0, -48($fp)
    lw $t1, -48($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_1: .asciiz "Test 2 - 100011"
    .text
    la $t2, string_1
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t3, 5
    li $t4, 10
    move $a0, $t3
    move $a1, $t4
    jal testRelational_func
    move $t5, $v0
    sw $t5, -48($fp)
    lw $t6, -48($fp)
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_2: .asciiz "Test 3 - 50"
    .text
    la $t7, string_2
    move $a0, $t7
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t8, 75
    move $a0, $t8
    jal testIfElse_func
    move $t9, $v0
    sw $t9, -48($fp)
    lw $t0, -48($fp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_3: .asciiz "Test 4 - 55"
    .text
    la $t1, string_3
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t2, 10
    move $a0, $t2
    jal testWhileLoop_func
    move $t3, $v0
    sw $t3, -48($fp)
    lw $t4, -48($fp)
    move $a0, $t4
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_4: .asciiz "Test 5 - 25"
    .text
    la $t5, string_4
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t6, 5
    li $t7, 5
    move $a0, $t6
    move $a1, $t7
    jal testNestedLoops_func
    move $t8, $v0
    sw $t8, -48($fp)
    lw $t9, -48($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_5: .asciiz "Test 6 - 25"
    .text
    la $t0, string_5
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $t1, $fp, -4   # get address of array testArray
    li $t2, 5
    move $a0, $t1
    move $a1, $t2
    jal testArrayOperations_func
    move $t3, $v0
    addi $t4, $fp, -4   # get address of array testArray
    li $t5, 5
    move $a0, $t4
    move $a1, $t5
    jal sumArray_func
    move $t6, $v0
    sw $t6, -48($fp)
    lw $t7, -48($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_6: .asciiz "Test 7 - 120"
    .text
    la $t8, string_6
    move $a0, $t8
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t9, 5
    move $a0, $t9
    jal factorial_func
    move $t0, $v0
    sw $t0, -48($fp)
    lw $t1, -48($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_7: .asciiz "Test 8 - 13"
    .text
    la $t2, string_7
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t3, 7
    move $a0, $t3
    jal fibonacci_func
    move $t4, $v0
    sw $t4, -48($fp)
    lw $t5, -48($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_8: .asciiz "Test 9 - 32"
    .text
    la $t6, string_8
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 2
    li $t8, 5
    move $a0, $t7
    move $a1, $t8
    jal power_func
    move $t9, $v0
    sw $t9, -48($fp)
    lw $t0, -48($fp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_9: .asciiz "Test 10 - 6"
    .text
    la $t1, string_9
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t2, 48
    li $t3, 18
    move $a0, $t2
    move $a1, $t3
    jal gcd_func
    move $t4, $v0
    sw $t4, -48($fp)
    lw $t5, -48($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_10: .asciiz "Test 11 - 4"
    .text
    la $t6, string_10
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 0
    sw $t7, -44($fp)
Lstart_110:
    lw $t8, -44($fp)
    li $t9, 5
    slt $t0, $t8, $t9
    beq $t0, $zero, Lend_111
    lw $t2, -44($fp)
    li $t3, 3
    mul $t4, $t2, $t3
    lw $t5, -44($fp)
    sll $t6, $t5, 2    # multiply index by 4
    addi $t7, $fp, -4   # get array base address
    sub $t6, $t7, $t6 # subtract scaled index
    sw $t4, 0($t6)     # store to array[index]
    lw $t8, -44($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -44($fp)
    j Lstart_110
Lend_111:
    addi $t1, $fp, -4   # get address of array testArray
    li $t2, 5
    li $t3, 12
    move $a0, $t1
    move $a1, $t2
    move $a2, $t3
    jal linearSearch_func
    move $t4, $v0
    sw $t4, -48($fp)
    lw $t5, -48($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_11: .asciiz "Test 12 - 1 2 5 8 9"
    .text
    la $t6, string_11
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 5
    li $t8, 0
    sll $t9, $t8, 2    # multiply index by 4
    addi $t0, $fp, -4   # get array base address
    sub $t9, $t0, $t9 # subtract scaled index
    sw $t7, 0($t9)     # store to array[index]
    li $t1, 2
    li $t2, 1
    sll $t3, $t2, 2    # multiply index by 4
    addi $t4, $fp, -4   # get array base address
    sub $t3, $t4, $t3 # subtract scaled index
    sw $t1, 0($t3)     # store to array[index]
    li $t5, 8
    li $t6, 2
    sll $t7, $t6, 2    # multiply index by 4
    addi $t8, $fp, -4   # get array base address
    sub $t7, $t8, $t7 # subtract scaled index
    sw $t5, 0($t7)     # store to array[index]
    li $t9, 1
    li $t0, 3
    sll $t1, $t0, 2    # multiply index by 4
    addi $t2, $fp, -4   # get array base address
    sub $t1, $t2, $t1 # subtract scaled index
    sw $t9, 0($t1)     # store to array[index]
    li $t3, 9
    li $t4, 4
    sll $t5, $t4, 2    # multiply index by 4
    addi $t6, $fp, -4   # get array base address
    sub $t5, $t6, $t5 # subtract scaled index
    sw $t3, 0($t5)     # store to array[index]
    addi $t7, $fp, -4   # get address of array testArray
    li $t8, 5
    move $a0, $t7
    move $a1, $t8
    jal bubbleSort_func
    move $t9, $v0
    addi $t0, $fp, -4   # get address of array testArray
    li $t1, 5
    move $a0, $t0
    move $a1, $t1
    jal printArray_func
    move $t2, $v0
    .data
string_12: .asciiz "Test 13 - 9 1"
    .text
    la $t3, string_12
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $t4, $fp, -4   # get address of array testArray
    li $t5, 5
    move $a0, $t4
    move $a1, $t5
    jal findMax_func
    move $t6, $v0
    sw $t6, -48($fp)
    lw $t7, -48($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $t8, $fp, -4   # get address of array testArray
    li $t9, 5
    move $a0, $t8
    move $a1, $t9
    jal findMin_func
    move $t0, $v0
    sw $t0, -48($fp)
    lw $t1, -48($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_13: .asciiz "Test 14 - 1 0"
    .text
    la $t2, string_13
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t3, 17
    move $a0, $t3
    jal isPrime_func
    move $t4, $v0
    sw $t4, -48($fp)
    lw $t5, -48($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t6, 18
    move $a0, $t6
    jal isPrime_func
    move $t7, $v0
    sw $t7, -48($fp)
    lw $t8, -48($fp)
    move $a0, $t8
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_14: .asciiz "Test 15 - 8"
    .text
    la $t9, string_14
    move $a0, $t9
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 20
    move $a0, $t0
    jal countPrimes_func
    move $t1, $v0
    sw $t1, -48($fp)
    lw $t2, -48($fp)
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_15: .asciiz "Test 16 - 5 4 3 2 1"
    .text
    la $t3, string_15
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t4, 0
    sw $t4, -44($fp)
Lstart_112:
    lw $t5, -44($fp)
    li $t6, 5
    slt $t7, $t5, $t6
    beq $t7, $zero, Lend_113
    lw $t9, -44($fp)
    li $t0, 1
    add $t1, $t9, $t0
    lw $t2, -44($fp)
    sll $t3, $t2, 2    # multiply index by 4
    addi $t4, $fp, -4   # get array base address
    sub $t3, $t4, $t3 # subtract scaled index
    sw $t1, 0($t3)     # store to array[index]
    lw $t5, -44($fp)
    li $t6, 1
    add $t7, $t5, $t6
    sw $t7, -44($fp)
    j Lstart_112
Lend_113:
    addi $t8, $fp, -4   # get address of array testArray
    li $t9, 5
    move $a0, $t8
    move $a1, $t9
    jal reverseArray_func
    move $t0, $v0
    addi $t1, $fp, -4   # get address of array testArray
    li $t2, 5
    move $a0, $t1
    move $a1, $t2
    jal printArray_func
    move $t3, $v0
    .data
string_16: .asciiz "Test 17 - 24 10 9"
    .text
    la $t4, string_16
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t5, 2
    li $t6, 3
    li $t7, 4
    move $a0, $t5
    move $a1, $t6
    move $a2, $t7
    jal multiply3_func
    move $t8, $v0
    sw $t8, -48($fp)
    lw $t9, -48($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    li $t1, 2
    li $t2, 3
    li $t3, 4
    move $a0, $t0
    move $a1, $t1
    move $a2, $t2
    move $a3, $t3
    jal add4_func
    move $t4, $v0
    sw $t4, -48($fp)
    lw $t5, -48($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t6, 5
    li $t7, 9
    li $t8, 3
    move $a0, $t6
    move $a1, $t7
    move $a2, $t8
    jal max3_func
    move $t9, $v0
    sw $t9, -48($fp)
    lw $t0, -48($fp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_17: .asciiz "Test 18 - 1"
    .text
    la $t1, string_17
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $t2, $fp, -4   # get address of array testArray
    li $t3, 5
    li $t4, 7
    move $a0, $t2
    move $a1, $t3
    move $a2, $t4
    jal fillArray_func
    move $t5, $v0
    addi $t6, $fp, -4   # get address of array testArray
    addi $t7, $fp, -24   # get address of array testArray2
    li $t8, 5
    move $a0, $t6
    move $a1, $t7
    move $a2, $t8
    jal copyArray_func
    move $t9, $v0
    addi $t0, $fp, -4   # get address of array testArray
    addi $t1, $fp, -24   # get address of array testArray2
    li $t2, 5
    move $a0, $t0
    move $a1, $t1
    move $a2, $t2
    jal arrayEqual_func
    move $t3, $v0
    sw $t3, -48($fp)
    lw $t4, -48($fp)
    move $a0, $t4
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_18: .asciiz "Test 19 - 15 -1 1 0"
    .text
    la $t5, string_18
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t6, 15
    sub $t7, $zero, $t6
    move $a0, $t7
    jal absoluteValue_func
    move $t8, $v0
    sw $t8, -48($fp)
    lw $t9, -48($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 5
    sub $t1, $zero, $t0
    move $a0, $t1
    jal sign_func
    move $t2, $v0
    sw $t2, -48($fp)
    lw $t3, -48($fp)
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t4, 5
    move $a0, $t4
    jal sign_func
    move $t5, $v0
    sw $t5, -48($fp)
    lw $t6, -48($fp)
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 0
    move $a0, $t7
    jal sign_func
    move $t8, $v0
    sw $t8, -48($fp)
    lw $t9, -48($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_19: .asciiz "Test 20 - 55 225"
    .text
    la $t0, string_19
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t1, 5
    move $a0, $t1
    jal sumOfSquares_func
    move $t2, $v0
    sw $t2, -48($fp)
    lw $t3, -48($fp)
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t4, 5
    move $a0, $t4
    jal sumOfCubes_func
    move $t5, $v0
    sw $t5, -48($fp)
    lw $t6, -48($fp)
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_20: .asciiz "Test 21 - 6 3"
    .text
    la $t7, string_20
    move $a0, $t7
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t8, 0
    sw $t8, -44($fp)
Lstart_114:
    lw $t9, -44($fp)
    li $t0, 5
    slt $t1, $t9, $t0
    beq $t1, $zero, Lend_115
    lw $t3, -44($fp)
    li $t4, 1
    add $t5, $t3, $t4
    li $t6, 2
    mul $t7, $t5, $t6
    lw $t8, -44($fp)
    sll $t9, $t8, 2    # multiply index by 4
    addi $t0, $fp, -4   # get array base address
    sub $t9, $t0, $t9 # subtract scaled index
    sw $t7, 0($t9)     # store to array[index]
    lw $t1, -44($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sw $t3, -44($fp)
    j Lstart_114
Lend_115:
    addi $t4, $fp, -4   # get address of array testArray
    li $t5, 5
    move $a0, $t4
    move $a1, $t5
    jal calculateMean_func
    move $t6, $v0
    sw $t6, -48($fp)
    lw $t7, -48($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t8, 5
    li $t9, 0
    sll $t0, $t9, 2    # multiply index by 4
    addi $t1, $fp, -4   # get array base address
    sub $t0, $t1, $t0 # subtract scaled index
    sw $t8, 0($t0)     # store to array[index]
    li $t2, 5
    li $t3, 1
    sll $t4, $t3, 2    # multiply index by 4
    addi $t5, $fp, -4   # get array base address
    sub $t4, $t5, $t4 # subtract scaled index
    sw $t2, 0($t4)     # store to array[index]
    li $t6, 3
    li $t7, 2
    sll $t8, $t7, 2    # multiply index by 4
    addi $t9, $fp, -4   # get array base address
    sub $t8, $t9, $t8 # subtract scaled index
    sw $t6, 0($t8)     # store to array[index]
    li $t0, 5
    li $t1, 3
    sll $t2, $t1, 2    # multiply index by 4
    addi $t3, $fp, -4   # get array base address
    sub $t2, $t3, $t2 # subtract scaled index
    sw $t0, 0($t2)     # store to array[index]
    li $t4, 7
    li $t5, 4
    sll $t6, $t5, 2    # multiply index by 4
    addi $t7, $fp, -4   # get array base address
    sub $t6, $t7, $t6 # subtract scaled index
    sw $t4, 0($t6)     # store to array[index]
    addi $t8, $fp, -4   # get address of array testArray
    li $t9, 5
    li $t0, 5
    move $a0, $t8
    move $a1, $t9
    move $a2, $t0
    jal countOccurrences_func
    move $t1, $v0
    sw $t1, -48($fp)
    lw $t2, -48($fp)
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_21: .asciiz "Test 22 - 12 4"
    .text
    la $t3, string_21
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t4, 3
    li $t5, 2
    move $a0, $t4
    move $a1, $t5
    jal leftShift_func
    move $t6, $v0
    sw $t6, -48($fp)
    lw $t7, -48($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t8, 16
    li $t9, 2
    move $a0, $t8
    move $a1, $t9
    jal rightShift_func
    move $t0, $v0
    sw $t0, -48($fp)
    lw $t1, -48($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_22: .asciiz "Test 23 - 87"
    .text
    la $t2, string_22
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t3, 10
    li $t4, 5
    li $t5, 3
    move $a0, $t3
    move $a1, $t4
    move $a2, $t5
    jal testComplexExpressions_func
    move $t6, $v0
    sw $t6, -48($fp)
    lw $t7, -48($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_23: .asciiz "Test 24 - 100 120"
    .text
    la $t8, string_23
    move $a0, $t8
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t9, 100
    sw $t9, -64($fp)
    lw $t0, -64($fp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t1, -64($fp)
    li $t2, 20
    add $t3, $t1, $t2
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_24: .asciiz "Test 25 - 10"
    .text
    la $t4, string_24
    move $a0, $t4
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t5, 5
    move $a0, $t5
    jal testVoidFunction_func
    move $t6, $v0
    li $t7, 999
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 64   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
