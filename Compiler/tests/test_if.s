.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400

    # x = 5
    li $t0, 5
    sw $t0, 0($sp)

    # if (x)
    lw $t1, 0($sp)
    beq $t1, $zero, L_else

    # print(x)
    move $a0, $t1
    li $v0, 1
    syscall

L_else:
    # Exit
    addi $sp, $sp, 400
    li $v0, 10
    syscall
