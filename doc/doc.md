Create a complete gradient image
================================

In this part, you will use the functions you have written in
previous projects to generate a complete .ppm image with a gradient
color fill.


What to write
-------------

Your code should implement this pseudo-code:

```
fd = open(filename, flags, mode)
if fd < 0: return fail_open

# write the header
length = writeHeader(buffer, xsize, ysize)
status = write(fd, buffer, length)
if status < 0: return fail_writeheader

# write all rows of pixels
for row in range(ysize):
    # write a single row of pixels
    length = 0
    for column in range(xsize):
	color = (row << 16) + (column << 8)
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

Testing
-------

You may wish to start by creating a simpler file. Change the size in
`params.s` to 8×8 instead of 256×256. The output should be this
exact file:

```
P3
8 8
255
0 0 0 0 1 0 0 2 0 0 3 0 0 4 0 0 5 0 0 6 0 0 7 0
1 0 0 1 1 0 1 2 0 1 3 0 1 4 0 1 5 0 1 6 0 1 7 0
2 0 0 2 1 0 2 2 0 2 3 0 2 4 0 2 5 0 2 6 0 2 7 0
3 0 0 3 1 0 3 2 0 3 3 0 3 4 0 3 5 0 3 6 0 3 7 0
4 0 0 4 1 0 4 2 0 4 3 0 4 4 0 4 5 0 4 6 0 4 7 0
5 0 0 5 1 0 5 2 0 5 3 0 5 4 0 5 5 0 5 6 0 5 7 0
6 0 0 6 1 0 6 2 0 6 3 0 6 4 0 6 5 0 6 6 0 6 7 0
7 0 0 7 1 0 7 2 0 7 3 0 7 4 0 7 5 0 7 6 0 7 7 0
```

Be sure to set it back to 256×256 to generate the complete gradient
image file.
