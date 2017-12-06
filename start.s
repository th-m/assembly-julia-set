@ The code starting here is just to help you test mandel in a
@ standalone program. It is not part of the assignment.

                .global _start
                .equ    sys_exit, 1

                .text
_start:
                mov     r0, #100

                @ load the first test case below
                @ change these two lines to use a different test case
                fldd    d0, x1
                fldd    d1, y1
                bl      mandel

                @ exit system call
                @ use mandel's return value as the exit status code
                mov     r7, #sys_exit
                svc     #0

                @ this is the default test case
                @ test this first: mandel should return 2
x1:             .double -1.4
y1:             .double 1.4

                @ this is a test case inside the set
                @ test this second: mandel should return 0
x2:             .double -0.21
y2:             .double -0.62

                @ this is a test case near the edge
                @ test this third: mandel should return 68
x3:             .double 0.27
y3:             .double 0.61
