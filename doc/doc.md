writeHeader
===========

Write an assembly language function to write the header for a PPM
file to a buffer. More information about PPM files is available
here:

* [http://en.wikipedia.org/wiki/Netpbm_format](http://en.wikipedia.org/wiki/Netpbm_format)

For this function, the important part is the header, which has a
simple format:

```
P3
xsize ysize
colormax
```

The “P3” is hard-coded, and signals the format in use (this is
called a magic value). The xsize and ysize values are integers
written out as plain text, and indicate the size of the image in
pixels. The colormax value tells the maximum color value for each
color channel (red, green, and blue), and is hard-coded at 255 for
our purposes.

For a 1024×768 image, the header would be:

```
P3
1024 768
255
```

Which is the string: "P3\n1024 768\n255\n"

Your job is to write that header into a buffer, and return the
number of bytes written.

The function will take three parameters:

    writeHeader(buffer, xsize, ysize)

and return the number of bytes written to the buffer.


Registers
---------

Your implementation of `writeHeader` will make calls to `itoa`.
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


Testing
-------

To test your code as a standalone program, use the `_start` block
included in `start.s`.
