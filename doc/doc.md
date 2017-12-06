Mandelbrot main loop
====================

Implement the main Mandelbrot calculation in a function called
“mandel”:

* `mandel(maxIterations, x, y)` → `iterations`

Note that `maxIterations` is an integer, while `x` and `y` are
float values. The calling convention dictates that the integer
parameter is passed in r0 (as usual) while the float parameters are
passed in d0 and d1, respectively. The return value (an integer)
is still return in r0.


The formula
-----------

The Mandelbrot set is a set of complex numbers. To determine whether
or not a number is in the set, a formula is applied iteratively. If
the number ever achieves a magnitude of 2.0 or higher, it will
“escape”, meaning that the value will get larger and larger without
bounds if the process is continued. These numbers are not part of
the set. The Mandelbrot set consists of all complex numbers that
never escape that threshold.

If we plot complex numbers on a plane, this means that members of
the Mandelbrot set will remained confined to a circle on the plane
of radius 2.0, centered on the origin. For numbers outside the set,
the plot would eventually escape the circle and then would rapidly
fly out toward infinity.

The formula is simple. If the number is c, we start with z set to
zero and repeat the formula:

* z’ = z² + c

Bear in mind that z and c are complex numbers. We can represent a
complex number using two real numbers—representing the real and
imaginary parts, respectively—approximated using two doubles. When
expressed this way, the formula becomes:

* z’ = (zr + i·zi)² + (cr + i·ci)
* z’ = zr² + i²·zi² + i·2·zr·zi + cr + i·ci

Since i² = -1, we can simplify to:

* z’ = zr² - zi² + i·2·zr·zi + cr + i·ci

Splitting z’ into its real and imaginary parts, we get:

* zr’ = zr² - zi² + cr
* zi’ = 2·zr·zi + ci

To make it easier to follow, we can use “a” and “b” instead of zr
and zi, and “x” and “y” instead of “cr” and “ci”, giving a formula
of:

* a’ = a² - b² + x
* b’ = 2·a·b + y

To test if a given value of z has reached the threshold of |z| ≥
2.0, we test if a² + b² ≥ 4.0 (this avoids an expensive √ (square
root) operation).

When given a single value for c and a maximum number of iterations
n, your job is to apply the formula up to n times and see if the
threshold is ever reached. If not, you will assume that c is in the
Mandelbrot set, and if it is, you should note how many iterations
were required to reach the threshold value.


Float instructions
------------------

Floating point calculations require different registers than the
familiar integer registers. d0 through d15 each hold 64-bit floats.
The instructions you will need to user are summarized on the
assembly language reference posted on the course website.

d0–d15 are all caller-saved, meaning that you are free to use any of
them within a function, but you must save any important values
before making a function call.


The calculation
---------------

The parameters *x* and *y* will be passed in using the d0 and d1
registers, respectively, so it is convenient to leave them there. I
recommend allocating registers as follows:

* d0: x
* d1: y
* d2: a
* d3: b
* d4: a²
* d5: b²
* d6: a² + b²
* d7: 4.0

You can compute a² by copying a into place, then multiplying it by
itself. Once a² and b² are computed, getting a² + b² is simple. Load
4.0 into d7 right at the beginning, then you will have it readily
available for comparisons.

The computation can proceed according to the following pseudo code:

* load 4.0 into d7
* copy maxIterations to r1
* set r0 (number of iterations) to 1
* copy x into a, and y into b
* forever:
    * compute a², b², and a² + b²
    * if a² + b² ≥ 4.0, return iterations
    * increment iteration count
    * if iterations > maxIterations, return 0
    * compute b = 2ab + y (this can be computed in-place,
        overwriting the old value of b)
    * compute a = a² - b² + x (this can be computed in-place,
        overwriting the old value of a; note that a² and b² are
        already computed)

Technically, a and b both start at 0.0, but the first iteration is
not very interesting, so we skip it by copying x to a and y to b,
then jumping directly to the bailout test. Only if the bailout test
(and max iteration test) fails do we compute the next values for a
and b.


Testing
-------

A `start.s` file is provided. It will call `mandel` with a simple
test case, and will use the return value of `mandel` as the exit
status code. For the default test case, you should expect an exit
status code of 2. When you run the code with `make run` or
 `grind action run`, make should report that as the error number.
For example:

    $ make run
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp start.s -o start.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp mandel.s -o mandel.o
    ld --fatal-warnings start.o mandel.o
    ./a.out
    Makefile:20: recipe for target 'run' failed
    make: *** [run] Error 2

When you get that much working, change `start.s` to load `x2` and
`y2` instead of `x1` and `y1` as the test values when it calls
`mandel`. The expected output for that point is 0 (the point is
inside the Mandelbrot set, so your code should bail out and return
zero). make will report this as success, since a zero return value
normally indicates that:

    $ make run
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp start.s -o start.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp mandel.s -o mandel.o
    ld --fatal-warnings start.o mandel.o
    ./a.out

The third test case (use `x3` and `y3`) should return 68, resulting
in something like:

    $ make run
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp start.s -o start.o
    as -g -march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp mandel.s -o mandel.o
    ld --fatal-warnings start.o mandel.o
    ./a.out
    Makefile:20: recipe for target 'run' failed
    make: *** [run] Error 68

After you get all three of these test cases working, run the full
suite of tests using `grind action test` or `make test` (if you are
running on an ARM machine). Do not forget to run `grind grade` when
you pass all of the tests.
