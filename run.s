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
	push	{r4,r5,r6,r7,r8,r9,ip,lr}
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
@ r0,1,2,7 used for svc
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


@bufsize = writeHeader(buffer, xsize, ysize)
@status = write(fd, buffer, bufsize)
@if status < 0: return fail_writeheader
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
	mov	r9, #0			@moves a 0 into register 9
	cmp	r0, #0			@compares the return to 0
	bge	3f			@branches if the call didnt fail
	mov	r0, #fail_writeheader	@if call failed move fail code into standard out
	pop	{r4,r7,r9,pc}		@pops register from the stack

@ write a single row of pixels
3:
  mov r5, #0 @length = 0
  
  bl writeRGB @length += writeRGB
  add r5, r5, r0 @adds the output and the length of the buffer and stores it in register 5
  mov r0, #' ' @ buffer[length] = ' '
  strb r0, [r6, r5] @buffer[length] = r0 val to store =' ' [(store in buffer) and at (position)]
  add r5, r5, #1 @length += 1
  
  add r7, r7, #1 @adds one to register 7
  ldr r1, =xsize @loads xsize into register 1
  ldr r1, [r1] @ loads teh value of xsize into register 1
  cmp r1, r7 @ compares register 7 with register 1
  bgt 3b  @branches if register 7 is greater tahn or equal to register 1
@status = close(fd)
@if status < 0: return f ail_close
4:
  mov r5, #'\n'
  sub r1, r5, #1
  strb r0, [r6, r1]
  @mov	r2, r0			@stores the buffer length into register 2
	mov	r0, r4			@moves the file descriptor into register 4
	ldr	r1, =buffer		@moves the buffer into register 1
  mov r2, r5
	mov	r7, #sys_write		@moves sys_write into register 7
	svc	#0			@calls to the system call
  cmp r0, #0
  bge 6f
  mov r0, #fail_writerow
  pop   {r4,r5,r6,r7,r8,r9,ip,pc} @pops register from the stack
  
  
6:
	mov	r0, r4			@moves the file descriptor into register 0
	mov	r7, #sys_close		@moves sys_close into register 7
	svc	#0			@executes a call to the system
	cmp	r0, #0			@compares the return to 0
	bge	7f			@branches if the call didnt fail
	mov	r0, #fail_close		@if the call failed, move fail code into standard out
	pop	{r4,r5,r6,r7,r8,r9,ip,pc}	@pops register from the stack
  
7:
  mov   r0, #0       @moves 0 into register 0 it says 
  pop   {r4,r5,r6,r7,r8,r9,ip,pc} @pops register from the stack
  

                .bss
buffer:         .space 64*1024
