.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400

    # Declared x at offset 0
    # Declared y at offset 4
    # Declared z at offset 8
    li $t0, 4
    sw $t0, 0($sp)
    li.s $f0, 4.000000
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t2
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall
