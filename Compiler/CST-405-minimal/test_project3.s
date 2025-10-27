.data
newline: .asciiz "\n"

.text
.globl main

testBasicPrecedence:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -4   # alloc local a (int)
    li $t0, 2
    sw $t0, -4($fp)
    addi $sp, $sp, -4   # alloc local b (int)
    li $t1, 3
    sw $t1, -8($fp)
    addi $sp, $sp, -4   # alloc local c (int)
    li $t2, 4
    sw $t2, -12($fp)
    addi $sp, $sp, -4   # alloc local result (float)
    lw $t3, -4($fp)
    mtc1 $t3, $f0
    cvt.s.w $f0, $f0
    mfc1 $t4, $f0      # cast int to float
    lw $t5, -8($fp)
    mtc1 $t5, $f0
    cvt.s.w $f0, $f0
    mfc1 $t6, $f0      # cast int to float
    lw $t7, -12($fp)
    mtc1 $t7, $f0
    cvt.s.w $f0, $f0
    mfc1 $t0, $f0      # cast int to float
    mtc1 $t6, $f0
    mtc1 $t0, $f2
    mul.s $f4, $f0, $f2
    mfc1 $t1, $f4
    mtc1 $t4, $f0
    mtc1 $t1, $f2
    add.s $f4, $f0, $f2
    mfc1 $t2, $f4
    lw $t3, -4($fp)
    mtc1 $t3, $f0
    cvt.s.w $f0, $f0
    mfc1 $t4, $f0      # cast int to float
    lw $t5, -8($fp)
    mtc1 $t5, $f0
    cvt.s.w $f0, $f0
    mfc1 $t6, $f0      # cast int to float
    mtc1 $t4, $f0
    mtc1 $t6, $f2
    div.s $f4, $f0, $f2
    mfc1 $t7, $f4
    mtc1 $t2, $f0
    mtc1 $t7, $f2
    sub.s $f4, $f0, $f2
    mfc1 $t0, $f4
    sw $t0, -16($fp)
    lw $t1, -16($fp)
    move $v0, $t1
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

testComplexPrecedence:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -4   # alloc local a (int)
    li $t2, 5
    sw $t2, -4($fp)
    addi $sp, $sp, -4   # alloc local b (int)
    li $t3, 10
    sw $t3, -8($fp)
    addi $sp, $sp, -4   # alloc local c (int)
    li $t4, 2
    sw $t4, -12($fp)
    lw $t6, -4($fp)
    mtc1 $t6, $f0
    cvt.s.w $f0, $f0
    mfc1 $t7, $f0      # cast int to float
    lw $t0, -8($fp)
    mtc1 $t0, $f0
    cvt.s.w $f0, $f0
    mfc1 $t1, $f0      # cast int to float
    mtc1 $t7, $f0
    mtc1 $t1, $f2
    add.s $f4, $f0, $f2
    mfc1 $t2, $f4
    addi $sp, $sp, -4   # allocate space for base
    sw $t2, 0($sp)     # save base value
    lw $t3, -12($fp)
    mtc1 $t3, $f0
    cvt.s.w $f0, $f0
    mfc1 $t4, $f0      # cast int to float
    lw $t5, -4($fp)
    mtc1 $t5, $f0
    cvt.s.w $f0, $f0
    mfc1 $t6, $f0      # cast int to float
    lw $t7, -8($fp)
    mtc1 $t7, $f0
    cvt.s.w $f0, $f0
    mfc1 $t0, $f0      # cast int to float
    mtc1 $t6, $f0
    mtc1 $t0, $f2
    div.s $f4, $f0, $f2
    mfc1 $t1, $f4
    mtc1 $t4, $f0
    mtc1 $t1, $f2
    sub.s $f4, $f0, $f2
    mfc1 $t2, $f4
    lw $t3, 0($sp)     # restore base value
    addi $sp, $sp, 4    # deallocate space for base
    mtc1 $t3, $f0     # move base to float reg
    mtc1 $t2, $f2     # move exponent to float reg
    cvt.w.s $f4, $f2   # convert exponent to integer (truncates)
    mfc1 $t1, $f4      # get integer exponent
    cvt.s.w $f6, $f4   # convert integer back to float
    sub.s $f8, $f2, $f6 # f8 = fractional part
    li.s $f10, 0.5     # load 0.5
    sub.s $f12, $f8, $f10 # frac - 0.5
    mfc1 $t5, $f12     # get difference as bits
    li $t6, 0x3A83126F  # small epsilon (0.001) as bits
    slt $t7, $t5, $t6  # check if |frac - 0.5| < epsilon (approximate)
    beqz $t1, Lfexp_zero_2       # if exponent is 0, result is 1
    li $t5, 1
    beq $t1, $t5, Lfexp_one_3   # if exponent is 1, check for fractional part
    li $t5, 2
    beq $t1, $t5, Lfexp_two_4   # if exponent is 2, result is base^2
    li.s $f8, 1.0      # result = 1.0
    move $t4, $t1     # counter = exponent
Lfexp_loop_0:
    beqz $t4, Lfexp_end_1      # if counter is 0, exit loop
    mul.s $f8, $f8, $f0 # result *= base
    addi $t4, $t4, -1 # counter--
    j Lfexp_loop_0
Lfexp_zero_2:
    li.s $f8, 1.0      # result = 1.0 (base^0)
    j Lfexp_end_1
Lfexp_one_3:
    mfc1 $t8, $f8      # get fractional part as bits
    li $t9, 0x3F000000  # 0.5 as IEEE 754 bits
    li $t4, 0x3A83126F  # small epsilon
    sub $t8, $t8, $t9  # frac - 0.5
    slt $t6, $t8, $t4  # check if |frac - 0.5| < epsilon
    bnez $t6, Lfexp_sqrt_5       # if close to 0.5, do square root
    li.s $f9, 0.0      # load zero
    add.s $f8, $f0, $f9 # result = base (base^1)
    j Lfexp_end_1
Lfexp_sqrt_5:
    sqrt.s $f10, $f0   # sqrt(base)
    mul.s $f8, $f0, $f10 # result = base * sqrt(base)
    j Lfexp_end_1
Lfexp_normal_6:
Lfexp_two_4:
    mul.s $f8, $f0, $f0 # result = base * base (base^2)
Lfexp_end_1:
    mfc1 $t5, $f8     # get float result as bits
    move $v0, $t5
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

testArrayMath:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -12   # alloc array arr[3] (int)
    li $t5, 2
    sw $t5, -4($fp)   # arr[0] = value
    li $t6, 3
    sw $t6, -8($fp)   # arr[1] = value
    li $t7, 4
    sw $t7, -12($fp)   # arr[2] = value
    addi $sp, $sp, -4   # alloc local result (float)
    li $t1, 0
    sll $t2, $t1, 2    # multiply index by 4
    addi $t3, $fp, -4   # get array base address
    sub $t2, $t3, $t2 # subtract scaled index
    lw $t3, 0($t2)     # load from array[index]
    mtc1 $t3, $f0
    cvt.s.w $f0, $f0
    mfc1 $t4, $f0      # cast int to float
    addi $sp, $sp, -4   # allocate space for base
    sw $t4, 0($sp)     # save base value
    li $t5, 1
    sll $t6, $t5, 2    # multiply index by 4
    addi $t7, $fp, -4   # get array base address
    sub $t6, $t7, $t6 # subtract scaled index
    lw $t7, 0($t6)     # load from array[index]
    mtc1 $t7, $f0
    cvt.s.w $f0, $f0
    mfc1 $t0, $f0      # cast int to float
    lw $t1, 0($sp)     # restore base value
    addi $sp, $sp, 4    # deallocate space for base
    mtc1 $t1, $f0     # move base to float reg
    mtc1 $t0, $f2     # move exponent to float reg
    cvt.w.s $f4, $f2   # convert exponent to integer (truncates)
    mfc1 $t1, $f4      # get integer exponent
    cvt.s.w $f6, $f4   # convert integer back to float
    sub.s $f8, $f2, $f6 # f8 = fractional part
    li.s $f10, 0.5     # load 0.5
    sub.s $f12, $f8, $f10 # frac - 0.5
    mfc1 $t5, $f12     # get difference as bits
    li $t6, 0x3A83126F  # small epsilon (0.001) as bits
    slt $t7, $t5, $t6  # check if |frac - 0.5| < epsilon (approximate)
    beqz $t1, Lfexp_zero_9       # if exponent is 0, result is 1
    li $t5, 1
    beq $t1, $t5, Lfexp_one_10   # if exponent is 1, check for fractional part
    li $t5, 2
    beq $t1, $t5, Lfexp_two_11   # if exponent is 2, result is base^2
    li.s $f8, 1.0      # result = 1.0
    move $t2, $t1     # counter = exponent
Lfexp_loop_7:
    beqz $t2, Lfexp_end_8      # if counter is 0, exit loop
    mul.s $f8, $f8, $f0 # result *= base
    addi $t2, $t2, -1 # counter--
    j Lfexp_loop_7
Lfexp_zero_9:
    li.s $f8, 1.0      # result = 1.0 (base^0)
    j Lfexp_end_8
Lfexp_one_10:
    mfc1 $t8, $f8      # get fractional part as bits
    li $t9, 0x3F000000  # 0.5 as IEEE 754 bits
    li $t4, 0x3A83126F  # small epsilon
    sub $t8, $t8, $t9  # frac - 0.5
    slt $t6, $t8, $t4  # check if |frac - 0.5| < epsilon
    bnez $t6, Lfexp_sqrt_12       # if close to 0.5, do square root
    li.s $f9, 0.0      # load zero
    add.s $f8, $f0, $f9 # result = base (base^1)
    j Lfexp_end_8
Lfexp_sqrt_12:
    sqrt.s $f10, $f0   # sqrt(base)
    mul.s $f8, $f0, $f10 # result = base * sqrt(base)
    j Lfexp_end_8
Lfexp_normal_13:
Lfexp_two_11:
    mul.s $f8, $f0, $f0 # result = base * base (base^2)
Lfexp_end_8:
    mfc1 $t0, $f8     # get float result as bits
    li $t3, 2
    sll $t4, $t3, 2    # multiply index by 4
    addi $t5, $fp, -4   # get array base address
    sub $t4, $t5, $t4 # subtract scaled index
    lw $t5, 0($t4)     # load from array[index]
    mtc1 $t5, $f0
    cvt.s.w $f0, $f0
    mfc1 $t6, $f0      # cast int to float
    mtc1 $t0, $f0
    mtc1 $t6, $f2
    add.s $f4, $f0, $f2
    mfc1 $t7, $f4
    sw $t7, -16($fp)
    lw $t0, -16($fp)
    move $v0, $t0
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

testScopesA:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    addi $sp, $sp, -4   # alloc local result (float)
    lw $t1, -4($fp)
    mtc1 $t1, $f0
    cvt.s.w $f0, $f0
    mfc1 $t2, $f0      # cast int to float
    lw $t3, -8($fp)
    mtc1 $t3, $f0
    cvt.s.w $f0, $f0
    mfc1 $t4, $f0      # cast int to float
    mtc1 $t2, $f0
    mtc1 $t4, $f2
    add.s $f4, $f0, $f2
    mfc1 $t5, $f4
    sw $t5, -12($fp)
    lw $t6, -12($fp)
    move $v0, $t6
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

testScopesB:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi $sp, $sp, -8   # alloc space for 2 parameters
    sw $a0, -4($fp)
    sw $a1, -8($fp)
    addi $sp, $sp, -4   # alloc local result (float)
    lw $t7, -4($fp)
    mtc1 $t7, $f0
    cvt.s.w $f0, $f0
    mfc1 $t0, $f0      # cast int to float
    lw $t1, -8($fp)
    mtc1 $t1, $f0
    cvt.s.w $f0, $f0
    mfc1 $t2, $f0      # cast int to float
    mtc1 $t0, $f0
    mtc1 $t2, $f2
    mul.s $f4, $f0, $f2
    mfc1 $t3, $f4
    sw $t3, -12($fp)
    lw $t4, -12($fp)
    move $v0, $t4
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
    jal testBasicPrecedence
    move $t5, $v0
    mtc1 $t5, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    jal testComplexPrecedence
    move $t6, $v0
    mtc1 $t6, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    jal testArrayMath
    move $t7, $v0
    mtc1 $t7, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 3
    move $a0, $t0
    li $t1, 4
    move $a1, $t1
    jal testScopesA
    move $t2, $v0
    mtc1 $t2, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t3, 3
    move $a0, $t3
    li $t4, 4
    move $a1, $t4
    jal testScopesB
    move $t5, $v0
    mtc1 $t5, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, -4   # alloc local store (float)
    li $t7, 6
    move $a0, $t7
    li $t0, 2
    move $a1, $t0
    jal testScopesA
    move $t1, $v0
    addi $sp, $sp, -4   # allocate space for base
    sw $t1, 0($sp)     # save base value
    li $t2, 2
    move $a0, $t2
    li $t3, 3
    move $a1, $t3
    jal testScopesB
    move $t4, $v0
    lw $t5, 0($sp)     # restore base value
    addi $sp, $sp, 4    # deallocate space for base
    mtc1 $t5, $f0     # move base to float reg
    mtc1 $t4, $f2     # move exponent to float reg
    cvt.w.s $f4, $f2   # convert exponent to integer (truncates)
    mfc1 $t1, $f4      # get integer exponent
    cvt.s.w $f6, $f4   # convert integer back to float
    sub.s $f8, $f2, $f6 # f8 = fractional part
    li.s $f10, 0.5     # load 0.5
    sub.s $f12, $f8, $f10 # frac - 0.5
    mfc1 $t5, $f12     # get difference as bits
    li $t6, 0x3A83126F  # small epsilon (0.001) as bits
    slt $t7, $t5, $t6  # check if |frac - 0.5| < epsilon (approximate)
    beqz $t1, Lfexp_zero_16       # if exponent is 0, result is 1
    li $t5, 1
    beq $t1, $t5, Lfexp_one_17   # if exponent is 1, check for fractional part
    li $t5, 2
    beq $t1, $t5, Lfexp_two_18   # if exponent is 2, result is base^2
    li.s $f8, 1.0      # result = 1.0
    move $t6, $t1     # counter = exponent
Lfexp_loop_14:
    beqz $t6, Lfexp_end_15      # if counter is 0, exit loop
    mul.s $f8, $f8, $f0 # result *= base
    addi $t6, $t6, -1 # counter--
    j Lfexp_loop_14
Lfexp_zero_16:
    li.s $f8, 1.0      # result = 1.0 (base^0)
    j Lfexp_end_15
Lfexp_one_17:
    mfc1 $t8, $f8      # get fractional part as bits
    li $t9, 0x3F000000  # 0.5 as IEEE 754 bits
    li $t4, 0x3A83126F  # small epsilon
    sub $t8, $t8, $t9  # frac - 0.5
    slt $t6, $t8, $t4  # check if |frac - 0.5| < epsilon
    bnez $t6, Lfexp_sqrt_19       # if close to 0.5, do square root
    li.s $f9, 0.0      # load zero
    add.s $f8, $f0, $f9 # result = base (base^1)
    j Lfexp_end_15
Lfexp_sqrt_19:
    sqrt.s $f10, $f0   # sqrt(base)
    mul.s $f8, $f0, $f10 # result = base * sqrt(base)
    j Lfexp_end_15
Lfexp_normal_20:
Lfexp_two_18:
    mul.s $f8, $f0, $f0 # result = base * base (base^2)
Lfexp_end_15:
    mfc1 $t6, $f8     # get float result as bits
    sw $t6, -4($fp)
    lw $t7, -4($fp)
    mtc1 $t7, $f12
    li $v0, 2
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    addi $sp, $sp, 4   # deallocate locals and params
    move $sp, $fp
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    li $v0, 10
    syscall

end:
    j end
