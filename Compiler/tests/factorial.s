# C-Minus Compiler Generated MIPS Code
# CST-405 Compiler Design

.data
newline: .asciiz "\n"
prompt: .asciiz "Enter a number: "

.text
.globl main


factorial:
    # Function prologue
    addi $sp, $sp, -32
    sw $ra, 28($sp)
    sw $fp, 24($sp)
    move $fp, $sp
    j L1
L0:
    lw $s0, n
    li $t8, 1
    sub $t4, $s0, $t8
    jal factorial
    move $t5, $v0
L1:
    # Function epilogue
    move $sp, $fp
    lw $fp, 24($sp)
    lw $ra, 28($sp)
    addi $sp, $sp, 32
    jr $ra

main:
    # Function prologue
    addi $sp, $sp, -32
    sw $ra, 28($sp)
    sw $fp, 24($sp)
    move $fp, $sp
    # Function epilogue
    move $sp, $fp
    lw $fp, 24($sp)
    lw $ra, 28($sp)
    addi $sp, $sp, 32
    li $v0, 10
    syscall

_input:
    li $v0, 4
    la $a0, prompt
    syscall
    li $v0, 5
    syscall
    jr $ra

_output:
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    jr $ra
