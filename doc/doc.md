Integer remainder
=================

In order to compute colors, you will need the ability to find the
remainder of an integer division operation. The ARM processors we
are using have multiplication instructions, but not division or
remainder instructions. In this step you will implement an integer
remainder function:

* `remainder(n, d)` → `n%d`

There are a few ways to compute integer remainder (the modulus
operator). The naive approach works like this:

```
def remainder(n, d):
    while n >= d:
        n = n - d
    return n
```

In this example, *n* is the numerator and *d* the denominator of a
fraction, or *n* is the number and *d* is the divisor, however you
prefer to think about it.

This algorithm simply subtracts *d* from *n* until *n* is smaller
than *d*. This is terribly inefficient if *n* is significantly
larger than *d*.

A better approach works by subtracting multiples of *d* from *n*
instead, thus cutting the number of iterations needed. Specifically,
we multiply *d* by a power of two (we can compute this by shifting
*d* left some number of times), subtract the result from *n* (but
only if the shifted value is still smaller than *n*) and repeat with
a smaller power of two. Consider this code:

```
def remainder(n, d):
    shift = 31
    while shift >= 0:
        if n >= d<<shift:
            n = n - d<<shift
        shift = shift - 1
    return n
```

Note that `d<<shift` means *d* left shifted *shift* times.

This version shifts *d* left 31 times, then 30, then 29, etc.
(ignore the problem of overflow for the moment), each time
subtracting the result from *n*, but only when *n* is big enough for
the subtraction to make sense. By combining these subtractions, this
approach can subtract any possible mulitiple of *d* from *n*,
leaving only the remainder behind. Note that this code runs a fixed
number of iterations (32) instead of a variable number like the
first version.

This can be improved if we can calculate the number of leading zeros
in each number. Instead of starting by shifting *d* to the left 31
times, we chose a shift value that will result in the first 1 bit of
the shifted *d* being in the same position as the first 1 bit in
*n*. Consider these values for *n* and *d*:

*   *n* = 01010110
*   *d* = 00001011

With this pair of numbers, there is no point in shifting *d* left 4
or more times, as that will guarantee a result bigger than *n*. We
can figure out that 3 is a good number of shifts to begin with by
subtracting the number of leading zeros in *n* (1) from the number
of leading zeros in *d* (4) giving 3.

The ARM instruction set includes an instruction to count the leading
zeros in a number:

```
clz     r0, r1          @ r0 = # of leading zeros in r1
```

With this, our remainder algorithm looks like:

```
def remainder(n, d):
    if n < d:
        return n
    shift = (# leading zeros in d) - (# leading zeros in n)
    while shift >= 0:
        if n >= d<<shift:
            n = n - d<<shift
        shift = shift - 1
    return n
```
