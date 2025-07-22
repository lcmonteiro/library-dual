#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test log(x) basic functionality
TEST(LogOperationTest, BasicLog)
{
    dual::number<double, 0> x(std::exp(1.0));  // e
    
    auto result = std::log(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0 / std::exp(1.0));  // d/dx log(x) = 1/x
}

/// @test Test log(1)
TEST(LogOperationTest, LogOne)
{
    dual::number<double, 0> x(1.0);
    
    auto result = std::log(x);
    
    EXPECT_DOUBLE_EQ(result.value(), 0.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);  // d/dx log(1) = 1/1 = 1
}

/// @test Test log with positive input
TEST(LogOperationTest, LogPositive)
{
    dual::number<double, 0> x(2.0);
    
    auto result = std::log(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::log(2.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.5);  // d/dx log(2) = 1/2
}

/// @test Test log with negative input (should produce NaN)
TEST(LogOperationTest, LogNegative)
{
    dual::number<double, 0> x(-1.0);
    
    auto result = std::log(x);
    
    EXPECT_TRUE(std::isnan(result.value()));
    EXPECT_TRUE(std::isnan(result.dvalue<0>()));  // Fixed bug: derivative should also be NaN
}

/// @test Test log(0) (should produce -inf)
TEST(LogOperationTest, LogZero)
{
    dual::number<double, 0> x(0.0);
    
    auto result = std::log(x);
    
    EXPECT_TRUE(std::isinf(result.value()) && result.value() < 0);
    EXPECT_TRUE(std::isinf(result.dvalue<0>()) && result.dvalue<0>() > 0);
}

/// @test Test log with very small positive input
TEST(LogOperationTest, LogVerySmall)
{
    dual::number<double, 0> x(1e-10);
    
    auto result = std::log(x);
    
    EXPECT_TRUE(std::isfinite(result.value()));
    EXPECT_LT(result.value(), -20.0);  // Should be very negative
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1e10);  // 1/(1e-10) = 1e10
}

/// @test Test log with large input
TEST(LogOperationTest, LogLarge)
{
    dual::number<double, 0> x(1e10);
    
    auto result = std::log(x);
    
    EXPECT_TRUE(std::isfinite(result.value()));
    EXPECT_GT(result.value(), 20.0);  // Should be large positive
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1e-10);  // 1/(1e10) = 1e-10
}

/// @test Test log with multiple indices
TEST(LogOperationTest, LogMultipleIndices)
{
    dual::number<double, 0, 1> x(4.0);
    
    auto result = std::log(x);
    
    EXPECT_DOUBLE_EQ(result.value(), std::log(4.0));
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.25);  // 1/4
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), 0.25);  // 1/4
}

/// @test Test log in chain rule
TEST(LogOperationTest, LogChainRule)
{
    dual::number<double, 0> x(2.0);
    
    // Test log(x^2)
    auto x_squared = x * x;
    auto result = std::log(x_squared);
    
    EXPECT_DOUBLE_EQ(result.value(), std::log(4.0));
    // d/dx log(x^2) = (1/x^2) * 2x = 2/x = 2/2 = 1
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0);
}

/// @test Test log-exp identity
TEST(LogOperationTest, LogExpIdentity)
{
    dual::number<double, 0> x(3.0);
    
    auto exp_result = std::exp(x);
    auto log_exp_result = std::log(exp_result);
    
    EXPECT_NEAR(log_exp_result.value(), x.value(), 1e-14);
    EXPECT_NEAR(log_exp_result.dvalue<0>(), x.dvalue<0>(), 1e-14);
}
