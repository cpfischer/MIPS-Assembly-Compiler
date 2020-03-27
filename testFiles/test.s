#=====================================================================
# INPUT:
#	a, b, c, d
# REGISTER ASSOCIATION:
#	$s0 = a
#	$s1 = b
#	$s3 = c
#	$s4 = d
# TEMPORARY REGISTERS USED:
# 
# OUTPUT:
# s0 = s3 = ((4a) - ((b + c) + 2a)) - (s4 - s1)
# s1 = user input
# s3 = user input
# s4 = user input
#=====================================================================

#######################################################
#
# text segment
#
#######################################################
		
		.text
		.globl main
		
main:		# s0 = a
	        # s1 =  b
	        # s3 = c
	        # s4 = d
		li	$v0, 5
		syscall
		move $s0, $v0		#s0 = v0 = a
		
		li	$v0, 5
		syscall
		move $s1, $v0		#s1 = v0 = b
		
		li	$v0, 5
		syscall
		move $s3, $v0		#s3 = v0 = c
		
		li	$v0, 5
		syscall
		move $s4, $v0		#s4 = v0 = d
							
							#t0 = s0
							#t1 = s1
							#t2 = t2
							#t3 = s3
							
		add $s3, $s1, $s3 	# s3 = s1 + s3 = b + c  
		add $s0, $s0, $s0	# s0 = s0 + s0 = 2a
		add $s3, $s3, $s0	# s3 = s3 + s0 = (b + c) + 2a
		sub $s4, $s4, $s1	# s4 = s4 - s1 = d - b
		add $s0, $s0, $s0 	# s0 = s0 + s0 = 4a
		sub $s3, $s0, $s3	# s3 = s0 - s3 = (4a) - ((b + c) + 2a)
		sub $s3, $s3, $s4	# s3 = s3 - s4 = ((4a) - ((b + c) + 2a)) - (s4 - s1)
		move $s0, $s3		# s0 = s3 = ((4a) - ((b + c) + 2a)) - (s4 - s1)
		
		move $a0, $s0		#a0 = s0 = a
		li 	 $v0, 1
		syscall
		
		li	$v0, 4
		la	$a0, NEWLINE	#print newline
		syscall
		
		move $a0, $s1		#a0 = s1 = b
		li 	 $v0, 1
		syscall
		
		li	$v0, 4
		la	$a0, NEWLINE	#print newline
		syscall
		
		move $a0, $s3		#a0 = s3 = c
		li 	 $v0, 1
		syscall
		
		li	$v0, 4
		la	$a0, NEWLINE	#print newline
		syscall
		
		move $a0, $s4		#a0 = s4 = d
		li 	 $v0, 1
		syscall
		
		li	$v0, 4
		la	$a0, NEWLINE	#print newline
		syscall
		
		li	$v0, 10			# exit
		syscall

######################################################################
#
# data Segment
#
######################################################################
.data
NEWLINE: .asciiz "\n"
