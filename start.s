@ The code starting here is just to help you test writeRGB in a
@ standalone program. It is not part of the assignment.

                .global _start
                .equ    stdout, 1
                .equ    sys_write, 4
                .equ    sys_exit, 1

                .bss
buffer:         .space  100

                .text
_start:
                @ call writeRGB
                ldr     r0, =buffer
                ldr     r1, =0x112233
                bl      writeRGB

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
