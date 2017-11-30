#include "gtest/gtest.h"
#include <stdio.h>

extern "C" int run();
extern "C" int regwrapper();
extern "C" int (*target_function)();
extern "C" int bad_register;
extern "C" int xsize, ysize;

TEST(gradient, defaultsize) {
    target_function = run;

    xsize = 16;
    ysize = 768;
    int status = regwrapper();

    // self-reported status code should be zero (success)
    EXPECT_EQ(0, status);

    // open and read the file
    FILE *fp = fopen("fractal.ppm", "r");
    ASSERT_FALSE(fp == NULL);
    const int maxSize = 256;
    char buffer[maxSize+1];
    size_t size = fread(buffer, 1, maxSize, fp);
    ASSERT_TRUE(size > 0);
    buffer[size] = 0;
    status = fclose(fp);
    ASSERT_EQ(0, status);

    // check for a match
    EXPECT_EQ(size, 116);
    EXPECT_STREQ("P3\n16 768\n255\n0 0 0 0 1 0 0 2 0 0 3 0 0 4 0 0 5 0 0 6 0 0 7 0 0 8 0 0 9 0 0 10 0 0 11 0 0 12 0 0 13 0 0 14 0 0 15 0\n", buffer);
    EXPECT_EQ(0, bad_register);
}

TEST(gradient, differentsize) {
    target_function = run;

    xsize = 23;
    ysize = 45678;
    int status = regwrapper();

    // self-reported status code should be zero (success)
    EXPECT_EQ(0, status);

    // open and read the file
    FILE *fp = fopen("fractal.ppm", "r");
    ASSERT_FALSE(fp == NULL);
    const int maxSize = 256;
    char buffer[maxSize+1];
    size_t size = fread(buffer, 1, maxSize, fp);
    ASSERT_TRUE(size > 0);
    buffer[size] = 0;
    status = fclose(fp);
    ASSERT_EQ(0, status);

    // check for a match
    EXPECT_EQ(size, 167);
    EXPECT_STREQ("P3\n23 45678\n255\n"
        "0 0 0 0 1 0 0 2 0 0 3 0 0 4 0 0 5 0 0 6 0 0 7 0 "
        "0 8 0 0 9 0 0 10 0 0 11 0 0 12 0 0 13 0 0 14 0 0 15 0 "
        "0 16 0 0 17 0 0 18 0 0 19 0 0 20 0 0 21 0 0 22 0\n", buffer);
    EXPECT_EQ(0, bad_register);
}
