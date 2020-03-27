##################################################
        .globl text
        .text
main:
        li $v0, 5
	syscall
	move $s0, $v0		#s0 = v0 = a
		
        li $v0, 10
        syscall

        .data
HELLO:  .asciiz "\n"
