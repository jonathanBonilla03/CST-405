.data
newline: .asciiz "\n"

.text
.globl main

main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    .data
string_0: .asciiz "=== IF & RETRY Demo ==="
    .text
    la $t0, string_0
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
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
    addi $sp, $sp, -4   # alloc local a (int)
    li $t2, 5
    sw $t2, -4($fp)
    .data
string_2: .asciiz "a is "
    .text
    la $t3, string_2
    move $a0, $t3
    li $v0, 4      # syscall for print_string
    syscall
    li $t4, 0     # output returns void (0)
    lw $t5, -4($fp)
    move $a0, $t5
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t6, -4($fp)
    li $t7, 6
    slt $t8, $t7, $t6
    lw $t0, -4($fp)
    li $t1, 3
    slt $t2, $t1, $t0
    or  $t4, $t8, $t2
    beq $t4, $zero, Lelse_0
    .data
string_3: .asciiz "if-then: a > 3 is true, expected output"
    .text
    la $t5, string_3
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_1
Lelse_0:
Lend_1:
    lw $t6, -4($fp)
    li $t7, 3
    slt $t8, $t7, $t6
    sltiu $t0, $t8, 1
    beq $t0, $zero, Lelse_2
    .data
string_4: .asciiz "if-then-else: a < 3 (true branch), NOT expected output"
    .text
    la $t1, string_4
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_3
Lelse_2:
    .data
string_5: .asciiz "if-then-else: !(a > 3) is false -> else branch, expected output"
    .text
    la $t2, string_5
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lend_3:
    addi $sp, $sp, -4   # alloc local b (int)
    li $t3, 10
    sw $t3, -8($fp)
    .data
string_6: .asciiz "b is "
    .text
    la $t4, string_6
    move $a0, $t4
    li $v0, 4      # syscall for print_string
    syscall
    li $t5, 0     # output returns void (0)
    lw $t6, -8($fp)
    move $a0, $t6
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t7, -4($fp)
    lw $t8, -8($fp)
    slt $t9, $t7, $t8
    beq $t9, $zero, Lelse_4
    .data
string_7: .asciiz "nested if: a < b is true, expected output"
    .text
    la $t1, string_7
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t2, -8($fp)
    li $t3, 10
    subu $t5, $t2, $t3
    sltiu $t4, $t5, 1
    beq $t4, $zero, Lelse_6
    .data
string_8: .asciiz "nested if: inner check b == 10 is true, expected output"
    .text
    la $t6, string_8
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_7
Lelse_6:
    .data
string_9: .asciiz "nested else, NOT expected output"
    .text
    la $t7, string_9
    move $a0, $t7
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lend_7:
    j Lend_5
Lelse_4:
Lend_5:
    addi $sp, $sp, -4   # alloc local cond (bool)
    lw $t8, -4($fp)
    li $t9, 5
    slt $t1, $t9, $t8
    xori $t0, $t1, 1
    lw $t2, -8($fp)
    li $t3, 10
    slt $t5, $t2, $t3
    xori $t4, $t5, 1
    beqz $t0, Lfalse_8      # if first operand is 0, result is 0
    beqz $t4, Lfalse_8      # if second operand is 0, result is 0
    li $t6, 1         # both true, result is 1
    j Lend_9
Lfalse_8:
    li $t6, 0         # result is 0
Lend_9:
    sw $t6, -12($fp)
    .data
string_10: .asciiz "boolean expr (a <= 5 && b >= 10) => "
    .text
    la $t7, string_10
    move $a0, $t7
    li $v0, 4      # syscall for print_string
    syscall
    li $t8, 0     # output returns void (0)
    lw $t9, -12($fp)
    move $a0, $t9
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_11: .asciiz "Expected: 1"
    .text
    la $t0, string_11
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_12: .asciiz ""
    .text
    la $t1, string_12
    move $a0, $t1
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_13: .asciiz "=== Demo complete ==="
    .text
    la $t2, string_13
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t3, 0
    move $v0, $t3
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
    li $v0, 10
    syscall

end:
    j end
