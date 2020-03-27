#================================================================
# Filename: a04q07.s
# Author: Caleb Fischer
#
# Description
# Goes through user input and prints the second largest number
#
# Register usage:
# a0, t0, t1, t2, s0, s1, s2, s3, s4, s5
# 
# t0 = 100s place
# t1 = divide by 10
# t2 = tens carry
# s0 = 10s place 1st number
# s1 = 1s place 1st number
# s2 = 10s place 2nd number
# s3 = 1s place 2nd number
# s4 = answer 10s place
# s5 = answer 1s place
#================================================================

#################################################################
#
# text segment
#
#################################################################
			.text
			.globl main
	
main:		li		$t0, 0		# t0 = hundreds place
			li		$t1, 10		# for division
			
			li		$v0, 5
			syscall
			move 	$s0, $v0	# loads s0 with first user input, a
		
			li		$v0, 5
			syscall
			move 	$s2, $v0	# loads s2 with second user input, b	

			div		$s0, $t1	# divide s0 by 10 to get HI, LO
			mflo	$s0			# move quotient of s0 / 10 into s0
			mfhi	$s1			# move s0 % 10 into s1
			
			div		$s2, $t1	# divide s2 by 10 to get HI, LO
			mflo	$s2			# move quotient of s2 / 10 into s2
			mfhi	$s3			# move s2 % 10 into s3
									
			# s0 = 10s place, s1 = ones
			# s2 = 10s place, s3 = ones
			# s4 = answer 10s, s5 = answer 1s
			# t2 = tens carry, t1 = 10
			add		$s5, $s1, $s3	# s5 = answer one place
			blt		$s5, 10, ELSE1	# jump to ELSE if s5 < 10
			
			div		$s5, $t1		# takes 10 out of s5			
			mfhi	$s5				# s5 = s5 % 10
			li		$t2, 1			# 10s carry = true, add later
			
			la 		$a0, space	# prints remainder line at top
			li		$v0, 4		# print string
			syscall
			la 		$a0, space
			li		$v0, 4		# print string
			syscall
			
			li 		$a0, 1		# prints 1
			li		$v0, 1		# print a0
			syscall
			la 		$a0, nl
			li		$v0, 4		# print a0
			syscall

			# add 10s place
ELSE1:		add 	$s4, $s0, $s2   # s4 = answer 10s place
			add		$s4, $s4, $t2	# add carry to s4
			
			blt		$s4, 10, ELSE2  # branch to s2 if s4 < 10
	
			div		$s4, $t1		# takes 10 out of s4			
			mfhi	$s4				# s4 = s4 % 10
			li		$t0, 1			# t0 = remainder, 100s place
			
			# printing
ELSE2:		la 		$a0, space
			li		$v0, 4			# print string
			syscall
			
			la 		$a0, space
			li		$v0, 4		# print string
			syscall
			
			move 	$a0, $s0    # prints 10s place of a
			li		$v0, 1		# print a0
			syscall
			
			la 		$a0, space	# space
			li		$v0, 4		# print string
			syscall
			
			move 	$a0, $s1    # prints 1s place of a
			li		$v0, 1		# print a0
			syscall
			
			la 		$a0, nl 	# newline
			li		$v0, 4		# print string
			syscall
			
			####################################
			# second number
			####################################
			la 		$a0, plus	# plus
			li		$v0, 4		# print string
			syscall
			la 		$a0, space	# space
			li		$v0, 4		# print string
			syscall
			
			move 	$a0, $s2    # prints 10s place of b
			li		$v0, 1		# print a0
			syscall
			
			la 		$a0, space	# space
			li		$v0, 4		# print string
			syscall
			
			move 	$a0, $s3    # prints 1s place of b
			li		$v0, 1		# print a0
			syscall
			
			la 		$a0, nl 	# newline
			li		$v0, 4		# print string
			syscall
			
			la		$a0, equals # equals line
			li		$v0, 4		# print string
			syscall
			
			la 		$a0, nl 	# newline
			li		$v0, 4		# print string
			syscall
			####################################
			# answer
			####################################
			bne		$t0, 1, ELSE3	# jump to print space if no hundreds
			move 	$a0, $t0    	# prints 100s place of answer
			li		$v0, 1			# print a0
			syscall
			j		ELSE4		# skip the second space
			
ELSE3:		la 		$a0, space	# space
			li		$v0, 4		# print string
			syscall

ELSE4:		la 		$a0, space	# space
			li		$v0, 4		# print string
			syscall
			
			move 	$a0, $s4    # prints 10s place of answer
			li		$v0, 1		# print a0
			syscall
			
			la 		$a0, space	# space
			li		$v0, 4		# print string
			syscall
			
			move 	$a0, $s5    # prints 1s place of answer
			li		$v0, 1		# print a0
			syscall
			
			la 		$a0, nl 	# newline
			li		$v0, 4		# print string
			syscall
			
			la		$a0, equals # equals line
			li		$v0, 4		# print string
			syscall
		
			li		$v0, 10		# exit
			syscall
		
#################################################################
# 
# data segment 
# 
#################################################################
			.data
space:		.asciiz " "
plus:		.asciiz "+"
equals:		.asciiz "-----"
nl:		.asciiz "\n"
