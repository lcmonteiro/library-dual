#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test negate basic functionality
TEST(NegateOperationTest, BasicNegate)
{
    dual::number<double, 0> x(5.0);
    
    auto result = -x;
    
    EXPECT_DOUBLE_EQ(result.value(), -5.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0);  // d/dx (-x) = -1
}

/// @test Test negate with zero
TEST(NegateOperationTest, NegateZero)
{
    dual::number<double, 0> x(0.0);
    
    auto result = -x;
    
    EXPECT_DOUBLE_EQ(result.value(), 0.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0);  // derivative is still -1
}

/// @test Test negate with negative number
TEST(NegateOperationTest, NegateNegative)
{
    dual::number<double, 0> x(-3.0);
    
    auto result = -x;
    
    EXPECT_DOUBLE_EQ(result.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0);  // d/dx (-x) = -1
}

/// @test Test double negation
TEST(NegateOperationTest, DoubleNegation)
{
    dual::number<double, 0> x(4.0);
    
    auto result = -(-x);
    
    EXPECT_DOUBLE_EQ(result.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);  // d/dx (-(-x)) = 1
}

/// @test Test negate in expression
TEST(NegateOperationTest, NegateInExpression)
{
    dual::number<double, 0> x(2.0);
    
    auto result = -(x * x);  // -(x^2)
    
    EXPECT_DOUBLE_EQ(result.value(), -4.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -4.0);  // d/dx -(x^2) = -2x = -4
}

/// @test Test negate with multiple indices
TEST(NegateOperationTest, MultipleIndices)
{
    dual::number<double, 0, 1, 2> x(3.0);
    
    auto result = -x;
    
    EXPECT_DOUBLE_EQ(result.value(), -3.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), -1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<2>(), -1.0);
}

/// @test Test negate with large numbers
TEST(NegateOperationTest, LargeNumbers)
{
    dual::number<double, 0> x(1e10);
    
    auto result = -x;
    
    EXPECT_DOUBLE_EQ(result.value(), -1e10);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0);
}
