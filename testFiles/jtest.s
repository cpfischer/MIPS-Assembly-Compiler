

		.text
		.globl main
		
main:	li	$s0, 6
		li	$s1, 1
		
Loop:	bgt	$s1, $s0, EXIT
		add	$s1, $s1, $s1
		j	Loop

EXIT:	li $v0, 10
		syscall