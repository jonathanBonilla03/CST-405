.data
newline: .asciiz "\n"

.text
.globl main

swap_func:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc space for 3 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    sw $a2, -12($fp)
    addi $sp, $sp, -4   # alloc local hold (int)
    lw $t0, -8($fp)
    sll $t1, $t0, 2    # multiply index by 4
    lw $t2, -4($fp)     # load array address from parameter
    sub $t1, $t2, $t1 # subtract scaled index for consistency
    lw $t3, 0($t1)     # load from array[index]
    sw $t3, -16($fp)
    lw $t4, -12($fp)
    sll $t5, $t4, 2    # multiply index by 4
    lw $t6, -4($fp)     # load array address from parameter
    sub $t5, $t6, $t5 # subtract scaled index for consistency
    lw $t7, 0($t5)     # load from array[index]
    lw $t8, -8($fp)
    sll $t9, $t8, 2    # multiply index by 4
    lw $t0, -4($fp)     # load array address from parameter
    sub $t9, $t0, $t9 # subtract scaled index for consistency
    sw $t7, 0($t9)     # store to array[index]
    lw $t1, -16($fp)
    lw $t2, -12($fp)
    sll $t3, $t2, 2    # multiply index by 4
    lw $t4, -4($fp)     # load array address from parameter
    sub $t3, $t4, $t3 # subtract scaled index for consistency
    sw $t1, 0($t3)     # store to array[index]
    lw $t5, -4($fp)
    move $v0, $t5
    addi $sp, $sp, 16   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 16   # deallocate locals and params
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
    addi $sp, $sp, -4   # alloc local a (int)
    li $t6, 10
    sw $t6, -4($fp)
    addi $sp, $sp, -4   # alloc local b (int)
    li $t7, 5
    sw $t7, -8($fp)
    addi $sp, $sp, -4   # alloc local c (int)
    li $t8, 20
    sw $t8, -12($fp)
    addi $sp, $sp, -4   # alloc local d (int)
    li $t9, 10
    sw $t9, -16($fp)
Lstart_0:
    lw $t0, -4($fp)
    lw $t1, -8($fp)
    slt $t2, $t1, $t0
    lw $t4, -12($fp)
    lw $t5, -16($fp)
    slt $t6, $t5, $t4
    beqz $t2, Lfalse_2      # if first operand is 0, result is 0
    beqz $t6, Lfalse_2      # if second operand is 0, result is 0
    li $t8, 1         # both true, result is 1
    j Lend_3
Lfalse_2:
    li $t8, 0         # result is 0
Lend_3:
    beq $t8, $zero, Lend_1
    .data
string_0: .asciiz "r = "
    .text
    la $t9, string_0
    move $a0, $t9
    li $v0, 4      # syscall for print_string
    syscall
    li $t0, 0     # output returns void (0)
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    slt $t3, $t2, $t1
    lw $t5, -12($fp)
    lw $t6, -16($fp)
    slt $t7, $t6, $t5
    beqz $t3, Lfalse_4      # if first operand is 0, result is 0
    beqz $t7, Lfalse_4      # if second operand is 0, result is 0
    li $t9, 1         # both true, result is 1
    j Lend_5
Lfalse_4:
    li $t9, 0         # result is 0
Lend_5:
    move $a0, $t9
    li $v0, 1      # syscall for print_int
    syscall
    li $t0, 0     # output returns void (0)
    .data
string_1: .asciiz ""
    .text
    la $t1, string_1
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t2, -4($fp)
    li $t3, 1
    sub $t4, $t2, $t3
    sw $t4, -4($fp)
    j Lstart_0
Lend_1:
    addi $sp, $sp, -20   # alloc array num[5] (int)
    li $t5, 1
    sw $t5, -20($fp)   # num[0] = value
    li $t6, 2
    sw $t6, -24($fp)   # num[1] = value
    li $t7, 3
    sw $t7, -28($fp)   # num[2] = value
    li $t8, 4
    sw $t8, -32($fp)   # num[3] = value
    li $t9, 5
    sw $t9, -36($fp)   # num[4] = value
    addi $sp, $sp, -4   # alloc local numLength (int)
    li $t0, 5
    sw $t0, -40($fp)
    addi $sp, $sp, -4   # alloc local x (int)
    li $t1, 0
    sw $t1, -44($fp)
Lstart_6:
    lw $t2, -44($fp)
    lw $t3, -40($fp)
    li $t4, 1
    sub $t5, $t3, $t4
    slt $t6, $t2, $t5
    beq $t6, $zero, Lend_7
    lw $t8, -44($fp)
    sll $t9, $t8, 2    # multiply index by 4
    addi $t0, $fp, -20   # get array base address
    sub $t9, $t0, $t9 # subtract scaled index
    lw $t1, 0($t9)     # load from array[index]
    lw $t2, -44($fp)
    li $t3, 1
    add $t4, $t2, $t3
    sll $t5, $t4, 2    # multiply index by 4
    addi $t6, $fp, -20   # get array base address
    sub $t5, $t6, $t5 # subtract scaled index
    lw $t7, 0($t5)     # load from array[index]
    slt $t8, $t1, $t7
    beq $t8, $zero, Lelse_8
    addi $t0, $fp, -20   # get address of array num
    lw $t1, -44($fp)
    lw $t2, -44($fp)
    li $t3, 1
    add $t4, $t2, $t3
    move $a0, $t0
    move $a1, $t1
    move $a2, $t4
    jal swap_func
    move $t5, $v0
    j Lend_9
Lelse_8:
Lend_9:
    lw $t6, -44($fp)
    li $t7, 1
    add $t8, $t6, $t7
    sw $t8, -44($fp)
    j Lstart_6
Lend_7:
    li $a0, 91
    li $v0, 11
    syscall
    li $t9, 0
    li $t0, 5
array_print_loop_10:
    bge $t9, $t0, array_print_end_11
    addi $t3, $fp, -20
    sll $t2, $t9, 2
    sub $t1, $t3, $t2
    lw $t1, 0($t1)
    move $a0, $t1
    li $v0, 1
    syscall
    addi $t4, $t9, 1
    bge $t4, $t0, skip_comma_array_print_loop_10
    li $a0, 44
    li $v0, 11
    syscall
    li $a0, 32
    li $v0, 11
    syscall
skip_comma_array_print_loop_10:
    addi $t9, $t9, 1
    j array_print_loop_10
array_print_end_11:
    li $a0, 93
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t5, 0
    move $v0, $t5
    addi $sp, $sp, 44   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
    addi $sp, $sp, 44   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
