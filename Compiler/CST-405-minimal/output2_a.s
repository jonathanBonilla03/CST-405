.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400

    # Declared array list[3] at offset 0
    li $t0, 0
    li $t1, 5
    # Array assignment: list[index] = value
    sll $t0, $t0, 2    # index * 4
    add $t0, $sp, $t0  # base + offset
    addi $t0, $t0, 0  # apply baseOffset
    sw $t1, 0($t0)     # store value
    li $t0, 1
    li $t1, 10
    # Array assignment: list[index] = value
    sll $t0, $t0, 2    # index * 4
    add $t0, $sp, $t0  # base + offset
    addi $t0, $t0, 0  # apply baseOffset
    sw $t1, 0($t0)     # store value
    li $t0, 2
    li $t1, 0
    # Array access: list[index]
    sll $t1, $t1, 2    # index * 4
    addi $t2, $sp, 0   # base address
    add $t2, $t2, $t1 # element address
    lw $t2, 0($t2)     # load value
    li $t3, 1
    # Array access: list[index]
    sll $t3, $t3, 2    # index * 4
    addi $t4, $sp, 0   # base address
    add $t4, $t4, $t3 # element address
    lw $t4, 0($t4)     # load value
    add $t2, $t2, $t4
    # Array assignment: list[index] = value
    sll $t0, $t0, 2    # index * 4
    add $t0, $sp, $t0  # base + offset
    addi $t0, $t0, 0  # apply baseOffset
    sw $t2, 0($t0)     # store value
    li $t0, 2
    # Array access: list[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 0   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer
    move $a0, $t1
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
