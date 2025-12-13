.data
newline: .asciiz "\n"

.text
.globl main

testOrderOfOperations_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 2 params + 1 locals
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    lw $t0, -4($fp)
    lw $t1, -8($fp)
    li $t2, 2
    mul $t3, $t1, $t2
    add $t4, $t0, $t3
    li $t5, 6
    li $t6, 3
    div $t5, $t6
    mflo $t7
    sub $t8, $t4, $t7
    sw $t8, -12($fp)
    lw $t9, -12($fp)
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

testWhileLoop_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 1 params + 2 locals
    sw $a0, -4($fp)
    li $t0, 0
    sw $t0, -8($fp)
    li $t1, 1
    sw $t1, -12($fp)
Lstart_0:
    lw $t2, -12($fp)
    lw $t3, -4($fp)
    slt $t5, $t3, $t2
    xori $t4, $t5, 1
    beq $t4, $zero, Lend_1
    lw $t6, -8($fp)
    lw $t7, -12($fp)
    add $t8, $t6, $t7
    sw $t8, -8($fp)
    lw $t9, -12($fp)
    li $t0, 1
    add $t1, $t9, $t0
    sw $t1, -12($fp)
    j Lstart_0
Lend_1:
    lw $t2, -8($fp)
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

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 0 params + 2 locals
    li $t3, 5
    li $t4, 4
    move $a0, $t3
    move $a1, $t4
    jal testOrderOfOperations_func
    move $t5, $v0
    sw $t5, -4($fp)
    lw $t6, -4($fp)
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t7, 5
    move $a0, $t7
    jal testWhileLoop_func
    move $t8, $v0
    sw $t8, -8($fp)
    lw $t9, -8($fp)
    move $a0, $t9
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
    li $v0, 10
    syscall

end:
    j end
