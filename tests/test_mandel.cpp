#include "gtest/gtest.h"

extern "C" int mandel(int maxiters, double x, double y);
extern "C" int regwrapper(int maxiters, double x, double y);
extern "C" int (*target_function)(int maxiters, double x, double y);
extern "C" int bad_register;

TEST(mandel, trivial) {
    target_function = mandel;

    // try some points that are outside the largest circle
    // so they require only a single iteration
    int n = regwrapper(100, 10.0, 10.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 10.0, -10.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -10.0, 10.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -10.0, -10.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.0, -10.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.0, 10.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 10.0, 0.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -10.0, 0.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.0, 10.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    // try some values right on the boundary of the outer circle
    n = regwrapper(100, -2.0, 0.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 2.0, 0.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.0, -2.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.0, 2.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -2.0, 2.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -2.0, -2.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 2.0, -2.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 2.0, 2.0);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);
}

TEST(mandel, easy) {
    target_function = mandel;

    // points just inside the outer circle, which should escape
    // after a single full iteration
    int n = regwrapper(100, -1.4, 1.4);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.1, 1.5);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 1.4, -0.3);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -1.0, -1.3);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    // move in a little closer
    n = regwrapper(100, -1.0, -1.1);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -1.6, -0.52);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -0.62, -0.98);
    EXPECT_EQ(4, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -1.07, 0.51);
    EXPECT_EQ(5, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -0.74, -0.51);
    EXPECT_EQ(6, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -1.12, 0.38);
    EXPECT_EQ(7, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.38, -0.48);
    EXPECT_EQ(8, n);
    EXPECT_EQ(0, bad_register);
}

TEST(mandel, inside) {
    target_function = mandel;

    // points inside the set
    int n = regwrapper(100, 0.0, 0.0);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -1.09, 0.00);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.16, 0.46);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -0.21, -0.62);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -0.96, -0.23);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -0.24, 0.16);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -1.16, -0.00);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -0.48, 0.08);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, -0.07, 0.06);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.06, 0.46);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);
}

TEST(mandel, iterations) {
    target_function = mandel;

    // test the iteration limit
    int n = regwrapper(12, -1.23, -0.22);
    EXPECT_EQ(11, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(11, -1.23, -0.22);
    EXPECT_EQ(11, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(10, -1.23, -0.22);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(19, -1.24, -0.14);
    EXPECT_EQ(18, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(18, -1.24, -0.14);
    EXPECT_EQ(18, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(17, -1.24, -0.14);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(100, 0.35, -0.42);
    EXPECT_EQ(55, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(55, 0.35, -0.42);
    EXPECT_EQ(55, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(54, 0.35, -0.42);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);
}

TEST(mandel, random) {
    target_function = mandel;

    // test a bunch of randomly generated points
    int n = regwrapper(1000, 0.26, -0.03);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.30, 1.69);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.12, -0.34);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.04, -0.66);
    EXPECT_EQ(21, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.68, 1.63);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.86, -0.30);
    EXPECT_EQ(9, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.32, 1.45);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.74, 1.11);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.39, -0.36);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.89, -1.04);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.85, -0.44);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.61, 0.63);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.92, 1.58);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.42, 0.24);
    EXPECT_EQ(5, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.22, -0.78);
    EXPECT_EQ(133, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.07, 0.63);
    EXPECT_EQ(23, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.75, 0.10);
    EXPECT_EQ(33, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.33, -1.92);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.29, -0.73);
    EXPECT_EQ(6, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.49, -1.56);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.64, 0.46);
    EXPECT_EQ(22, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.81, 1.24);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.27, 0.61);
    EXPECT_EQ(68, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.58, -0.58);
    EXPECT_EQ(23, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.03, 0.25);
    EXPECT_EQ(553, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.67, 0.03);
    EXPECT_EQ(4, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.25, 0.58);
    EXPECT_EQ(39, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.75, 0.01);
    EXPECT_EQ(315, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.99, -0.47);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.07, 0.63);
    EXPECT_EQ(23, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.50, 1.96);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.48, 1.00);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.81, -0.44);
    EXPECT_EQ(7, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.81, -0.16);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.47, -1.36);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.13, 0.10);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.16, 0.90);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.91, -1.67);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.12, -0.64);
    EXPECT_EQ(25, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.36, 0.06);
    EXPECT_EQ(26, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.08, 0.23);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.31, -0.09);
    EXPECT_EQ(17, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.60, 0.29);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.60, 0.09);
    EXPECT_EQ(4, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.24, 0.65);
    EXPECT_EQ(58, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.61, 0.76);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.46, 0.19);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.73, -0.33);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.23, 1.36);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.00, -0.81);
    EXPECT_EQ(34, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.07, -1.13);
    EXPECT_EQ(4, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.41, 0.60);
    EXPECT_EQ(181, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.77, -0.12);
    EXPECT_EQ(27, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.75, 0.15);
    EXPECT_EQ(22, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.36, -0.67);
    EXPECT_EQ(37, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.27, -0.64);
    EXPECT_EQ(31, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.80, 0.73);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.58, -1.21);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.15, -0.60);
    EXPECT_EQ(20, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.55, 0.55);
    EXPECT_EQ(451, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.95, 1.98);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.21, 1.74);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.61, -0.14);
    EXPECT_EQ(4, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.50, -0.93);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.24, -0.12);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.06, 1.22);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.71, -0.67);
    EXPECT_EQ(5, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.90, -0.14);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.96, -0.24);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.32, 1.94);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.79, 0.06);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.81, -0.30);
    EXPECT_EQ(4, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.20, 0.44);
    EXPECT_EQ(6, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.37, -0.13);
    EXPECT_EQ(23, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.37, 0.02);
    EXPECT_EQ(99, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.47, 0.43);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.56, -0.14);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.89, -1.42);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.59, -1.20);
    EXPECT_EQ(3, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.57, 1.04);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.36, -0.12);
    EXPECT_EQ(640, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.18, 1.13);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.81, -0.82);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.81, -0.19);
    EXPECT_EQ(37, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.31, -1.37);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.48, -1.99);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.19, 0.66);
    EXPECT_EQ(8, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.76, -0.63);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.28, -1.09);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.10, 1.64);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.20, -0.48);
    EXPECT_EQ(5, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.01, 1.36);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.78, -1.10);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -1.90, -1.93);
    EXPECT_EQ(1, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.36, 0.98);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.36, -0.68);
    EXPECT_EQ(21, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 0.42, 0.21);
    EXPECT_EQ(62, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, 1.15, -0.54);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.30, 0.13);
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, bad_register);

    n = regwrapper(1000, -0.68, 1.81);
    EXPECT_EQ(2, n);
    EXPECT_EQ(0, bad_register);
}
