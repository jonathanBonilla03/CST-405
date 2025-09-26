.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400

    # Declared array numbers[5] at offset 0
    # Declared x at offset 20
    li $t0, 10
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall
