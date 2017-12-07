@ The code starting here is just to help you test your code in a
@ standalone program. It is not part of the assignment.

                .global _start
                .equ    sys_exit, 1

                .text
_start:
                @ set maxiters parameter to 255
                mov     r0, #255

                @ load the first test case below
                @ change these two lines to use a different test case
                mov     r1, #col1
                mov     r2, #row1
                bl      calcPixel

                @ exit system call
                @ use the blue color channel as the exit status code
                and     r0, r0, #0xff
                mov     r7, #sys_exit
                svc     #0

                @ this is the default test case for a point inside the set
                @ test this first: calcPixel should return 0
                .equ    col1, 142
                .equ    row1, 113

                @ this is a test case with a low number of iterations
                @ test this second: calcPixel should return 0x010101
                @ and the exit status code should be 1
                .equ    col2, 210
                .equ    row2, 30

                @ this is a test case with a higher number of iterations
                @ test this third: calcPixel should return 0x373737
                @ and the exit status code should be 55
                .equ    col3, 139
                .equ    row3, 90
