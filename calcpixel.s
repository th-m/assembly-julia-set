                .global calcPixel

                .text

                twofivefive:	.double 255.0
                four:		.double	4.0
@ calcPixel(maxiters, col, row) -> rgb
@ S registers overlap d registers
@ used to convert from int to double
@ http://cit.dixie.edu/cs/2810/arm-assembly.html

calcPixel:
  	push	{ip,lr}		
  	mov	r3, #128	@store 128
  	fldd	d0, twofivefive	@loads 255
  	fldd	d1, four	@loads 4
  	fdivd	d2, d0, d1	@divides 255/4
  	sub	r1, r1, r3	@subtracts column - 128
  	sub	r2, r3, r2	@subtracts 128 - row
    @vmov	s0, r1		@moves r1 into s7
  	vmov	s7, r1		@moves r1 into s7
  	fsitod	d0, s7		@moves s7 into d0
  	@ move to d register for division
    @vmov	s3, r2		@moves r2 into s7
    vmov	s7, r2		@moves r2 into s7
  	fsitod	d1, s7		@moves s7 into d0
    @ store outputs in d0 and d1 for mandel
  	fdivd	d0, d0, d2	@divides (column-128)/(255/4)
  	fdivd	d1, d1, d2	@divides -(row-128)/(255/4)
  	bl	mandel		@branches to mandel
  	bl	getColor	@branches to getColor
  	pop	{ip,pc}		@pops register from the stack

