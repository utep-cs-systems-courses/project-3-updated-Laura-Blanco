	.arch msp430g2553
	.p2align 2
	.text

	.extern red_on
	.extern dim_state

jt:
	.word option0
	.word option1

	.global red_50
red_50:
	cmp.b #2, &dim_state 	;if dim_state is >= 2 end
	jhs done
	mov.b &dim_state, r13	;r13 = dim_state
	add.b r13,r13		;x2
	mov jt(r13),r0
	
option0:
	mov.b #1, &red_on 	;red_on = 1
	mov.b #1, &dim_state 	;dim_state = 1
	jmp done

option1:
	mov.b #0, &red_on	;red_on = 0
	mov.b #0, &dim_state	;dim_state = 0
	jmp done

done:
	mov.b #1,r12		;to return
	pop r0			;return
