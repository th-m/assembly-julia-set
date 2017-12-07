    .global mandel

    .text

    four:	.double 4.0

@ mandel(maxiters, x, y) -> iters
mandel:
  push	{ip,lr}
  @d0: x		@d4: a^2
  @d1: y		@d5: b^2
  @d2: a		@d6: a^2 + b^2
  @d3: b		@d7: 4.0
  @r0: iterations
  @r1: maxiters
1:
  fldd	d7, four	@loads 4.0 into d7
  mov	r1, r0		@copies maxIterations into r1
  mov	r0, #1		@sets r0 to 1
  fcpyd	d2, d0		@copies x into a
  fcpyd	d3, d1		@copies y into b
2:
  fmuld	d4, d2, d2	@a^2
  fmuld	d5, d3, d3	@b^2
  faddd	d6, d4, d5	@a^2 + b^ 2
  fcmpd	d6, d7		@compare a^2 + b^2 >= 4.0
  fmstat			@stores the double flags into the interger flags registers
  bge	3f		@exits the loop if d6 >= d7
  add	r0, r0, #1	@adds one to the iterations
  cmp	r0, r1		@compare iterations with maxIterations
  bgt	4f		@exits the loop if iters >= maxiters

  fmuld	d3, d3, d2	@a * b
  faddd	d3, d3, d3	@2ab
  faddd	d3, d3, d1	@b = 2ab + y and stores it as the new b

  fsubd	d2, d4, d5	@a^2 - b^2
  faddd	d2, d2, d0	@a^2 - b^2 + x and stores it as the new A
  b	2b		@loops back to lable 2
3:
  pop 	{ip,pc}		@returns the function if the mandle function exceeded 4
4:
  mov	r0, #0		@moves 0 into register 0
  pop	{ip,pc}		@returns the function
