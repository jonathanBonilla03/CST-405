.data
newline: .asciiz "\n"

.text
.globl main
main:
    addi $sp, $sp, -400  # stack space
    # Declared a at offset 0
    # Declared b at offset 4
    # Declared c at offset 8
    # Declared d at offset 12
    # Declared flag at offset 16
    li $t0, 5
    sw $t0, 0($sp)
    li $t1, 2
    sw $t1, 4($sp)
    lw $t2, 0($sp)
    lw $t3, 4($sp)
    mul $t4, $t2, $t3
    li $t5, 10
    li $t6, 2
    div $t5, $t6
    mflo $t7
    add $t0, $t4, $t7
    sw $t0, 8($sp)
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    slt $t3, $t2, $t1
    lw $t5, 8($sp)
    li $t6, 15
    subu $t0, $t5, $t6
    sltiu $t7, $t0, 1
    and $t1, $t3, $t7
    sw $t1, 16($sp)
    lw $t2, 16($sp)
    beq $t2, $zero, L_else_0
    lw $t3, 8($sp)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j L_end_1
L_else_0:
    lw $t4, 0($sp)
    move $a0, $t4
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
L_end_1:
    li $t5, 3
    sw $t5, 12($sp)
    lw $t6, 12($sp)
    li $t7, 5
    slt $t0, $t7, $t6
    sltiu $t2, $t0, 1
    lw $t3, 0($sp)
    li $t4, 5
    subu $t6, $t3, $t4
    sltiu $t5, $t6, 1
    or  $t7, $t2, $t5
    beq $t7, $zero, L_else_2
    lw $t0, 12($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j L_end_3
L_else_2:
    lw $t1, 4($sp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
L_end_3:
    lw $t2, 0($sp)
    lw $t3, 4($sp)
    slt $t4, $t2, $t3
    beq $t4, $zero, L_else_4
    li $t6, 100
    move $a0, $t6
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j L_end_5
L_else_4:
    li $t7, 999
    move $a0, $t7
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
L_end_5:

    addi $sp, $sp, 400
    li $v0, 10
    syscall
