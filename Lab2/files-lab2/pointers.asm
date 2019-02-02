
        # pointers.asm
# By David Broman, 2015-09-14
# This file is in the public domain


.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

.data


text1: 	  .asciiz "This is a string."
text2:	  .asciiz "Yet another thing."

.align 2
list1: 	.space 80
list2: 	.space 80
count:	.word  0

.text
main:
	jal	work
stop:	j	stop

# function work()
work:
	PUSH	($ra)
	# loading arguments for copycodes
	la 	$a0,text1 # arg1 pointer to string text1
	la	$a1,list1	# arg2 char[] list1
	la	$a2,count	# arg3 <datatype> count (int?)
	jal	copycodes	# calling copycodes
	# <void> copycodes has no return ($v0)
	la 	$a0,text2	# arg1 pointer to string text2
	la	$a1,list2	# arg2 char[] list2
	la	$a2,count	# arg3 <datatype> count
	jal	copycodes
	# <void> copycodes has no return ($v0)
	# <void> work has no return ($v0)
	POP	($ra)


# function copycodes()
copycodes:
# while loop with if statement in beq
loop:
	lb	$t0,0($a0)	# store char from string text
	beq	$t0,$0,done # while there is chars in text
	sw	$t0,0($a1)	# store word to list

	addi	$a0,$a0,1	# move to next byte (char) in string
	addi	$a1,$a1,4	# move to next word in list
# increment count by 1
	lw	$t1,0($a2)	#
	addi	$t1,$t1,1	# count++
	sw	$t1,0($a2)	#
	j	loop
done:
	jr	$ra
