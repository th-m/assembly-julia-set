calcPixel
=========

`mandel` works on floating point coordinates, but you must generate
an image with discrete pixels. In the next step you will calculate
points based on their location in a 256×256 image centered at the
origin. You will also convert the number of iterations into a shade
of gray.

Once this step is complete, you will have the functionality required
to compute a pixel color for each point in a complete image.


The parameters
--------------

To simplify the computation, you will assume that the image to be
generated is 256×256 pixels, and it will compute a Mandelbrot image
centered at the origin with 0.25 magnification. We will save the
details for the next project, but for now this means that you can
convert a pixel coordinate (a column and row number) to complex
plane coordinates (x and y float values) as follows:

* x = (column - 128) / (255.0 / 4.0)
* y = -(row - 128) / (255.0 / 4.0)


The code
--------

In `calcpixel.s`, write the function calcPixel, which should work
as follows:

* `calcPixel(maxIterations, column, row)` → `rgb`

`calcPixel` converts the column and row numbers into *x* and *y*
coordinates as indicated above, then calls `mandel` to compute the
number of iterations. It then passes the number of iterations to
`getColor` (which is provided) to get an RGB color value.

Since `calcPixel` needs to call `mandel`, it must pass double values
as parameters. Just as `mandel` expects its first two double
parameters to be in d0 and d1 when it is called, `calcPixel` must
put those parameters in those registers before calling `mandel`.

`getColor` is a simple function that copies its input value (the
number of iterations) into the red, green, and blue channels of a
single RGB value, resulting in a shade of gray. A pixel with few
iterations will be a dark shade of gray, and one with close to 255
iterations will be very close to white. This function is a
placeholder—in a later project this function will look up a color
from a palette.

Note that both *x* and *y* require division with a divisor of (255.0
/ 4.0). I suggest computing this value once at the beginning of
`calcPixel` (store it in one of the `d` registers) and then use it in
the computation of *x* and *y*.

Note: you should not need to modify `getcolor.s` at all for this
project.


Testing
-------

A `start.s` file is provided. It will call `calcPixel` with a simple
test case, and will use the blue color value of the return value of
`calcPixel` as the exit status code. For the default test case, you
should expect an exit status code of 0. When you run the code with
`make run` or `grind action run`, make should report this as a
success. For example:

    $ make run
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp getcolor.s -o getcolor.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp calcpixel.s -o calcpixel.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp start.s -o start.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp mandel.s -o mandel.o
    ld --fatal-warnings getcolor.o calcpixel.o start.o mandel.o
    ./a.out

When you get that much working, change `start.s` to load `col2` and
`row2` instead of `col1` and `row1` as the test values when it calls
`calcPixel`. The expected output for this case is 1 (the point at
that location escapes the threshold value after a single iteration),
so your code should return the color value `0x010101`. make will
report the blue part of this color as the error number:

    $ make run
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp getcolor.s -o getcolor.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp calcpixel.s -o calcpixel.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp start.s -o start.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp mandel.s -o mandel.o
    ld --fatal-warnings getcolor.o calcpixel.o start.o mandel.o
    ./a.out
    Makefile:20: recipe for target 'run' failed
    make: *** [run] Error 1

The third test case (use `col3` and `row3`) should return
`0x373737`, and the blue part of that color is `0x37` or decimal 55:

    $ make run
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp getcolor.s -o getcolor.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp calcpixel.s -o calcpixel.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp start.s -o start.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp mandel.s -o mandel.o
    ld --fatal-warnings getcolor.o calcpixel.o start.o mandel.o
    ./a.out
    Makefile:20: recipe for target 'run' failed
    make: *** [run] Error 55

After you get all three of these test cases working, run the full
suite of tests.
