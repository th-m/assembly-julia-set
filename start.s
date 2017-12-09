@ The code starting here is just to help you test your code in a
@ standalone program. It is not part of the assignment.

                .global _start
                .equ    sys_exit, 1

                .text
_start:
                @ load a test case for remainder
                ldr     r0, =num1
                ldr     r1, =den1
                bl      remainder

                mov     r7, #sys_exit
                svc     #0

                @ this is the default test case
                @ test this first: remainder should return 5
                @ and the exit status code should be 5
                .equ    num1, 25
                .equ    den1, 20

                @ test this second: remainder should return 2
                @ and the exit status code should be 2
                .equ    num2, 57
                .equ    den2, 5

                @ test this third: remainder should return 37
                @ and the exit status code should be 37
                .equ    num3, 1234567
                .equ    den3, 87
