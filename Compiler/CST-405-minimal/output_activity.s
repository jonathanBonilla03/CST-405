.data
newline: .asciiz "\n"

.text
.globl main

divide:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    addi $sp, $sp, -8   # alloc array d[2]
    lw $t0, -4($fp)
    mtc1 $t0, $f0
    cvt.s.w $f0, $f0
    mfc1 $t1, $f0      # cast int to float
    li $t2, 0
    sll $t3, $t2, 2    # multiply index by 4
    addi $t4, $fp, -12   # get array base address
    sub $t3, $t4, $t3 # subtract scaled index
    sw $t1, 0($t3)     # store to array[index]
    lw $t4, -8($fp)
    mtc1 $t4, $f0
    cvt.s.w $f0, $f0
    mfc1 $t5, $f0      # cast int to float
    li $t6, 1
    sll $t7, $t6, 2    # multiply index by 4
    addi $t8, $fp, -12   # get array base address
    sub $t7, $t8, $t7 # subtract scaled index
    sw $t5, 0($t7)     # store to array[index]
    li $t0, 0
    sll $t1, $t0, 2    # multiply index by 4
    addi $t2, $fp, -12   # get array base address
    sub $t1, $t2, $t1 # subtract scaled index
    lw $t2, 0($t1)     # load from array[index]
    li $t3, 1
    sll $t4, $t3, 2    # multiply index by 4
    addi $t5, $fp, -12   # get array base address
    sub $t4, $t5, $t4 # subtract scaled index
    lw $t5, 0($t4)     # load from array[index]
    mtc1 $t2, $f0
    mtc1 $t5, $f2
    div.s $f4, $f0, $f2
    mfc1 $t6, $f4
    move $v0, $t6
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
    addi $sp, $sp, -4   # alloc local x
    addi $sp, $sp, -4   # alloc local y
    li $t7, 2
    move $a0, $t7
    li $t0, 3
    move $a1, $t0
    jal divide
    move $t1, $v0
    sw $t1, -4($fp)
    li $t2, 5
    move $a0, $t2
    li $t3, 10
    move $a1, $t3
    jal divide
    move $t4, $v0
    sw $t4, -8($fp)
    lw $t5, -4($fp)
    li $t6, 0
    mtc1 $t5, $f0
    mtc1 $t6, $f2
    cvt.s.w $f2, $f2
    c.lt.s $f2, $f0
    bc1t float_true_7
    li $t7, 0
    j float_end_7
float_true_7:
    li $t7, 1
float_end_7:
    lw $t1, -4($fp)
    li $t2, 1
    mtc1 $t1, $f0
    mtc1 $t2, $f2
    cvt.s.w $f2, $f2
    c.lt.s $f0, $f2
    bc1t float_true_3
    li $t3, 0
    j float_end_3
float_true_3:
    li $t3, 1
float_end_3:
    beqz $t7, Lfalse_2      # if first operand is 0, result is 0
    beqz $t3, Lfalse_2      # if second operand is 0, result is 0
    li $t5, 1         # both true, result is 1
    j Lend_3
Lfalse_2:
    li $t5, 0         # result is 0
Lend_3:
    beq $t5, $zero, Lelse_0
    lw $t6, -4($fp)
    mtc1 $t6, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t7, -8($fp)
    li $t0, 0
    mtc1 $t7, $f0
    mtc1 $t0, $f2
    cvt.s.w $f2, $f2
    c.lt.s $f2, $f0
    bc1t float_true_1
    li $t1, 0
    j float_end_1
float_true_1:
    li $t1, 1
float_end_1:
    lw $t3, -8($fp)
    li $t4, 1
    mtc1 $t3, $f0
    mtc1 $t4, $f2
    cvt.s.w $f2, $f2
    c.lt.s $f0, $f2
    bc1t float_true_5
    li $t5, 0
    j float_end_5
float_true_5:
    li $t5, 1
float_end_5:
    beqz $t1, Lfalse_6      # if first operand is 0, result is 0
    beqz $t5, Lfalse_6      # if second operand is 0, result is 0
    li $t7, 1         # both true, result is 1
    j Lend_7
Lfalse_6:
    li $t7, 0         # result is 0
Lend_7:
    beq $t7, $zero, Lelse_4
    lw $t0, -8($fp)
    mtc1 $t0, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_5
Lelse_4:
    li $t1, 1
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lend_5:
    lw $t2, -4($fp)
    lw $t3, -8($fp)
    mtc1 $t2, $f0
    mtc1 $t3, $f2
    add.s $f4, $f0, $f2
    mfc1 $t4, $f4
    li $t5, 1
    mtc1 $t4, $f0
    mtc1 $t5, $f2
    cvt.s.w $f2, $f2
    c.lt.s $f2, $f0
    bc1t float_true_6
    li $t6, 0
    j float_end_6
float_true_6:
    li $t6, 1
float_end_6:
    beq $t6, $zero, Lelse_8
    li $t0, 2
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_9
Lelse_8:
Lend_9:
    j Lend_1
Lelse_0:
    li $t1, 0
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lend_1:
    addi $sp, $sp, 8   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
