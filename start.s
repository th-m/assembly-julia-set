@ The code starting here is just to help you test writeHeader in a
@ standalone program. It is not part of the assignment.

                .global _start
                .equ    stdout, 1
                .equ    sys_write, 4
                .equ    sys_exit, 1

                .bss
buffer:         .space  100

                .text
_start:
                @ call writeHeader
                ldr     r0, =buffer
                mov     r1, #1024
                mov     r2, #768
                bl      writeHeader

                @ write the buffer to stdout
                mov     r2, r0
                mov     r0, #stdout
                ldr     r1, =buffer
                mov     r7, #sys_write
                svc     #0

                @ exit system call
                mov     r0, #0
                mov     r7, #sys_exit
                svc     #0
