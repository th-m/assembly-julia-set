writeRGB
========

Write an assembly language function to write a single color to a
buffer:

    writeRGB(buffer, color) -> number of bytes written

The color is encoded as a single integer value, with each color
channel using 8 bits. The least significant 8 bits comprise the blue
color channel, the next 8 bits the green channel, and the next 8
bits the red channel.

When written as a hexadecimal constant, the red, green, and blue
colors each use two hexadecimal digits and read from left to right.
For example:

* 0x112233

Is a color with 0x11 for the red value (17 in decimal), 0x22 for the
green value (34 in decimal), and 0x33 for the blue value (51 in
decimal).

The function should write these values to the buffer by calling
`itoa` on each value, and it should add spaces between the values
(but not at the end).

Note the calling conventions for ARM functions. When the function
is called, its parameters will be in these registers:

* r0: buffer (1st parameter)
* r1: rgb value (2nd parameter)

When writeRGB finishes, it should return the number of bytes written
to the buffer in the r0 register.


Registers
---------

Your implementation of `writeRGB` will make calls to `itoa`.
To prepare for a call to a function (`itoa` in this case), you
should place the first parameter value in r0 and the second in r1.
Then make the function call using:

    bl  itoa

When `itoa` returns, you should assume that any valus in r0–r3, r12,
and r14 have been overwritten. If you have values stored in these
caller-saved registers, you must save them before making the
function call. There are two basic approaches to this problem:

1.  Pick call-saved registers and use those instead. At the
    beginning of your function, you need to push the old
    contents of those registers to the stack, and you need to
    pop them again at the end before returning. In between, you can
    use them freely, and assume that their values remain consistent
    across function calls (since any function you call will save the
    value and restore it just like you are doing).

2.  Use the caller-saved registers, but save the values before
    making the function call and restore them afterward. In this
    approach, you push the values to the stack immediately before
    making a function call, and pop them off the stack right after.
    This does not replace your need to save callee-saved registers
    that you plan to use, it is just another occasion to spill
    register values onto the stack for temporary storage.


Shifts and masks
----------------

To extract parts of a single word, you need to think of the value as
a collection of bits, rather than as a single integer value. When
using `mov`, `add`, `orr`, `and`, etc., you can use the barrel
shifter to move values around. For example, to extract the green
part of a color, you could do the following. This assumes the entire
color value is in r7, and it puts just the green part into r6:

    mov r6, #0xff

This loads 0xff (called a *mask*) into r6, which is the number
11111111 (8 bits that are 1) in binary. When you `and` another value
with that number, it will leave those eight bits alone, and will set
all other bits in the word to zero. This instruction:

    and r6, r6, r7, lsr #8

takes the value in r7 and shifts it right either times. Since the
green part of the color normally occupies bits 8–15, this shifts
them into positions 0–7. It then performs the `and` operation with
the mask value, thus turning off all other bits and leaving only the
value of the green color channel in r6. The bits are also in the
right bit positions so that the green value will be between 0 and
255.

Similar code can be used to isolate the red part (shift right 16
times instead of 8) and the blue part (no shifting required, just
`and` with the mask value).


Testing
-------

To test your code as a standalone program, use the `_start` block
included in `start.s`.
