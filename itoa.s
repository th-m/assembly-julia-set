			.global	itoa

			.equ	div10_magic, 0xcccccccd
                       
			.text
@ itoa(buffer, n) -> number of bytes written
itoa:
			push	{r4,r5,r6,r7,r8,lr}
			@ r0: buffer
			@ r1: n
			@ r2: length of output
			@ r3: division magic number
			@ r4: digit
			@ r5: new n
			@r6: i
			@r7: j
			@r8: temp j
			ldr	r3, =div10_magic
			mov	r2, #0
1:                      
			@ do a division by 10
			umull	r4, r5, r3, r1        @ multiply by magic number
			mov	r5, r5, lsr #3        @ shift: new_n is in r5
			add	r4, r5, r5, lsl #2    @ compute new_n*5
			sub	r4, r1, r4, lsl #1    @ remainder = n - new_n*5*2
			add	r4, r4, #'0'          @ convert to a digit
			strb	r4, [r0, r2]          @ store in buffer
			add	r2, r2, #1            @ length++
			subs	r1, r5, #0            @ n = new and compare with 0
			bgt	1b
			
			@ r3: i
			@ r4: j
			@ r1: temp_a
			@ r5: temp_b
															@ i = 0
															@ j = len(buffer)-1
															@ goto test (3):
2:
			mov	r6, #0
			mov	r8, r2
			sub	r7, r8, #1
3:
			ldrb	r4, [r0,r6]			@ ldrb(load byte)load position r6(0) of r0(buffer--string) into r4 
			ldrb	r5, [r0,r7]			@ load position r7(len-1) of r0(buffer--string) into r5 
			strb	r4, [r0,r7]			@ strb(store byte) store r4 into r7 of r0(buffer--string)
			strb	r5, [r0,r6]			@ strb(store byte) store r5 into r6 of r0(buffer--string)
			add	r6, r6, #1				@ (store, v1, v2) add 1 to increment floor iterator
			sub	r7, r7, #1				@ (store, v1, v2) sub 1 to increment ciel iterator
			cmp	r6, r7						@ set some flags
			ble	3b								@ branch less than or equal (if i less than or equal to 7 switch) 3b (label 3, b is back)
4:
			mov	r0, r2
			pop	{r4,r5,r6,r7,r8,pc}
                      
