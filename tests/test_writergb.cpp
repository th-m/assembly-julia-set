#include "gtest/gtest.h"

extern "C" int writeRGB(char *buffer, int rgb);
extern "C" int regwrapper(char *buffer, int rgb);
extern "C" int (*target_function)(char *buffer, int rgb);
extern "C" int bad_register;

TEST(writeRGB, zero) {
    char buff[100];
    target_function = writeRGB;

    int n = regwrapper(buff, 0);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("0 0 0", buff);
    EXPECT_EQ(0, bad_register);
}

TEST(writeRGB, red) {
    char buff[100];
    target_function = writeRGB;

    int n = regwrapper(buff, 0x010000);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("1 0 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x090000);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("9 0 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x0a0000);
    EXPECT_EQ(6, n);
    buff[n] = 0;
    EXPECT_STREQ("10 0 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0xff0000);
    EXPECT_EQ(7, n);
    buff[n] = 0;
    EXPECT_STREQ("255 0 0", buff);
    EXPECT_EQ(0, bad_register);
}

TEST(writeRGB, green) {
    char buff[100];
    target_function = writeRGB;

    int n = regwrapper(buff, 0x000100);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("0 1 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x000900);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("0 9 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x000c00);
    EXPECT_EQ(6, n);
    buff[n] = 0;
    EXPECT_STREQ("0 12 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x006400);
    EXPECT_EQ(7, n);
    buff[n] = 0;
    EXPECT_STREQ("0 100 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x00fe00);
    EXPECT_EQ(7, n);
    buff[n] = 0;
    EXPECT_STREQ("0 254 0", buff);
    EXPECT_EQ(0, bad_register);
}

TEST(writeRGB, blue) {
    char buff[100];
    target_function = writeRGB;

    int n = regwrapper(buff, 0x000001);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("0 0 1", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x000008);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("0 0 8", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x000020);
    EXPECT_EQ(6, n);
    buff[n] = 0;
    EXPECT_STREQ("0 0 32", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x000099);
    EXPECT_EQ(7, n);
    buff[n] = 0;
    EXPECT_STREQ("0 0 153", buff);
    EXPECT_EQ(0, bad_register);
}

TEST(writeRGB, all) {
    char buff[100];
    target_function = writeRGB;

    int n = regwrapper(buff, 0x010101);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("1 1 1", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x020304);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("2 3 4", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x203040);
    EXPECT_EQ(8, n);
    buff[n] = 0;
    EXPECT_STREQ("32 48 64", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0x776655);
    EXPECT_EQ(10, n);
    buff[n] = 0;
    EXPECT_STREQ("119 102 85", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0xffffff);
    EXPECT_EQ(11, n);
    buff[n] = 0;
    EXPECT_STREQ("255 255 255", buff);
    EXPECT_EQ(0, bad_register);
}

TEST(writeRGB, extra) {
    char buff[100];
    target_function = writeRGB;

    int n = regwrapper(buff, 0xff000000);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("0 0 0", buff);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(buff, 0xff010203);
    EXPECT_EQ(5, n);
    buff[n] = 0;
    EXPECT_STREQ("1 2 3", buff);
    EXPECT_EQ(0, bad_register);
}
