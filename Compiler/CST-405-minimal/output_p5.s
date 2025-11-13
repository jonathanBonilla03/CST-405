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
    li $t7, 3
    slt $t8, $t7, $t6
    beq $t8, $zero, Lelse_0
    .data
string_3: .asciiz "if-then: a > 3 is true"
    .text
    la $t0, string_3
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_1
Lelse_0:
Lend_1:
    lw $t1, -4($fp)
    li $t2, 3
    slt $t3, $t1, $t2
    beq $t3, $zero, Lelse_2
    .data
string_4: .asciiz "if-then-else: a < 3 (true branch)"
    .text
    la $t5, string_4
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_3
Lelse_2:
    .data
string_5: .asciiz "if-then-else: a < 3 is false -> else branch"
    .text
    la $t6, string_5
    move $a0, $t6
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
Lend_3:
    addi $sp, $sp, -4   # alloc local b (int)
    li $t7, 10
    sw $t7, -8($fp)
    .data
string_6: .asciiz "b is "
    .text
    la $t8, string_6
    move $a0, $t8
    li $v0, 4      # syscall for print_string
    syscall
    li $t9, 0     # output returns void (0)
    lw $t0, -8($fp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    slt $t3, $t1, $t2
    beq $t3, $zero, Lelse_4
    .data
string_7: .asciiz "nested if: a < b is true"
    .text
    la $t5, string_7
    move $a0, $t5
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t6, -8($fp)
    li $t7, 10
    subu $t9, $t6, $t7
    sltiu $t8, $t9, 1
    beq $t8, $zero, Lelse_6
    .data
string_8: .asciiz "nested if: inner check b == 10 is true"
    .text
    la $t0, string_8
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    j Lend_7
Lelse_6:
Lend_7:
    j Lend_5
Lelse_4:
Lend_5:
    addi $sp, $sp, -4   # alloc local cond (bool)
    lw $t1, -4($fp)
    li $t2, 5
    slt $t4, $t2, $t1
    xori $t3, $t4, 1
    lw $t5, -8($fp)
    li $t6, 10
    slt $t8, $t5, $t6
    xori $t7, $t8, 1
    beqz $t3, Lfalse_8      # if first operand is 0, result is 0
    beqz $t7, Lfalse_8      # if second operand is 0, result is 0
    li $t9, 1         # both true, result is 1
    j Lend_9
Lfalse_8:
    li $t9, 0         # result is 0
Lend_9:
    sw $t9, -12($fp)
    .data
string_9: .asciiz "boolean expr (a <= 5 && b >= 10) =>"
    .text
    la $t0, string_9
    move $a0, $t0
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    lw $t1, -12($fp)
    move $a0, $t1
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_10: .asciiz ""
    .text
    la $t2, string_10
    move $a0, $t2
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    .data
string_11: .asciiz "=== Demo complete ==="
    .text
    la $t3, string_11
    move $a0, $t3
    li $v0, 4
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t4, 0
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
    li $v0, 10
    syscall

end:
    j end
