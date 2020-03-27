#================================================================
# Filename:
# Author: Caleb Fischer
#
# Description
#  x + (y / (z + i)) * (t + t + t)
# Register usage:
# $s0 = x
# $s1 = y
# $s2 = z
# $s3 = i
# $s4 = t
#
# Temporary Registers:
# $t0 = t^2
#================================================================
		.text
		.globl main

main:	        li      $v0, 5 		# get int x
		syscall
		move	$s0, $v0	# $s0 = $v0 == x
		
		li		$v0, 5 		# get int y
		syscall
		move	$s1, $v0	# $s1 = $v0 == y
		
		li		$v0, 5 		# get int z
		syscall
		move	$s2, $v0	# $s2 = $v0 == z
		
		li		$v0, 5		# get int i
		syscall
		move	$s3, $v0	# $s3 = $v0 == i
	
		li		$v0, 5		# get int t
		syscall
		move	$s4, $v0	# $s4 = $v0 == t
		
		#================================
		# y / (z + i)
		#================================
		add		$s3, $s2, $s3	# $s3 = $s2 + $s3 == i = z + i
		div		$s1, $s3		# $s1 / $s3 == y / (z + i)
		mflo	$s1				# $s1 = quotient $s1 / $s3 == y / (z + i) 
		
		#================================
		# t ^ 3
		#================================
		mul		$t0, $s4, $s4	# $t0 = $s4 * $s4 = t^2
		mul		$s4, $t0, $s4	# $s4 = $t0 * $s4 = t^3
		
		#================================
		# x + (y / (z + i)) * t^3
		#================================
		mul		$s1, $s1, $s4	# $s1 = $s1 * $s4 == (y / (z + i)) * t^3
		add		$a0, $s0, $s1	# $a0 = $s0 + $s1 == x + (y / (z + i)) * t^3
		
		li		$v0, 1			# print a0
		syscall
		
		li		$v0, 10			# exit
		syscall
