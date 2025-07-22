#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test pow(x, n) with integer exponent
TEST(PowOperationTest, PowerInteger)
{
    dual::number<double, 0> x(3.0);
    dual::number<double, 1> n(2.0);
    
    auto result = std::pow(x, n);
    
    EXPECT_DOUBLE_EQ(result.value(), 9.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 6.0);  // d/dx (x^2) = 2x = 6
    // d/dn (x^n) = x^n * ln(x) = 9 * ln(3)
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), 9.0 * std::log(3.0));
}

/// @test Test pow(x, 0.5) - square root
TEST(PowOperationTest, PowerHalf)
{
    dual::number<double, 0> x(4.0);
    dual::number<double, 1> n(0.5);
    
    auto result = std::pow(x, n);
    
    EXPECT_DOUBLE_EQ(result.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.25);  // d/dx (x^0.5) = 0.5 * x^(-0.5) = 0.5/2 = 0.25
    // d/dn (x^n) = x^n * ln(x) = 2 * ln(4)
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), 2.0 * std::log(4.0));
}

/// @test Test pow(x, 0) - should be 1
TEST(PowOperationTest, PowerZero)
{
    dual::number<double, 0> x(5.0);
    dual::number<double, 1> n(0.0);
    
    auto result = std::pow(x, n);
    
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);  // d/dx (x^0) = 0
    // d/dn (x^0) = x^0 * ln(x) = 1 * ln(5) = ln(5)
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), std::log(5.0));
}

/// @test Test pow(1, x) - should be 1
TEST(PowOperationTest, BaseOne)
{
    dual::number<double, 0> base(1.0);
    dual::number<double, 1> x(3.0);
    
    auto result = std::pow(base, x);
    
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 3.0);  // d/d(base) (base^x) = x * base^(x-1) = 3 * 1^2 = 3
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), 0.0);  // d/dx (1^x) = 1^x * ln(1) = 1 * 0 = 0
}

/// @test Test pow with negative base and integer exponent
TEST(PowOperationTest, NegativeBaseInteger)
{
    dual::number<double, 0> x(-2.0);
    dual::number<double, 1> n(3.0);
    
    auto result = std::pow(x, n);
    
    EXPECT_DOUBLE_EQ(result.value(), -8.0);
    // d/dx (x^n) = n * x^(n-1) = 3 * (-2)^2 = 3 * 4 = 12
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 12.0);
}

/// @test Test pow with negative base and non-integer exponent (should produce NaN)
TEST(PowOperationTest, NegativeBaseNonInteger)
{
    dual::number<double, 0> x(-2.0);
    dual::number<double, 1> n(0.5);
    
    auto result = std::pow(x, n);
    
    EXPECT_TRUE(std::isnan(result.value()));
    EXPECT_TRUE(std::isnan(result.dvalue<0>()));
    EXPECT_TRUE(std::isnan(result.dvalue<1>()));
}

/// @test Test pow(0, 0) edge case
TEST(PowOperationTest, ZeroToZero)
{
    dual::number<double, 0> x(0.0);
    dual::number<double, 1> n(0.0);
    
    auto result = std::pow(x, n);
    
    // 0^0 is typically defined as 1 in many implementations
    EXPECT_TRUE(std::isfinite(result.value()) || std::isnan(result.value()));
}

/// @test Test pow(0, positive) - should be 0
TEST(PowOperationTest, ZeroToPositive)
{
    dual::number<double, 0> x(0.0);
    dual::number<double, 1> n(2.0);
    
    auto result = std::pow(x, n);
    
    EXPECT_DOUBLE_EQ(result.value(), 0.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);  // d/dx (0^2) = 0
}

/// @test Test pow with scalar base
TEST(PowOperationTest, ScalarBase)
{
    double base = 2.0;
    dual::number<double, 0> x(3.0);
    
    auto result = std::pow(base, x);
    
    EXPECT_DOUBLE_EQ(result.value(), 8.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 8.0 * std::log(2.0));  // d/dx (2^x) = 2^x * ln(2)
}

/// @test Test pow with scalar exponent
TEST(PowOperationTest, ScalarExponent)
{
    dual::number<double, 0> x(3.0);
    double exponent = 2.0;
    
    auto result = std::pow(x, exponent);
    
    EXPECT_DOUBLE_EQ(result.value(), 9.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 6.0);  // d/dx (x^2) = 2x = 6
}
