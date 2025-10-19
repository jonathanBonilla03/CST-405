.text
.globl _func_main

_func_add:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    lw $t0, 8($fp)
    lw $t1, 12($fp)
    add $t2, $t0, $t1
    move $v0, $t2
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra

_func_main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    li $a0, 2
    li $a1, 3
    jal _func_add
    move $t0, $v0
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 10
    syscall
