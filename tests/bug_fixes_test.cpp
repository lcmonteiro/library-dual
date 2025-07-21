#include <gtest/gtest.h>
#include <cmath>
#include <limits>

#include "dual.hpp"

/// @test Test that logarithm derivative is NaN for negative input (Bug Fix #1)
TEST(BugFixesTest, LogarithmNegativeInputDerivative)
{
    dual::number<double, 0> x(-1.0);
    auto result = std::log(x);
    
    // Both value and derivative should be NaN for negative input
    EXPECT_TRUE(std::isnan(result.value()));
    EXPECT_TRUE(std::isnan(result.dvalue<0>()));
}

/// @test Test that logarithm derivative is inf for zero input (Bug Fix #1)
TEST(BugFixesTest, LogarithmZeroInputDerivative)
{
    dual::number<double, 0> x(0.0);
    auto result = std::log(x);
    
    // Value should be -inf, derivative should be inf for zero input
    EXPECT_TRUE(std::isinf(result.value()) && result.value() < 0);
    EXPECT_TRUE(std::isinf(result.dvalue<0>()) && result.dvalue<0>() > 0);
}

/// @test Test that logarithm works correctly for positive input
TEST(BugFixesTest, LogarithmPositiveInput)
{
    dual::number<double, 0> x(std::exp(1.0));  // e
    auto result = std::log(x);
    
    // log(e) = 1, d/dx log(x) = 1/x = 1/e
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 1.0 / std::exp(1.0));
}

/// @test Test unary minus operator (Bug Fix #2)
TEST(BugFixesTest, UnaryMinusOperator)
{
    dual::number<double, 0> x(5.0);
    auto neg_x = -x;
    
    // -x should have value -5.0 and derivative -1.0
    EXPECT_DOUBLE_EQ(neg_x.value(), -5.0);
    EXPECT_DOUBLE_EQ(neg_x.dvalue<0>(), -1.0);
}

/// @test Test unary minus with complex expression
TEST(BugFixesTest, UnaryMinusComplexExpression)
{
    dual::number<double, 0> x(2.0);
    auto result = -(x * x);  // -(x^2)
    
    // -(x^2) = -4, d/dx -(x^2) = -2x = -4
    EXPECT_DOUBLE_EQ(result.value(), -4.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -4.0);
}

/// @test Test unary minus with zero
TEST(BugFixesTest, UnaryMinusZero)
{
    dual::number<double, 0> x(0.0);
    auto neg_x = -x;
    
    // -0 should be 0, derivative should still be -1
    EXPECT_DOUBLE_EQ(neg_x.value(), 0.0);
    EXPECT_DOUBLE_EQ(neg_x.dvalue<0>(), -1.0);
}

/// @test Test that functional utilities use correct parameter names (Bug Fix #3)
TEST(BugFixesTest, FunctionalUtilitiesParameterNames)
{
    // This test mainly checks that the code compiles with the corrected parameter names
    dual::number<double, 0> x(1.0);
    dual::number<double, 1> y(2.0);
    dual::number<double, 2> z(3.0);
    
    dual::array<dual::number<double, 0>, dual::number<double, 1>, dual::number<double, 2>> arr(x, y, z);
    
    // Test that summation works with corrected parameter names
    auto sum = dual::summation(arr, [](const auto& elem) { return elem.value(); });
    EXPECT_DOUBLE_EQ(sum, 6.0);  // 1 + 2 + 3 = 6
}

/// @test Test chain rule still works correctly after fixes
TEST(BugFixesTest, ChainRuleAfterFixes)
{
    dual::number<double, 0> x(1.0);
    
    // Test f(x) = -sin(log(x^2))
    auto x_squared = x * x;
    auto log_x_squared = std::log(x_squared);
    auto sin_log_x_squared = std::sin(log_x_squared);
    auto result = -sin_log_x_squared;
    
    // Manually calculate: f(x) = -sin(log(x^2)) = -sin(2*log(x))
    // f'(x) = -cos(2*log(x)) * (2/x) = -cos(2*log(1)) * 2 = -cos(0) * 2 = -2
    double expected_value = -std::sin(2.0 * std::log(1.0));  // -sin(0) = 0
    double expected_derivative = -std::cos(2.0 * std::log(1.0)) * 2.0;  // -cos(0) * 2 = -2
    
    EXPECT_DOUBLE_EQ(result.value(), expected_value);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), expected_derivative);
}

/// @test Test edge cases still work after fixes
TEST(BugFixesTest, EdgeCasesAfterFixes)
{
    // Test that sqrt still works correctly
    dual::number<double, 0> x(4.0);
    auto sqrt_result = std::sqrt(x);
    EXPECT_DOUBLE_EQ(sqrt_result.value(), 2.0);
    EXPECT_DOUBLE_EQ(sqrt_result.dvalue<0>(), 0.25);  // 1/(2*sqrt(4)) = 1/4
    
    // Test that division still works correctly
    dual::number<double, 0> numerator(6.0);
    dual::number<double, 1> denominator(2.0);
    auto div_result = numerator / denominator;
    EXPECT_DOUBLE_EQ(div_result.value(), 3.0);
    EXPECT_DOUBLE_EQ(div_result.dvalue<0>(), 0.5);  // d/d(numerator) (6/2) = 1/2
    EXPECT_DOUBLE_EQ(div_result.dvalue<1>(), -1.5); // d/d(denominator) (6/2) = -6/4 = -1.5
}

/// @test Test multiple derivative indices work with unary minus
TEST(BugFixesTest, UnaryMinusMultipleIndices)
{
    dual::number<double, 0, 1, 2> x(3.0);
    auto neg_x = -x;
    
    EXPECT_DOUBLE_EQ(neg_x.value(), -3.0);
    EXPECT_DOUBLE_EQ(neg_x.dvalue<0>(), -1.0);
    EXPECT_DOUBLE_EQ(neg_x.dvalue<1>(), -1.0);
    EXPECT_DOUBLE_EQ(neg_x.dvalue<2>(), -1.0);
}