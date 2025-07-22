#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test sqrt(x) basic functionality
TEST(SqrtOperationTest, BasicSqrt)
{
    dual::number<double, 0> x(4.0);
    
    auto result = std::sqrt(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.25);  // d/dx sqrt(x) = 1/(2*sqrt(x)) = 1/4
}

/// @test Test sqrt(1)
TEST(SqrtOperationTest, SqrtOne)
{
    dual::number<double, 0> x(1.0);
    
    auto result = std::sqrt(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.5);  // d/dx sqrt(1) = 1/(2*1) = 0.5
}

/// @test Test sqrt(0) - derivative should be infinite
TEST(SqrtOperationTest, SqrtZero)
{
    dual::number<double, 0> x(0.0);
    
    auto result = std::sqrt(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 0.0);
    EXPECT_TRUE(std::isinf(result.dvalue<0>()));  // d/dx sqrt(0) = 1/(2*0) = inf
}

/// @test Test sqrt with negative input (should produce NaN)
TEST(SqrtOperationTest, SqrtNegative)
{
    dual::number<double, 0> x(-4.0);
    
    auto result = std::sqrt(x);
    
    EXPECT_TRUE(std::isnan(result.value()));
    EXPECT_TRUE(std::isnan(result.dvalue<0>()));  // Both value and derivative should be NaN
}

/// @test Test sqrt with large input
TEST(SqrtOperationTest, SqrtLarge)
{
    dual::number<double, 0> x(1e10);
    
    auto result = std::sqrt(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 1e5);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0/(2.0 * 1e5));  // 1/(2*sqrt(1e10)) = 5e-6
}

/// @test Test sqrt with small input
TEST(SqrtOperationTest, SqrtSmall)
{
    dual::number<double, 0> x(1e-10);
    
    auto result = std::sqrt(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 1e-5);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0/(2.0 * 1e-5));  // 1/(2*sqrt(1e-10)) = 5e4
}

/// @test Test sqrt with multiple indices
TEST(SqrtOperationTest, SqrtMultipleIndices)
{
    dual::number<double, 0, 1> x(9.0);
    
    auto result = std::sqrt(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0/6.0);  // 1/(2*3) = 1/6
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), 1.0/6.0);  // 1/(2*3) = 1/6
}

/// @test Test sqrt in chain rule
TEST(SqrtOperationTest, SqrtChainRule)
{
    dual::number<double, 0> x(2.0);
    
    // Test sqrt(x^2) = |x|, but for positive x it's just x
    auto x_squared = x * x;
    auto result = std::sqrt(x_squared);
    
    EXPECT_DOUBLE_EQ(result.value(), 2.0);
    // d/dx sqrt(x^2) = d/dx |x| = sign(x) = 1 for positive x
    // Using chain rule: (1/(2*sqrt(x^2))) * 2x = (1/(2*2)) * 2*2 = 1
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);
}

/// @test Test sqrt-square identity
TEST(SqrtOperationTest, SqrtSquareIdentity)
{
    dual::number<double, 0> x(5.0);
    
    auto sqrt_result = std::sqrt(x);
    auto square_result = sqrt_result * sqrt_result;
    
    EXPECT_NEAR(square_result.value(), x.value(), 1e-14);
    // This is more complex due to chain rule, but should be close to 1
    EXPECT_NEAR(square_result.dvalue<0>(), x.dvalue<0>(), 1e-14);
}

/// @test Test perfect squares
TEST(SqrtOperationTest, PerfectSquares)
{
    std::vector<double> perfect_squares = {1.0, 4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0, 81.0, 100.0};
    
    for (double val : perfect_squares) {
        dual::number<double, 0> x(val);
        auto result = std::sqrt(x);
        
        double expected_value = std::sqrt(val);
        double expected_derivative = 1.0 / (2.0 * expected_value);
        
        EXPECT_DOUBLE_EQ(result.value(), expected_value);
        EXPECT_DOUBLE_EQ(result.dvalue<0>(), expected_derivative);
    }
}
