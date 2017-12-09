#include "gtest/gtest.h"

extern "C" int remainder(int n, int d);
extern "C" int regwrapper(int n, int d);
extern "C" int (*target_function)(int n, int d);
extern "C" int bad_register;

TEST(remainder, all) {
    target_function = remainder;

    int n = regwrapper(25, 20);
    EXPECT_EQ(5, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(25, 21);
    EXPECT_EQ(4, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(25, 22);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(57, 5);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(57, 6);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(57, 7);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1234567, 87);
    EXPECT_EQ(37, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1234567, 88);
    EXPECT_EQ(15, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1234567, 89);
    EXPECT_EQ(48, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(123, 123);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(123, 124);
    EXPECT_EQ(123, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(123, 125);
    EXPECT_EQ(123, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 2);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(18769, 137);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(18769, 138);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);
}
