#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test cos(0)
TEST(CosOperationTest, CosZero)
{
    dual::number<double, 0> x(0.0);
    
    auto result = std::cos(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);  // d/dx cos(0) = -sin(0) = 0
}

/// @test Test cos(π/2)
TEST(CosOperationTest, CosPiOverTwo)
{
    dual::number<double, 0> x(M_PI_2);
    
    auto result = std::cos(x);
    
    EXPECT_NEAR(result.value(), 0.0, 1e-9);
    EXPECT_NEAR(result.dvalue<0>(), -1.0, 1e-9);  // d/dx cos(π/2) = -sin(π/2) = -1
}

/// @test Test cos(π)
TEST(CosOperationTest, CosPi)
{
    dual::number<double, 0> x(M_PI);
    
    auto result = std::cos(x);
    
    EXPECT_NEAR(result.value(), -1.0, 1e-9);
    EXPECT_NEAR(result.dvalue<0>(), 0.0, 1e-9);  // d/dx cos(π) = -sin(π) = 0
}

/// @test Test cos(2π)
TEST(CosOperationTest, CosTwoPi)
{
    dual::number<double, 0> x(2.0 * M_PI);
    
    auto result = std::cos(x);
    
    EXPECT_NEAR(result.value(), 1.0, 1e-9);
    EXPECT_NEAR(result.dvalue<0>(), 0.0, 1e-9);  // d/dx cos(2π) = -sin(2π) = 0
}

/// @test Test cos(-π/2)
TEST(CosOperationTest, CosNegativePiOverTwo)
{
    dual::number<double, 0> x(-M_PI_2);
    
    auto result = std::cos(x);
    
    EXPECT_NEAR(result.value(), 0.0, 1e-9);
    EXPECT_NEAR(result.dvalue<0>(), 1.0, 1e-9);  // d/dx cos(-π/2) = -sin(-π/2) = -(-1) = 1
}

/// @test Test cos(π/4)
TEST(CosOperationTest, CosPiOverFour)
{
    dual::number<double, 0> x(M_PI_4);
    
    auto result = std::cos(x);
    
    EXPECT_NEAR(result.value(), std::sqrt(2.0)/2.0, 1e-9);
    EXPECT_NEAR(result.dvalue<0>(), -std::sqrt(2.0)/2.0, 1e-9);  // d/dx cos(π/4) = -sin(π/4) = -√2/2
}

/// @test Test cos with arbitrary value
TEST(CosOperationTest, CosArbitrary)
{
    dual::number<double, 0> x(1.5);
    
    auto result = std::cos(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::cos(1.5));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -std::sin(1.5));  // d/dx cos(x) = -sin(x)
}

/// @test Test cos with negative input
TEST(CosOperationTest, CosNegative)
{
    dual::number<double, 0> x(-2.0);
    
    auto result = std::cos(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::cos(-2.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -std::sin(-2.0));  // d/dx cos(-2) = -sin(-2) = sin(2)
}

/// @test Test cos with multiple indices
TEST(CosOperationTest, CosMultipleIndices)
{
    dual::number<double, 0, 1> x(1.0);
    
    auto result = std::cos(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::cos(1.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -std::sin(1.0));
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), -std::sin(1.0));
}

/// @test Test cos in chain rule
TEST(CosOperationTest, CosChainRule)
{
    dual::number<double, 0> x(1.0);
    
    // Test cos(x^2)
    auto x_squared = x * x;
    auto result = std::cos(x_squared);
    
    EXPECT_DOUBLE_EQ(result.value(), std::cos(1.0));
    // d/dx cos(x^2) = -sin(x^2) * 2x = -sin(1) * 2 * 1 = -2*sin(1)
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -2.0 * std::sin(1.0));
}

/// @test Test cos-sin relationship
TEST(CosOperationTest, CosSinRelationship)
{
    dual::number<double, 0> x(0.7);
    
    auto cos_result = std::cos(x);
    auto sin_result = std::sin(x);
    
    // cos^2 + sin^2 = 1
    auto sum_of_squares = cos_result * cos_result + sin_result * sin_result;
    EXPECT_NEAR(sum_of_squares.value(), 1.0, 1e-14);
}
