.data
newline: .asciiz "\n"

.text
.globl main

testOrderOfOperations_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -24   # alloc space for 2 params + 4 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t0, -4($fp)
    lw $t1, -8($fp)
    li $t2, 2
    mul $t3, $t1, $t2
    add $t4, $t0, $t3
    sw $t4, -12($fp)
    lw $t5, -4($fp)
    lw $t6, -8($fp)
    li $t7, 2
    div $t6, $t7
    mflo $t8
    sub $t9, $t5, $t8
    sw $t9, -16($fp)
    lw $t0, -4($fp)
    lw $t1, -8($fp)
    add $t2, $t0, $t1
    li $t3, 2
    mul $t4, $t2, $t3
    sw $t4, -20($fp)
    lw $t5, -4($fp)
    li $t6, 2
    mul $t7, $t5, $t6
    lw $t8, -8($fp)
    li $t9, 2
    div $t8, $t9
    mflo $t0
    add $t1, $t7, $t0
    li $t2, 1
    sub $t3, $t1, $t2
    sw $t3, -24($fp)
    lw $t4, -12($fp)
    lw $t5, -16($fp)
    add $t6, $t4, $t5
    lw $t7, -20($fp)
    add $t8, $t6, $t7
    lw $t9, -24($fp)
    add $t0, $t8, $t9
    move $v0, $t0
    addi $sp, $sp, 24   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 24   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

testWhileLoopCounting_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 0 params + 3 locals
    li $t1, 1
    sw $t1, -4($fp)
    li $t2, 0
    sw $t2, -8($fp)
    li $t3, 5
    sw $t3, -12($fp)
    li $t4, 100
    move $a0, $t4
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lstart_0:
    lw $t5, -4($fp)
    lw $t6, -12($fp)
    slt $t8, $t6, $t5
    xori $t7, $t8, 1
    beq $t7, $zero, Lend_1
    lw $t9, -4($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t0, -8($fp)
    lw $t1, -4($fp)
    add $t2, $t0, $t1
    sw $t2, -8($fp)
    lw $t3, -4($fp)
    li $t4, 1
    add $t5, $t3, $t4
    sw $t5, -4($fp)
    j Lstart_0
Lend_1:
    li $t6, 200
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t7, -8($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t8, -8($fp)
    move $v0, $t8
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

testWhileLoopConditions_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 1 params + 3 locals
    sw $a0, -4($fp)
    lw $t9, -4($fp)
    sw $t9, -8($fp)
    li $t0, 0
    sw $t0, -12($fp)
    li $t1, 0
    sw $t1, -16($fp)
    li $t2, 300
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lstart_2:
    lw $t3, -8($fp)
    li $t4, 0
    slt $t5, $t4, $t3
    beq $t5, $zero, Lend_3
    lw $t7, -8($fp)
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t8, -12($fp)
    lw $t9, -8($fp)
    li $t0, 2
    mul $t1, $t9, $t0
    add $t2, $t8, $t1
    sw $t2, -12($fp)
    lw $t3, -8($fp)
    li $t4, 2
    sub $t5, $t3, $t4
    sw $t5, -8($fp)
    lw $t6, -16($fp)
    li $t7, 1
    add $t8, $t6, $t7
    sw $t8, -16($fp)
    j Lstart_2
Lend_3:
    li $t9, 400
    move $a0, $t9
    li $v0, 1
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
    lw $t1, -12($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t2, -12($fp)
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

testNestedWhileLoops_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 0 params + 4 locals
    li $t3, 1
    sw $t3, -4($fp)
    li $t4, 0
    sw $t4, -16($fp)
    li $t5, 500
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lstart_4:
    lw $t6, -4($fp)
    li $t7, 3
    slt $t9, $t7, $t6
    xori $t8, $t9, 1
    beq $t8, $zero, Lend_5
    lw $t0, -4($fp)
    li $t1, 10
    mul $t2, $t0, $t1
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t3, 1
    sw $t3, -8($fp)
    li $t4, 0
    sw $t4, -12($fp)
Lstart_6:
    lw $t5, -8($fp)
    lw $t6, -4($fp)
    slt $t8, $t6, $t5
    xori $t7, $t8, 1
    beq $t7, $zero, Lend_7
    lw $t9, -12($fp)
    lw $t0, -8($fp)
    add $t1, $t9, $t0
    sw $t1, -12($fp)
    lw $t2, -8($fp)
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t3, -8($fp)
    li $t4, 1
    add $t5, $t3, $t4
    sw $t5, -8($fp)
    j Lstart_6
Lend_7:
    lw $t6, -12($fp)
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t7, -16($fp)
    lw $t8, -12($fp)
    add $t9, $t7, $t8
    sw $t9, -16($fp)
    lw $t0, -4($fp)
    li $t1, 1
    add $t2, $t0, $t1
    sw $t2, -4($fp)
    j Lstart_4
Lend_5:
    li $t3, 600
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t4, -16($fp)
    move $a0, $t4
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t5, -16($fp)
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

testOrderInLoopConditions_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -16   # alloc space for 0 params + 4 locals
    li $t6, 1
    sw $t6, -4($fp)
    li $t7, 3
    sw $t7, -8($fp)
    li $t8, 2
    sw $t8, -12($fp)
    li $t9, 0
    sw $t9, -16($fp)
    li $t0, 700
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lstart_8:
    lw $t1, -4($fp)
    lw $t2, -12($fp)
    mul $t3, $t1, $t2
    lw $t4, -8($fp)
    li $t5, 4
    mul $t6, $t4, $t5
    slt $t8, $t6, $t3
    xori $t7, $t8, 1
    beq $t7, $zero, Lend_9
    lw $t9, -4($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t0, -4($fp)
    lw $t1, -12($fp)
    mul $t2, $t0, $t1
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t3, -16($fp)
    lw $t4, -4($fp)
    lw $t5, -12($fp)
    mul $t6, $t4, $t5
    add $t7, $t3, $t6
    li $t8, 1
    add $t9, $t7, $t8
    sw $t9, -16($fp)
    lw $t0, -4($fp)
    li $t1, 1
    add $t2, $t0, $t1
    sw $t2, -4($fp)
    j Lstart_8
Lend_9:
    li $t3, 800
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t4, -16($fp)
    move $a0, $t4
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t5, -16($fp)
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

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -24   # alloc space for 0 params + 6 locals
    li $t6, 1
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 10
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t8, 5
    li $t9, 4
    move $a0, $t8
    move $a1, $t9
    jal testOrderOfOperations_func
    move $t0, $v0
    sw $t0, -4($fp)
    lw $t1, -4($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t2, 2
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    jal testWhileLoopCounting_func
    move $t3, $v0
    sw $t3, -8($fp)
    li $t4, 3
    move $a0, $t4
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t5, 6
    move $a0, $t5
    jal testWhileLoopConditions_func
    move $t6, $v0
    sw $t6, -12($fp)
    li $t7, 4
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    jal testNestedWhileLoops_func
    move $t8, $v0
    sw $t8, -16($fp)
    li $t9, 5
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    jal testOrderInLoopConditions_func
    move $t0, $v0
    sw $t0, -20($fp)
    li $t1, 6
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t2, -4($fp)
    lw $t3, -8($fp)
    li $t4, 2
    mul $t5, $t3, $t4
    add $t6, $t2, $t5
    lw $t7, -16($fp)
    li $t8, 2
    div $t7, $t8
    mflo $t9
    sub $t0, $t6, $t9
    sw $t0, -24($fp)
    lw $t1, -24($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t2, 999
    move $a0, $t2
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 24   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
