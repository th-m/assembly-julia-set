#include "gtest/gtest.h"

extern "C" int writeHeader(char *buffer, int x, int y);
extern "C" int regwrapper(char *buffer, int x, int y);
extern "C" int (*target_function)(char *buffer, int x, int y);
extern "C" int bad_register;

TEST(writeHeader, all) {
    char buff[100];
    target_function = writeHeader;

    int n = regwrapper(buff, 0, 0);
    buff[n] = 0;
    EXPECT_EQ(strlen(buff), n);
    EXPECT_STREQ("P3\n0 0\n255\n", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 1, 2);
    buff[n] = 0;
    EXPECT_EQ(strlen(buff), n);
    EXPECT_STREQ("P3\n1 2\n255\n", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 1024, 768);
    buff[n] = 0;
    EXPECT_EQ(strlen(buff), n);
    EXPECT_STREQ("P3\n1024 768\n255\n", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 2560, 1440);
    buff[n] = 0;
    EXPECT_EQ(strlen(buff), n);
    EXPECT_STREQ("P3\n2560 1440\n255\n", buff);
    EXPECT_EQ(0, bad_register);
}
