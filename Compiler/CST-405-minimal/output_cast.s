.data
newline: .asciiz "\n"

.text
.globl main

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -4   # alloc local a
    addi $sp, $sp, -4   # alloc local b
    li $t0, 5
    sw $t0, -4($fp)
    lw $t1, -4($fp)
    move $t2, $t1      # cast to float
    sw $t2, -8($fp)
    lw $t3, -8($fp)
    move $a0, $t3
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 8
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
