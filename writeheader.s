.global writeHeader

.equ color_magic, 255

.text
@writeHeader(buffer, xsize, ysize) -> number of bytes written
writeHeader:

push {r4,r5,r6,r7,lr}		@pushes the registers to the stack saving their values
  @r0: Buffer / Number to add to the buffer
  @r1: Xsize
  @r2: Ysize
  @r4: Buffer
  @r5: Length of Buffer
  @r6: ysize
  @r7: 255 color value
1:
  ldr	r7, =color_magic	@moves the color magic number into r7
  mov	r4, r0			@moves the buffer to r4, saving it
  mov	r6, r2			@moves ysize to r6, saving it
  mov	r5, #0			@sets the buffer length to 0
  
  mov	r0, #'P'		@moves a P into r0
  strb	r0, [r4,r5]		@stores P in the buffer
  add	r5, r5, #1		@adds 1 to the length of the buffer
  
  mov	r0, #'3'		@moves a 3 into r0
  strb	r0, [r4,r5]		@stores 3 in the buffer
  add	r5, r5, #1		@add one to the length of the buffer
  
  mov	r0, #'\n'		@moves a newline character into the buffer
  strb	r0, [r4,r5]		@stores the newline character in the buffer
  add	r5, r5, #1		@adds one to the buffer length
  add	r0, r4, r5		@adds the buffer and its length and stores it in r0
2:
  @r1 is already xsize
  bl	itoa			@Branches to the itoa function
  add	r5, r5, r0		@adds one to the length of the buffer
  mov	r0, #' '		@moves the newline character into r0
  strb	r0, [r4,r5]		@moves the newline character into the buffer
  add	r5, r5, #1		@adds one to the length of the buffer
  add	r0, r4, r5		@add the buffer and its length and stores it in r0
3:
  mov	r1, r6			@moves the ysize into r1
  bl	itoa			@branches to the itoa function
  add	r5, r5, r0		@adds one to the buffer length
  mov	r0, #'\n'		@moves the newline character into r0
  strb	r0, [r4,r5]		@stores the newline character into the buffer
  add	r5, r5, #1		@adds one to the length of the buffer
  add	r0, r4, r5		@adds the buffer and its length and stores it in r0
4:
  mov	r1, r7			@moves 255 into r1
  bl	itoa			@branches to the itoa function
  add	r5, r5, r0		@adds one to the length of the buffer
  mov	r0, #'\n'		@moves the newline character into r0
  strb	r0, [r4,r5]		@stores the newline character into the buffer
  add	r5, r5, #1		@adds one to the buffer length
  add	r0, r4, r5		@adds the buffer and its length and stores it in r0
5:
  mov	r0, r5			@moves the length of the buffer into r0
  pop	{r4,r5,r6,r7,pc}	@pops the register from the stack returning them to their original value
