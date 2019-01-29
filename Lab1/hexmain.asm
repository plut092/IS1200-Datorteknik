  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,-1		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
hexasc:
	andi	$a0,$a0,0x0f	# masking the 4 lsb, because only the 4 lsb are to be used
	addi	$t0,$0,10	# $t0 variable for slt check if $a0 < 10
	slt	$t1,$a0,$t0	# $t1 is set to 1 if $a0 < $t0
	beq	$t1,$0 hexascLetters # branching to handle numbers larger than 9
	nop
	addi	$v0,$a0,0x30	# starting at the value of ascii 0 with $a0 offset
	jr	$ra
	
hexascLetters:
	addi	$v0,$a0,0x37	# starting at the ascii symbol 10 places before of A with $a0 offset
	jr $ra

	# 17 = 10001 is masked to 0001 so because of overflow it's read as 1
