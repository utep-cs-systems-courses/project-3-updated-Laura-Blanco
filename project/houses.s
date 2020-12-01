	.arch msp430g2553
	.p2align 2
	.text

	.extern house_state
	
jt:
	.word choice0
	.word choice1
	.word choice2

	.global houses
houses:
	cmp.b #3, &house_state	;if variable is larger than or equal then exit
	jhs exit
	mov.b &house_state, r13	;r13 = house_state
	add.b r13,r13 		;x2
	mov jt(r13),r0

choice0:
	call #drawHouse
	mov.b #1, &house_state	;house_state = 1
	jmp exit		;break

choice1:
	mov.b #0,r12		;move for the function call
	call #House2
	mov.b #2, &house_state 	;house_state = 2
	jmp exit

choice2:
	mov.b #1,r12		;move 1 for function call to r12
	call #House2
	mov.b #0,&house_state	;house_state = 0
	jmp exit

exit:
	pop r0
	
