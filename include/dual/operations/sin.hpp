/// @file sin.hpp
/// @brief Defines sine operations for dual numbers, including derivative computations
///        and element-wise array transforms.

#pragma once

#include <cmath>
#include "dual/operations.hpp"

namespace dual
{
  /// @brief Functor for computing sine and its derivative for dual numbers.
  struct sin : unary_operation<sin>
  {
    /// @brief Computes the sine of a value.
    /// @tparam T The numeric type of the value.
    /// @param v The input value.
    /// @return The sine of v.
    template <class T>
    auto value(const T &v) const
    {
      return std::sin(v);
    }

    /// @brief Computes the derivative of the sine operation.
    /// @tparam T The numeric type of the value.
    /// @param n A duo containing the input value and its derivative.
    /// @return The derivative of sin(n.v).
    template <class T>
    auto dvalue(const duo<T> &n) const
    {
      return std::cos(n.v) * n.d;
    }
  };
} // namespace dual

namespace std
{
  /// @brief Overloads the sin function for dual numbers.
  /// @tparam T The numeric type.
  /// @param n The dual number.
  /// @return The result of applying sine using dual arithmetic.
  template <class T, dual::sin::enable_t<T> = 0>
  inline auto sin(const T &n)
  {
    return std::invoke(dual::sin{}, n);
  }
} // namespace std

namespace dual
{
  /// @brief Functor for element-wise sine transformation on arrays.
  struct sin_transform : transform_unary_operation<sin_transform>
  {
    /// @brief Applies sine to an array element.
    /// @tparam T The numeric type of the element.
    /// @param n The array element.
    /// @return The sine of the element.
    template <class T>
    auto transform(const T &n) const
    {
      return std::sin(n);
    }
  };
} // namespace dual

namespace std
{
  /// @brief Overloads the sin function for arrays of dual numbers.
  /// @tparam T The array type.
  /// @param n The array of dual numbers.
  /// @return An array with each element as the sine of the original element.
  template <class T, dual::sin_transform::enable_t<T> = 0>
  inline auto sin(const T &n)
  {
    return std::invoke(dual::sin_transform{}, n);
  }
} // namespace std
