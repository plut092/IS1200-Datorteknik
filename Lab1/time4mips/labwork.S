# labwork.S
# Written 2015-2017 by F Lundevall
# Skeleton file for IS1200/IS1500 lab 1.
# The macros PUSH and POP are in the public domain.
# Please add your own code at the end of the file.
#
# Please keep the two macros PUSH and POP unchanged
#
.macro	PUSH reg
		addi		$sp,$sp,-4
		sw			\reg,0($sp)
.endm

.macro	POP reg
		lw			\reg,0($sp)
		addi		$sp,$sp,4
.endm
#
# Please add your own code below this line
#

.globl	delay
.globl	time2string
.text
delay:
		addi		$t0,$0,13400		# constant for how many iterations of the for-loop
		add			$t1,$0,$0				# variable i
														# $a0 is the variable for ms
		# test for negative number $a0
		slt			$t2,$a0,$0
		beq			$t2,1,delayEnd	# if $a0 < 0 then end delay
		nop
		j				delayWhileLoop
		nop
delayWhileLoop:
		beq			$a0,$0,delayEnd
		nop
		addi		$a0,$a0,-1
		j				delayForLoop
		nop

delayForLoop:
		beq			$t1,$t0, delayForEnd	# i = $t0 then stop for-loop
		nop
		addi		$t1,$t1,1				# increment variable i 	in for-loop
		j				delayForLoop
		nop
delayForEnd:
		add			$t1,$0,$0				# resets i = 0
		j				delayWhileLoop
		nop
delayEnd:
		jr			$ra
		nop


time2string:
		# $a0 output address from time2string.
		# $a1 contains time-info, only 16 lowest bits are used
# handeling x to output (x0:00)
		PUSH		$a0							# pushing the output address value to save it
		andi		$a0,$a1,0x0f000	# masking the bit from time-info
		srl			$a0,$a0,12			# shifting the value for the hexasc function
		PUSH		$a1							# Pushing values that needs to be saved during hexasc
		PUSH		$ra
		jal			hexasc					# converts numbers into hexascii symbols
		nop
		POP			$ra							# retrieving the saved values
		POP			$a1
		POP			$a0
		sb			$v0,0($a0)			# stores the byte with the offset of what place the number will have in the outputstring
		PUSH		$a0							# saves the output address value before next iteration
# handeling x to output (0x:00)
		andi		$a0,$a1,0x0f00	# 2nd iteration
		srl			$a0,$a0,8
		PUSH		$a1
		PUSH		$ra
		jal			hexasc
		nop
		POP			$ra
		POP			$a1
		POP			$a0
		sb			$v0,1($a0)
# loading : to output
		andi		$v0,$v0,0				# storing a : to output
		addi		$v0,$v0,0x3a
		sb			$v0,2($a0)
		PUSH		$a0
# handeling x to output(00:x0)
		andi		$a0,$a1,0x0f0		# 3rd iteration
		srl			$a0,$a0,4
		PUSH		$a1
		PUSH		$ra
		jal			hexasc
		nop
		POP			$ra
		POP			$a1
		POP			$a0
		sb			$v0,3($a0)
		PUSH		$a0
# handeling x to output (00:0x)
		andi		$a0,$a1,0x0f		# 4th iteration
		# check if the second is "9" then branches to time2stringNINE for lab assignment
		addi		$t0,$0,9				# temp variable for branching to time2stringNINE
		beq			$t0,$a0,time2stringNINE
		nop
		PUSH		$a1
		PUSH		$ra
		jal			hexasc
		nop
		POP			$ra
		POP			$a1
		POP			$a0
		sb			$v0,4($a0)
# null byte for end of string
		add			$v0,$0,$0
		sb			$v0,5($a0)
time2stringEnd:
		jr			$ra							# returns from the subrutine time2string
		nop
time2stringNINE:						# typing out xx:xNINE when the second is 9
		POP			$a0							# getting the return address from stack
		li			$v0,0x4e494e45	# puts NINE in variable
		sw			$v0,4($a0)			# store NINE in output address
		add			$v0,$0,$0				# put end of string (null byte) to variable
s		sb			$v0,8($a0)			#	store null byte in output address
		j				time2stringEnd
		nop
hexasc:
		andi		$a0,$a0,0x0f		# masking the 4 lsb, because only the 4 lsb are to be used
		addi		$t0,$0,10				# $t0 variable for slt check if $a0 < 10
		slt			$t1,$a0,$t0			# $t1 is set to 1 if $a0 < $t0
		beq			$t1,$0, hexascLetters # branching to handle numbers larger than 9
		nop
		addi		$v0,$a0,0x30		# starting at the value of ascii 0 with $a0 offset
		jr			$ra
		nop

hexascLetters:
		addi		$v0,$a0,0x37		# starting at the ascii symbol 10 places before of A with $a0 offset
		jr			$ra
		nop
