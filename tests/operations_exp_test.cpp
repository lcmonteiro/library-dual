#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test exp(x) basic functionality
TEST(ExpOperationTest, BasicExp)
{
    dual::number<double, 0> x(1.0);
    
    auto result = std::exp(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::exp(1.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), std::exp(1.0));  // d/dx exp(x) = exp(x)
}

/// @test Test exp(0)
TEST(ExpOperationTest, ExpZero)
{
    dual::number<double, 0> x(0.0);
    
    auto result = std::exp(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);  // d/dx exp(0) = exp(0) = 1
}

/// @test Test exp with negative input
TEST(ExpOperationTest, ExpNegative)
{
    dual::number<double, 0> x(-1.0);
    
    auto result = std::exp(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::exp(-1.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), std::exp(-1.0));  // d/dx exp(-1) = exp(-1)
}

/// @test Test exp with large positive input
TEST(ExpOperationTest, ExpLargePositive)
{
    dual::number<double, 0> x(10.0);
    
    auto result = std::exp(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::exp(10.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), std::exp(10.0));
}

/// @test Test exp with large negative input
TEST(ExpOperationTest, ExpLargeNegative)
{
    dual::number<double, 0> x(-10.0);
    
    auto result = std::exp(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::exp(-10.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), std::exp(-10.0));
}

/// @test Test exp overflow
TEST(ExpOperationTest, ExpOverflow)
{
    dual::number<double, 0> x(1000.0);
    
    auto result = std::exp(x);
    
    EXPECT_TRUE(std::isinf(result.value()));
    EXPECT_TRUE(std::isinf(result.dvalue<0>()));
}

/// @test Test exp underflow
TEST(ExpOperationTest, ExpUnderflow)
{
    dual::number<double, 0> x(-1000.0);
    
    auto result = std::exp(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 0.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);
}

/// @test Test exp with multiple indices
TEST(ExpOperationTest, ExpMultipleIndices)
{
    dual::number<double, 0, 1> x(2.0);
    
    auto result = std::exp(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::exp(2.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), std::exp(2.0));
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), std::exp(2.0));
}

/// @test Test exp in chain rule
TEST(ExpOperationTest, ExpChainRule)
{
    dual::number<double, 0> x(1.0);
    
    // Test exp(x^2)
    auto x_squared = x * x;
    auto result = std::exp(x_squared);
    
    EXPECT_DOUBLE_EQ(result.value(), std::exp(1.0));
    // d/dx exp(x^2) = exp(x^2) * 2x = exp(1) * 2 * 1 = 2*exp(1)
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 2.0 * std::exp(1.0));
}
