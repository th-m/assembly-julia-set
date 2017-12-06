  .global writeRGB

  .text
@writeRGB(buffer, color) -> number of bytes written
writeRGB:
  push	{r4,r5,r6,r7,r8,r9,r10,lr}	@saves the callie-saved registers to the stack
  @r0: buffer
  @r1: rgb value
  @r4: length of buffer
  @r5: buffer
  @r6: working rgb value
  @r7: rgb value
  @r8: green part
  @r9: red part
  @r10: blue part
1:
  mov	r4, #0			@moves buffer to a saved register
  mov	r5, r0			@moves buffer to a saved register
  mov	r7, r1			@moves rgb value to a saved register
  mov	r6, #0xff		@moves a mask into r6
  and	r8, r6, r7, lsr #8	@puts the green value into r8
  and	r9, r6, r7, lsr #16	@puts the red value into r9
  and	r10, r6, r7		@puts the blue value into r10
2:
  mov	r1, r9			@moves the red value into r1
  bl	itoa			@branches to itoa
  add	r4, r4, r0		@adds the number of bytes written to the buffer and the buffer length
  mov	r0, #' '		@moves a space character to r0
  strb	r0, [r5, r4]		@stores the space in the buffer
  add	r4, r4, #1		@adds one to the length of the buffer
  add	r0, r5, r4		@adds the buffer and its length to r0
3:
  mov	r1, r8			@moves the green value into r1
  bl	itoa			@branches to itoa
  add	r4, r4, r0		@adds the number of bytes written to the buffer and the buffer length
  mov	r0, #' '		@moves a space character to r0
  strb	r0, [r5, r4]		@stores the space in the buffer
  add	r4, r4, #1		@adds one to the length of the buffer
  add	r0, r5, r4		@adds the buffer and its length to r0
4:
  mov	r1, r10			@moves the blue value into r1
  bl	itoa			@branches to itoa
  add	r4, r4, r0		@adds the number of bytes written to the buffer and the buffer length
5:
  mov	r0, r4			@moves the total number of bytes written to r0
  pop	{r4,r5,r6,r7,r8,r9,r10,pc}	@restores the callie-saved registers
