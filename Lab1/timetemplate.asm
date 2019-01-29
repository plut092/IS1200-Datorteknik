# timetemplate.asm
# Written 2015 by F Lundevall
# Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
addi	$sp,$sp,-4
sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
lw	%reg,0($sp)
addi	$sp,$sp,4
.end_macro

.data
.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
.text
main:
# print timstr
la	$a0,timstr
li	$v0,4
syscall
nop
# wait a little, 2 has constant of 265 for a second. 900 constant for 1000ms
li	$a0,1000
jal	delay
nop
# call tick
la	$a0,mytime
jal	tick
nop
# call your function time2string
la	$a0,timstr
la	$t0,mytime
lw	$a1,0($t0)
jal	time2string
nop
# print a newline
li	$a0,10
li	$v0,11
syscall
nop
# go back and do it all again
j	main
nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
addiu	$t0,$t0,1	# increase
andi	$t1,$t0,0xf	# check lowest digit
sltiu	$t2,$t1,0xa	# if digit < a, okay
bnez	$t2,tiend
nop
addiu	$t0,$t0,0x6	# adjust lowest digit
andi	$t1,$t0,0xf0	# check next digit
sltiu	$t2,$t1,0x60	# if digit < 6, okay
bnez	$t2,tiend
nop
addiu	$t0,$t0,0xa0	# adjust digit
andi	$t1,$t0,0xf00	# check minute digit
sltiu	$t2,$t1,0xa00	# if digit < a, okay
bnez	$t2,tiend
nop
addiu	$t0,$t0,0x600	# adjust digit
andi	$t1,$t0,0xf000	# check last digit
sltiu	$t2,$t1,0x6000	# if digit < 6, okay
bnez	$t2,tiend
nop
addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
jr	$ra		# return
nop

# you can write your code for subroutine "hexasc" below this line

delay:
addi	$t0,$0,500	# constant for how many iterations of the for-loop
add	$t1,$0,$0	# variable i
      # $a0 is the variable for ms
# test for negative number $a0
slt	$t2,$a0,$0
beq	$t2,1,delayEnd	# if $a0 < 0 then end delay
nop
j	delayWhileLoop
nop
delayWhileLoop:
beq	$a0,$0,delayEnd
nop
addi	$a0,$a0,-1
j	delayForLoop
nop

delayForLoop:
beq	$t1,$t0, delayForEnd	# i = $t0 then stop for-loop
nop
addi	$t1,$t1,1	# increment variable i 	in for-loop
j	delayForLoop
nop
delayForEnd:
add	$t1,$0,$0	# resets i = 0
j	delayWhileLoop
nop
delayEnd:
jr	$ra
nop


time2string:
# $a0 output address from time2string.
# $a1 contains time-info, only 16 lowest bits are used
# handeling x to output (x0:00)
PUSH	($a0)		# pushing the output address value to save it
andi	$a0,$a1,0x0f000	# masking the bit from time-info
srl	$a0,$a0,12	# shifting the value for the hexasc function
PUSH	($a1)		# Pushing values that needs to be saved during hexasc
PUSH	($ra)
jal	hexasc		# converts numbers into hexascii symbols
nop
POP	($ra)		# retrieving the saved values
POP	($a1)
POP	($a0)
sb	$v0,0($a0)	# stores the byte with the offset of what place the number will have in the outputstring
PUSH	($a0)		# saves the output address value before next iteration
# handeling x to output (0x:00)
andi	$a0,$a1,0x0f00	# 2nd iteration
srl	$a0,$a0,8
PUSH	($a1)
PUSH	($ra)
jal	hexasc
nop
POP	($ra)
POP	($a1)
POP	($a0)
sb	$v0,1($a0)

#loading : to output
andi	$v0,$v0,0	# storing a : to output
addi	$v0,$v0,0x3a
sb	$v0,2($a0)
PUSH	($a0)

# handeling x to output(00:x0)
andi	$a0,$a1,0x0f0	# 3rd iteration
srl	$a0,$a0,4
PUSH	($a1)
PUSH	($ra)
jal	hexasc
nop
POP	($ra)
POP	($a1)
POP	($a0)
sb	$v0,3($a0)
PUSH	($a0)

# handeling x to output (00:0x)
andi	$a0,$a1,0x0f	# 4th iteration
PUSH	($a1)
PUSH	($ra)
jal	hexasc
nop
POP	($ra)
POP	($a1)
POP	($a0)
sb	$v0,4($a0)

# null byte for end of string
add	$v0,$0,$0
sb	$v0,5($a0)

jr	$ra		# returns from the subrutine time2string
nop


hexasc:
andi	$a0,$a0,0x0f	# masking the 4 lsb, because only the 4 lsb are to be used
addi	$t0,$0,10	# $t0 variable for slt check if $a0 < 10
slt	$t1,$a0,$t0	# $t1 is set to 1 if $a0 < $t0
beq	$t1,$0 hexascLetters # branching to handle numbers larger than 9
nop
addi	$v0,$a0,0x30	# starting at the value of ascii 0 with $a0 offset
jr	$ra
nop

hexascLetters:
addi	$v0,$a0,0x37	# starting at the ascii symbol 10 places before of A with $a0 offset
jr $ra
nop

# 17 = 10001 is masked to 0001 so because of overflow it's read as 1
