                .global filename, xsize, ysize, iters
                .data

filename:       .asciz  "fractal.ppm"

                .balign
xsize:          .word   1024
ysize:          .word   768
iters:          .word   255
