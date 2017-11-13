Create a file with a header
===========================

In this project, you will use the functions you have written in
previous steps to generate a complete .ppm image with a gradient
color fill.


start and run
-------------

You will be writing a standalone program, but it must also be tested
using a unit test framework. The included file `start.s` is
necessary when running the code as a standalone program. All it does
is call the function `run` and then exit.

When you are running your code using unit tests (for grading or the
"test" action), the `start.s` file will be ignored.

The bulk of your code for this project will be written in a function
called `run`.


System calls
------------

A system call is similar to a function call, except that the call is
being made to the operating system instead of to more code within
your program. The basic process is the same as for a function call,
with parameters going in the same registers (at least for the
parameters we will use). In addition, the system call number must be
loaded into the r7 register, and then instead of issuing a “bl”
instruction, you should issue a “svc #0” instruction.

For example, to write a message to stdout (which always has the file
descriptor 1):

``` asm
mov r0, #1                      @ stdout
ldr r1, =buffer                 @ where to find the data to write
mov r2, #20                     @ number of bytes to write
mov r7, #sys_write              @ sys_write is 1, defined elsewhere
svc #0
```

The result of the call is in r0 after the call finishes. If this
value is negative, it normally indicates an error.

While testing your code, it may be helpful to use an error status
code as the value in a call to exit. If you do this, then you can
look up the error code in this chart (the syscall result is the
error code negated):

``` c
#define EPERM        1  /* Operation not permitted */
#define ENOENT       2  /* No such file or directory */
#define ESRCH        3  /* No such process */
#define EINTR        4  /* Interrupted system call */
#define EIO          5  /* I/O error */
#define ENXIO        6  /* No such device or address */
#define E2BIG        7  /* Argument list too long */
#define ENOEXEC      8  /* Exec format error */
#define EBADF        9  /* Bad file number */
#define ECHILD      10  /* No child processes */
#define EAGAIN      11  /* Try again */
#define ENOMEM      12  /* Out of memory */
#define EACCES      13  /* Permission denied */
#define EFAULT      14  /* Bad address */
#define ENOTBLK     15  /* Block device required */
#define EBUSY       16  /* Device or resource busy */
#define EEXIST      17  /* File exists */
#define EXDEV       18  /* Cross-device link */
#define ENODEV      19  /* No such device */
#define ENOTDIR     20  /* Not a directory */
#define EISDIR      21  /* Is a directory */
#define EINVAL      22  /* Invalid argument */
#define ENFILE      23  /* File table overflow */
#define EMFILE      24  /* Too many open files */
#define ENOTTY      25  /* Not a typewriter */
#define ETXTBSY     26  /* Text file busy */
#define EFBIG       27  /* File too large */
#define ENOSPC      28  /* No space left on device */
#define ESPIPE      29  /* Illegal seek */
#define EROFS       30  /* Read-only file system */
#define EMLINK      31  /* Too many links */
#define EPIPE       32  /* Broken pipe */
#define EDOM        33  /* Math argument out of domain of func */
#define ERANGE      34  /* Math result not representable */
```

The syscalls you will need in this assignment are as follows:

*   4: `sys_write(fd, buffer, count)` returns the number of bytes
    written, or negative to signal an error.
*   5: `sys_open(filename, flags, mode)` returns the file
    descriptor, or negative to signal an error.
*   6: `sys_close(fd)` returns negative to signal an error.
*   1: `sys_exit(status)` does not return.


What to write
-------------

For this first step, you will create a file, write a header to it,
close the file, and then return.

Your code should implement this pseudo-code in `run.s`:

```
fd = open(filename, flags, mode)
if fd < 0: return fail_open

# write the header
length = writeHeader(buffer, xsize, ysize)
status = write(fd, buffer, length)
if status < 0: return fail_writeheader

# close the file
status = close(fd)
if status < 0: return fail_close
return 0
```

The starter code include constant definitions for flags and mode as
well as for the system calls you will need.

The starter code also include a file `params.s` that defines some
data in the data segment, including `filename`, `xsize`, and
`ysize`. You should use these values and not hard-code them
anywhere.
