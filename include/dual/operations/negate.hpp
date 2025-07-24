/// @file negate.hpp
/// @brief Defines negation operations for dual numbers, including derivative computations
///        and element-wise array transforms.

#pragma once

#include "dual/helpers/operations.hpp"

namespace dual
{
  /// @brief Functor for computing the negation and its derivative for dual numbers.
  struct negate : unary_operation<negate>
  {
    /// @brief Computes the negation of a value.
    /// @tparam T The numeric type of the value.
    /// @param v The input value.
    /// @return The negation of v.
    template <class T>
    auto value(const T &v) const
    {
      return -v;
    }

    /// @brief Computes the derivative of the negation operation.
    /// @tparam T The numeric type of the value.
    /// @param n A duo containing the input value and its derivative.
    /// @return The negation of the derivative component.
    template <class T>
    auto dvalue(const duo<T> &n) const
    {
      return -n.d;
    }
  };

  /// @brief Overloads the unary minus operator for dual numbers.
  /// @tparam T The numeric type.
  /// @param n The dual number.
  /// @return The result of negating n using dual arithmetic.
  template <class T, negate::enable_t<T> = 0>
  inline auto operator-(const T &n)
  {
    return std::invoke(negate{}, n);
  }

  /// @brief Functor for element-wise negation transformation on arrays.
  struct negate_transform : transform_unary_operation<negate_transform>
  {
    /// @brief Applies negation to an array element.
    /// @tparam T The numeric type of the element.
    /// @param n The array element.
    /// @return The negation of the element.
    template <class T>
    auto transform(const T &n) const
    {
      return -n;
    }
  };

  /// @brief Overloads the unary minus operator for arrays of dual numbers.
  /// @tparam T The array type.
  /// @param n The array of dual numbers.
  /// @return An array with each element negated.
  template <class T, negate_transform::enable_t<T> = 0>
  inline auto operator-(const T &n)
  {
    return std::invoke(negate_transform{}, n);
  }

} // namespace dual
