#include "gtest/gtest.h"

extern "C" int calcPixel(int maxiters, int col, int row);
extern "C" int regwrapper(int maxiters, int col, int row);
extern "C" int (*target_function)(int maxiters, int col, int row);
extern "C" int bad_register;

TEST(calcPixel, black) {
    target_function = calcPixel;

    // test some black pixels
    int rgb = regwrapper(255, 142, 113);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 97, 163);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 125, 165);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 140, 153);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 125, 130);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 86, 110);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 132, 136);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 110, 157);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 121, 157);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 68, 125);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 114, 87);
    EXPECT_EQ(0x000000, rgb);
    EXPECT_EQ(0, bad_register);
}

TEST(calcPixel, lowiters) {
    target_function = calcPixel;

    // test some low iteration values
    int rgb = regwrapper(255, 254, 212);
    EXPECT_EQ(0x010101, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 210, 30);
    EXPECT_EQ(0x010101, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 132, 243);
    EXPECT_EQ(0x020202, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 249, 19);
    EXPECT_EQ(0x010101, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 185, 120);
    EXPECT_EQ(0x030303, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 236, 152);
    EXPECT_EQ(0x020202, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 164, 30);
    EXPECT_EQ(0x020202, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 212, 146);
    EXPECT_EQ(0x020202, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 113, 197);
    EXPECT_EQ(0x060606, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 64, 50);
    EXPECT_EQ(0x030303, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 32, 160);
    EXPECT_EQ(0x030303, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 5, 70);
    EXPECT_EQ(0x010101, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 43, 250);
    EXPECT_EQ(0x010101, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 175, 223);
    EXPECT_EQ(0x020202, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 183, 221);
    EXPECT_EQ(0x020202, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 86, 251);
    EXPECT_EQ(0x010101, rgb);
    EXPECT_EQ(0, bad_register);
}

TEST(calcPixel, highiters) {
    target_function = calcPixel;

    // test some high iteration values
    int rgb = regwrapper(255, 114, 79);
    EXPECT_EQ(0x343434, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 139, 90);
    EXPECT_EQ(0x373737, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 153, 113);
    EXPECT_EQ(0x353535, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 50, 118);
    EXPECT_EQ(0xdcdcdc, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 50, 138);
    EXPECT_EQ(0xdcdcdc, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 49, 135);
    EXPECT_EQ(0x808080, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 115, 76);
    EXPECT_EQ(0xd0d0d0, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 145, 97);
    EXPECT_EQ(0x333333, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 70, 111);
    EXPECT_EQ(0x353535, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 127, 80);
    EXPECT_EQ(0x343434, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 153, 113);
    EXPECT_EQ(0x353535, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 70, 113);
    EXPECT_EQ(0x414141, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 50, 120);
    EXPECT_EQ(0xfefefe, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 104, 89);
    EXPECT_EQ(0x4f4f4f, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 39, 129);
    EXPECT_EQ(0x585858, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 75, 115);
    EXPECT_EQ(0x353535, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 82, 110);
    EXPECT_EQ(0xc5c5c5, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 154, 148);
    EXPECT_EQ(0x363636, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 102, 90);
    EXPECT_EQ(0x686868, rgb);
    EXPECT_EQ(0, bad_register);

    rgb = regwrapper(255, 110, 169);
    EXPECT_EQ(0x7a7a7a, rgb);
    EXPECT_EQ(0, bad_register);
}
