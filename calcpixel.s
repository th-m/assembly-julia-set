                .global calcPixel

                .text

                twofivefive:	.double 255.0
                four:		.double	4.0
@ calcPixel(maxiters, col, row) -> rgb
calcPixel:
  	push	{ip,lr}		@pushes registers to the stack
  	mov	r3, #128	@moves 128 into register 3
  	fldd	d0, twofivefive	@loads into d0 255
  	fldd	d1, four	@loads into d1 4
  	fdivd	d2, d0, d1	@divides 255/4
  	sub	r1, r1, r3	@subtracts column - 128
  	sub	r2, r3, r2	@subtracts 128 - row
  	vmov	s7, r1		@moves r1 into s7
  	fsitod	d0, s7		@moves s7 into d0
  	vmov	s7, r2		@moves r2 into s7
  	fsitod	d1, s7		@moves s7 into d0
  	fdivd	d0, d0, d2	@divides (column-128)/(255/4)
  	fdivd	d1, d1, d2	@divides -(row-128)/(255/4)
  	bl	mandel		@branches to mandel
  	bl	getColor	@branches to getColor
  	pop	{ip,pc}		@pops register from the stack

