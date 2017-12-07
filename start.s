@ The code in this file is just for testing purposes to help you make a
@ standalone program. It is not part of the assignment.

                .global _start
                .equ    sys_exit, 1

                .text
_start:
                @ call run
                bl      run

                @ exit system call
                mov     r7, #sys_exit
                svc     #0
