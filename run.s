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

@ your code goes here


                .bss
buffer:         .space 64*1024
