#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test dual - dual with same index
TEST(MinusOperationTest, DualMinusDualSameIndex)
{
    dual::number<double, 0> x(7.0);
    dual::number<double, 0> y(3.0);
    
    auto result = x - y;
    
    EXPECT_DOUBLE_EQ(result.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);  // dx - dy = 1 - 1 = 0
}

/// @test Test dual - dual with different indices
TEST(MinusOperationTest, DualMinusDualDifferentIndices)
{
    dual::number<double, 0> x(8.0);
    dual::number<double, 1> y(3.0);
    
    auto result = x - y;
    
    EXPECT_DOUBLE_EQ(result.value(), 5.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);   // dx = 1
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), -1.0);  // -dy = -1
}

/// @test Test dual - scalar
TEST(MinusOperationTest, DualMinusScalar)
{
    dual::number<double, 0> x(10.0);
    double scalar = 4.0;
    
    auto result = x - scalar;
    
    EXPECT_DOUBLE_EQ(result.value(), 6.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);  // d/dx (x - c) = 1
}

/// @test Test scalar - dual
TEST(MinusOperationTest, ScalarMinusDual)
{
    double scalar = 10.0;
    dual::number<double, 0> x(3.0);
    
    auto result = scalar - x;
    
    EXPECT_DOUBLE_EQ(result.value(), 7.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0);  // d/dx (c - x) = -1
}

/// @test Test subtraction with zero
TEST(MinusOperationTest, SubtractionWithZero)
{
    dual::number<double, 0> x(5.0);
    dual::number<double, 0> zero(0.0);
    
    auto result1 = x - zero;
    auto result2 = zero - x;
    
    EXPECT_DOUBLE_EQ(result1.value(), 5.0);
    EXPECT_DOUBLE_EQ(result1.dvalue<0>(), 0.0);  // 1 - 1 = 0
    
    EXPECT_DOUBLE_EQ(result2.value(), -5.0);
    EXPECT_DOUBLE_EQ(result2.dvalue<0>(), 0.0);  // 1 - 1 = 0
}

/// @test Test subtraction with negative numbers
TEST(MinusOperationTest, SubtractionWithNegative)
{
    dual::number<double, 0> x(3.0);
    dual::number<double, 0> y(-2.0);
    
    auto result = x - y;
    
    EXPECT_DOUBLE_EQ(result.value(), 5.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);  // 1 - 1 = 0
}

/// @test Test self subtraction
TEST(MinusOperationTest, SelfSubtraction)
{
    dual::number<double, 0> x(7.0);
    
    auto result = x - x;
    
    EXPECT_DOUBLE_EQ(result.value(), 0.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);  // 1 - 1 = 0
}
