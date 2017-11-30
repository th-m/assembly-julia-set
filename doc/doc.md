Create a file with one row of pixels
====================================

In this step you will change your `run` function to write a single
row of pixels to the output file in addition to the header that you
wrote earlier.


What to write
-------------

For this first step, you will create a file, write a header to it,
generate a single row of pixels with a gradient pattern, write it to
the file, close the file, and then return.

Your code should implement this pseudo-code:

```
fd = open(filename, flags, mode)
if fd < 0: return fail_open

# write the header
length = writeHeader(buffer, xsize, ysize)
status = write(fd, buffer, length)
if status < 0: return fail_writeheader

# write a single row of pixels
length = 0
for column in range(xsize):
    color = column << 8
    length += writeRGB(buffer+length, color)
    buffer[length] = ' '
    length += 1

# replace last space with a newline
buffer[length-1] = '\n'
status = write(fd, buffer, length)
if status < 0: return fail_writerow

# close the file
status = close(fd)
if status < 0: return fail_close
return 0
```
