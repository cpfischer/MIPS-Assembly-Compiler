.text
.globl main

la $s0, J1
sw $s0, JTABLE
lw $s1, JTABLE
jr $s1

move $a0, $s1
li $v0, 1
syscall
        
li $v0, 10
syscall
        
la $s0, J2
la $s3, JTABLE
sw $s0, 4($s3)
lw $s1, 4($s3)
jr $s1



lw $a0, H
li $v0, 4
syscall
        
la $s0, J3
la $s3, JTABLE
sw $s0, 8($s3)
lw $s1, 8($s3)
jr $s1
                        



