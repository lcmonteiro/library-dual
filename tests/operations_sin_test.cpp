#include <gtest/gtest.h>

#include "dual.hpp"

/// @test Evaluates sin(0) and its derivative.
TEST(SinFunctionTest, SinAtZero)
{
    dual::number<double, 0> x(0.0);
    auto result = std::sin(x);

    EXPECT_DOUBLE_EQ(result.value(), 0.0);     // sin(0) = 0
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0); // d/dx sin(x) at x=0 is cos(0) = 1
}

/// @test Evaluates sin(pi/2) and its derivative.
TEST(SinFunctionTest, SinAtPiOverTwo)
{
    dual::number<double, 0> x(M_PI_2);
    auto result = std::sin(x);

    EXPECT_DOUBLE_EQ(result.value(), 1.0);      // sin(pi/2) = 1
    EXPECT_NEAR(result.dvalue<0>(), 0.0, 1e-9); // d/dx sin(x) at x=pi/2 is cos(pi/2) ≈ 0
}

/// @test Evaluates sin(pi) and its derivative.
TEST(SinFunctionTest, SinAtPi)
{
    dual::number<double, 0> x(M_PI);
    auto result = std::sin(x);

    EXPECT_NEAR(result.value(), 0.0, 1e-9);     // sin(pi) = 0
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0); // d/dx sin(x) at x=pi is cos(pi) = -1
}

/// @test Evaluates sin(-pi/2) and its derivative.
TEST(SinFunctionTest, SinAtNegativePiOverTwo)
{
    dual::number<double, 0> x(-M_PI_2);
    auto result = std::sin(x);

    EXPECT_DOUBLE_EQ(result.value(), -1.0);     // sin(-pi/2) = -1
    EXPECT_NEAR(result.dvalue<0>(), 0.0, 1e-9); // d/dx sin(x) at x=-pi/2 is cos(-pi/2) ≈ 0
}

/// @test Evaluates sin(1.0) and its derivative.
TEST(SinFunctionTest, SinAtOne)
{
    dual::number<double, 0> x(1.0); // x = 1, dx = 1
    auto result = std::sin(x);

    EXPECT_DOUBLE_EQ(result.value(), std::sin(1.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), std::cos(1.0));
}
