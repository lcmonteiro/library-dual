#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test dual + dual with same index
TEST(PlusOperationTest, DualPlusDualSameIndex)
{
    dual::number<double, 0> x(3.0);
    dual::number<double, 0> y(4.0);
    
    auto result = x + y;
    
    EXPECT_DOUBLE_EQ(result.value(), 7.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 2.0);  // dx + dy = 1 + 1 = 2
}

/// @test Test dual + dual with different indices
TEST(PlusOperationTest, DualPlusDualDifferentIndices)
{
    dual::number<double, 0> x(2.0);
    dual::number<double, 1> y(5.0);
    
    auto result = x + y;
    
    EXPECT_DOUBLE_EQ(result.value(), 7.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);  // dx = 1
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), 1.0);  // dy = 1
}

/// @test Test dual + scalar
TEST(PlusOperationTest, DualPlusScalar)
{
    dual::number<double, 0> x(3.0);
    double scalar = 5.0;
    
    auto result = x + scalar;
    
    EXPECT_DOUBLE_EQ(result.value(), 8.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);  // d/dx (x + c) = 1
}

/// @test Test scalar + dual
TEST(PlusOperationTest, ScalarPlusDual)
{
    double scalar = 2.0;
    dual::number<double, 0> x(6.0);
    
    auto result = scalar + x;
    
    EXPECT_DOUBLE_EQ(result.value(), 8.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);  // d/dx (c + x) = 1
}

/// @test Test addition commutativity
TEST(PlusOperationTest, AdditionCommutativity)
{
    dual::number<double, 0> x(4.0);
    dual::number<double, 1> y(7.0);
    
    auto result1 = x + y;
    auto result2 = y + x;
    
    EXPECT_DOUBLE_EQ(result1.value(), result2.value());
    EXPECT_DOUBLE_EQ(result1.dvalue<0>(), result2.dvalue<0>());
    EXPECT_DOUBLE_EQ(result1.dvalue<1>(), result2.dvalue<1>());
}

/// @test Test addition with zero
TEST(PlusOperationTest, AdditionWithZero)
{
    dual::number<double, 0> x(5.0);
    dual::number<double, 0> zero(0.0);
    
    auto result = x + zero;
    
    EXPECT_DOUBLE_EQ(result.value(), 5.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 2.0);  // 1 + 1 = 2
}
