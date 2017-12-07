                .global getColor

                .text
@ getColor(iters) -> rgb
getColor:
                push    {ip,lr}
                @ make sure the input is < 256
                and     r0, r0, #0xff

                @ use r0 as all three color channels
                orr     r1, r0, r0, lsl #8
                orr     r0, r1, r0, lsl #16
                pop     {ip,pc}
