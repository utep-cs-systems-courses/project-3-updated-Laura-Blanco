	.arch msp430g2553
	.p2align 2
	.text

	.extern led_changed
	.extern red_25
	.extern red_50
	.extern red_75
	
jt:
	.word case1
	.word case2
	.word case3

	.global dimmer
dimmer:
	sub #2, r1 		;make space for local variable
	mov.b #0, 0(r1)		;led = 0
	cmp.b #-4,r12 		;if light >= then finish
	jl end
	add.b r12,r12		;x2
	mov jt(r12),r0

case1:
	call #red_25		;call method
	mov.b r12,0(r1)		;move what was returned into led
	jmp end

case2:
	call #red_50
	mov.b r12,0(r1)		;move return value to led
	jmp end

case3:
	call #red_75
	mov.b r12,0(r1)
	jmp end

end:
	mov.b 0(r1), &led_changed ;led_changed = led
	call #led_update	  ;update led
	add #2, r1		  ;reset stack
	pop r0
