.global run

.equ    flags, 577
.equ    mode, 0644
.equ    sys_write, 4
.equ    sys_open, 5
.equ    sys_close, 6

.equ    fail_open, 1
.equ    fail_writeheader, 2
.equ    fail_writerow, 3
.equ    fail_close, 4

.text

@ run() -> exit code
run:
push	{r4,r5,r6,r7,r8,r9,r10,r11,ip,lr}
  @r0: first parameter for the system call
  @r1: second parameter for the system call
  @r2: third parameter for the system call
  @r4: file descriptor
  @r5: buffer length
  @r6: buffer
  @r7: value of the system call 
  @r8: column size
  @r9: row size
  
@fd = open(filename, flags, mode)
@if fd < 0: return 1 (open failed)
1:
  ldr	r0, =filename		@loads the filename into register 0
  ldr	r1, =flags		@loads flags value into register 1
  ldr	r2, =mode		@loads mode value into register 2
  mov	r7, #sys_open		@loads sys_open into register 7
  svc	#0			@calls to the system call
  cmp	r0, #0			@compares the return to 0
  mov	r4, r0			@moves the file descriptor to r4
  bge	2f			@branches if call didnt fail
  mov	r0, #fail_open		@if call failed move fail code into standard out
  pop	{r4,r7,ip,pc}		@pops register from the stack


2:
  ldr	r0, =buffer		@moves the buffer into register 0
  ldr	r1, =xsize		@moves the address of xsize into register 1
  ldr	r2, =ysize		@moves the address of ysize into register 2
  ldr	r1, [r1]		@moves the value of xsize into register 1
  ldr	r2, [r2]		@moves the value of ysize into register 2
  bl	writeHeader		@branches to writeHeader
  mov	r2, r0			@stores the buffer length into register 2
  mov	r0, r4			@moves the file descriptor into register 4
  ldr	r1, =buffer		@moves the buffer into register 1
  mov	r7, #sys_write		@moves sys_write into register 7
  svc	#0			@calls to the system call
  mov	r7, #0			@moves a 0 into register 7
  @mov	r9, #0			@moves a 0 into register 9
  mov	r10, #0			@moves a 0 into register 9
  cmp	r0, #0			@compares the return to 0
  bge	3f			@branches if the call didnt fail
  @ NOTE reset r5, r2, and r8 for row loop
  @mov r0, #0
  @ldr r5, =buffer @ store buffer in r5
  @@mov r4, r2
  @mov r9, #0 @ reset length of buffer back to 0
  @mov r8, #0 @length = 0
  @
  @bge	4f			@branches if the call didnt fail
  mov	r0, #fail_writeheader	@if call failed move fail code into standard out
  pop	{r4,r7,r9,pc}		@pops register from the stack

@bufsize = 0
@for column from 0 to xsize - 1 inclusive
@color = column << 8@color = column shifted left 8 bits
@bufsize += writeRGB(buffer + bufsize, color)
@buffer[bufsize] = ' '
@bufsize += 1
3:
  @mov r7, r8, lsl #8 @r7
  @mov r10, r11, lsl #16
  @mov r1, r8, lsl #8
  @mov r1, r8, lsl #8
  @add r0, r9, r5 @adds the buffer and the length of the buffer and stores it in register 0
  @bl writeRGB @returns total length of bytes writtn in r0
  @add r9, r9, r0
  @mov r7, #' ' @ buffer[length] = ' '
  @strb r7, [r5, r9] @adds one to register 7
  @add r9, r9, #1 @length += 1
  @add r8, r8, #1
  ldr	r0, =iters		@moves memory of iters into r0
  ldr	r0, [r0]		@moves value of r0 into r0
  mov	r1, r7			@moves column into r1
  @mov	r2, r9			@moves row into r2
  mov	r2, r10			@moves row into r2
  bl	calcPixel		@branches to calcPixel
  mov	r1, r0			@moves the return to register 1
  ldr	r11, =buffer		@moves the buffer into register 6
  add	r0, r11, r5		@moves the buffer and its size into register 0
  bl	writeRGB		@branches to writeRGB function
  add	r5, r5, r0		@adds the output and the length of the buffer and stores it in register 5
  mov	r0, #' '		@adds a blank space to register 0
  strb	r0, [r11, r5]		@stores the value in register 0 in the buffer at position register 5
  add	r5, r5, #1		@adds one to the length of the buffer
  add	r7, r7, #1		@adds one to register 7
  ldr	r1, =xsize		@loads xsize into register 1
  ldr	r1, [r1]		@loads the value of xsize into register 1
  cmp	r1, r7			@compares register 7 with register 1
  bgt	3b			@branches if register 7 is greater than or equal to register 1


4:
  @ add r8, r8, #1
  @ldr r7, =xsize @loads xsize into register 1
  @ldr r7, [r7]
  @sub r7, r7, #1
  @cmp r8, r7 @ compares register 7 with register 1
  @ble 3b

  mov	r0, #'\n'		
  sub	r1, r5, #1		
  strb	r0, [r11, r1]		
  mov	r0, r4			
  ldr	r1, =buffer		
  mov	r2, r5		
  mov	r7, #sys_write		
  svc	#0			
  cmp	r0, #0			
  bge	5f			
  mov	r0, #fail_writerow	
  pop	{r4,r5,r6,r7,r8,r9,r10,r11,ip,pc}

5:
  mov	r5, #0			@resets the length of the buffer to 0
  mov	r7, #0			@resets the column variable to 0
  @add	r9, r9, #1		@adds one to the row variable
  add	r10, r10, #1		@adds one to the row variable
  ldr	r8, =ysize		@loads in ysize for compatrison
  ldr	r8, [r8]		@loads in ysize for comparison
  cmp	r10, r8			@compares ysize with the row variable
  blt	3b			@branches to the start of the loop if r9 is less than r8


6:
  mov	r0, r4			@moves the file descriptor into register 0
  mov	r7, #sys_close		@moves sys_close into register 7
  svc	#0			@executes a call to the system
  cmp	r0, #0			@compares the return to 0
  bge	7f			@branches if the call didnt fail
  mov	r0, #fail_close		@if the call failed, move fail code into standard out
  pop	{r4,r5,r6,r7,r8,r9,r10,r11,ip,pc}	@pops register from the stack

@return 0 (success)
7:
  mov	r0, #0			@moves 0 into register 0
  pop	{r4,r5,r6,r7,r8,r9,r10,r11,ip,pc}	@pops register from the stack

    .bss
buffer:			.space 64*4096
