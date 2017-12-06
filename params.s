                .global filename, xsize, ysize, iters
                .data

filename:       .asciz  "fractal.ppm"

                .balign
xsize:          .word   256
ysize:          .word   256
iters:          .word   255
