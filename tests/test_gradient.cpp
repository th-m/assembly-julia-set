#include "gtest/gtest.h"
#include <stdio.h>

extern "C" int run();
extern "C" int regwrapper();
extern "C" int (*target_function)();
extern "C" int bad_register;
extern "C" int xsize, ysize;

TEST(gradient, defaultsize) {
    target_function = run;

    xsize = 1024;
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
    EXPECT_EQ(size, 16);
    EXPECT_STREQ("P3\n1024 768\n255\n", buffer);
    EXPECT_EQ(0, bad_register);
}

TEST(gradient, differentsize) {
    target_function = run;

    xsize = 123;
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
    EXPECT_EQ(size, 17);
    EXPECT_STREQ("P3\n123 45678\n255\n", buffer);
    EXPECT_EQ(0, bad_register);
}
