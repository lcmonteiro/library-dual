#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test dual * dual with same index
TEST(MultipliesOperationTest, DualMultiplyDualSameIndex)
{
    dual::number<double, 0> x(3.0);
    dual::number<double, 0> y(4.0);
    
    auto result = x * y;
    
    EXPECT_DOUBLE_EQ(result.value(), 12.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 7.0);  // x*dy + y*dx = 3*1 + 4*1 = 7
}

/// @test Test dual * dual with different indices
TEST(MultipliesOperationTest, DualMultiplyDualDifferentIndices)
{
    dual::number<double, 0> x(2.0);
    dual::number<double, 1> y(5.0);
    
    auto result = x * y;
    
    EXPECT_DOUBLE_EQ(result.value(), 10.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 5.0);  // y*dx = 5*1 = 5
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), 2.0);  // x*dy = 2*1 = 2
}

/// @test Test dual * scalar
TEST(MultipliesOperationTest, DualMultiplyScalar)
{
    dual::number<double, 0> x(3.0);
    double scalar = 5.0;
    
    auto result = x * scalar;
    
    EXPECT_DOUBLE_EQ(result.value(), 15.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 5.0);  // d/dx (x * c) = c
}

/// @test Test scalar * dual
TEST(MultipliesOperationTest, ScalarMultiplyDual)
{
    double scalar = 4.0;
    dual::number<double, 0> x(6.0);
    
    auto result = scalar * x;
    
    EXPECT_DOUBLE_EQ(result.value(), 24.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 4.0);  // d/dx (c * x) = c
}

/// @test Test multiplication with zero
TEST(MultipliesOperationTest, MultiplicationWithZero)
{
    dual::number<double, 0> x(5.0);
    dual::number<double, 0> zero(0.0);
    
    auto result = x * zero;
    
    EXPECT_DOUBLE_EQ(result.value(), 0.0);
    // Product rule: d/dx(u*v) = u*dv + v*du = x*d(zero) + zero*dx = 5*1 + 0*1 = 5
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 5.0);
}

/// @test Test multiplication with one
TEST(MultipliesOperationTest, MultiplicationWithOne)
{
    dual::number<double, 0> x(7.0);
    dual::number<double, 0> one(1.0);
    
    auto result = x * one;
    
    EXPECT_DOUBLE_EQ(result.value(), 7.0);
    // Product rule: d/dx(u*v) = u*dv + v*du = x*d(one) + one*dx = 7*1 + 1*1 = 8
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 8.0);
}

/// @test Test multiplication commutativity
TEST(MultipliesOperationTest, MultiplicationCommutativity)
{
    dual::number<double, 0> x(3.0);
    dual::number<double, 1> y(4.0);
    
    auto result1 = x * y;
    auto result2 = y * x;
    
    EXPECT_DOUBLE_EQ(result1.value(), result2.value());
    EXPECT_DOUBLE_EQ(result1.dvalue<0>(), result2.dvalue<0>());
    EXPECT_DOUBLE_EQ(result1.dvalue<1>(), result2.dvalue<1>());
}

/// @test Test square (x * x)
TEST(MultipliesOperationTest, Square)
{
    dual::number<double, 0> x(3.0);
    
    auto result = x * x;
    
    EXPECT_DOUBLE_EQ(result.value(), 9.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 6.0);  // d/dx (x^2) = 2x = 6
}

/// @test Test multiplication with negative numbers
TEST(MultipliesOperationTest, MultiplicationWithNegative)
{
    dual::number<double, 0> x(3.0);
    dual::number<double, 0> y(-2.0);
    
    auto result = x * y;
    
    EXPECT_DOUBLE_EQ(result.value(), -6.0);
    // Product rule: d/dx(u*v) = u*dv + v*du = x*dy + y*dx = 3*1 + (-2)*1 = 1
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);
}
