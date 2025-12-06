.data
newline: .asciiz "\n"

.text
.globl main

testOptimizedConditions_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -24   # alloc space for 1 params + 5 locals
    sw $a0, -4($fp)
    li $t0, 5
    li $t1, 3
    li $t2, 2
    mul $t3, $t1, $t2
    add $t4, $t0, $t3
    sw $t4, -12($fp)
    lw $t5, -12($fp)
    li $t6, 4
    add $t7, $t5, $t6
    sw $t7, -16($fp)
    li $t8, 100
    li $t9, 50
    mul $t0, $t8, $t9
    sw $t0, -20($fp)
    lw $t1, -4($fp)
    li $t2, 1
    mul $t3, $t1, $t2
    sw $t3, -24($fp)
    lw $t4, -16($fp)
    li $t5, 10
    slt $t6, $t5, $t4
    beq $t6, $zero, Lelse_0
    lw $t8, -24($fp)
    lw $t9, -12($fp)
    add $t0, $t8, $t9
    sw $t0, -8($fp)
    j Lend_1
Lelse_0:
    li $t1, 0
    sw $t1, -8($fp)
Lend_1:
    li $t2, 2
    li $t3, 2
    add $t4, $t2, $t3
    li $t5, 4
    subu $t7, $t4, $t5
    sltiu $t6, $t7, 1
    beq $t6, $zero, Lelse_2
    lw $t8, -8($fp)
    li $t9, 1
    add $t0, $t8, $t9
    sw $t0, -8($fp)
    j Lend_3
Lelse_2:
Lend_3:
    lw $t1, -4($fp)
    lw $t2, -12($fp)
    add $t3, $t1, $t2
    sw $t3, -24($fp)
    lw $t4, -4($fp)
    li $t5, 0
    slt $t6, $t5, $t4
    beq $t6, $zero, Lelse_4
    lw $t8, -24($fp)
    sw $t8, -8($fp)
    j Lend_5
Lelse_4:
    lw $t9, -24($fp)
    li $t0, 5
    sub $t1, $t9, $t0
    sw $t1, -8($fp)
Lend_5:
    lw $t2, -8($fp)
    move $v0, $t2
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

testOptimizedLoop_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -24   # alloc space for 1 params + 5 locals
    sw $a0, -4($fp)
    li $t3, 0
    sw $t3, -8($fp)
    li $t4, 0
    sw $t4, -12($fp)
    li $t5, 10
    li $t6, 5
    mul $t7, $t5, $t6
    sw $t7, -16($fp)
    li $t8, 3
    li $t9, 2
    add $t0, $t8, $t9
    sw $t0, -20($fp)
Lstart_6:
    lw $t1, -12($fp)
    lw $t2, -4($fp)
    slt $t3, $t1, $t2
    beq $t3, $zero, Lend_7
    lw $t5, -16($fp)
    lw $t6, -20($fp)
    add $t7, $t5, $t6
    sw $t7, -24($fp)
    lw $t8, -8($fp)
    lw $t9, -12($fp)
    li $t0, 1
    mul $t1, $t9, $t0
    add $t2, $t8, $t1
    sw $t2, -8($fp)
    lw $t3, -8($fp)
    lw $t4, -12($fp)
    li $t5, 0
    add $t6, $t4, $t5
    add $t7, $t3, $t6
    sw $t7, -8($fp)
    lw $t8, -8($fp)
    lw $t9, -24($fp)
    add $t0, $t8, $t9
    sw $t0, -8($fp)
    lw $t1, -12($fp)
    li $t2, 1
    add $t3, $t1, $t2
    sw $t3, -12($fp)
    j Lstart_6
Lend_7:
    li $t4, 999
    sw $t4, -24($fp)
    lw $t5, -8($fp)
    li $t6, 2
    li $t7, 3
    mul $t8, $t6, $t7
    add $t9, $t5, $t8
    move $v0, $t9
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

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 0 params + 3 locals
    li $t0, 8
    li $t1, 2
    add $t2, $t0, $t1
    sw $t2, -12($fp)
    li $t3, 1
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t4, -12($fp)
    move $a0, $t4
    jal testOptimizedConditions_func
    move $t5, $v0
    sw $t5, -4($fp)
    lw $t6, -4($fp)
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 2
    move $a0, $t7
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t8, 5
    move $a0, $t8
    jal testOptimizedLoop_func
    move $t9, $v0
    sw $t9, -8($fp)
    lw $t0, -8($fp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t1, 3
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t2, -4($fp)
    li $t3, 4
    li $t4, 5
    mul $t5, $t3, $t4
    li $t6, 2
    sub $t7, $t5, $t6
    add $t8, $t2, $t7
    sw $t8, -4($fp)
    lw $t9, -4($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 12   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
