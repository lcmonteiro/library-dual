#include <gtest/gtest.h>
#include <cmath>
#include "dual.hpp"

/// @test Test dual / dual with same index
TEST(DividesOperationTest, DualDivideDualSameIndex)
{
    dual::number<double, 0> x(6.0);
    dual::number<double, 0> y(2.0);
    
    auto result = x / y;
    
    EXPECT_DOUBLE_EQ(result.value(), 3.0);
    // d/dx (u/v) = (v*du - u*dv)/v^2 = (2*1 - 6*1)/4 = -4/4 = -1
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -1.0);
}

/// @test Test dual / dual with different indices
TEST(DividesOperationTest, DualDivideDualDifferentIndices)
{
    dual::number<double, 0> x(8.0);
    dual::number<double, 1> y(2.0);
    
    auto result = x / y;
    
    EXPECT_DOUBLE_EQ(result.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.5);   // d/dx (x/y) = 1/y = 1/2
    EXPECT_DOUBLE_EQ(result.dvalue<1>(), -2.0);  // d/dy (x/y) = -x/y^2 = -8/4 = -2
}

/// @test Test dual / scalar
TEST(DividesOperationTest, DualDivideScalar)
{
    dual::number<double, 0> x(10.0);
    double scalar = 5.0;
    
    auto result = x / scalar;
    
    EXPECT_DOUBLE_EQ(result.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.2);  // d/dx (x/c) = 1/c = 1/5
}

/// @test Test scalar / dual
TEST(DividesOperationTest, ScalarDivideDual)
{
    double scalar = 12.0;
    dual::number<double, 0> x(3.0);
    
    auto result = scalar / x;
    
    EXPECT_DOUBLE_EQ(result.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -4.0/3.0);  // d/dx (c/x) = -c/x^2 = -12/9 = -4/3
}

/// @test Test division by one
TEST(DividesOperationTest, DivisionByOne)
{
    dual::number<double, 0> x(7.0);
    dual::number<double, 0> one(1.0);
    
    auto result = x / one;
    
    EXPECT_DOUBLE_EQ(result.value(), 7.0);
    // d/dx (x/1) = (1*dx - x*d(1))/1^2 = (1*1 - 7*1)/1 = -6
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), -6.0);
}

/// @test Test self division
TEST(DividesOperationTest, SelfDivision)
{
    dual::number<double, 0> x(5.0);
    
    auto result = x / x;
    
    EXPECT_DOUBLE_EQ(result.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 0.0);  // d/dx (x/x) = (x*1 - x*1)/x^2 = 0
}

/// @test Test division with negative numbers
TEST(DividesOperationTest, DivisionWithNegative)
{
    dual::number<double, 0> x(-6.0);
    dual::number<double, 0> y(2.0);
    
    auto result = x / y;
    
    EXPECT_DOUBLE_EQ(result.value(), -3.0);
    // d/dx (-6/2) = (2*1 - (-6)*1)/4 = (2 + 6)/4 = 2
    EXPECT_DOUBLE_EQ(result.dvalue<0>(), 2.0);
}

/// @test Test division by zero (should produce infinity)
TEST(DividesOperationTest, DivisionByZero)
{
    dual::number<double, 0> x(5.0);
    dual::number<double, 1> zero(0.0);
    
    auto result = x / zero;
    
    EXPECT_TRUE(std::isinf(result.value()));
    EXPECT_TRUE(std::isinf(result.dvalue<0>()) || std::isnan(result.dvalue<0>()));
    EXPECT_TRUE(std::isinf(result.dvalue<1>()) || std::isnan(result.dvalue<1>()));
}

/// @test Test small number division
TEST(DividesOperationTest, SmallNumberDivision)
{
    dual::number<double, 0> x(1e-10);
    dual::number<double, 0> y(2e-10);
    
    auto result = x / y;
    
    EXPECT_DOUBLE_EQ(result.value(), 0.5);
    // Should handle small numbers correctly
    EXPECT_TRUE(std::isfinite(result.dvalue<0>()));
}
