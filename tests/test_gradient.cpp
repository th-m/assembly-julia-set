#include "gtest/gtest.h"
#include <stdio.h>

extern "C" int run();
extern "C" int regwrapper();
extern "C" int (*target_function)();
extern "C" int bad_register;
extern "C" int xsize, ysize;

TEST(gradient, all) {
    target_function = run;

    xsize = 83;
    ysize = 116;
    int status = regwrapper();

    // self-reported status code should be zero (success)
    EXPECT_EQ(0, status);

    // open and read the file
    FILE *fp = fopen("fractal.ppm", "r");
    ASSERT_FALSE(fp == NULL);
    const int maxSize = 256*256*12 + 1000;
    char buffer[maxSize+1];
    size_t size = fread(buffer, 1, maxSize, fp);
    ASSERT_TRUE(size > 0);
    buffer[size] = 0;
    status = fclose(fp);
    ASSERT_EQ(0, status);

    // read the comparison file
    fp = fopen("tests/fractal.ppm", "r");
    ASSERT_FALSE(fp == NULL);
    char buffer2[maxSize+1];
    size_t size2 = fread(buffer2, 1, maxSize, fp);
    ASSERT_TRUE(size2 > 0);
    buffer2[size2] = 0;
    status = fclose(fp);
    ASSERT_EQ(0, status);

    // check for a match
    EXPECT_EQ(size, size2);
    int line = 1, col = 0;
    int mismatchcount = 0;
    for (size_t i = 0; i < size && mismatchcount < 10; i++) {
        if (buffer[i] == '\n') {
            line++;
            col = 0;
        }
        col++;
        if (buffer[i] != buffer2[i]) {
            ADD_FAILURE() << "Mismatch at line " << line << " column " << col;
            mismatchcount++;
        }
    }
    if (mismatchcount >= 10) {
        ADD_FAILURE() << "Too many mismatches, quitting";
    }
    EXPECT_EQ(0, bad_register);
}
